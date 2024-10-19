#include "cheat.h"
#include "utility.hpp"
#include "draw.h"

vec2 calcAngle(vec3 src, vec3 dst)
{
	vec2 angle;
	angle.x = -atan2f(dst.x - src.x, dst.y - src.y) / (float)M_PI * 180 + 180;
	angle.y = asinf((dst.z - src.z) / src.distTo(dst)) * 180 / (float)M_PI;
	return angle;
}

void nAimbot(pEntity* ent)
{
	offsets.localPlayer->setViewAngle(calcAngle(offsets.localPlayer->getHeadPosition(), ent->getHeadPosition()));
}

void sAimbot(pEntity* ent)
{
	vec3 headPos = ent->getHeadPosition();
	vec3 feetPos = ent->getFeetPosition();
	offsets.localPlayer->setHeadPosition({ headPos.x, headPos.y, (headPos.z + feetPos.z) / 2 });
}

void cheat::aimbot::initAll()
{
	if (!cheat::aimbot::enable || offsets.localPlayer == NULL)
		return;

	if (cheat::aimbot::fov != 0)
		iDraw->circle({ offsets.windowWidth / 2.f, offsets.windowHeight / 2.f }, cheat::aimbot::fov, 30, ImColor(255, 255, 255, 255));

	pEntity* ent = offsets.getClosedTarget();

	if (ent == NULL )
		return;

	if (cheat::esp::teamCheck)
		if (ent->getTeam() == offsets.localPlayer->getTeam())
			return;

	if (cheat::aimbot::visible)
		if (!offsets.isVisible(ent))
			return;

	if (!GetAsyncKeyState(VK_LBUTTON))
		return;

	if (cheat::aimbot::silent)
		sAimbot(ent);
	else
		nAimbot(ent);
}