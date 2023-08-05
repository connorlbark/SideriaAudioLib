
#include "../../include/util/Random.h"

#include <cstring>


namespace siderialib {
    namespace random {

        static inline uint64_t rotl(const uint64_t x, int k) {
            return (x << k) | (x >> (64 - k));
        }

        uint64_t next() {
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

