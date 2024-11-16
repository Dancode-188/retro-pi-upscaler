# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(RetroUpscaler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include our custom CMake modules
include(cmake/FetchCatch2.cmake)

# Add subdirectories
add_subdirectory(src/core)
add_subdirectory(tests/test_core)