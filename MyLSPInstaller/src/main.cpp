#include <Lightup.h>
#include <stdio.h>

int main()
{
	EasyWSCEnumProtocols enumProtocols;
	if (!enumProtocols.Invoke())
	{
		return 1;
	}

	printf("count: %d\n", enumProtocols.ProtocolListLength());
	
	for (int i = 0, len = enumProtocols.ProtocolListLength(); i < len; ++i)
	{
		LPWSAPROTOCOL_INFOW protocol = &enumProtocols.ProtocolList()[i];
		wprintf(L"[%d] %ws\n", protocol->dwCatalogEntryId, protocol->szProtocol);
	}

	return 0;
}