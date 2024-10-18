#include "offsets.h"
#include "utility.hpp"
#include "cheat.h"

void offset::init()
{
	offset::intersectGeometryPtr = cUtility.signatureScanner("ac_client.exe", "55 8B EC 83 E4 ? 81 EC ? ? ? ? 53 8B DA 8B D1");;
	if (offset::intersectGeometryPtr == NULL)
		console.report(logLevel::ERR, "offset::intersectGeometryPtr not found.");

	offset::entitylistPtr = *reinterpret_cast<uintptr_t**>(cUtility.signatureScanner("ac_client.exe", "3B 0D ? ? ? ? 0F 8D ? ? ? ? A1 ? ? ? ? 8B 34 88") + 13);
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
		pEntity* ent = *(pEntity**)(*offsets.entitylistPtr + i * 4);

		if (ent == NULL || offsets.localPlayer == NULL || offsets.localPlayer == ent)
			continue;

		vec.push_back(ent);
	}
	return vec;
}

pEntity* offset::getClosedTarget()
{
	float oldDist = FLT_MAX;
	float newDist = 0;
	pEntity* aimTarget = NULL;

	for (pEntity* ent : offsets.getEntity())
	{
		if (ent->getHealth() <= 0)
			continue;

		vec3 localHead = offsets.localPlayer->getHeadPosition();
		vec3 targetHead = ent->getHeadPosition();
		vec2 screenMiddle = { offsets.windowWidth / 2.f, offsets.windowHeight / 2.f };
		vec2 targetHeadScreen;

		if (!cUtility.WorldToScreen(targetHead, targetHeadScreen))
			continue;

		newDist = abs(screenMiddle.dist2D(targetHeadScreen));

		if (newDist < oldDist && newDist <= cheat::aimbot::fov)
		{
			oldDist = newDist;
			aimTarget = ent;
		}
	}
	return aimTarget;
}

void offset::intersectGeometry(const vec3& from, vec3& to)
{
	uintptr_t intersectGeometryPtr = offsets.intersectGeometryPtr;

	void* pFrom = (void*)&from;
	void* pTo = (void*)&to;

	__asm {
		mov ecx, pFrom
		mov edx, pTo
		call offsets.intersectGeometryPtr
	}
}

bool offset::isVisible(pEntity* ent) {
	vec3 localPlayer = offsets.localPlayer->getFeetPosition();
	vec3 tmpTo = ent->getHeadPosition().x >= 0 ? ent->getHeadPosition() : ent->getFeetPosition();
	vec3 from = vec3(localPlayer.x, localPlayer.y, localPlayer.z);
	vec3 to = vec3(tmpTo.x, tmpTo.y, tmpTo.z);

	offsets.intersectGeometry(from, to);
	return to.x == tmpTo.x && to.y == tmpTo.y && to.z == tmpTo.z;
}