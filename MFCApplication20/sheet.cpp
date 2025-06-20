// sheet.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication20.h"
#include "sheet.h"

// sheet

IMPLEMENT_DYNAMIC(sheet, CPropertySheet)

sheet::sheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

sheet::sheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&p1);
	AddPage(&p2);

}

BOOL sheet::OnInitDialog()
{
	CPropertySheet::OnInitDialog();

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{

		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, SYSCMD_TOP, L"置顶");
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, L"关于");

	}
	return TRUE;
}


sheet::~sheet()
{
}

BEGIN_MESSAGE_MAP(sheet, CPropertySheet)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// sheet 消息处理程序

void sheet::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类

	switch (nID)
	{
	case SYSCMD_TOP:
	{
		CMenu* pSysMenu = GetSystemMenu(FALSE);
		if (pSysMenu != nullptr)
		{
			if (!ONTOP)
			{
				::SetWindowPos(AfxGetApp()->GetMainWnd()->GetSafeHwnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); // 窗口置顶
				ONTOP = TRUE;
				pSysMenu->ModifyMenu(SYSCMD_TOP, MF_BYCOMMAND, SYSCMD_TOP, L"取消置顶");
			}
			else
			{
				::SetWindowPos(AfxGetApp()->GetMainWnd()->GetSafeHwnd(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); // 窗口置顶
				ONTOP = FALSE;
				pSysMenu->ModifyMenu(SYSCMD_TOP, MF_BYCOMMAND, SYSCMD_TOP, L"置顶");
			}

		}
		break;
	}
	case IDM_ABOUTBOX:
	{
		CDialog dlg(IDD_ABOUTBOX);
		dlg.DoModal();
	}
	default:
		CPropertySheet::OnSysCommand(nID, lParam);

	}

}
