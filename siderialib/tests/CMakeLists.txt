
add_executable(tests
        dsp/buffers/TestStereoCircularBuffer.cpp
        TestMain.cpp)
target_link_libraries(tests siderialib)
target_link_libraries(tests gtest gtest_main)
