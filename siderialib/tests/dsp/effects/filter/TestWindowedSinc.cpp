#include <gtest/gtest.h>
#include <matplot/matplot.h>

#include "../../../test_utils/SineFrequencyAnalysis.h"
#include "../../../../lib/effects/filter/WindowedSincFilter.h"

using namespace siderialib;

TEST(TestWindowedSincFilter, GenerateLPFPlot) {
//    WindowedSincFilter filter{};
//
//    SineFrequencyAnalysis analysis{};
//
//    filter.initialize(
//            501,
//            44100.0/4.0,
//            44100.f);
//    analysis.initialize(
//            [&filter](sfloat in) {
//                return filter.tick(in);
//            },
//            [&filter]() {
//                filter.initialize(
//                        501,
//                        44100./2.,
//                        44100.f);
//            },
//            44100.f);
//
//    analysis.setStabilityBuffer(44100);
//
//    std::vector<sfloat> y = analysis.analyze(
//            10.0,
//            22500.0,
//            3000,
//            1.0,
//            44100);
//
//
//    std::vector<sfloat> x(3000);
//    for (int i = 0; i < 3000; i++) {
//        x[i] = (((22500.f-10.f)/3000.f) * (sfloat)i + 10.f);
//    }
//
//    std::vector<double> fir{};
//    std::vector<int> firX{};
//
//    fir.reserve(filter.getFirLength());
//    firX.reserve(filter.getFirLength());
//    for (int i = 0; i < filter.getFirLength(); i++) {
//        fir.push_back(filter.getFir()[i]);
//        firX.push_back(i - (filter.getFirLength()/2));
//    }
//
//
//    matplot::plot(x, y);
////    printf("%f\n",fir[5]);
//    std::filesystem::create_directories("plots");
//    std::filesystem::create_directories("plots/biquad_filter");
//    matplot::save("plots/windowed_sinc/lpf10000hz.svg");
//    matplot::plot(firX, fir);
//    matplot::save("plots/windowed_sinc/fir.svg");

}
