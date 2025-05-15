#include "dashboard.h"



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
