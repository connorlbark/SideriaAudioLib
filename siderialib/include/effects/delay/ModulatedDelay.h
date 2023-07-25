#pragma once

#include "../../Effect.h"
#include "../../dsp/buffers/StereoCircularBuffer.h"
#include "../../dsp/LFO.h"

namespace siderialib {
	class ModulatedDelay : public Effect {
	private:
		StereoCircularBuffer buf;

		sfloat mix = 0.5;
		int delaySamps = 1;
		sfloat sampleRate;
		sfloat feedback = 0.0;

		LFO mod;
	public:

		void initialize(sfloat sampleRate, int maxDelaySamps);

		void tick(Buffer& buf) override final;
		void tick(Buffer& in, Buffer& out) override final;

		void tick(svec2& in, svec2& out);

		void setMix(sfloat mix) { this->mix = mix; };
		sfloat getMix() { this->mix; }

		void setDelayMs(sfloat ms) { this->delaySamps = (int)((ms / 1000.0f) * sampleRate); }
		sfloat getDelayMs() { return (this->delaySamps / sampleRate) * 1000.0f; };

		void setFeedback(sfloat feedback) { this->feedback = feedback; }
		sfloat getFeedback() { return feedback; }
	};
}