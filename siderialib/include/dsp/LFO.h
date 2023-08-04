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
		LFOType type;

		// phase wraps around from 0.0 to 1.0
        double phase = 0.0;
		sfloat hz = 100.0f;
		sfloat depth = 0.0f;
		double phasePerSample = 0.0;
		sfloat sampleRate = 0.0f;

		void incrementPhase();
		double modSource(double phase);

	public:
		void initialize(sfloat sampleRate) { this->sampleRate = sampleRate; }
		// tick modulation, result will be inbetween 0.0 to 1.0
		double tick();
        inline double value() { return this->modSource(phase) * depth; };
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
        void setPhase(double phase) { this->phase = fmod(this->phase, 1.0); }
        double getPhase() { return this->phase; }
	};
}