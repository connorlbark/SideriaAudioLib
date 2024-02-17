
add_executable(tests
        dsp/buffers/TestStereoCircularBuffer.cpp
        TestMain.cpp
        util/TestSmoothedParameter.cpp
        test_utils/SineFrequencyAnalysis.cpp
        test_utils/TestSineFrequencyAnalysis.cpp
        dsp/effects/filter/TestBiquadFilter.cpp
)
target_link_libraries(tests siderialib)
target_link_libraries(tests gtest gtest_main)
