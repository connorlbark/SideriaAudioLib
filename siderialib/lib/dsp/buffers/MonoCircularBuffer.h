#pragma once

#include "../../siderialib.h"
#include "util/StaticMemoryAllocation.h"

namespace siderialib {
	class MonoCircularBuffer {
	private:

		sfloat* _buf;
		int _numSamples;

		int _circularSampleIdx;

        int flattenIndex(int sample) const;

		void incrementCircularSampleIdx();
	public:
        MonoCircularBuffer() = default;

		int mapToNonCircularIndex(int sample) const;

		// initializes the buffer with two channels and the specified number of samples
        void initialize(StaticMemoryAllocation &sma, int numSamples);

		sfloat read(int sample) const;

		void write(sfloat val, int sample);

		int size() const;

		int numChannels() const;

		// fills out "in" with the most recently written samples
		sfloat readCircular() const;

		// increments circular pointer and writes the sample
		void writeCircular(sfloat val);

		// read into the past starting from the latest write to the buffer
		sfloat readCircular(int numSampsAgo) const;

        sfloat hermiteInterpolation(int index, double t) const;
        sfloat linearInterpolation(int index, double t) const;
    };
}

