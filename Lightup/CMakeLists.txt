add_definitions (
	-D_UNICODE
	-DUNICODE )

set (
	src
	include/Lightup.h
	src/Buffer.h
	src/Buffer.cpp
	src/CriticalSection.h
	src/CriticalSection.cpp
	src/EasyWSCEnumProtocols.h
	src/EasyWSCEnumProtocols.cpp )

add_library (
	Lightup 
	STATIC 
	${src} )