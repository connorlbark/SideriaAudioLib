#include "LFO.h"

using namespace siderialib;

void LFO::incrementPhase() {
    _phase += _phasePerSample;
	if (_phase > 1.0f) {
        _phase -= 1.0f;
	}
}

void LFO::tick() {
	incrementPhase();
	_val = this->modSource(_phase) * _depth;
}

sfloat LFO::modSource(sfloat phase) const {
	switch (this->_type) {
    case LFOType::TRIANGLE:
        if (phase < 0.5f) {
            return phase * 2.f;
        }
        return 2.f - phase * 2.f;
	default:

		return (sinf(phase * TWOPI) + 1.f) / 2.f;
	}
}

void LFO::setRateHz(sfloat hz) {
	this->_hz = hz;

    _phasePerSample = hz / _sampleRate;
}

void LFO::setDepth(sfloat depth) {
	this->_depth = depth;
}

sfloat LFO::getRateHz() const {
	return this->_hz;
}

sfloat LFO::getDepth() const {
	return this->_depth;
}

void LFO::setType(LFOType type) {
	this->_type = type;
}

