#include "sections.h"

// Whichever section's state is true, is displayed as the current tab
// (Declarations)
bool Selectable_state::DashBoard = true; // ---------> The Default tab 
bool Selectable_state::Settings = false;
bool Selectable_state::Battery_Health = false;
bool Selectable_state::Alerts_and_Notifications = false;

// set all the states of Selectable_state to false
void false_all_states()
{
    Selectable_state::DashBoard = Selectable_state::Settings = Selectable_state::Alerts_and_Notifications = Selectable_state::Battery_Health = false;

}

// DashBoard section of the app
void show_dashboard(core::BatteryStatus& CurrentBatteryStatus, sf::Clock& clock)
{
    ImGui::BeginChildFrame(ImGui::GetID("TabRegion"), ImVec2(650, 500));
    ImGui::Text("DashBoard");
    ImGui::Separator();
    if (ImGui::BeginTabBar("DashBoard"))
    {
        if (ImGui::BeginTabItem("DashBoard"))
        {
            ImGui::NewLine();
            ImGui::NewLine();
            ImGui::SetCursorPosX(50);
            core::BatteryPercentageWidget(CurrentBatteryStatus, clock);
            ImGui::SameLine();

            ImGui::SetCursorPosX(250);
            ImGui::SetCursorPosX(250);
            ImGui::BeginChild(ImGui::GetID("BatteryInfo"), ImVec2(300, 300));

            ImGui::Text("Battery Percentage : %i%%", (int)CurrentBatteryStatus.battery_percentage);

            ImGui::Text("Charging Status : ");
            ImGui::SameLine();
            ImVec4 color = (CurrentBatteryStatus.is_charging ? ImVec4(0, 255, 0, 255) : ImVec4(255, 255, 255, 255));
            ImGui::TextColored(color, (CurrentBatteryStatus.is_charging ? "Charging" : "Not Charging"));
            ImGui::EndChild();

            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    ImGui::EndChildFrame();
}

// Alerts and notification section of the app
void show_alerts_and_notification(core::BatteryStatus& battery_status)
{
    ImGui::BeginChildFrame(ImGui::GetID("TabRegion"), ImVec2(650, 500));
    ImGui::Text("Alerts and Notifications");
    ImGui::Separator();
    if (ImGui::BeginTabBar("Alerts and Notifications"))
    {
        if (ImGui::BeginTabItem("Alerts and Notifications"))
        {
            ImGui::NewLine();
            ImGui::Separator();
            ImGui::BulletText("Notification Preferences");
            ImGui::Separator();
            ImGui::NewLine();
            std::string text1 = "Alert me when the Battery Reaches " + std::to_string(core::Config::ALERT_PERCENTAGE) + "%%";
            ImGui::Text(text1.c_str());
            ImGui::SliderInt("Alert Percentage", &core::Config::ALERT_PERCENTAGE, 1, 100);
            ImGui::NewLine();

            ImGui::Separator();

            std::string text2 = "Once the battery reaches " + std::to_string(core::Config::ALERT_PERCENTAGE) + "%%, send alerts repeatedly after every " + std::to_string(core::Config::REMIND_AFTER_EVERY) + " seconds";
            ImGui::Text(text2.c_str());
            ImGui::SliderInt("Repeat Interval", &(core::Config::REMIND_AFTER_EVERY), 10, 60);
            ImGui::NewLine();

            ImGui::Separator();

            ImGui::BulletText("Notification Type");
            ImGui::Separator();
            ImGui::NewLine();
            //ImGui::BeginChildFrame(ImGui::GetID("Notification Type"), ImVec2(700, 100));

            ImGui::Checkbox("Message Box Notification", &core::Config::MESSAGE_BOX_ALERT_PREFERENCE);

            ImGui::SameLine();

            ImGui::SetCursorPosX(300);
            if (ImGui::Button("Show Example MessageBox Alert"))
            {
                core::ShowNotification(L"Example Alert", L"You'll receive alerts like these");
            }

            ImGui::NewLine();

            ImGui::Checkbox("Toast Notification", &core::Config::TOAST_NOTIFICATION_ALERT_PREFERENCE);

            ImGui::SameLine();

            ImGui::SetCursorPosX(300);
            if (ImGui::Button("Show Example Toast Alert", ImVec2(255, 20)))
            {
                core::toast_notification((int)battery_status.battery_percentage, L"You'll receive notifications like these");
            }





            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }



    ImGui::EndChildFrame();


}

// Settings section of the app
void show_settings()
{
    ImGui::BeginChildFrame(ImGui::GetID("TabRegion"), ImVec2(650, 500));
    ImGui::Text("Settings");
    ImGui::Separator();
    if (ImGui::BeginTabBar("Settings"))
    {
        if (ImGui::BeginTabItem("Settings"))
        {
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    ImGui::EndChildFrame();
}

// Battery Health Section of the app
void show_battery_health()
{
    ImGui::BeginChildFrame(ImGui::GetID("TabRegion"), ImVec2(650, 500));
    ImGui::Text("Battery Health");
    ImGui::Separator();
    if (ImGui::BeginTabBar("Battery Health"))
    {
        if (ImGui::BeginTabItem("Battery Health"))
        {
            if (ImGui::Button("execute"))
            {
                //executeCommandWithAdmin(L"powercfg /REPORT");
                //execute_cmd(L"powercfg /BATTERYREPORT");
                system("powercfg /BATTERYREPORT");
            }

            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    ImGui::EndChildFrame();
}
