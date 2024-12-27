#include "Upsample.h"

using namespace siderialib;

void Upsample::initialize(StaticMemoryAllocation &sma, int maxUpSampleFactor) {
    this->_upsampleFactor = 1;
    this->_outputBuffer.initialize(sma, maxUpSampleFactor);
}

int Upsample::getOutBufferSize() const {
    return _upsampleFactor;
}

int Upsample::getUpsampleFactor() const {
    return _upsampleFactor;
}

sfloat Upsample::readOutputBuffer(int index) {
    return _outputBuffer.readCircular( index);
}

void Upsample::tick(sfloat in) {
    double delta = 1.0 / (double )_upsampleFactor;

    for (int i = _upsampleFactor - 1; i >= 1; i--) {
        _outputBuffer.writeCircular(linearInterpolation(
                _lastSample,
                in,
                delta * (double)i));
    }

    _outputBuffer.writeCircular(_lastSample);


    _lastSample = in;
}

void Upsample::setUpsampleFactor(int ratio) {
    this->_upsampleFactor = ratio;
}