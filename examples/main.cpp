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
#include <cstdlib>
#include <string>
#include <bitcoin/system.hpp>

BC_USE_LIBBITCOIN_MAIN

// Testing out our http://utf8everywhere.org implementation.
int bc::system::main(int argc, char* argv[])
{
    using namespace bc;
    using namespace bc::system;

    // Windows utf8 everywhere demonstration.
    set_utf8_stdio();

    system::cout << "output : acción.кошка.日本国" << std::endl;
    system::cerr << "error : acción.кошка.日本国" << std::endl;

    system::cout << "Enter text to input..." << std::endl;
    std::string console;
    system::cin >> console;
    system::cout << "input[0] : " << console << std::endl;

    if (argc > 1)
        system::cout << "argv[1] : " << argv[1] << std::endl;

#ifdef _MSC_VER
    if (environ[0] != nullptr)
        system::cout << "environ[0] : " << environ[0] << std::endl;
#endif

    // Extracting Satoshi's words from genesis block.
    const auto block = settings(chain::selection::mainnet).genesis_block;
    const auto message = to_string((*(*block.transactions_ptr())[0]->inputs_ptr())[0]->script().ops()[2].data());
    system::cout << message << std::endl;

    return EXIT_SUCCESS;
}
