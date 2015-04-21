#include "Global.h"

SOCKET WSPAPI
WSPSocket(
_In_ int af,
_In_ int type,
_In_ int protocol,
_In_opt_ LPWSAPROTOCOL_INFOW lpProtocolInfo,
_In_ GROUP g,
_In_ DWORD dwFlags,
_Out_ LPINT lpErrno
)
{
	return WSAEINVAL;
}