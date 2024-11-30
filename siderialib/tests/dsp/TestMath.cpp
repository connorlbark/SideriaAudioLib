#include <gtest/gtest.h>
#include "../../include/dsp/Math.h"

TEST(Math, Pan) {
    float pan = 1.0f;
    EXPECT_FLOAT_EQ(siderialib::constantPowerPanL(pan, 1.0f), 1.0);
    EXPECT_FLOAT_EQ(siderialib::constantPowerPanR(pan, 1.0f), 0.0);

    pan = 0.0f;
    EXPECT_FLOAT_EQ(siderialib::constantPowerPanL(pan, 1.0f), 0.0);
    EXPECT_FLOAT_EQ(siderialib::constantPowerPanR(pan, 1.0f), 1.0);

    pan = 0.5f;
    EXPECT_FLOAT_EQ(siderialib::constantPowerPanL(pan, 1.0f), 0.70710677);
    EXPECT_FLOAT_EQ(siderialib::constantPowerPanR(pan, 1.0f), 0.70710677);

    pan = 0.25f;
    EXPECT_FLOAT_EQ(siderialib::constantPowerPanL(pan, 1.0f), 0.5);
    EXPECT_FLOAT_EQ(siderialib::constantPowerPanR(pan, 1.0f), 0.8660254);
}