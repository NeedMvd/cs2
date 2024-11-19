#include "Menu.h"
#include <Windows.h>
#include "../ImGui/ImGui/imgui.h"
#include "custom/custom.h"
#include "../Cheat/Run.h"
#include <vector>
using namespace Custom;
#include "../Cheat/Settings.h"
#include "../Cheat/SDK/Bone.h"
std::vector < const char* > hitboxes = { "Head", "Neck", "Spine", "Leg Lower Left", "Leg Lower Right" };


#define ALPHA    ( ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder )


void Menu::Draw()
{
	Cheats::Run();


	if (GetAsyncKeyState(VK_INSERT) & 1)
		is_visible = !is_visible;


	if (!is_visible)
		return;


	auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | NULL | NULL | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | NULL | NULL | NULL;

	static int tab = 0;

	ImGui::SetNextWindowSize({ 560.000000f,360.000000f });

	ImGui::Begin("Edited", nullptr, flags);
	{
		ImVec2 p = ImGui::GetWindowPos();
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(p.x + 10, p.y + 10), ImVec2(p.x + 550, p.y + 350), ImColor(0.000000f, 0.000000f, 0.000000f, 0.4f), 0, 15); // main frame
		ImGui::GetWindowDrawList()->AddRect(ImVec2(p.x + 0, p.y + 0), ImVec2(p.x + 560, p.y + 360), ImColor(0.000000f, 0.000000f, 0.000000f, 0.639216f), 0, 15, 1.000000);  // main frame
		ImGui::GetWindowDrawList()->AddRect(ImVec2(p.x + 10, p.y + 10), ImVec2(p.x + 550, p.y + 350), ImColor(0.000000f, 0.000000f, 0.000000f, 0.639216f), 0, 15, 1.000000);  // main frame
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(p.x + 15, p.y + 60), ImVec2(p.x + 545, p.y + 345), ImColor(0.066667f, 0.066667f, 0.066667f, 1.000000f), 0, 15); // main frame
		ImGui::GetWindowDrawList()->AddRect(ImVec2(p.x + 15, p.y + 60), ImVec2(p.x + 545, p.y + 345), ImColor(0.000001f, 0.000001f, 0.000001f, 1.000000f), 0, 15, 1.000000);  // main frame

		ImGui::SetCursorPos({ 15,17 });
		if (Tab("legitbot", { 125,35 }, tab == 0))
			tab = 0;

		ImGui::SetCursorPos({ 15 + 125 + 10,17 });
		if (Tab("visuals", { 125,35 }, tab == 1))
			tab = 1;

		ImGui::SetCursorPos({ 15 + 250 + 20,17 });
		if (Tab("misc", { 125,35 }, tab == 2))
			tab = 2;

		ImGui::SetCursorPos({ 15 + 375 + 30,17 });
		if (Tab("skins", { 125,35 }, tab == 3))
			tab = 3;

		if (tab == 0)
		{
			ImGui::SetCursorPos({ 21,65 });
			ImGui::BeginChild("##1", { 166,276 });
			{
				NewCheckbox("Aimbot", &Aimbot::Enable);
				ImGui::SliderFloat("Fov", &Aimbot::Fov, 0.f, 15.f);
				ImGui::SliderFloat("Smooth", &Aimbot::Smooth, 0.000f, 1.f);

				ImGui::SliderFloat("RCS X", &Aimbot::RCS_X, 0.f, 2.f);
				ImGui::SliderFloat("RCS Y", &Aimbot::RCS_Y, 0.f, 2.f);

				ImGui::Combo("Hitbox", &Aimbot::hitbox, "Head\0Neck \0Spine\0Leg Lower Left\0Leg Lower Right\0");

			}
			ImGui::EndChild();

			ImGui::SetCursorPos({ 31 + 166,65 });
			ImGui::BeginChild("##2", { 166,276 });
			{
				ImGui::ColorPicker3("Color Box", Visuals::ESP_Box_Color, ALPHA);
			}
			ImGui::EndChild();

			ImGui::SetCursorPos({ 41 + 166 + 166,65 });
			ImGui::BeginChild("##3", { 166,276 });
			{

			}
			ImGui::EndChild();
		}
		else if (tab == 1)
		{
			ImGui::SetCursorPos({ 21,65 });
			ImGui::BeginChild("##1", { 166,276 });
			{

			}
			ImGui::EndChild();

			ImGui::SetCursorPos({ 31 + 166,65 });
			ImGui::BeginChild("##2", { 166,276 });
			{

			}
			ImGui::EndChild();

			ImGui::SetCursorPos({ 41 + 166 + 166,65 });
			ImGui::BeginChild("##3", { 166,276 });
			{

			}
			ImGui::EndChild();
		}
		else if (tab == 2)
		{
			ImGui::SetCursorPos({ 21,65 });
			ImGui::BeginChild("##1", { 166,276 });
			{

			}
			ImGui::EndChild();

			ImGui::SetCursorPos({ 31 + 166,65 });
			ImGui::BeginChild("##2", { 166,276 });
			{

			}
			ImGui::EndChild();

			ImGui::SetCursorPos({ 41 + 166 + 166,65 });
			ImGui::BeginChild("##3", { 166,276 });
			{

			}
			ImGui::EndChild();
		}
		else if (tab == 3)
		{
			ImGui::SetCursorPos({ 21,65 });
			ImGui::BeginChild("##1", { 166,276 });
			{

			}
			ImGui::EndChild();

			ImGui::SetCursorPos({ 31 + 166,65 });
			ImGui::BeginChild("##2", { 166,276 });
			{

			}
			ImGui::EndChild();

			ImGui::SetCursorPos({ 41 + 166 + 166,65 });
			ImGui::BeginChild("##3", { 166,276 });
			{

			}
			ImGui::EndChild();//
		}
	}
	ImGui::End();
}
