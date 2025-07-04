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
#include "../../test.hpp"
#include "../hash.hpp"
    
BOOST_AUTO_TEST_SUITE(sha256_tests_)

constexpr auto vector = have_128 || have_256 || have_512;
constexpr auto native = have_sha;

// Other test vectors are dependent upon the correctness of these.
static_assert(sha256::hash(sha256::byte_t{}) == sha_byte256);
static_assert(sha256::hash(sha256::half_t{}) == sha_half256);
static_assert(sha256::hash(sha256::block_t{}) == sha_full256);

BOOST_AUTO_TEST_CASE(sha256__hash__null_hash__expected)
{
    // Correlate non-const-evaluated to const-evaluated.
    BOOST_REQUIRE_EQUAL(sha256::hash(sha256::byte_t{}), sha_byte256);
    BOOST_REQUIRE_EQUAL(sha256::hash(sha256::half_t{}), sha_half256);
    BOOST_REQUIRE_EQUAL(sha256::hash(sha256::block_t{}), sha_full256);
}

// accumulator<sha256>::hash (false, false, false)
BOOST_AUTO_TEST_CASE(sha256_256__fff_accumulator_hash__test_vectors__expected)
{
    using sha_256 = sha::algorithm<sha::h256<>, false, false, false>;
    static_assert(!sha_256::native);
    static_assert(!sha_256::vector);
    static_assert(!sha_256::caching);

    // Verify non-const-evaluated against public vectors.
    for (const auto& test: sha256_256_tests)
    {
        const auto hash = accumulator<sha_256>::hash(test.data);
        BOOST_REQUIRE_EQUAL(hash, test.expected);
    }
}

// accumulator<sha256>::hash (true, false, false)
BOOST_AUTO_TEST_CASE(sha256_256__tff_accumulator_hash__test_vectors__expected)
{
    using sha_256 = sha::algorithm<sha::h256<>, true, false, false>;
    static_assert(sha_256::native == native);
    static_assert(!sha_256::vector);
    static_assert(!sha_256::caching);

    // Verify non-const-evaluated against public vectors.
    for (const auto& test: sha256_256_tests)
    {
        const auto hash = accumulator<sha_256>::hash(test.data);
        BOOST_REQUIRE_EQUAL(hash, test.expected);
    }
}

// accumulator<sha256>::hash (true, false, true)
BOOST_AUTO_TEST_CASE(sha256_256__tft_accumulator_hash__test_vectors__expected)
{
    using sha_256 = sha::algorithm<sha::h256<>, true, false, true>;
    static_assert(sha_256::native == native);
    static_assert(!sha_256::vector);
    static_assert(sha_256::caching);

    // Verify non-const-evaluated against public vectors.
    for (const auto& test: sha256_256_tests)
    {
        const auto hash = accumulator<sha_256>::hash(test.data);
        BOOST_REQUIRE_EQUAL(hash, test.expected);
    }
}

// accumulator<sha256>::hash (true, true, false)
BOOST_AUTO_TEST_CASE(sha256_256__ttf_accumulator_hash__test_vectors__expected)
{
    using sha_256 = sha::algorithm<sha::h256<>, true, true, false>;
    static_assert(sha_256::native == native);
    static_assert(sha_256::vector == vector);
    static_assert(!sha_256::caching);

    // Verify non-const-evaluated against public vectors.
    for (const auto& test: sha256_256_tests)
    {
        const auto hash = accumulator<sha_256>::hash(test.data);
        BOOST_REQUIRE_EQUAL(hash, test.expected);
    }
}

// accumulator<sha256>::hash (true, true, true)
BOOST_AUTO_TEST_CASE(sha256_256__ttt_accumulator_hash__test_vectors__expected)
{
    using sha_256 = sha::algorithm<sha::h256<>, true, true, true>;
    static_assert(sha_256::native == native);
    static_assert(sha_256::vector == vector);
    static_assert(sha_256::caching);

    // Verify non-const-evaluated against public vectors.
    for (const auto& test: sha256_256_tests)
    {
        const auto hash = accumulator<sha_256>::hash(test.data);
        BOOST_REQUIRE_EQUAL(hash, test.expected);
    }
}

