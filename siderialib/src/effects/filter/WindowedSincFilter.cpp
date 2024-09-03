#include "effects/filter/WindowedSincFilter.h"

using namespace siderialib;

double sinc (double x) {
    if (x == 0.0) {

        return 1.0;

    }

    return sin(x) / x;

}


// see : https://www.dspguide.com/ch16/2.htm
void windowedSinc(double *fir, int firLength, sfloat cutoff, sfloat sampleRate) {

    double fc = (cutoff/sampleRate);
    fc = 0.015;

    for (int i = 0; i < firLength; i++) {
        int offset = i - (firLength-1)/2;

        if (offset == 0) {
            fir[i] = 2.0 * PI * fc;
        } else {
            fir[i] = (
//                    sin(2.0 * PI * fc * (double)offset) / ((double)offset * PI)
                (sin(2.0 * PI * fc * (double) offset) / (double)offset)
                * (0.42 - 0.5 * cos((2 * PI * i)/firLength) + 0.08 * cos((4 * PI * i)/firLength))
            );
        }
    }

    double sum = 0.0;

    for (int i = 0; i < firLength; i++) {
        sum += fir[i];
    }
    for (int i = 0; i < firLength; i++) {
        fir[i] /= sum;
    }
}

void hammingWindow(double *fir, int firLength) {

    for (int i = 0; i < firLength; i++ ) {
        int offset = i - (firLength-1)/2;

        fir[i] *= 0.54 + 0.46 * cos(((2 * PI * (sfloat)offset) / (sfloat)firLength));
    }
}

void siderialib::WindowedSincFilter::initialize(int _firLength, sfloat cutoff, sfloat _sampleRate) {

    this->sampleRate = _sampleRate;
    this->firLength = _firLength;

    this->fir = (double*)malloc(sizeof(double) * firLength);
    this->hist.initialize(_firLength);

    windowedSinc(fir, firLength, cutoff, sampleRate);
    //hammingWindow(fir, firLength);

}

void siderialib::WindowedSincFilter::initialize(double *_fir, int _firLength) {
    fir = _fir;
    firLength = _firLength;
}

double *WindowedSincFilter::getFir() {
    return fir;
}

int WindowedSincFilter::getFirLength() const {
    return firLength;
}

sfloat WindowedSincFilter::tick(siderialib::sfloat in) {
    hist.writeCircular(in);

    double out = 0.0;
    for (int i = 0; i < firLength; i ++ ) {
        out += (double)hist.readCircular(i) * fir[i];
    }

    return (sfloat)out;
};

WindowedSincFilter::~WindowedSincFilter() {
    free(fir);
}
