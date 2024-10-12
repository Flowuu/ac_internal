#include <MinHook.h>
#include <flogger.hpp>

class hook
{
public:
	void init(void* targetFunction, void* DetourFunction, void** ppOriginal) {

		if (MH_Initialize() == MH_OK)
			console.logWithTitle(logLevel::INFO, "MinHook", "Initialized.");

		if (MH_CreateHook(targetFunction, DetourFunction, ppOriginal) == MH_OK)
			console.logWithTitle(logLevel::INFO, "MinHook", "Created hook at 0x%x.", targetFunction);

		if (MH_EnableHook(targetFunction) == MH_OK)
			console.logWithTitle(logLevel::INFO, "MinHook", "Enabled hook.");
	}

	void closeHook(void* targetFunction)
	{
		if (MH_DisableHook(targetFunction) == MH_OK)
			console.logWithTitle(logLevel::INFO, "MinHook", "Enabled hook.");

		if (MH_RemoveHook(targetFunction) == MH_OK)
			console.logWithTitle(logLevel::INFO, "MinHook", "Enabled hook.");

		if (MH_Uninitialize() == MH_OK)
			console.logWithTitle(logLevel::INFO, "MinHook", "Enabled hook.");
	}

	void closeHook()
	{
		if (MH_DisableHook(MH_ALL_HOOKS) == MH_OK)
			console.logWithTitle(logLevel::INFO, "MinHook", "Enabled hook.");

		if (MH_RemoveHook(MH_ALL_HOOKS) == MH_OK)
			console.logWithTitle(logLevel::INFO, "MinHook", "Enabled hook.");

		if (MH_Uninitialize() == MH_OK)
			console.logWithTitle(logLevel::INFO, "MinHook", "Enabled hook.");
	}
}; inline hook mHook;