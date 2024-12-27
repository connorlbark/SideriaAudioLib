#include "../../../include/effects/delay/ModulatedDelay.h"
#include "dsp/Math.h"

using namespace siderialib;

void ModulatedDelay::tick(sfloat L, sfloat R) {
    sfloat mod = this->_mod->value();

    sfloat modulatedDelaySamps = (sfloat)this->_buf.mapToNonCircularIndex((int)this->_delaySamps.tick()) + mod * 400.0f;

	int flooredModDelaySamps = (int)(modulatedDelaySamps);
    double t = modulatedDelaySamps - (sfloat)flooredModDelaySamps;

    sfloat delayedL = this->_buf.linearInterpolation(0, flooredModDelaySamps, t);
    sfloat delayedR = this->_buf.linearInterpolation(1, flooredModDelaySamps, t);

    if (_pingPong) {
        if (_pingPongDirection == PingPongDirection::LEFT) {
            writeToBuffer((L + R) / 2.f + delayedR * _feedback, delayedL * _feedback);
        } else {
            writeToBuffer(delayedR * _feedback, (L + R) / 2.f + delayedL * _feedback);
        }

        // don't apply pan to ping pong
        _lastOutL = L * (_mix - 1.f) + delayedL * _mix;
        _lastOutR = R * (_mix - 1.f) + delayedR * _mix;
    } else {
        writeToBuffer(L + delayedL * _feedback,
                      R + delayedR * _feedback);

        _lastOutL = constantPowerPanL(this->_pan, delayedL * _mix) + L * (1.f - _mix);
        _lastOutR = constantPowerPanR(this->_pan, delayedR * _mix) + R * (1.f - _mix);
    }
}

void ModulatedDelay::writeToBuffer(sfloat L, sfloat R) {
    this->_buf.writeCircular(L, R);
}

void ModulatedDelay::initialize(LFO *lfo, float sampleRate, int maxDelaySamps) {
	this->_buf.initialize(maxDelaySamps);
    this->_delaySamps.initialize(1000.0, sampleRate);
	this->_sampleRate = sampleRate;
	_lastOutL = 0.f;
	_lastOutR = 0.f;
    this->_mix = 1.0f;

    this->_mod = lfo;
}

void ModulatedDelay::initialize(LFO *lfo, float sampleRate, sfloat *buf, int bufLength) {
    this->_buf.initialize(buf, bufLength);
    this->_delaySamps.initialize(1000.0, sampleRate);
    this->_sampleRate = sampleRate;
    _lastOutL = 0.f;
    _lastOutR = 0.f;
    this->_mix = 1.0f;

    this->_mod = lfo;
}

sfloat ModulatedDelay::lastOutL() const {
	return _lastOutL;
}

sfloat ModulatedDelay::lastOutR() const {
	return _lastOutR;
}

