#include "dashboard.h"

// The BatteryPercentageWidget to show battery percentage
void BatteryPercentageWidget(core::BatteryStatus& CurrentBatteryStatus, sf::Clock& clock) {
    // Set up sizes
    ImVec2 canvas_size(100, 200);
    float battery_width = 80.0f;
    float battery_height = 160.0f;
    float battery_thickness = 5.0f;
    float cap_height = 12.0f; // Height of the small cap at the top

    // Calculate battery fill height
    float battery_fill_height = battery_height * (CurrentBatteryStatus.battery_percentage / 100.0f);

    // Draw battery outline
    ImGui::BeginGroup();
    ImGui::Dummy(ImVec2(0.0f, 5.0f));
    ImGui::BeginChild("BatteryCanvas", canvas_size);
    ImDrawList* draw_list = ImGui::GetWindowDrawList();


    int val = (int)CurrentBatteryStatus.is_charging ? abs(230.0f * sinf(clock.getElapsedTime().asSeconds())) : 230;
    // Draw battery body
    ImVec2 battery_pos = ImGui::GetCursorScreenPos();
    ImVec2 battery_top_left = battery_pos;
    ImVec2 battery_bottom_right = ImVec2(battery_pos.x + battery_width, battery_pos.y + battery_height);
    draw_list->AddRectFilled(battery_top_left, battery_bottom_right, IM_COL32(230, 230, 230, 255), battery_thickness);
    ImVec2 battery_inner_top_left = ImVec2(battery_top_left.x + battery_thickness, battery_top_left.y + battery_thickness);
    ImVec2 battery_inner_bottom_right = ImVec2(battery_bottom_right.x - battery_thickness, battery_bottom_right.y - battery_thickness);
    draw_list->AddRectFilled(battery_inner_top_left, battery_inner_bottom_right, IM_COL32(230, 230, 230, 255));

    // Draw battery cap
    /*ImVec2 cap_top_left = ImVec2(battery_top_left.x + battery_thickness, battery_top_left.y - cap_height);
    ImVec2 cap_bottom_right = ImVec2(battery_bottom_right.x - battery_thickness, battery_top_left.y);
    draw_list->AddRectFilled(cap_top_left, cap_bottom_right, IM_COL32(230, 230, 230, 230));
    */

    // Draw battery fill
    ImVec2 battery_fill_top_left = ImVec2(battery_inner_top_left.x, battery_bottom_right.y - battery_fill_height + battery_thickness);
    ImVec2 battery_fill_bottom_right = battery_inner_bottom_right;
    draw_list->AddRectFilled(battery_fill_top_left, battery_fill_bottom_right, IM_COL32(0, val, 0, 255));

    ImGui::EndChild();
    ImGui::EndGroup();
}



// DashBoard section of the app
void show_dashboard(core::BatteryStatus& CurrentBatteryStatus, sf::Clock& clock, nlohmann::json loaded_json_data)
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
            BatteryPercentageWidget(CurrentBatteryStatus, clock);
            ImGui::SameLine();

            ImGui::SetCursorPosX(250);
            ImGui::SetCursorPosX(250);
            ImGui::BeginChild(ImGui::GetID("BatteryInfo"), ImVec2(300, 300));

            ImGui::Text("Battery Percentage : %i%%", (int)CurrentBatteryStatus.battery_percentage);

            ImGui::Text("Charging Status : ");
            ImGui::SameLine();
            ImVec4 color = (CurrentBatteryStatus.is_charging ? ImVec4(0, 255, 0, 255) : ImVec4(255, 255, 255, 255));
            ImGui::TextColored(color, (CurrentBatteryStatus.is_charging ? "Charging" : "Not Charging"));
            ImGui::Text("Last Charged : %s%", core::Config::LAST_CHARGED.c_str());

            ImGui::EndChild();

            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    ImGui::EndChildFrame();
}
