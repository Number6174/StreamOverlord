// SPDX-FileCopyrightText: 2021 Number6174
// SPDX-License-Identifier: GPL-3.0-or-later

#include "NonceGenerator.h"

#include <random>

std::string common::generateOAuthState(int length) {
    // Follows RFC 3986 https://tools.ietf.org/html/rfc3986
    // for characters that don't need to be percent-encoded
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                          "abcdefghijklmnopqrstuvwxyz"
                          "0123456789"
                          "-._~";

    // Setup PRNG
    std::random_device rnd;
    std::mt19937 prng{rnd()};
    std::uniform_int_distribution<int> dist(0, static_cast<int>(alphabet.size()));

    // Generate nonce
    std::string result;
    for (int i = 0; i < length; ++i)
        result += alphabet[dist(prng)];

    return result;
}
