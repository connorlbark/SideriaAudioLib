#pragma once

#include "dsp/Types.h"

namespace siderialib {
    class Decimate {
    private:

        int _downsampleFactor = 1;

        sfloat _value = 0.0;
        int _counter = 0;

    public:
        Decimate() = default;

        void initialize();

        sfloat tick(sfloat in);

        void setDownsampleFactor(int factor);
        int getDownsampleFactor() const;
    };
}