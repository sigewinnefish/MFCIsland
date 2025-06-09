// page2.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication20.h"
#include "afxdialogex.h"
#include "page2.h"


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
END_MESSAGE_MAP()


// page2 消息处理程序

void page2::OnBnClickedButtonLog()
{
	MessageBox(L"a");
}
