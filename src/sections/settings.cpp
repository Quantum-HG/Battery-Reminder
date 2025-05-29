#include "settings.h"
#include <imgui.h>
#include <Windows.h>

void customTheme()
{
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.04f, 0.18f, 0.10f, 0.40f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.66f, 0.16f, 0.80f);
    colors[ImGuiCol_TabActive] = ImVec4(0.18f, 0.57f, 0.26f, 0.84f);
    colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.00f, 0.40f, 0.00f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 0.64f, 0.08f, 0.69f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.95f, 1.00f, 0.00f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.89f, 1.00f, 0.00f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.86f, 1.00f, 0.00f, 0.67f);
    colors[ImGuiCol_Button] = ImVec4(0.00f, 0.61f, 0.06f, 0.62f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.00f, 0.71f, 0.05f, 0.79f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 0.80f, 0.08f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.00f, 0.90f, 0.12f, 0.45f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.73f, 0.08f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.01f, 0.87f, 0.13f, 0.80f);
    colors[ImGuiCol_Separator] = ImVec4(0.00f, 0.81f, 0.04f, 0.60f);
    colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.50f, 0.01f, 0.79f);
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.01f, 0.40f, 0.18f, 1.00f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.45f, 0.02f, 1.00f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.00f, 0.33f, 0.09f, 1.00f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.00f, 1.00f, 0.16f, 0.07f);
}

// Settings section of the app
void show_settings()
{
    if (ImGui::BeginTabBar("Settings"))
    {
        if (ImGui::BeginTabItem("Settings"))
        {
            static const char* themes[] = {"Default", "Dark", "Classic" };
            static int current_theme = core::Config::THEME;

            if (ImGui::Combo("Select Theme", &current_theme, themes, IM_ARRAYSIZE(themes))) {
                switch (current_theme) {
                case 0: customTheme(); break;
                case 1: ImGui::StyleColorsDark(); break;
                case 2: ImGui::StyleColorsClassic(); break;
                }
            }

            core::Config::THEME = current_theme;

            ImGui::EndTabItem();

        }

        ImGui::EndTabBar();
    }
}
