#include "battery_health.h"



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
