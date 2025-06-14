#pragma once
#include "afxdialogex.h"
#include "mainisland.h"
#include "httprequest.h"
#include "phasejson.h"
#include "appmessage.h"

// page1 对话框

class page1 : public CPropertyPage
{
	DECLARE_DYNAMIC(page1)

public:
	page1();
	virtual ~page1();
	virtual BOOL OnInitDialog();

	BOOL initok{};

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton gamestartbtn; //游戏启动按钮
	CButton setexepathbtn; //设置路径按钮
	CButton getconfigbtn; //获取配置按钮

	void CheckSetfieldofviewextra();
	void CheckSetfpsextra();

	afx_msg void OnBnClickedButtonGamestart();
	afx_msg void OnBnClickedButtonSetgamedir();

	afx_msg void OnBnClickedCheckNotinject();
	afx_msg void OnBnClickedCheckSetfieldofview();

	CButton radio_guofu;
	CString gamepath;

	BOOL noinject{};
	BOOL setfov;
	BOOL disablefog;
	afx_msg void OnBnClickedCheckSetenablefogrendering();
	int fov;
	CSpinButtonCtrl fovspin;

	afx_msg void OnEnUpdateEditFov();
	BOOL FixLowFovScene;
	afx_msg void OnBnClickedCheckFixlowfovscene();
	BOOL EnableSetTargetFrameRate;
	afx_msg void OnBnClickedCheckSettargetframerate();
	int fps;
	afx_msg void OnEnUpdateEditFps();
	CSpinButtonCtrl fpsspin;
	BOOL HideQuestBanner;
	afx_msg void OnBnClickedCheckSetupquestbanner();
	BOOL RemoveOpenTeamProgress;
	afx_msg void OnBnClickedCheckOpenteam();
	BOOL DisableEventCameraMove;
	afx_msg void OnBnClickedCheck10Disableeventcameramove();
	BOOL DisableShowDamageText;
	afx_msg void OnBnClickedCheckShowonedamagetextex();
	BOOL RedirectCombineEntry;
	afx_msg void OnBnClickedCheckRedirectcombineentry();
	BOOL UsingTouchScreen;
	afx_msg void OnBnClickedCheckSwitchinputdevicetotouchscreen();



private:
	IslandEnvironment* pIslandEnvironment;

public:
	afx_msg void OnBnClickedButtonGetconfig();
protected:
	afx_msg LRESULT page1::OnGameEnd(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGameRunning(WPARAM wParam, LPARAM lParam);
};
