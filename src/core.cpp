#include "core.h"

// return the data from file
nlohmann::json core::load_json_data()
{
    std::ifstream file("data.json");

    // Check if the file stream is open
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading" << std::endl;
        exit(1);
    }

    // Create a JSON object
    nlohmann::json data;

    // Read JSON data from the file stream into the JSON object
    try {
        file >> data;
    }
    catch (nlohmann::json::parse_error& e) {
        std::cerr << "Parse error: " << e.what() << std::endl;
        exit(1);
    }

    // Close the file stream
    file.close();

    return data;
}

// Load data from the file 
nlohmann::json core::set_Config(nlohmann::json data)
{
    core::Config::ALERT_PERCENTAGE = data["ALERT_PERCENTAGE"].get<int>();
    core::Config::REMIND_AFTER_EVERY = data["REMIND_AFTER_EVERY"].get<int>();
    core::Config::MESSAGE_BOX_ALERT_PREFERENCE = data["MESSAGE_BOX_ALERT_PREFERENCE"].get<bool>();
    core::Config::TOAST_NOTIFICATION_ALERT_PREFERENCE = data["TOAST_NOTIFICATION_ALERT_PREFERENCE"].get<bool>();
    core::Config::LAST_CHARGED = data["LAST_CHARGED"].get<std::string>();
    return data;
}

// Save data to file
void core::save_data(nlohmann::json loaded_json_data)
{// Create a JSON object
    nlohmann::json j = {
        {"ALERT_PERCENTAGE", core::Config::ALERT_PERCENTAGE},
        {"REMIND_AFTER_EVERY", core::Config::REMIND_AFTER_EVERY},
        {"MESSAGE_BOX_ALERT_PREFERENCE", core::Config::MESSAGE_BOX_ALERT_PREFERENCE},
        {"TOAST_NOTIFICATION_ALERT_PREFERENCE", core::Config::TOAST_NOTIFICATION_ALERT_PREFERENCE},
        {"LAST_CHARGED", core::Config::LAST_CHARGED}
    };

    // "CHARGE_CYCLES", { {core::getDate(),  0}, }
    

    std::ofstream file("data.json");

    // Write the JSON object to the file stream
    file << j;

    // Close the file stream
    file.close();
}

// Toast notifications to notify battery percentage
void core::toast_notification(int battery_percentage, std::wstring caption = L"Unplug your charger")
{
    std::wstring appName = L"Battery Reminder";
    std::wstring appUserModelID = L"Battery Reminder";

    std::vector<std::wstring> words = { L"Your Device Battery is ", std::to_wstring(battery_percentage), L"% charged" };

    std::wstring text;
    for (const auto& word : words) {
        text.append(word);
    }

    // Output the joined string
    std::wcout << text << std::endl;

    std::wstring imagePath = L"app.ico";
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


// get the Battery Status
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

// Shows a Message Box style notification
void core::ShowNotification(const std::wstring& title, const std::wstring& message) {
    // Display a system notification
    MessageBoxW(NULL, message.c_str(), title.c_str(), MB_ICONINFORMATION | MB_SYSTEMMODAL);
}

// Current current date as std::string
std::string core::getDateTime()
{
    // Get the current time point
    auto now = std::chrono::system_clock::now();

    // Convert to time_t to get calendar time
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    // Convert to tm structure for local time
    std::tm localTime;
    localtime_s(&localTime, &now_c); // For Windows; use localtime_r on POSIX

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


// Func Definitions of CustomHandler class
void CustomHandler::toastActivated() const {}
void CustomHandler::toastActivated(int actionIndex) const {}
void CustomHandler::toastDismissed(WinToastDismissalReason state) const {}
void CustomHandler::toastFailed() const {}

// Declaration of Configuration Variables
int core::Config::ALERT_PERCENTAGE = 95;
int core::Config::REMIND_AFTER_EVERY = 10;
bool core::Config::MESSAGE_BOX_ALERT_PREFERENCE = false;
bool core::Config::TOAST_NOTIFICATION_ALERT_PREFERENCE = false;
std::string core::Config::LAST_CHARGED = "";