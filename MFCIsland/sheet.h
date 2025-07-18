#pragma once
#include "MainPage.h"
#include "LogPage.h"
#include "DamagePage.h"

// sheet

class sheet : public CPropertySheet
{
	DECLARE_DYNAMIC(sheet)

public:
	virtual BOOL OnInitDialog();
	MainPage p1;
	Logpage p2;
	DamagePage dp;
	BOOL ONTOP = 0;

	sheet(UINT nIDCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	sheet(LPCTSTR pszCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	virtual ~sheet();
	HICON m_hIcon;

protected:

	DECLARE_MESSAGE_MAP()
	virtual void OnSysCommand(UINT nID, LPARAM lParam);
	virtual void PostNcDestroy();
};


