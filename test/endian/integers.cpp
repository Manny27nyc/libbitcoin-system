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

BOOST_AUTO_TEST_SUITE(endian_integers_tests)

// These are fully covered as dependencies for other endian functions.
// Data to_big_data(Data&&, Integer)
// Data to_little_data(Data&&, Integer)
// Integer from_big_array<Integer>(data_array)
// Integer from_big_array<Integer>(length, data_array)
// Integer from_big_chunk<Integer>(length, data_chunk)
// Integer from_little_array<Integer>(data_array)
// Integer from_little_array<Integer>(length, data_array)
// Integer from_little_chunk<Integer>(length, data_chunk)

BOOST_AUTO_TEST_SUITE_END()
