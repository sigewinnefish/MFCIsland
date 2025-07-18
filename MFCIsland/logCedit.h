#pragma once


// LogCedit

class LogCedit : public CEdit
{
	DECLARE_DYNAMIC(LogCedit)

public:
	LogCedit();
	virtual ~LogCedit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
};


