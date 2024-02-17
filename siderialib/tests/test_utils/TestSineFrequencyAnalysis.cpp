#include <gtest/gtest.h>
#include <matplot/matplot.h>

#include "SineFrequencyAnalysis.h"

using namespace siderialib;

TEST(TestSineFrequencyAnalysis, PassThrough) {
    SineFrequencyAnalysis analysis{};

    analysis.initialize(
            [](sfloat in) {
                return in;
            },
            []() {
                // do nothing on reset
            },
            1000);

    // full cycle
    ASSERT_EQ(0.5,
              analysis.analyze(
                      1.0,
                      0.5,
                      1000));

    // half cycle should still have same max
    ASSERT_EQ(0.5,
              analysis.analyze(
                      1.0,
                      0.5,
                      500));

    // quarter cycle should also go almost up to 0.5
    ASSERT_NEAR(0.5,
              analysis.analyze(
                      1.0,
                      0.5,
                      250),
              0.01);

    // half cycle with different amp should work
    ASSERT_EQ(1.5,
              analysis.analyze(
                      1.0,
                      1.5,
                      500));
}

TEST(TestSineFrequencyAnalysis, ResetsEachTime) {
    SineFrequencyAnalysis analysis{};

    int numTimesRan = 0;

    analysis.initialize(
            [&numTimesRan](sfloat in) {
                return (sfloat)numTimesRan++;
            },
            [&numTimesRan]() {
                numTimesRan = 0;
            },
            1000);

    ASSERT_EQ(999,
              analysis.analyze(
                      1.0,
                      0.5,
                      1000));


    ASSERT_EQ(249,
                analysis.analyze(
                        1.0,
                        0.5,
                        250));
}

TEST(TestSineFrequencyAnalysis, RunsManyTimes) {
    SineFrequencyAnalysis analysis{};

    int numTimesRan = 0;

    analysis.initialize(
            [&numTimesRan](sfloat in) {
                return (sfloat) numTimesRan++;
            },
            [&numTimesRan]() {
                numTimesRan = 0;
            }, 1000.f);

    std::vector<sfloat> results = analysis.analyze(
            0.0, 200.0, 10,
            0.5, 100);

    ASSERT_EQ(10, results.size());
    for (float result : results) {
        ASSERT_EQ(99, result);
    }
}

TEST(TestSineFrequencyAnalysis, GenerateSinePlot) {
    SineFrequencyAnalysis analysis{};

    std::vector<sfloat> y;

    analysis.initialize(
            [&y](sfloat in) {
                y.push_back(in);
                return in;
            },
            [&y]() {
            }, 1000.f);

    analysis.analyze(1.0,0.5, 3000);

    matplot::plot(y);
    matplot::save("plots/sine_freq_analysis/sineInput.svg");

}