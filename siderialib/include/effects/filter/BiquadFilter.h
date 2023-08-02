#pragma once

#include "../../siderialib.h"

namespace siderialib {
	enum BiquadType {
		LPF = 0,
		HPF =1
	};
	
	class BiquadFilter  {
	private:
        double* a;
        double* x;
        int circAIdx = 0;
        int aLen;
        double* b;
        double* y;
        int circBIdx = 0;
        int bLen;

        float linGain = 1.0;


        int mapAIdx(int idx) {
            idx += circAIdx;
            if (idx < 0) {
                idx += aLen;
            }
            else if (idx >= aLen) {
                idx -= aLen;
            }
            return idx;
        }

        int mapBIdx(int idx) {
            idx += circBIdx;
            if (idx < 0) {
                idx += bLen;
            }
            else if (idx >= bLen) {
                idx -= bLen;
            }
            return idx;
        }

		BiquadType type = BiquadType::LPF;
		sfloat samplingRate;
	
		sfloat Q;
		sfloat cutoffHz;

		void initializeParams();
		void recalcParams();
	public:
        ~BiquadFilter() {
            free(this->a);
            free(this->b);
            free(this->x);
            free(this->y);
        }

		void initialize(sfloat samplingRate, BiquadType type, sfloat cutoffHz, sfloat Q);

		void setCutoff(sfloat cutoffHz);
		sfloat getCutoff() { return this->cutoffHz; }
		void setQ(sfloat Q);
		sfloat getQ() { return this->Q; }

        void setParams(sfloat cutoff, sfloat Q, sfloat dB);

        void setGain(sfloat dB) {
            this->linGain = std::pow(10.f, dB / 20.f);
        }

        sfloat tick(sfloat in) {
            x[circAIdx] = in;
            circAIdx = (circAIdx+1) % aLen;

            double out = 0.0;

            int finalIdx;
            for (int aIdx = 0; aIdx < aLen; aIdx++) {
                finalIdx = mapAIdx(-aIdx);
                out += x[finalIdx] * a[aIdx];
            }

            for (int bIdx = 0; bIdx < bLen; bIdx++) {
                finalIdx = mapBIdx(-bIdx - 1);
                out -= y[finalIdx] * b[bIdx];
            }

            y[circBIdx] = out;
            circBIdx = (circBIdx+1) % bLen;

            return (sfloat)out * linGain;
        }
	};
}