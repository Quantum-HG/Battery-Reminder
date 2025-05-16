/*
 * Battery Reminder
 * ----------------
 * Licensed under the MIT License.
 * Copyright (c) 2025 Quantum-HG
 * See the LICENSE file in the project root for license information.
 */

#include "app.h"

// Battery Reminder Main
int main()
{
    core::SetWorkingDirectoryToExePath();
    App app;
    app.run();
    
    return 0;
}
