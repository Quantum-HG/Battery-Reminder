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


// The BatteryPercentageWidget to show battery percentage
void BatteryPercentageWidget(core::BatteryStatus& CurrentBatteryStatus, sf::Clock& clock);


// DashBoard section of the app
void show_dashboard(core::BatteryStatus& CurrentBatteryStatus, sf::Clock& clock, nlohmann::json loaded_json_data);

