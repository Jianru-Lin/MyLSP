#include "Global.h"
#include "WSP.h"

bool versionNegotiation(WORD wVersionRequested, LPWSPDATA lpWSPData)
{
	// TODO check wVersionRequested

	// set lpWSPData, support 2.2 only

	lpWSPData->wVersion = MAKEWORD(2, 2);
	lpWSPData->wHighVersion = lpWSPData->wVersion;
	
	return true;
}

void fillProcTable(LPWSPPROC_TABLE lpProcTable)
{
	lpProcTable->lpWSPAccept				= WSPAccept;
	lpProcTable->lpWSPAddressToString		= WSPAddressToString;
	lpProcTable->lpWSPAsyncSelect			= WSPAsyncSelect;
	lpProcTable->lpWSPBind					= WSPBind;
	lpProcTable->lpWSPCancelBlockingCall	= WSPCancelBlockingCall;
	lpProcTable->lpWSPCleanup				= WSPCleanup;
	lpProcTable->lpWSPCloseSocket			= WSPCloseSocket;
	lpProcTable->lpWSPConnect				= WSPConnect;
	lpProcTable->lpWSPDuplicateSocket		= WSPDuplicateSocket;
	lpProcTable->lpWSPEnumNetworkEvents		= WSPEnumNetworkEvents;
	lpProcTable->lpWSPEventSelect			= WSPEventSelect;
	lpProcTable->lpWSPGetOverlappedResult	= WSPGetOverlappedResult;
	lpProcTable->lpWSPGetPeerName			= WSPGetPeerName;
	lpProcTable->lpWSPGetSockName			= WSPGetSockName;
	lpProcTable->lpWSPGetSockOpt			= WSPGetSockOpt;
	lpProcTable->lpWSPGetQOSByName			= WSPGetQOSByName;
	lpProcTable->lpWSPIoctl					= WSPIoctl;
	lpProcTable->lpWSPJoinLeaf				= WSPJoinLeaf;
	lpProcTable->lpWSPListen				= WSPListen;
	lpProcTable->lpWSPRecv					= WSPRecv;
	lpProcTable->lpWSPRecvDisconnect		= WSPRecvDisconnect;
	lpProcTable->lpWSPRecvFrom				= WSPRecvFrom;
	lpProcTable->lpWSPSelect				= WSPSelect;
	lpProcTable->lpWSPSend					= WSPSend;
	lpProcTable->lpWSPSendDisconnect		= WSPSendDisconnect;
	lpProcTable->lpWSPSendTo				= WSPSendTo;
	lpProcTable->lpWSPSetSockOpt			= WSPSetSockOpt;
	lpProcTable->lpWSPShutdown				= WSPShutdown;
	lpProcTable->lpWSPSocket				= WSPSocket;
	lpProcTable->lpWSPStringToAddress		= WSPStringToAddress;
}

int WSPAPI WSPStartup(
		WORD wVersionRequested,
		LPWSPDATA lpWSPData,
		LPWSAPROTOCOL_INFO lpProtocolInfo,
		WSPUPCALLTABLE UpcallTable,
		LPWSPPROC_TABLE lpProcTable
	)
{
	// 使用临界区来保护当前函数执行时不会因为重入而出错

	g.Enter();

	// 由于 WSPStartup() 和 WSPCleanup() 可能会被反复调用多次
	// 此处使用引用计数来保证资源构建和销毁时的正确性

	g.IncRefCount();

	// 不管当前函数是第几次被调用，总是更新上调函数表，这是 MSDN 要求的
	// https://msdn.microsoft.com/en-us/library/windows/desktop/ms742296(v=vs.85).aspx
	
	g.SetUpcallTable(UpcallTable);

	if (g.GetRefCount() > 1) {
		// 已经构建过，无需重复执行
		g.Leave();
		return 0;
	}

	// 尚未构建过，接下来有多步操作，不过首先应完成版本协商

	if (!versionNegotiation(wVersionRequested, lpWSPData)) {
		// 协商失败，无法满足调用者的需求
		g.Leave();
		return WSAVERNOTSUPPORTED;
	}

	// 填写例程实现表
	
	fillProcTable(lpProcTable);

	// 成功了，一切就绪

	return 0;
}