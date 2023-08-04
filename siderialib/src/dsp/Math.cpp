#include "../../include/dsp/Math.h"


using namespace siderialib;

double siderialib::InterpolateHermite4pt3oX(double x0, double x1, double x2, double x3, double t) {
    double diff = x1 - x2;
    double c1 = x2 - x0;
    double c3 = x3 - x0 + 3 * diff;
    double c2 = -(2 * diff + c1 + c3);
    return 0.5f * ((c3 * t + c2) * t + c1) * t + x1;
}

sfloat siderialib::triangleWave(sfloat x) {
    if (x < 0) {
        return 0;
    }

    if (x < .25) {
        return x * 4.f;
    } else if (x < 0.75) {
        return 2.f-4.f * x;
    } else if (x < 1) {
        return 4.f * x - 4.f;
    }

    return 0;
}