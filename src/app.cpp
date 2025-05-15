#include "app.h"


App::App() {
    // Empty constructor
    io = nullptr;
    style = nullptr;
}

App::~App() {
    // Empty destructor
}

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

void App::init() {
    // TODO: call initWindow, initImGui, etc.

    loaded_json_data = core::load_data();

    initWindow();
    initImGui();
    initImGuiIO();
    initImGuiStyles();
}

void App::initWindow() {
    // TODO: create SFML window and set icon

    window.create(sf::VideoMode(900, 544), "Battery Reminder");
    window.setFramerateLimit(60);

    // set window icon
    sf::Image icon;
    if (!icon.loadFromFile("assets/flash.png")) {
        std::cerr << "Failed to load icon.\n";
    }
    else {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
}

void App::initImGui() {
    // TODO: init ImGui-SFML
    ImGui::SFML::Init(window);
}

void App::initImGuiIO() {
    // TODO: load fonts, set ImGui IO settings

    io = &ImGui::GetIO();
    io->Fonts->Clear();
    io->Fonts->AddFontFromFileTTF("Orbitron-Black.ttf", 16.0f);
    ImGui::SFML::UpdateFontTexture();

    
}

void App::initImGuiStyles() {
    // TODO: set ImGui styles

    // Changing the style
    ImGui::StyleColorsClassic();

    style = &ImGui::GetStyle();
    style->GrabRounding = 12.f;

}

void App::handleInputs() {
    // TODO: handle SFML and ImGui events

    // handling sfml inputs
    sf::Event event;
    while (window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);

        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void App::startframe() {
    // TODO: begin ImGui frame

    // Start new ImGui frame
    ImGui::SFML::Update(window, sf::seconds(1.f / 60.f));
}

void App::mainloop() {
    // MAIN LOOP LOGIC
    //=========================================================================================================================================================================================================================================================


    currentBatteryStatus = core::get_BatteryStatus();

    if (not was_charging)
    {
        if (currentBatteryStatus.is_charging)
        {
            // loaded_json_data["CHARGE_CYCLES"][core::getDate()] += 1;
        }
    }
    was_charging = currentBatteryStatus.is_charging;

    // std::cout << "w- " << window.getSize().x << ", h- " << window.getSize().y << std::endl;

    // ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)); // Change frame background color
    ImGui::Begin("Hello, ImGui!", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);
    // ImGui::Begin("Hello, ImGui!",nullptr, ImGuiWindowFlags_NoMove);



    if (currentBatteryStatus.is_charging)
    {
        ImGui::GetForegroundDrawList()->AddRect(ImVec2(0, 0), ImVec2(ImGui::GetWindowSize().x - 10, ImGui::GetWindowSize().y - 20), IM_COL32(0, 230, 0, abs(250.0f * sinf(clock.getElapsedTime().asSeconds()))), 0.0f, 0, 4);
    }
    //sf::Texture texture;
    // texture.loadFromFile("flash.png");
    //ImGui::Image(texture);

    ImGui::BeginChildFrame(ImGui::GetID("ScrollingRegion"), ImVec2(250, 500));


    if (ImGui::Selectable("DashBoard", currentSection == AppSections::DashBoard))
    {
        currentSection = AppSections::DashBoard;
    }
    else if (ImGui::Selectable("Battery Health", currentSection == AppSections::Battery_Health))
    {
        currentSection = AppSections::Battery_Health;
    }
    else if (ImGui::Selectable("Alerts and Notifications", currentSection == AppSections::Alerts_and_Notifications))
    {
        currentSection = AppSections::Alerts_and_Notifications;
    }
    else if (ImGui::Selectable("Settings", currentSection == AppSections::Settings))
    {
        currentSection = AppSections::Settings;
    }


    ImGui::ShowDemoWindow();
    ImGui::EndChildFrame();

    // Widgets inside the container
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
        core::save_data(loaded_json_data);
        core::ShowNotification(L"Success", L"Your changes have been saved");
    }


    ImGui::End();
    // ImGui::PopStyleColor();


    //=========================================================================================================================================================================================================================================================

}

void App::update() {
    // TODO: update app logic if needed
}

void App::endframe() {
    // TODO: render ImGui and display

    // Render ImGui
    window.clear();
    ImGui::SFML::Render(window);
    window.display();
}

void App::shutDown() {
    // TODO: cleanup ImGui-SFML

    // Shutdown ImGui and ImGui-SFML
    ImGui::SFML::Shutdown();
}