# Sideria Audio Lib

## Building (native and ARM)

- Set Debug profile with default toolchain output to `debug/`
- Download arm toolchain for Daisy
- Create new Arm-based toolchain with `arm-none-eabi-gcc` and `arm-non-eabi-g++`
- Create new CMake profile using the arm-based compilers, with the CMake flag `-DCMAKE_TOOLCHAIN_FILE=arm-gcc-toolchain.cmake`. This will make sure CMake knows how to use the arm compiler properly.
- Set CMake profile's output to `debug-arm`