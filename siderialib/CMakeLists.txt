# CMakeList.txt : CMake project for SideriaAudioLib, include source and define
# project specific logic here.
#


# Add source to this project's executable.
add_library (siderialib STATIC
        "include/siderialib.h"  "include/dsp/Types.h" "include/dsp/buffers/StereoCircularBuffer.h" "src/dsp/buffers/StereoCircularBuffer.cpp" "include/effects/delay/ModulatedDelay.h" "include/dsp/LFO.h" "src/dsp/LFO.cpp" "src/effects/delay/ModulatedDelay.cpp" "include/dsp/Math.h" "src/dsp/Math.cpp" "include/effects/filter/BiquadFilter.h"
        "src/effects/filter/BiquadFilter.cpp"
        include/effects/Disperse.h
        src/effects/Disperse.cpp
        include/util/Random.h
        include/util/SmoothedParameter.h
        src/util/SmoothedParameter.cpp
        src/util/Random.cpp
        src/effects/nonlinear/TapeSaturation.cpp
        include/effects/nonlinear/TapeSaturation.h
        src/dsp/Oversample.cpp
        include/dsp/Oversample.h
        src/effects/filter/WindowedSincFilter.cpp
        include/effects/filter/WindowedSincFilter.h
        src/dsp/buffers/MonoCircularBuffer.cpp
        include/effects/resample/Decimate.h
        include/effects/resample/Upsample.h
        include/effects/resample/VariableResample.h
)

target_include_directories(siderialib PUBLIC include)
target_compile_features(siderialib PUBLIC cxx_std_14)

if(MSVC)
  target_compile_options(siderialib PRIVATE /W4 /WX)
else()
  target_compile_options(siderialib PRIVATE -Wall -Wextra -Wpedantic -Werror -O2)
endif()



if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_definitions(SLIB_DEBUG=1)

  enable_testing()
  add_subdirectory(tests)
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET siderialib PROPERTY CXX_STANDARD 14)
endif()



