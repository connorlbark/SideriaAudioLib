#include "../../include/dsp/LFO.h"
#include "../../include/siderialib.h"

using namespace siderialib;

void LFO::incrementPhase() {
    _phase += _phasePerSample;
	if (_phase > 1.0) {
        _phase -= 1.0;
	}
}

double LFO::tick() {
	incrementPhase();
	return value();
}

double LFO::modSource(double phase) {
	switch (this->_type) {
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
	this->_hz = hz;

    _phasePerSample = (double)hz / (double)_sampleRate;
}

void LFO::setDepth(sfloat depth) {
	this->_depth = depth;
}

sfloat LFO::getRateHz() {
	return this->_hz;
}

sfloat LFO::getDepth() {
	return this->_depth;
}

void LFO::setType(LFOType type) {
	this->_type = type;
}

