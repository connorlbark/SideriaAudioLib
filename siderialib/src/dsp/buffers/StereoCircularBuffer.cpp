#include "../../../include/dsp/buffers/StereoCircularBuffer.h"
#if SLIB_DEBUG
#include <stdexcept>
#include <string>
#endif

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
	circularSampleIdx = 0;
	this->numSamples = numSamples;

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

#if SLIB_DEBUG
	if (sample >= numSamples || sample < 0) {
		throw new std::domain_error("Samples should range from 0 to " + std::to_string(numSamples) + ", instead given: " + std::to_string(sample));
	}

	if (channel >= numSamples || channel < 0) {
		throw new std::domain_error("Channels should range from 0 to " + std::to_string(numChannels()) + ", instead given: " + std::to_string(channel));
	}
#endif

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