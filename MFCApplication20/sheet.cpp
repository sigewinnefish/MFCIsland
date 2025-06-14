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

	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{

		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, SYSCMD_TOP, L"置顶");

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
	if (nID == SYSCMD_TOP)
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

	}
	else
	{
		CPropertySheet::OnSysCommand(nID, lParam);
	}



}
