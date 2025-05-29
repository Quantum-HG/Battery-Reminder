#include "battery_health.h"



// Battery Health Section of the app
void show_battery_health()
{
    if (ImGui::BeginTabBar("Battery Health"))
    {
        if (ImGui::BeginTabItem("Battery Health"))
        {
            ImGui::NewLine();
            ImGui::Separator();
            ImGui::BulletText("Generate the Latest Battery Report for your Device");

            ImGui::Separator();
            ImGui::NewLine();
            if (ImGui::Button("Generate Battery Report"))
            {
                std::string reportPath = core::getAppDataPath() + "\\Battery Reminder\\data\\battery_report.html";
                std::string command = "powercfg /batteryreport /output \"" + reportPath + "\"";


                ShellExecuteA(NULL,"open","cmd.exe",("/C " + command).c_str(), NULL,SW_HIDE);
                core::ShowNotification(L"Success", L"Battery Report Generated Successfully!");

            }

            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip("Click to generate a detailed Battery Report of your System.");
            }

            ImGui::Separator();

            ImGui::NewLine();
            ImGui::NewLine();
            ImGui::Separator();

            ImGui::BulletText("View the Last Generated Battery Report");
            ImGui::Separator();
            ImGui::NewLine();

            if (ImGui::Button("View Battery Report"))
            {
                std::string file_path = core::getAppDataPath() + "\\Battery Reminder\\" + "data\\battery_report.html";
                std::cout << file_path.c_str() << std::endl;

                try
                {
                    ShellExecuteA(NULL, "open", file_path.c_str(), NULL, NULL, SW_HIDE);
				}
                catch (const std::exception& e)
                {
                    core::ShowNotification(L"Error", L"Battery Report not found. Please generate it first.");
                    return;
                }
            }

            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip("Click to open the last generated Battery Report.\nIt is recommended to generate it first.");
            }

            ImGui::Separator();

            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
}
