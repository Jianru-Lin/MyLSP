#pragma once

SOCKET WSPAPI
WSPAccept(
_In_ SOCKET s,
_Out_writes_bytes_to_opt_(*addrlen, *addrlen) struct sockaddr FAR * addr,
_Inout_opt_ LPINT addrlen,
_In_opt_ LPCONDITIONPROC lpfnCondition,
_In_opt_ DWORD_PTR dwCallbackData,
_Out_ LPINT lpErrno
);

INT WSPAPI
WSPAddressToString(
_In_reads_bytes_(dwAddressLength) LPSOCKADDR lpsaAddress,
_In_ DWORD dwAddressLength,
_In_opt_ LPWSAPROTOCOL_INFOW lpProtocolInfo,
_Out_writes_to_(*lpdwAddressStringLength, *lpdwAddressStringLength) LPWSTR lpszAddressString,
_Inout_ LPDWORD lpdwAddressStringLength,
_Out_ LPINT lpErrno
);

int WSPAPI
WSPAsyncSelect(
_In_ SOCKET s,
_In_ HWND hWnd,
_In_ unsigned int wMsg,
_In_ long lEvent,
_Out_ LPINT lpErrno
);

int WSPAPI
WSPBind(
_In_ SOCKET s,
_In_reads_bytes_(namelen) const struct sockaddr FAR * name,
_In_ int namelen,
_Out_ LPINT lpErrno
);

int WSPAPI
WSPCancelBlockingCall(
_Out_ LPINT lpErrno
);

int WSPAPI
WSPCleanup(
_Out_ LPINT lpErrno
);

int WSPAPI
WSPCloseSocket(
_In_ SOCKET s,
_Out_ LPINT lpErrno
);

int WSPAPI
WSPConnect(
_In_ SOCKET s,
_In_reads_bytes_(namelen) const struct sockaddr FAR * name,
_In_ int namelen,
_In_opt_ LPWSABUF lpCallerData,
_Out_opt_ LPWSABUF lpCalleeData,
_In_opt_ LPQOS lpSQOS,
_In_opt_ LPQOS lpGQOS,
_Out_ LPINT lpErrno
);

int WSPAPI
WSPDuplicateSocket(
_In_ SOCKET s,
_In_ DWORD dwProcessId,
_Out_ LPWSAPROTOCOL_INFOW lpProtocolInfo,
_Out_ LPINT lpErrno
);

int WSPAPI
WSPEnumNetworkEvents(
_In_ SOCKET s,
_In_ WSAEVENT hEventObject,
_Out_ LPWSANETWORKEVENTS lpNetworkEvents,
_Out_ LPINT lpErrno
);

int WSPAPI
WSPEventSelect(
_In_ SOCKET s,
_In_opt_ WSAEVENT hEventObject,
_In_ long lNetworkEvents,
_Out_ LPINT lpErrno
);

BOOL WSPAPI
WSPGetOverlappedResult(
_In_ SOCKET s,
_In_ LPWSAOVERLAPPED lpOverlapped,
_Out_ LPDWORD lpcbTransfer,
_In_ BOOL fWait,
_Out_ LPDWORD lpdwFlags,
_Out_ LPINT lpErrno
);

int WSPAPI
WSPGetPeerName(
_In_ SOCKET s,
_Out_writes_bytes_to_(*namelen, *namelen) struct sockaddr FAR * name,
_Inout_ LPINT namelen,
_Out_ LPINT lpErrno
);

int WSPAPI
WSPGetSockName(
_In_ SOCKET s,
_Out_writes_bytes_to_(*namelen, *namelen) struct sockaddr FAR * name,
_Inout_ LPINT namelen,
_Out_ LPINT lpErrno
);

int WSPAPI
WSPGetSockOpt(
_In_ SOCKET s,
_In_ int level,
_In_ int optname,
_Out_writes_bytes_(*optlen) char FAR * optval,
_Inout_ LPINT optlen,
_Out_ LPINT lpErrno
);

BOOL WSPAPI
WSPGetQOSByName(
_In_ SOCKET s,
_In_ LPWSABUF lpQOSName,
_Out_ LPQOS lpQOS,
_Out_ LPINT lpErrno
);

int WSPAPI
WSPIoctl(
_In_ SOCKET s,
_In_ DWORD dwIoControlCode,
_In_reads_bytes_opt_(cbInBuffer) LPVOID lpvInBuffer,
_In_ DWORD cbInBuffer,
_Out_writes_bytes_to_opt_(cbOutBuffer, *lpcbBytesReturned) LPVOID lpvOutBuffer,
_In_ DWORD cbOutBuffer,
_Out_ LPDWORD lpcbBytesReturned,
_Inout_opt_ LPWSAOVERLAPPED lpOverlapped,
_In_opt_ LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
_In_opt_ LPWSATHREADID lpThreadId,
_Out_ LPINT lpErrno
);

