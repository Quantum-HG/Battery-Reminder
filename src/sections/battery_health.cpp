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
            ImGui::NewLine();
            ImGui::Separator();
            ImGui::BulletText("Generate the Latest Battery Report for your Device");
            ImGui::SetItemTooltip("Click to generate a battery report.\nThis is an HTML document will all the relevant informations");

            ImGui::Separator();
            ImGui::NewLine();
            if (ImGui::Button("Generate Battery Report"))
            {
                //executeCommandWithAdmin(L"powercfg /REPORT");
                //execute_cmd(L"powercfg /BATTERYREPORT");
                //system("powercfg /BATTERYREPORT");
                std::string cmd = "powercfg /batteryreport /output " ;
                std::string file_path = core::getAppDataPath() + "\\Battery Reminder\\" + "data\\battery_report.html";
                system((cmd + file_path).c_str());
                core::ShowNotification(L"Success", L"Battery Report Generated Successfully!");
                //system("start battery_report.html");

            }
            ImGui::Separator();

            ImGui::NewLine();
            ImGui::NewLine();
            ImGui::Separator();

            ImGui::BulletText("View the Last Generated Battery Report");
            ImGui::SetItemTooltip("Click to open the last generated battery report in your default browser.\nIt is recommended to generate it first.");
            ImGui::Separator();
            ImGui::NewLine();

            if (ImGui::Button("View Battery Report"))
            {
                std::string file_path = core::getAppDataPath() + "\\Battery Reminder\\" + "data\\battery_report.html";
                ShellExecuteA(NULL, "open", file_path.c_str(), NULL, NULL, SW_SHOWNORMAL);
            }

            ImGui::Separator();

            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    ImGui::EndChildFrame();
}
