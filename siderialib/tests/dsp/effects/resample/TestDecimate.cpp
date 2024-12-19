#include <gtest/gtest.h>
#include "../../../../include/effects/resample/Decimate.h"


TEST(Decimate, Decimate) {
    siderialib::Decimate decimate;
    decimate.initialize();
    decimate.setDownsampleFactor(2);

    ASSERT_EQ(1.0, decimate.tick(1.0));
    ASSERT_EQ(1.0, decimate.tick(2.0));
    ASSERT_EQ(3.0, decimate.tick(3.0));
    ASSERT_EQ(3.0, decimate.tick(4.0));

    decimate.setDownsampleFactor(3);

    ASSERT_EQ(1.0, decimate.tick(1.0));
    ASSERT_EQ(1.0, decimate.tick(2.0));
    ASSERT_EQ(1.0, decimate.tick(3.0));
    ASSERT_EQ(4.0, decimate.tick(4.0));
    ASSERT_EQ(4.0, decimate.tick(5.0));
    ASSERT_EQ(4.0, decimate.tick(6.0));

}