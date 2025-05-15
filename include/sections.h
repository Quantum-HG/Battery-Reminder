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

// including the different sections
#include "dashboard.h"
#include "settings.h"
#include "battery_health.h"
#include "alerts_and_notifications.h"


enum class AppSections
{
    DashBoard,
    Settings,
    Battery_Health,
    Alerts_and_Notifications
};
