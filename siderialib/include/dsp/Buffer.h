#pragma once

#include "Types.h"

namespace siderialib {
	class Buffer {
	public:
		// reads from the buffer at the specified channel and sample indices
		virtual sfloat read(int channel, int sample) = 0;
		// writes to the buffer at the specified channel and sample indices
		virtual void write(sfloat in, int channel, int sample) = 0;
		// returns the number of samples the buffer contains per channel
		virtual int size() = 0;
		// returns the number of channels the buffer contains
		virtual int numChannels() = 0;

		sfloat hermiteInterpolation(int channel, sfloat idx);
		sfloat hermiteInterpolation(int channel, int index, sfloat t);
		sfloat linearInterpolation(int channel, int index, sfloat t);
		sfloat sincInterpolation(int channel, int index, sfloat t);
	};
}
