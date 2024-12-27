#include <gtest/gtest.h>
#include "../../../../lib/effects/resample/VariableResample.h"


TEST(VariableResample, VariableResample) {
    siderialib::StaticMemoryAllocation sma;
    sma.initialize(20);

    siderialib::VariableResample resample;
    resample.initialize(sma);
    resample.setResampleFactor(0.5);

    ASSERT_EQ(2, resample.getDecimateFactor());
    ASSERT_EQ(1, resample.getUpsampleFactor());

    resample.tick(1.0);
    resample.tick(1.0);
    resample.tick(1.0);

    ASSERT_FLOAT_EQ(1.0, resample.tick(1.0));
    ASSERT_FLOAT_EQ(1.0, resample.tick(2.0));
    ASSERT_FLOAT_EQ(1.0, resample.tick(3.0));
    ASSERT_FLOAT_EQ(3.0, resample.tick(4.0));
    ASSERT_FLOAT_EQ(3.0, resample.tick(5.0));
    ASSERT_FLOAT_EQ(5.0, resample.tick(6.0));

    resample.setResampleFactor(0.75);

    ASSERT_EQ(4, resample.getDecimateFactor());
    ASSERT_EQ(3, resample.getUpsampleFactor());

    resample.tick(1.0);
    resample.tick(1.0);
    resample.tick(1.0);


    ASSERT_FLOAT_EQ(1.0, resample.tick(1.0));
    ASSERT_FLOAT_EQ(1.0, resample.tick(2.0));
    ASSERT_FLOAT_EQ(2.3333333, resample.tick(3.0));
    ASSERT_FLOAT_EQ(3.6666667, resample.tick(4.0));
    ASSERT_FLOAT_EQ(3.6666667, resample.tick(4.0));
    ASSERT_FLOAT_EQ(4.0, resample.tick(4.0));
    ASSERT_FLOAT_EQ(4.0, resample.tick(4.0));

    sma.freeAllocation();
}