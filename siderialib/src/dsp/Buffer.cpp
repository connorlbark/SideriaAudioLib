#include "../../include/dsp/Buffer.h"
#include "../../include/dsp/Math.h"

using namespace siderialib;



sfloat Buffer::hermiteInterpolation(int channel, sfloat sample) {
    int floored = (int)sample;
    return InterpolateHermite4pt3oX(
        read(channel, floored-1),
        read(channel, floored),
        read(channel, floored+1),
        read(channel, floored+2),
        sample - floored
    );
}

sfloat Buffer::hermiteInterpolation(int channel, int index, sfloat t) {
    return InterpolateHermite4pt3oX(
        read(channel, index - 1),
        read(channel, index),
        read(channel, index + 1),
        read(channel, index + 2),
        t
    );
}

sfloat Buffer::linearInterpolation(int channel, int index, sfloat t) {
    return read(channel, index) * (1.f - t) + read(channel, index + 1) * t;
}