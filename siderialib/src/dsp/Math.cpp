#include "../../include/dsp/Math.h"
#include <cmath>

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


sfloat siderialib::constantPowerPanL(siderialib::sfloat pan, siderialib::sfloat l) {
    return sqrt(pan) * l;
}

sfloat siderialib::constantPowerPanR(siderialib::sfloat pan, siderialib::sfloat r) {
    return sqrt(1-pan) * r;
}

sfloat siderialib::randUniform(unsigned long *seed) {
    // Linear congruential generator parameters
    const unsigned long a = 1664525;  // multiplier
    const unsigned long c = 1013904223;  // increment
    const unsigned long m = 4294967296;  // modulus (2^32)

    // Update the seed using LCG
    *seed = (a * (*seed) + c) % m;

    // Convert to float in range [0, 1)
    return (sfloat)(*seed) / (sfloat)m;
}

bool siderialib::randBool(unsigned long *seed) {
    return siderialib::randUniform(seed) > 0.5;
}