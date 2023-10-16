# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
if ( NOT CMAKE_BUILD_TYPE )
    message( "Build Type not set, defaulting to Debug..." )
    set( CMAKE_BUILD_TYPE Debug )
endif()

# Enable Hot Reload for MSVC compilers if supported.

project ("SideriaAudioLib")
set (CMAKE_CXX_STANDARD 14)

option(ARM "ARM" OFF)

# Include sub-projects.
add_subdirectory ("siderialib")
if(${ARM} MATCHES OFF)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_subdirectory("external/googletest")
    endif()
    add_subdirectory ("external/JUCE")
    add_subdirectory ("projects/disperse-juce")
    add_subdirectory ("spkr")
endif()