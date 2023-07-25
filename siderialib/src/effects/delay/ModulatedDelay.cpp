#include "../../../include/effects/delay/ModulatedDelay.h"

using namespace siderialib;

void ModulatedDelay::tick(sfloat L, sfloat R) {
	sfloat delayedL = this->buf.readCircular(0, this->delaySamps);
	sfloat delayedR = this->buf.readCircular(0, this->delaySamps);

	
	this->buf.writeCircular(L + delayedL * feedback, R + delayedR * feedback);

	_lastOutL = L * (mix - 1.f) + delayedL * mix;
	_lastOutR = R * (mix - 1.f) + delayedR * mix;
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
}

sfloat ModulatedDelay::lastOutL() {
	return _lastOutL;
}

sfloat ModulatedDelay::lastOutR() {
	return _lastOutR;
}