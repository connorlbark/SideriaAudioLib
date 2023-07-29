#include "../../include/dsp/Math.h"


double siderialib::InterpolateHermite4pt3oX(double x0, double x1, double x2, double x3, double t) {
    double diff = x1 - x2;
    double c1 = x2 - x0;
    double c3 = x3 - x0 + 3 * diff;
    double c2 = -(2 * diff + c1 + c3);
    return 0.5f * ((c3 * t + c2) * t + c1) * t + x1;
}