// accumulator<sha256>::hash (false, true, false)
BOOST_AUTO_TEST_CASE(sha256_256__ftf_accumulator_hash__test_vectors__expected)
{
    using sha_256 = sha::algorithm<sha::h256<256>, false, true, false>;
    static_assert(!sha_256::native);
    static_assert(sha_256::vector == vector);
    static_assert(!sha_256::caching);

    // Verify non-const-evaluated against public vectors.
    for (const auto& test: sha256_256_tests)
    {
        const auto hash = accumulator<sha_256>::hash(test.data);
        BOOST_REQUIRE_EQUAL(hash, test.expected);
    }
}

// accumulator<sha_256_224>::hash (false, false, false)
BOOST_AUTO_TEST_CASE(sha256_224__fff_accumulator_hash__test_vectors__expected)
{
    using sha_256_224 = sha::algorithm<sha::h256<224>, false, false, false>;
    static_assert(!sha_256_224::native);
    static_assert(!sha_256_224::vector);
    static_assert(!sha_256_224::caching);

    // Verify non-const-evaluated against public vectors.
    for (const auto& test: sha256_224_tests)
    {
        const auto hash = accumulator<sha_256_224>::hash(test.data);
        BOOST_REQUIRE_EQUAL(hash, test.expected);
    }
}

// accumulator<sha_256_224>::hash (true, true, true)
BOOST_AUTO_TEST_CASE(sha256_224__ttt_accumulator_hash__test_vectors__expected)
{
    using sha_256_224 = sha::algorithm<sha::h256<224>, true, true, true>;

    // Native only for sha256 (and sha160 when implemented).
    static_assert(sha_256_224::native == native);
    static_assert(sha_256_224::vector == vector);
    static_assert(sha_256_224::caching);

    // Verify non-const-evaluated against public vectors.
    for (const auto& test: sha256_224_tests)
    {
        const auto hash = accumulator<sha_256_224>::hash(test.data);
        BOOST_REQUIRE_EQUAL(hash, test.expected);
    }
}

// sha256::hash
BOOST_AUTO_TEST_CASE(sha256__hash__one_block__expected)
{
    static_assert(sha256::hash(std_array<sha256::block_t, 1>({ sha256::block_t{ 0 } })) == sha_full256);
    BOOST_CHECK_EQUAL(sha256::hash(sha256::block_t{ 0 }), sha_full256);
}

BOOST_AUTO_TEST_CASE(sha256__hash__full_block__expected)
{
    static_assert(sha256::hash(sha256::block_t{ 0 }) == sha_full256);
    BOOST_CHECK_EQUAL(sha256::hash(sha256::block_t{ 0 }), sha_full256);
}

BOOST_AUTO_TEST_CASE(sha256__hash__state__equals_byteswapped_half)
{
    constexpr auto expected = sha256::hash(sha256::half_t{ 42 });
    static_assert(sha256::finalize_second(sha256::state_t{ byteswap(42_u32) }) == expected);
    BOOST_CHECK_EQUAL(sha256::finalize_second(sha256::state_t{ byteswap(42_u32) }), expected);
}

BOOST_AUTO_TEST_CASE(sha256__hash__half_block__expected)
{
    static_assert(sha256::hash(sha256::half_t{ 0 }) == sha_half256);
    BOOST_CHECK_EQUAL(sha256::hash(sha256::half_t{ 0 }), sha_half256);
}

