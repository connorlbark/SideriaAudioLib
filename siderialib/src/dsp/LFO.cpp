#include "../../include/dsp/LFO.h"
#include "../../include/siderialib.h"
#include "../../include/util/Random.h"
using namespace siderialib;

void LFO::incrementPhase() {
    lastPhase = phase;
	phase += phasePerSample;
	if (phase > 1.0) {
		phase -= 1.0;
	}
}

double LFO::tick() {
	incrementPhase();
	return modSource(phase) * depth;
}

double LFO::modSource(double phase) {
	switch (this->type) {
        case RANDOM:
            if (lastPhase > phase) {
                _randomSourceVal = random::nextUniform();
            }
            return _randomSourceVal;
        case TRIANGLE:
            if (phase < 0.5) {
                return phase * 2;
            }
            return 2. - phase * 2;
	default:
        double out = (std::sin(phase * TWOPI) + 1) / 2;

		return out;
	}
}

void LFO::setRateHz(sfloat hz) {
	this->hz = hz;

	phasePerSample = (long double)hz/(long double)sampleRate;
}

void LFO::setDepth(sfloat depth) {
	this->depth = depth;
}

sfloat LFO::getRateHz() {
	return this->hz;
}

sfloat LFO::getDepth() {
	return this->depth;
}

void LFO::setType(LFOType type) {
	this->type = type;
}