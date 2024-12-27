#pragma once

#include "../../siderialib.h"

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

        ~MonoCircularBuffer() {
            delete _buf;
            _numSamples = 0;
            _circularSampleIdx = 0;
        }

		int mapToNonCircularIndex(int sample) const;

		// initializes the buffer with two channels and the specified number of samples
        void initialize(int numSamples);
        // takes in and takes ownership of *buf; when the destructor of this class is called, it will free this buffer.
        void initialize(sfloat *buf, int len);

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

