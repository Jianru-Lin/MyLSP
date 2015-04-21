#include "Global.h"

int WSPAPI
WSPSendDisconnect(
_In_ SOCKET s,
_In_opt_ LPWSABUF lpOutboundDisconnectData,
_Out_ LPINT lpErrno
)
{
	return WSAEINVAL;
}