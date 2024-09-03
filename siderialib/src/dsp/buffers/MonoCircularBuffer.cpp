#include "../../../include/dsp/buffers/MonoCircularBuffer.h"
#include "../../../include/siderialib.h"
#include "../../../include/dsp/Math.h"

using namespace siderialib;

int MonoCircularBuffer::flattenIndex(int sample) const {
    while (sample < 0) {
        sample += _numSamples;
    }

    return sample;
}

void MonoCircularBuffer::incrementCircularSampleIdx() {
	_circularSampleIdx++;
	if (_circularSampleIdx == _numSamples) {
        _circularSampleIdx = 0;
	}
}

void MonoCircularBuffer::initialize(int numSamples) {
    _buf = (sfloat*)malloc(sizeof(sfloat) * numSamples);
	this->initialize(_buf, numSamples);
}

void MonoCircularBuffer::initialize(sfloat *buf, int length) {
    this->_buf = buf;
    _circularSampleIdx = 0;
    this->_numSamples = length / 2;

    if (buf) {
        for (int i = 0; i < _numSamples * 2; i++) {
            buf[i] = 0.f;
        }
    }
}

sfloat MonoCircularBuffer::read(int sample) const {
	while (sample < 0) {
		sample += _numSamples;
	}
	while (sample >= _numSamples) {
		sample -= _numSamples;
	}
	
	return _buf[flattenIndex(sample)];
}

void MonoCircularBuffer::write(sfloat val, int sample) {

    _buf[flattenIndex(sample)] = val;
}

sfloat MonoCircularBuffer::readCircular() const {
	return _buf[flattenIndex(_circularSampleIdx - 1)];
}


sfloat MonoCircularBuffer::readCircular(int numSampsAgo) const {
	return _buf[flattenIndex(mapToNonCircularIndex(numSampsAgo))];

}

void MonoCircularBuffer::writeCircular(sfloat val) {
    _buf[flattenIndex(_circularSampleIdx)] = val;

    incrementCircularSampleIdx();
}

int MonoCircularBuffer::size() const {
	return _numSamples;
}

int MonoCircularBuffer::numChannels() const {
	return 2;
}

int MonoCircularBuffer::mapToNonCircularIndex(int numSampsAgo) const {
	int finalIdx = _circularSampleIdx - 1 - numSampsAgo;

	return finalIdx;
}

sfloat MonoCircularBuffer::hermiteInterpolation(int index, double t) const {
    return (sfloat)InterpolateHermite4pt3oX(
            read(index - 1),
            read(index),
            read(index + 1),
            read(index + 2),
            t
    );
}

sfloat MonoCircularBuffer::linearInterpolation(int index, double t) const {
    sfloat x1 = read(index);
    sfloat x2 = read(index + 1);

    double out = x1 + (x2 - x1) * t;
    return (sfloat) out;
}
