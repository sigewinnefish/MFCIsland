#pragma once

#include <windows.h> 

int LogServer();

void processLogMessage(WCHAR* pchRequest, DWORD* cbBytesRead);

DWORD WINAPI LogServerProc(LPVOID lpParameter);
