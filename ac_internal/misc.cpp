#include "cheat.h"
#include "utility.hpp"
#include "draw.h"

void cheat::misc::initAll()
{
	if (!cheat::misc::enable)
		return;

	if (cheat::misc::infiniteAmmo)
			offsets.localPlayer->setAmmo(100);

	if (cheat::misc::infinitHealth)
		
		offsets.localPlayer->setHealth(999);

	if (cheat::misc::noRecoil)
	{
		vec2 curAngle = offsets.localPlayer->getViewAngle();
		offsets.localPlayer->setViewAngle(curAngle);
	}

	if (cheat::misc::rapidFire)
		offsets.localPlayer->setWeaponCooldDown(cheat::misc::rapidFireCooldown);

	if(cheat::misc::nadeTimer)
		if (offsets.localPlayer->getWeaponId() == 7 && offsets.localPlayer->isAttacking())
            iDraw->drawTimerLine({ (float)offsets.windowWidth / 2, (float)offsets.windowHeight / 2 }, 2, cheat::misc::nadeTimerColor);

	if (cheat::misc::reloadTimer)
		if (offsets.localPlayer->isReloading() != 0)
			if (offsets.localPlayer->getWeaponId() == weaponIds::PISTOL)
				iDraw->drawTimerLine({ (float)offsets.windowWidth / 2, (float)offsets.windowHeight / 2 + 20}, 1.5, cheat::misc::reloadTimerColor);
			else if (offsets.localPlayer->getWeaponId() == weaponIds::AKIMBO)
				iDraw->drawTimerLine({ (float)offsets.windowWidth / 2, (float)offsets.windowHeight / 2 + 20 }, 1.5, cheat::misc::reloadTimerColor);
			else if(offsets.localPlayer->getWeaponId() == weaponIds::SUBMACHINE)
				iDraw->drawTimerLine({ (float)offsets.windowWidth / 2, (float)offsets.windowHeight / 2 + 20}, 1.6, cheat::misc::reloadTimerColor);
			else if (offsets.localPlayer->getWeaponId() == weaponIds::CARBINE)
				iDraw->drawTimerLine({ (float)offsets.windowWidth / 2, (float)offsets.windowHeight / 2 + 20 }, 1.8, cheat::misc::reloadTimerColor);
			else if (offsets.localPlayer->getWeaponId() == weaponIds::ASSAULT_RIFLE)
				iDraw->drawTimerLine({ (float)offsets.windowWidth / 2, (float)offsets.windowHeight / 2 + 20 }, 2, cheat::misc::reloadTimerColor);
			else if (offsets.localPlayer->getWeaponId() == weaponIds::SHOTGUN)
				iDraw->drawTimerLine({ (float)offsets.windowWidth / 2, (float)offsets.windowHeight / 2 + 20 }, 3.0, cheat::misc::reloadTimerColor);
			else if (offsets.localPlayer->getWeaponId() == weaponIds::SNIPER_RIFLE)
				iDraw->drawTimerLine({ (float)offsets.windowWidth / 2, (float)offsets.windowHeight / 2 + 20 }, 3.0, cheat::misc::reloadTimerColor);
}