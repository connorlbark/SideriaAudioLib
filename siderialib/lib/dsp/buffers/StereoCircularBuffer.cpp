#include "StereoCircularBuffer.h"
#include "siderialib.h"
#include "dsp/Math.h"

using namespace siderialib;

int StereoCircularBuffer::flattenIndex(int channel, int sample) const {
    while (sample < 0) {
        sample += _numSamples;
    }

    return _numSamples * channel + sample;
}

void StereoCircularBuffer::incrementCircularSampleIdx() {
	_circularSampleIdx++;
	if (_circularSampleIdx == _numSamples) {
        _circularSampleIdx = 0;
	}
}

void StereoCircularBuffer::initialize(StaticMemoryAllocation &sma, int numSamples) {
    _buf = sma.allocate(numSamples * 2);
    _circularSampleIdx = 0;
    this->_numSamples = numSamples;

    if (_buf) {
        for (int i = 0; i < _numSamples * 2; i++) {
            _buf[i] = 0.f;
        }
    }
}

sfloat StereoCircularBuffer::read(int channel, int sample) const {
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

sfloat StereoCircularBuffer::readCircular(int channel) const {
	return _buf[flattenIndex(channel, _circularSampleIdx - 1)];
}


sfloat StereoCircularBuffer::readCircular(int channel, int numSampsAgo) const {
	return _buf[flattenIndex(channel, mapToNonCircularIndex(numSampsAgo))];

}

void StereoCircularBuffer::writeCircular(sfloat L, sfloat R) {
    _buf[flattenIndex(0, _circularSampleIdx)] = L;
    _buf[flattenIndex(1, _circularSampleIdx)] = R;

    incrementCircularSampleIdx();
}

int StereoCircularBuffer::size() const {
	return _numSamples;
}

int StereoCircularBuffer::numChannels() const {
	return 2;
}

int StereoCircularBuffer::mapToNonCircularIndex(int numSampsAgo) const {
	int finalIdx = _circularSampleIdx - 1 - numSampsAgo;

	return finalIdx;
}

sfloat StereoCircularBuffer::hermiteInterpolation(int channel, int index, double t) const {
    return (sfloat)InterpolateHermite4pt3oX(
            read(channel, index - 1),
            read(channel, index),
            read(channel, index + 1),
            read(channel, index + 2),
            t
    );
}

sfloat StereoCircularBuffer::linearInterpolation(int channel, int index, double t) const {
    sfloat x1 = read(channel, index);
    sfloat x2 = read(channel, index + 1);


    return siderialib::linearInterpolation(x1, x2, t);
}
