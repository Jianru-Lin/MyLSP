set (
	src
	include/Lightup.h
	src/Buffer.h
	src/Buffer.cpp
	src/CriticalSection.h
	src/CriticalSection.cpp )

add_library (
	Lightup 
	STATIC 
	${src} )