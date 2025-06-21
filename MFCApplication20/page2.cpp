// page2.cpp: 实现文件
//

#include "pch.h"
#include "page2.h"
#include "logserver.h"


// page2 对话框

IMPLEMENT_DYNAMIC(page2, CPropertyPage)

page2::page2()
	: CPropertyPage(IDD_PROPPAGE_2)

{
    HANDLE hThread = ::CreateThread(NULL, 0, LogServerProc, NULL, 0, NULL);

    if (hThread != NULL)
    {
        CloseHandle(hThread);
        hThread = NULL;
    }
}

page2::~page2()
{
}

void page2::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BUTTON_LOG, logbutton);
    DDX_Control(pDX, IDC_LOG, logedit);
}


BEGIN_MESSAGE_MAP(page2, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_LOG, &page2::OnBnClickedButtonLog)
    ON_BN_CLICKED(IDC_BUTTON_WRITEFILE, &page2::OnBnClickedButtonWritefile)
    ON_MESSAGE(WM_LOGSENT, &page2::OnLogsent)
    ON_BN_CLICKED(IDC_BUTTON_CLEARLOG, &page2::OnBnClickedButtonClearlog)
END_MESSAGE_MAP()


// page2 消息处理程序

void page2::OnBnClickedButtonLog()
{

    if (!enablelog)
    {
        logbutton.SetWindowTextW(L"停止日志");
        logedit.SetSel(-1, -1); // 选中编辑框中的所有文本
        logedit.ReplaceSel(_T("日志启动...\r\n")); // 替换选中的文本

        enablelog = true;
        logbutton.enablelog = true;
    }
    else
    {
        logbutton.SetWindowTextW(L"开启日志");
        logedit.SetSel(-1, -1); // 选中编辑框中的所有文本
        logedit.ReplaceSel(_T("日志停止...\r\n")); // 替换选中的文本

        enablelog = false;
        logbutton.enablelog = false;
        return;
    }

}



void page2::OnBnClickedButtonWritefile()
{
    CString txt;
    logedit.GetWindowText(txt);
    CFileDialog fd(TRUE);
    if (fd.DoModal() == IDOK) {
        CString fp = fd.GetPathName();
    }
}

afx_msg LRESULT page2::OnLogsent(WPARAM wParam, LPARAM lParam)
{
    WCHAR* pchRequest = (WCHAR*)wParam;
    DWORD* cbBytesRead = (DWORD*)lParam;
    LPCWSTR logMessage = pchRequest; // 获取日志消息
    if (!enablelog)
    {
        return 0;
    }
    int nLength = logedit.GetWindowTextLength();
    logedit.SetSel(nLength, nLength);
    logedit.ReplaceSel(pchRequest);




    return 0;
}

BOOL page2::OnInitDialog()
{
    CPropertyPage::OnInitDialog();
    logedit.SendMessage(EM_LIMITTEXT, 0);
    // TODO:  在此添加额外的初始化

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void page2::OnBnClickedButtonClearlog()
{

    logedit.SetWindowText(NULL);

}
