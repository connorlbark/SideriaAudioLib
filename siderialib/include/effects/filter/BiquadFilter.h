#pragma once

#include "../../siderialib.h"

namespace siderialib {
	enum class BiquadType {
		LPF = 0,
		HPF =1
	};
	
	class BiquadFilter  {
	private:
        double _a0;
        double _a1;
        double _a2;

        double _b1;
        double _b2;

        double _x1;
        double _x2;

        double _y1;
        double _y2;

        double _out;

        float _linGain = 1.0;


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