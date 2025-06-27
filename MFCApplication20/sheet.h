#pragma once
#include "page1.h"
#include "page2.h"
#include "DamagePage.h"

// sheet

class sheet : public CPropertySheet
{
	DECLARE_DYNAMIC(sheet)

public:
	virtual BOOL OnInitDialog();
	page1 p1;
	page2 p2;
	DamagePage dp;
	BOOL ONTOP = 0;

	sheet(UINT nIDCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	sheet(LPCTSTR pszCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	virtual ~sheet();
	HICON m_hIcon;

protected:

	DECLARE_MESSAGE_MAP()
	virtual void sheet::OnSysCommand(UINT nID, LPARAM lParam);
	virtual void PostNcDestroy();
};


