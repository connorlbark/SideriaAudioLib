#pragma once

#include "../../dsp/buffers/StereoCircularBuffer.h"
#include "../../dsp/LFO.h"
#include "../../effects/filter/BiquadFilter.h"

namespace siderialib {
	class ModulatedDelay {
	private:
		StereoCircularBuffer buf;

		sfloat mix = 0.5;
		sfloat delaySamps = 1;
		sfloat sampleRate;
		sfloat feedback = 0.0;

        LFO _mod1;
        LFO _mod2;

        // placed before writing to circular buffer, so in essence, filters delayed sounds many times
        BiquadFilter _lpfL;
        BiquadFilter _lpfR;
        bool _enableLpf;
        // placed before writing to circular buffer, so in essence, filters delayed sounds many times
        BiquadFilter _hpfL;
        BiquadFilter _hpfR;
        bool _enableHpf;

		sfloat _lastOutL;
		sfloat _lastOutR;

        void writeToBuffer(sfloat L, sfloat R);
	public:

        void initialize(sfloat sampleRate, int maxDelaySamps);
        void initialize(sfloat sampleRate, sfloat *buf, int maxDelaySamps);

		void tick(sfloat L, sfloat R);

		sfloat lastOutL();
		sfloat lastOutR();

		void setMix(sfloat mix) { this->mix = mix; };
		sfloat getMix() { return this->mix; }

		void setDelayMs(sfloat ms) { this->delaySamps = ((ms / 1000.0f) * sampleRate); }
		sfloat getDelayMs() { return (this->delaySamps / sampleRate) * 1000.0f; };

		void setFeedback(sfloat feedback) { this->feedback = feedback; }
		sfloat getFeedback() { return feedback; }

        inline LFO &mod1() { return _mod1; };
        inline LFO &mod2() { return _mod2; }

        void setLpfParams(sfloat cutoff, sfloat Q, sfloat dBGain);
        void setHpfParams(sfloat cutoff, sfloat Q, sfloat dBGain);

        void enableLpf(bool enabled) { this->_enableLpf = enabled; }
        void enableHpf(bool enabled) { this->_enableHpf = enabled; }
	};
}