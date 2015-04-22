#pragma once
class EasyWSCEnumProtocols
{
public:
	EasyWSCEnumProtocols();
	~EasyWSCEnumProtocols();

public:
	bool Invoke(LPINT lpiProtocols = NULL);

public:
	LPWSAPROTOCOL_INFOW ProtocolList();
	int ProtocolListLength();

private:
	Buffer *protocolListBuffer;
	int protocolListLength;
};

