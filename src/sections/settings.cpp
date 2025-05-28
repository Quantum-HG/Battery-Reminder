#include "settings.h"
#include <imgui.h>
#include <Windows.h>

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
            static const char* themes[] = { "Dark", "Classic" };
            static int current_theme = core::Config::THEME;

            if (ImGui::Combo("Select Theme", &current_theme, themes, IM_ARRAYSIZE(themes))) {
                switch (current_theme) {
                case 0: ImGui::StyleColorsDark(); break;
                case 1: ImGui::StyleColorsClassic(); break;
                }
            }

            core::Config::THEME = current_theme;

            ImGui::EndTabItem();

        }

        ImGui::EndTabBar();
    }

    ImGui::EndChildFrame();
}
