#include "../../include/dsp/LFO.h"
#include <math.h>
#include <assert.h>
#if SLIB_DEBUG
#include <stdexcept>
#include <string>
#endif

using namespace siderialib;

void LFO::incrementPhase() {
	phase += phasePerSample;
	if (phase > 1.0f) {
		phase -= 1.0f;
	}
}

sfloat LFO::tick() {
	incrementPhase();
	return modSource(phase) * depth;
}

sfloat LFO::modSource(sfloat phase) {
	switch (this->type) {
	default:
		return sinf(phase * TWOPI);
	}
}

void LFO::setRateMs(sfloat ms) {
	
#if SLIB_DEBUG
	assert(ms > 0.0);
	if (ms <= 0.0) {
		throw new std::domain_error("Range cannot be less than or equal to zero, instead given: " + std::to_string(ms));
	}
#endif
	
	this->ms = ms;

	// sampleRate * ms/1000.0 = num samples per LFO repetition
	// 1/num samples per LFO repetition = phase (from 0 to 1) per sample
	phasePerSample = 1.0f / (sampleRate * (ms / 1000.0f));
}

void LFO::setDepth(sfloat depth) {

#if SLIB_DEBUG
	if (depth < 0.0 || depth > 1.0) {
		throw new std::domain_error("Depth ranges from 0.0 to 1.0, instead given: " + std::to_string(depth));
	}
#endif

	this->depth = depth;
}

sfloat LFO::getRateMs() {
	return this->ms;
}

sfloat LFO::getDepth() {
	return this->depth;
}

void LFO::setType(LFOType type) {
	this->type = type;
}