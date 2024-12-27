#include "StaticMemoryAllocation.h"


using namespace siderialib;

sfloat *StaticMemoryAllocation::allocate(int size) {
    sfloat *ptr = _data + _index;
    _index += size;

    printf("StaticMemoryAllocation: allocated %d bytes, %d left\n", size, _size - _index);
    if (_index > _size) {
        printf("StaticMemoryAllocation: out of memory\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

double *StaticMemoryAllocation::allocateDouble(int size) {
    sfloat * allocation = this->allocate(size * (sizeof(double ) / sizeof(sfloat)));

    return (double *) allocation;
}

void StaticMemoryAllocation::clear() {
    if (_data == nullptr) {
        return;
    }

    _index = 0;

    for (int i = 0; i < _size; i++) {
        _data[i] = 0.0f;
    }
}

void StaticMemoryAllocation::freeAllocation()  {
    if (_data != nullptr) {
        free(_data);
    }
}

void StaticMemoryAllocation::initialize(int size) {
    _size = size;
    _data = (sfloat*)malloc(sizeof(sfloat) * size);
    clear();
}

void StaticMemoryAllocation::initialize(siderialib::sfloat *data, int size)  {
    _size = size;
    _data = data;
    clear();
}