#pragma once

#include "../../siderialib.h"

namespace siderialib {
	enum BiquadType {
		LPF = 0,
		HPF =1
	};
	
	class BiquadFilter  {
	private:
        double* _a;
        double* _x;
        int _circAIdx = 0;
        int _aLen;
        double* _b;
        double* _y;
        int _circBIdx = 0;
        int _bLen;

        float _linGain = 1.0;


        int mapAIdx(int idx) {
            idx += _circAIdx;
            if (idx < 0) {
                idx += _aLen;
            }
            else if (idx >= _aLen) {
                idx -= _aLen;
            }
            return idx;
        }

        int mapBIdx(int idx) {
            idx += _circBIdx;
            if (idx < 0) {
                idx += _bLen;
            }
            else if (idx >= _bLen) {
                idx -= _bLen;
            }
            return idx;
        }

		BiquadType _type = BiquadType::LPF;
		sfloat _samplingRate;
	
		sfloat _Q;
		sfloat _cutoffHz;

		void initializeParams();
		void recalcParams();
	public:
        ~BiquadFilter() {
            free(this->_a);
            free(this->_b);
            free(this->_x);
            free(this->_y);
        }

		void initialize(sfloat samplingRate, BiquadType type, sfloat cutoffHz, sfloat Q);

		void setCutoff(sfloat cutoffHz);
		sfloat getCutoff() { return this->_cutoffHz; }
		void setQ(sfloat Q);
		sfloat getQ() { return this->_Q; }

        void setParams(sfloat cutoff, sfloat Q, sfloat dB);

        void setGain(sfloat dB) {
            this->_linGain = std::pow(10.f, dB / 20.f);
        }

        sfloat tick(sfloat in) {
            _x[_circAIdx] = in;
            _circAIdx = (_circAIdx+1) % _aLen;

            double out = 0.0;

            int finalIdx;
            for (int aIdx = 0; aIdx < _aLen; aIdx++) {
                finalIdx = mapAIdx(-aIdx);
                out += _x[finalIdx] * _a[aIdx];
            }

            for (int bIdx = 0; bIdx < _bLen; bIdx++) {
                finalIdx = mapBIdx(-bIdx - 1);
                out -= _y[finalIdx] * _b[bIdx];
            }

            _y[_circBIdx] = out;
            _circBIdx = (_circBIdx+1) % _bLen;

            return (sfloat)out * _linGain;
        }
	};
}