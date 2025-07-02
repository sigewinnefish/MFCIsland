// DamagePage.cpp: 实现文件
//

#include "pch.h"
#include "DamagePage.h"


// DamagePage 对话框

IMPLEMENT_DYNAMIC(DamagePage, CPropertyPage)

DamagePage::DamagePage()
	: CPropertyPage(IDD_DamagePage)
{
}

DamagePage::~DamagePage()
{
}

void DamagePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DAMAGE, m_damageListctl);
	DDX_Control(pDX, IDC_COMBO_DELAY, m_delalyctl);
	DDX_Control(pDX, IDC_BUTTON_STAT, damagestatbtn);
}

BEGIN_MESSAGE_MAP(DamagePage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_STAT, &DamagePage::OnBnClickedButtonStat)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_DELAY, &DamagePage::OnCbnSelchangeComboDelay)
	ON_BN_CLICKED(IDC_BUTTON_STATCLEAR, &DamagePage::OnBnClickedButtonStatclear)
END_MESSAGE_MAP()

// DamagePage 消息处理程序

BOOL DamagePage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	InitializeCriticalSection(&cs); // 初始化临界区

	HANDLE hThread = CreateThread(NULL, 0, DamageThreadProc, (LPVOID)&listDamageData, 0, NULL); // 创建一个子线程

	if (hThread != NULL)
	{
		CloseHandle(hThread);
		hThread = NULL;
	}
	hThread = CreateThread(NULL, 0, DamagecalcThreadProc, (LPVOID)&listDamageData, 0, NULL); // 创建一个子线程

	if (hThread != NULL)
	{
		CloseHandle(hThread);
		hThread = NULL;
	}

	initdelaycbox();
	initdamagelistctr();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void DamagePage::initdamagelistctr()
{
	m_damageListctl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); // 设置扩展样式
	m_damageListctl.InsertColumn(0, L"序号", LVCFMT_LEFT, 0);
	m_damageListctl.InsertColumn(1, L"元素种类", LVCFMT_LEFT, 0);
	m_damageListctl.InsertColumn(2, L"伤害次数", LVCFMT_LEFT, 0);
	m_damageListctl.InsertColumn(3, L"最大伤害", LVCFMT_LEFT, 0);
	m_damageListctl.InsertColumn(4, L"伤害标准差", LVCFMT_LEFT, 0);
	m_damageListctl.InsertColumn(5, L"累计伤害", LVCFMT_LEFT, 0);

	int nItem{ 0 };
	const WCHAR* elementNames[] = {
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
	for (const WCHAR* elementname : elementNames)
	{
		swprintf(numbuf, sizeof(numbuf) / sizeof(WCHAR), L"%d", nItem);
		m_damageListctl.InsertItem(nItem, numbuf);
		m_damageListctl.SetItemText(nItem, 1, elementname);
		m_damageListctl.SetItemText(nItem, 2, L"0");
		m_damageListctl.SetItemText(nItem, 3, L"0.0000");
		m_damageListctl.SetItemText(nItem, 4, L"0.00");
		m_damageListctl.SetItemText(nItem, 5, L"0");
		nItem++;
	}


	CHeaderCtrl* pHeader = m_damageListctl.GetHeaderCtrl();
	if (pHeader)
	{
		HDITEM hdi{};
		hdi.mask = HDI_FORMAT;
		pHeader->GetItem(5, &hdi);
		hdi.fmt |= HDF_STRING | HDF_SORTDOWN;
		pHeader->SetItem(5, &hdi);
	}

	autoColumnWidth(&m_damageListctl, 0);
	autoColumnWidth(&m_damageListctl, 1);
	autoColumnWidth(&m_damageListctl, 2);
	autoColumnWidth(&m_damageListctl, 3);
	autoColumnWidth(&m_damageListctl, 4);
	autoColumnWidth(&m_damageListctl, 5);
}
void DamagePage::initdelaycbox()
{
	m_delalyctl.AddString(L"2000  ms"); //0
	m_delalyctl.AddString(L"1500  ms"); //1
	m_delalyctl.AddString(L"1000  ms"); //2
	m_delalyctl.AddString(L"500   ms"); //3
	m_delalyctl.AddString(L"250   ms"); //4
	m_delalyctl.AddString(L"不刷新");
	m_delalyctl.SetCurSel(2);
	SetTimer(1, 1000, NULL);
}

