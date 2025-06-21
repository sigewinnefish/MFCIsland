// page1.cpp: 实现文件
//

#include "pch.h"
#include "page1.h"
#include <vector>



// page1 对话框

IMPLEMENT_DYNAMIC(page1, CPropertyPage)

page1::page1()
	: CPropertyPage(IDD_PROPPAGE_1)
	, setfov(FALSE)
	, disablefog(FALSE)
	, fov(45)
	, FixLowFovScene(FALSE)
	, fps(60)
	, HideQuestBanner(FALSE)
	, RemoveOpenTeamProgress(FALSE)
	, DisableEventCameraMove(FALSE)
	, DisableShowDamageText(FALSE)
	, RedirectCombineEntry(FALSE)
	, UsingTouchScreen(FALSE)
	, EnableSetTargetFrameRate(FALSE)
	, pIslandEnvironment(nullptr)
{

}

page1::~page1()
{
}

BOOL page1::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	pIslandEnvironment = (IslandEnvironment*)filemapping();
	gamepath = AfxGetApp()->GetProfileString(_T("Settings"), _T("GamePath"));
	noinject = AfxGetApp()->GetProfileInt(_T("Settings"), _T("NoInject"),NULL);


	setfov = AfxGetApp()->GetProfileInt(_T("Settings"), _T("SetFov"), NULL);
	disablefog = AfxGetApp()->GetProfileInt(_T("Settings"), _T("DisableFog"), NULL);
	fov = AfxGetApp()->GetProfileInt(_T("Settings"), _T("Fov"), 45);
	FixLowFovScene = AfxGetApp()->GetProfileInt(_T("Settings"), _T("FixLowFovScene"), NULL);
	EnableSetTargetFrameRate = AfxGetApp()->GetProfileInt(_T("Settings"), _T("EnableSetTargetFrameRate"), NULL);
	fps = AfxGetApp()->GetProfileInt(_T("Settings"), _T("Fps"), 60);
	HideQuestBanner = AfxGetApp()->GetProfileInt(_T("Settings"), _T("HideQuestBanner"), NULL);
	RemoveOpenTeamProgress = AfxGetApp()->GetProfileInt(_T("Settings"), _T("RemoveOpenTeamProgress"), NULL);
	DisableEventCameraMove = AfxGetApp()->GetProfileInt(_T("Settings"), _T("DisableEventCameraMove"), NULL);
	DisableShowDamageText = AfxGetApp()->GetProfileInt(_T("Settings"), _T("DisableShowDamageText"), NULL);
	RedirectCombineEntry = AfxGetApp()->GetProfileInt(_T("Settings"), _T("RedirectCombineEntry"), NULL);
	UsingTouchScreen = AfxGetApp()->GetProfileInt(_T("Settings"), _T("UsingTouchScreen"), NULL);

	pIslandEnvironment->EnableSetFieldOfView = setfov;
	pIslandEnvironment->DisableFog = disablefog;
	pIslandEnvironment->FieldOfView = static_cast<float>(fov);
	pIslandEnvironment->FixLowFovScene = FixLowFovScene;
	pIslandEnvironment->EnableSetTargetFrameRate = EnableSetTargetFrameRate;
	pIslandEnvironment->TargetFrameRate = fps;
	pIslandEnvironment->HideQuestBanner = HideQuestBanner;
	pIslandEnvironment->RemoveOpenTeamProgress = RemoveOpenTeamProgress;
	pIslandEnvironment->DisableEventCameraMove = DisableEventCameraMove;
	pIslandEnvironment->DisableShowDamageText = DisableShowDamageText;
	pIslandEnvironment->RedirectCombineEntry = RedirectCombineEntry;
	pIslandEnvironment->UsingTouchScreen = UsingTouchScreen;

	pIslandEnvironment->FunctionOffsets.MickeyWonder = AfxGetApp()->GetProfileInt(_T("FunctionOffsets"), _T("MickeyWonder"), NULL);
	pIslandEnvironment->FunctionOffsets.MickeyWonderPartner = AfxGetApp()->GetProfileInt(_T("FunctionOffsets"), _T("MickeyWonderPartner"), NULL);
	pIslandEnvironment->FunctionOffsets.MickeyWonderPartner2 = AfxGetApp()->GetProfileInt(_T("FunctionOffsets"), _T("MickeyWonderPartner2"), NULL);
	pIslandEnvironment->FunctionOffsets.SetFieldOfView = AfxGetApp()->GetProfileInt(_T("FunctionOffsets"), _T("SetFieldOfView"), NULL);
	pIslandEnvironment->FunctionOffsets.SetEnableFogRendering = AfxGetApp()->GetProfileInt(_T("FunctionOffsets"), _T("SetEnableFogRendering"), NULL);
	pIslandEnvironment->FunctionOffsets.SetTargetFrameRate = AfxGetApp()->GetProfileInt(_T("FunctionOffsets"), _T("SetTargetFrameRate"), NULL);
	pIslandEnvironment->FunctionOffsets.OpenTeam = AfxGetApp()->GetProfileInt(_T("FunctionOffsets"), _T("OpenTeam"), NULL);
	pIslandEnvironment->FunctionOffsets.OpenTeamPageAccordingly = AfxGetApp()->GetProfileInt(_T("FunctionOffsets"), _T("OpenTeamPageAccordingly"), NULL);
	pIslandEnvironment->FunctionOffsets.CheckCanEnter = AfxGetApp()->GetProfileInt(_T("FunctionOffsets"), _T("CheckCanEnter"), NULL);
	pIslandEnvironment->FunctionOffsets.SetupQuestBanner = AfxGetApp()->GetProfileInt(_T("FunctionOffsets"), _T("SetupQuestBanner"), NULL);
	pIslandEnvironment->FunctionOffsets.FindGameObject = AfxGetApp()->GetProfileInt(_T("FunctionOffsets"), _T("FindGameObject"), NULL);
	pIslandEnvironment->FunctionOffsets.SetActive = AfxGetApp()->GetProfileInt(_T("FunctionOffsets"), _T("SetActive"), NULL);
	pIslandEnvironment->FunctionOffsets.EventCameraMove = AfxGetApp()->GetProfileInt(_T("FunctionOffsets"), _T("EventCameraMove"), NULL);
	pIslandEnvironment->FunctionOffsets.ShowOneDamageTextEx = AfxGetApp()->GetProfileInt(_T("FunctionOffsets"), _T("ShowOneDamageTextEx"), NULL);
	pIslandEnvironment->FunctionOffsets.SwitchInputDeviceToTouchScreen = AfxGetApp()->GetProfileInt(_T("FunctionOffsets"), _T("SwitchInputDeviceToTouchScreen"), NULL);
	pIslandEnvironment->FunctionOffsets.MickeyWonderCombineEntry = AfxGetApp()->GetProfileInt(_T("FunctionOffsets"), _T("MickeyWonderCombineEntry"), NULL);
	pIslandEnvironment->FunctionOffsets.MickeyWonderCombineEntryPartner = AfxGetApp()->GetProfileInt(_T("FunctionOffsets"), _T("MickeyWonderCombineEntryPartner"), NULL);

	fovspin.SetRange(0, 99);
	fpsspin.SetRange(0, 720);
	radio_guofu.SetCheck(1);
	// TODO:  在此添加额外的初始化
	CheckSetfieldofviewextra();
	CheckSetfpsextra();
	UpdateData(FALSE); //把值同步到控件上
	initok = 1;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void page1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_GAMESTART, gamestartbtn);
	DDX_Control(pDX, IDC_BUTTON_SETGAMEPATH, setexepathbtn);
	DDX_Control(pDX, IDC_BUTTON_GETCONFIG, getconfigbtn);
	DDX_Control(pDX, IDC_RADIO2, radio_guofu);
	DDX_Text(pDX, IDC_EDIT_GAMEPATH, gamepath);
	DDX_Check(pDX, IDC_CHECK_NOTINJECT, noinject);
	DDX_Check(pDX, IDC_CHECK_SetFieldOfView, setfov);
	DDX_Check(pDX, IDC_CHECK_SetEnableFogRendering, disablefog);
	DDX_Text(pDX, IDC_EDIT_FOV, fov);
	//DDV_MinMaxInt(pDX, fov, 0, 99);
	DDX_Control(pDX, IDC_SPIN_FOV, fovspin);
	DDX_Check(pDX, IDC_CHECK_FixLowFovScene, FixLowFovScene);
	DDX_Check(pDX, IDC_CHECK_SetTargetFrameRate, EnableSetTargetFrameRate);
	DDX_Text(pDX, IDC_EDIT_FPS, fps);
	DDX_Control(pDX, IDC_SPIN_FPS, fpsspin);
	DDX_Check(pDX, IDC_CHECK_SetupQuestBanner, HideQuestBanner);
	DDX_Check(pDX, IDC_CHECK_OpenTeam, RemoveOpenTeamProgress);
	DDX_Check(pDX, IDC_CHECK10_DisableEventCameraMove, DisableEventCameraMove);
	DDX_Check(pDX, IDC_CHECK_ShowOneDamageTextEx, DisableShowDamageText);
	DDX_Check(pDX, IDC_CHECK_RedirectCombineEntry, RedirectCombineEntry);
	DDX_Check(pDX, IDC_CHECK_SwitchInputDeviceToTouchScreen, UsingTouchScreen);
}


