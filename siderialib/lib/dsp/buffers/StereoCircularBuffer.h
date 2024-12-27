#pragma once

#include "../../siderialib.h"
#include "util/StaticMemoryAllocation.h"

namespace siderialib {
	// circular buffer with two channels for simplified
	// operation in the most common case, stereo
	class StereoCircularBuffer {
	private:

		sfloat* _buf;
		int _numSamples;

		int _circularSampleIdx;

        int flattenIndex(int channel, int sample) const;

		void incrementCircularSampleIdx();
	public:
        StereoCircularBuffer() = default;

		int mapToNonCircularIndex(int sample) const;

		// initializes the buffer with two channels and the specified number of samples
        void initialize(StaticMemoryAllocation &sma, int numSamples);

		sfloat read(int channel, int sample) const;

		void write(sfloat val, int channel, int sample);

		int size() const;

		int numChannels() const;

		// fills out "in" with the most recently written samples
		sfloat readCircular(int channel) const;

		// increments circular pointer and writes the sample
		void writeCircular(sfloat L, sfloat R);

		// read into the past starting from the latest write to the buffer
		sfloat readCircular(int channel, int numSampsAgo) const;

        sfloat hermiteInterpolation(int channel, int index, double t) const;
        sfloat linearInterpolation(int channel, int index, double t) const;
    };
}

