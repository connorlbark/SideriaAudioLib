#include <gtest/gtest.h>
#include "../../lib/dsp/Math.h"

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

TEST(Math, FractionFromFloat) {

    float val = 0.5f;
    siderialib::Fraction frac = siderialib::floatToFraction(val);
    EXPECT_EQ(frac.numerator, 1);
    EXPECT_EQ(frac.denominator, 2);

    val = 0.25f;
    frac = siderialib::floatToFraction(val);
    EXPECT_EQ(frac.numerator, 1);
    EXPECT_EQ(frac.denominator, 4);

    val = 0.62;
    frac = siderialib::floatToFraction(val, 8);
    EXPECT_EQ(frac.numerator, 5);
    EXPECT_EQ(frac.denominator, 8);

    frac = siderialib::floatToFraction(val, 7);
    EXPECT_EQ(frac.numerator, 3);
    EXPECT_EQ(frac.denominator, 5);

    val = 0.6;
    frac = siderialib::floatToFraction(val, 10);
    EXPECT_EQ(frac.numerator, 3);
    EXPECT_EQ(frac.denominator, 5);

}