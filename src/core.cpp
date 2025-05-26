#include "core.h"


nlohmann::json core::load_json_data()
{
    std::string file_path = core::getAppDataPath() + "\\Battery Reminder\\" + "data\\data.json";
    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading" << std::endl;
        exit(1);
    }

    nlohmann::json data;

    try {
        file >> data;
    }
    catch (nlohmann::json::parse_error& e) {
        std::cerr << "Parse error: " << e.what() << std::endl;
        exit(1);
    }

    file.close();

    return data;
}

#ifndef BATTERY_REMINDER_WATCHER
void core::set_Config(nlohmann::json data)
{
    core::Config::ALERT_PERCENTAGE = data["ALERT_PERCENTAGE"].get<int>();
    core::Config::REMIND_AFTER_EVERY = data["REMIND_AFTER_EVERY"].get<int>();
    core::Config::THEME = data["THEME"].get<int>();
    core::Config::MESSAGE_BOX_ALERT_PREFERENCE = data["MESSAGE_BOX_ALERT_PREFERENCE"].get<bool>();
    core::Config::TOAST_NOTIFICATION_ALERT_PREFERENCE = data["TOAST_NOTIFICATION_ALERT_PREFERENCE"].get<bool>();
    core::Config::PLUGGED_IN_ALERT = data["PLUGGED_IN_ALERT"];
    core::Config::UNPLUGGED_ALERT = data["UNPLUGGED_ALERT"];
    core::Config::LAST_CHARGED = data["LAST_CHARGED"].get<std::string>();
}
#endif

void core::save_data()
{
    nlohmann::json j = {
        {"ALERT_PERCENTAGE", core::Config::ALERT_PERCENTAGE},
        {"REMIND_AFTER_EVERY", core::Config::REMIND_AFTER_EVERY},
        {"MESSAGE_BOX_ALERT_PREFERENCE", core::Config::MESSAGE_BOX_ALERT_PREFERENCE},
        {"TOAST_NOTIFICATION_ALERT_PREFERENCE", core::Config::TOAST_NOTIFICATION_ALERT_PREFERENCE},
        {"LAST_CHARGED", core::Config::LAST_CHARGED},
        {"PLUGGED_IN_ALERT", core::Config::PLUGGED_IN_ALERT},
        {"UNPLUGGED_ALERT", core::Config::UNPLUGGED_ALERT},
        {"THEME", core::Config::THEME}
    };

    std::ofstream file(core::getAppDataPath() + "\\Battery Reminder\\" + "data\\data.json");
    
    file << j;

    file.close();
}

void core::toast_notification(int battery_percentage, std::wstring caption = L"Unplug your charger")
{
    std::wstring appName = L"Battery_Reminder";
    std::wstring appUserModelID = L"Battery_Reminder";

    std::vector<std::wstring> words = { L"Your Device Battery is ", std::to_wstring(battery_percentage), L"% charged" };

    std::wstring text;
    for (const auto& word : words) {
        text.append(word);
    }

    // Output the joined string
    std::wcout << text << std::endl;

    std::wstring imagePath = L"assets\\app.ico";
    std::wstring attribute = caption;
    std::vector<std::wstring> actions;
    INT64 expiration = 0;

    bool onlyCreateShortcut = false;
    WinToastTemplate::AudioOption audioOption = WinToastTemplate::AudioOption::Default;

    WinToast::instance()->setAppName(appName);
    WinToast::instance()->setAppUserModelId(appUserModelID);

    if (!WinToast::instance()->initialize()) {
        std::wcerr << L"Error, your system in not compatible!" << std::endl;
    }

    WinToastTemplate templ(WinToastTemplate::Text02);
    templ.setTextField(text, WinToastTemplate::FirstLine);
    templ.setAudioOption(audioOption);
    templ.setAttributionText(attribute);
    templ.setImagePath(imagePath);

    for (auto const& action : actions) {
        templ.addAction(action);
    }

    if (expiration) {
        templ.setExpiration(expiration);
    }

    if (WinToast::instance()->showToast(templ, new CustomHandler()) < 0) {
        std::wcerr << L"Could not launch your toast notification!";
    }

    // Give the handler a chance for 15 seconds (or the expiration plus 1 second)
    //Sleep(expiration ? (DWORD)expiration + 1000 : 15000);
}

core::BatteryStatus core::get_BatteryStatus()
{
    core::BatteryStatus battery_status;
    SYSTEM_POWER_STATUS status;
    if (GetSystemPowerStatus(&status)) {
        if (status.BatteryFlag != 128) {
            battery_status.battery_percentage = (float)static_cast<int>(status.BatteryLifePercent);
            if (status.BatteryFlag & 8) {
                battery_status.is_charging = true;
            }
            else {
                battery_status.is_charging = false;
            }
        }
        else {
            battery_status.is_battery_present = false;
        }
    }
    else {
        battery_status.is_battery_present = false;
        battery_status.battery_percentage = 0;
        battery_status.is_charging = false;

    }
    
    return battery_status;
}

void core::ShowNotification(const std::wstring& title, const std::wstring& message) {
    // Display a system notification
    MessageBoxW(NULL, message.c_str(), title.c_str(), MB_ICONINFORMATION | MB_SYSTEMMODAL);
}

std::string core::getDateTime()
{
    auto now = std::chrono::system_clock::now();

    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::tm localTime;
    localtime_s(&localTime, &now_c);

    // Format: DD-MM-YYYY HH:MM:SS
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M", &localTime);

    return std::string(buffer);
}

std::string core::getWindowsUsername() {
    char username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;

    if (GetUserNameA(username, &username_len)) {
        return std::string(username);
    }
    else {
        return "Unknown User";
    }
}

void core::SetWorkingDirectoryToExePath() {
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    *strrchr(path, '\\') = '\0'; // strip filename
    SetCurrentDirectoryA(path);
}

std::string core::getAppDataPath()
{
    wchar_t appDataPath[MAX_PATH];
    SHGetFolderPathW(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, appDataPath);

    std::wstring path = std::wstring(appDataPath);

    return std::string(path.begin(), path.end());

}


// Func Definitions of CustomHandler class
void CustomHandler::toastActivated() const {}
void CustomHandler::toastActivated(int actionIndex) const {}
void CustomHandler::toastDismissed(WinToastDismissalReason state) const {}
void CustomHandler::toastFailed() const {}

// Declaration of Configuration Variables
int core::Config::ALERT_PERCENTAGE = 95;
int core::Config::REMIND_AFTER_EVERY = 10;
int core::Config::THEME = 2;
bool core::Config::MESSAGE_BOX_ALERT_PREFERENCE = true;
bool core::Config::TOAST_NOTIFICATION_ALERT_PREFERENCE = true;
bool core::Config::PLUGGED_IN_ALERT = true;
bool core::Config::UNPLUGGED_ALERT = true;
std::string core::Config::LAST_CHARGED = "";