# Sideria Audio Lib

## What is this?

This is a hand-made audio library which is the basis for all of my plugins and pedals. It is written in pure C-like C++ (no `new`, no `v-tables`, only `c-arrays`, etc.) for maximum portability to both PCs and also Arm/microcontrollers. The `siderialib/` folder contains the backend audio code - e.g., filters, delays, etc.. This code can then be linked to different "frontends" in the `projects/` folder, like a JUCE VST3 plugin or an Arm chip like the Electro-Smith Daisy.

Everything that can easily be made into a CMake project has been made into one. If you build this project at the top level, the library and all of the JUCE plugins will be built. However, any projects which use the Electro-Smith Daisy will need to be compiled separately as they do not support CMake. See the next section for details.

## Building (native and ARM)

First, compile JUCE.
```bash
cmake . -B cmake-build -DJUCE_BUILD_EXAMPLES=ON -DJUCE_BUILD_EXTRAS=ON
```

Then, set up build profiles
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

