#pragma once

#include "../../siderialib.h"

namespace siderialib {
	enum class BiquadType {
		LPF = 0,
		HPF =1
	};
	
	class BiquadFilter  {
	private:
        double _a0 = 0.f;
        double _a1 = 0.f;
        double _a2 = 0.f;

        double _b1 = 0.f;
        double _b2 = 0.f;

        double _x1 = 0.f;
        double _x2 = 0.f;

        double _y1 = 0.f;
        double _y2 = 0.f;

        double _out = 0.f;

        double _linGain = 1.0;


		BiquadType _type = BiquadType::LPF;
		sfloat _samplingRate;
	
		sfloat _Q;
		sfloat _cutoffHz;

		void recalcParams();
	public:
        ~BiquadFilter() = default;

		void initialize(sfloat samplingRate, BiquadType type, sfloat cutoffHz, sfloat Q);

		void setCutoff(sfloat cutoffHz);
		inline sfloat getCutoff() const { return this->_cutoffHz; }
		void setQ(sfloat Q);
		inline sfloat getQ() const { return this->_Q; }

        void setParams(sfloat cutoff, sfloat Q, sfloat dB);

        void setGain(sfloat dB) {
            this->_linGain = std::pow(10.f, dB / 20.f);
        }

        sfloat tick(sfloat in);
	};
}