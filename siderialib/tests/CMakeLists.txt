
add_executable(tests
        dsp/buffers/TestStereoCircularBuffer.cpp
        TestMain.cpp
        util/TestSmoothedParameter.cpp
        test_utils/SineFrequencyAnalysis.cpp
        test_utils/TestSineFrequencyAnalysis.cpp
        dsp/effects/filter/TestBiquadFilter.cpp
        dsp/effects/filter/TestWindowedSinc.cpp
        dsp/TestMath.cpp
        dsp/effects/resample/TestDecimate.cpp
        dsp/effects/resample/TestUpsample.cpp
        dsp/effects/resample/TestVariableResample.cpp
        util/TestStaticMemoryAllocation.cpp
)
target_link_libraries(tests siderialib)
target_link_libraries(tests matplot)
target_link_libraries(tests gtest gtest_main)

