#include "settings.h"
#include <imgui.h>
#include <Windows.h>

void OpenHyperlink(const char* url) {
    ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}

void ShowHyperlink(const char* label, const char* url) {
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.26f, 0.59f, 0.98f, 1.0f));
    ImGui::Text("%s", label);
    ImGui::PopStyleColor();

    if (ImGui::IsItemHovered())
    {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
        ImGui::BeginTooltip();
        ImGui::TextUnformatted(url);
        ImGui::EndTooltip();
    }

    if (ImGui::IsItemClicked()) {
        OpenHyperlink(url);
    }
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
            static const char* themes[] = { "Dark", "Classic" };
            static int current_theme = core::Config::THEME;

            if (ImGui::Combo("Select Theme", &current_theme, themes, IM_ARRAYSIZE(themes))) {
                switch (current_theme) {
                case 0: ImGui::StyleColorsDark(); break;
                case 1: ImGui::StyleColorsClassic(); break;
                }
            }

            core::Config::THEME = current_theme;

            ImGui::NewLine();
            ImGui::Separator();
            ImGui::NewLine();

            ImGui::Text("Battery Reminder");
            //ImGui::Text("Version: 1.0.0");
            ImGui::Text("Copyright (c) 2025 Quantum-HG");
            ImGui::Text("Licensed under the MIT License.");
            ShowHyperlink("GitHub Repository", "https://github.com/Quantum-HG/Battery-Reminder");
            ShowHyperlink("View License", "https://github.com/Quantum-HG/Battery-Reminder/blob/master/LICENSE");
            ShowHyperlink("Report Issues", "https://github.com/Quantum-HG/Battery-Reminder/discussions");


            ImGui::EndTabItem();

        }

        ImGui::EndTabBar();
    }

    ImGui::EndChildFrame();
}
