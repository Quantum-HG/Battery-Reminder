/*
 * Battery_Reminder_Watcher
 * ----------------
 * Licensed under the MIT License.
 * Copyright (c) 2025 Quantum-HG
 * See the LICENSE file in the project root for license information.
 */
#define BATTERY_REMINDER_WATCHER
#include "app.h"

// Battery Reminder Watcher Main
//int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
int main(int argc, char* argv[])
{
	core::SetWorkingDirectoryToExePath();
	BatteryReminderWatcher app;
	app.run();

	return 0;
}