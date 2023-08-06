#include "../../include/util/SmoothedParameter.h"
#include <cmath>

using namespace siderialib;


void SmoothedParameter::initialize(sfloat smoothingTimeMs, sfloat sampleRate) {
    _a = expf(-6.28318530718f / (smoothingTimeMs * 0.001f * sampleRate));
    _b = 1.0f - _a;
}


sfloat SmoothedParameter::tick()
{
    _val = (_target * _b) + (_val * _a);
    return _val;
}
