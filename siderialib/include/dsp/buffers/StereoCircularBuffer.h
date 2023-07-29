#pragma once

#include "../Buffer.h"

namespace siderialib {
	// circular buffer with two channels for simplified
	// operation in the most common case, stereo
	class StereoCircularBuffer : public Buffer {
	private:

		sfloat* buf;
		int numSamples;

		int circularSampleIdx;

		inline int flattenIndex(int channel, int sample);

		void incrementCircularSampleIdx();
	public:
        ~StereoCircularBuffer();

		int mapToNonCircularIndex(int sample);

		// initializes the buffer with two channels and the specified number of samples
		void initialize(int numSamples);

		sfloat read(int channel, int sample) override final;

		void write(sfloat val, int channel, int sample) override final;

		int size() override final;

		int numChannels() override final;

		// fills out "in" with the most recently written samples
		sfloat readCircular(int channel);

		// increments circular pointer and writes the sample
		void writeCircular(sfloat L, sfloat R);

		// read into the past starting from the latest write to the buffer
		sfloat readCircular(int channel, int numSampsAgo);
	};
}

