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
#include "../test.hpp"

BOOST_AUTO_TEST_SUITE(point_value_tests)

using namespace bc::system::wallet;

static const auto hash1 = base16_hash(
    "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f");

BOOST_AUTO_TEST_CASE(point_value__default_constructor__always__zero_value)
{
    static const point_value instance;
    BOOST_REQUIRE(instance.hash() == null_hash);
    BOOST_REQUIRE_EQUAL(instance.index(), chain::point::null_index);
    BOOST_REQUIRE_EQUAL(instance.value(), 0u);
}

BOOST_AUTO_TEST_CASE(point_value__move_constructor__always__expected)
{
    point_value other{ { hash1, 42 }, 34 };
    const point_value instance(std::move(other));
    BOOST_REQUIRE_EQUAL(instance.hash(),  hash1);
    BOOST_REQUIRE_EQUAL(instance.index(), 42u);
    BOOST_REQUIRE_EQUAL(instance.value(), 34u);
}

BOOST_AUTO_TEST_CASE(point_value__copy_constructor__always__expected)
{
    static const point_value other{ { hash1, 42 }, 34 };
    const point_value instance(other);
    BOOST_REQUIRE_EQUAL(instance.hash(), hash1);
    BOOST_REQUIRE_EQUAL(instance.index(), 42u);
    BOOST_REQUIRE_EQUAL(instance.value(), 34u);
}

BOOST_AUTO_TEST_CASE(point_value__constructor4__always__expected)
{
    chain::point foo{ hash1, 42 };
    static const point_value instance(std::move(foo), 34);
    BOOST_REQUIRE_EQUAL(instance.hash(), hash1);
    BOOST_REQUIRE_EQUAL(instance.index(), 42u);
    BOOST_REQUIRE_EQUAL(instance.value(), 34u);
}

BOOST_AUTO_TEST_CASE(point_value__constructor5__always__expected)
{
    static const chain::point foo{ hash1, 42 };
    static const point_value instance(foo, 34);
    BOOST_REQUIRE_EQUAL(instance.hash(), hash1);
    BOOST_REQUIRE_EQUAL(instance.index(), 42u);
    BOOST_REQUIRE_EQUAL(instance.value(), 34u);
}

BOOST_AUTO_TEST_CASE(point_value__move_assign__always__expected)
{
    point_value other{ { hash1, 42 }, 34 };
    const auto instance = std::move(other);
    BOOST_REQUIRE_EQUAL(instance.hash(), hash1);
    BOOST_REQUIRE_EQUAL(instance.index(), 42u);
    BOOST_REQUIRE_EQUAL(instance.value(), 34u);
}

BOOST_AUTO_TEST_CASE(point_value__copy_assign__always__expected)
{
    static const point_value other{ { hash1, 42 }, 34 };
    const auto instance = other;
    BOOST_REQUIRE_EQUAL(instance.hash(), hash1);
    BOOST_REQUIRE_EQUAL(instance.index(), 42u);
    BOOST_REQUIRE_EQUAL(instance.value(), 34u);
}

BOOST_AUTO_TEST_CASE(point_value__equality__same__true)
{
    static const point_value instance1{ { hash1, 42 }, 34 };
    static const point_value instance2{ { hash1, 42 }, 34 };
    BOOST_REQUIRE(instance1 == instance2);
}

BOOST_AUTO_TEST_CASE(point_value__equality__different_by_hash__false)
{
    static const point_value instance1{ { hash1, 42 }, 34 };
    static const point_value instance2{ { null_hash, 43 }, 34 };
    BOOST_REQUIRE(!(instance1 == instance2));
}

BOOST_AUTO_TEST_CASE(point_value__equality__different_by_index__false)
{
    static const point_value instance1{ { hash1, 42 }, 34 };
    static const point_value instance2{ { hash1, 43 }, 34 };
    BOOST_REQUIRE(!(instance1 == instance2));
}

BOOST_AUTO_TEST_CASE(point_value__equality__different_by_value__false)
{
    static const point_value instance1{ { hash1, 42 }, 34 };
    static const point_value instance2{ { hash1, 42 }, 35 };
    BOOST_REQUIRE(!(instance1 == instance2));
}

BOOST_AUTO_TEST_CASE(point_value__inequality__same__false)
{
    static const point_value instance1{ { hash1, 42 }, 34 };
    static const point_value instance2{ { hash1, 42 }, 34 };
    BOOST_REQUIRE(!(instance1 != instance2));
}

BOOST_AUTO_TEST_CASE(point_value__inequality__different_by_hash__true)
{
    static const point_value instance1{ { hash1, 42 }, 34 };
    static const point_value instance2{ { null_hash, 43 }, 34 };
    BOOST_REQUIRE(instance1 != instance2);
}

BOOST_AUTO_TEST_CASE(point_value__inequality__different_by_index__true)
{
    static const point_value instance1{ { hash1, 42 }, 34 };
    static const point_value instance2{ { hash1, 43 }, 34 };
    BOOST_REQUIRE(instance1 != instance2);
}

BOOST_AUTO_TEST_CASE(point_value__inequality__different_by_value__true)
{
    static const point_value instance1{ { hash1, 42 }, 34 };
    static const point_value instance2{ { hash1, 42 }, 35 };
    BOOST_REQUIRE(instance1 != instance2);
}

BOOST_AUTO_TEST_CASE(point_value__set_value__42__42)
{
    static const auto expected = 42u;
    point_value instance;
    instance.set_value(expected);
    BOOST_REQUIRE_EQUAL(instance.value(), expected);
}

BOOST_AUTO_TEST_CASE(point_value__set_value__zeroize__zero)
{
    point_value instance;
    instance.set_value(42);
    instance.set_value(0);
    BOOST_REQUIRE_EQUAL(instance.value(), 0u);
}

BOOST_AUTO_TEST_SUITE_END()
