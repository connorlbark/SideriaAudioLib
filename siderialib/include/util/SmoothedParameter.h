#pragma once

#include "../siderialib.h"
#include "../dsp/Types.h"

namespace siderialib {
    class SmoothedParameter
    {
    private:
        float _val = 0.0;

        float _target = 0.0;

        float _a = 0;
        float _b = 0;
    public:
        void initialize(sfloat smoothingTimeMs, sfloat sampleRate);

        void process();
        inline float value() const { return this->_val; }
        void setTarget(sfloat target) { this->_target = target; }
    };
}
