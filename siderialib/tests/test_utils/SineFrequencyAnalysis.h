#pragma once

#include "../../include/siderialib.h"


namespace siderialib {
    class SineFrequencyAnalysis {
    private:
        std::function<sfloat(sfloat)> run;
        std::function<void(void)> reset;

        sfloat samplingRate;


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
    };
}



