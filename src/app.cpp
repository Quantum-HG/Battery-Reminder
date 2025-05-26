#include "app.h"
#define FONT_PATH "assets\\Roboto-Medium.ttf"
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 544
//#define SHOW_DEMO_WINDOW 

App::App() {
    io = nullptr;
    style = nullptr;
}

App::~App() {}

void App::run() {
    init();
    while (window.isOpen()) {
        handleInputs();
        startframe();
        mainloop();
        update();
        endframe();
    }
    shutDown();
}

void App::init()
{
    loaded_json_data = core::load_json_data();

    // Set Configs from the loaded json data
    core::set_Config(loaded_json_data);

    initWindow();
    initImGui();
    initImGuiIO();
    initImGuiStyles();
}

void App::initWindow() {

    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Battery_Reminder", sf::Style::Close);
    window.setFramerateLimit(60);

    // set window icon

    /*sf::Image icon;
    if (!icon.loadFromFile("assets\\icon.png")) {
        std::cerr << "Failed to load icon.\n";
    }
    else {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }*/
}

void App::initImGui() {
    // TODO: init ImGui-SFML
    ImGui::SFML::Init(window);
}

void App::initImGuiIO() {
    // TODO: load fonts, set ImGui IO settings

    io = &ImGui::GetIO();
    io->Fonts->Clear();
    io->Fonts->AddFontFromFileTTF(FONT_PATH, 16.0f);
    ImGui::SFML::UpdateFontTexture();
    io->IniFilename = std::string(core::getAppDataPath() + "\\Battery Reminder\\" + "data\\imgui.ini").c_str();
}

void App::initImGuiStyles() {

    switch (core::Config::THEME) {
    case 0: ImGui::StyleColorsDark(); break;
    case 1: ImGui::StyleColorsClassic(); break;
    }

    style = &ImGui::GetStyle();
    style->GrabRounding = 12.f;

}

void App::handleInputs() {

    // handling sfml inputs
    sf::Event event;
    while (window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);

        if (event.type == sf::Event::Closed)
        {
            core::save_data(); // save data before closing
            window.close();
        }
    }
}

void App::startframe() {

    // Start new ImGui frame
    ImGui::SFML::Update(window, sf::seconds(1.f / 60.f));
}

void App::mainloop() {
    // MAIN LOOP LOGIC
    //=========================================================================================================================================================================================================================================================

    currentBatteryStatus = core::get_BatteryStatus();

    was_charging = currentBatteryStatus.is_charging;

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2( static_cast<int> (this->window.getSize().x), static_cast<int> (this->window.getSize().y)));
    ImGui::Begin("Battery Reminder!", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar);


    if (currentBatteryStatus.is_charging)
    {
        ImGui::GetForegroundDrawList()->AddRect(ImVec2(2, 2), ImVec2(897, 541), 
            IM_COL32(
                (currentBatteryStatus.battery_percentage<=20 ? 200 : 0),
                (currentBatteryStatus.battery_percentage > 20 ? 200 : 0),
                0,
                abs(250.0f * sinf(clock.getElapsedTime().asSeconds()))), 0.0f, 0, 4);
    }

    ImGui::BeginChildFrame(ImGui::GetID("ScrollingRegion"), ImVec2(250, 500));

    if (ImGui::Selectable("DashBoard", currentSection == AppSections::DashBoard))
        currentSection = AppSections::DashBoard;

    else if (ImGui::Selectable("Battery Health", currentSection == AppSections::Battery_Health))
        currentSection = AppSections::Battery_Health;

    else if (ImGui::Selectable("Alerts and Notifications", currentSection == AppSections::Alerts_and_Notifications))
        currentSection = AppSections::Alerts_and_Notifications;

    else if (ImGui::Selectable("Settings", currentSection == AppSections::Settings))
        currentSection = AppSections::Settings;

    #ifdef SHOW_DEMO_WINDOW
    ImGui::ShowDemoWindow();
    #endif 

    ImGui::EndChildFrame();

    ImGui::SameLine();


    if (currentSection == AppSections::DashBoard)
    {
        show_dashboard(currentBatteryStatus, clock, loaded_json_data);
    }
    else if (currentSection == AppSections::Alerts_and_Notifications)
    {
        show_alerts_and_notification(currentBatteryStatus);
    }
    else if (currentSection == AppSections::Battery_Health)
    {
        show_battery_health();
    }
    else if (currentSection == AppSections::Settings)
    {
        show_settings();
    }


    if (ImGui::Button("Save Changes"))
    {
        core::save_data();
        core::ShowNotification(L"Success", L"Your changes have been saved");
    }


    ImGui::End();
    //=========================================================================================================================================================================================================================================================

}

void App::update() {}

void App::endframe() {

    // Render ImGui
    window.clear();
    ImGui::SFML::Render(window);
    window.display();
}

void App::shutDown() {

    // Shutdown ImGui and ImGui-SFML
    ImGui::SFML::Shutdown();
}