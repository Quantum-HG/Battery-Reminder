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
                std::string reportPath = core::getAppDataPath() + "\\Battery Reminder\\data\\battery_report.html";
                std::string command = "powercfg /batteryreport /output \"" + reportPath + "\"";


                ShellExecuteA(NULL,"open","cmd.exe",("/C " + command).c_str(), NULL,SW_HIDE);
                //std::string cmd = "powercfg /batteryreport /output " ;
                //std::string file_path = core::getAppDataPath() + "\\Battery Reminder\\" + "data\\battery_report.html";
                //std::string final_path = "\"" + file_path + "\"";
                ////system((cmd + final_path).c_str());
                //ShellExecuteA(NULL, "open", (cmd + final_path).c_str(), NULL, NULL, SW_HIDE);
                ////ImGui::Text((cmd + final_path).c_str());
                core::ShowNotification(L"Success", L"Battery Report Generated Successfully!");

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
                std::cout << file_path.c_str() << std::endl;
                //system(file_path.c_str());
                ShellExecuteA(NULL, "open", file_path.c_str(), NULL, NULL, SW_HIDE);
            }

            ImGui::Separator();

            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    ImGui::EndChildFrame();
}