BEGIN_MESSAGE_MAP(page1, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_GAMESTART, &page1::OnBnClickedButtonGamestart)
	ON_BN_CLICKED(IDC_BUTTON_SETGAMEPATH, &page1::OnBnClickedButtonSetgamedir)
	ON_BN_CLICKED(IDC_CHECK_NOTINJECT, &page1::OnBnClickedCheckNotinject)
	ON_BN_CLICKED(IDC_CHECK_SetFieldOfView, &page1::OnBnClickedCheckSetfieldofview)
	ON_BN_CLICKED(IDC_CHECK_SetEnableFogRendering, &page1::OnBnClickedCheckSetenablefogrendering)
	ON_EN_UPDATE(IDC_EDIT_FOV, &page1::OnEnUpdateEditFov)
	ON_BN_CLICKED(IDC_CHECK_FixLowFovScene, &page1::OnBnClickedCheckFixlowfovscene)
	ON_BN_CLICKED(IDC_CHECK_SetTargetFrameRate, &page1::OnBnClickedCheckSettargetframerate)
	ON_EN_UPDATE(IDC_EDIT_FPS, &page1::OnEnUpdateEditFps)
	ON_BN_CLICKED(IDC_CHECK_SetupQuestBanner, &page1::OnBnClickedCheckSetupquestbanner)
	ON_BN_CLICKED(IDC_CHECK_OpenTeam, &page1::OnBnClickedCheckOpenteam)
	ON_BN_CLICKED(IDC_CHECK10_DisableEventCameraMove, &page1::OnBnClickedCheck10Disableeventcameramove)
	ON_BN_CLICKED(IDC_CHECK_ShowOneDamageTextEx, &page1::OnBnClickedCheckShowonedamagetextex)
	ON_BN_CLICKED(IDC_CHECK_RedirectCombineEntry, &page1::OnBnClickedCheckRedirectcombineentry)
	ON_BN_CLICKED(IDC_CHECK_SwitchInputDeviceToTouchScreen, &page1::OnBnClickedCheckSwitchinputdevicetotouchscreen)
	ON_BN_CLICKED(IDC_BUTTON_GETCONFIG, &page1::OnBnClickedButtonGetconfig)
	ON_MESSAGE(WM_GAME_END, &page1::OnGameEnd)
	ON_MESSAGE(WM_GAME_RUNNING, &page1::OnGameRunning)
