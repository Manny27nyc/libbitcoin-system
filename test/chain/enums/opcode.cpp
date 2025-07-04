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

BOOST_AUTO_TEST_SUITE(opcode_tests)

using namespace system::chain;

// opcode_to_mnemonic
// ----------------------------------------------------------------------------
// Partial coverage includes those with aliases and samples of each "range" of codes.

// Use the traditional serializations for all codes (in this case 'zero' vs. 'push_0').
BOOST_AUTO_TEST_CASE(opcode__opcode_to_mnemonic__zero_any_forks__zero)
{
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::push_size_0, flags::no_rules), "zero");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::push_size_0, flags::all_rules), "zero");
}

// We formerly serialized all 1-75 as 'special'.
BOOST_AUTO_TEST_CASE(opcode__opcode_to_mnemonic__push_size_42_any_forks__push_42)
{
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::push_size_42, flags::no_rules), "push_42");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::push_size_42, flags::all_rules), "push_42");
}

// Use the traditional serializations for all codes (in this case 'pushdata1' vs. 'push_one').
BOOST_AUTO_TEST_CASE(opcode__opcode_to_mnemonic__push_one_size_any_forks__pushdata1)
{
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::push_one_size, flags::no_rules), "pushdata1");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::push_one_size, flags::all_rules), "pushdata1");
}

// Use the traditional serializations for all codes (in this case 'pushdata2' vs. 'push_two').
BOOST_AUTO_TEST_CASE(opcode__opcode_to_mnemonic__push_two_size_size_any_forks__pushdata2)
{
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::push_two_size, flags::no_rules), "pushdata2");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::push_two_size, flags::all_rules), "pushdata2");
}

// Use the traditional serializations for all codes (in this case 'pushdata4' vs. 'push_four').
BOOST_AUTO_TEST_CASE(opcode__opcode_to_mnemonic__push_four_size_any_forks__pushdata4)
{
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::push_four_size, flags::no_rules), "pushdata4");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::push_four_size, flags::all_rules), "pushdata4");
}

// Use the traditional serializations for all codes (in this case 'reserved' vs. 0x50).
BOOST_AUTO_TEST_CASE(opcode__opcode_to_mnemonic__reserved_80_any_forks__reserved)
{
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::reserved_80, flags::no_rules), "reserved");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::reserved_80, flags::all_rules), "reserved");
}

BOOST_AUTO_TEST_CASE(opcode__opcode_to_mnemonic__push_positive_7_any_forks__7)
{
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::push_positive_7, flags::no_rules), "7");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::push_positive_7, flags::all_rules), "7");
}

// Use the traditional serializations for all codes (in this case 'ver' vs. '0x62').
BOOST_AUTO_TEST_CASE(opcode__opcode_to_mnemonic__op_ver_any_forks__ver)
{
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::op_ver, flags::no_rules), "ver");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::op_ver, flags::all_rules), "ver");
}

// Use the traditional serializations for all codes (in this case 'verif' vs. '0x65').
BOOST_AUTO_TEST_CASE(opcode__opcode_to_mnemonic__op_verif_any_forks__verif)
{
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::op_verif, flags::no_rules), "verif");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::op_verif, flags::all_rules), "verif");
}

// Use the traditional serializations for all codes (in this case 'vernotif' vs. '0x66').
BOOST_AUTO_TEST_CASE(opcode__opcode_to_mnemonic__op_vernotif_any_forks__vernotif)
{
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::op_vernotif, flags::no_rules), "vernotif");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::op_vernotif, flags::all_rules), "vernotif");
}

// Use the traditional serializations for all codes (in this case '2drop' vs. 'drop2').
BOOST_AUTO_TEST_CASE(opcode__opcode_to_mnemonic__drop2_any_forks__2drop)
{
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::drop2, flags::no_rules), "2drop");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::drop2, flags::all_rules), "2drop");
}

// Use the traditional serializations for all codes (in this case '2dup' vs. 'dup2').
BOOST_AUTO_TEST_CASE(opcode__opcode_to_mnemonic__rdup2_any_forks__2dup)
{
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::dup2, flags::no_rules), "2dup");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::dup2, flags::all_rules), "2dup");
}

// Use the traditional serializations for all codes (in this case '3dup' vs. 'dup3').
BOOST_AUTO_TEST_CASE(opcode__opcode_to_mnemonic__dup3_any_forks__3dup)
{
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::dup3, flags::no_rules), "3dup");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::dup3, flags::all_rules), "3dup");
}

