#include "../../include/dsp/LFO.h"
#include "../../include/siderialib.h"

using namespace siderialib;

void LFO::incrementPhase() {
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