#include "Decimate.h"

using namespace siderialib;

void Decimate::initialize() {
    this->_downsampleFactor = 1;
    this->_counter = 0;
}

void Decimate::setDownsampleFactor(int factor) {
    this->_downsampleFactor = factor;
    this->_counter = 0;
}

sfloat Decimate::tick(sfloat in) {
    if (_counter == 0) {
        _value = in;
    }

    _counter = (_counter + 1) % _downsampleFactor;
    return _value;
}

int Decimate::getDownsampleFactor() const {
    return _downsampleFactor;
}
