#pragma once

namespace siderialib {
    const double PI = 3.1415926535897932384626;
    const double TWOPI = 2*PI;

#if DOUBLE_PRECISION
    typedef double sfloat;
#else
    typedef float sfloat;
#endif
}

