#include "../../../include/effects/filter/BiquadFilter.h"
#include "../../../include/siderialib.h"

using namespace siderialib;


void BiquadFilter::initializeParams() {
	this->aLen = 3;
	this->a = (double*)malloc(sizeof(double) * aLen);
	this->x = (double*)malloc(sizeof(double) * aLen);
	for (int i = 0; i < aLen; i++) {
		x[i] = 0.0;
	}

	this->bLen = 2;
	this->b = (double*)malloc(sizeof(double) * bLen);
	this->y = (double*)malloc(sizeof(double) * bLen);
	for (int i = 0; i < bLen; i++) {
		y[i] = 0.0;
	}

	recalcParams();
}

void BiquadFilter::recalcParams() {
	double thetac = TWOPI * cutoffHz / (double)this->samplingRate;
	double K = tan(thetac / 2.0);
	double W = K * K;
	double alpha = 1.0 + (K / Q) + W;
	
	b[0] = 2.0 * (W - 1.0) / alpha;
	b[1] = (1.0 - (K / Q) + W) / alpha;

    if (type == BiquadType::LPF) {
        a[0] = W/alpha;
        a[1] = 2 * W/alpha;
        a[2] = a[0];
    } else if (type == BiquadType::HPF) {
        a[0] = 1.0 / alpha;
        a[1] = -2.0 / alpha;
        a[2] = a[0];
    }
}

void BiquadFilter::initialize(sfloat samplingRate, BiquadType type, sfloat cutoffHz, sfloat Q) {
	this->samplingRate = samplingRate;
	this->type = type;
	
	this->cutoffHz = cutoffHz;
	this->Q = Q;

	initializeParams();
}

void BiquadFilter::setCutoff(sfloat cutoffHz) {
	this->cutoffHz = cutoffHz;
	this->recalcParams();
}

void BiquadFilter::setQ(sfloat Q) {
	this->Q = Q;
	this->recalcParams();
}

