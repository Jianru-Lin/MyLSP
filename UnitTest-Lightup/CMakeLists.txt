include_directories (
	${gtest_SOURCE_DIR}/include
	${gtest_SOURCE_DIR} )

include_directories (
	../Lightup/include )

add_definitions (
	-D_UNICODE
	-DUNICODE )

add_executable (
	UnitTest-Lightup
	Buffer.cpp 
	CriticalSection.cpp
	EasyWSCEnumProtocols.cpp
	EasyInstallLSP.cpp
	Guid2Str.cpp )

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