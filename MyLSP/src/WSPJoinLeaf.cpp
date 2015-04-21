#include "Global.h"

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
)
{
	return WSAEINVAL;
}