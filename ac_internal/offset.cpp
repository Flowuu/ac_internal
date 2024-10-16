#include "offsets.h"
#include "utility.hpp"

void offset::init()
{
	offset::entitylistPtr = **reinterpret_cast<uintptr_t**>(cUtility.signatureScanner("ac_client.exe", "3B 0D ? ? ? ? 0F 8D ? ? ? ? A1 ? ? ? ? 8B 34 88") + 13);
	if (offset::entitylistPtr == NULL)
		console.report(logLevel::ERR, "offset::entitylistPtr not found.");

	offset::localPlayer = **reinterpret_cast<pEntity***>(cUtility.signatureScanner("ac_client.exe", "8B 84 24 0C 01 00 00 53 8B 1D ? ? ? ? 56 8B 08 85 C9 79 ? 8B F3 EB") + 10);
	if (offset::localPlayer == NULL)
		console.report(logLevel::ERR, "offset::localPlayer not found.");

	offset::playerCount = *reinterpret_cast<int**>(cUtility.signatureScanner("ac_client.exe", "3B 0D ? ? ? ? 0F 8D ? ? ? ? A1 ? ? ? ? 8B 34 88") + 2);
	if (offset::playerCount == NULL)
		console.report(logLevel::ERR, "offset::playerCount not found.");

	offset::matrix = *reinterpret_cast<float**>(cUtility.signatureScanner("ac_client.exe", "50 68 ? ? ? ? E8 42 CE FF FF 8B C1 8D 54 24") + 2);
	if (offset::matrix == NULL)
		console.report(logLevel::ERR, "offset::matrix not found.");

	offset::windowHeight = **reinterpret_cast<int**>(cUtility.signatureScanner("ac_client.exe", "03 0D ? ? ? ? 8B 35 ? ? ? ? D3 E3 8B 0D ? ? ? ? 90") + 8);
	if (offset::windowHeight == NULL)
		console.report(logLevel::ERR, "offset::windowHeight not found.");

	offset::windowWidth = **reinterpret_cast<int**>(cUtility.signatureScanner("ac_client.exe", "03 0D ? ? ? ? 8B 35 ? ? ? ? D3 E3 8B 0D ? ? ? ? 90") + 16);
	if (offset::windowWidth == NULL)
		console.report(logLevel::ERR, "offset::windowWidth not found.");
}

std::vector<pEntity*> offset::getEntity()
{
	std::vector<pEntity*> vec;
	for (int i = 0; i < *offsets.playerCount; ++i)
	{
		pEntity* entity = *(pEntity**)(offsets.entitylistPtr + i * 4);

		if (entity == NULL || offsets.localPlayer == NULL || offsets.localPlayer == entity || entity->getHealth() <= 0)
			continue;

		vec.push_back(entity);
	}
	return vec;
}