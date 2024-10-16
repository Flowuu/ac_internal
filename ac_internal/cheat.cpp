#include "cheat.h"
#include "hook.hpp"

WNDPROC oWindProc;

typedef bool(__stdcall* glSwapBuff)(HDC hdc);
typedef int(*hSDL_SetRelativeMouseMode)(int);

glSwapBuff oSwapBuff = (glSwapBuff)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers");
hSDL_SetRelativeMouseMode SDL_SetRelativeMouseMode = (hSDL_SetRelativeMouseMode)(GetProcAddress(GetModuleHandle(L"SDL2.dll"), "SDL_SetRelativeMouseMode"));

#include "draw.h"

bool __stdcall mHookSwapBuff(HDC hdc)
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
		cheat::menu::menuToggle = !cheat::menu::menuToggle;
	SDL_SetRelativeMouseMode(!cheat::menu::menuToggle);

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGuiIO& io = ImGui::GetIO();

	if(cheat::menu::menuToggle)
	{
		io.MouseDrawCursor = cheat::menu::menuToggle;

		ImGui::ShowDemoWindow();
	}

	cheat::esp::initAll();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	return oSwapBuff(hdc);
}

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK nWindProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (cheat::menu::menuToggle)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return true;

		if (uMsg == WM_MOUSEMOVE || uMsg == WM_LBUTTONDOWN || uMsg == WM_RBUTTONDOWN || uMsg == WM_KEYDOWN || uMsg == WM_MOUSEWHEEL)
			return 0;
	}

	return CallWindowProc(oWindProc, hWnd, uMsg, wParam, lParam);
}

void cheat::menu::initImgui()
{
	oWindProc = (WNDPROC)SetWindowLongPtr(FindWindowA(NULL, "AssaultCube"), GWLP_WNDPROC, (LONG_PTR)nWindProc);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplWin32_Init(FindWindowA(NULL, "AssaultCube"));
	ImGui_ImplOpenGL2_Init();

	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4* colors = ImGui::GetStyle().Colors;

	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.13f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.10f, 0.10f, 0.13f, 0.92f);
	colors[ImGuiCol_Border] = ImVec4(0.44f, 0.37f, 0.61f, 0.29f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.13f, 0.13f, 0.17f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.20f, 0.25f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.16f, 0.16f, 0.21f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.16f, 0.16f, 0.21f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.16f, 0.21f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.16f, 0.16f, 0.21f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.16f, 0.16f, 0.21f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.10f, 0.13f, 1.00f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.16f, 0.16f, 0.21f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.19f, 0.20f, 0.25f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.24f, 0.24f, 0.32f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.74f, 0.58f, 0.98f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.44f, 0.37f, 0.61f, 0.54f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.74f, 0.58f, 0.98f, 0.54f);
	colors[ImGuiCol_Button] = ImVec4(0.13f, 0.13f, 0.17f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.20f, 0.25f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.16f, 0.16f, 0.21f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.13f, 0.13f, 0.17f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.19f, 0.20f, 0.25f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.16f, 0.16f, 0.21f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.44f, 0.37f, 0.61f, 1.00f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.74f, 0.58f, 0.98f, 1.00f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.84f, 0.58f, 1.00f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.44f, 0.37f, 0.61f, 0.29f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.74f, 0.58f, 0.98f, 0.29f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.84f, 0.58f, 1.00f, 0.29f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.24f, 0.24f, 0.32f, 1.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.16f, 0.16f, 0.21f, 1.00f);
	colors[ImGuiCol_TabSelected] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	colors[ImGuiCol_TabSelectedOverline] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_TabDimmed] = ImVec4(0.16f, 0.16f, 0.21f, 1.00f);
	colors[ImGuiCol_TabDimmedSelected] = ImVec4(0.16f, 0.16f, 0.21f, 1.00f);
	colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_TextLink] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

	style.WindowPadding = ImVec2(8, 8);
	style.FramePadding = ImVec2(4, 3);
	style.ItemSpacing = ImVec2(4, 3);
	style.ItemInnerSpacing = ImVec2(4, 3);
	style.GrabMinSize = 4;

	style.WindowBorderSize = 1;
	style.ChildBorderSize = 1;
	style.PopupBorderSize = 1;
	style.FrameBorderSize = 1;
	style.TabBorderSize = 1;
	style.TabBarBorderSize = 1;
	style.TabBarOverlineSize = 1;

	style.WindowRounding = 3;
	style.ChildRounding = 3;
	style.FrameRounding = 2;
	style.PopupRounding = 2;
	style.ScrollbarRounding = 2;
	style.GrabRounding = 2;
	style.TabRounding = 1;

	style.SeparatorTextBorderSize = 1;
	style.SeparatorTextPadding = ImVec2(20, 4);
}

void cheat::menu::closeImgui()
{
	SDL_SetRelativeMouseMode(true);

	SetWindowLongPtr(FindWindowA(NULL, "AssaultCube"), GWLP_WNDPROC, (DWORD)oWindProc);
}

void cheat::initAll()
{
	cheat::menu::initImgui();

	mHook.init(oSwapBuff, &mHookSwapBuff, reinterpret_cast<void**>(&oSwapBuff));
}