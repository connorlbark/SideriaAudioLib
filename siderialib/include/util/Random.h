#pragma once

/*  Written in 2018 by David Blackman and Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */

#include <cstdint>
#include <cstring>

/* This is xoshiro256+ 1.0, our best and fastest generator for floating-point
   numbers. We suggest to use its upper bits for floating-point
   generation, as it is slightly faster than xoshiro256++/xoshiro256**. It
   passes all tests we are aware of except for the lowest three bits,
   which might fail linearity tests (and just those), so if low linear
   complexity is not considered an issue (as it is usually the case) it
   can be used to generate 64-bit outputs, too.

   We suggest to use a sign test to extract a random Boolean value, and
   right shifts to extract subsets of bits.

   The state must be seeded so that it is not everywhere zero. If you have
   a 64-bit seed, we suggest to seed a splitmix64 generator and use its
   output to fill s. */


namespace siderialib {
    namespace random {
        static inline uint64_t rotl(const uint64_t x, int k) {
            return (x << k) | (x >> (64 - k));
        }


        static uint64_t s[4];

        uint64_t next(void) {
            const uint64_t result = s[0] + s[3];

            const uint64_t t = s[1] << 17;

            s[2] ^= s[0];
            s[3] ^= s[1];
            s[1] ^= s[2];
            s[0] ^= s[3];

            s[2] ^= t;

            s[3] = rotl(s[3], 45);

            return result;
        }

        // from https://stackoverflow.com/questions/52147419/how-to-convert-random-uint64-t-to-random-double-in-range-0-1-using-bit-wise-o
        double to_01(uint64_t i) {
            constexpr uint64_t mask1 = 0x3FF0000000000000ULL;
            constexpr uint64_t mask2 = 0x3FFFFFFFFFFFFFFFULL;
            const uint64_t to_12 = (i | mask1) & mask2;
            double d;
            memcpy(&d, &to_12,
            8);
            return d - 1;
        }

        float nextUniform() {
            return (float) to_01(next());
        }
    }
}

