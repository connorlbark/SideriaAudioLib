#pragma once

#include "Types.h"
#include "../siderialib.h"

namespace siderialib {
	enum LFOType {
		SIN = 0,
        TRIANGLE = 1,
	};

	class LFO {
	private:
		LFOType _type;

		// phase wraps around from 0.0 to 1.0
        sfloat _phase = 0.0;
		sfloat _hz = 100.0f;
		sfloat _depth = 0.0f;
		sfloat _phasePerSample = 0.0;
		sfloat _sampleRate = 0.0f;

        sfloat _val = 0.f;

		void incrementPhase();
		double modSource(double phase);

	public:
		void initialize(sfloat sampleRate) { this->_sampleRate = sampleRate; }
		// tick modulation, result will be inbetween 0.0 to 1.0
		void tick();
        inline sfloat value() { return _val; }
		// set rate as a time in milliseconds
		void setRateHz(sfloat ms);
		// set depth as a percentage, from 0.0 to 1.0
		void setDepth(sfloat depth);
		// get rate as milliseconds
		sfloat getRateHz();
		// get depth as percentage
		sfloat getDepth();
		// set modulation type, e.g., SIN
		void setType(LFOType type);
        void setPhase(sfloat phase) { this->_phase = fmod(phase, 1.0f); }
        double getPhase() { return this->_phase; }
	};
}