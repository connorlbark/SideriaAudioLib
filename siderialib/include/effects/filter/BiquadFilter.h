#pragma once

#include "../IIRFilter.h"

namespace siderialib {
	enum BiquadType {
		LPF = 0,
		HPF =1
	};
	
	class BiquadFilter : public IIRFilter {
	private:
		BiquadType type = BiquadType::LPF;
		sfloat samplingRate;
	
		sfloat Q;
		sfloat cutoffHz;
	protected:
		void initializeParams() override final;
		void recalcParams();
	public:
		void initialize(sfloat samplingRate, BiquadType type, sfloat cutoffHz, sfloat Q);

		void setCutoff(sfloat cutoffHz);
		sfloat getCutoff() { return this->cutoffHz; }
		void setQ(sfloat Q);
		sfloat getQ() { return this->Q; }

        void setParams(sfloat cutoff, sfloat Q, sfloat dB);
	};
}