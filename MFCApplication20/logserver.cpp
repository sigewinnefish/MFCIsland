#include "pch.h"
#include "logserver.h"



void processLogMessage(WCHAR* pchRequest, DWORD* cbBytesRead)
{
    wprintf(L"%s",pchRequest);
}

int LogServer() {

    while (true)
    {
        HANDLE hPipe; // �ܵ����
        LPCTSTR lpszPipename = L"\\\\.\\pipe\\mfcislandpipe";
        const int BUFSIZE = 1024; // ��������С
        BOOL fConnected = FALSE;

        hPipe = CreateNamedPipe(
            lpszPipename,             // pipe name 
            PIPE_ACCESS_INBOUND,       // �ܵ��е����������ӿͻ��˵���������
            PIPE_TYPE_MESSAGE |       // message type pipe 
            PIPE_READMODE_MESSAGE |   // message-read mode 
            PIPE_WAIT | // blocking mode 
            PIPE_REJECT_REMOTE_CLIENTS, //����Զ�̿ͻ��˵����ӻ��Զ����ܾ���               
            PIPE_UNLIMITED_INSTANCES, // max. instances  
            BUFSIZE,                  // output buffer size 
            BUFSIZE,                  // input buffer size 
            0,                        // client time-out ֵΪ�㽫����Ĭ�ϳ�ʱ 50 ����
            NULL);                    // default security attribute 

        if (hPipe == INVALID_HANDLE_VALUE)
        {
            _tprintf(TEXT("CreateNamedPipe failed, GLE=%d.\n"), GetLastError());
            return -1;
        }

        fConnected = ConnectNamedPipe(hPipe, NULL) ?
            TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

        if (fConnected)
        {
            BOOL fSuccess = FALSE;
            WCHAR* pchRequest = new WCHAR[BUFSIZE];
            DWORD cbBytesRead = 0; // ReadFile ���ض�ȡ���ֽ�

            while (1)
            {

                fSuccess = ReadFile(
                    hPipe,        // �ܵ����
                    pchRequest,    // buffer to receive data 
                    BUFSIZE * sizeof(WCHAR), // size of buffer 
                    &cbBytesRead, // ָ��ʹ��ͬ�� hFile ����ʱ���ն�ȡ���ֽ����ı�����ָ�롣
                    NULL);        // not overlapped I/O 


                processLogMessage(pchRequest, &cbBytesRead);


                if (!fSuccess || cbBytesRead == 0)
                {
                    if (GetLastError() == ERROR_BROKEN_PIPE)
                    {
						AfxMessageBox(L"�ͻ����ѶϿ����ӡ�");
                        break;
                    }
                    break;
                }

            }

            delete[] pchRequest;
        }

        FlushFileBuffers(hPipe);
        DisconnectNamedPipe(hPipe);
        CloseHandle(hPipe);

        if (true)
        {
            return 0;
        }

    }

}
    

DWORD WINAPI LogServerProc(LPVOID lpParameter)
{
    LogServer();
    return 0;
}