#include "pch.h"
#include "phasejson.h"

void phasejson(std::vector<char>* config, IslandEnvironment* pIslandEnvironment)
{
	json UnlockerIsland_json = json::parse(config->data());
	pIslandEnvironment->FunctionOffsets.MickeyWonder = UnlockerIsland_json["Chinese"]["MickeyWonderMethod"];
	pIslandEnvironment->FunctionOffsets.MickeyWonderPartner = UnlockerIsland_json["Chinese"]["MickeyWonderMethodPartner"];
	pIslandEnvironment->FunctionOffsets.MickeyWonderPartner2 = UnlockerIsland_json["Chinese"]["MickeyWonderMethodPartner2"];
	pIslandEnvironment->FunctionOffsets.SetFieldOfView = UnlockerIsland_json["Chinese"]["SetFieldOfView"];
	pIslandEnvironment->FunctionOffsets.SetEnableFogRendering = UnlockerIsland_json["Chinese"]["SetEnableFogRendering"];
	pIslandEnvironment->FunctionOffsets.SetTargetFrameRate = UnlockerIsland_json["Chinese"]["SetTargetFrameRate"];
	pIslandEnvironment->FunctionOffsets.OpenTeam = UnlockerIsland_json["Chinese"]["OpenTeam"];
	pIslandEnvironment->FunctionOffsets.OpenTeamPageAccordingly = UnlockerIsland_json["Chinese"]["OpenTeamPageAccordingly"];
	pIslandEnvironment->FunctionOffsets.CheckCanEnter = UnlockerIsland_json["Chinese"]["CheckCanEnter"];
	pIslandEnvironment->FunctionOffsets.SetupQuestBanner = UnlockerIsland_json["Chinese"]["SetupQuestBanner"];
	pIslandEnvironment->FunctionOffsets.FindGameObject = UnlockerIsland_json["Chinese"]["FindGameObject"];
	pIslandEnvironment->FunctionOffsets.SetActive = UnlockerIsland_json["Chinese"]["SetActive"];
	pIslandEnvironment->FunctionOffsets.EventCameraMove = UnlockerIsland_json["Chinese"]["EventCameraMove"];
	pIslandEnvironment->FunctionOffsets.ShowOneDamageTextEx = UnlockerIsland_json["Chinese"]["ShowOneDamageTextEx"];
	pIslandEnvironment->FunctionOffsets.SwitchInputDeviceToTouchScreen = UnlockerIsland_json["Chinese"]["SwitchInputDeviceToTouchScreen"];
	pIslandEnvironment->FunctionOffsets.MickeyWonderCombineEntry = UnlockerIsland_json["Chinese"]["MickeyWonderCombineEntryMethod"];
	pIslandEnvironment->FunctionOffsets.MickeyWonderCombineEntryPartner = UnlockerIsland_json["Chinese"]["MickeyWonderCombineEntryMethodPartner"];

};