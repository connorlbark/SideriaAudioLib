#pragma once

#include "Types.h"

namespace siderialib {
	enum LFOType {
		SIN = 0,
	};

	class LFO {
	private:
		LFOType type;

		// phase wraps around from 0.0 to 1.0
		sfloat phase;
		sfloat rateMs;
		sfloat ms;
		sfloat depth;
		sfloat phasePerSample;
		sfloat sampleRate;

		void incrementPhase();
		sfloat modSource(sfloat phase);

	public:
		// tick modulation, result will be inbetween 0.0 to 1.0
		sfloat tick();
		// set rate as a time in milliseconds
		void setRateMs(sfloat ms);
		// set depth as a percentage, from 0.0 to 1.0
		void setDepth(sfloat depth);
		// get rate as milliseconds
		sfloat getRateMs();
		// get depth as percentage
		sfloat getDepth();
		// set modulation type, e.g., SIN
		void setType(LFOType type);
	};
}