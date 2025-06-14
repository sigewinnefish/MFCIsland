
// MFCApplication20.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication20.h"
#include "sheet.h"
#include "page1.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication20App

BEGIN_MESSAGE_MAP(CMFCApplication20App, CWinApp)
	//ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
	
END_MESSAGE_MAP()



// CMFCApplication20App 构造

CMFCApplication20App::CMFCApplication20App()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CMFCApplication20App 对象

CMFCApplication20App theApp;


// CMFCApplication20App 初始化

BOOL CMFCApplication20App::InitInstance()
{

	CWinApp::InitInstance();

	SetRegistryKey(_T("MFCIsland"));


	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	


	sheet* s = new sheet(L"MFCIsland");

	m_pMainWnd = s;

	INT_PTR nResponse = s->Create(NULL, WS_OVERLAPPEDWINDOW, TRUE);

	s->ModifyStyle(WS_MAXIMIZEBOX, NULL, NULL); // 取消最大化按钮
		
	s->ShowWindow(SW_SHOWNORMAL);


#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return TRUE;
}

