#pragma once
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl2.h>
#include <imgui/imgui_impl_win32.h>
#include "offsets.hpp"

namespace cheat
{
	void initAll();

	namespace aimbot
	{

	}

	namespace esp
	{
		void initAll();
	}

	namespace misc
	{

	}

	namespace menu
	{
		void initImgui();
		void closeImgui();

		inline bool menuToggle = false;
	}
}