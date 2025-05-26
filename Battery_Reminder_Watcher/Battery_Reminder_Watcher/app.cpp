#include "app.h"

BatteryReminderWatcher::BatteryReminderWatcher(){}

BatteryReminderWatcher::~BatteryReminderWatcher(){}

void BatteryReminderWatcher::init()
{
	loaded_json_data = core::load_json_data();
	currentBatteryStatus = core::get_BatteryStatus();
	start = std::chrono::high_resolution_clock::now();
	is_charging = currentBatteryStatus.is_charging;
}

void BatteryReminderWatcher::mainloop()
{
	// check if the charger has just plugged out/in
	if (is_charging != currentBatteryStatus.is_charging)
	{
		if (!is_charging and loaded_json_data["PLUGGED_IN_ALERT"].get<bool>()) // charger is plugged in
		{
			core::toast_notification((int)currentBatteryStatus.battery_percentage, L"Charger Plugged In");
		}
		else // charger is unplugged
		{
			if (loaded_json_data["UNPLUGGED_ALERT"].get<bool>())
			{   core::Config::LAST_CHARGED = core::getDateTime();
				core::save_data();
				core::toast_notification((int)currentBatteryStatus.battery_percentage, L"Charger Unplugged");
			}
	}
	}

	is_charging = currentBatteryStatus.is_charging;

	// Reload JsonData to be Updated with json file
	loaded_json_data = core::load_json_data();


	auto now = std::chrono::high_resolution_clock::now();


	auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();

	// Check if the elapsed time is greater than or equal to the REMIND_AFTER_EVERY value
	if (elapsed >= loaded_json_data["REMIND_AFTER_EVERY"].get<int>())
	{
		start = now; // reset the start time

		// Get the current battery status
		currentBatteryStatus = core::get_BatteryStatus();

		// if charger is plugged in, check if the battery percent is greater than alert percentage and show alerts
		if (currentBatteryStatus.is_charging)
		{
			if (currentBatteryStatus.battery_percentage >= loaded_json_data["ALERT_PERCENTAGE"])
			{
				// show alerts according to the user's preference
				if (loaded_json_data["TOAST_NOTIFICATION_ALERT_PREFERENCE"].get<bool>())
					core::toast_notification((int)currentBatteryStatus.battery_percentage, L"Unplug your charger !");

				if (loaded_json_data["MESSAGE_BOX_ALERT_PREFERENCE"].get<bool>())
					core::ShowNotification(L"Unplug your charger", L"Unplug your charger !");

			}
		}
	}
}

void BatteryReminderWatcher::run()
{
	init();
	while (true)
	{
		mainloop();
		Sleep(16);
	}
}
