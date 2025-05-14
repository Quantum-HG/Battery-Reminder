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

// Whichever section's state is true, is displayed as the current tab
namespace Selectable_state
{
    extern bool DashBoard;
    extern bool Settings;
    extern bool Battery_Health;
    extern bool Alerts_and_Notifications;
}

// set all the states of Selectable_state to false
void false_all_states();

// DashBoard section of the app
void show_dashboard(core::BatteryStatus& CurrentBatteryStatus, sf::Clock& clock);

// Battery Health Section of the app
void show_battery_health();

// Alerts and notification section of the app
void show_alerts_and_notification(core::BatteryStatus& battery_status);

// Settings section of the app
void show_settings();
