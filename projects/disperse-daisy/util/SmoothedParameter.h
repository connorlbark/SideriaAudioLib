#pragma once
#include "daisy_petal.h"
using namespace daisy;

class SmoothedParameter
{
private:
  Parameter &param;

  float _lastVal = 0.0;
  float _val = 0.0;

public:
  SmoothedParameter(Parameter &param) : param(param) {}

  void Process();
  inline float Value();
  bool Changed();
};