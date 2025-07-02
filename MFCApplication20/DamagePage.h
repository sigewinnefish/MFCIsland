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

	listDamageData listDamageData{};
	void autoColumnWidth(CListCtrl* listCtrl, int columnIndex);
	afx_msg void OnCbnSelchangeComboDelay();
	CComboBox m_delalyctl;
	INT64 damagetotaltemp[8] = { 0 };
	float damagedeviationtemp[8] = { 0 };
	float damagemaxtemp[8] = { 0 };
	int damagecountemp[8] = { 0 };
	
	wchar_t szBuffer[1024]; 
	bool enabledamagestat = false;

private:
	void initdamagelistctr();
	void initdelaycbox();
public:
	afx_msg void OnBnClickedButtonStatclear();
	CButton damagestatbtn;
};

