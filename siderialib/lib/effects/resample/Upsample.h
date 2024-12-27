#pragma once

#include "dsp/buffers/MonoCircularBuffer.h"
#include "dsp/Math.h"

namespace siderialib {
    class Upsample {
    private:
        int _upsampleFactor = 1;

        // if we wanted to use more complex interpolation,
        // we could use a circular buffer to store the needed
        // samples
         MonoCircularBuffer _outputBuffer{};
        // since we're just doing linear interp
        // we can just store the last sample
        sfloat _lastSample = 0.0;
    public:
        Upsample() : _outputBuffer() {}

        void initialize(StaticMemoryAllocation &sma, int maxUpSampleFactor) {
            this->_upsampleFactor = 1;
            this->_outputBuffer.initialize(sma, maxUpSampleFactor);
        }

        void setUpsampleFactor(int ratio) {
            this->_upsampleFactor = ratio;
        }

        void tick(sfloat in) {
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

        sfloat readOutputBuffer(int index) {
            return _outputBuffer.readCircular( index);
        }

        int getOutBufferSize() const {
            return _upsampleFactor;
        }


        int getUpsampleFactor() const {
            return _upsampleFactor;
        }
    };
}