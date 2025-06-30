#include "pch.h"
#include "mainisland.h"
#include "appmessage.h"
#include "sheet.h"
#include <detours.h>


typedef HMODULE(WINAPI* pGetModuleHandleW)(LPCWSTR);
typedef LONG(WINAPI* pGetCurrentPackageFamilyName)(UINT32*, PWSTR);
static pGetModuleHandleW TrueGetModuleHandleW = nullptr;

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

void detours_sethook(PVOID* ppPointer,PVOID pDetourh)
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(ppPointer, pDetourh);
    DetourTransactionCommit();
}

void detours_unsethook(PVOID* ppPointer, PVOID pDetourh)
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(ppPointer, pDetourh);
    DetourTransactionCommit();
}

static LONG WINAPI fGetCurrentPackageFamilyName(_Inout_ UINT32* packageFamilyNameLength, _Out_writes_opt_(*packageFamilyNameLength) PWSTR packageFamilyName)
{
    return 0;
}

static HMODULE WINAPI fGetModuleHandleW(_In_opt_ LPCWSTR lpModuleName)
{
    if (lpModuleName != nullptr)
    {
        if (wcscmp(lpModuleName, L"Snap.Hutao.dll") == 0)
        {
            return reinterpret_cast<HMODULE>(1);
        }
    }

	return TrueGetModuleHandleW(lpModuleName);
}

void sethook(HANDLE h)
{
    DWORD tid;
    HMODULE hkb;

    
	hkb = GetModuleHandleW(L"kernelbase.dll");
	TrueGetModuleHandleW = (pGetModuleHandleW)GetProcAddress(hkb,"GetModuleHandleW");
    detours_sethook(reinterpret_cast<PVOID*>(&TrueGetModuleHandleW), fGetModuleHandleW);

    HANDLE dh = loaddll(L"Snap.Hutao.UnlockerIsland.dll");
    if (!dh)
    {
        AfxMessageBox(L"Snap.Hutao.UnlockerIsland.dll����ʧ��", MB_OK | MB_ICONERROR);
        return;
    }

    detours_unsethook(reinterpret_cast<PVOID*>(&TrueGetModuleHandleW), fGetModuleHandleW);

    hkb = GetModuleHandleW(L"kernelbase.dll");
    pGetCurrentPackageFamilyName TrueGetCurrentPackageFamilyName = (pGetCurrentPackageFamilyName)GetProcAddress(hkb, "GetCurrentPackageFamilyName");
    detours_sethook(reinterpret_cast<PVOID*>(&TrueGetCurrentPackageFamilyName), fGetCurrentPackageFamilyName);

    FARPROC pDllGetWindowsHookForHutao = GetProcAddress((HMODULE)dh, "DllGetWindowsHookForHutao"); //��ȡ������ַ
    HRESULT (WINAPI * DllGetWindowsHookForHutao)(HOOKPROC*) = (HRESULT(WINAPI *)(HOOKPROC*))pDllGetWindowsHookForHutao; // ���ݵ�ַתΪdll�ĺ���
    HOOKPROC hp;
    DllGetWindowsHookForHutao(&hp); //����dll�ĺ���

    detours_unsethook(reinterpret_cast<PVOID*>(&TrueGetCurrentPackageFamilyName), fGetCurrentPackageFamilyName);

    DWORD pid = GetProcessId(h); //ͨ�����̾����ȡ����id

    Sleep(5000);

    HandleData hd{ pid,0 };
    tid = findtid(hd);
	ENSURE(tid != 0);
    HHOOK hhook = SetWindowsHookExW(WH_GETMESSAGE, hp, (HMODULE)dh, tid);

    Sleep(5000); //Ԥ��ʱ��SetWindowsHookExW  ����hook����

    UnhookWindowsHookEx(hhook);

}

LPVOID filemapping(PCWSTR NAME)
{
    HANDLE h = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, NAME);

    if (h == NULL)
    {
        h = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_EXECUTE_READWRITE, 0, 1024, NAME);

    }
    LPVOID pMapViewOfFile = MapViewOfFile(_Notnull_ h, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
    return pMapViewOfFile;
}

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
    HANDLE h{};
    startprocess(((CString*)lpParameter)->GetString(), h);
    PostMessage(((sheet*)(AfxGetApp()->GetMainWnd()))->p1.m_hWnd, WM_GAME_RUNNING, 0, 0);
    sethook(h);
    WaitForSingleObject(h, INFINITE);
    PostMessage(((sheet*)(AfxGetApp()->GetMainWnd()))->p1.m_hWnd, WM_GAME_END, 0 ,0);
    return 0;
}