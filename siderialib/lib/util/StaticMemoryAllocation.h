#pragma once

#include "siderialib.h"

namespace siderialib {

    class StaticMemoryAllocation {
    private:
        int _size = 0;
        int _index = 0;
        sfloat *_data = nullptr;

    public:
        StaticMemoryAllocation() = default;

        void initialize(int size);
        void initialize(sfloat *data, int size);

        // will exit program if OOM
        sfloat *allocate(int size);
        double *allocateDouble(int size);

        // clear memory and refresh for reuse
        void clear();
        // free memory (no longer usable, requires reinitialization)
        void freeAllocation();
    };

}