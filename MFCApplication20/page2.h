#pragma once
#include "afxdialogex.h"
#include "logbtn.h"
#include "appmessage.h"
#include "MFCApplication20.h"
#include "logCedit.h"

// page2 对话框

class page2 : public CPropertyPage
{
	DECLARE_DYNAMIC(page2)

public:
	page2();
	virtual ~page2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLog();
	afx_msg void OnBnClickedButtonWritefile();
	
	logbtn logbutton;
	logCedit logedit;
	BOOL enablelog = FALSE;
protected:
	afx_msg LRESULT OnLogsent(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonClearlog();

};
