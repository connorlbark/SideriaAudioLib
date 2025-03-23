add_executable(disperse_wasm DisperseWasm.cpp)

#set(CMAKE_EXECUTABLE_SUFFIX ".wasm")

set_target_properties(disperse_wasm PROPERTIES COMPILE_FLAGS "-Os -s WASM=1 --no-entry")
set_target_properties(disperse_wasm PROPERTIES LINK_FLAGS    "-Os -s WASM=1 --no-entry")

target_link_libraries(disperse_wasm PRIVATE siderialib)
