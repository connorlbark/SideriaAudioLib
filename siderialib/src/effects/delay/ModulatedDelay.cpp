#include "../../../include/effects/delay/ModulatedDelay.h"
#include "../../../include/siderialib.h"

using namespace siderialib;

static int samples = 0;
void ModulatedDelay::tick(sfloat L, sfloat R) {
    double mod = this->_mod.tick();
    double modulatedDelaySamps = this->buf.mapToNonCircularIndex(this->delaySamps) + mod * 400.0;

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

void ModulatedDelay::tick(Buffer& buf) {
	return this->tick(buf, buf);
}

void ModulatedDelay::tick(Buffer& in, Buffer& out) {

	for (int i = 0; i < in.size(); i++) {
		this->tick(in.read(0, i), in.read(1, i));

		out.write(_lastOutL, 0, i);
		out.write(_lastOutR, 1, i);
	}
}

void ModulatedDelay::initialize(float sampleRate, int maxDelaySamps) {
	this->buf.initialize(maxDelaySamps);
	this->sampleRate = sampleRate;
	_lastOutL = 0.f;
	_lastOutR = 0.f;
	this->_mod.initialize(sampleRate);
	this->_mod.setDepth(0.0);
	this->_mod.setRateHz(1.0);

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