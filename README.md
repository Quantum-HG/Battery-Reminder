# Battery Reminder

**Battery Reminder** is a lightweight Windows desktop application built in C++. It alerts users when their laptop battery reaches a user-defined battery level—helping prevent overcharging and prolong battery health. It features a custom ImGui-based interface, SFML rendering, and native Windows notifications via WinToastLib.


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

---

## Building Instructions

- 📄 [Step-by-step guide for Visual Studio](docs/visual_studio_guide.md)

---

## Contributing

- Refer to [CONTRIBUTING.md](CONTRIBUTING.md)

---

## 📄 License

This project is licensed under the MIT License. See `LICENSE` for details.

