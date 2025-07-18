#include "pch.h"
#include "logserver.h"
#include "appmessage.h"

void processLogMessage(WCHAR* pchRequest, DWORD* cbBytesRead)
{
	SendMessage(((sheet*)(AfxGetApp()->GetMainWnd()))->p2.m_hWnd, WM_LOGSENT, (WPARAM)pchRequest, (LPARAM)cbBytesRead);
	//必须为sendmessage 否则大量输入会导致错误
}

int LogServer() {

	while (true)
	{
		HANDLE hPipe; // 管道句柄
		LPCTSTR lpszPipename = L"\\\\.\\pipe\\mfcislandpipe";
		const int BUFSIZE = 512; // 缓冲区大小
		BOOL fConnected = FALSE;

		hPipe = CreateNamedPipe(
			lpszPipename,             // pipe name 
			PIPE_ACCESS_INBOUND,       // 管道中的数据流仅从客户端到服务器。
			PIPE_TYPE_MESSAGE |       // message type pipe 
			PIPE_READMODE_MESSAGE |   // message-read mode 
			PIPE_WAIT | // blocking mode 
			PIPE_REJECT_REMOTE_CLIENTS, //来自远程客户端的连接会自动被拒绝。               
			PIPE_UNLIMITED_INSTANCES, // max. instances  
			BUFSIZE,                  // output buffer size 
			BUFSIZE,                  // input buffer size 
			0,                        // client time-out 值为零将导致默认超时 50 毫秒
			NULL);                    // default security attribute 


		if (hPipe == INVALID_HANDLE_VALUE)
		{
			_tprintf(TEXT("CreateNamedPipe failed, GLE=%d.\n"), GetLastError());
			return -1;
		}

		fConnected = ConnectNamedPipe(hPipe, NULL) ?
			TRUE : (GetLastError() == ERROR_PIPE_CONNECTED); //使命名管道服务器进程能够等待客户端进程连接到命名管道的实例。

		if (fConnected)
		{
			BOOL fSuccess = FALSE;
			WCHAR* pchRequest = new WCHAR[BUFSIZE];
			ZeroMemory(pchRequest, BUFSIZE * sizeof(WCHAR));
			DWORD cbBytesRead = 0; // ReadFile 返回读取的字节

			while (1)
			{

				fSuccess = ReadFile(
					hPipe,        // 管道句柄
					pchRequest,    // buffer to receive data 
					BUFSIZE * sizeof(WCHAR), // size of buffer 
					&cbBytesRead, // 指向使用同步 hFile 参数时接收读取的字节数的变量的指针。
					NULL);        // not overlapped I/O 

				if (!fSuccess || cbBytesRead == 0)
				{
					if (GetLastError() == ERROR_BROKEN_PIPE)
					{
						//AfxMessageBox(L"客户端已断开连接。");
						break;
					}
					break;
				}

				processLogMessage(pchRequest, &cbBytesRead);

			}

			delete[] pchRequest;
		}

		FlushFileBuffers(hPipe);
		DisconnectNamedPipe(hPipe);
		CloseHandle(hPipe);
	}

}


DWORD WINAPI LogServerProc(LPVOID lpParameter)
{
	LogServer();
	return 0;
}