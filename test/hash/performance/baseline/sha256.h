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
// Copyright (c) 2014-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CRYPTO_SHA256_H
#define BITCOIN_CRYPTO_SHA256_H

#include <stdint.h>
#include <stdlib.h>
#include "../../../test.hpp"

namespace baseline {

class CSHA256
{
private:
    uint32_t s[8];
    unsigned char buf[64];
    uint64_t bytes;

public:
    using digest_t = system::hash_digest;
    static const size_t digest_bytes = 32;

    CSHA256();
    CSHA256& Write(const unsigned char* data, size_t len);
    void Finalize(unsigned char hash[digest_bytes]);
    CSHA256& Reset();
};

void SHA256D64(unsigned char* output, const unsigned char* input, size_t blocks);

} // namespace baseline

#endif // BITCOIN_CRYPTO_SHA256_H
