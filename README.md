# Sideria Audio Lib

## Building (native and ARM)

- Set Debug profile with default toolchain output to `debug/`
- Download arm toolchain for Daisy
- Create new CMake profile with the CMake flag `-DCMAKE_TOOLCHAIN_FILE=/Users/connorbarker/code/sideria/SideriaAudioLib/external/libDaisy/cmake/toolchains/stm32h750xx.cmake`. This will make sure CMake knows how to use the arm compiler properly.
- Set CMake profile's output to `debug-arm`

Now, running the cmake build profiles should work fine.

Once those build, you can start working on the building the projects
based on the daisy.
- Make sure all git submodules are fetched
- Compile libDaisy - `cd external/libDaisy; make all`
- Compile DaisySP - `cd external/DaisySP; make all`
- Compile the desired project `cd projects/X-daisy; make all`

