#pragma once
class EasyInstallLSP
{
public:
	EasyInstallLSP();
	~EasyInstallLSP();

public:
	bool Invoke(LPGUID lpProviderId, const WCHAR *lpszProviderDllPath);
};

