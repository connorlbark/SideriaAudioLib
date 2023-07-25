#include "../../../include/effects/delay/ModulatedDelay.h"

using namespace siderialib;

void ModulatedDelay::tick(svec2& in, svec2& out) {
	svec2 delayed;
	this->buf.readCircular(delayed, this->delaySamps);

	svec2 feedback = in + delayed * feedback;
	this->buf.writeCircular(feedback);

	out.x = in.x * (mix - 1.f) + delayed.x * mix;
	out.y = in.y * (mix - 1.f) + delayed.y * mix;
}

void ModulatedDelay::tick(Buffer& buf) {
	return this->tick(buf, buf);
}

void ModulatedDelay::tick(Buffer& in, Buffer& out) {
	svec2 inVec;
	svec2 outVec;

	for (int i = 0; i < in.size(); i++) {
		inVec.x = in.read(0, i);
		inVec.y = in.read(1, i);

		this->tick(inVec, outVec);

		out.write(outVec.x, 0, i);
		out.write(outVec.y, 1, i);
	}
}

void ModulatedDelay::initialize(float sampleRate, int maxDelaySamps) {
	this->buf.initialize(maxDelaySamps);
	this->sampleRate = sampleRate;
}