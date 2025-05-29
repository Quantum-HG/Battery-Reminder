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


    // Draw battery body
    ImVec2 battery_pos = ImGui::GetCursorScreenPos();
    ImVec2 battery_top_left = battery_pos;
    ImVec2 battery_bottom_right = ImVec2(battery_pos.x + battery_width, battery_pos.y + battery_height);
    draw_list->AddRectFilled(battery_top_left, battery_bottom_right, IM_COL32(230, 230, 230, 255), battery_thickness);
    
    ImVec2 cap_top_left = ImVec2(battery_pos.x + 10, battery_pos.y - 150);
    ImVec2 cap_bottom_right = ImVec2(battery_bottom_right.x, battery_pos.y + battery_height);
    //draw_list->AddRectFilled(cap_top_left, cap_bottom_right, IM_COL32(230, 0, 0, 230));
    
    ImVec2 battery_inner_top_left = ImVec2(battery_top_left.x + battery_thickness, battery_top_left.y + battery_thickness);
    ImVec2 battery_inner_bottom_right = ImVec2(battery_bottom_right.x - battery_thickness, battery_bottom_right.y - battery_thickness);
    //draw_list->AddRectFilled(battery_inner_top_left, battery_inner_bottom_right, IM_COL32(230, 230, 230, 255));

    // Draw battery cap

    // Draw battery fill
    ImVec2 battery_fill_top_left = ImVec2(battery_inner_top_left.x, battery_bottom_right.y - battery_fill_height + battery_thickness);
    ImVec2 battery_fill_bottom_right = battery_inner_bottom_right;
    ImVec4 level_color = getBatteryLevelColor(CurrentBatteryStatus, clock);
    draw_list->AddRectFilled
    (battery_fill_top_left,
    battery_fill_bottom_right,
    IM_COL32(level_color.x * 200,
            level_color.y * 200,
            level_color.z * 200,
            255));

    ImGui::EndChild();
    ImGui::EndGroup();
}

ImVec4 getBatteryLevelColor(core::BatteryStatus& CurrentBatteryStatus, sf::Clock& clock) {
	
    ImVec4 color;
    float val = (float)CurrentBatteryStatus.is_charging ? abs(sinf(clock.getElapsedTime().asSeconds())) : 1.f;
    
    if (CurrentBatteryStatus.battery_percentage <= 20) {
		color = ImVec4(1.0f * val, 0.0f, 0.0f, 1.0f); // Red for low battery
	} else if (CurrentBatteryStatus.battery_percentage <= 70) {
		color = ImVec4(1.0f * val, 1.0f * val, 0.0f, 1.0f); // Yellow for medium battery
	} else {
		color = ImVec4(0.0f, 1.0f * val, 0.0f, 1.0f); // Green for high battery
	}
    return color;
}

// DashBoard section of the app
void show_dashboard(core::BatteryStatus& CurrentBatteryStatus, sf::Clock& clock, nlohmann::json loaded_json_data)
{
    if (ImGui::BeginTabBar("DashBoard"))
    {
        if (ImGui::BeginTabItem("DashBoard"))
        {
            // Get the latest "LAST_CHARGED" value from the JSON data
            core::Config::LAST_CHARGED = core::load_json_data()["LAST_CHARGED"].get<std::string>();
            ImGui::NewLine();
            ImGui::NewLine();
            ImGui::SetCursorPosX(250);
            BatteryPercentageWidget(CurrentBatteryStatus, clock);
            ImGui::SameLine();

            ImGui::SetCursorPosX(200);
            //ImGui::BeginChild(ImGui::GetID("BatteryInfo"), ImVec2(340, 300));

            ImGui::NewLine();

            if (ImGui::BeginTable("BatteryInfoTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 160.0f);
                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 160.f);
                //ImGui::TableHeadersRow();

                // Row 1: User
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("User");
                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%s", core::getWindowsUsername().c_str());

                // Row 2: Battery Percentage
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("Battery Percentage");
                ImGui::TableSetColumnIndex(1);
                ImVec4 level_color = getBatteryLevelColor(CurrentBatteryStatus, clock);
                ImGui::TextColored(level_color,"%d%%", static_cast<int>(CurrentBatteryStatus.battery_percentage));

                // Row 3: Charging Status
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("Charging Status");
                ImGui::TableSetColumnIndex(1);
                ImVec4 color = (CurrentBatteryStatus.is_charging ? ImVec4(0.0f, 1.0f, 0.0f, 1.0f) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                ImGui::TextColored(color, "%s", (CurrentBatteryStatus.is_charging ? "Charging" : "Not Charging"));

                // Row 4: Last Charged
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("Last Charged");
                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%s", core::Config::LAST_CHARGED.c_str());

                ImGui::EndTable();
            }

            //ImGui::EndChild();

            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

}
