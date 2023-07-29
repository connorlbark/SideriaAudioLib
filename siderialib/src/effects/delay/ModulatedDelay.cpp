#include "../../../include/effects/delay/ModulatedDelay.h"

using namespace siderialib;

static int samples = 0;
void ModulatedDelay::tick(sfloat L, sfloat R) {
    double mod = this->mod.tick();
    double modulatedDelaySamps = this->buf.mapToNonCircularIndex(this->delaySamps) + mod * 30.0;

	int flooredModDelaySamps = (int)floor(modulatedDelaySamps);
    double t = modulatedDelaySamps - flooredModDelaySamps;

    sfloat delayedL = this->buf.linearInterpolation(0, flooredModDelaySamps, t);
    sfloat delayedR = this->buf.linearInterpolation(1, flooredModDelaySamps, t);

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
	this->mod.initialize(sampleRate);
	this->mod.setDepth(1.0);
	this->mod.setRateHz(1.0);
}

sfloat ModulatedDelay::lastOutL() {
	return _lastOutL;
}

sfloat ModulatedDelay::lastOutR() {
	return _lastOutR;
}