#include <Lightup.h>
#include <stdio.h>

void printUsage()
{
	printf("MyLSPInstaller install <guid> <dll-path> <[GUID <guid>...]|[Name <name>...]|[CatalogId <id>...]>\n");
}

bool InstallDummyProvider()
{
	// TODO
	return false;
}

bool InstallProvider()
{
	// TODO
	return false;
}

int main(int argc, char **argv)
{
	// 我们需要调用 WSAStartup 函数来初始化 Winsock 库
	// 这会影响到后续的安装过程

	WSADATA data = { 0 };
	int error = WSAStartup(MAKEWORD(2, 2), &data);
	if (error != 0)
	{
		printf("Failed, WSAStartup() returned %d\n", error);
		return 1;
	}

	// 

	EasyWSCEnumProtocols enumProtocols;
	if (!enumProtocols.Invoke())
	{
		return 1;
	}

	printf("count: %d\n", enumProtocols.ProtocolListLength());
	
	for (int i = 0, len = enumProtocols.ProtocolListLength(); i < len; ++i)
	{
		LPWSAPROTOCOL_INFOW protocol = &enumProtocols.ProtocolList()[i];
		GUID guid = protocol->ProviderId;
		wprintf(L"%ws\n", Guid2Str(guid).Str());
		wprintf(L"[%d] %ws\n\n", protocol->dwCatalogEntryId, protocol->szProtocol);
	}

	return 0;
}