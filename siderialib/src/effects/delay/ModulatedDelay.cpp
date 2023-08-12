#include "../../../include/effects/delay/ModulatedDelay.h"

using namespace siderialib;

void ModulatedDelay::tick(sfloat L, sfloat R) {
    sfloat mod = this->_mod->value();

    sfloat modulatedDelaySamps = (sfloat)this->_buf.mapToNonCircularIndex((int)this->_delaySamps.tick()) + mod * 400.0f;

	int flooredModDelaySamps = (int)std::floor(modulatedDelaySamps);
    double t = modulatedDelaySamps - (sfloat)flooredModDelaySamps;

    sfloat delayedL = this->_buf.linearInterpolation(0, flooredModDelaySamps, t);
    sfloat delayedR = this->_buf.linearInterpolation(1, flooredModDelaySamps, t);

    writeToBuffer(L + delayedL * _feedback, R + delayedR * _feedback);

	_lastOutL = L * (_mix - 1.f) + delayedL * _mix;
	_lastOutR = R * (_mix - 1.f) + delayedR * _mix;
}

void ModulatedDelay::writeToBuffer(sfloat L, sfloat R) {
    if (_enableHpf) {
        L = this->_hpfL.tick(L);
        R = this->_hpfR.tick(R);
    }
    if (_enableLpf) {
        L = this->_lpfL.tick(L);
        R = this->_lpfR.tick(R);
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

    this->_enableHpf = false;
    this->_enableLpf = false;
    this->_lpfL.initialize(_sampleRate, BiquadType::LPF, _sampleRate/2.f, 1.0);
    this->_lpfR.initialize(_sampleRate, BiquadType::LPF, _sampleRate/2.f, 1.0);
    this->_hpfL.initialize(_sampleRate, BiquadType::HPF, 0.0f, 1.0);
    this->_hpfR.initialize(_sampleRate, BiquadType::HPF, 0.0f, 1.0);
}

void ModulatedDelay::initialize(LFO *lfo, float sampleRate, sfloat *buf, int bufLength) {
    this->_buf.initialize(buf, bufLength);
    this->_delaySamps.initialize(1000.0, sampleRate);
    this->_sampleRate = sampleRate;
    _lastOutL = 0.f;
    _lastOutR = 0.f;
    this->_mix = 1.0f;

    this->_mod = lfo;
//    this->_mod.initialize(sampleRate);
//    this->_mod.setDepth(0.0);
//    this->_mod.setRateHz(1.0);

    this->_enableHpf = false;
    this->_enableLpf = false;
    this->_lpfL.initialize(sampleRate, BiquadType::LPF, sampleRate/2.f, 1.0);
    this->_lpfR.initialize(sampleRate, BiquadType::LPF, sampleRate/2.f, 1.0);
    this->_hpfL.initialize(sampleRate, BiquadType::HPF, 0.0f, 1.0);
    this->_hpfR.initialize(sampleRate, BiquadType::HPF, 0.0f, 1.0);

}

sfloat ModulatedDelay::lastOutL() const {
	return _lastOutL;
}

sfloat ModulatedDelay::lastOutR() const {
	return _lastOutR;
}

void ModulatedDelay::setLpfParams(sfloat cutoff, sfloat Q, sfloat dBGain) {
    this->_lpfL.setParams(cutoff, Q, dBGain);
    this->_lpfR.setParams(cutoff, Q, dBGain);
}

void ModulatedDelay::setHpfParams(sfloat cutoff, sfloat Q, sfloat dBGain) {
    this->_hpfL.setParams(cutoff, Q, dBGain);
    this->_hpfR.setParams(cutoff, Q, dBGain);
}