#include "cheat.h"
#include <string>

void aimbotSubMenu()
{
	ImGui::SeparatorText("Aimbot");
	ImGui::Checkbox("Enable", &cheat::aimbot::enable);

	if (!cheat::aimbot::enable)
		return;

	ImGui::Checkbox("Visible check", &cheat::aimbot::visible);
	ImGui::Checkbox("Silent", &cheat::aimbot::silent);
	ImGui::Checkbox("Team check", &cheat::aimbot::teamCheck);

	ImGui::SliderFloat("Fov", &cheat::aimbot::fov, 0, 500);
}

void espSubMenu()
{
	ImGui::SeparatorText("Esp");
	ImGui::Checkbox("Enable", &cheat::esp::enable);

	if (!cheat::esp::enable)
		return;


	ImGui::Checkbox("Visible check", &cheat::esp::visible);
	ImGui::Checkbox("Team check", &cheat::esp::teamCheck);


	ImGui::Checkbox("Name", &cheat::esp::name);
	if (cheat::esp::name)
	{
		ImGui::SameLine();
		ImGui::ColorEdit4("Name color", (float*)(&cheat::esp::nameColor), ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);

		if(cheat::esp::visible)
		{
			ImGui::SameLine();
			ImGui::ColorEdit4("Name invisible color", (float*)(&cheat::esp::InvisibleNameColor), ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
		}
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
		if (cheat::esp::visible)
		{
			ImGui::SameLine();
			ImGui::ColorEdit4("Box Invisible color", (float*)(&cheat::esp::InvisibleboxColor), ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
		}
	}


	ImGui::Checkbox("fill box", &cheat::esp::fillBox);
	if (cheat::esp::fillBox)
	{
		ImGui::SameLine();
		ImGui::ColorEdit4("fill box color | top", (float*)(&cheat::esp::fillBoxTopColor), ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::ColorEdit4("fill box color | bottom", (float*)(&cheat::esp::fillBoxBottomColor), ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);

		if (cheat::esp::visible)
		{
			ImGui::SameLine();
			ImGui::ColorEdit4("Invisible fill box color | top", (float*)(&cheat::esp::InvisibleFillBoxTopColor), ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
			ImGui::SameLine();
			ImGui::ColorEdit4("Invisible fill box color | bottom", (float*)(&cheat::esp::InvisibleboxColor), ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
		}
	}

	if (true)
	{

	}
}

void miscSubMenu()
{
	ImGui::SeparatorText("Misc");
	ImGui::Checkbox("Enable", &cheat::misc::enable);

	if (!cheat::misc::enable)
		return;

	ImGui::Checkbox("Infinite ammo", &cheat::misc::infiniteAmmo);

	ImGui::Checkbox("Infinite health", &cheat::misc::infinitHealth);

	ImGui::Checkbox("No recoil", &cheat::misc::noRecoil);

	ImGui::Checkbox("Rapid fire", &cheat::misc::rapidFire); ImGui::SameLine();
	ImGui::InputInt("Rapid fire cooldown", &cheat::misc::rapidFireCooldown);

	ImGui::Checkbox("Nade timer", &cheat::misc::nadeTimer); ImGui::SameLine();
	if(cheat::misc::nadeTimer)
		ImGui::ColorEdit4("Nade timer color", (float*)(&cheat::misc::nadeTimerColor), ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);

	ImGui::Checkbox("Reload timer", &cheat::misc::reloadTimer); ImGui::SameLine();
	if (cheat::misc::reloadTimer)
		ImGui::ColorEdit4("Reload Timer Color", (float*)(&cheat::misc::reloadTimerColor), ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);

	ImGui::Checkbox("Player list", &cheat::misc::playerList);
}

void playerListWindow()
{
	ImGui::Begin("playerList", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);

	// Create a table with 7 columns
	ImGui::BeginTable("playerList", 7, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg);

	// Header section
	ImGui::TableSetupColumn("Name");
	ImGui::TableSetupColumn("Ping");
	ImGui::TableSetupColumn("Alive/Dead");
	ImGui::TableSetupColumn("Deaths");
	ImGui::TableSetupColumn("Kills");
	ImGui::TableSetupColumn("Current Weapon");
	ImGui::TableSetupColumn(""); // Empty column for buttons
	ImGui::TableHeadersRow();

	// Loop through the entities and display their data
	for (size_t i = 0; i < offsets.getEntity().size(); ++i) {
		pEntity* ent = offsets.getEntity()[i];

		if (ent->getHealth() <= 0)
			continue;

		ImGui::TableNextRow();

		// Display the entity's alive status
		ent->isAlive() ? ImGui::Text("Alive") : ImGui::Text("Dead");

		// Display the data for each column
		ImGui::TableSetColumnIndex(0);
		ImGui::Text("%s", ent->getName());

		ImGui::TableSetColumnIndex(1);
		ImGui::Text("%dms", ent->getPing());

		ImGui::TableSetColumnIndex(2);
		ImGui::Text("%s", ent->isAlive() ? "Alive" : "Dead");

		ImGui::TableSetColumnIndex(3);
		ImGui::Text("%d", ent->getDeathCount());

		ImGui::TableSetColumnIndex(4);
		ImGui::Text("%d", ent->getKillCount());

		ImGui::TableSetColumnIndex(5);
		ImGui::Text("%s", ent->getWeaponName());

		// Buttons in the last column with unique IDs
		ImGui::TableSetColumnIndex(6);

		ImGui::PushID(i); // Use the index as a unique ID

		if (ImGui::Button("Steal name")) {
			offsets.localPlayer->setName(ent->getName());
		}

		ImGui::SameLine();

		if (ImGui::Button("Select enemy")) {
			// Implement your select enemy logic here
		}

		ImGui::PopID();
	}
	ImGui::EndTable(); // End the table

	ImGui::Separator();

	if (ImGui::Button("Set"))
		offsets.localPlayer->setName(cheat::misc::setName);

	ImGui::SameLine();
	ImGui::InputText("Name", cheat::misc::setName, sizeof(cheat::misc::setName));

	ImGui::End();
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

	if (cheat::misc::playerList)
		playerListWindow();
}