END_MESSAGE_MAP()


void page1::CheckSetfieldofviewextra() 
{
	if (!setfov)
	{
		GetDlgItem(IDC_CHECK_SetEnableFogRendering)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FOV)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_FOV)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_FixLowFovScene)->EnableWindow(FALSE);
		
	}
	else
	{
		GetDlgItem(IDC_CHECK_SetEnableFogRendering)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FOV)->EnableWindow(TRUE);
		GetDlgItem(IDC_SPIN_FOV)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_FixLowFovScene)->EnableWindow(TRUE);
	}
};

void page1::CheckSetfpsextra()
{
	if (!EnableSetTargetFrameRate)
	{

		GetDlgItem(IDC_EDIT_FPS)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_FPS)->EnableWindow(FALSE);


	}
	else
	{
		GetDlgItem(IDC_EDIT_FPS)->EnableWindow(TRUE);
		GetDlgItem(IDC_SPIN_FPS)->EnableWindow(TRUE);
	}
};

void page1::writeconfigtoreg()
{
	AfxGetApp()->WriteProfileInt(_T("FunctionOffsets"), _T("MickeyWonder"), pIslandEnvironment->FunctionOffsets.MickeyWonder);
	AfxGetApp()->WriteProfileInt(_T("FunctionOffsets"), _T("MickeyWonderPartner"), pIslandEnvironment->FunctionOffsets.MickeyWonderPartner);
	AfxGetApp()->WriteProfileInt(_T("FunctionOffsets"), _T("MickeyWonderPartner2"), pIslandEnvironment->FunctionOffsets.MickeyWonderPartner2);
	AfxGetApp()->WriteProfileInt(_T("FunctionOffsets"), _T("SetFieldOfView"), pIslandEnvironment->FunctionOffsets.SetFieldOfView);
	AfxGetApp()->WriteProfileInt(_T("FunctionOffsets"), _T("SetEnableFogRendering"), pIslandEnvironment->FunctionOffsets.SetEnableFogRendering);
	AfxGetApp()->WriteProfileInt(_T("FunctionOffsets"), _T("SetTargetFrameRate"), pIslandEnvironment->FunctionOffsets.SetTargetFrameRate);
	AfxGetApp()->WriteProfileInt(_T("FunctionOffsets"), _T("OpenTeam"), pIslandEnvironment->FunctionOffsets.OpenTeam);
	AfxGetApp()->WriteProfileInt(_T("FunctionOffsets"), _T("OpenTeamPageAccordingly"), pIslandEnvironment->FunctionOffsets.OpenTeamPageAccordingly);
	AfxGetApp()->WriteProfileInt(_T("FunctionOffsets"), _T("CheckCanEnter"), pIslandEnvironment->FunctionOffsets.CheckCanEnter);
	AfxGetApp()->WriteProfileInt(_T("FunctionOffsets"), _T("SetupQuestBanner"), pIslandEnvironment->FunctionOffsets.SetupQuestBanner);
	AfxGetApp()->WriteProfileInt(_T("FunctionOffsets"), _T("FindGameObject"), pIslandEnvironment->FunctionOffsets.FindGameObject);
	AfxGetApp()->WriteProfileInt(_T("FunctionOffsets"), _T("SetActive"), pIslandEnvironment->FunctionOffsets.SetActive);
	AfxGetApp()->WriteProfileInt(_T("FunctionOffsets"), _T("EventCameraMove"), pIslandEnvironment->FunctionOffsets.EventCameraMove);
	AfxGetApp()->WriteProfileInt(_T("FunctionOffsets"), _T("ShowOneDamageTextEx"), pIslandEnvironment->FunctionOffsets.ShowOneDamageTextEx);
	AfxGetApp()->WriteProfileInt(_T("FunctionOffsets"), _T("SwitchInputDeviceToTouchScreen"), pIslandEnvironment->FunctionOffsets.SwitchInputDeviceToTouchScreen);
	AfxGetApp()->WriteProfileInt(_T("FunctionOffsets"), _T("MickeyWonderCombineEntry"), pIslandEnvironment->FunctionOffsets.MickeyWonderCombineEntry);
	AfxGetApp()->WriteProfileInt(_T("FunctionOffsets"), _T("MickeyWonderCombineEntryPartner"), pIslandEnvironment->FunctionOffsets.MickeyWonderCombineEntryPartner);

}




