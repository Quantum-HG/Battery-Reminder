#pragma once
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

class App
{
public:
    App();
    ~App();
	// runs the app
	void run();

private:
    sf::RenderWindow window;    // the sfml app window
    sf::Clock clock;            // the sfml app clock
    sf::Image icon;             // the sfml app icon
    ImGuiIO* io;                // imGui IO 
    ImGuiStyle* style;          // imGui style
    core::BatteryStatus CurrentBatteryStatus;
    bool was_charging = false;
    nlohmann::json loaded_json_data;

    
    void init();
    void initWindow();
    void initImGui();
    void initImGuiIO();
    void initImGuiStyles();
    void handleInputs();
    void startframe();
    void mainloop();
    void endframe();
    void update();
    void shutDown();

};

