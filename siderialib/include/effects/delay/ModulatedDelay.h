#pragma once

#include "../../dsp/buffers/StereoCircularBuffer.h"
#include "../../dsp/LFO.h"
#include "../../effects/filter/BiquadFilter.h"

namespace siderialib {
	class ModulatedDelay {
	private:
		StereoCircularBuffer _buf;

		sfloat _mix = 0.5;
		int _delaySamps = 1;
		sfloat _sampleRate;
		sfloat _feedback = 0.0;

		LFO _mod;

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

		void setMix(sfloat mix) { this->_mix = mix; }
		sfloat getMix() { return this->_mix; }

		void setDelayMs(sfloat ms) { this->_delaySamps = (int)((ms / 1000.0f) * _sampleRate); }
		sfloat getDelayMs() { return (this->_delaySamps / _sampleRate) * 1000.0f; }

		void setFeedback(sfloat feedback) { this->_feedback = feedback; }
		sfloat getFeedback() { return _feedback; }

        inline LFO &mod() { return _mod; }

        void setLpfParams(sfloat cutoff, sfloat Q, sfloat dBGain);
        void setHpfParams(sfloat cutoff, sfloat Q, sfloat dBGain);

        void enableLpf(bool enabled) { this->_enableLpf = enabled; }
        void enableHpf(bool enabled) { this->_enableHpf = enabled; }
	};
}