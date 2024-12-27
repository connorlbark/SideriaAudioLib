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

        void initialize(StaticMemoryAllocation &sma, int maxUpSampleFactor);

        void setUpsampleFactor(int ratio);

        void tick(sfloat in);

        sfloat readOutputBuffer(int index);

        int getOutBufferSize() const;


        int getUpsampleFactor() const;
    };
}