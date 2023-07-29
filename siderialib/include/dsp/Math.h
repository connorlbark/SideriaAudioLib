#pragma once

#include "Types.h"

namespace siderialib {

    // from https://stackoverflow.com/questions/1125666/how-do-you-do-bicubic-or-other-non-linear-interpolation-of-re-sampled-audio-da
    // trying to get x(n+t) where x1 is x(n), x0 is x(n-1), x2 is x(n+1), x3 is x(n+2)
    double InterpolateHermite4pt3oX(double x0, double x1, double x2, double x3, double t);
}