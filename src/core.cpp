#include "core.h"

// Load data from the file 
nlohmann::json core::load_data()
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

    core::Config::ALERT_PERCENTAGE = data["ALERT_PERCENTAGE"];
    core::Config::REMIND_AFTER_EVERY = data["REMIND_AFTER_EVERY"];
    core::Config::MESSAGE_BOX_ALERT_PREFERENCE = data["MESSAGE_BOX_ALERT_PREFERENCE"];
    core::Config::TOAST_NOTIFICATION_ALERT_PREFERENCE = data["TOAST_NOTIFICATION_ALERT_PREFERENCE"];

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
        {"CHARGE_CYCLES", loaded_json_data["CHARGE_CYCLES"]}
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
    std::wstring appName = L"Full Battery Reminder";
    std::wstring appUserModelID = L"Full Battery Reminder";

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

// The BatteryPercentageWidget to show battery percentage
void core::BatteryPercentageWidget(core::BatteryStatus& CurrentBatteryStatus, sf::Clock& clock) {
    // Set up sizes
    ImVec2 canvas_size(100, 200);
    float battery_width = 80.0f;
    float battery_height = 160.0f;
    float battery_thickness = 5.0f;
    float cap_height = 12.0f; // Height of the small cap at the top

    // Calculate battery fill height
    float battery_fill_height = battery_height * (CurrentBatteryStatus.battery_percentage / 100.0f);

    // Draw battery outline
    ImGui::BeginGroup();
    ImGui::Dummy(ImVec2(0.0f, 5.0f));
    ImGui::BeginChild("BatteryCanvas", canvas_size);
    ImDrawList* draw_list = ImGui::GetWindowDrawList();


    int val = (int)CurrentBatteryStatus.is_charging ? abs(230.0f * sinf(clock.getElapsedTime().asSeconds())) : 230;
    // Draw battery body
    ImVec2 battery_pos = ImGui::GetCursorScreenPos();
    ImVec2 battery_top_left = battery_pos;
    ImVec2 battery_bottom_right = ImVec2(battery_pos.x + battery_width, battery_pos.y + battery_height);
    draw_list->AddRectFilled(battery_top_left, battery_bottom_right, IM_COL32(230, 230, 230, 255), battery_thickness);
    ImVec2 battery_inner_top_left = ImVec2(battery_top_left.x + battery_thickness, battery_top_left.y + battery_thickness);
    ImVec2 battery_inner_bottom_right = ImVec2(battery_bottom_right.x - battery_thickness, battery_bottom_right.y - battery_thickness);
    draw_list->AddRectFilled(battery_inner_top_left, battery_inner_bottom_right, IM_COL32(230, 230, 230, 255));

    // Draw battery cap
    /*ImVec2 cap_top_left = ImVec2(battery_top_left.x + battery_thickness, battery_top_left.y - cap_height);
    ImVec2 cap_bottom_right = ImVec2(battery_bottom_right.x - battery_thickness, battery_top_left.y);
    draw_list->AddRectFilled(cap_top_left, cap_bottom_right, IM_COL32(230, 230, 230, 230));
    */

    // Draw battery fill
    ImVec2 battery_fill_top_left = ImVec2(battery_inner_top_left.x, battery_bottom_right.y - battery_fill_height + battery_thickness);
    ImVec2 battery_fill_bottom_right = battery_inner_bottom_right;
    draw_list->AddRectFilled(battery_fill_top_left, battery_fill_bottom_right, IM_COL32(0, val, 0, 255));

    ImGui::EndChild();
    ImGui::EndGroup();
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
std::string core::getDate()
{
    // Get the current time point
    auto now = std::chrono::system_clock::now();

    // Convert to time_t to get the calendar time
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    // Convert to tm structure for local time
    std::tm localTime;
    localtime_s(&localTime, &now_c); // Use localtime_r for POSIX systems

    std::string date = std::to_string(localTime.tm_mday) + "-" + std::to_string(localTime.tm_mon) + "-" + std::to_string(localTime.tm_year + 1900);

    return date;
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
int core::Config::CHARGE_CYCLE_COUNT_TODAY = 0;