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