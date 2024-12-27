#include <gtest/gtest.h>
#include "../../lib/util/StaticMemoryAllocation.h"

using namespace siderialib;

TEST(StaticMemoryAllocation, Allocate) {
    StaticMemoryAllocation sma;

    sma.initialize(10);

    sfloat *buf1 = sma.allocate(5);
    sfloat *buf2 = sma.allocate(5);

    buf1[0] = 1.0;
    buf1[1] = 2.0;
    buf1[2] = 3.0;
    buf1[3] = 4.0;
    buf1[4] = 5.0;

    buf2[0] = 6.0;
    buf2[1] = 7.0;
    buf2[2] = 8.0;
    buf2[3] = 9.0;
    buf2[4] = 10.0;


    ASSERT_EQ(1.0, buf1[0]);
    ASSERT_EQ(2.0, buf1[1]);
    ASSERT_EQ(3.0, buf1[2]);
    ASSERT_EQ(4.0, buf1[3]);
    ASSERT_EQ(5.0, buf1[4]);

    ASSERT_EQ(6.0, buf2[0]);
    ASSERT_EQ(7.0, buf2[1]);
    ASSERT_EQ(8.0, buf2[2]);
    ASSERT_EQ(9.0, buf2[3]);
    ASSERT_EQ(10.0, buf2[4]);
}

TEST(StaticMemoryAllocation, AllocateDouble) {
    StaticMemoryAllocation sma;

    sma.initialize(15);

    double *buf1 = sma.allocateDouble(5);
    sfloat *buf2 = sma.allocate(5);

    buf1[0] = 1.0;
    buf1[1] = 2.0;
    buf1[2] = 3.0;
    buf1[3] = 4.0;
    buf1[4] = 5.0;

    buf2[0] = 6.0;
    buf2[1] = 7.0;
    buf2[2] = 8.0;
    buf2[3] = 9.0;
    buf2[4] = 10.0;

    ASSERT_EQ(1.0, buf1[0]);
    ASSERT_EQ(2.0, buf1[1]);
    ASSERT_EQ(3.0, buf1[2]);
    ASSERT_EQ(4.0, buf1[3]);
    ASSERT_EQ(5.0, buf1[4]);

    ASSERT_EQ(6.0, buf2[0]);
    ASSERT_EQ(7.0, buf2[1]);
    ASSERT_EQ(8.0, buf2[2]);
    ASSERT_EQ(9.0, buf2[3]);
    ASSERT_EQ(10.0, buf2[4]);
}