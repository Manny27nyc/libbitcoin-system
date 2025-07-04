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
#include "parse_encrypted_private.hpp"

#include <bitcoin/system/crypto/crypto.hpp>
#include <bitcoin/system/data/data.hpp>
#include <bitcoin/system/hash/hash.hpp>
#include <bitcoin/system/wallet/keys/encrypted_keys.hpp>
#include "parse_encrypted_key.hpp"
#include "parse_encrypted_prefix.hpp"

namespace libbitcoin {
namespace system {
namespace wallet {

const data_array<parse_encrypted_private::magic_size>
parse_encrypted_private::magic_
{
    { 0x01 }
};

data_array<parse_encrypted_private::prefix_size>
parse_encrypted_private::prefix_factory(uint8_t address,
    bool multiplied) NOEXCEPT
{
    const auto base = multiplied ? multiplied_context_ : default_context_;
    const auto context = static_cast<uint8_t>(base + address);
    return splice(magic_, to_array(context));
}

parse_encrypted_private::parse_encrypted_private(
    const encrypted_private& key) NOEXCEPT
    : parse_encrypted_key<prefix_size>(
        slice<0, 2>(key),
        slice<2, 3>(key),
        slice<3, 7>(key),
        slice<7, 15>(key)),
    data1_(slice<15, 23>(key)),
    data2_(slice<23, 39>(key))
{
    set_valid(verify_magic() && verify_checksum(key));
}

uint8_t parse_encrypted_private::address_version() const NOEXCEPT
{
    const auto base = multiplied() ? multiplied_context_ : default_context_;
    return context() - base;
}

quarter_hash parse_encrypted_private::data1() const NOEXCEPT
{
    return data1_;
}

half_hash parse_encrypted_private::data2() const NOEXCEPT
{
    return data2_;
}

bool parse_encrypted_private::multiplied() const NOEXCEPT
{
    // This is a double negative (multiplied = not not multiplied).
    return is_zero(flags() & ek_flag::ec_non_multiplied);
}

bool parse_encrypted_private::verify_magic() const NOEXCEPT
{
    return slice<zero, magic_size>(prefix()) == magic_;
}

} // namespace wallet
} // namespace system
} // namespace libbitcoin
