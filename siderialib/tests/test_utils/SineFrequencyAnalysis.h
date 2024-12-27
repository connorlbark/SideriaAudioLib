#pragma once

#include "../../lib/siderialib.h"
#include <functional>


namespace siderialib {
    class SineFrequencyAnalysis {
    private:
        std::function<sfloat(sfloat)> run;
        std::function<void(void)> reset;

        sfloat samplingRate;

        int nStabilityTicks = 0; // default to zero


    public:
        void initialize(
                std::function<sfloat(sfloat)> run,
                std::function<void(void)> reset,
                sfloat samplingRate);

        sfloat analyze(sfloat freqHz, sfloat amp, int numTicks);

        std::vector<sfloat> analyze(
                sfloat minFreqHz,
                sfloat maxFreqHz,
                int numBins,
                sfloat amp,
                int numTicks);

        void setStabilityBuffer(int nTicks);
    };
}



