#include "SmoothedParameter.h"
#include "../params.h"
#include <cmath>

const float a = exp(-6.28318530718 / (SMOOTHING_TIME_MS * 0.001f * SAMPLE_RATE));
const float b = 1.0f - a;

void SmoothedParameter::Process()
{
  _lastVal = _val;
  _val = (param.Value() * b) + (_val * a);
}

inline float SmoothedParameter::Value()
{
  return _val;
}

inline bool SmoothedParameter::Changed()
{
  return abs(_val - _lastVal) < .01;
}
