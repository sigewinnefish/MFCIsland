// page2.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication20.h"
#include "afxdialogex.h"
#include "page2.h"
#include "logserver.h"


// page2 对话框

IMPLEMENT_DYNAMIC(page2, CPropertyPage)

page2::page2()
	: CPropertyPage(IDD_PROPPAGE_2)
{

}

page2::~page2()
{
}

void page2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(page2, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_LOG, &page2::OnBnClickedButtonLog)
    ON_BN_CLICKED(IDC_BUTTON_WRITEFILE, &page2::OnBnClickedButtonWritefile)
END_MESSAGE_MAP()


// page2 消息处理程序

void page2::OnBnClickedButtonLog()
{
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

    HANDLE hThread = ::CreateThread(NULL, 0, LogServerProc, NULL, 0, NULL); // 创建一个子线程

    if (hThread != NULL)
    {
        CloseHandle(hThread);
        hThread = NULL;
    }
}



void page2::OnBnClickedButtonWritefile()
{
    // TODO: 在此添加控件通知处理程序代码
}
