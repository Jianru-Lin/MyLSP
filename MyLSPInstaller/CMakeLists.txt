include_directories (
	../Lightup/include )

add_definitions (
	-D_UNICODE
	-DUNICODE )

add_executable (
	MyLSPInstaller
	src/main.cpp )

target_link_libraries (
	MyLSPInstaller
	advapi32
	iphlpapi
	psapi
	shell32
	ws2_32
	Lightup )