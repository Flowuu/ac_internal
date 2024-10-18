#pragma once
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl2.h>
#include <imgui/imgui_impl_win32.h>
#include "offsets.h"

namespace cheat
{
	void initAll();

	namespace aimbot
	{
		void initAll();

		inline bool enable = true;
		inline bool visible = false;
		inline bool silent = true;
		inline bool teamCheck = true;
		inline float fov = 100.f;
	}

	namespace esp
	{
		void initAll();

		inline bool enable = true;

		inline bool visible = false;

		inline bool teamCheck = true;

		inline bool name = true;
		inline ImColor nameColor = { 255, 255, 255, 255 };
		inline ImColor InvisibleNameColor = { 100, 100, 255, 255 };

		inline bool health = true;
		inline ImColor healthColor = { 0, 255, 0, 255 };

		inline bool armour = true;
		inline ImColor armourColor = { 0, 0, 255, 255 };

		inline bool box = true;
		inline ImColor boxColor = { 255, 255, 255, 255 };
		inline ImColor InvisibleboxColor = { 100, 100, 255, 255 };


		inline bool fillBox = false;
		inline ImColor fillBoxTopColor = { 255, 100, 100, 0 };
		inline ImColor fillBoxBottomColor = { 255, 100, 100, 100 };
		inline ImColor InvisibleFillBoxTopColor = { 100, 100, 255, 0 };
		inline ImColor InvisibleFillBoxBottomColor = { 100, 100, 255, 100 };


	}

	namespace misc
	{
		void initAll();

		inline bool enable = true;

		inline bool rapidFire = false;
		inline int rapidFireCooldown = 10;

		inline bool infiniteAmmo = false;

		inline bool infinitHealth = false;

		inline bool noRecoil = false;

		inline bool reloadTimer = true;
		inline ImColor reloadTimerColor = { 255, 0, 0, 100 };

		inline bool nadeTimer = true;
		inline ImColor nadeTimerColor = { 255, 0, 0, 100 };

		inline char setName[32] = "ac_internal.dll";

		inline bool playerList = true;
	}

	namespace menu
	{
		void initImgui();
		void closeImgui();

		void mainMenu();
		inline bool menuToggle = true;
	}
}