BOOST_AUTO_TEST_CASE(sha256__hash__half_blocks__expected)
{
    constexpr auto expected = sha256::hash(sha256::half_t{ 0 }, sha256::half_t{ 0 });
    static_assert(sha256::hash(sha256::block_t{ 0 }) == expected);
    BOOST_CHECK_EQUAL(sha256::hash(sha256::half_t{ 0 }, sha256::half_t{ 0 }), expected);
}

BOOST_AUTO_TEST_CASE(sha256__hash__quart_blocks__expected)
{
    constexpr auto expected = sha256::hash(sha256::quart_t{ 0 }, sha256::quart_t{ 0 });
    static_assert(sha256::hash(sha256::half_t{ 0 }) == expected);
    BOOST_CHECK_EQUAL(sha256::hash(sha256::quart_t{ 0 }, sha256::quart_t{ 0 }), expected);
}

// sha256::midstate
BOOST_AUTO_TEST_CASE(sha256__midstate__half_blocks__expected)
{
    constexpr sha256::state_t expected
    {
        0xda5698be,
        0x17b9b469,
        0x62335799,
        0x779fbeca,
        0x8ce5d491,
        0xc0d26243,
        0xbafef9ea,
        0x1837a9d8
    };

    auto copy = expected;

    static_assert(sha256::midstate(sha256::half_t{ 0 }, sha256::half_t{ 0 }) == expected);
    BOOST_CHECK_EQUAL(sha256::midstate(sha256::half_t{ 0 }, sha256::half_t{ 0 }), expected);
    BOOST_CHECK_EQUAL(sha256::finalize(copy, one), sha256::hash(sha256::half_t{ 0 }, sha256::half_t{ 0 }));
}

// sha256::simple_hash
BOOST_AUTO_TEST_CASE(sha256__simple_hash__minimal__expected)
{
    BOOST_CHECK_EQUAL(sha256::simple_hash(data_array<zero>{}), accumulator<sha256>::hash(data_array<zero>{}));
}

BOOST_AUTO_TEST_CASE(sha256__simple_hash__byte__expected)
{
    static_assert(sha256::simple_hash(data_array<one>{ 0 }) == sha_byte256);
    BOOST_CHECK_EQUAL(sha256::simple_hash(data_array<one>{ 0 }), accumulator<sha256>::hash(data_array<one>{ 0 }));
}

BOOST_AUTO_TEST_CASE(sha256__simple_hash__maximal__expected)
{
    BOOST_CHECK_EQUAL(sha256::simple_hash(data_array<sha256::space>{ 0 }), accumulator<sha256>::hash(data_array<sha256::space>{ 0 }));
}

BOOST_AUTO_TEST_CASE(sha256__simple_hash__quart_block__expected)
{
    BOOST_CHECK_EQUAL(sha256::simple_hash(sha256::quart_t{ 0 }), accumulator<sha256>::hash(sha256::quart_t{ 0 }));
}

BOOST_AUTO_TEST_CASE(sha256__simple_hash__half_block__expected)
{
    static_assert(sha256::simple_hash(sha256::half_t{ 0 }) == sha_half256);
    BOOST_CHECK_EQUAL(sha256::simple_hash(sha256::half_t{ 0 }), accumulator<sha256>::hash(sha256::half_t{ 0 }));
}

// sha256::double_hash
BOOST_AUTO_TEST_CASE(sha256__double_hash__full_block__expected)
{
    constexpr auto expected = sha256::hash(sha256::hash(sha256::block_t{ 42 }));
    static_assert(sha256::double_hash(sha256::block_t{ 42 }) == expected);
    BOOST_CHECK_EQUAL(sha256::double_hash(sha256::block_t{ 42 }), expected);
}

BOOST_AUTO_TEST_CASE(sha256__double_hash__half_block__expected)
{
    constexpr auto expected = sha256::hash(sha256::hash(sha256::half_t{ 42 }));
    static_assert(sha256::double_hash(sha256::half_t{ 42 }) == expected);
    BOOST_CHECK_EQUAL(sha256::double_hash(sha256::half_t{ 42 }), expected);
}

