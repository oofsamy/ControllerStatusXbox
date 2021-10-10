#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"

#include "ControllerWrapper.h"

#include "version.h"
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);


class ControllerStatusXbox: public BakkesMod::Plugin::BakkesModPlugin, public BakkesMod::Plugin::PluginSettingsWindow/*, public BakkesMod::Plugin::PluginWindow*/
{

	virtual void onLoad();
	virtual void onUnload();

	void RenderSettings() override;
	std::string GetPluginName() override;
	void SetImGuiContext(uintptr_t ctx) override;

	void GenerateNotification(int StateType);

	int StateOfController = DISCONNECTED;

	enum States {
		DISCONNECTED = 0x01,
		CONNECTED = 0x02,
		CRITICAL = 0x03,
		LOW = 0x04,
		MEDIUM = 0x05,
		FULL = 0x06,
		CHARGING = 0x07,
	};
};

