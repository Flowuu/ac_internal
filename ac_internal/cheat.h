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
		inline bool enable = true;
	}

	namespace esp
	{
		void initAll();

		inline bool enable = true;
		inline bool teamCheck = true;

		inline bool name = true;
		inline ImColor nameColor = { 255, 255, 255, 255 };

		inline bool health = true;
		inline ImColor healthColor = { 0, 255, 0, 255 };

		inline bool armour = true;
		inline ImColor armourColor = { 0, 0, 255, 255 };

		inline bool box = true;
		inline ImColor boxColor = { 255, 0, 0, 255 };


		inline bool fillBox = false;
		inline ImColor fillBoxTopColor = { 255, 0, 0, 0 };
		inline ImColor fillBoxBottomColor = { 255, 0, 0, 100 };


	}

	namespace misc
	{
		inline bool enable = true;
	}

	namespace menu
	{
		void initImgui();
		void closeImgui();

		void mainMenu();
		inline bool menuToggle = true;
	}
}