SOCKET WSPAPI
WSPJoinLeaf(
_In_ SOCKET s,
_In_reads_bytes_(namelen) const struct sockaddr FAR * name,
_In_ int namelen,
_In_opt_ LPWSABUF lpCallerData,
_Out_opt_ LPWSABUF lpCalleeData,
_In_opt_ LPQOS lpSQOS,
_In_opt_ LPQOS lpGQOS,
_In_ DWORD dwFlags,
_Out_ LPINT lpErrno
);

int WSPAPI
WSPListen(
_In_ SOCKET s,
_In_ int backlog,
_Out_ LPINT lpErrno
);

int WSPAPI
WSPRecv(
_In_ SOCKET s,
_In_reads_(dwBufferCount) LPWSABUF lpBuffers,
_In_ DWORD dwBufferCount,
_Out_opt_ LPDWORD lpNumberOfBytesRecvd,
_Inout_ LPDWORD lpFlags,
_Inout_opt_ LPWSAOVERLAPPED lpOverlapped,
_In_opt_ LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
_In_opt_ LPWSATHREADID lpThreadId,
_In_ LPINT lpErrno
);

int WSPAPI
WSPRecvDisconnect(
_In_ SOCKET s,
_In_opt_ LPWSABUF lpInboundDisconnectData,
_Out_ LPINT lpErrno
);

int WSPAPI
WSPRecvFrom(
_In_ SOCKET s,
_In_reads_(dwBufferCount) LPWSABUF lpBuffers,
_In_ DWORD dwBufferCount,
_Out_opt_ LPDWORD lpNumberOfBytesRecvd,
_Inout_ LPDWORD lpFlags,
_Out_writes_bytes_to_opt_(*lpFromlen, *lpFromlen) struct sockaddr FAR * lpFrom,
_Inout_opt_ LPINT lpFromlen,
_Inout_opt_ LPWSAOVERLAPPED lpOverlapped,
_In_opt_ LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
_In_opt_ LPWSATHREADID lpThreadId,
_Out_ LPINT lpErrno
);

int WSPAPI
WSPSelect(
_In_ int nfds,
_Inout_opt_ fd_set FAR * readfds,
_Inout_opt_ fd_set FAR * writefds,
_Inout_opt_ fd_set FAR * exceptfds,
_In_opt_ const struct timeval FAR * timeout,
_Out_ LPINT lpErrno
);

int WSPAPI
WSPSend(
_In_ SOCKET s,
_In_reads_(dwBufferCount) LPWSABUF lpBuffers,
_In_ DWORD dwBufferCount,
_Out_opt_ LPDWORD lpNumberOfBytesSent,
_In_ DWORD dwFlags,
_Inout_opt_ LPWSAOVERLAPPED lpOverlapped,
_In_opt_ LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
_In_opt_ LPWSATHREADID lpThreadId,
_Out_ LPINT lpErrno
);

int WSPAPI
WSPSendDisconnect(
_In_ SOCKET s,
_In_opt_ LPWSABUF lpOutboundDisconnectData,
_Out_ LPINT lpErrno
);

int WSPAPI
WSPSendTo(
_In_ SOCKET s,
_In_reads_(dwBufferCount) LPWSABUF lpBuffers,
_In_ DWORD dwBufferCount,
_Out_opt_ LPDWORD lpNumberOfBytesSent,
_In_ DWORD dwFlags,
_In_reads_bytes_opt_(iTolen) const struct sockaddr FAR * lpTo,
_In_ int iTolen,
_Inout_opt_ LPWSAOVERLAPPED lpOverlapped,
_In_opt_ LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
_In_opt_ LPWSATHREADID lpThreadId,
_Out_ LPINT lpErrno
);

int WSPAPI
WSPSetSockOpt(
_In_ SOCKET s,
_In_ int level,
_In_ int optname,
_In_reads_bytes_opt_(optlen) const char FAR * optval,
_In_ int optlen,
_Out_ LPINT lpErrno
);

int WSPAPI
WSPShutdown(
_In_ SOCKET s,
_In_ int how,
_Out_ LPINT lpErrno
);

SOCKET WSPAPI
WSPSocket(
_In_ int af,
_In_ int type,
_In_ int protocol,
_In_opt_ LPWSAPROTOCOL_INFOW lpProtocolInfo,
_In_ GROUP g,
_In_ DWORD dwFlags,
_Out_ LPINT lpErrno
);

INT WSPAPI
WSPStringToAddress(
_In_ LPWSTR AddressString,
_In_ INT AddressFamily,
_In_opt_ LPWSAPROTOCOL_INFOW lpProtocolInfo,
_Out_writes_bytes_to_(*lpAddressLength, *lpAddressLength) LPSOCKADDR lpAddress,
_Inout_ LPINT lpAddressLength,
_Out_ LPINT lpErrno
);
