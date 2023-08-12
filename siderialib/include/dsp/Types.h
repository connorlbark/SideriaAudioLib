#pragma once

namespace siderialib {

#if DOUBLE_PRECISION
    typedef double sfloat;
#else
    typedef float sfloat;
#endif

    const sfloat PI = 3.1415926535897932384626f;
    const sfloat TWOPI = 2.f*PI;

}

