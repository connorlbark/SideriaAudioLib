#pragma once

#include "../../StereoEffect.h"
#include "../../dsp/buffers/StereoCircularBuffer.h"
#include "../../dsp/LFO.h"

namespace siderialib {
	class ModulatedDelay : public StereoEffect {
	private:
		StereoCircularBuffer buf;

		sfloat mix = 0.5;
		int delaySamps = 1;
		sfloat sampleRate;
		sfloat feedback = 0.0;

		LFO mod;

		sfloat _lastOutL;
		sfloat _lastOutR;
	public:

		void initialize(sfloat sampleRate, int maxDelaySamps);

		void tick(Buffer& buf) override final;
		void tick(Buffer& in, Buffer& out) override final;

		void tick(sfloat L, sfloat R) override final;

		sfloat lastOutL() override final;
		sfloat lastOutR() override final;

		void setMix(sfloat mix) { this->mix = mix; };
		sfloat getMix() { this->mix; }

		void setDelayMs(sfloat ms) { this->delaySamps = (int)((ms / 1000.0f) * sampleRate); }
		sfloat getDelayMs() { return (this->delaySamps / sampleRate) * 1000.0f; };

		void setFeedback(sfloat feedback) { this->feedback = feedback; }
		sfloat getFeedback() { return feedback; }
	};
}