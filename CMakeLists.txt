cmake_minimum_required (VERSION 2.6)
project (MyLSP)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Output)

add_subdirectory (MyLSP)
add_subdirectory (MyLSPInstaller)
add_subdirectory (Lightup)
add_subdirectory (gtest-1.7.0)
add_subdirectory (UnitTest-Lightup)

enable_testing()
add_test(UnitTest-Lightup ${CMAKE_BINARY_DIR}/Output/UnitTest-Lightup)