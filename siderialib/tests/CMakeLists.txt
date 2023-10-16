
add_executable(tests dsp/buffers/TestStereoCircularBuffer.cpp)
target_link_libraries(tests siderialib)
target_link_libraries(tests gtest_main)
add_test(NAME gtest COMMAND tests)