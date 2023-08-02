#include "../../../include/dsp/buffers/StereoCircularBuffer.h"
#include "../../../include/siderialib.h"
#include "../../../include/dsp/Math.h"

using namespace siderialib;

int StereoCircularBuffer::flattenIndex(int channel, int sample) {
	return numSamples * channel + sample;
};

void StereoCircularBuffer::incrementCircularSampleIdx() {
	circularSampleIdx++;
	if (circularSampleIdx == numSamples) {
		circularSampleIdx = 0;
	}
};

void StereoCircularBuffer::initialize(int numSamples) {
	buf = (sfloat*)malloc(sizeof(sfloat) * 2 * numSamples);
	this->initialize(buf, numSamples * 2);
}

void StereoCircularBuffer::initialize(sfloat *buf, int length) {
    buf = buf;
    circularSampleIdx = 0;
    this->numSamples = length / 2;

    if (buf) {
        for (int i = 0; i < numSamples * 2; i++) {
            buf[i] = 0.f;
        }
    }
}

sfloat StereoCircularBuffer::read(int channel, int sample) {
	while (sample < 0) {
		sample += numSamples;
	}
	while (sample >= numSamples) {
		sample -= numSamples;
	}
	
	return buf[flattenIndex(channel, sample)];
}

void StereoCircularBuffer::write(sfloat val, int channel, int sample) {

	buf[flattenIndex(channel, sample)] = val;
}

sfloat StereoCircularBuffer::readCircular(int channel) {
	return buf[flattenIndex(channel, circularSampleIdx)];
}


sfloat StereoCircularBuffer::readCircular(int channel, int numSampsAgo) {
	return buf[flattenIndex(channel, mapToNonCircularIndex(numSampsAgo))];

}

void StereoCircularBuffer::writeCircular(sfloat L, sfloat R) {
	buf[flattenIndex(0, circularSampleIdx)] = L;
	buf[flattenIndex(1, circularSampleIdx)] = R;

    incrementCircularSampleIdx();
}

int StereoCircularBuffer::size() {
	return numSamples;
}

int StereoCircularBuffer::numChannels() {
	return 2;
}

int StereoCircularBuffer::mapToNonCircularIndex(int numSampsAgo) {
	int finalIdx = circularSampleIdx - numSampsAgo;

	return finalIdx;
}

//StereoCircularBuffer::~StereoCircularBuffer() {
//    free(this->buf);
//}

sfloat StereoCircularBuffer::hermiteInterpolation(int channel, int index, double t) {
    return (sfloat)InterpolateHermite4pt3oX(
            read(channel, index - 1),
            read(channel, index),
            read(channel, index + 1),
            read(channel, index + 2),
            t
    );
}

sfloat x1;
sfloat x2;
sfloat StereoCircularBuffer::linearInterpolation(int channel, int index, double t) {
    x1 = read(channel, index);
    x2 = read(channel, index + 1);

    double out = x1 + (x2 - x1) * t;
    return (sfloat) out;
}
