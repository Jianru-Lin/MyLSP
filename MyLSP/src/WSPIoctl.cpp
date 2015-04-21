#include "Global.h"

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
)
{
	return WSAEINVAL;
}