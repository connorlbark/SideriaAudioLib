#include "SineFrequencyAnalysis.h"

#include <utility>
#include <iostream>

using namespace siderialib;

void SineFrequencyAnalysis::initialize(
        std::function<sfloat(sfloat)> run,
        std::function<void(void)> reset,
        sfloat samplingRate) {
    this->run = std::move(run);
    this->reset = std::move(reset);
    this->samplingRate = samplingRate;
}


sfloat SineFrequencyAnalysis::analyze(sfloat freqHz, sfloat amp, int numTicks) {
    this->reset();

    sfloat maxOutputAmp = 0.f;
    double sinePhase = 0.f;
    double phasePerTick =  freqHz / samplingRate;

    // achieve stability
    for (int i = 0; i < nStabilityTicks; i ++) {
        this->run((sfloat)sin(sinePhase * 2 * PI) * amp);
        sinePhase += phasePerTick;
    }

    for (int i = 0; i < numTicks; i++) {
        sfloat out = this->run((sfloat)sin(sinePhase * 2 * PI) * amp);

        if (abs(out) > maxOutputAmp) {
            maxOutputAmp = abs(out);
        }

        sinePhase += phasePerTick;

        if (sinePhase > 1.0) {
            sinePhase -= 1.0;
        }
    }

    return maxOutputAmp;
}

std::vector<sfloat> SineFrequencyAnalysis::analyze(sfloat minFreqHz, sfloat maxFreqHz, int numBins, sfloat amp, int numTicks) {
    std::vector<sfloat> vals{};

    sfloat freqWidth = (maxFreqHz - minFreqHz) / numBins;

    for (int i = 0; i < numBins; i++) {
        sfloat freq = minFreqHz + freqWidth * (sfloat)i;

        vals.push_back(analyze(freq, amp, numTicks));
    }

    return vals;
}

void SineFrequencyAnalysis::setStabilityBuffer(int nTicks) {
    this->nStabilityTicks = nTicks;
}

