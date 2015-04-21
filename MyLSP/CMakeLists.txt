include_directories (
	../Lightup/include )

if (CMAKE_CL_64)
	set (
		MyLSP
		MyLSP64 )
	set (
		Lightup
		Lightup64 )
	set (
		ModuleDef
		src/module64.def )
else (CMAKE_CL_64)
	set (
		MyLSP
		MyLSP )
	set (
		Lightup
		Lightup )
	set (
		ModuleDef
		src/module.def )
endif (CMAKE_CL_64)

set (
	MyLSP_src
	${ModuleDef}
	src/Global.h
	src/Global.cpp
	src/DllMain.cpp
	src/WSPStartup.cpp
	src/WSPAccept.cpp
	src/WSPAddressToString.cpp
	src/WSPAsyncSelect.cpp
	src/WSPBind.cpp
	src/WSPCancelBlockingCall.cpp
	src/WSPCleanup.cpp
	src/WSPCloseSocket.cpp
	src/WSPConnect.cpp
	src/WSPDuplicateSocket.cpp
	src/WSPEnumNetworkEvents.cpp
	src/WSPEventSelect.cpp
	src/WSPGetOverlappedResult.cpp
	src/WSPGetPeerName.cpp
	src/WSPGetSockName.cpp
	src/WSPGetSockOpt.cpp
	src/WSPGetQOSByName.cpp
	src/WSPIoctl.cpp
	src/WSPJoinLeaf.cpp
	src/WSPListen.cpp
	src/WSPRecv.cpp
	src/WSPRecvDisconnect.cpp
	src/WSPRecvFrom.cpp
	src/WSPSelect.cpp
	src/WSPSend.cpp
	src/WSPSendDisconnect.cpp
	src/WSPSendTo.cpp
	src/WSPSetSockOpt.cpp
	src/WSPShutdown.cpp
	src/WSPSocket.cpp
	src/WSPStringToAddress.cpp )


add_library (
	${MyLSP} 
	SHARED
	${MyLSP_src} )

target_link_libraries (
	${MyLSP}
	${Lightup} )