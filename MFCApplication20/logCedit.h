#pragma once


// logCedit

class logCedit : public CEdit
{
	DECLARE_DYNAMIC(logCedit)

public:
	logCedit();
	virtual ~logCedit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
};


