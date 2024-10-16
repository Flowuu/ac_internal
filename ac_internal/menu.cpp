#include "cheat.h"

void aimbotSubMenu()
{
	ImGui::SeparatorText("Aimbot");
	ImGui::Checkbox("Enable", &cheat::aimbot::enable);
}

void espSubMenu()
{
	ImGui::SeparatorText("Esp");
	ImGui::Checkbox("Enable", &cheat::esp::enable);
}

void miscSubMenu()
{
	ImGui::SeparatorText("Misc");
	ImGui::Checkbox("Enable", &cheat::misc::enable);
}

int selectedTab = 0;
void cheat::menu::mainMenu()
{
	ImGui::SetNextWindowSize({700, 400});
	ImGui::Begin("ac_internal", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::Button("Aimbot", { 225, 25 })) selectedTab = 0;
	ImGui::SameLine();
	if (ImGui::Button("Esp", { 225, 25 })) selectedTab = 1;
	ImGui::SameLine();
	if (ImGui::Button("Misc", { 225, 25 })) selectedTab = 2;


	if (selectedTab == 0)
		aimbotSubMenu();
	else if (selectedTab == 1)
		espSubMenu();
	else if (selectedTab == 2)
		miscSubMenu();

	ImGui::End();
}