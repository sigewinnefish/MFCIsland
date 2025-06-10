#pragma once

#include <winhttp.h>
#include <vector>
#pragma comment(lib, "winhttp.lib")

void httprequest(std::vector<char>* config);