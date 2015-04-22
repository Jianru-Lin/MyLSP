include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_definitions (
	-D_UNICODE
	-DUNICODE )

# come from gtest's file: internal_utils.cmake
foreach (flag_var
         CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
         CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    string(REPLACE "/MD" "-MT" ${flag_var} "${${flag_var}}")
endforeach()


add_executable (
	UnitTest-Lightup
	main.cpp )

target_link_libraries (
	UnitTest-Lightup
	advapi32
	iphlpapi
	psapi
	shell32
	ws2_32
	Lightup
	gtest 
	gtest_main )
