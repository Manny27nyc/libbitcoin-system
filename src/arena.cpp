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
#include <bitcoin/system/arena.hpp>

#include <cstdlib>
#include <bitcoin/system/constants.hpp>

namespace libbitcoin {

bool operator==(const arena& left, const arena& right) NOEXCEPT
{
    return &left == &right || left.is_equal(right);
}

// static
// use bc::default_arena::get() vs. std::pmr::get_default_resource()
arena* default_arena::get() NOEXCEPT
{
    static default_arena resource{};
    return &resource;
}

void* default_arena::do_allocate(size_t bytes, size_t) THROWS
{
    ////if (align > __STDCPP_DEFAULT_NEW_ALIGNMENT__)
    ////    return ::operator new(bytes, std::align_val_t{ align });
    BC_PUSH_WARNING(NO_MALLOC_OR_FREE)
    return std::malloc(bytes);
    BC_POP_WARNING()
}

void default_arena::do_deallocate(void* ptr, size_t, size_t) NOEXCEPT
{
    ////if (align > __STDCPP_DEFAULT_NEW_ALIGNMENT__)
    ////    ::operator delete(ptr, std::align_val_t{ align });
    BC_PUSH_WARNING(NO_MALLOC_OR_FREE)
    std::free(ptr);
    BC_POP_WARNING()
}

bool default_arena::do_is_equal(const arena& other) const NOEXCEPT
{
    // Do not cross the streams.
    return &other == this;
}

// null return indicates that this arena is not detachable.
void* default_arena::start(size_t) THROWS
{
    return nullptr;
}

size_t default_arena::detach() NOEXCEPT
{
    return zero;
}

void default_arena::release(void*) NOEXCEPT
{
}

} // namespace libbitcoin
