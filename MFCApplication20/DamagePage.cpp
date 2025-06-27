// DamagePage.cpp: 实现文件
//

#include "pch.h"
#include "DamagePage.h"
#include "mainisland.h"


// DamagePage 对话框

IMPLEMENT_DYNAMIC(DamagePage, CPropertyPage)

DamagePage::DamagePage()
	: CPropertyPage(IDD_DamagePage)
{
	pElementalDamages = (ElementalDamages*)filemapping(ISLAND_ENVIRONMENT_EXTRA);
}

DamagePage::~DamagePage()
{
}

void DamagePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DAMAGE, m_damageListctl);
}

BEGIN_MESSAGE_MAP(DamagePage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_STAT, &DamagePage::OnBnClickedButtonStat)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// DamagePage 消息处理程序

BOOL DamagePage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	SetTimer(1, 500, NULL);
	
	m_damageListctl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); // 设置扩展样式
	m_damageListctl.InsertColumn(0, L"序号", LVCFMT_LEFT, 0);
	m_damageListctl.InsertColumn(1, L"元素种类", LVCFMT_LEFT, 0);
	m_damageListctl.InsertColumn(2, L"最大单次伤害", LVCFMT_LEFT, 0);
	m_damageListctl.InsertColumn(3, L"单次伤害方差", LVCFMT_LEFT, 0);
	m_damageListctl.InsertColumn(4, L"累计伤害", LVCFMT_LEFT, 0);
	
	int nItem{0};
	WCHAR* elementNames[] = {
	L"无元素",
	L"火元素",
	L"水元素",
	L"草元素",
	L"雷元素",
	L"冰元素",
	L"风元素",
	L"岩元素",
	};

	WCHAR numbuf[2];
	for (WCHAR* elementname : elementNames)
	{
		swprintf(numbuf, sizeof(numbuf)/sizeof(WCHAR), L"%d", nItem);
		m_damageListctl.InsertItem(nItem, numbuf);
		m_damageListctl.SetItemText(nItem, 1, elementname);
		
		nItem++;
	}


	CHeaderCtrl* pHeader = m_damageListctl.GetHeaderCtrl();
	if (pHeader)
	{
		HDITEM hdi{};
		hdi.mask = HDI_FORMAT;
		pHeader->GetItem(4, &hdi);
		hdi.fmt |=  HDF_STRING | HDF_SORTDOWN;
		pHeader->SetItem(4, &hdi);
	}

	autoColumnWidth(&m_damageListctl, 0);
	autoColumnWidth(&m_damageListctl, 1);
	autoColumnWidth(&m_damageListctl, 2);
	autoColumnWidth(&m_damageListctl, 3);
	autoColumnWidth(&m_damageListctl, 4);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void DamagePage::autoColumnWidth(CListCtrl* listCtrl, int columnIndex)
{

	listCtrl->SetColumnWidth(columnIndex, LVSCW_AUTOSIZE_USEHEADER);
	listCtrl->SetColumnWidth(columnIndex, listCtrl->GetColumnWidth(columnIndex)*1.5);
}


void DamagePage::OnBnClickedButtonStat()
{

	//m_damageListctl.SetItemText(0, 3, L"Address 4");
}

void DamagePage::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


	wchar_t szBuffer[256];
	//swprintf_s(szBuffer, L"%d", rand());

	//m_damageListctl.SetItemText(2, 2, szBuffer);

	CPropertyPage::OnTimer(nIDEvent);
}
