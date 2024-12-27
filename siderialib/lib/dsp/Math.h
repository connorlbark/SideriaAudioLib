#pragma once

#include "Types.h"

namespace siderialib {

    // from https://stackoverflow.com/questions/1125666/how-do-you-do-bicubic-or-other-non-linear-interpolation-of-re-sampled-audio-da
    // trying to get x(n+t) where x1 is x(n), x0 is x(n-1), x2 is x(n+1), x3 is x(n+2)
    double InterpolateHermite4pt3oX(double x0, double x1, double x2, double x3, double t);

    sfloat linearInterpolation(sfloat x0, sfloat x1, double t);

    sfloat triangleWave(sfloat x);

    sfloat constantPowerPanL(sfloat pan, sfloat l);
    sfloat constantPowerPanR(sfloat pan, sfloat r);

    sfloat randUniform(unsigned long *seed);
    bool randBool(unsigned long *seed);

    // val must be in [0, 1]
    Fraction floatToFraction(sfloat val, int maxDenominator = 7);
}