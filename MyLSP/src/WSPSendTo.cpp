#include "Global.h"

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
)
{
	return WSAEINVAL;
}