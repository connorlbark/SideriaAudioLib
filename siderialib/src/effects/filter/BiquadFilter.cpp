#include "../../../include/effects/filter/BiquadFilter.h"
#include "../../../include/siderialib.h"

using namespace siderialib;


void BiquadFilter::recalcParams() {
	double thetac = TWOPI * _cutoffHz / (double)this->_samplingRate;
	double K = tan(thetac / 2.0);
	double W = K * K;
	double alpha = 1.0 + (K / _Q) + W;

    _b1 = 2.0 * (W - 1.0) / alpha;
    _b2 = (1.0 - (K / _Q) + W) / alpha;

    if (_type == BiquadType::LPF) {
        _a0 = W/alpha;
        _a1 = 2 * W/alpha;
        _a2 = _a0;
    } else if (_type == BiquadType::HPF) {
        _a0 = 1.0 / alpha;
        _a1 = -2.0 / alpha;
        _a2 = _a0;
    }
}

void BiquadFilter::initialize(sfloat samplingRate, BiquadType type, sfloat cutoffHz, sfloat Q) {
	this->_samplingRate = samplingRate;
	this->_type = type;
	
	this->_cutoffHz = cutoffHz;
	this->_Q = Q;

	recalcParams();
}

void BiquadFilter::setCutoff(sfloat cutoffHz) {
	this->_cutoffHz = cutoffHz;
	this->recalcParams();
}

void BiquadFilter::setQ(sfloat Q) {
	this->_Q = Q;
	this->recalcParams();
}

void BiquadFilter::setParams(sfloat cutoff, sfloat Q, sfloat dB) {
    this->_cutoffHz = cutoff;
    this->_Q =Q;
    setGain(dB);
    this->recalcParams();
}

sfloat BiquadFilter::tick(sfloat x0) {

    _out = x0 * _a0 + _x1 * _a1 * _x2 * _a2 -  _y1 * _b1 - _y2 * _b2;

    _x2 = _x1;
    _x1 = x0;

    _y2 = _y1;
    _y1 = _out;

    return (sfloat)_out * _linGain;
}