void page1::OnBnClickedButtonGamestart()
{
	if (pIslandEnvironment->FunctionOffsets.MickeyWonder == NULL)
	{
		AfxMessageBox(L"注册表中配置为空，请先获取配置写入注册表");
		return;
	}
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (!radio_guofu.GetCheck()) 
	{
		AfxMessageBox(L"国际服目前暂不支持");
		return;
	} // 国际服目前暂不支持

	if (noinject)
	{
		HANDLE h{};
		startprocess(gamepath.GetString(), h);
		SetDlgItemText(IDC_STATIC_STATUS, L"");
	}
	else
	{
		HANDLE hThread = CreateThread(NULL, 0, ThreadProc, (LPVOID)&gamepath, 0, NULL); // 创建一个子线程
		
		if (hThread != NULL)
		{
			CloseHandle(hThread);
			hThread = NULL;
		}


	}

}

void page1::OnBnClickedButtonSetgamedir()
{

	CFileDialog fd(TRUE);
	if (fd.DoModal() == IDOK) {
		CString fp = fd.GetPathName();
		SetDlgItemText(IDC_EDIT_GAMEPATH, fp);
		UpdateData(TRUE);
		AfxGetApp()->WriteProfileString(_T("Settings"), _T("GamePath"), gamepath);

	}
}

void page1::OnBnClickedCheckNotinject()
{
	UpdateData(TRUE);
	AfxGetApp()->WriteProfileInt(_T("Settings"), _T("NoInject"), noinject);

}

void page1::OnBnClickedCheckSetfieldofview()
{
	UpdateData(TRUE);
	pIslandEnvironment->EnableSetFieldOfView = setfov;
	CheckSetfieldofviewextra();
	AfxGetApp()->WriteProfileInt(_T("Settings"), _T("SetFov"), setfov);

}

