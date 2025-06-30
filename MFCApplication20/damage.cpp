#include "pch.h"
#include "mainisland.h"
#include "damage.h"
#include <numeric>

#define pDamages ((std::vector<float>*) pdata)
#define pDamageData ((DamageData*)plistDamageData)
volatile BOOL clear = 0;
DamageInnerData * pdata = nullptr;
CRITICAL_SECTION cs;
HANDLE hEventtogglestat;

DWORD WINAPI DamageThreadProc(LPVOID lpParameter)
{
    DamageInnerData data{};
    pdata = &data;

	ElementalDamages* pElementalDamages = (ElementalDamages*)filemapping(ISLAND_ENVIRONMENT_EXTRA);

    listDamageData* plistDamageData = (listDamageData*)lpParameter;

	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, L"Local\\MFCIslandEvent");
    hEventtogglestat = CreateEvent(NULL, TRUE, FALSE, NULL);
	
    if (!hEventtogglestat)
    {
        return GetLastError();
    }

	if(!hEvent)
	{

		return GetLastError();
	}

    while (true)
    {
        WaitForSingleObject(hEvent, INFINITE);
        WaitForSingleObject(hEventtogglestat, INFINITE);
        
        EnterCriticalSection(&cs);
        switch (pElementalDamages->type)
        {
        case 0:
            pDamages[0].push_back(pElementalDamages->Physical.current);
            break;
        case 1:
            pDamages[1].push_back(pElementalDamages->Pyro.current);
            break;
        case 2:
            pDamages[2].push_back(pElementalDamages->Hydro.current);
            break;
        case 3:
            pDamages[3].push_back(pElementalDamages->Dendro.current);
            break;
        case 4:
            pDamages[4].push_back(pElementalDamages->Electro.current);
            break;
        case 5:
            pDamages[5].push_back(pElementalDamages->Cryo.current);
            break;
        case 7:
            pDamages[6].push_back(pElementalDamages->Anemo.current);
            break;
        case 8:
            pDamages[7].push_back(pElementalDamages->Geo.current);
            break;
        default:
            break;
        }
        LeaveCriticalSection(&cs);

    }
	return 0;
}

DWORD WINAPI DamagecalcThreadProc(LPVOID lpParameter)
{
    listDamageData* plistDamageData = (listDamageData*)lpParameter;

    while (!pdata)
    {
		Sleep(50);
    }

	ENSURE(pdata != nullptr);
    
    while (true)
    {
        
        for (int i = 0; i < 8; i++)
        {
            if (pDamages[i].empty())
            {
                continue;
            }

            EnterCriticalSection(&cs);
            if (clear)
            {
                *pdata = DamageInnerData{};
                clear = 0;
            }
            std::vector<float> temp = pDamages[i];
            LeaveCriticalSection(&cs);

            if (temp.empty())
            {
                continue;
            }

            pDamageData[i].max = *std::max_element(temp.begin(), temp.end());
            pDamageData[i].total = std::accumulate(temp.begin(), temp.end(), 0LL);

            int n = (int)temp.size();
            float mean = pDamageData[i].total / static_cast<float>(n);
            float sum = 0.0f;
            for (float pDamage : temp)
            {
                sum += (mean - pDamage) * (mean - pDamage);

            }
            pDamageData[i].deviation = (float)sqrt(sum / n);

        }
        Sleep(250);


    }
}