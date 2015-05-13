cmake_minimum_required (VERSION 2.6)
project (MyLSP)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Output)

add_custom_target(Dependency)

if (CMAKE_CL_64)
	include_directories($ENV{devpackages}/icu/x64/include)
	link_directories($ENV{devpackages}/icu/x64/lib64)
	add_custom_command(TARGET Dependency COMMAND echo copy /Y "\"$ENV{devpackages}\\icu\\x64\\bin64\\*.dll\"" "\"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>\"")
	add_custom_command(TARGET Dependency COMMAND copy /Y "\"$ENV{devpackages}\\icu\\x64\\bin64\\*.dll\"" "\"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>\"")
else (CMAKE_CL_64)
	include_directories($ENV{devpackages}/icu/x86/include)
	link_directories($ENV{devpackages}/icu/x86/lib)
	add_custom_command(TARGET Dependency COMMAND echo copy /Y "\"$ENV{devpackages}\\icu\\x86\\bin\\*.dll\"" "\"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>\"")
	add_custom_command(TARGET Dependency COMMAND copy /Y "\"$ENV{devpackages}\\icu\\x86\\bin\\*.dll\"" "\"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>\"")
endif (CMAKE_CL_64)

add_subdirectory (MyLSP)
add_subdirectory (MyLSPInstaller)
add_subdirectory (Lightup)
add_subdirectory (gtest-1.7.0)
add_subdirectory (UnitTest-Lightup)

enable_testing()
add_test(UnitTest-Lightup ${CMAKE_BINARY_DIR}/Output/UnitTest-Lightup)