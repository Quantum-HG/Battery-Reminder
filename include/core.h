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

using namespace WinToastLib;
// using json = nlohmann::json;


// Namespace Containing all the Custom Functions
namespace core {

    // BatteryStatus struct which have variables to store user's battery status
    struct BatteryStatus
    {
        bool  is_battery_present{ true };
        float battery_percentage{ 0.f };
        bool  is_charging       {false};
    };


    // Configurations which can be set 
    namespace Config
    {
        extern int  ALERT_PERCENTAGE;
        extern int  REMIND_AFTER_EVERY;

        extern bool MESSAGE_BOX_ALERT_PREFERENCE;
        extern bool TOAST_NOTIFICATION_ALERT_PREFERENCE;

        extern int  CHARGE_CYCLE_COUNT_TODAY;
    }

    BatteryStatus get_BatteryStatus();

    void ShowNotification(const std::wstring& title, const std::wstring& message);

    // Load data from the file 
    nlohmann::json load_data();

    // Save data to file
    void save_data(nlohmann::json loaded_json_data);

    // Creates a toast Battery notification
    void toast_notification(int battery_percentage, std::wstring caption);

    // The BatteryPercentageWidget to show battery percentage
    void BatteryPercentageWidget(core::BatteryStatus& CurrentBatteryStatus, sf::Clock& clock);

    // Current current date as std::string
    std::string getDate();
}

class CustomHandler : public IWinToastHandler {
public:
    void toastActivated() const;
    void toastActivated(int actionIndex) const;
    void toastDismissed(WinToastDismissalReason state) const ;
    void toastFailed() const;
};


