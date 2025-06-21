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

		CFont* pOldFont = SelectFont(pDC);
		ENSURE(pOldFont != NULL);

		CRect textRect = rect; // 原始按钮区域
		textRect.DeflateRect(4, 4);
		CBrush brush(RGB(137, 167, 194));
		CBrush* pold = pDC->SelectObject(&brush);
		pDC->RoundRect(textRect, CPoint(3, 3));
		pDC->SelectObject(pold);

		CFont font;
		font.CreateFont(
			0, // height
			0, // width
			0, // escapement
			0, // orientation
			FW_NORMAL, // weight
			FALSE, // italic
			FALSE, // underline
			FALSE, // strikeout
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			CLEARTYPE_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE,
			L"微软雅黑" // font name
		);

		CString strText;
		GetWindowText(strText);
		pDC->SelectObject(&font);
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(strText, textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		pDC->SelectObject(pOldFont);
	}
	else
	{
		CFont* pOldFont = SelectFont(pDC);
		ENSURE(pOldFont != NULL);

		CRect textRect = rect; // 原始按钮区域
		textRect.DeflateRect(4, 4);
		CBrush brush(RGB(193, 57, 94));
		CBrush* pold = pDC->SelectObject(&brush);
		pDC->RoundRect(textRect, CPoint(3, 3));
		pDC->SelectObject(pold);

		CFont font;
		font.CreateFont(
			0, // height
			0, // width
			0, // escapement
			0, // orientation
			FW_NORMAL, // weight
			FALSE, // italic
			FALSE, // underline
			FALSE, // strikeout
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			CLEARTYPE_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE,
			L"微软雅黑" // font name
		);

		CString strText;
		GetWindowText(strText);
		pDC->SelectObject(&font);
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(strText, textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		pDC->SelectObject(pOldFont);
		//CMFCButton::OnDraw(pDC, rect, uiState);
	}




}
