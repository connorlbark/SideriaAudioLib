#pragma once

#include "../siderialib.h"
#include "../dsp/Types.h"

namespace siderialib {
    class SmoothedParameter
    {
    private:
        sfloat _val = 0.0;

        sfloat _target = 0.0;

        sfloat _a = 0;
        sfloat _b = 0;
    public:
        void initialize(sfloat smoothingTimeMs, sfloat sampleRate);

        sfloat tick();
        inline sfloat value() const { return this->_val; }
        void setTarget(sfloat target) { this->_target = target; }
    };
}
