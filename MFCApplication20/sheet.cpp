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



sheet::~sheet()
{
}


BEGIN_MESSAGE_MAP(sheet, CPropertySheet)
END_MESSAGE_MAP()


// sheet 消息处理程序
