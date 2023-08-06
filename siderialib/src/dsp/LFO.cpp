#include "../../include/dsp/LFO.h"
#include "../../include/siderialib.h"

using namespace siderialib;

void LFO::incrementPhase() {
    _phase += _phasePerSample;
	if (_phase > 1.0) {
        _phase -= 1.0;
	}
}

void LFO::tick() {
	incrementPhase();
	_val = this->modSource(_phase) * _depth;
}

double LFO::modSource(double phase) {
	switch (this->_type) {
    case TRIANGLE:
        if (phase < 0.5) {
            return phase * 2.f;
        }
        return 2.f - phase * 2.f;
	default:
        double out = (sinf(phase * TWOPI) + 1) / 2;

		return out;
	}
}

void LFO::setRateHz(sfloat hz) {
	this->_hz = hz;

    _phasePerSample = hz / _sampleRate;
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

