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

// Sponsored in part by Digital Contract Design, LLC

#include "../test.hpp"
#include "siphash.hpp"

// This is a lot of tests, not suprisingly very fast execution.

BOOST_AUTO_TEST_SUITE(siphash_tests)

BOOST_AUTO_TEST_CASE(siphash__hash__test_key__expected)
{
    half_hash hash{};
    BOOST_REQUIRE(decode_base16(hash, hash_test_key));

    constexpr auto expected = 0xa129ca6149be45e5;
    constexpr auto message = base16_array("000102030405060708090a0b0c0d0e");
    BOOST_REQUIRE_EQUAL(siphash(hash, message), expected);
}

BOOST_AUTO_TEST_CASE(siphash__hash__vectors__expected)
{
    half_hash hash{};
    BOOST_REQUIRE(decode_base16(hash, hash_test_key));

    for (const auto& result: siphash_hash_tests)
    {
        data_chunk data;
        BOOST_REQUIRE(decode_base16(data, result.message));

        data_chunk encoded_expected;
        BOOST_REQUIRE(decode_base16(encoded_expected, result.result));

        const auto expected = from_little_endian<uint64_t>(encoded_expected);
        BOOST_REQUIRE_EQUAL(siphash(hash, data), expected);
    }
}

BOOST_AUTO_TEST_CASE(siphash__key__vectors__expected)
{
    half_hash hash{};
    BOOST_REQUIRE(decode_base16(hash, hash_test_key));

    const auto key = to_siphash_key(hash);

    for (const auto& result: siphash_hash_tests)
    {
        data_chunk data;
        BOOST_REQUIRE(decode_base16(data, result.message));

        data_chunk encoded_expected;
        BOOST_REQUIRE(decode_base16(encoded_expected, result.result));

        const auto expected = from_little_endian<uint64_t>(encoded_expected);
        BOOST_REQUIRE_EQUAL(siphash(key, data), expected);
    }
}

BOOST_AUTO_TEST_SUITE_END()