void DamagePage::autoColumnWidth(CListCtrl* listCtrl, int columnIndex)
{

	listCtrl->SetColumnWidth(columnIndex, LVSCW_AUTOSIZE_USEHEADER);
	listCtrl->SetColumnWidth(columnIndex, (int)(listCtrl->GetColumnWidth(columnIndex)*1.75));
}


void DamagePage::OnTimer(UINT_PTR nIDEvent) //非抢占计时器
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	for (int i = 0; i < 8; i++)
	{	

		if (damagecountemp[i] != ((DamageData*)&listDamageData)[i].count)
		{
			ZeroMemory(szBuffer, sizeof(szBuffer));
			swprintf_s(szBuffer, L"%d", ((DamageData*)&listDamageData)[i].count);
			m_damageListctl.SetItemText(i, 2, szBuffer);
			damagecountemp[i] = ((DamageData*)&listDamageData)[i].count;
		}

		if (damagemaxtemp[i] != ((DamageData*)&listDamageData)[i].max)
		{
			ZeroMemory(szBuffer, sizeof(szBuffer));
			swprintf_s(szBuffer, L"%.4f", ((DamageData*)&listDamageData)[i].max);
			m_damageListctl.SetItemText(i, 3, szBuffer);
			damagemaxtemp[i] = ((DamageData*)&listDamageData)[i].max;
		}

		if (damagedeviationtemp[i] != ((DamageData*)&listDamageData)[i].deviation)
		{
			ZeroMemory(szBuffer, sizeof(szBuffer));
			swprintf_s(szBuffer, L"%.2f", ((DamageData*)&listDamageData)[i].deviation);
			m_damageListctl.SetItemText(i, 4, szBuffer);
			damagedeviationtemp[i] = ((DamageData*)&listDamageData)[i].deviation;
		}

		if (damagetotaltemp[i] != ((DamageData*)&listDamageData)[i].total)
		{
			ZeroMemory(szBuffer, sizeof(szBuffer));
			swprintf_s(szBuffer, L"%lld", ((DamageData*)&listDamageData)[i].total);
			m_damageListctl.SetItemText(i, 5, szBuffer);
			damagetotaltemp[i] = ((DamageData*)&listDamageData)[i].total;
		}

	}



	CPropertyPage::OnTimer(nIDEvent);
}



void DamagePage::OnCbnSelchangeComboDelay()
{
	switch (m_delalyctl.GetCurSel())
	{
	case 0:
		KillTimer(1);
		SetTimer(1, 2000, NULL);
		break;
	case 1:
		KillTimer(1);
		SetTimer(1, 1500, NULL);
		break;
	case 2:
		KillTimer(1);
		SetTimer(1, 1000, NULL);
		break;
	case 3:
		KillTimer(1);
		SetTimer(1, 500, NULL);
		break;
	case 4:
		KillTimer(1);
		SetTimer(1, 250, NULL);
		break;
	case 5:
		KillTimer(1);
		break;
	default:
		break;
	}
}

void DamagePage::OnBnClickedButtonStat()
{
	if (!hEventtogglestat) return;

	if (!enabledamagestat)
	{
		SetEvent(hEventtogglestat);
		enabledamagestat = !enabledamagestat;
		damagestatbtn.SetWindowTextW(L"关闭统计");
	}
	else
	{
		ResetEvent(hEventtogglestat);
		enabledamagestat = !enabledamagestat;
		damagestatbtn.SetWindowTextW(L"开启统计");
	}
	

}

void DamagePage::OnBnClickedButtonStatclear()
{
	
	ZeroMemory(&listDamageData, sizeof(listDamageData));
	for (int i = 0; i < 8; i++)
	{
		m_damageListctl.SetItemText(i, 2, L"0");
		m_damageListctl.SetItemText(i, 3, L"0.0000");
		m_damageListctl.SetItemText(i, 4, L"0.00");
		m_damageListctl.SetItemText(i, 5, L"0");

	}

	
	clear = TRUE; // 清除数据
	SetEvent(hEventcal);
}

