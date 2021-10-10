#include "pch.h"
#include "ControllerStatusXbox.h"

std::string ControllerStatusXbox::GetPluginName() {
	return "ControllerStatusXbox";
}

void ControllerStatusXbox::SetImGuiContext(uintptr_t ctx) {
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

void ControllerStatusXbox::RenderSettings() {
	ImGui::TextUnformatted("This plugin uses BakkesModSDK's notification system to alert you whenever your controller is at High/Medium/Low/Critical battery level and when it disconnects/connects");
}