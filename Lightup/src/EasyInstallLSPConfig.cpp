#include "../include/Lightup.h"

EasyInstallLSPConfig::EasyInstallLSPConfig()
{

}

EasyInstallLSPConfig::EasyInstallLSPConfig(LPCTSTR fileName)
{

}

EasyInstallLSPConfig::~EasyInstallLSPConfig()
{

}

LPCTSTR EasyInstallLSPConfig::GetDllPath() const
{
	return (LPCTSTR)this->dllPathBuffer.Adress();
}

GUID EasyInstallLSPConfig::GetProviderGuid() const
{
	return this->providerGuid;
}

int EasyInstallLSPConfig::GetBaseCatalogIdListLength() const
{
	return this->catalogIdListLength;
}

bool EasyInstallLSPConfig::GetBaseCatalogIdOf(int i, DWORD* result) const
{
	if (i < 0 || i >= this->catalogIdListLength || result == NULL)
	{
		return false;
	}
	else
	{
		*result = this->catalogIdList[i];
		return true;
	}
}
