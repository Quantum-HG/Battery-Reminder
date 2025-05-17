# Building Battery Reminder with Visual Studio

### Prerequisites
- Visual Studio 2022 (Recommended) + Windows SDK
- MSVC compiler
- Required libraries 
    ## These libraries should be according to the file structure as in the given repo's libraries/
    - SFML
    - ImGui
    - ImGui-SFML
    - WinToastLib
    - nlohmann/json

### Steps

1. Clone the repository:

    ```bash
    git clone https://github.com/Quantum-HG/Battery-Reminder.git
    cd Battery-Reminder
    ```
    
2. Open the `.sln` file in Visual Studio.

3. There are two Projects within the solution
    - Battery_Reminder
    - Battery_Reminder_Watcher

    For Battery_Reminder :-
        - Configure Additional Include Directories as:-
            - include
            - libraries\json\single_include
            - libraries\imgui
            - libraries\imgui-sfml
            - libraries\sfml\include
            - libraries\wintoast\include

        - Configure Additional Library Directories as:-
            - libraries\sfml\lib

        - Link the program against the following libraries:-
            - opengl32.lib
            - sfml-graphics.lib
            - sfml-window.lib
            - sfml-system.lib
    
    For Battery_Reminder_Watcher :-
        - Configure Additional Include Directories as:-
            - ..\..\include
            - ..\..\libraries\wintoast\include
            - ..\..\libraries\json\single_include

4. Build the Solution. The exe files can be found in the x64 directory.

5. Copy all required DLLs and assets,data folder into the executable directory.
