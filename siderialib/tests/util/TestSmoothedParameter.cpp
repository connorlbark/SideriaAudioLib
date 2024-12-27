#include <gtest/gtest.h>
#include "../../lib/util/SmoothedParameter.h"

using namespace siderialib;

TEST(TestSmoothedParameter, ConvergesEventually) {

    sfloat sampleRate = 1000.f;
    sfloat smoothingTime = 1000.f;

    SmoothedParameter param = SmoothedParameter{};

    param.initialize(smoothingTime, sampleRate);

    ASSERT_EQ(0.f, param.value());

    // converges upward small amount
    param.setTarget(5.0);

    sfloat valBefore;
    sfloat valAfter;
    for (int i = 0; i < 1000; i++) {
        valBefore = param.value();
        param.tick();
        valAfter = param.value();

        ASSERT_GT(valAfter, valBefore);
    }

    ASSERT_NEAR(5.f, param.value(), .01f);

    // converges upward large amount
    param.setTarget(500.0);

    for (int i = 0; i < 1000; i++) {
        valBefore = param.value();
        param.tick();
        valAfter = param.value();

        ASSERT_GT(valAfter, valBefore);
    }

    ASSERT_NEAR(500.f, param.value(), 1.0f);

    // converges downward small change
    param.setTarget(0.0);

    for (int i = 0; i < 1000; i++) {
        valBefore = param.value();
        param.tick();
        valAfter = param.value();

        ASSERT_LT(valAfter, valBefore);
    }

    ASSERT_NEAR(0.f, param.value(), 1.0f);

}

TEST(TestSmoothedParameter, SampleRateHandledCorrectly) {

    sfloat sampleRate = 200.f;
    sfloat smoothingTime = 1000.f;

    SmoothedParameter param = SmoothedParameter{};

    param.initialize(smoothingTime, sampleRate);

    param.setTarget(10.f);

    sfloat valBefore;
    sfloat valAfter;
    for (int i = 0; i < 200; i++) {
        valBefore = param.value();
        param.tick();
        valAfter = param.value();

        ASSERT_GT(valAfter, valBefore);
        ASSERT_TRUE(param.value() < 9.99f);

    }

    ASSERT_NEAR(10.f, param.value(), .02f);
}

TEST(TestSmoothedParameter, SmoothingTimeHandledCorrectly) {

    sfloat sampleRate = 1000.f;
    sfloat smoothingTime = 2000.f;

    SmoothedParameter param = SmoothedParameter{};

    param.initialize(smoothingTime, sampleRate);

    param.setTarget(10.f);

    sfloat valBefore;
    sfloat valAfter;
    for (int i = 0; i < 2000; i++) {
        valBefore = param.value();
        param.tick();
        valAfter = param.value();

        ASSERT_GT(valAfter, valBefore);
        ASSERT_TRUE(param.value() < 9.99f);

    }

    ASSERT_NEAR(10.f, param.value(), .02f);
}