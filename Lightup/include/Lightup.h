#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <WS2spi.h>

// GUIDstr use this header
#include <Rpc.h>
#pragma comment(lib, "Rpcrt4.lib")

#include "../src/Buffer.h"
#include "../src/CriticalSection.h"
#include "../src/EasyWSCEnumProtocols.h"
#include "../src/EasyInstallLSP.h"
#include "../src/Guid2Str.h"