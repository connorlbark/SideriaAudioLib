#pragma once

#include "../Effect.h"

namespace siderialib {
	class IIRFilter : public Effect {
	protected:
		double* a;
		double* x;
		int circAIdx = 0;
		int aLen;
		double* b;
		double* y;
		int circBIdx = 0;
		int bLen;

		
		int mapAIdx(int idx) {
			if (idx < 0) {
				idx += aLen;
			}
			else if (idx >= aLen) {
				idx -= aLen;
			}
			return idx;
		}

		int mapBIdx(int idx) {
			if (idx < 0) {
				idx += bLen;
			}
			else if (idx >= bLen) {
				idx -= bLen;
			}
			return idx;
		}

		virtual void initializeParams() = 0;
	public:

		void tick(Buffer& buf) override final {
			return this->tick(buf, buf);
		}

		void tick(Buffer& in, Buffer& out) override final {
			for (int i = 0; i < in.size(); i++) {
				out.write(this->tick(in.read(0, i)), 0, i);
			}
		}

		sfloat tick(sfloat in) {
			double out = a[0] * in;

			int finalIdx = 0;
			for (int aIdx = 1; aIdx < aLen; aIdx++) {
				finalIdx = mapAIdx(-aIdx);
				out += x[finalIdx] * a[aIdx];
			}

			for (int bIdx = 1; bIdx < bLen; bIdx++) {
				finalIdx = mapBIdx(-bIdx);
				out += y[finalIdx] * b[bIdx];
			}

			x[circAIdx] = in;
			y[circBIdx] = out;

			circAIdx = ++circAIdx % aLen;
			circBIdx = ++circBIdx % bLen;

			return (sfloat)out;
		}
	};
}
