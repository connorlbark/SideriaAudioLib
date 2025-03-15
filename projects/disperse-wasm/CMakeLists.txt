add_executable(disperse_wasm DisperseWasm.cpp)

set(CMAKE_EXECUTABLE_SUFFIX ".wasm")

set_target_properties(disperse_wasm PROPERTIES COMPILE_FLAGS "-Os -s SIDE_MODULE=1 ")
set_target_properties(disperse_wasm PROPERTIES LINK_FLAGS    "-Os -s WASM=1 -s SIDE_MODULE=1 -s STANDALONE_WASM --no-entry")

link_libraries(disperse_wasm PUBLIC siderialib)
include_directories(../../siderialib/lib)
