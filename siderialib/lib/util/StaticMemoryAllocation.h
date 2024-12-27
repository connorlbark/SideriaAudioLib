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

        void initialize(int size) {
            _size = size;
            _data = (sfloat*)malloc(sizeof(sfloat) * size);
            clear();
        }

        void initialize(sfloat *data, int size) {
            _size = size;
            _data = data;
            clear();
        }

        sfloat *allocate(int size) {
            printf("size: %d, _size: %d, _index: %d\n", size, _size, _index);
            sfloat *ptr = _data + _index;
            _index += size;
            printf("index: %d\n", _index);

            printf("StaticMemoryAllocation: allocated %d bytes, %d left\n", size, _size - _index);
            if (_index > _size) {
                printf("StaticMemoryAllocation: out of memory\n");
                exit(EXIT_FAILURE);
            }
            return ptr;
        }


        double *allocateDouble(int size) {
            sfloat *ptr = (sfloat*)_data + _index;
            _index += size * (sizeof(double) / sizeof(sfloat));
            return (double*)ptr;
        }

        void clear() {
            if (_data == nullptr) {
                return;
            }

            _index = 0;

            for (int i = 0; i < _size; i++) {
                _data[i] = 0.0f;
            }
        }

        void freeAllocation() {
            if (_data != nullptr) {
                free(_data);
            }
        }
    };

}