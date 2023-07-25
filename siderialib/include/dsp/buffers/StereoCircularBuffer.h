#pragma once

#include "../Buffer.h"
#include <assert.h>
#include <memory>

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

		// initializes the buffer with two channels and the specified number of samples
		void initialize(int numSamples);

		sfloat read(int channel, int sample) override final;

		void write(sfloat val, int channel, int sample) override final;

		int size() override final;

		int numChannels() override final;

		// fills out "in" with the most recently written samples
		void readCircular(svec2& in);

		// increments circular pointer and writes the sample
		void writeCircular(svec2& in);

		// read into the past starting from the latest write to the buffer
		void readCircular(svec2& in, int numSampsAgo);

	};
}

