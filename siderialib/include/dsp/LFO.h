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
        double _phase = 0.0;
		sfloat _hz = 100.0f;
		sfloat _depth = 0.0f;
		double _phasePerSample = 0.0;
		sfloat _sampleRate = 0.0f;

		void incrementPhase();
		double modSource(double phase);

	public:
		void initialize(sfloat sampleRate) { this->_sampleRate = sampleRate; }
		// tick modulation, result will be inbetween 0.0 to 1.0
		double tick();
        inline double value() { return this->modSource(_phase) * _depth; };
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
        void setPhase(double phase) { this->_phase = fmod(phase, 1.0); }
        double getPhase() { return this->_phase; }
	};
}