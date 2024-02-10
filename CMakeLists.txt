cmake_minimum_required(VERSION 3.0)
project(Compiler)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Compiler_SOURCE_DIR}/bin)

add_subdirectory(lib)
