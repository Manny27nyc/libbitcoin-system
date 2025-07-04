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

BOOST_AUTO_TEST_SUITE(points_value_tests)

using namespace bc::system::wallet;

BOOST_AUTO_TEST_CASE(points_value__value__default__zero)
{
    static const points_value instance{};
    BOOST_REQUIRE_EQUAL(instance.value(), 0u);
}

BOOST_AUTO_TEST_CASE(points_value__value__single_point_value__expected)
{
    static const auto expected = 42u;
    static const points_value instance{ { { { null_hash, 0u }, expected } } };
    BOOST_REQUIRE_EQUAL(instance.value(), expected);
}

BOOST_AUTO_TEST_CASE(points_value__value__multiple_point_values__expected)
{
    static const auto expected = 10u + 30u + 42u;
    static const points_value instance
    {
        {
            { { null_hash, 0u }, 10u },
            { { null_hash, 1u }, 30u },
            { { null_hash, 0u }, 42u },
        }
    };
    BOOST_REQUIRE_EQUAL(instance.value(), expected);
}

BOOST_AUTO_TEST_CASE(points_value__value__multiple_point_values_remove_last__expected)
{
    static const auto expected = 10u + 30u;
    points_value instance
    {
        {
            { { null_hash, 0u }, 10u },
            { { null_hash, 1u }, 30u },
            { { null_hash, 0u }, 42u },
        }
    };
    instance.points.pop_back();
    BOOST_REQUIRE_EQUAL(instance.value(), expected);
}

BOOST_AUTO_TEST_CASE(points_value__value__multiple_point_values_clear__zero)
{
    points_value instance
    {
        {
            { { null_hash, 0u }, 10u },
            { { null_hash, 1u }, 30u },
            { { null_hash, 0u }, 42u },
        }
    };
    instance.points.clear();
    BOOST_REQUIRE_EQUAL(instance.value(), 0u);
}

BOOST_AUTO_TEST_SUITE_END()
