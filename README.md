# Sideria Audio Lib

## Building (native and ARM)

- Set Debug profile with default toolchain output to `cmake-build-debug`, with "Build Type" set to "Debug"
- Download arm toolchain for Daisy
- Create new CMake profile with the CMake flag `-DCMAKE_TOOLCHAIN_FILE=/Users/connorbarker/code/sideria/SideriaAudioLib/external/libDaisy/cmake/toolchains/stm32h750xx.cmake`. This will make sure CMake knows how to use the arm compiler properly
- Make sure "Build Type" is "Debug" and set CMake profile's output to `cmake-build-daisy-debug`
- Now, clone these two profiles, and make sure their "Build Type" type is "Release", otherwise the same.

Now, running the cmake build profiles should work fine, and you should get
four build folders: `cmake-build-daisy-debug`, `cmake-build-debug`, `cmake-build-daisy-release`, `cmake-build-release`

Once those are built, you can start working on the building the projects
based on the daisy.
- Make sure all git submodules are fetched
- Compile libDaisy - `cd external/libDaisy; make all`
- Compile DaisySP - `cd external/DaisySP; make all`
- Compile the desired project `cd projects/X-daisy; make all`

By default, this will compile a release version. If you want to make a debug
version, instead of `make all`, do `DEBUG=1 make all`.

