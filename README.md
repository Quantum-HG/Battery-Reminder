# 🪫 Battery Reminder

**Battery Reminder** is a lightweight C++ desktop app for Windows that alerts you when your laptop battery is fully charged. It uses SFML for graphics, ImGui for the UI, and WinToastLib for native Windows notifications.

![Screenshot](assets/demo.png)

---

## ⚙️ Features

* 🔔 Native Windows toast notifications
* 🖼️ Custom UI with ImGui
* 📆 Persistent data saved with JSON
* 🔎 Open-source and lightweight

---

## 🌮 Technologies Used

* C++17
* [SFML](https://www.sfml-dev.org/)
* [ImGui](https://github.com/ocornut/imgui) + [ImGui-SFML](https://github.com/eliasdaler/imgui-sfml)
* [WinToastLib](https://github.com/mohabouje/WinToast)
* [nlohmann/json](https://github.com/nlohmann/json)

---

## 🚀 Getting Started

### Requirements

* Windows 10/11
* C++17 compatible compiler (MSVC recommended)
* SFML 2.5+
* ImGui + ImGui-SFML
* WinToastLib
* nlohmann/json

### Build Instructions (Manual)

1. Clone the repo:

```bash
git clone https://github.com/Quantum-HG/Battery-Reminder.git
cd Battery-Reminder
```

2. Add the source files to your IDE (Visual Studio, Code::Blocks, etc).

3. Link libraries:

* `sfml-graphics`
* `sfml-window`
* `sfml-system`
* `user32.lib`, `shell32.lib` (required for WinToast)

4. Place `Orbitron-Black.ttf` and other assets in the `assets/` folder.

---

## 📋 Folder Structure

```
Battery-Reminder/
├── assets/          # Icons, fonts, etc.
├── src/             # C++ source files
├── include/         # Header files
├── data/            # Saved JSON config/data
├── README.md
├── main.cpp
└── ...
```

---

## 🎉 Contributing

Pull requests are welcome! If you have ideas for new features or improvements, feel free to open an issue or fork the project.

---

## 📄 License

This project is licensed under the MIT License. See `LICENSE` for details.

