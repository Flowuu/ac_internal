#include "cheat.h"
#include "hook.hpp"

WNDPROC oWindProc;

typedef bool(__stdcall* glSwapBuff)(HDC hdc);
typedef int(*hSDL_SetRelativeMouseMode)(int);

glSwapBuff oSwapBuff = (glSwapBuff)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers");
hSDL_SetRelativeMouseMode SDL_SetRelativeMouseMode = (hSDL_SetRelativeMouseMode)(GetProcAddress(GetModuleHandle(L"SDL2.dll"), "SDL_SetRelativeMouseMode"));


bool __stdcall mHookSwapBuff(HDC hdc)
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
		cheat::menu::menuToggle = !cheat::menu::menuToggle;

	SDL_SetRelativeMouseMode(!cheat::menu::menuToggle);


	if(cheat::menu::menuToggle)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDrawCursor = cheat::menu::menuToggle;

		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow();

		ImGui::Render();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	}

	return oSwapBuff(hdc);
}

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK nWindProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (cheat::menu::menuToggle)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return true;

		if (uMsg == WM_MOUSEMOVE || uMsg == WM_LBUTTONDOWN || uMsg == WM_RBUTTONDOWN || uMsg == WM_KEYDOWN)
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