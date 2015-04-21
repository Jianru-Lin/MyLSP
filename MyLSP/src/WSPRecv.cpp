#include "Global.h"

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
)
{
	return WSAEINVAL;
}