#pragma once
#include "core.h"

class BatteryReminderWatcher
{
public:
	BatteryReminderWatcher();
	~BatteryReminderWatcher();
	void run();

private:

	nlohmann::json loaded_json_data;

	core::BatteryStatus currentBatteryStatus;

	bool running = true;

	std::chrono::steady_clock::time_point start;

	bool is_charging;

	void init();
	void mainloop();

};