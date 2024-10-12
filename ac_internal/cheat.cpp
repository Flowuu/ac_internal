#include "cheat.h"

#include "hook.hpp"

typedef bool(__stdcall* glSwapBuff)(HDC hdc);
glSwapBuff oSwapBuff = (glSwapBuff)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers");

bool __stdcall mHookSwapBuff(HDC hdc)
{
	console.log("Hooked!!!");

	return oSwapBuff(hdc);
}

void cheat::initAll()
{
	mHook.init(oSwapBuff, &mHookSwapBuff, reinterpret_cast<void**>(&oSwapBuff));
}