#pragma once

#include "dsp/Buffer.h"

namespace siderialib {
	class Effect {
	public:
		// apply effect and modify buffer in-place
		virtual void tick(Buffer& buf) = 0;

		// apply effect from one audio buffer to another
		virtual void tick(Buffer& in, Buffer& out) = 0;
	};
}