#pragma once
#include "page1.h"
#include "page2.h"

// sheet

class sheet : public CPropertySheet
{
	DECLARE_DYNAMIC(sheet)

public:
	page1 p1;
	page2 p2;

	sheet(UINT nIDCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	sheet(LPCTSTR pszCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	virtual ~sheet();

protected:
	DECLARE_MESSAGE_MAP()
};


