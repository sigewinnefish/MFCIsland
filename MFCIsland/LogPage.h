#pragma once
#include "afxdialogex.h"
#include "logbtn.h"
#include "appmessage.h"
#include "MFCIslandApplication.h"
#include "LogCedit.h"

// Logpage 对话框

class Logpage : public CPropertyPage
{
	DECLARE_DYNAMIC(Logpage)

public:
	Logpage();
	virtual ~Logpage();

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
	LogCedit logedit;
	BOOL enablelog = FALSE;
protected:
	afx_msg LRESULT OnLogsent(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonClearlog();

	afx_msg void OnBnClickedButtonExportasCsv();
};
