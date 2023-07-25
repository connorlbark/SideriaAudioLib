# CMakeList.txt : CMake project for SideriaAudioLib, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_library (siderialib STATIC "SideriaAudioLib.cpp" "SideriaAudioLib.h"  "include/dsp/Types.h" "include/dsp/Buffer.h" "include/dsp/buffers/CBuffer.h" "include/dsp/buffers/StereoCircularBuffer.h" "src/dsp/buffers/StereoCircularBuffer.cpp" "src/dsp/buffers/CBuffer.cpp" "include/effects/delay/ModulatedDelay.h" "include/dsp/LFO.h" "src/dsp/LFO.cpp" "src/effects/delay/ModulatedDelay.cpp" "include/StereoEffect.h")

target_include_directories(siderialib PUBLIC include)
target_compile_features(siderialib PUBLIC cxx_std_20)

add_compile_definitions(SLIB_DEBUG=1)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET siderialib PROPERTY CXX_STANDARD 20)
endif()

