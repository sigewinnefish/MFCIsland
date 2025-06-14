#include "pch.h"
#include "mainisland.h"
#include "appmessage.h"
#include "sheet.h"

void startprocess(CString path,HANDLE& h)
{
	SHELLEXECUTEINFO execinfo{};
	execinfo.cbSize = sizeof(execinfo);
	execinfo.fMask = execinfo::fMask;
	execinfo.hwnd = execinfo::hwnd;
	execinfo.nShow = execinfo::nShow;
	execinfo.lpFile = path;
    BOOL started = ShellExecuteEx(&execinfo);
    h = execinfo.hProcess;
}

static HANDLE loaddll(LPCWSTR dllpath)
{
    HANDLE h;
    h = LoadLibrary(dllpath);
    return h;
}

static BOOL IsMainWindow(HWND handle)
{
    return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
}

static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {

    HandleData& data = *(HandleData*)lParam;
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (data.pid != pid || !IsMainWindow(hwnd))
        return TRUE;

    data.hwnd = hwnd;
    return FALSE;

}


static DWORD findtid(HandleData hd)
{
    EnumWindows(EnumWindowsProc, (LPARAM)&hd);
    DWORD tid = GetWindowThreadProcessId(_Notnull_ hd.hwnd, 0);
    return tid;
}

void sethook(HANDLE h)
{
    DWORD tid;
    
    if (!loaddll(L"Snap.Hutao.dll"))
    {
        AfxMessageBox(L"Snap.Hutao.dll����ʧ�ܣ���������", MB_OK | MB_ICONERROR);
        return;
    }

    HANDLE dh = loaddll(L"Snap.Hutao.UnlockerIsland.dll");
    if (!dh)
    {
        AfxMessageBox(L"Snap.Hutao.UnlockerIsland.dll����ʧ��", MB_OK | MB_ICONERROR);
        return;
    }

    FARPROC pIslandGetWindowHook = GetProcAddress((HMODULE)dh, "IslandGetWindowHook"); //��ȡ������ַ
    HRESULT (WINAPI *IslandGetWindowHook)(HOOKPROC*) = (HRESULT(WINAPI *)(HOOKPROC*))pIslandGetWindowHook; // ���ݵ�ַתΪdll�ĺ���
    HOOKPROC hp;
    IslandGetWindowHook(&hp); //����dll�ĺ���
    DWORD pid = GetProcessId(h); //ͨ�����̾����ȡ����id

    Sleep(5000);

    HandleData hd{ pid,0 };
    tid = findtid(hd);
    HHOOK hhook = SetWindowsHookExW(WH_GETMESSAGE, hp, (HMODULE)dh, tid);

    Sleep(5000); //Ԥ��ʱ��SetWindowsHookExW  ����hook����

}

LPVOID filemapping()
{
    HANDLE h = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, ISLAND_ENVIRONMENT_NAME);

    if (h == NULL)
    {
        h = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_EXECUTE_READWRITE, 0, 1024, ISLAND_ENVIRONMENT_NAME);

    }
    LPVOID pMapViewOfFile = MapViewOfFile(_Notnull_ h, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
    return pMapViewOfFile;
}

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
    HANDLE h{};
    startprocess(((CString*)lpParameter)->GetString(), h);
    SendMessage(((sheet*)(AfxGetApp()->GetMainWnd()))->p1.m_hWnd, WM_GAME_RUNNING, 0, 0);
    sethook(h);
    WaitForSingleObject(h, INFINITE);
    SendMessage(((sheet*)(AfxGetApp()->GetMainWnd()))->p1.m_hWnd, WM_GAME_END, 0 ,0);
    return 0;
}