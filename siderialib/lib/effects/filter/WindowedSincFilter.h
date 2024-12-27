#pragma once

#include "../../siderialib.h"
#include "../../dsp/buffers/MonoCircularBuffer.h"

namespace siderialib {
    class WindowedSincFilter {
    private:
        double *fir;
        MonoCircularBuffer hist;

        int firLength;
        sfloat sampleRate;


    public:
        ~WindowedSincFilter();

        void initialize(StaticMemoryAllocation &sma, int firLength, sfloat cutoff, sfloat sampleRate);

        double *getFir();
        int getFirLength() const;

        sfloat tick(sfloat in);
    };
}