#pragma once
#include <iostream>
#include <windows.h>
#include <Lmcons.h>
#include "wintoastlib.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <ctime>
#include <chrono>
#include <string>

using namespace WinToastLib;

// Namespace Containing all the Custom Core Functions
namespace core {

    // BatteryStatus struct which have variables to store user's battery status
    struct BatteryStatus
    {
        bool  is_battery_present{ true };
        float battery_percentage{ 0.f };
        bool  is_charging       {false};
    };

    // Configurations which can be set by the user
    namespace Config
    {
        extern int  ALERT_PERCENTAGE;
        extern int  REMIND_AFTER_EVERY;
        extern bool MESSAGE_BOX_ALERT_PREFERENCE;
        extern bool TOAST_NOTIFICATION_ALERT_PREFERENCE;
        extern bool PLUGGED_IN_ALERT;
        extern bool UNPLUGGED_ALERT;
        extern std::string LAST_CHARGED; // stores the datetime when the charger was last plugged out
    }

    // Helps to get the current battery status
    BatteryStatus get_BatteryStatus();

    // shows a message box with the given title and message
    void ShowNotification(const std::wstring& title, const std::wstring& message);

    // loads and returns the json data from the file
    nlohmann::json load_json_data();
    
    // Set the Current Configs equal to the loaded json data
    void set_Config(nlohmann::json data);

    // Save data to file
    void save_data();

    // Creates a toast Battery notification
    void toast_notification(int battery_percentage, std::wstring caption);

    // Current current date as std::string
    std::string getDateTime();

    // Get the Windows username
    std::string getWindowsUsername();

    // Sets the Current working directory to the path of the executable
    void SetWorkingDirectoryToExePath();

    std::string getAppDataPath();
}

class CustomHandler : public IWinToastHandler {
public:
    void toastActivated() const;
    void toastActivated(int actionIndex) const;
    void toastDismissed(WinToastDismissalReason state) const ;
    void toastFailed() const;
};