BOOST_AUTO_TEST_CASE(sha256__double_hash__half_blocks__expected)
{
    constexpr auto expected = sha256::hash(sha256::hash(block<sha256>(0, 1)));
    static_assert(sha256::double_hash({ 0 }, { 1 }) == expected);
    BOOST_CHECK_EQUAL(sha256::double_hash({ 0 }, { 1 }), expected);
}

// sha256::merkle_hash
BOOST_AUTO_TEST_CASE(sha256__merkle_hash__two__expected)
{
    constexpr auto expected = sha256::double_hash({ 0 }, { 1 });
    static_assert(merkle_hash<sha256, 0, 1>(expected));
    sha256::digests_t digests{ { 0 }, { 1 } };
    sha256::merkle_hash(digests);
    BOOST_CHECK_EQUAL(digests.size(), one);
    BOOST_CHECK_EQUAL(digests.front(), expected);
}

BOOST_AUTO_TEST_CASE(sha256__merkle_hash__four__expected)
{
    constexpr auto expected1 = sha256::double_hash({ 0 }, { 1 });
    constexpr auto expected2 = sha256::double_hash({ 2 }, { 3 });
    static_assert(merkle_hash<sha256, 0, 1, 2, 3>(expected1, expected2));
    sha256::digests_t digests{ { 0 }, { 1 }, { 2 }, { 3 } };
    sha256::merkle_hash(digests);
    BOOST_CHECK_EQUAL(digests.size(), two);
    BOOST_CHECK_EQUAL(digests.front(), expected1);
    BOOST_CHECK_EQUAL(digests.back(), expected2);
}

// sha256::merkle_root
BOOST_AUTO_TEST_CASE(sha256__merkle_root__empty__null_hash)
{
    constexpr auto expected = null_hash;
    static_assert(sha256::merkle_root({}) == expected);
    BOOST_CHECK_EQUAL(sha256::merkle_root({}), expected);
}

BOOST_AUTO_TEST_CASE(sha256__merkle_root__one__same)
{
    constexpr auto expected = sha256::digest_t{ 42 };
    static_assert(sha256::merkle_root({ { 42 } }) == expected);
    BOOST_CHECK_EQUAL(sha256::merkle_root({ { 42 } }), expected);
}

BOOST_AUTO_TEST_CASE(sha256__merkle_root__two__expected)
{
    constexpr auto expected = sha256::double_hash({ 0 }, { 1 });
    // vc++ debug compiler failure.
    ////static_assert(sha256::merkle_root({ { 0 }, { 1 } }) == expected);
    BOOST_CHECK_EQUAL(sha256::merkle_root({ { 0 }, { 1 } }), expected);
}

BOOST_AUTO_TEST_CASE(sha256__merkle_root__three__expected)
{
    constexpr auto expected1 = sha256::double_hash({ 0 }, { 1 });
    constexpr auto expected2 = sha256::double_hash({ 2 }, { 2 });
    constexpr auto expected = sha256::double_hash(expected1, expected2);
    static_assert(sha256::merkle_root({ { 0 }, { 1 }, { 2 } }) == expected);
    BOOST_CHECK_EQUAL(sha256::merkle_root({ { 0 }, { 1 }, { 2 } }), expected);
}

BOOST_AUTO_TEST_CASE(sha256__merkle_root__four__expected)
{
    constexpr auto expected1 = sha256::double_hash({ 0 }, { 1 });
    constexpr auto expected2 = sha256::double_hash({ 2 }, { 3 });
    constexpr auto expected = sha256::double_hash(expected1, expected2);
    static_assert(sha256::merkle_root({ { 0 }, { 1 }, { 2 }, { 3 } }) == expected);
    BOOST_CHECK_EQUAL(sha256::merkle_root({ { 0 }, { 1 }, { 2 }, { 3 } }), expected);
}

BOOST_AUTO_TEST_SUITE_END()
