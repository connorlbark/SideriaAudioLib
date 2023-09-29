#pragma once
#include "daisy_petal.h"
using namespace daisy;

class TrackedParameter
{
private:
  float _realValue;
  float _changingValue;
  float _out;
  Parameter _param;

  bool _continuousChanges;
  bool _isChanging;

  bool _hasChanged;

  float _sensitivity = 0.07;

  inline void _updateValue(float newValue)
  {
    this->_realValue = newValue;

    if (abs(_realValue - _out) > _sensitivity)
    {
      if (!_continuousChanges)
      {
        if (!_isChanging)
        {
          _isChanging = true;
        }
      }
      else
      {
        _hasChanged = true;
      }
      this->_out = _realValue;
    }
    else if (!_continuousChanges && _isChanging)
    {
      _hasChanged = true;
      _isChanging = false;
    }
    else
    {
      _hasChanged = false;
      _isChanging = false;
    }
  }

public:
  void Init(daisy::AnalogControl input, float min, float max, daisy::Parameter::Curve curve, bool continuousUpdates, float sensitivity = 0.02f)
  {
    _param.Init(input, min, max, curve);
    this->_sensitivity = sensitivity;
    this->_realValue = _param.Value();
    this->_out = _realValue;
    this->_changingValue = continuousUpdates;
    this->_isChanging = false;
  }

  float Process()
  {
    _updateValue(_param.Process());
    return _out;
  }

  inline float Value()
  {
    return _out;
  }

  inline bool Changed()
  {
    return _hasChanged;
  }
};