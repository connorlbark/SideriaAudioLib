//
// Created by Connor Barker on 9/29/23.
//
#include <gtest/gtest.h>
#include "../../../include/dsp/buffers/StereoCircularBuffer.h"

TEST(TestStereoCircularBuffer, Initialize) {
    siderialib::StereoCircularBuffer buf1{};

    buf1.initialize(1000);

    ASSERT_EQ(buf1.size(), 1000);
    ASSERT_EQ(buf1.numChannels(), 2);

    for (int i = 0; i < buf1.size(); i++) {
        ASSERT_EQ(buf1.read(0, i), 0.0f);
        ASSERT_EQ(buf1.read(1, i), 0.0f);
    }

    siderialib::StereoCircularBuffer buf2{};

    buf2.initialize(200);

    ASSERT_EQ(buf2.size(), 200);
    ASSERT_EQ(buf2.numChannels(), 2);

    for (int i = 0; i < buf2.size(); i++) {
        ASSERT_EQ(buf2.read(0, i), 0.0f);
        ASSERT_EQ(buf2.read(1, i), 0.0f);
    }

}

TEST(TestStereoCircularBuffer, WriteAndReadCircular) {
    siderialib::StereoCircularBuffer buf{};

    buf.initialize(5);

    ASSERT_EQ(buf.readCircular(0), 0.f);
    ASSERT_EQ(buf.readCircular(1), 0.f);

    buf.writeCircular(1.f, 5.f);

    ASSERT_EQ(buf.readCircular(0), 1.f);
    ASSERT_EQ(buf.readCircular(1), 5.f);

    ASSERT_EQ(buf.readCircular(0, 0), 1.f);
    ASSERT_EQ(buf.readCircular(1, 0), 5.f);

    ASSERT_EQ(buf.readCircular(0, 1), 0.f);
    ASSERT_EQ(buf.readCircular(1, 1), 0.f);

    buf.writeCircular(2.f, 4.f);

    ASSERT_EQ(buf.readCircular(0), 2.f);
    ASSERT_EQ(buf.readCircular(1), 4.f);

    ASSERT_EQ(buf.readCircular(0, 0), 2.f);
    ASSERT_EQ(buf.readCircular(1, 0), 4.f);

    ASSERT_EQ(buf.readCircular(0, 1), 1.f);
    ASSERT_EQ(buf.readCircular(1, 1), 5.f);

    ASSERT_EQ(buf.readCircular(0, 2), 0.f);
    ASSERT_EQ(buf.readCircular(1, 2), 0.f);

    buf.writeCircular(3.f, 3.f);
    buf.writeCircular(4.f, 2.f);
    buf.writeCircular(5.f, 1.f);
    buf.writeCircular(6.f, 0.f);

    ASSERT_EQ(buf.readCircular(0, 0), 6.f);
    ASSERT_EQ(buf.readCircular(1, 0), 0.f);

    ASSERT_EQ(buf.readCircular(0, 1), 5.f);
    ASSERT_EQ(buf.readCircular(1, 1), 1.f);

    ASSERT_EQ(buf.readCircular(0, 2), 4.f);
    ASSERT_EQ(buf.readCircular(1, 2), 2.f);

    ASSERT_EQ(buf.readCircular(0, 3), 3.f);
    ASSERT_EQ(buf.readCircular(1, 3), 3.f);

    ASSERT_EQ(buf.readCircular(0, 4), 2.f);
    ASSERT_EQ(buf.readCircular(1, 4), 4.f);

    // loops back around
    ASSERT_EQ(buf.readCircular(0, 5), 6.f);
    ASSERT_EQ(buf.readCircular(1, 5), 0.f);

    ASSERT_EQ(buf.readCircular(0, 6), 5.f);
    ASSERT_EQ(buf.readCircular(1, 6), 1.f);

    ASSERT_EQ(buf.readCircular(0, 7), 4.f);
    ASSERT_EQ(buf.readCircular(1, 7), 2.f);

    ASSERT_EQ(buf.readCircular(0, 8), 3.f);
    ASSERT_EQ(buf.readCircular(1, 8), 3.f);

    ASSERT_EQ(buf.readCircular(0, 9), 2.f);
    ASSERT_EQ(buf.readCircular(1, 9), 4.f);

    // loop again...
    ASSERT_EQ(buf.readCircular(0, 10), 6.f);
    ASSERT_EQ(buf.readCircular(1, 10), 0.f);

}
