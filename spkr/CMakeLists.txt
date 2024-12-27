# CMakeList.txt : CMake project for SideriaAudioLib, lib source and define
# project specific logic here.
#

add_subdirectory("thirdpartylibs/AudioFile")

# Add source to this project's executable.
add_executable (spkr "spkr.cpp")
target_link_libraries(spkr PUBLIC siderialib)
target_link_libraries(spkr PUBLIC AudioFile)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET spkr PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
