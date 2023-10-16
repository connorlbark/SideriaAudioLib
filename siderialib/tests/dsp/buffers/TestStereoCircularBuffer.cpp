//
// Created by Connor Barker on 9/29/23.
//
#include <gtest/gtest.h>
#include "../../../include/dsp/buffers/StereoCircularBuffer.h"

TEST(TestStereoCircularBuffer, Initialize) {
    siderialib::StereoCircularBuffer buf{};

    buf.initialize(1000);

    ASSERT_EQ(buf.size(), 1000);
    ASSERT_EQ(buf.numChannels(), 2);

    for (int i = 0; i < buf.size(); i++) {
        ASSERT_EQ(buf.read(0, i), 0.0f);
        ASSERT_EQ(buf.read(1, i), 0.0f);
    }
}