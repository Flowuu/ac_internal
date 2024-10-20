#include "cheat.h"
#include "utility.hpp"
#include "draw.h"

// Inline angle calculation for better performance
inline vec2 calcAngle(const vec3& src, const vec3& dst)
{
    vec2 angle;
    float deltaX = dst.x - src.x;
    float deltaY = dst.y - src.y;
    float deltaZ = dst.z - src.z;
    angle.x = -atan2f(deltaX, deltaY) * (180.f / (float)M_PI) + 180.f;
    angle.y = asinf(deltaZ / src.distTo(dst)) * (180.f / (float)M_PI);
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
    if (!cheat::aimbot::enable || offsets.localPlayer == nullptr)
        return;

    if (cheat::aimbot::fov != 0)
        iDraw->circle({ offsets.windowWidth / 2.f, offsets.windowHeight / 2.f }, cheat::aimbot::fov, 30, ImColor(255, 255, 255, 255));

    if (!GetAsyncKeyState(VK_LBUTTON))
        return;

    pEntity* ent = offsets.getClosedTarget();
    if (!ent)
        return;

    if (cheat::esp::teamCheck && ent->getTeam() == offsets.localPlayer->getTeam() ||
        cheat::aimbot::visible && !offsets.isVisible(ent))
        return;

    if (cheat::aimbot::silent)
        sAimbot(ent);
    else
        nAimbot(ent);
}
