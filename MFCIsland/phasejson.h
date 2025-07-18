#pragma once

#include <nlohmann/json.hpp>
#include "mainisland.h"


using nlohmann::json;
void phasejson(std::vector<char>* config,IslandEnvironment* pIslandEnvironment);