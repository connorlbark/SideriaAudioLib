#include "../../../include/effects/delay/ModulatedDelay.h"

using namespace siderialib;

void ModulatedDelay::tick(sfloat L, sfloat R) {
    sfloat mod = this->_mod->value();

    sfloat modulatedDelaySamps = (sfloat)this->_buf.mapToNonCircularIndex((int)this->_delaySamps.tick()) + mod * 400.0f;

	int flooredModDelaySamps = (int)(modulatedDelaySamps);
    double t = modulatedDelaySamps - (sfloat)flooredModDelaySamps;

    sfloat delayedL = this->_buf.linearInterpolation(0, flooredModDelaySamps, t);
    sfloat delayedR = this->_buf.linearInterpolation(1, flooredModDelaySamps, t);

    if (_pingPong) {
        writeToBuffer((L + R) / 2.f + delayedR * _feedback, delayedL * _feedback);
    } else {
        writeToBuffer(L + delayedL * _feedback, R + delayedR * _feedback);
    }

	_lastOutL = L * (_mix - 1.f) + delayedL * _mix;
	_lastOutR = R * (_mix - 1.f) + delayedR * _mix;
}

void ModulatedDelay::writeToBuffer(sfloat L, sfloat R) {

    if (_enableLpf) {
        L = this->_lpf1L.tick(this->_lpf2L.tick(L));
        R = this->_lpf1R.tick(this->_lpf2R.tick(R));
    }


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

    this->_enableLpf = false;
    this->_lpf1L.initialize(_sampleRate, BiquadType::LPF, _sampleRate/2.f, 1.0);
    this->_lpf1R.initialize(_sampleRate, BiquadType::LPF, _sampleRate/2.f, 1.0);
    this->_lpf2L.initialize(_sampleRate, BiquadType::LPF, _sampleRate/2.f, 1.0);
    this->_lpf2R.initialize(_sampleRate, BiquadType::LPF, _sampleRate/2.f, 1.0);
}

void ModulatedDelay::initialize(LFO *lfo, float sampleRate, sfloat *buf, int bufLength) {
    this->_buf.initialize(buf, bufLength);
    this->_delaySamps.initialize(1000.0, sampleRate);
    this->_sampleRate = sampleRate;
    _lastOutL = 0.f;
    _lastOutR = 0.f;
    this->_mix = 1.0f;

    this->_mod = lfo;

    this->_enableLpf = false;
    this->_lpf1L.initialize(sampleRate, BiquadType::LPF, sampleRate/2.f, 1.0);
    this->_lpf1R.initialize(sampleRate, BiquadType::LPF, sampleRate/2.f, 1.0);
    this->_lpf2L.initialize(sampleRate, BiquadType::LPF, sampleRate/2.f, 1.0);
    this->_lpf2R.initialize(sampleRate, BiquadType::LPF, sampleRate/2.f, 1.0);

}

sfloat ModulatedDelay::lastOutL() const {
	return _lastOutL;
}

sfloat ModulatedDelay::lastOutR() const {
	return _lastOutR;
}

void ModulatedDelay::setLpfParams(sfloat cutoff, sfloat Q, sfloat dBGain) {
    this->_lpf1L.setParams(cutoff, Q, dBGain);
    this->_lpf1R.setParams(cutoff, Q, dBGain);
    this->_lpf2L.setParams(cutoff, Q, dBGain);
    this->_lpf2R.setParams(cutoff, Q, dBGain);

}
