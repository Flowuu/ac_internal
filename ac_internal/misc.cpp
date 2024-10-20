#include "cheat.h"
#include "utility.hpp"
#include "draw.h"

void cheat::misc::initAll()
{
	if (!cheat::misc::enable)
		return;

	if (cheat::misc::infiniteAmmo)
		offsets.localPlayer->setAmmo(100);

	if (cheat::misc::infiniteHealth)
		offsets.localPlayer->setHealth(100);

	if (cheat::misc::noRecoil)
	{
		bool patched = false;
		if (!patched)
		{
			cUtility.patchBytes(offsets.spreadfunc, "C2 08 00");
			patched = true;
		}
	}
	else
	{
		bool patched = false;
		if (!patched)
		{
			cUtility.patchBytes(offsets.spreadfunc, "83 EC 28");
			patched = true;
		}
	}

	if (cheat::misc::rapidFire)
		offsets.localPlayer->setWeaponCooldDown(cheat::misc::rapidFireCooldown);

	if (cheat::misc::nadeTimer)
		if (offsets.localPlayer->getWeaponId() == 7 && offsets.localPlayer->isAttacking())
			iDraw->drawTimerLine({ (float)offsets.windowWidth / 2, (float)offsets.windowHeight / 2 }, 2, cheat::misc::nadeTimerColor);

	if (cheat::misc::reloadTimer)
		if (offsets.localPlayer->isReloading() != 0)
			if (offsets.localPlayer->getWeaponId() == weaponIds::PISTOL)
				iDraw->drawTimerLine({ (float)offsets.windowWidth / 2, (float)offsets.windowHeight / 2 + 20 }, 1.5, cheat::misc::reloadTimerColor);
			else if (offsets.localPlayer->getWeaponId() == weaponIds::AKIMBO)
				iDraw->drawTimerLine({ (float)offsets.windowWidth / 2, (float)offsets.windowHeight / 2 + 20 }, 1.5, cheat::misc::reloadTimerColor);
			else if (offsets.localPlayer->getWeaponId() == weaponIds::SUBMACHINE)
				iDraw->drawTimerLine({ (float)offsets.windowWidth / 2, (float)offsets.windowHeight / 2 + 20 }, 1.6, cheat::misc::reloadTimerColor);
			else if (offsets.localPlayer->getWeaponId() == weaponIds::CARBINE)
				iDraw->drawTimerLine({ (float)offsets.windowWidth / 2, (float)offsets.windowHeight / 2 + 20 }, 1.8, cheat::misc::reloadTimerColor);
			else if (offsets.localPlayer->getWeaponId() == weaponIds::ASSAULT_RIFLE)
				iDraw->drawTimerLine({ (float)offsets.windowWidth / 2, (float)offsets.windowHeight / 2 + 20 }, 2, cheat::misc::reloadTimerColor);
			else if (offsets.localPlayer->getWeaponId() == weaponIds::SHOTGUN)
				iDraw->drawTimerLine({ (float)offsets.windowWidth / 2, (float)offsets.windowHeight / 2 + 20 }, 3.0, cheat::misc::reloadTimerColor);
			else if (offsets.localPlayer->getWeaponId() == weaponIds::SNIPER_RIFLE)
				iDraw->drawTimerLine({ (float)offsets.windowWidth / 2, (float)offsets.windowHeight / 2 + 20 }, 3.0, cheat::misc::reloadTimerColor);
}
