#pragma once
#include "daisy_petal.h"
using namespace daisy;

class SmoothedParameter
{
private:
  float _lastVal = 0.0;
  float _val = 0.0;

public:
  Parameter param;

  SmoothedParameter() {}

  void Process();
  inline float Value();
  bool Changed();
};

#include <cmath>
#include "../params.h"

const float a = exp(-6.28318530718 / (SMOOTHING_TIME_MS * 0.001f * SAMPLE_RATE));
const float b = 1.0f - a;

void SmoothedParameter::Process()
{
  _lastVal = _val;
  _val = (param.Process() * b) + (_val * a);
}

inline float SmoothedParameter::Value()
{
  return _val;
}

inline bool SmoothedParameter::Changed()
{
  return abs(_val - _lastVal) < .01;
}
