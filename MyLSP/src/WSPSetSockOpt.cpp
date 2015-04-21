#include "Global.h"

int WSPAPI
WSPSetSockOpt(
_In_ SOCKET s,
_In_ int level,
_In_ int optname,
_In_reads_bytes_opt_(optlen) const char FAR * optval,
_In_ int optlen,
_Out_ LPINT lpErrno
)
{
	return WSAEINVAL;
}