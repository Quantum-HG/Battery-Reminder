#include "alerts_and_notifications.h"

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

            ImGui::Checkbox("Message Box Notification", &core::Config::MESSAGE_BOX_ALERT_PREFERENCE);

            ImGui::SameLine();

            ImGui::SetCursorPosX(300);
            if (ImGui::Button("      Show Example MessageBox Alert      "))
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

            ImGui::NewLine();
            ImGui::Separator();
            ImGui::BulletText("Charging Alerts");
            ImGui::Separator();
            ImGui::NewLine();

            ImGui::Checkbox("Alert on Charger Plugged                    ", &core::Config::PLUGGED_IN_ALERT);
            
            ImGui::SameLine();

            ImGui::Checkbox("Alert on Charger Unplugged", &core::Config::UNPLUGGED_ALERT);

            ImGui::NewLine();

            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }



    ImGui::EndChildFrame();


}
