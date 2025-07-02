#pragma once
#include <vector>

constexpr PCWSTR ISLAND_ENVIRONMENT_EXTRA = L"B6134FBA-EBA9-49F0-B670-9DFE43293329";

struct DamageFromIsland
{
	float current;
};


struct ElementalDamages
{
    DamageFromIsland Physical;
    DamageFromIsland Pyro;
    DamageFromIsland Hydro;
    DamageFromIsland Dendro;
    DamageFromIsland Electro;
    DamageFromIsland Cryo;
    DamageFromIsland Anemo;
    DamageFromIsland Geo;
    short type;
};

struct DamageData
{
    float max;
    float deviation;
    INT64 total;
    int count;
};


struct listDamageData
{
    DamageData Physical;
    DamageData Pyro;
    DamageData Hydro;
    DamageData Dendro;
    DamageData Electro;
    DamageData Cryo;
    DamageData Anemo;
    DamageData Geo;
};

struct DamageInnerData
{
    std::vector<float> physicaldamages;
    std::vector<float> pyrodamages;
    std::vector<float> hydrodamages;
    std::vector<float> dendrodamages;
    std::vector<float> electrodamages;
    std::vector<float> cryodamages;
    std::vector<float> anemodamages;
    std::vector<float> geodamages;

};


DWORD WINAPI DamageThreadProc(LPVOID lpParameter);
DWORD WINAPI DamagecalcThreadProc(LPVOID lpParameter);
inline volatile BOOL clear = 0;
inline CRITICAL_SECTION cs;
inline HANDLE hEventtogglestat;
inline HANDLE hEventcal;