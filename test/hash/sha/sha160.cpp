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
    
BOOST_AUTO_TEST_SUITE(sha160_tests_)

// Other test vectors are dependent upon the correctness of these.
static_assert(sha160::hash(sha160::byte_t{}) == sha_byte160);
static_assert(sha160::hash(sha160::half_t{})  == sha_half160);
static_assert(sha160::hash(sha160::block_t{}) == sha_full160);

constexpr auto vector = have_128 || have_256 || have_512;
constexpr auto native = /*have_sha*/ false;

BOOST_AUTO_TEST_CASE(sha160__hash__null_hash__expected)
{
    // Correlate non-const-evaluated to const-evaluated.
    BOOST_REQUIRE_EQUAL(sha160::hash(sha160::byte_t{}), sha_byte160);
    BOOST_REQUIRE_EQUAL(sha160::hash(sha160::half_t{}), sha_half160);
    BOOST_REQUIRE_EQUAL(sha160::hash(sha160::block_t{}), sha_full160);
}

// accumulator<sha160>::hash (false, false, false)
BOOST_AUTO_TEST_CASE(sha160__fff_accumulator_hash__test_vectors__expected)
{
    using sha_160 = sha::algorithm<sha::h160, false, false, false>;
    static_assert(!sha_160::native);
    static_assert(!sha_160::vector);
    static_assert(!sha_160::caching);

    // Verify non-const-evaluated against public vectors.
    for (const auto& test: sha160_tests)
    {
        const auto hash = accumulator<sha_160>::hash(test.data);
        BOOST_REQUIRE_EQUAL(hash, test.expected);
    }
}

// accumulator<sha160>::hash (true, false, false)
BOOST_AUTO_TEST_CASE(sha160__tff_accumulator_hash__test_vectors__expected)
{
    using sha_160 = sha::algorithm<sha::h160, true, false, false>;
    static_assert(sha_160::native == native);
    static_assert(!sha_160::vector);
    static_assert(!sha_160::caching);

    // Verify non-const-evaluated against public vectors.
    for (const auto& test: sha160_tests)
    {
        const auto hash = accumulator<sha_160>::hash(test.data);
        BOOST_REQUIRE_EQUAL(hash, test.expected);
    }
}

// accumulator<sha160>::hash (true, false, true)
BOOST_AUTO_TEST_CASE(sha160__tft_accumulator_hash__test_vectors__expected)
{
    using sha_160 = sha::algorithm<sha::h160, true, false, true>;
    static_assert(sha_160::native == native);
    static_assert(!sha_160::vector);
    static_assert(sha_160::caching);

    // Verify non-const-evaluated against public vectors.
    for (const auto& test: sha160_tests)
    {
        const auto hash = accumulator<sha_160>::hash(test.data);
        BOOST_REQUIRE_EQUAL(hash, test.expected);
    }
}

// accumulator<sha160>::hash (true, true, false)
BOOST_AUTO_TEST_CASE(sha160__ttf_accumulator_hash__test_vectors__expected)
{
    using sha_160 = sha::algorithm<sha::h160, true, true, false>;
    static_assert(sha_160::native == native);
    static_assert(sha_160::vector == vector);
    static_assert(!sha_160::caching);

    // Verify non-const-evaluated against public vectors.
    for (const auto& test: sha160_tests)
    {
        const auto hash = accumulator<sha_160>::hash(test.data);
        BOOST_REQUIRE_EQUAL(hash, test.expected);
    }
}

// accumulator<sha160>::hash (true, true, true)
BOOST_AUTO_TEST_CASE(sha160__ttt_accumulator_hash__test_vectors__expected)
{
    using sha_160 = sha::algorithm<sha::h160, true, true, true>;
    static_assert(sha_160::native == native);
    static_assert(sha_160::vector == vector);
    static_assert(sha_160::caching);

    // Verify non-const-evaluated against public vectors.
    for (const auto& test: sha160_tests)
    {
        const auto hash = accumulator<sha_160>::hash(test.data);
        BOOST_REQUIRE_EQUAL(hash, test.expected);
    }
}

// accumulator<sha160>::hash (false, true, false)
BOOST_AUTO_TEST_CASE(sha160__ftf_accumulator_hash__test_vectors__expected)
{
    using sha_160 = sha::algorithm<sha::h160, false, true, false>;
    static_assert(!sha_160::native);
    static_assert(sha_160::vector == vector);
    static_assert(!sha_160::caching);

    // Verify non-const-evaluated against public vectors.
    for (const auto& test: sha160_tests)
    {
        const auto hash = accumulator<sha_160>::hash(test.data);
        BOOST_REQUIRE_EQUAL(hash, test.expected);
    }
}

BOOST_AUTO_TEST_SUITE_END()
