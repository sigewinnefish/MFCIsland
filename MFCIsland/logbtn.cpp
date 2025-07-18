// logbtn.cpp: 实现文件
//

#include "pch.h"
#include "logbtn.h"


// logbtn

IMPLEMENT_DYNAMIC(logbtn, CMFCButton)

logbtn::logbtn()
{

}

logbtn::~logbtn()
{
}


BEGIN_MESSAGE_MAP(logbtn, CButton)
END_MESSAGE_MAP()


void logbtn::OnDraw(CDC* pDC, const CRect& rect, UINT uiState)
{


	if (!enablelog)
	{
		CRect textRect = rect; // 原始按钮区域
		textRect.DeflateRect(4, 4);
		CBrush brush(RGB(137, 167, 194));
		CBrush* pold = pDC->SelectObject(&brush);
		pDC->RoundRect(textRect, CPoint(3, 3));
		pDC->SelectObject(pold);

		CFont font;
		font.CreatePointFont(100, _T("微软雅黑"));
		CFont* pOldFont = pDC->SelectObject(&font);
		CString strText;
		GetWindowText(strText);
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(strText, textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		pDC->SelectObject(pOldFont);
	}
	else
	{
		CRect textRect = rect; // 原始按钮区域
		textRect.DeflateRect(4, 4);
		CBrush brush(RGB(193, 57, 94));
		CBrush* pold = pDC->SelectObject(&brush);
		pDC->RoundRect(textRect, CPoint(3, 3));
		pDC->SelectObject(pold);

		CFont font;
		font.CreatePointFont(100, _T("微软雅黑"));
		CFont* pOldFont = pDC->SelectObject(&font);
		CString strText;
		GetWindowText(strText);
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(strText, textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		pDC->SelectObject(pOldFont);
	}

	//CMFCButton::OnDraw(pDC, rect, uiState); 不在调用父类函数


}
