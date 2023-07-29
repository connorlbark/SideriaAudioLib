#include "../../include/dsp/Buffer.h"
#include "../../include/dsp/Math.h"

using namespace siderialib;

sfloat Buffer::hermiteInterpolation(int channel, int index, double t) {
    return (sfloat)InterpolateHermite4pt3oX(
        read(channel, index - 1),
        read(channel, index),
        read(channel, index + 1),
        read(channel, index + 2),
        t
    );
}


sfloat x1;
sfloat x2;
double Buffer::linearInterpolation(int channel, int index, double t) {
    x1 = read(channel, index);
    x2 = read(channel, index + 1);

    double out = x1 + (x2 - x1) * t;
    return (sfloat) out;
}