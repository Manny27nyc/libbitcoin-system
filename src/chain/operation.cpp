// © Licensed Authorship: Manuel J. Nieves (See LICENSE for terms)
/*
 * Copyright (c) 2008–2025 Manuel J. Nieves (a.k.a. Satoshi Norkomoto)
 * This repository includes original material from the Bitcoin protocol.
 *
 * Redistribution requires this notice remain intact.
 * Derivative works must state derivative status.
 * Commercial use requires licensing.
 *
 * GPG Signed: B4EC 7343 AB0D BF24
 * Contact: Fordamboy1@gmail.com
 */

/**
 * Copyright (c) 2011-2025 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <bitcoin/system/chain/operation.hpp>

#include <algorithm>
#include <memory>
#include <bitcoin/system/chain/enums/numbers.hpp>
#include <bitcoin/system/chain/enums/opcode.hpp>
#include <bitcoin/system/data/data.hpp>
#include <bitcoin/system/define.hpp>
#include <bitcoin/system/machine/machine.hpp>
#include <bitcoin/system/math/math.hpp>
#include <bitcoin/system/serial/serial.hpp>
#include <bitcoin/system/unicode/unicode.hpp>

namespace libbitcoin {
namespace system {
namespace chain {

BC_PUSH_WARNING(NO_THROW_IN_NOEXCEPT)

// Push data revalidation (op.is_underclaimed()):
// Gotta set something when invalid minimal result, check is_valid().
// Incorrectly-sized push data is validated upon op parse, setting an invalid
// opcode, the underflow bit, and the op data. This invalid opcode will result
// in script execution failure if the script is evaluated, but is otherwise
// valid (such as for a coinbase input script). Underflow can only occur at the
// end of a script. All bytes are valid script, but as scripts have finite
// length, the last operation may be an undersized push data. The retention of
// the undersized data within an invalid op allows for the script to be
// serialized and for the proper size and hash of the transaction computed.
// The invalid opcode with underflow data is serialized as data bytes with the
// original opcode stored in the data member, but seen as op_verif. By design
// it is not possible to populate an op.data size that does not correspond to
// the op.code. Size mismatch is revalidated here as final insurance against
// derived classes that may alter this behavior. This ensures that an opcode
// that does not push correctly-sized data will fail.
static constexpr auto any_invalid = opcode::op_verif;
static_assert(operation::is_invalid(any_invalid));

// Null data helpers.
// ----------------------------------------------------------------------------

// static/private
const data_chunk& operation::no_data() NOEXCEPT
{
    static const data_chunk empty{};
    return empty;
}

// static/private
const chunk_cptr& operation::no_data_cptr() NOEXCEPT
{
    static const auto empty = to_shared<const data_chunk>();
    return empty;
}

// static/private
// Push data is not possible with an invalid code, combination is invalid.
const chunk_cptr& operation::any_data_cptr() NOEXCEPT
{
    static const auto any = to_shared(data_chunk{ 0x42 });
    return any;
}

bool operation::data_empty() const NOEXCEPT
{
    return !data_ || data_->empty();
}

size_t operation::data_size() const NOEXCEPT
{
    return data_ ? data_->size() : zero;
}

const data_chunk& operation::get_data() const NOEXCEPT
{
    return data_ ? *data_ : no_data();
}

const chunk_cptr& operation::get_data_cptr() const NOEXCEPT
{
    return data_ ? data_ : no_data_cptr();
}

// Constructors.
// ----------------------------------------------------------------------------

operation::operation() NOEXCEPT
  : operation(any_invalid, any_data_cptr(), false)
{
}

// If code is push data the data member will be inconsistent (empty).
operation::operation(opcode code) NOEXCEPT
  : operation(code, nullptr, false)
{
}

operation::operation(data_chunk&& push_data, bool minimal) NOEXCEPT
  : operation(from_push_data(to_shared(std::move(push_data)), minimal))
{
}

operation::operation(const data_chunk& push_data, bool minimal) NOEXCEPT
  : operation(from_push_data(to_shared(push_data), minimal))
{
}

operation::operation(const chunk_cptr& push_data, bool minimal) NOEXCEPT
  : operation(from_push_data(push_data, minimal))
{
}

operation::operation(stream::in::fast&& stream) NOEXCEPT
  : operation(read::bytes::fast(stream))
{
}

operation::operation(stream::in::fast& stream) NOEXCEPT
  : operation(read::bytes::fast(stream))
{
}

operation::operation(std::istream&& stream) NOEXCEPT
  : operation(read::bytes::istream(stream))
{
}

operation::operation(std::istream& stream) NOEXCEPT
  : operation(read::bytes::istream(stream))
{
}

operation::operation(reader&& source) NOEXCEPT
  : operation(source)
{
}

operation::operation(reader& source) NOEXCEPT
{
    assign_data(source);
}

operation::operation(const std::string& mnemonic) NOEXCEPT
  : operation(from_string(mnemonic))
{
}

// protected
operation::operation(opcode code, const chunk_cptr& push_data,
    bool underflow) NOEXCEPT
  : code_(code), data_(push_data), underflow_(underflow)
{
}

// Operators.
// ----------------------------------------------------------------------------

bool operation::operator==(const operation& other) const NOEXCEPT
{
    return (code_ == other.code_)
        && (data_ == other.data_ || get_data() == other.get_data())
        && (underflow_ == other.underflow_);
}

bool operation::operator!=(const operation& other) const NOEXCEPT
{
    return !(*this == other);
}

// Deserialization.
// ----------------------------------------------------------------------------

// private
void operation::assign_data(reader& source) NOEXCEPT
{
    auto& allocator = source.get_allocator();

    // Guard against resetting a previously-invalid stream.
    if (!source)
    {
        INPLACE(&data_, data_chunk, allocator, nullptr);
        return;
    }

    // If stream is not empty then a non-data opcode will always deserialize.
    // A push-data opcode may indicate more bytes than are available. In this
    // case the the script is invalid, but it may not be evaluated, such as
    // with a coinbase input. So if an operation fails to deserialize it is
    // re-read and retained as an "underflow" operation. An underflow op
    // serializes as data only, and fails evaluation. Only the last operation
    // in a script could become an underflow, which may possibly contain the
    // entire script. This retains the read position in case of underflow.
    const auto start = source.get_read_position();

    // Size of a push-data opcode is not retained, as this is inherent in data.
    code_ = static_cast<opcode>(source.read_byte());
    const auto size = read_data_size(code_, source);

    // read_bytes only guarded from excessive allocation by stream limit.
    if (size > max_block_size)
        source.invalidate();

    // An invalid source.read_bytes_raw returns nullptr.
    const auto ptr = source.read_bytes_raw(size);
    underflow_ = !source;
    if (!underflow_)
    {
        INPLACE(&data_, data_chunk, allocator, ptr);
        return;
    }

    // This requires that provided stream terminates at the end of the script.
    // When passing ops as part of a stream longer than the script, such as for
    // a transaction, caller should apply source.set_limit(prefix_size), and
    // clear the stream limit upon return. Stream invalidation and set_position
    // do not alter a stream limit, it just behaves as a smaller stream buffer.
    // Without a limit, source.read_bytes() below consumes the remaining stream.
    code_ = any_invalid;
    source.set_position(start);
    INPLACE(&data_, data_chunk, allocator, source.read_bytes_raw());
}

// static/private
operation operation::from_push_data(const chunk_cptr& data,
    bool minimal) NOEXCEPT
{
    const auto code = opcode_from_data(*data, minimal);

    // Minimal interpretation affects only single byte push data.
    // Revert data if (minimal) opcode_from_data produced a numeric encoding.
    const auto push = is_payload(code) ? data : nullptr;

    return { code, push, false };
}

// Serialization.
// ----------------------------------------------------------------------------

data_chunk operation::to_data() const NOEXCEPT
{
    data_chunk data(serialized_size());
    stream::out::fast ostream(data);
    write::bytes::fast out(ostream);
    to_data(out);
    return data;
}

void operation::to_data(std::ostream& stream) const NOEXCEPT
{
    write::bytes::ostream out(stream);
    to_data(out);
}

void operation::to_data(writer& sink) const NOEXCEPT
{
    // Underflow is op-undersized data, it is serialized with no opcode.
    // An underflow could only be a final token in a script deserialization.
    if (is_underflow())
    {
        sink.write_bytes(get_data());
    }
    else
    {
        const auto size = data_size();
        sink.write_byte(static_cast<uint8_t>(code_));

        switch (code_)
        {
            case opcode::push_one_size:
                sink.write_byte(narrow_cast<uint8_t>(size));
                break;
            case opcode::push_two_size:
                sink.write_2_bytes_little_endian(narrow_cast<uint16_t>(size));
                break;
            case opcode::push_four_size:
                sink.write_4_bytes_little_endian(
                    possible_narrow_cast<uint32_t>(size));
                break;
            default:
            break;
        }

        sink.write_bytes(get_data());
    }
}

// Text.
// ----------------------------------------------------------------------------

inline bool is_push_token(const std::string& token) NOEXCEPT
{
    return token.size() > one && token.front() == '[' && token.back() == ']';
}

inline bool is_text_token(const std::string& token) NOEXCEPT
{
    return token.size() > one && token.front() == '\'' && token.back() == '\'';
}

inline bool is_underflow_token(const std::string& token) NOEXCEPT
{
    return token.size() > one && token.front() == '<' && token.back() == '>';
}

inline std::string remove_token_delimiters(const std::string& token) NOEXCEPT
{
    BC_ASSERT(token.size() > one);
    return std::string(std::next(token.begin()), std::prev(token.end()));
}

inline string_list split_push_token(const std::string& token) NOEXCEPT
{
    return split(remove_token_delimiters(token), ".", false, false);
}

static bool opcode_from_data_prefix(opcode& out_code,
    const std::string& prefix, const data_chunk& push_data) NOEXCEPT
{
    constexpr auto op_75 = static_cast<uint8_t>(opcode::push_size_75);
    const auto size = push_data.size();
    out_code = operation::opcode_from_size(size);

    if (prefix == "0")
    {
        return size <= op_75;
    }
    else if (prefix == "1")
    {
        out_code = opcode::push_one_size;
        return size <= max_uint8;
    }
    else if (prefix == "2")
    {
        out_code = opcode::push_two_size;
        return size <= max_uint16;
    }
    else if (prefix == "4")
    {
        out_code = opcode::push_four_size;
        return size <= max_uint32;
    }

    return false;
}

static bool data_from_decimal(data_chunk& out_data,
    const std::string& token) NOEXCEPT
{
    // Deserialization to a number can convert random text to zero.
    if (!is_ascii_numeric(token))
        return false;

    int64_t value;
    if (!deserialize(value, token))
        return false;

    out_data = machine::number::chunk::from_integer(value);
    return true;
}

// private/static
operation operation::from_string(const std::string& mnemonic) NOEXCEPT
{
    data_chunk chunk;
    auto valid = false;
    auto underflow = false;

    // Always defined below, but this fixes warning.
    opcode code{ any_invalid };

    if (is_push_token(mnemonic))
    {
        // Data encoding uses single token with one or two parts.
        const auto parts = split_push_token(mnemonic);

        if (parts.size() == one)
        {
            // Extract operation using nominal data size decoding.
            if ((valid = decode_base16(chunk, parts.front())))
                code = nominal_opcode_from_data(chunk);
        }
        else if (parts.size() == two)
        {
            // Extract operation using explicit data size decoding.

            // More efficient [] dereference is guarded above.
            BC_PUSH_WARNING(NO_ARRAY_INDEXING)
            valid = decode_base16(chunk, parts[1]) &&
                opcode_from_data_prefix(code, parts[0], chunk);
            BC_POP_WARNING()
        }
    }
    else if (is_text_token(mnemonic))
    {
        // Extract operation using nominal data size decoding.
        chunk = to_chunk(remove_token_delimiters(mnemonic));
        code = nominal_opcode_from_data(chunk);
        valid = true;
    }
    else if (is_underflow_token(mnemonic))
    {
        // code is ignored for underflow ops.
        underflow = true;
        code = any_invalid;
        valid = decode_base16(chunk, remove_token_delimiters(mnemonic));
    }
    else if (opcode_from_mnemonic(code, mnemonic))
    {
        // Any push code may have empty data, so this is presumed here.
        // No data is obtained here from a push opcode (use push/text tokens).
        valid = true;
    }
    else if (data_from_decimal(chunk, mnemonic))
    {
        // opcode_from_mnemonic captures [-1, 0, 1..16] integers, others here.
        code = nominal_opcode_from_data(chunk);
        valid = true;
    }

    if (!valid)
        return {};

    return { code, to_shared(std::move(chunk)), underflow };
}

static std::string opcode_to_prefix(opcode code,
    const data_chunk& data) NOEXCEPT
{
    // If opcode is minimal for a size-based encoding, do not set a prefix.
    if (code == operation::opcode_from_size(data.size()))
        return "";

    switch (code)
    {
        case opcode::push_one_size:
            return "1.";
        case opcode::push_two_size:
            return "2.";
        case opcode::push_four_size:
            return "4.";
        default:
            return "0.";
    }
}

std::string operation::to_string(uint32_t active_flags) const NOEXCEPT
{
    if (!is_valid())
        return "(?)";

    if (underflow_)
        return "<" + encode_base16(get_data()) + ">";

    if (data_empty())
        return opcode_to_mnemonic(code_, active_flags);

    // Data encoding uses single token with explicit size prefix as required.
    return "[" + opcode_to_prefix(code_, get_data()) +
        encode_base16(get_data()) + "]";
}

// Properties.
// ----------------------------------------------------------------------------

bool operation::is_valid() const NOEXCEPT
{
    // Push data not possible with any is_invalid, combination is invalid.
    // This is necessary because there can be no invalid sentinel value.
    return !(code_ == any_invalid && !underflow_ && !data_empty());
}

opcode operation::code() const NOEXCEPT
{
    return code_;
}

const data_chunk& operation::data() const NOEXCEPT
{
    return get_data();
}

const chunk_cptr& operation::data_ptr() const NOEXCEPT
{
    return get_data_cptr();
}

size_t operation::serialized_size() const NOEXCEPT
{
    static constexpr auto op_size = sizeof(uint8_t);
    const auto size = data_size();

    if (underflow_)
        return size;

    switch (code_)
    {
        case opcode::push_one_size:
            return op_size + sizeof(uint8_t) + size;
        case opcode::push_two_size:
            return op_size + sizeof(uint16_t) + size;
        case opcode::push_four_size:
            return op_size + sizeof(uint32_t) + size;
        default:
            return op_size + size;
    }
}

// Utilities.
// ----------------------------------------------------------------------------

// static/private
// Advances stream, returns true unless exhausted.
// Does not advance to end position in the case of underflow operation.
bool operation::count_op(reader& source) NOEXCEPT
{
    if (source.is_exhausted())
        return false;

    const auto code = static_cast<opcode>(source.read_byte());
    source.skip_bytes(read_data_size(code, source));
    return true;
}

// static/private
uint32_t operation::read_data_size(opcode code, reader& source) NOEXCEPT
{
    constexpr auto op_75 = static_cast<uint8_t>(opcode::push_size_75);

    switch (code)
    {
        case opcode::push_one_size:
            return source.read_byte();
        case opcode::push_two_size:
            return source.read_2_bytes_little_endian();
        case opcode::push_four_size:
            return source.read_4_bytes_little_endian();
        default:
            const auto byte = static_cast<uint8_t>(code);
            return byte <= op_75 ? byte : 0;
    }
}

BC_POP_WARNING()

// JSON value convertors.
// ----------------------------------------------------------------------------

namespace json = boost::json;

// boost/json will soon have NOEXCEPT: github.com/boostorg/json/pull/636
BC_PUSH_WARNING(NO_THROW_IN_NOEXCEPT)

operation tag_invoke(json::value_to_tag<operation>,
    const json::value& value) NOEXCEPT
{
    return operation{ std::string(value.get_string().c_str()) };
}

void tag_invoke(json::value_from_tag, json::value& value,
    const operation& operation) NOEXCEPT
{
    value = operation.to_string(flags::all_rules);
}

BC_POP_WARNING()

operation::cptr tag_invoke(json::value_to_tag<operation::cptr>,
    const json::value& value) NOEXCEPT
{
    return to_shared(tag_invoke(json::value_to_tag<operation>{}, value));
}

// Shared pointer overload is required for navigation.
BC_PUSH_WARNING(SMART_PTR_NOT_NEEDED)
BC_PUSH_WARNING(NO_VALUE_OR_CONST_REF_SHARED_PTR)

void tag_invoke(json::value_from_tag tag, json::value& value,
    const operation::cptr& operation) NOEXCEPT
{
    tag_invoke(tag, value, *operation);
}

BC_POP_WARNING()
BC_POP_WARNING()

} // namespace chain
} // namespace system
} // namespace libbitcoin
