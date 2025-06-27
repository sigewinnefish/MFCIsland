#pragma once
#include "afxdialogex.h"
#include "MFCApplication20.h"
#include "damage.h"

// DamagePage 对话框

class DamagePage : public CPropertyPage
{
	DECLARE_DYNAMIC(DamagePage)

public:
	DamagePage();
	virtual ~DamagePage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DamagePage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_damageListctl;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonStat();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	ElementalDamages* pElementalDamages;
	void autoColumnWidth(CListCtrl* listCtrl, int columnIndex);
};

