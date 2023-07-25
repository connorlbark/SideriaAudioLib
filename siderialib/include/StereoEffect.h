
#include "Effect.h"

namespace siderialib {
	class StereoEffect : public Effect {
	public:
		virtual void tick(sfloat L, sfloat R) = 0;
		virtual sfloat lastOutL() = 0;
		virtual sfloat lastOutR() = 0;
	};
}