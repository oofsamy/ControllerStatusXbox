#include "pch.h"
#include "ControllerStatusXbox.h"


BAKKESMOD_PLUGIN(ControllerStatusXbox, "Alerts when your controller changes state", plugin_version, PLUGINTYPE_THREADED)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

Controller* ControllerInstance = new Controller(1);

void ControllerStatusXbox::onLoad()
{
	_globalCvarManager = cvarManager;
	cvarManager->registerCvar("csx_enabled", "1", "Enable plugin", true, true, 1, true, 1, true);
	gameWrapper->LoadToastTexture("xbox_logo", std::string(gameWrapper->GetDataFolderW().begin(), gameWrapper->GetDataFolderW().end()) + "/assets/xboxnoti.wav");

	gameWrapper->HookEvent("Function Engine.GameViewportClient.Tick", [this](std::string eventName) {
		if (ControllerInstance->IsConnected()) {
			switch (ControllerInstance->SetBatteryInfo(0, BATTERY_DEVTYPE_GAMEPAD, &ControllerInstance->BatteryInfo)) {
				switch (ControllerInstance->BatteryInfo.BatteryLevel) {
					case BATTERY_LEVEL_EMPTY:
						if (StateOfController != CRITICAL) {
							StateOfController = CRITICAL;
							GenerateNotification(CRITICAL);
						}
						break;
					case BATTERY_LEVEL_LOW:
						if (StateOfController != LOW) {
							StateOfController = LOW;
							GenerateNotification(LOW);
						}
						break;
					case BATTERY_LEVEL_MEDIUM:
						if (StateOfController != MEDIUM) {
							StateOfController = MEDIUM;
							GenerateNotification(MEDIUM);
						}
						break;
					case BATTERY_LEVEL_FULL:
						if (StateOfController != FULL) {
							StateOfController = FULL;
							GenerateNotification(FULL);
						}
						break;
				}
			}
		} else {
			if (StateOfController != DISCONNECTED) {
				StateOfController = DISCONNECTED;
				GenerateNotification(DISCONNECTED);
			}
		}
	});

}

void ControllerStatusXbox::onUnload() {
	delete ControllerInstance;
}

void ControllerStatusXbox::GenerateNotification(int StateType) {
	CVarWrapper EnabledCVar = cvarManager->getCvar("csx_enabled");
	if (EnabledCVar.getBoolValue()) {
		std::string Title = "Xbox Controller Status";

		if (StateType == 1) {
			std::string Message = "Controller has been disconnected";
			gameWrapper->Toast(Title, Message, "xbox_logo", 3.5f, ToastType_Info, 500.f, 75.f); //float width = 290.f, float height = 60.f last 2 parameters
		}
		else if (StateType == 2) {
			std::string Message = "Controller has been connected";
			gameWrapper->Toast(Title, Message, "xbox_logo", 3.5f, ToastType_Info, 500.f, 75.f);
		}
		else if (StateType == 3) {
			std::string Message = "Controller battery is now at critical\nStart charging it now!";
			gameWrapper->Toast(Title, Message, "xbox_logo", 3.5f, ToastType_Error, 500.f, 75.f);
		}
		else if (StateType == 4) {
			std::string Message = "Controller battery is now at Low";
			gameWrapper->Toast(Title, Message, "xbox_logo", 3.5f, ToastType_Warning, 500.f, 75.f);
		}
		else if (StateType == 5) {
			std::string Message = "Controller battery is now at Medium";
			gameWrapper->Toast(Title, Message, "xbox_logo", 3.5f, ToastType_OK, 500.f, 75.f);
		}
		else if (StateType == 7) {
			std::string Message = "Controller battery is now Full\nFeel free to unplug your controller!";
			gameWrapper->Toast(Title, Message, "xbox_logo", 3.5f, ToastType_OK, 500.f, 75.f);
		}
		else {
			gameWrapper->Toast(Title, "No valid argument was given", "xbox_logo", 3.5f, ToastType_Error, 350.f, 75.f);
		}
	}
}