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

	this->buf.writeCircular(L + delayedL * feedback, R + delayedR * feedback);

	_lastOutL = L * (mix - 1.f) + delayedL * mix;
	_lastOutR = R * (mix - 1.f) + delayedR * mix;

    samples++;
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
	this->_mod.setDepth(1.0);
	this->_mod.setRateHz(1.0);

    this->enableHpf = false;
    this->enableLpf = false;
    this->_lpf.initialize(sampleRate, BiquadType::LPF, sampleRate/2.f, 1.0);
    this->_hpf.initialize(sampleRate, BiquadType::HPF, 0.0f, 1.0);
}

sfloat ModulatedDelay::lastOutL() {
	return _lastOutL;
}

sfloat ModulatedDelay::lastOutR() {
	return _lastOutR;
}