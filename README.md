# Battery Reminder

**Battery Reminder** is a lightweight Windows desktop application developed in C++. It notifies users when their laptop battery is fully charged. The application features a custom user interface built with ImGui, utilizes SFML for rendering, and delivers native Windows toast notifications via WinToastLib.

## Application Preview

![Application UI](media/preview.gif)

---

## Features

- Native Windows toast notifications
- Custom user interface using ImGui
- Persistent settings and data stored in JSON format
- Lightweight, fast, and open-source

---

## Technologies Used

- C++17
- [SFML](https://www.sfml-dev.org/) – Multimedia and graphics library
- [ImGui](https://github.com/ocornut/imgui) – Immediate mode GUI
- [ImGui-SFML](https://github.com/eliasdaler/imgui-sfml) – SFML bindings for ImGui
- [WinToastLib](https://github.com/mohabouje/WinToast) – Native Windows toast notification library
- [nlohmann/json](https://github.com/nlohmann/json) – JSON for Modern C++

---

## Getting Started

### Requirements

- Windows 10 or 11
- C++17-compatible compiler (MSVC recommended)
- SFML 2.5 or later
- ImGui and ImGui-SFML
- WinToastLib
- nlohmann/json

### Build Instructions

1. Clone the repository:

    ```bash
    git clone https://github.com/Quantum-HG/Battery-Reminder.git
    cd Battery-Reminder
    ```

2. Open the project in your preferred IDE (e.g., Visual Studio or Code::Blocks) and add the source files.

3. Link the following libraries:

    - sfml-graphics
    - sfml-window
    - sfml-system
    - user32.lib
    - shell32.lib

4. Ensure that `Orbitron-Black.ttf` and all required resources are placed in the `assets/` directory.

---

## 🎉 Contributing

Pull requests are welcome! If you have ideas for new features or improvements, feel free to open an issue or fork the project.

---

## 📄 License

This project is licensed under the MIT License. See `LICENSE` for details.