void page1::OnBnClickedCheckSetenablefogrendering()
{
	UpdateData(TRUE);
	pIslandEnvironment->DisableFog = disablefog;
	AfxGetApp()->WriteProfileInt(_T("Settings"), _T("DisableFog"), disablefog);
}

void page1::OnEnUpdateEditFov()
{
	if (!initok)
	{
		return;
	}
	UpdateData(TRUE);
	pIslandEnvironment->FieldOfView = static_cast<float>(fov);
	AfxGetApp()->WriteProfileInt(_T("Settings"), _T("Fov"), fov);

}

void page1::OnBnClickedCheckFixlowfovscene()
{

	UpdateData(TRUE);
	pIslandEnvironment->FixLowFovScene = FixLowFovScene;
	AfxGetApp()->WriteProfileInt(_T("Settings"), _T("FixLowFovScene"), FixLowFovScene);
}

void page1::OnBnClickedCheckSettargetframerate()
{
	UpdateData(TRUE);
	pIslandEnvironment->EnableSetTargetFrameRate = EnableSetTargetFrameRate;
	CheckSetfpsextra();
	AfxGetApp()->WriteProfileInt(_T("Settings"), _T("EnableSetTargetFrameRate"), EnableSetTargetFrameRate);
	
}

void page1::OnEnUpdateEditFps()
{
	if (!initok)
	{
		return;
	}
	UpdateData(TRUE);
	pIslandEnvironment->TargetFrameRate = fps;
	AfxGetApp()->WriteProfileInt(_T("Settings"), _T("Fps"), fps);
}

void page1::OnBnClickedCheckSetupquestbanner()
{
	UpdateData(TRUE);
	pIslandEnvironment->HideQuestBanner = HideQuestBanner;
	AfxGetApp()->WriteProfileInt(_T("Settings"), _T("HideQuestBanner"), HideQuestBanner);
}

void page1::OnBnClickedCheckOpenteam()
{
	UpdateData(TRUE);
	pIslandEnvironment->RemoveOpenTeamProgress = RemoveOpenTeamProgress;
	AfxGetApp()->WriteProfileInt(_T("Settings"), _T("RemoveOpenTeamProgress"), RemoveOpenTeamProgress);
}

void page1::OnBnClickedCheck10Disableeventcameramove()
{
	UpdateData(TRUE);
	pIslandEnvironment->DisableEventCameraMove = DisableEventCameraMove;
	AfxGetApp()->WriteProfileInt(_T("Settings"), _T("DisableEventCameraMove"), DisableEventCameraMove);
}

void page1::OnBnClickedCheckShowonedamagetextex()
{
	UpdateData(TRUE);
	pIslandEnvironment->DisableShowDamageText = DisableShowDamageText;
	AfxGetApp()->WriteProfileInt(_T("Settings"), _T("DisableShowDamageText"), DisableShowDamageText);
}

void page1::OnBnClickedCheckRedirectcombineentry()
{
	UpdateData(TRUE);
	pIslandEnvironment->RedirectCombineEntry = RedirectCombineEntry;
	AfxGetApp()->WriteProfileInt(_T("Settings"), _T("RedirectCombineEntry"), RedirectCombineEntry);
}

void page1::OnBnClickedCheckSwitchinputdevicetotouchscreen()
{
	UpdateData(TRUE);
	pIslandEnvironment->UsingTouchScreen = UsingTouchScreen;
	AfxGetApp()->WriteProfileInt(_T("Settings"), _T("UsingTouchScreen"), UsingTouchScreen);
}
	
void page1::OnBnClickedButtonGetconfig()
{
	std::vector<char> config;
	httprequest(&config);
	phasejson(&config,pIslandEnvironment);
	writeconfigtoreg();
	
}

afx_msg LRESULT page1::OnGameEnd(WPARAM wParam, LPARAM lParam)
{
	SetDlgItemText(IDC_STATIC_STATUS, L"游戏进程结束");
	GetDlgItem(IDC_CHECK_SwitchInputDeviceToTouchScreen)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GAMESTART)->EnableWindow(TRUE);
	return 0;
}

afx_msg LRESULT page1::OnGameRunning(WPARAM wParam, LPARAM lParam)
{
	SetDlgItemText(IDC_STATIC_STATUS, L"游戏正在运行");
	GetDlgItem(IDC_CHECK_SwitchInputDeviceToTouchScreen)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GAMESTART)->EnableWindow(FALSE);
	return 0;
}
