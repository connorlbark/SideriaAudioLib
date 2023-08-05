#pragma once

#include "../../siderialib.h"

namespace siderialib {
	// circular buffer with two channels for simplified
	// operation in the most common case, stereo
	class StereoCircularBuffer {
	private:

		sfloat* _buf;
		int _numSamples;

		int _circularSampleIdx;

		inline int flattenIndex(int channel, int sample);

		void incrementCircularSampleIdx();
	public:
        ~StereoCircularBuffer() {
            free(this->_buf);
        }

		int mapToNonCircularIndex(int sample);

		// initializes the buffer with two channels and the specified number of samples
        void initialize(int numSamples);
        // takes in and takes ownership of *buf; when the destructor of this class is called, it will free this buffer.
        void initialize(sfloat *buf, int len);

		sfloat read(int channel, int sample);

		void write(sfloat val, int channel, int sample);

		int size();

		int numChannels();

		// fills out "in" with the most recently written samples
		sfloat readCircular(int channel);

		// increments circular pointer and writes the sample
		void writeCircular(sfloat L, sfloat R);

		// read into the past starting from the latest write to the buffer
		sfloat readCircular(int channel, int numSampsAgo);

        sfloat hermiteInterpolation(int channel, int index, double t);
        sfloat linearInterpolation(int channel, int index, double t);
    };
}

