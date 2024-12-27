# CMakeList.txt : CMake project for SideriaAudioLib, include source and define
# project specific logic here.
#


# Add source to this project's executable.
add_library (siderialib STATIC
        "lib/siderialib.h"  "lib/dsp/Types.h" "lib/dsp/buffers/StereoCircularBuffer.h" "lib/dsp/buffers/StereoCircularBuffer.cpp" "lib/effects/delay/ModulatedDelay.h" "lib/dsp/LFO.h" "lib/dsp/LFO.cpp" "lib/effects/delay/ModulatedDelay.cpp" "lib/dsp/Math.h" "lib/dsp/Math.cpp" "lib/effects/filter/BiquadFilter.h"
        "lib/effects/filter/BiquadFilter.cpp"
        lib/effects/Disperse.h
        lib/effects/Disperse.cpp
        lib/util/Random.h
        lib/util/SmoothedParameter.h
        lib/util/SmoothedParameter.cpp
        lib/util/Random.cpp
        lib/effects/nonlinear/TapeSaturation.cpp
        lib/effects/nonlinear/TapeSaturation.h
        lib/effects/filter/WindowedSincFilter.cpp
        lib/effects/filter/WindowedSincFilter.h
        lib/dsp/buffers/MonoCircularBuffer.cpp
        lib/effects/resample/Decimate.h
        lib/effects/resample/Upsample.h
        lib/effects/resample/VariableResample.h
        lib/effects/disperse/DisperseParallelVoice.cpp
        lib/effects/disperse/DisperseParallelVoice.h
        lib/effects/disperse/DisperseConstants.h
        lib/util/StaticMemoryBlock.cpp
        lib/util/StaticMemoryAllocation.h
        lib/effects/resample/Upsample.cpp
        lib/effects/resample/Decimate.cpp
)

target_include_directories(siderialib PUBLIC lib)
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



