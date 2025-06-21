// logCedit.cpp: 实现文件
//

#include "pch.h"
#include "logCedit.h"


// logCedit

IMPLEMENT_DYNAMIC(logCedit, CEdit)

logCedit::logCedit()
{

}

logCedit::~logCedit()
{
}


BEGIN_MESSAGE_MAP(logCedit, CEdit)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// logCedit 消息处理程序



HBRUSH logCedit::CtlColor(CDC* pDC, UINT)
{

    static HBRUSH writebghBrush = ::CreateSolidBrush(RGB(255, 255, 255));
	ENSURE(writebghBrush != NULL);
	pDC->SetTextColor(RGB(70, 70, 70));
    return writebghBrush;

}