// Use the traditional serializations for all codes (in this case '2over' vs. 'over2').
BOOST_AUTO_TEST_CASE(opcode__opcode_to_mnemonic__over2_any_forks__vernotif)
{
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::over2, flags::no_rules), "2over");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::over2, flags::all_rules), "2over");
}

// Use the traditional serializations for all codes (in this case '2rot' vs. 'rot2').
BOOST_AUTO_TEST_CASE(opcode__opcode_to_mnemonic__rot2_any_forks__2rot)
{
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::rot2, flags::no_rules), "2rot");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::rot2, flags::all_rules), "2rot");
}

// Use the traditional serializations for all codes (in this case '2swap' vs. 'swap2').
BOOST_AUTO_TEST_CASE(opcode__opcode_to_mnemonic__swap2_any_forks__2swap)
{
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::swap2, flags::no_rules), "2swap");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::swap2, flags::all_rules), "2swap");
}

// Use the traditional serializations for all codes (in this case '1add' vs. 'add1').
BOOST_AUTO_TEST_CASE(opcode__opcode_to_mnemonic__add1_any_forks__2rot)
{
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::add1, flags::no_rules), "1add");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::add1, flags::all_rules), "1add");
}

// Use the traditional serializations for all codes (in this case '1sub' vs. 'sub1').
BOOST_AUTO_TEST_CASE(opcode__opcode_to_mnemonic__sub1_any_forks__2swap)
{
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::sub1, flags::no_rules), "1sub");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::sub1, flags::all_rules), "1sub");
}

// All nop1 to nop10.
BOOST_AUTO_TEST_CASE(opcode__opcode_to_mnemonic__nops_any_forks__nop)
{
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::nop1, flags::no_rules), "nop1");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::nop1, flags::all_rules), "nop1");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::nop2, flags::no_rules), "nop2");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::nop2, flags::all_rules), "checklocktimeverify");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::nop3, flags::no_rules), "nop3");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::nop3, flags::all_rules), "checksequenceverify");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::nop4, flags::no_rules), "nop4");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::nop4, flags::all_rules), "nop4");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::nop5, flags::no_rules), "nop5");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::nop5, flags::all_rules), "nop5");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::nop6, flags::no_rules), "nop6");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::nop6, flags::all_rules), "nop6");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::nop7, flags::no_rules), "nop7");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::nop7, flags::all_rules), "nop7");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::nop8, flags::no_rules), "nop8");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::nop8, flags::all_rules), "nop8");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::nop9, flags::no_rules), "nop9");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::nop9, flags::all_rules), "nop9");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::nop10, flags::no_rules), "nop10");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::nop10, flags::all_rules), "nop10");
}

// All reserved_186 to reserved_255.
BOOST_AUTO_TEST_CASE(opcode__opcode_to_mnemonic__reserved_186_to_255_any_forks__hex)
{
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::reserved_186, flags::no_rules), "0xba");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::reserved_186, flags::all_rules), "checksigadd");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::reserved_187, flags::no_rules), "0xbb");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::reserved_187, flags::all_rules), "0xbb");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::reserved_255, flags::no_rules), "0xff");
    BOOST_REQUIRE_EQUAL(opcode_to_mnemonic(opcode::reserved_255, flags::all_rules), "0xff");
}

// opcode_from_mnemonic
// ----------------------------------------------------------------------------
// Partial coverage includes all aliases and boundaries of each "range" of codes.

// zero

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__zero__push_size_0)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "zero"));
    BOOST_REQUIRE(out_code == opcode::push_size_0);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__push_0__push_size_0)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "push_0"));
    BOOST_REQUIRE(out_code == opcode::push_size_0);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__0__push_size_0)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "0"));
    BOOST_REQUIRE(out_code == opcode::push_size_0);
}

// push n (special)

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__push_1__push_size_1)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "push_1"));
    BOOST_REQUIRE(out_code == opcode::push_size_1);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__push_75__push_size_75)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "push_75"));
    BOOST_REQUIRE(out_code == opcode::push_size_75);
}

