#pragma once
#include "../../ImGui/ImGui/imgui.h"
#include "../../ImGui/ImGui/imgui_internal.h"
namespace Custom
{

	bool NewCheckbox(const char* label, bool* v);
	bool Tab(const char* label, const ImVec2& size_arg, bool state);
}