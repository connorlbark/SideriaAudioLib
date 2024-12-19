#pragma once

namespace siderialib {

#if DOUBLE_PRECISION
    typedef double sfloat;
#else
    typedef float sfloat;
#endif

    const double PI = 3.1415926535897932384626f;
    const double TWOPI = 2.*PI;


    struct Fraction {
        int numerator;
        int denominator;
    };
}