// push n byte size (pushdata)

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__push_one__push_one_size)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "push_one"));
    BOOST_REQUIRE(out_code == opcode::push_one_size);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__push_two__push_two_size)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "push_two"));
    BOOST_REQUIRE(out_code == opcode::push_two_size);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__push_four__push_four_size)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "push_four"));
    BOOST_REQUIRE(out_code == opcode::push_four_size);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__pushdata1__push_one_size)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "pushdata1"));
    BOOST_REQUIRE(out_code == opcode::push_one_size);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__pushdata2_push_two_size)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "pushdata2"));
    BOOST_REQUIRE(out_code == opcode::push_two_size);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__pushdata4__push_four_size)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "pushdata4"));
    BOOST_REQUIRE(out_code == opcode::push_four_size);
}

// negative one

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__minus1__push_negative_1)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "-1"));
    BOOST_REQUIRE(out_code == opcode::push_negative_1);
}

// reserved

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__reserved__reserved_80)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "reserved"));
    BOOST_REQUIRE(out_code == opcode::reserved_80);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__reserved_80__reserved_80)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "reserved_80"));
    BOOST_REQUIRE(out_code == opcode::reserved_80);
}

// positive numbers

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__1__push_positive_1)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "1"));
    BOOST_REQUIRE(out_code == opcode::push_positive_1);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__16__push_positive_16)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "16"));
    BOOST_REQUIRE(out_code == opcode::push_positive_16);
}

// ver/verif/vernotif

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__ver__op_ver)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "ver"));
    BOOST_REQUIRE(out_code == opcode::op_ver);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__verif__op_verif)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "verif"));
    BOOST_REQUIRE(out_code == opcode::op_verif);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__vernotif__op_vernotif)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "vernotif"));
    BOOST_REQUIRE(out_code == opcode::op_vernotif);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__op_ver__op_ver)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "op_ver"));
    BOOST_REQUIRE(out_code == opcode::op_ver);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__op_verif__op_verif)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "op_verif"));
    BOOST_REQUIRE(out_code == opcode::op_verif);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__op_vernotif__op_vernotif)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "op_vernotif"));
    BOOST_REQUIRE(out_code == opcode::op_vernotif);
}

// math

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__drop2__drop2)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "drop2"));
    BOOST_REQUIRE(out_code == opcode::drop2);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__dup2__dup2)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "dup2"));
    BOOST_REQUIRE(out_code == opcode::dup2);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__dup3__dup3)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "dup3"));
    BOOST_REQUIRE(out_code == opcode::dup3);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__over2__over2)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "over2"));
    BOOST_REQUIRE(out_code == opcode::over2);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__rot2__rot2)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "rot2"));
    BOOST_REQUIRE(out_code == opcode::rot2);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__swap2__swap2)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "swap2"));
    BOOST_REQUIRE(out_code == opcode::swap2);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__add1__add1)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "add1"));
    BOOST_REQUIRE(out_code == opcode::add1);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__sub1__sub1)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "sub1"));
    BOOST_REQUIRE(out_code == opcode::sub1);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__mul2__mul2)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "mul2"));
    BOOST_REQUIRE(out_code == opcode::op_mul2);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__div2__div2)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "div2"));
    BOOST_REQUIRE(out_code == opcode::op_div2);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__2drop__drop2)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "2drop"));
    BOOST_REQUIRE(out_code == opcode::drop2);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__2dup__dup2)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "2dup"));
    BOOST_REQUIRE(out_code == opcode::dup2);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__3dup__dup3)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "3dup"));
    BOOST_REQUIRE(out_code == opcode::dup3);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__2over__over2)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "2over"));
    BOOST_REQUIRE(out_code == opcode::over2);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__2rot__rot2)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "2rot"));
    BOOST_REQUIRE(out_code == opcode::rot2);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__2swap__swap2)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "2swap"));
    BOOST_REQUIRE(out_code == opcode::swap2);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__1add__add1)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "1add"));
    BOOST_REQUIRE(out_code == opcode::add1);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__1sub__sub1)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "1sub"));
    BOOST_REQUIRE(out_code == opcode::sub1);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__2mul__mul2)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "2mul"));
    BOOST_REQUIRE(out_code == opcode::op_mul2);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__2div__div2)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "2div"));
    BOOST_REQUIRE(out_code == opcode::op_div2);
}

// reserved1/reserved2

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__reserved1__reserved_137)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "reserved1"));
    BOOST_REQUIRE(out_code == opcode::reserved_137);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__reserved2__reserved_138)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "reserved2"));
    BOOST_REQUIRE(out_code == opcode::reserved_138);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__op_vernotif__reserved_137)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "reserved_137"));
    BOOST_REQUIRE(out_code == opcode::reserved_137);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__op_vernotif__reserved_138)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "reserved_138"));
    BOOST_REQUIRE(out_code == opcode::reserved_138);
}

