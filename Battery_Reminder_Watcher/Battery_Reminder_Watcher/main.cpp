#include "core.h"

int main()
{
	nlohmann::json loaded_json_data = core::load_data();
	core::BatteryStatus currentBatteryStatus = core::get_BatteryStatus();
	
	printf("Hello World!\n");
	

	bool running = true;
	auto start = std::chrono::high_resolution_clock::now();
	bool is_charging = currentBatteryStatus.is_charging;
	while (running)
	{
		

		// check if the charger has just plugged out
		if (is_charging != currentBatteryStatus.is_charging)
		{
			if (!is_charging)
			{
				// charger is plugged in
				core::toast_notification((int)currentBatteryStatus.battery_percentage, L"Charger Plugged ");
			}
			else
			{
				// charger is unplugged
				core::Config::LAST_CHARGED = core::getDateTime();
				core::save_data(loaded_json_data);
				core::toast_notification((int)currentBatteryStatus.battery_percentage, L"Charger Unplugged");
			}
		}

		is_charging = currentBatteryStatus.is_charging;

		


		loaded_json_data = core::load_data();

		// Runn the below code every n seconds, where n is the value of REMIND_AFTER_EVERY
		auto now = std::chrono::high_resolution_clock::now();

		// Calculate the elapsed time in seconds
		auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();

		// Check if the elapsed time is greater than or equal to the REMIND_AFTER_EVERY value
		if (elapsed >= loaded_json_data["REMIND_AFTER_EVERY"])
		{
			start = now; // reset the start time

			// Get the current battery status
			currentBatteryStatus = core::get_BatteryStatus();

			// if charger is plugged in, check if the battery percent is greater than alert percentage and show alerts
			if (currentBatteryStatus.is_charging)
			{
				if (currentBatteryStatus.battery_percentage >= loaded_json_data["ALERT_PERCENTAGE"])
				{
					// if the prefernce is set in json file then show the alerts accordingly	
					if (loaded_json_data["TOAST_NOTIFICATION_ALERT_PREFERENCE"])
					{
						core::toast_notification((int)currentBatteryStatus.battery_percentage, L"Unplug your charger !");
					}

					if (loaded_json_data["MESSAGE_BOX_ALERT_PREFERENCE"])
					{
						core::ShowNotification(L"Unplug your charger", L"Unplug your charger");
					}

				}
			}
		}

		Sleep(1000);
	}

	return 0;
}