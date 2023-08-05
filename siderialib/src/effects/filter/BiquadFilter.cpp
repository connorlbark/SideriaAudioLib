#include "../../../include/effects/filter/BiquadFilter.h"
#include "../../../include/siderialib.h"

using namespace siderialib;


void BiquadFilter::initializeParams() {
	this->_aLen = 3;
	this->_a = (double*)malloc(sizeof(double) * _aLen);
	this->_x = (double*)malloc(sizeof(double) * _aLen);
	for (int i = 0; i < _aLen; i++) {
        _x[i] = 0.0;
	}

	this->_bLen = 2;
	this->_b = (double*)malloc(sizeof(double) * _bLen);
	this->_y = (double*)malloc(sizeof(double) * _bLen);
	for (int i = 0; i < _bLen; i++) {
        _y[i] = 0.0;
	}

	recalcParams();
}

void BiquadFilter::recalcParams() {
	double thetac = TWOPI * _cutoffHz / (double)this->_samplingRate;
	double K = tan(thetac / 2.0);
	double W = K * K;
	double alpha = 1.0 + (K / _Q) + W;

    _b[0] = 2.0 * (W - 1.0) / alpha;
    _b[1] = (1.0 - (K / _Q) + W) / alpha;

    if (_type == BiquadType::LPF) {
        _a[0] = W/alpha;
        _a[1] = 2 * W/alpha;
        _a[2] = _a[0];
    } else if (_type == BiquadType::HPF) {
        _a[0] = 1.0 / alpha;
        _a[1] = -2.0 / alpha;
        _a[2] = _a[0];
    }
}

void BiquadFilter::initialize(sfloat samplingRate, BiquadType type, sfloat cutoffHz, sfloat Q) {
	this->_samplingRate = samplingRate;
	this->_type = type;
	
	this->_cutoffHz = cutoffHz;
	this->_Q = Q;

	initializeParams();
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