#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "core.h"
#include "wintoastlib.h"
#include "nlohmann/json.hpp"
#include <fstream>

void OpenHyperlink(const char* url);
void ShowHyperlink(const char* label, const char* url);

// Settings section of the app
void show_about();