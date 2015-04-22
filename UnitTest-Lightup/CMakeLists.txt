include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_definitions (
	-D_UNICODE
	-DUNICODE )

if (CMAKE_CL_64)
	set (
		UnitTest-Lightup
		UnitTest-Lightup64 )
	set (
		Lightup
		Lightup64 )
else (CMAKE_CL_64)
	set (
		UnitTest-Lightup
		UnitTest-Lightup )
	set (
		Lightup
		Lightup )
endif (CMAKE_CL_64)


add_executable (
	${UnitTest-Lightup}
	main.cpp )

target_link_libraries (
	${UnitTest-Lightup}
	advapi32
	iphlpapi
	psapi
	shell32
	ws2_32
	${Lightup}
	gtest 
	gtest_main )
