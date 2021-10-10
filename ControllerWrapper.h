#pragma once
#include <windows.h>
#include <Xinput.h>

#pragma comment(lib, "XInput.lib")


class Controller {
	private:
		XINPUT_STATE ControllerState;
		int ControllerNum;
	public:
		XINPUT_BATTERY_INFORMATION BatteryInfo;
		Controller(int num);
		XINPUT_STATE GetState();
		DWORD SetBatteryInfo(DWORD UserIndex, BYTE DevType, XINPUT_BATTERY_INFORMATION* BatteryInfoPtr);
		BOOL IsConnected();
};