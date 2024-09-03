#include <gtest/gtest.h>
#include <matplot/matplot.h>

#include "../../../test_utils/SineFrequencyAnalysis.h"
#include "../../../../include/effects/filter/BiquadFilter.h"

using namespace siderialib;

TEST(TestBiquadFilter, GenerateLPFPlot) {
    BiquadFilter filter;

    SineFrequencyAnalysis analysis{};

    analysis.initialize(
            [&filter](sfloat in) {
                return filter.tick(in);
            },
            [&filter]() {
                filter.initialize(
                        44100.0,
                        BiquadType::LPF,
                        10000.0,
                        1.0f);
            },
            44100.f);

    analysis.setStabilityBuffer(44100);

    std::vector<sfloat> y = analysis.analyze(
            10.0,
            22500.0,
            3000,
            1.0,
            44100);


    std::vector<sfloat> x(3000);
    for (int i = 0; i < 3000; i++) {
        x[i] = (((22500.f-10.f)/3000.f) * (sfloat)i + 10.f);
    }

    matplot::figure(true);
    matplot::plot(x, y);
    std::filesystem::create_directories("plots");
    std::filesystem::create_directories("plots/biquad_filter");
    matplot::save("plots/biquad_filter/lpf10000hzQ1.svg");
}

TEST(TestBiquadFilter, GenerateHPFPlot) {
    BiquadFilter filter;

    SineFrequencyAnalysis analysis{};

    analysis.initialize(
            [&filter](sfloat in) {
                return filter.tick(in);
            },
            [&filter]() {
                filter.initialize(
                        44100.0,
                        BiquadType::HPF,
                        10000.0,
                        1.0f);
            },
            44100.f);

    analysis.setStabilityBuffer(44100);

    std::vector<sfloat> y = analysis.analyze(
            10.0,
            22500.0,
            3000,
            1.0,
            44100);


    std::vector<sfloat> x(3000);
    for (int i = 0; i < 3000; i++) {
        x[i] = (((22500.f-10.f)/3000.f) * (sfloat)i + 10.f);
    }

    matplot::figure(true);
    matplot::plot(x, y);
    std::filesystem::create_directories("plots");
    std::filesystem::create_directories("plots/biquad_filter");
    matplot::save("plots/biquad_filter/hpf10000hzQ1.svg");
}

TEST(TestBiquadFilter, LPFBasicChecks) {
    BiquadFilter filter;

    SineFrequencyAnalysis analysis{};

    analysis.initialize(
            [&filter](sfloat in) {
                return filter.tick(in);
            },
            [&filter]() {
                filter.initialize(
                        44100.0,
                        BiquadType::LPF,
                        10000.0,
                        1.0f);
            },
            44100.f);

    analysis.setStabilityBuffer(44100);

    std::vector<sfloat> y = analysis.analyze(
            10.0,
            22500.0,
            3000,
            1.0,
            44100);

    // passband should monotonically increase
    sfloat prevValue = y[0];
    for (int i = 0; i < 1100; i++) {
        ASSERT_LT(y[i], 1.2);
        ASSERT_GE(y[i], .99);

        ASSERT_GE(y[i], prevValue);
    }

    // stopband should monotonically decrease
    prevValue = y[1149];
    for (int i = 1150; i < 3000; i++) {
        ASSERT_LT(y[i], 1.15);
        ASSERT_LE(y[i], prevValue);
    }

    // check a few points on the stopband slope
    // to make sure it's roughly as expected
    ASSERT_LT(y[1500], 0.8);
    ASSERT_LT(y[1600], 0.7);
    ASSERT_LT(y[1700], 0.6);
    ASSERT_LT(y[1800], 0.5);
    ASSERT_LT(y[2000], 0.3);
    ASSERT_LT(y[2200], 0.2);
    ASSERT_LT(y[2900], 0.01);
}

TEST(TestBiquadFilter, HPFBasicChecks) {
    BiquadFilter filter;

    SineFrequencyAnalysis analysis{};

    analysis.initialize(
            [&filter](sfloat in) {
                return filter.tick(in);
            },
            [&filter]() {
                filter.initialize(
                        44100.0,
                        BiquadType::HPF,
                        10000.0,
                        1.0f);
            },
            44100.f);

    analysis.setStabilityBuffer(44100);

    std::vector<sfloat> y = analysis.analyze(
            10.0,
            22500.0,
            3000,
            1.0,
            44100);

    // stopband should monotonically increase
    sfloat prevValue = y[0];
    for (int i = 0; i < 1500; i++) {
        ASSERT_LT(y[i], 1.2);

        ASSERT_GE(y[i], prevValue);
    }

    // passband should monotonically decrease
    prevValue = y[1699];
    for (int i = 1700; i < 3000; i++) {
        ASSERT_LT(y[i], 1.2);
        ASSERT_LE(y[i], prevValue);
    }

    // check a few points on the stopband slope
    // to make sure it's roughly as expected
    ASSERT_GT(y[5], 0.0);
    ASSERT_GT(y[500], 0.05);
    ASSERT_GT(y[1000], 0.3);
    ASSERT_GT(y[1200], 0.4);
    ASSERT_GT(y[1300], 0.5);
    ASSERT_GT(y[1400], 0.7);
    ASSERT_GT(y[1500], 1);
}