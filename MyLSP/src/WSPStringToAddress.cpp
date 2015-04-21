#include "Global.h"

INT WSPAPI
WSPStringToAddress(
_In_ LPWSTR AddressString,
_In_ INT AddressFamily,
_In_opt_ LPWSAPROTOCOL_INFOW lpProtocolInfo,
_Out_writes_bytes_to_(*lpAddressLength, *lpAddressLength) LPSOCKADDR lpAddress,
_Inout_ LPINT lpAddressLength,
_Out_ LPINT lpErrno
)

{
	return WSAEINVAL;
}