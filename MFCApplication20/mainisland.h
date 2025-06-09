#pragma once

#include "framework.h"


constexpr PCWSTR ISLAND_ENVIRONMENT_NAME = L"4F3E8543-40F7-4808-82DC-21E48A6037A7";

struct HandleData
{
    DWORD pid;
    HWND hwnd;
};

enum struct IslandState : int
{
    None = 0,
    Error = 1,
    Started = 2,
    Stopped = 3,
};

struct FunctionOffsets
{
    UINT32 MickeyWonder;
    UINT32 MickeyWonderPartner;
    UINT32 MickeyWonderPartner2;
    UINT32 SetFieldOfView;
    UINT32 SetEnableFogRendering;
    UINT32 SetTargetFrameRate;
    UINT32 OpenTeam;
    UINT32 OpenTeamPageAccordingly;
    UINT32 CheckCanEnter;
    UINT32 SetupQuestBanner;
    UINT32 FindGameObject;
    UINT32 SetActive;
    UINT32 EventCameraMove;
    UINT32 ShowOneDamageTextEx;
    UINT32 SwitchInputDeviceToTouchScreen;
    UINT32 MickeyWonderCombineEntry;
    UINT32 MickeyWonderCombineEntryPartner;
};

struct IslandEnvironment
{
    enum IslandState State;
    DWORD LastError;

    FunctionOffsets FunctionOffsets;

    BOOL EnableSetFieldOfView;
    FLOAT FieldOfView;
    BOOL FixLowFovScene;
    BOOL DisableFog;
    BOOL EnableSetTargetFrameRate;
    INT32 TargetFrameRate;
    BOOL RemoveOpenTeamProgress;
    BOOL HideQuestBanner;
    BOOL DisableEventCameraMove;
    BOOL DisableShowDamageText;
    BOOL UsingTouchScreen;
    BOOL RedirectCombineEntry;
};

namespace execinfo
{
    //constexpr DWORD cbSize;               // in, required, sizeof of this structure
    constexpr ULONG fMask = SEE_MASK_NOCLOSEPROCESS;                // in, SEE_MASK_XXX values
    constexpr HWND hwnd = NULL;                  // in, optional
    //constexpr LPCWSTR  lpVerb;            // in, optional when unspecified the default verb is choosen
    //constexpr LPCWSTR  lpFile;            // in, either this value or lpIDList must be specified
    constexpr LPCWSTR  lpParameters = NULL;      // in, optional
    //constexpr LPCWSTR  lpDirectory;       // in, optional
    constexpr int nShow = 1;                  // in, required
    //constexpr HINSTANCE hInstApp;         // out when SEE_MASK_NOCLOSEPROCESS is specified


};

void startprocess(CString path, HANDLE& h);
void sethook(HANDLE h);
LPVOID filemapping();
DWORD WINAPI ThreadProc(LPVOID lpParameter);