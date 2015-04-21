include_directories (
	../Lightup/include )

add_definitions (
	-D_UNICODE
	-DUNICODE )

if (CMAKE_CL_64)
	set (
		MyLSPInstaller
		MyLSPInstaller64 )
	set (
		Lightup
		Lightup64 )
else (CMAKE_CL_64)
	set (
		MyLSPInstaller
		MyLSPInstaller )
	set (
		Lightup
		Lightup )
endif (CMAKE_CL_64)


add_executable (
	${MyLSPInstaller}
	src/main.cpp )

target_link_libraries (
	${MyLSPInstaller}
	advapi32
	iphlpapi
	psapi
	shell32
	ws2_32
	${Lightup} )