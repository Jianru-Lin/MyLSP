if (CMAKE_CL_64)
	set (
		Lightup
		Lightup64 )
else (CMAKE_CL_64)
	set (
		Lightup
		Lightup )
endif (CMAKE_CL_64)


set (
	src
	include/Lightup.h
	src/Buffer.h
	src/Buffer.cpp
	src/CriticalSection.h
	src/CriticalSection.cpp )

add_library (
	${Lightup} 
	STATIC 
	${src} )