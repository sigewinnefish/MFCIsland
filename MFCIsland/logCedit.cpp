// LogCedit.cpp: 实现文件
//

#include "pch.h"
#include "LogCedit.h"


// LogCedit

IMPLEMENT_DYNAMIC(LogCedit, CEdit)

LogCedit::LogCedit()
{

}

LogCedit::~LogCedit()
{
}


BEGIN_MESSAGE_MAP(LogCedit, CEdit)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// LogCedit 消息处理程序



HBRUSH LogCedit::CtlColor(CDC* pDC, UINT)
{

    static HBRUSH writebghBrush = ::CreateSolidBrush(RGB(255, 255, 255));
	ENSURE(writebghBrush != NULL);
	pDC->SetTextColor(RGB(70, 70, 70));
    return writebghBrush;

}
