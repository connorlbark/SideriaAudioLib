#pragma once

#include "../../dsp/buffers/StereoCircularBuffer.h"
#include "../../dsp/LFO.h"
#include "../../effects/filter/BiquadFilter.h"
#include "../../util/SmoothedParameter.h"

namespace siderialib
{
	class ModulatedDelay
	{
	private:
		StereoCircularBuffer _buf;

		sfloat _mix = 0.5;
		SmoothedParameter _delaySamps;
		sfloat _sampleRate;
		sfloat _feedback = 0.0;

		LFO *_mod;

		// 2-stage lpf placed before writing to circular buffer, so in essence, filters delayed sounds many times
		BiquadFilter _lpf1L;
		BiquadFilter _lpf1R;
        BiquadFilter _lpf2L;
        BiquadFilter _lpf2R;
        bool _enableLpf;

		sfloat _lastOutL = 0.f;
		sfloat _lastOutR = 0.f;

		void writeToBuffer(sfloat L, sfloat R);

	public:
        ModulatedDelay() = default;

		void initialize(LFO *lfo, sfloat sampleRate, int maxDelaySamps);
		void initialize(LFO *lfo, sfloat sampleRate, sfloat *buf, int maxDelaySamps);

		void tick(sfloat L, sfloat R);

		sfloat lastOutL() const;
		sfloat lastOutR() const;

		void setMix(sfloat mix) { this->_mix = mix; }
		sfloat getMix() const { return this->_mix; }

		void setDelayMs(sfloat ms) { this->_delaySamps.setTarget((ms / 1000.0f) * _sampleRate); }
		sfloat getDelayMs() const { return (this->_delaySamps.value() / _sampleRate) * 1000.0f; }

		void setFeedback(sfloat feedback) { this->_feedback = feedback; }
		sfloat getFeedback() const { return _feedback; }

		void setLpfParams(sfloat cutoff, sfloat Q, sfloat dBGain);
		void enableLpf(bool enabled) { this->_enableLpf = enabled; }
	};
}