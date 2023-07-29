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
	
#if SLIB_DEBUG
	if (hz <= 0.0) {
		throw new std::domain_error("Hz cannot be less than or equal to zero, instead given: " + std::to_string(hz));
	}
#endif
	
	this->hz = hz;

	phasePerSample = (long double)hz/(long double)sampleRate;
}

void LFO::setDepth(sfloat depth) {

#if SLIB_DEBUG
	if (depth < 0.0 || depth > 1.0) {
		throw new std::domain_error("Depth ranges from 0.0 to 1.0, instead given: " + std::to_string(depth));
	}
#endif

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