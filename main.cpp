/*
 * Battery Reminder
 * ----------------
 * Licensed under the MIT License.
 * Copyright (c) 2025 Quantum-HG
 * See the LICENSE file in the project root for license information.
 */

#include "app.h"

// Battery Reminder Main
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    core::SetWorkingDirectoryToExePath();
    App app;
    app.run();
    
    return 0;
}
