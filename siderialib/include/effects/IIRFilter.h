#pragma once

#include "../Effect.h"
#include "../siderialib.h"

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

		virtual void initializeParams() = 0;
	public:
        ~IIRFilter() {
            free(this->a);
            free(this->b);
            free(this->x);
            free(this->y);
        }

		void tick(Buffer& buf) override final {
			return this->tick(buf, buf);
		}

		void tick(Buffer& in, Buffer& out) override final {
			for (int i = 0; i < in.size(); i++) {
				out.write(this->tick(in.read(0, i)), 0, i);
			}
		}

        void setGain(sfloat dB) {
            this->linGain = std::pow(10.f, dB / 20.f);
        }

		sfloat tick(sfloat in) {
            x[circAIdx] = in;
            circAIdx = ++circAIdx % aLen;

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
			circBIdx = ++circBIdx % bLen;

			return (sfloat)out * linGain;
		}
	};
}
