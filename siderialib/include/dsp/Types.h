#pragma once

namespace siderialib {
    const double PI = 3.1415926535897932384626;
    const double TWOPI = 2*PI;

#if DOUBLE_PRECISION
    typedef double sfloat;
#else
    typedef float sfloat;
#endif

    // svec2 offers an easy way to work with stereo audio
    struct svec2 {
        sfloat x;
        sfloat y;

        svec2() {
            x = 0;
            y = 0;
        }

        svec2(sfloat x, sfloat y) {
            this->x = x;
            this->y = y;
        }

        svec2(sfloat val) {
            this->x = val;
            this->y = val;
        }


        svec2 operator*(sfloat f) {
            return svec2(this->x * f, this->y * f);
        }

        svec2 operator*(svec2 & f) {
            return svec2(this->x * f.x, this->y * f.y);
        }

        void operator*=(sfloat f) {
            this->x *= f;
            this->y *= f;
        }

        void operator*=(svec2& f) {
            this->x *= f.x;
            this->y *= f.y;
        }

        svec2 operator+(svec2 f) {
            return svec2(this->x + f.x, this->y + f.y);
        }

        void operator+=(svec2& f) {
            this->x += f.x;
            this->y += f.y;
        }

        inline sfloat L() { return x; }

        inline sfloat R() { return y; }
    };
}

