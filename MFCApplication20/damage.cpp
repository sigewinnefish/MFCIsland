#include "pch.h"
#include "mainisland.h"
#include "damage.h"
#include <numeric>
#include <execution>

#define pDamages ((std::vector<float>*) pdata)
#define pDamageData ((DamageData*)plistDamageData)

DamageInnerData* pdata = nullptr;
volatile BOOL DamageThreadProcStarted = 0;

DWORD WINAPI DamageThreadProc(LPVOID lpParameter)
{
    DamageThreadProcStarted = 1;
    DamageInnerData data{};
    pdata = &data;

	ElementalDamages* pElementalDamages = (ElementalDamages*)filemapping(ISLAND_ENVIRONMENT_EXTRA);

    listDamageData* plistDamageData = (listDamageData*)lpParameter;

	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, L"Local\\MFCIslandEvent");
    hEventtogglestat = CreateEvent(NULL, TRUE, FALSE, NULL);
    hEventcal = CreateEvent(NULL, FALSE, FALSE, NULL);
	
    if (!hEventtogglestat)
    {
        return GetLastError();
    }

	if(!hEvent)
	{
		return GetLastError();
	}

    if (!hEventcal)
    {
        return GetLastError();
    }

    while (true)
    {
 
        if (WaitForSingleObject(hEventtogglestat, INFINITE)) continue;
        if (WaitForSingleObject(hEvent, INFINITE) != 0) continue;
        
        
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

        SetEvent(hEventcal);
    }
	return 0;
}

DWORD WINAPI DamagecalcThreadProc(LPVOID lpParameter)
{
    listDamageData* plistDamageData = (listDamageData*)lpParameter;

    while (!pdata || !hEventtogglestat || !hEventcal)
    {
		Sleep(50);
    }


	ENSURE(pdata != nullptr);
    
    while (true)
    {
        if (clear) 
        {
            clear = 0;
            EnterCriticalSection(&cs);
            *pdata = DamageInnerData{};
            LeaveCriticalSection(&cs);
        }

        for (int i = 0; i < 8; i++)
        {
            if (pDamages[i].empty())
            {
                continue;
            }

            EnterCriticalSection(&cs);
            std::vector<float> temp = pDamages[i];
            LeaveCriticalSection(&cs);

            if (temp.empty())
            {
                continue;
            }

            pDamageData[i].max = *std::max_element(temp.begin(), temp.end());
            pDamageData[i].total = std::reduce(std::execution::unseq, temp.begin(), temp.end(), 0LL, [](__int64 acc, float damageval) {return acc + static_cast<__int64>(damageval);});
            int n = (int)temp.size();
            pDamageData[i].count = n;

            float mean = pDamageData[i].total / static_cast<float>(n);
            float sum = std::reduce(std::execution::unseq, temp.begin(), temp.end(), 0.0f,
                [mean](float acc, float damageval)
                {
                    
                    return acc + (mean - damageval) * (mean - damageval);;
                }
            );

            pDamageData[i].deviation = (float)sqrt(sum / n);

        }
        Sleep(50);

        loop:if (WaitForSingleObject(__notnull hEventcal, INFINITE) != 0) goto loop;

        

    }
}