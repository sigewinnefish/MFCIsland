#pragma once

constexpr PCWSTR ISLAND_ENVIRONMENT_EXTRA = L"B6134FBA-EBA9-49F0-B670-9DFE43293329";

struct Damage
{
	double current;
	INT64 total;
};


struct ElementalDamages
{
	Damage Pyro;
	Damage Hydro;
	Damage Anemo;
	Damage Electro;
	Damage Dendro;
	Damage Cryo;
	Damage Geo;
	Damage Physical;

};

