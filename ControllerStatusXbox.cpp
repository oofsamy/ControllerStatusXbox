#include "pch.h"
#include "ControllerStatusXbox.h"


BAKKESMOD_PLUGIN(ControllerStatusXbox, "Alerts when your controller changes state", plugin_version, PLUGINTYPE_THREADED)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void ControllerStatusXbox::onLoad()
{
	_globalCvarManager = cvarManager;

}

void ControllerStatusXbox::onUnload()
{
}