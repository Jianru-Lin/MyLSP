#include "Global.h"

int WSPAPI
WSPDuplicateSocket(
_In_ SOCKET s,
_In_ DWORD dwProcessId,
_Out_ LPWSAPROTOCOL_INFOW lpProtocolInfo,
_Out_ LPINT lpErrno
)
{
	return WSAEINVAL;
}