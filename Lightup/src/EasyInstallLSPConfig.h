#pragma once
class EasyInstallLSPConfig
{
public:
	EasyInstallLSPConfig();
	EasyInstallLSPConfig(LPCTSTR fileName);
	~EasyInstallLSPConfig();

public:
	LPCTSTR	GetDllPath()								const;
	GUID	GetProviderGuid()							const;
	int		GetBaseCatalogIdListLength()				const;
	bool	GetBaseCatalogIdOf(int i, DWORD* result)	const;

private:
	Buffer	dllPathBuffer;
	GUID	providerGuid;
	int		catalogIdListLength;
	int		catalogIdList[MAX_PROTOCOL_CHAIN];
};

