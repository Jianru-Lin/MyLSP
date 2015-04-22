#include "../include/Lightup.h"

EasyWSCEnumProtocols::EasyWSCEnumProtocols()
{
	this->protocolListBuffer = NULL;
	this->protocolListLength = 0;
}


EasyWSCEnumProtocols::~EasyWSCEnumProtocols()
{
	if (this->protocolListBuffer != NULL) 
	{
		delete this->protocolListBuffer;
	}
}

bool EasyWSCEnumProtocols::Invoke(LPINT lpiProtocols /*= NULL*/)
{
	DWORD len = 0;
	INT error = 0;
	int ret = WSCEnumProtocols(lpiProtocols, NULL, &len, &error);
	if (ret == SOCKET_ERROR)
	{
		if (error == WSAENOBUFS)
		{
			// ok, it's time to allocate memory and retry
			this->protocolListBuffer = new Buffer(len);
			
			// watch out, memory allocation can be failed
			if (this->protocolListBuffer->Adress() == NULL)
			{
				// oops
				return false;
			}
			else
			{
				// retry
				ret = WSCEnumProtocols(lpiProtocols, (LPWSAPROTOCOL_INFOW)this->protocolListBuffer->Adress(), &len, &error);
				
				if (ret == SOCKET_ERROR)
				{
					// unbelievable, we failed again!
					// but it's ok, just return false
					return false;
				}
				else
				{
					// ok, remember the length of the list
					// and return true
					this->protocolListLength = ret;
					return true;
				}
			}
		}
		else
		{
			// unexpected error
			return false;
		}
	}
	else
	{
		// unexpected error
		return false;
	}
}

LPWSAPROTOCOL_INFOW EasyWSCEnumProtocols::ProtocolList()
{
	if (this->protocolListBuffer == NULL)
	{
		return NULL;
	}
	else
	{
		return (LPWSAPROTOCOL_INFOW)this->protocolListBuffer->Adress();
	}
}

int EasyWSCEnumProtocols::ProtocolListLength()
{
	return this->protocolListLength;
}
