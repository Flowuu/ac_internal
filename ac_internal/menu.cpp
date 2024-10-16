#include "cheat.h"

void aimbotSubMenu()
{
	ImGui::SeparatorText("Aimbot");
	ImGui::Checkbox("Enable", &cheat::aimbot::enable);

	if (cheat::aimbot::enable)
		return;
}

void espSubMenu()
{
	ImGui::SeparatorText("Esp");
	ImGui::Checkbox("Enable", &cheat::esp::enable);

	if (!cheat::esp::enable)
		return;

	ImGui::Checkbox("Team check", &cheat::esp::teamCheck);


	ImGui::Checkbox("Name", &cheat::esp::name);
	if (cheat::esp::name)
	{
		ImGui::SameLine();
		ImGui::ColorEdit4("Name color", (float*)(&cheat::esp::nameColor), ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
	}


	ImGui::Checkbox("Health", &cheat::esp::health);
	if (cheat::esp::health)
	{
		ImGui::SameLine();
		ImGui::ColorEdit4("health color", (float*)(&cheat::esp::healthColor), ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
	}


	ImGui::Checkbox("Armour", &cheat::esp::armour);
	if (cheat::esp::armour)
	{
		ImGui::SameLine();
		ImGui::ColorEdit4("Armour color", (float*)(&cheat::esp::armourColor), ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
	}


	ImGui::Checkbox("Box", &cheat::esp::box);
	if (cheat::esp::box)
	{
		ImGui::SameLine();
		ImGui::ColorEdit4("box color", (float*)(&cheat::esp::boxColor), ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
	}


	ImGui::Checkbox("fill box", &cheat::esp::fillBox);
	if (cheat::esp::fillBox)
	{
		ImGui::SameLine();
		ImGui::ColorEdit4("fill box color | top", (float*)(&cheat::esp::fillBoxTopColor), ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::ColorEdit4("fill box color | bottom", (float*)(&cheat::esp::fillBoxTopColor), ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
	}


}

void miscSubMenu()
{
	ImGui::SeparatorText("Misc");
	ImGui::Checkbox("Enable", &cheat::misc::enable);

	if (cheat::misc::enable)
		return;


}

int selectedTab = 0;
void cheat::menu::mainMenu()
{
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