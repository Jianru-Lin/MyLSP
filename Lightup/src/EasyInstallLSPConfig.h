#pragma once
class EasyInstallLSPConfig
{
public:
	EasyInstallLSPConfig();
	~EasyInstallLSPConfig();

public:
	LPCTSTR	DllPath();
	GUID	ProviderGuid();
	int		BaseCatalogIdListLength();
	DWORD	BaseCatalogIdOf(int i);

private:
};

