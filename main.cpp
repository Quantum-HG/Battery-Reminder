#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "core.h"
#include "wintoastlib.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include "sections.h"
#include <ctime>
#include <chrono>



int main()
{
    

    bool was_charging = false;
    core::get_BatteryStatus().is_charging;

    nlohmann::json loaded_json_data = core::load_data();
    // Initialize ImGui and ImGui-SFML
    sf::RenderWindow window(sf::VideoMode(900, 544), "Battery Reminder");
    ImGui::SFML::Init(window);
    window.setFramerateLimit(60);
    sf::Clock clock;
    
    // Load and Set the Font
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("Orbitron-Black.ttf", 16.0f);
    ImGui::SFML::UpdateFontTexture();    
    ImGui::StyleColorsClassic();
    ImGuiStyle& style = ImGui::GetStyle();
    style.GrabRounding = 12.f;
    sf::Image icon;
    icon.loadFromFile("assests/flash.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    while (window.isOpen())
    {
        

        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Start new ImGui frame
        ImGui::SFML::Update(window, sf::seconds(1.f / 60.f));

        
        core::BatteryStatus CurrentBatteryStatus = core::get_BatteryStatus();
        
        
        std::string today = core::getDate();
        if (not was_charging)
        {
            if (CurrentBatteryStatus.is_charging)
            {
                // loaded_json_data["CHARGE_CYCLES"][core::getDate()] += 1;
            }
        }
        was_charging = CurrentBatteryStatus.is_charging;
        
        // std::cout << "w- " << window.getSize().x << ", h- " << window.getSize().y << std::endl;
        
        // ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)); // Change frame background color
        ImGui::Begin("Hello, ImGui!",nullptr, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoScrollbar);
        // ImGui::Begin("Hello, ImGui!",nullptr, ImGuiWindowFlags_NoMove);
       

        
        if (CurrentBatteryStatus.is_charging)
        {
            ImGui::GetForegroundDrawList()->AddRect(ImVec2(0, 0), ImVec2(ImGui::GetWindowSize().x - 10, ImGui::GetWindowSize().y - 20), IM_COL32(0, 230, 0, abs(250.0f * sinf(clock.getElapsedTime().asSeconds()))), 0.0f, 0, 4);
        }
        //sf::Texture texture;
        // texture.loadFromFile("flash.png");
        //ImGui::Image(texture);
        
        ImGui::BeginChildFrame(ImGui::GetID("ScrollingRegion"), ImVec2(250, 500));


        if (ImGui::Selectable("DashBoard", Selectable_state::DashBoard))
        {
            false_all_states();
            Selectable_state::DashBoard = true;
            
        }
        if (ImGui::Selectable("Battery Health", Selectable_state::Battery_Health))
        {
            false_all_states();
            Selectable_state::Battery_Health = true;
            }
        if (ImGui::Selectable("Alerts and Notifications", Selectable_state::Alerts_and_Notifications))
        {
            false_all_states();
            Selectable_state::Alerts_and_Notifications = true;
        }
        if (ImGui::Selectable("Settings", Selectable_state::Settings))
        {
            false_all_states();
        Selectable_state::Settings = true;
        }


        ImGui::ShowDemoWindow(); 
        ImGui::EndChildFrame();

        // Widgets inside the container
        ImGui::SameLine();


        
        if (Selectable_state::DashBoard == true)
        {
            show_dashboard(CurrentBatteryStatus, clock);
        }
        else if (Selectable_state::Alerts_and_Notifications == true)
        {
            show_alerts_and_notification(CurrentBatteryStatus);
        }
        else if (Selectable_state::Battery_Health == true)
        {
            show_battery_health();
        }
        else if (Selectable_state::Settings == true)
        {
            show_settings();
        }


        if (ImGui::Button("Save Changes"))
        {
            core::save_data(loaded_json_data);
            core::ShowNotification(L"Success", L"Your changes have been saved");
        }
        

        ImGui::End();
        // ImGui::PopStyleColor();

       



        // Render ImGui
        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    // Shutdown ImGui and ImGui-SFML
    ImGui::SFML::Shutdown();

    
    return 0;
}
