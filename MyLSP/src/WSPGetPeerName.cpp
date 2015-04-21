#include "Global.h"

int WSPAPI
WSPGetPeerName(
_In_ SOCKET s,
_Out_writes_bytes_to_(*namelen, *namelen) struct sockaddr FAR * name,
_Inout_ LPINT namelen,
_Out_ LPINT lpErrno
)
{
	return WSAEINVAL;
}