#include <Windows.h>
#include <flogger.hpp>
#include "cheat.h"
#include "hook.hpp"

void closeAll(HINSTANCE hinstDll)
{
	console.report(logLevel::WARNING, "Detaching ac_internal.dll");

	Sleep(1500);

	cheat::menu::closeImgui();

	mHook.closeHook();
	console.close();
	FreeLibraryAndExitThread(hinstDll, 0);
}

void initAll(HINSTANCE hinstDll)
{
	console.toggleTimestamp();
	console.report(logLevel::Success, "Injected.");

	cheat::initAll();

	while (!GetAsyncKeyState(VK_END));

	closeAll(hinstDll);
}

bool WINAPI DllMain(HINSTANCE hinstDll, DWORD fdwReason,  LPVOID lpReserved)
{
	DisableThreadLibraryCalls(hinstDll);

	if (fdwReason == DLL_PROCESS_ATTACH)
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)initAll, hinstDll, 0, nullptr);

	return true;
}