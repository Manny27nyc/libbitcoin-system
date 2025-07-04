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
#include "ec_context.hpp"

#include <secp256k1.h>
#include <bitcoin/system/define.hpp>

namespace libbitcoin {
namespace system {

// Protected constructor (abstract) base class.
// ----------------------------------------------------------------------------

ec_context::ec_context(int flags) NOEXCEPT
  : context_(secp256k1_context_create(flags))
{
    BC_ASSERT(context_ != nullptr);
}

ec_context::~ec_context() NOEXCEPT
{
    BC_ASSERT(context_ != nullptr);

    if (!is_null(context_))
        secp256k1_context_destroy(context_);
}

// Concrete type for signing init.
// ----------------------------------------------------------------------------

ec_context_sign::ec_context_sign() NOEXCEPT
  : ec_context(SECP256K1_CONTEXT_SIGN)
{
}

const secp256k1_context* ec_context_sign::context() NOEXCEPT
{
    static ec_context_sign instance{};
    static auto context = instance.context_;
    return context;
}

// Concrete type for verification init.
// ----------------------------------------------------------------------------

ec_context_verify::ec_context_verify() NOEXCEPT
  : ec_context(SECP256K1_CONTEXT_VERIFY)
{
}

const secp256k1_context* ec_context_verify::context() NOEXCEPT
{
    static ec_context_verify instance{};
    static auto context = instance.context_;
    return context;
}

} // namespace system
} // namespace libbitcoin
