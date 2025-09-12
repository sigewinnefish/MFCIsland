#include "pch.h"
#include "mainisland.h"
#include "appmessage.h"
#include "sheet.h"
#include "resource.h"
#include <detours.h>
#include <pathcch.h>
#pragma comment(lib, "Pathcch.lib")

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

void injectUsingRemoteThread(HANDLE h)
{
    HMODULE haddr = GetModuleHandleW(NULL);

    //LoadLibrary(L"Snap.Hutao.UnlockerIsland.dll");
    WCHAR dllPath[MAX_PATH];
    GetModuleFileNameW(NULL, dllPath, MAX_PATH);
    PathCchRemoveFileSpec(dllPath, MAX_PATH);
    PathCchCombine(dllPath, MAX_PATH, dllPath, L"Snap.Hutao.UnlockerIsland.dll");

    DWORD pid = GetProcessId(h);
    HANDLE hOpenProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
    LPVOID ptr = VirtualAllocEx(hOpenProcess, NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    BOOL iswrite = WriteProcessMemory(hOpenProcess, ptr, dllPath, wcslen(dllPath) * 2 + 2, NULL);
   
    HMODULE hm = GetModuleHandleW(L"kernel32.dll");
    FARPROC hp = GetProcAddress(hm, "LoadLibraryW");
    
    Sleep(10000);
    HANDLE hcrt = CreateRemoteThread(hOpenProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)hp, ptr, NULL, NULL);
    WaitForSingleObject(hcrt, INFINITE);
    BOOL free = VirtualFreeEx(hOpenProcess, ptr, 0, MEM_RELEASE);
    CloseHandle(hcrt);
    FreeLibrary(hm);


}



void sethook(HANDLE h)
{
    Sleep(8000);
    DWORD tid;
    HMODULE hkb;

	hkb = GetModuleHandleW(L"kernelbase.dll");
	TrueGetModuleHandleW = (pGetModuleHandleW)GetProcAddress(hkb,"GetModuleHandleW");
    detours_sethook(reinterpret_cast<PVOID*>(&TrueGetModuleHandleW), fGetModuleHandleW);

    HANDLE dh = loaddll(L"Snap.Hutao.UnlockerIsland.dll");
    if (!dh)
    {
        AfxMessageBox(IDS_ERROR_DLLLOAD, MB_OK | MB_ICONERROR);
        detours_unsethook(reinterpret_cast<PVOID*>(&TrueGetModuleHandleW), fGetModuleHandleW);
        return;
    }

    detours_unsethook(reinterpret_cast<PVOID*>(&TrueGetModuleHandleW), fGetModuleHandleW);

    hkb = GetModuleHandleW(L"kernelbase.dll");
    pGetCurrentPackageFamilyName TrueGetCurrentPackageFamilyName = (pGetCurrentPackageFamilyName)GetProcAddress(hkb, "GetCurrentPackageFamilyName");
    detours_sethook(reinterpret_cast<PVOID*>(&TrueGetCurrentPackageFamilyName), fGetCurrentPackageFamilyName);

    FARPROC pDllGetWindowsHookForHutao = GetProcAddress((HMODULE)dh, "DllGetWindowsHookForHutao"); //获取函数地址
    HRESULT (WINAPI * DllGetWindowsHookForHutao)(HOOKPROC*) = (HRESULT(WINAPI *)(HOOKPROC*))pDllGetWindowsHookForHutao; // 根据地址转为dll的函数
    HOOKPROC hp;
    DllGetWindowsHookForHutao(&hp); //调用dll的函数

    detours_unsethook(reinterpret_cast<PVOID*>(&TrueGetCurrentPackageFamilyName), fGetCurrentPackageFamilyName);

    DWORD pid = GetProcessId(h); //通过进程句柄获取进程id

    HandleData hd{ pid,0 };

    while (true)
    {
        tid = findtid(hd);
        Sleep(50);
        if (tid)
        {
            break;
        }
    }
    
	ENSURE(tid != 0);
    HHOOK hhook = SetWindowsHookExW(WH_GETMESSAGE, hp, (HMODULE)dh, tid);
    PostThreadMessageW(tid, 0, 0, 0);
    Sleep(5000); //预留时间SetWindowsHookExW  否则hook不到
    UnhookWindowsHookEx(hhook);
    FreeLibrary((HMODULE)dh);

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
    //injectUsingRemoteThread(h);
    WaitForSingleObject(h, INFINITE);
    PostMessage(((sheet*)(AfxGetApp()->GetMainWnd()))->p1.m_hWnd, WM_GAME_END, 0 ,0);
    return 0;
}