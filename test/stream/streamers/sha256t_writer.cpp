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
#include <sstream>

BOOST_AUTO_TEST_SUITE(sha256t_writer_tests)

static const auto& genesis() NOEXCEPT
{
    static auto block = settings(chain::selection::mainnet).genesis_block;
    return block;
}

BOOST_AUTO_TEST_CASE(sha256t_writer__stream__genesis_block__expected)
{
    std::ostringstream stream{};
    hash::sha256t::ostream<"mytag"> hasher{ stream };
    genesis().header().to_data(hasher);
    hasher.flush();
    BOOST_REQUIRE(hasher);
    BOOST_REQUIRE_EQUAL(to_chunk(stream.str()), to_chunk(tagged_hash("mytag", genesis().header().to_data())));
}

BOOST_AUTO_TEST_CASE(sha256t_writer__fast__genesis_block__expected)
{
    hash_digest hash{};
    stream::out::fast stream{ hash };
    hash::sha256t::fast<"mytag"> hasher{ stream };
    genesis().header().to_data(hasher);
    hasher.flush();
    BOOST_REQUIRE(hasher);
    BOOST_REQUIRE_EQUAL(hash, tagged_hash("mytag", genesis().header().to_data()));
}

////BOOST_AUTO_TEST_CASE(sha256t_writer__copy__genesis_block__expected)
////{
////    hash_digest hash{};
////    hash::sha256t::copy<"mytag"> hasher{ hash };
////    genesis().header().to_data(hasher);
////    hasher.flush();
////    BOOST_REQUIRE(hasher);
////    BOOST_REQUIRE_EQUAL(hash, tagged_hash("mytag", genesis().header().to_data()));
////}
////
////BOOST_AUTO_TEST_CASE(sha256t_writer__text__genesis_block__expected)
////{
////    std::string hash;
////    hash::sha256t::text<"mytag"> hasher(hash);
////    genesis().header().to_data(hasher);
////    hasher.flush();
////    BOOST_REQUIRE(hasher);
////    BOOST_REQUIRE_EQUAL(hash, to_string(genesis().header().hash()));
////}
////
////BOOST_AUTO_TEST_CASE(sha256t_writer__data__genesis_block__expected)
////{
////    data_chunk hash;
////    hash::sha256t::data<"mytag"> hasher(hash);
////    genesis().header().to_data(hasher);
////    hasher.flush();
////    BOOST_REQUIRE(hasher);
////    BOOST_REQUIRE_EQUAL(hash, to_chunk(genesis().header().hash()));
////}

BOOST_AUTO_TEST_SUITE_END()
