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

		inline int flattenIndex(int channel, int sample) const;

		void incrementCircularSampleIdx();
	public:
        ~StereoCircularBuffer() {
            delete _buf;
        }

        StereoCircularBuffer(StereoCircularBuffer const &fp) = delete;
        StereoCircularBuffer const & operator=(StereoCircularBuffer const &fp) = delete;

        StereoCircularBuffer& operator=(StereoCircularBuffer&& other) noexcept
        {
            if (this != &other) {
                if (this->_buf != nullptr) {
                    free(this->_buf);
                }

                this->_buf = other._buf;
                this->_numSamples = other._numSamples;
                this->_circularSampleIdx = other._circularSampleIdx;

                other._buf = nullptr;
                other._numSamples = 0;
                other._circularSampleIdx = 0;
            }

            return *this;
        }

		int mapToNonCircularIndex(int sample) const;

		// initializes the buffer with two channels and the specified number of samples
        void initialize(int numSamples);
        // takes in and takes ownership of *buf; when the destructor of this class is called, it will free this buffer.
        void initialize(sfloat *buf, int len);

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

