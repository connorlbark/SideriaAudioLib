#include "../../../include/effects/delay/ModulatedDelay.h"
#include "../../../include/siderialib.h"

using namespace siderialib;

static int samples = 0;
void ModulatedDelay::tick(sfloat L, sfloat R) {
    double mod = this->_mod1.tick() + this->_mod2.tick();
    printf("%f\n", mod);
    double modulatedDelaySamps = this->buf.mapToNonCircularIndex(this->delaySamps) + mod;

    // make sure it is still w/n range ( may create artifacts, so make sure this doesn't happen outside the delay )
    modulatedDelaySamps = (modulatedDelaySamps < 0.f ? 0.f : modulatedDelaySamps);
    modulatedDelaySamps = (modulatedDelaySamps > this->buf.size() ? this->buf.size() : modulatedDelaySamps);

	int flooredModDelaySamps = (int)std::floor(modulatedDelaySamps);
    double t = modulatedDelaySamps - flooredModDelaySamps;

    sfloat delayedL = this->buf.hermiteInterpolation(0, flooredModDelaySamps, t);
    sfloat delayedR = this->buf.hermiteInterpolation(1, flooredModDelaySamps, t);


    writeToBuffer(L + delayedL * feedback, R + delayedR * feedback);

	_lastOutL = L * (mix - 1.f) + delayedL * mix;
	_lastOutR = R * (mix - 1.f) + delayedR * mix;

    samples++;
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

    this->buf.writeCircular(L, R);
}

void ModulatedDelay::initialize(float sampleRate, int maxDelaySamps) {
	this->buf.initialize(maxDelaySamps);
	this->sampleRate = sampleRate;
	_lastOutL = 0.f;
	_lastOutR = 0.f;
    this->mix = 1.0f;
	this->_mod1.initialize(sampleRate);
	this->_mod1.setDepth(0.0);
	this->_mod1.setRateHz(1.0);
    this->_mod2.initialize(sampleRate);
    this->_mod2.setDepth(0.0);
    this->_mod2.setRateHz(1.0);

    this->_enableHpf = false;
    this->_enableLpf = false;
    this->_lpfL.initialize(sampleRate, BiquadType::LPF, sampleRate/2.f, 1.0);
    this->_lpfR.initialize(sampleRate, BiquadType::LPF, sampleRate/2.f, 1.0);
    this->_hpfL.initialize(sampleRate, BiquadType::HPF, 0.0f, 1.0);
    this->_hpfR.initialize(sampleRate, BiquadType::HPF, 0.0f, 1.0);
}

void ModulatedDelay::initialize(float sampleRate, sfloat *buf, int bufLength) {
    this->buf.initialize(buf, bufLength);
    this->sampleRate = sampleRate;
    _lastOutL = 0.f;
    _lastOutR = 0.f;
    this->mix = 1.0f;
    this->_mod1.initialize(sampleRate);
    this->_mod1.setDepth(0.0);
    this->_mod1.setRateHz(1.0);
    this->_mod2.initialize(sampleRate);
    this->_mod2.setDepth(0.0);
    this->_mod2.setRateHz(1.0);

    this->_enableHpf = false;
    this->_enableLpf = false;
    this->_lpfL.initialize(sampleRate, BiquadType::LPF, sampleRate/2.f, 1.0);
    this->_lpfR.initialize(sampleRate, BiquadType::LPF, sampleRate/2.f, 1.0);
    this->_hpfL.initialize(sampleRate, BiquadType::HPF, 0.0f, 1.0);
    this->_hpfR.initialize(sampleRate, BiquadType::HPF, 0.0f, 1.0);

}

sfloat ModulatedDelay::lastOutL() {
	return _lastOutL;
}

sfloat ModulatedDelay::lastOutR() {
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