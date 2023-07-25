#include "../../../include/dsp/buffers/StereoCircularBuffer.h"

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
}

sfloat StereoCircularBuffer::read(int channel, int sample) {

#if SLIB_DEBUG
	assert(sample < numSamples);
	assert(channel < 2);
	assert(sample >= 0);
	assert(channel >= 0);
#endif


	return buf[flattenIndex(channel, sample)];
}

void StereoCircularBuffer::write(sfloat val, int channel, int sample) {

#if SLIB_DEBUG
	assert(sample < numSamples);
	assert(channel < 2);
	assert(sample >= 0);
	assert(channel >= 0);
#endif

	buf[flattenIndex(channel, sample)] = val;
}

void StereoCircularBuffer::readCircular(svec2 &in) {
	in.x = buf[flattenIndex(0, circularSampleIdx)];
	in.y = buf[flattenIndex(1, circularSampleIdx)];
}


void StereoCircularBuffer::readCircular(svec2& in, int numSampsAgo) {
	int finalIdx = circularSampleIdx - numSampsAgo;

	while (finalIdx < 0) {
		finalIdx += numSamples;
	}

	in.x = buf[flattenIndex(0, finalIdx)];
	in.y = buf[flattenIndex(1, finalIdx)];

}

void StereoCircularBuffer::writeCircular(svec2& in) {
	incrementCircularSampleIdx();

	buf[flattenIndex(0, circularSampleIdx)] = in.x;
	buf[flattenIndex(1, circularSampleIdx)] = in.y;

}

int StereoCircularBuffer::size() {
	return numSamples;
}

int StereoCircularBuffer::numChannels() {
	return 2;
}