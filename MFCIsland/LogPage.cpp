// Logpage.cpp: 实现文件
//

#include "pch.h"
#include "LogPage.h"
#include "logserver.h"


// Logpage 对话框

IMPLEMENT_DYNAMIC(Logpage, CPropertyPage)

Logpage::Logpage()
	: CPropertyPage(IDD_PROPPAGE_2)

{
    HANDLE hThread = ::CreateThread(NULL, 0, LogServerProc, NULL, 0, NULL);

    if (hThread != NULL)
    {
        CloseHandle(hThread);
        hThread = NULL;
    }
}

Logpage::~Logpage()
{
}

void Logpage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BUTTON_LOG, logbutton);
    DDX_Control(pDX, IDC_LOG, logedit);
}


BEGIN_MESSAGE_MAP(Logpage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_LOG, &Logpage::OnBnClickedButtonLog)
    ON_BN_CLICKED(IDC_BUTTON_WRITEFILE, &Logpage::OnBnClickedButtonWritefile)
    ON_MESSAGE(WM_LOGSENT, &Logpage::OnLogsent)
    ON_BN_CLICKED(IDC_BUTTON_CLEARLOG, &Logpage::OnBnClickedButtonClearlog)
    ON_BN_CLICKED(IDC_BUTTON_EXPORTAS_CSV, &Logpage::OnBnClickedButtonExportasCsv)
END_MESSAGE_MAP()


// Logpage 消息处理程序

void Logpage::OnBnClickedButtonLog()
{

    if (!enablelog)
    {
        logbutton.SetWindowTextW(L"停止日志");
        //logedit.SetSel(-1, -1); // 选中编辑框中的所有文本
        //logedit.ReplaceSel(L"日志启动...\r\n"); // 替换选中的文本

        enablelog = true;
        logbutton.enablelog = true;
    }
    else
    {
        logbutton.SetWindowTextW(L"开启日志");
        //logedit.SetSel(-1, -1); // 选中编辑框中的所有文本
        //logedit.ReplaceSel(L"日志停止...\r\n"); // 替换选中的文本

        enablelog = false;
        logbutton.enablelog = false;
        return;
    }

}


void Logpage::OnBnClickedButtonWritefile()
{
    CFileDialog fd(FALSE, L"txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"TXT (*.txt)|*.txt|");
    if (fd.DoModal() == IDOK) {
        CString fp = fd.GetPathName();
        LPCWSTR filename = fp.GetString();
        HANDLE hFile = CreateFile(filename, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        DWORD lpNumberOfBytesWritten;
        CString txt;
        logedit.GetWindowText(txt);
        WriteFile(hFile, txt.GetString(), txt.GetLength()*sizeof(WCHAR), &lpNumberOfBytesWritten, NULL);
        CloseHandle(hFile);
    }
    
}

afx_msg LRESULT Logpage::OnLogsent(WPARAM wParam, LPARAM lParam)
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

BOOL Logpage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();
    logedit.SendMessage(EM_LIMITTEXT, 0);
    // TODO:  在此添加额外的初始化

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void Logpage::OnBnClickedButtonClearlog()
{

    logedit.SetWindowText(NULL);

}

void Logpage::OnBnClickedButtonExportasCsv()
{
    CFileDialog fd(FALSE, L"csv", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"CSV (*.csv)|*.csv|");
    if (fd.DoModal() == IDOK) {
        CString fp = fd.GetPathName();
        LPCWSTR filename = fp.GetString();
        CString txt;
        logedit.GetWindowText(txt);
        DWORD size = txt.GetLength() * sizeof(WCHAR);
        ENSURE(size > 2);

        HANDLE hFile = CreateFile(filename, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        char* pchar = new char[size - 2];
        RtlCopyMemory(pchar, (char*)(txt.GetString()), size - 2);
        int i = 1;
        std::vector<WCHAR*> plines{ (WCHAR*)pchar };
        while (true)
        {
            auto a = (WCHAR*)pchar + i;
            if (*a == 0)
            {
                break;
            }
            if (*a == L'\r' && *(a + 2) == L'[')
            {
                plines.push_back(a + 2);
                *a = 0;
            }
            i++;
        }

        WCHAR* plbracket = nullptr;
        WCHAR* prbracket = nullptr;


        enum MyEnum
        {
            type = 2,
            damageType,
            showType,
            damage,
            worldPos,
            attackee,
            elementReactionType,

        };

        constexpr WCHAR comma = L',';
        std::wstring result;
        result.append(L"type,damageType,showType,damage,worldPos,attackee,elementReactionType\n");

        for (WCHAR* pline : plines)
        {

            i = 0;
            int bkcount = 0;

            while (true)
            {
                WCHAR* a = pline + i;
                if (*a == L'[')
                {
                    plbracket = a;
                }

                if (*a == L']')
                {
                    prbracket = a;
                }
                if (plbracket && prbracket)
                {
                    bkcount += 1;
                    switch (bkcount)
                    {
                    case type:
                        result.append(plbracket + 6, (prbracket - plbracket - 6));
                        result.append(&comma, 1);
                        break;
                    case damageType:
                        result.append(plbracket + 12, (prbracket - plbracket - 12));
                        result.append(&comma, 1);
                        break;
                    case showType:
                        result.append(plbracket + 10, (prbracket - plbracket - 10));
                        result.append(&comma, 1);
                        break;
                    case damage:
                        result.append(plbracket + 8, (prbracket - plbracket - 8));
                        result.append(&comma, 1);
                        break;
                    case worldPos:
                        result.append(plbracket + 1, (prbracket - plbracket - 1));
                        result.append(&comma, 1);
                        break;
                    case attackee:
                        result.append(plbracket + 1, (prbracket - plbracket - 1));
                        result.append(&comma, 1);
                        break;

                    case elementReactionType:
                        result.append(plbracket + 1, (prbracket - plbracket - 1));
                        break;
                    }

                    plbracket = 0;
                    prbracket = 0;
                }

                if (*a == 0)
                {
                    result.append(L"\n");
                    break;
                }
                i++;
            }

        }

        char* utf8result = new char[result.size()];
        DWORD utf8resultsize = result.size();
        WideCharToMultiByte(CP_UTF8, NULL, result.c_str(), -1, utf8result, utf8resultsize, NULL, NULL);
        WriteFile(hFile, utf8result, utf8resultsize, NULL, NULL);

        CloseHandle(hFile);
        delete[] pchar;
        delete[] utf8result;
    }
}
