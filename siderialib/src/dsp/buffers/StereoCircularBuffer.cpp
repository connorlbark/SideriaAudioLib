#include "../../../include/dsp/buffers/StereoCircularBuffer.h"
#include "../../../include/siderialib.h"
#include "../../../include/dsp/Math.h"

using namespace siderialib;

int StereoCircularBuffer::flattenIndex(int channel, int sample) {
	return _numSamples * channel + sample;
}

void StereoCircularBuffer::incrementCircularSampleIdx() {
	_circularSampleIdx++;
	if (_circularSampleIdx == _numSamples) {
        _circularSampleIdx = 0;
	}
}

void StereoCircularBuffer::initialize(int numSamples) {
    _buf = (sfloat*)malloc(sizeof(sfloat) * 2 * numSamples);
	this->initialize(_buf, numSamples * 2);
}

void StereoCircularBuffer::initialize(sfloat *buf, int length) {
    this->_buf = buf;
    _circularSampleIdx = 0;
    this->_numSamples = length / 2;

    if (buf) {
        for (int i = 0; i < _numSamples * 2; i++) {
            buf[i] = 0.f;
        }
    }
}

sfloat StereoCircularBuffer::read(int channel, int sample) {
	while (sample < 0) {
		sample += _numSamples;
	}
	while (sample >= _numSamples) {
		sample -= _numSamples;
	}
	
	return _buf[flattenIndex(channel, sample)];
}

void StereoCircularBuffer::write(sfloat val, int channel, int sample) {

    _buf[flattenIndex(channel, sample)] = val;
}

sfloat StereoCircularBuffer::readCircular(int channel) {
	return _buf[flattenIndex(channel, _circularSampleIdx)];
}


sfloat StereoCircularBuffer::readCircular(int channel, int numSampsAgo) {
	return _buf[flattenIndex(channel, mapToNonCircularIndex(numSampsAgo))];

}

void StereoCircularBuffer::writeCircular(sfloat L, sfloat R) {
    _buf[flattenIndex(0, _circularSampleIdx)] = L;
    _buf[flattenIndex(1, _circularSampleIdx)] = R;

    incrementCircularSampleIdx();
}

int StereoCircularBuffer::size() {
	return _numSamples;
}

int StereoCircularBuffer::numChannels() {
	return 2;
}

int StereoCircularBuffer::mapToNonCircularIndex(int numSampsAgo) {
	int finalIdx = _circularSampleIdx - numSampsAgo;

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
