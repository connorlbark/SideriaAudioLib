#include <gtest/gtest.h>

#include "../../../test_utils/SineFrequencyAnalysis.h"
#include "../../../../include/effects/filter/BiquadFilter.h"

using namespace siderialib;

TEST(TestBiquadFilter, BasicLPF) {
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
                        1000.0,
                        2.f);
            },
            44100.f);

    std::vector<sfloat> bins = analysis.analyze(
            10.0,
            2000.0,
            2000,
            1.0,
            44100 * 3);

//    // sanity check
//    for (sfloat val : bins) {
//        ASSERT_LT(val, 1.5);
//        ASSERT_GE(val, 0.0);
//    }
//
//    for (int i = 0; i < 1000; i++) {
//        ASSERT_NEAR(
//                bins.at(i),
//                1.0,
//                .22);
//    }
//
//    for (int i = 1001; i < bins.size(); i++) {
//        ASSERT_TRUE(bins.at(i) < 1.0);
//    }

    for (int i = 0; i < bins.size(); i++) {
        if (i == 0) {
            printf("[%f,", bins.at(i));
        } else if (i == bins.size()-1) {
            printf("%f]\n", bins.at(i));
        } else {
            printf("%f,", bins.at(i));
        }
    }
}