// nop2/checklocktimeverify
static_assert(opcode::checklocktimeverify == opcode::nop2, "checklocktimeverify drift");

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__nop2__nop2)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "nop2"));
    BOOST_REQUIRE(out_code == opcode::nop2);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__checklocktimeverify__nop2_or_checklocktimeverify)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "checklocktimeverify"));
    BOOST_REQUIRE(out_code == opcode::nop2);
}

// nop3/checksequenceverify
static_assert(opcode::checksequenceverify == opcode::nop3, "checksequenceverify drift");

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__nop3__nop3)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "nop3"));
    BOOST_REQUIRE(out_code == opcode::nop3);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__checksequenceverify__nop3_or_checksequenceverify)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "checksequenceverify"));
    BOOST_REQUIRE(out_code == opcode::nop3);
}

// reserved_186/checksigadd
static_assert(opcode::checksigadd == opcode::reserved_186, "checksigadd drift");

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__reserved_186__reserved_186)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "reserved_186"));
    BOOST_REQUIRE(out_code == opcode::reserved_186);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_mnemonic__checksigadd__reserved_186_or_checksigadd)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_mnemonic(out_code, "checksigadd"));
    BOOST_REQUIRE(out_code == opcode::reserved_186);
}

// opcode_to_hexadecimal
// ----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(opcode__opcode_to_hexadecimal__zero__0x00)
{
    BOOST_REQUIRE_EQUAL(opcode_to_hexadecimal(opcode::push_size_0), "0x00");
}

BOOST_AUTO_TEST_CASE(opcode__opcode_to_hexadecimal__push_size_42__0x2a)
{
    BOOST_REQUIRE_EQUAL(opcode_to_hexadecimal(opcode::push_size_42), "0x2a");
}

BOOST_AUTO_TEST_CASE(opcode__opcode_to_hexadecimal__reserved_255__0xff)
{
    BOOST_REQUIRE_EQUAL(opcode_to_hexadecimal(opcode::reserved_255), "0xff");
}

// opcode_from_hexadecimal
// ----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(opcode__opcode_from_hexadecimal__empty__false)
{
    opcode out_code;
    BOOST_REQUIRE(!opcode_from_hexadecimal(out_code, ""));
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_hexadecimal__bogus__false)
{
    opcode out_code;
    BOOST_REQUIRE(!opcode_from_hexadecimal(out_code, "bogus"));
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_hexadecimal__9_bits__false)
{
    opcode out_code;
    BOOST_REQUIRE(!opcode_from_hexadecimal(out_code, "0x"));
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_hexadecimal__8_bits__false)
{
    opcode out_code;
    BOOST_REQUIRE(!opcode_from_hexadecimal(out_code, "0xf"));
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_hexadecimal__16_bits__expected)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_hexadecimal(out_code, "0xff"));
    BOOST_REQUIRE(out_code == opcode::reserved_255);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_hexadecimal__24_bits__false)
{
    opcode out_code;
    BOOST_REQUIRE(!opcode_from_hexadecimal(out_code, "0xffe"));
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_hexadecimal__48_bits__false)
{
    opcode out_code;
    BOOST_REQUIRE(!opcode_from_hexadecimal(out_code, "0xffee"));
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_hexadecimal__upper_case__expected)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_hexadecimal(out_code, "0xFE"));
    BOOST_REQUIRE(out_code == opcode::reserved_254);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_hexadecimal__mixed_case__expected)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_hexadecimal(out_code, "0xFe"));
    BOOST_REQUIRE(out_code == opcode::reserved_254);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_hexadecimal__numeric__expected)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_hexadecimal(out_code, "0x42"));
    BOOST_REQUIRE(out_code == opcode::push_size_66);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_hexadecimal__alphanumeric__expected)
{
    opcode out_code;
    BOOST_REQUIRE(opcode_from_hexadecimal(out_code, "0x4f"));
    BOOST_REQUIRE(out_code == opcode::push_negative_1);
}

BOOST_AUTO_TEST_CASE(opcode__opcode_from_hexadecimal__upper_case_prefix__false)
{
    opcode out_code;
    BOOST_REQUIRE(!opcode_from_hexadecimal(out_code, "0X4f"));
}

BOOST_AUTO_TEST_SUITE_END()
