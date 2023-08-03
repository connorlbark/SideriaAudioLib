# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.

project ("SideriaAudioLib")
set (CMAKE_CXX_STANDARD 14)

option(ARM "ARM" OFF)

# Include sub-projects.
add_subdirectory ("siderialib")
if(${ARM} MATCHES OFF)
    add_subdirectory ("spkr")
endif()