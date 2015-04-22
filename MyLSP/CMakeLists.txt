include_directories (
	../Lightup/include )

add_definitions (
	-D_UNICODE
	-DUNICODE )

set (
	MyLSP_src
	src/module.def
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
	MyLSP 
	SHARED
	${MyLSP_src} )

target_link_libraries (
	MyLSP 
	Lightup )