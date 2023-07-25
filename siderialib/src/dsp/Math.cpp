#include "../../include/dsp/Math.h"


sfloat siderialib::InterpolateHermite4pt3oX(sfloat x0, sfloat x1, sfloat x2, sfloat x3, sfloat t) {
    float diff = x1 - x2;
    float c1 = x2 - x0;
    float c3 = x3 - x0 + 3 * diff;
    float c2 = -(2 * diff + c1 + c3);
    return 0.5f * ((c3 * t + c2) * t + c1) * t + x1;
}