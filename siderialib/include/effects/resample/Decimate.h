#pragma once

#include "dsp/Types.h"

namespace siderialib {
    class Decimate {
    private:

        int _downsampleFactor = 1;

        sfloat _value = 0.0;
        int _counter = 0;

    public:
        Decimate() = default;

        void initialize() {
            this->_downsampleFactor = 1;
            this->_counter = 0;
        }

        void setDownsampleFactor(int factor) {
            this->_downsampleFactor = factor;
            this->_counter = 0;
        }

        sfloat tick(sfloat in) {
            if (_counter == 0) {
                _value = in;
            }

            _counter = (_counter + 1) % _downsampleFactor;
            return _value;
        }


        int getDownsampleFactor() const {
            return _downsampleFactor;
        }
    };
}