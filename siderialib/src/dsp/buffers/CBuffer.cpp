#include "../../../include/dsp/buffers/CBuffer.h"
#include "../../../include/siderialib.h"

using namespace siderialib;

int CBuffer::flattenIndex(int channel, int sample) {
	return _numSamples * channel + sample;
}

void CBuffer::initialize(int numChannels, int numSamples) {
	buf = (sfloat*)malloc(sizeof(sfloat) * numChannels * numSamples);
}

sfloat CBuffer::read(int channel, int sample) {

#if SLIB_DEBUG
	assert(sample < _numSamples);
	assert(channel < _numChannels);
	assert(sample >= 0);
	assert(channel >= 0);
#endif


	return buf[flattenIndex(channel, sample)];
}

void CBuffer::write(sfloat val, int channel, int sample) {

#if SLIB_DEBUG
	assert(sample < _numSamples);
	assert(channel < _numChannels);
	assert(sample >= 0);
	assert(channel >= 0);
#endif

	buf[flattenIndex(channel, sample)] = val;
}

int CBuffer::size() {
	return _numSamples;
}

int CBuffer::numChannels() {
	return _numChannels;
}

CBuffer::~CBuffer() {
    free(this->buf);
}
