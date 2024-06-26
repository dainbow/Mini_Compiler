cmake_minimum_required(VERSION 3.21)
project(MyCompiler LANGUAGES CXX C)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/externals/cmake-scripts" ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/externals/cmake-modules" ${CMAKE_MODULE_PATH})
message("${CMAKE_MODULE_PATH}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_COLOR_DIAGNOSTICS ON)

set(ENABLE_ALL_WARNINGS ON)
set(ENABLE_EFFECTIVE_CXX ON)
include(compiler-options)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MyCompiler_SOURCE_DIR}/bin)

add_subdirectory(lib)
