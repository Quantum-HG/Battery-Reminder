#include "settings.h"


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
