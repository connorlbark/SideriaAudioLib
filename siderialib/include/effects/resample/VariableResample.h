#pragma once


#include "Decimate.h"
#include "Upsample.h"
#include "dsp/Math.h"

namespace siderialib {

    const int MAX_RESAMPLE_DENOM = 10;
    class VariableResample {
    private:
        Decimate _decimate;
        Upsample _upsample;

    public:
        VariableResample() = default;

        void initialize() {
            _upsample.initialize(MAX_RESAMPLE_DENOM-1);
            _decimate.initialize();
        }

        void initialize(sfloat *upsampleBuf, int upsampleBufLen) {
            _upsample.initialize(upsampleBuf, upsampleBufLen);
            _decimate.initialize();
        }

        void setResampleFactor(sfloat factor) {
            Fraction frac = floatToFraction(factor, MAX_RESAMPLE_DENOM);

            setResampleFactor(frac.numerator, frac.denominator);
        }

        void setResampleFactor(int upsampleFactor, int downsampleFactor) {
            _upsample.setUpsampleFactor(upsampleFactor);
            _decimate.setDownsampleFactor(downsampleFactor);
        }

        int getDecimateFactor() {
            return _decimate.getDownsampleFactor();
        }

        int getUpsampleFactor() {
            return _upsample.getUpsampleFactor();
        }



        sfloat tick(sfloat in) {

            // upsample then downsample
            _upsample.tick(in);


            sfloat out;
            for (int i = 0; i < _upsample.getOutBufferSize(); i++) {
                out = _decimate.tick(_upsample.readOutputBuffer(i));
            }

            return out;
        }
    };
}