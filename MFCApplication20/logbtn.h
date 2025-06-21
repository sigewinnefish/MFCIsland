#pragma once
#include "framework.h"
// logbtn

class logbtn : public CMFCButton
{
	DECLARE_DYNAMIC(logbtn)

public:
	logbtn();
	virtual ~logbtn();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnDraw(CDC* pDC, const CRect& rect, UINT uiState);
	BOOL enablelog = FALSE;
};


 