#include <gtest/gtest.h>
#include "../../../../include/effects/resample/Upsample.h"


TEST(Upsample, Upsample) {
    siderialib::Upsample upsample;
    upsample.initialize(10);

    upsample.setUpsampleFactor(2);
    ASSERT_FLOAT_EQ(2, upsample.getOutBufferSize());

    upsample.tick(1.0);
    upsample.tick(2.0);

    ASSERT_FLOAT_EQ(1.0, upsample.readOutputBuffer(0));
    ASSERT_FLOAT_EQ(1.5, upsample.readOutputBuffer(1));

    upsample.tick(2.0);

    ASSERT_FLOAT_EQ(2.0, upsample.readOutputBuffer(0));
    ASSERT_FLOAT_EQ(2.0, upsample.readOutputBuffer(1));

    upsample.tick(1.0);

    ASSERT_FLOAT_EQ(2.0, upsample.readOutputBuffer(0));
    ASSERT_FLOAT_EQ(1.5, upsample.readOutputBuffer(1));

    upsample.setUpsampleFactor(5);
    ASSERT_EQ(5, upsample.getOutBufferSize());


    upsample.tick(2.0);

    ASSERT_FLOAT_EQ(1.0, upsample.readOutputBuffer(0));
    ASSERT_FLOAT_EQ(1.2, upsample.readOutputBuffer(1));
    ASSERT_FLOAT_EQ(1.4, upsample.readOutputBuffer(2));
    ASSERT_FLOAT_EQ(1.6, upsample.readOutputBuffer(3));
    ASSERT_FLOAT_EQ(1.8, upsample.readOutputBuffer(4));

}