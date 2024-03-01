cmake_minimum_required(VERSION 3.21)
project(MyCompiler)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/externals/cmake-scripts" ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/externals/cmake-modules" ${CMAKE_MODULE_PATH})

include(compiler-options)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_COLOR_DIAGNOSTICS ON)

set(ENABLE_ALL_WARNINGS ON)
set(ENABLE_EFFECTIVE_CXX ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MyCompiler_SOURCE_DIR}/bin)

add_subdirectory(lib)
