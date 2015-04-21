#include "Global.h"

SOCKET WSPAPI
WSPAccept(
_In_ SOCKET s,
_Out_writes_bytes_to_opt_(*addrlen, *addrlen) struct sockaddr FAR * addr,
_Inout_opt_ LPINT addrlen,
_In_opt_ LPCONDITIONPROC lpfnCondition,
_In_opt_ DWORD_PTR dwCallbackData,
_Out_ LPINT lpErrno
)
{
	return WSAEINVAL;
}