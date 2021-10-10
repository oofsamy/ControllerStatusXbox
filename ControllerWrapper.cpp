#include <windows.h>
#include <Xinput.h>

#include "pch.h"
#include "ControllerWrapper.h"

Controller::Controller(int Num) {
	ControllerNum = Num - 1;
}

XINPUT_STATE Controller::GetState() {
	ZeroMemory(&ControllerState, sizeof(XINPUT_STATE));

	XInputGetState(ControllerNum, &ControllerState);

	return ControllerState;
}

DWORD Controller::SetBatteryInfo(DWORD UserIndex, BYTE DevType, XINPUT_BATTERY_INFORMATION* BatteryInfoPtr) {
	return XInputGetBatteryInformation(UserIndex, DevType, BatteryInfoPtr);
}

BOOL Controller::IsConnected() {
	ZeroMemory(&ControllerState, sizeof(XINPUT_STATE));

	DWORD Result = XInputGetState(ControllerNum, &ControllerState);

	return Result == ERROR_SUCCESS;
}