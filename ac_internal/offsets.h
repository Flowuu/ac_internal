#ifndef offsets_h
#define offsets_h

#include <Windows.h>
#include <flogger.hpp>
#include "math_def.h"

#define aHealth 0xEC
#define aArmour 0xF0
#define aAttacking 0x204	//sub_4D68A0(*(unsigned __int8*)(v3 + 516));
#define aScoping 0x66		//sub_4D68A0(*(unsigned __int8 *)(v3 + 102));

#define aCurweaponId 0x4	//(*(void **)(*(_DWORD *)(v3 + 0x364) + 4));
#define aAmmo 0x10
#define aMagcontent 0x14		//(**(_DWORD **)(*(_DWORD *)(player + 0x364) + 20));
#define aReload 0x20
#define aShots 0x124
#define aShotCooldown 0x18
#define aSpread 0x114
#define aRecoil 0x11E
#define aDamage 0x10C
#define aReloadTime 0x108
#define aSound 0x104

#define aName_1 0x205	//*(void **)(v3 + 0x205);
#define aTeam_1 0x30C
#define aPing 0x1D0
#define aPj 0x1CC
#define aState 0x76		//((void *)*(unsigned __int8 *)(v3 + 0x76));
#define aRole 0x200
#define aFrags 0x1DC
#define aFlags_1 0x1E0
#define aDeaths 0x1E4
#define aTks 0x1E8
#define aAlive 0x76		//((void *)(*(_BYTE *)(v3 + 0x76) == 0));

#define xHeadPosition 0x4
#define yHeadPosition 0x8
#define zHeadPosition 0xc

#define xPosition 0x28
#define yPosition 0x2C
#define zPosition 0x30

#define xViewAngle 0x34
#define yViewAngle 0x38


enum weaponIds {
	KNIFE = 0,
	PISTOL = 1,
	ASSAULT_RIFLE = 6,
	SNIPER_RIFLE = 5,
	SUBMACHINE = 4,
	SHOTGUN = 3,
	CARBINE = 2,
	AKIMBO = 8,
	GRENADE = 7
};

class pEntity
{
private:

	uintptr_t curWeapon() {
		return *(uintptr_t*)(this + 0x364);
	}

	char* iptoa(uint32_t ip)
	{
		char formattedIP[16]; // Renamed to avoid conflicts
		std::snprintf(formattedIP, sizeof(formattedIP), "%d.%d.%d.%d",
			(ip >> 24) & 255,
			(ip >> 16) & 255,
			(ip >> 8) & 255,
			ip & 255);
		return formattedIP;
	}
#define ATTR_STR(name, attribute)    if(!strcmp(attr, #name)) { result(attribute); return; }
public:
	char* getName()
	{
		return (char*)(this + aName_1);
	}

	bool isAlive() {
		return !*(bool*)(this + aAlive);
	}

	int playerState() {
		return *(int*)(this + aState);
	}

	int getPing() {
		return *(int*)(this + aPing);
	}

	int getDeathCount() {
		return *(int*)(this + aDeaths);
	}

	int getKillCount() {
		return *(int*)(this + aFrags);
	}

	int getHealth() {
		return *(int*)(this + aHealth);
	}

	int getArmour() {
		return *(int*)(this + aArmour);
	}

	int getTeam() {
		return *(int*)(this + aTeam_1);
	}

	int getMagcontent() {
		return **(int**)(curWeapon() + aMagcontent);
	}

	int getAmmo() {
		return **(int**)(curWeapon() + aAmmo);
	}

	int getWeaponId() {
		return *(int*)(curWeapon() + aCurweaponId);
	}

	const char* getWeaponName()
	{
		const char* weapon = NULL;

		if (this->getWeaponId() == weaponIds::PISTOL)
			weapon = "Pistol";
		else if (this->getWeaponId() == weaponIds::AKIMBO)
			weapon = "Akimbo";
		else if (this->getWeaponId() == weaponIds::SUBMACHINE)
			weapon = "Submachine";
		else if (this->getWeaponId() == weaponIds::CARBINE)
			weapon = "Carbine";
		else if (this->getWeaponId() == weaponIds::ASSAULT_RIFLE)
			weapon = "Assault Rifle";
		else if (this->getWeaponId() == weaponIds::SHOTGUN)
			weapon = "Shotgun";
		else if (this->getWeaponId() == weaponIds::SNIPER_RIFLE)
			weapon = "Sniper Rifle";
		else if (this->getWeaponId() == weaponIds::KNIFE)
			weapon = "Knife";

		return weapon;
	}

	bool isAttacking() {
		return *(bool*)(this + aAttacking);
	}

	bool isScopig() {
		return *(bool*)(this + aScoping);
	}

	bool isReloading() {
		return *(bool*)(curWeapon() + aReload);
	}

	bool isShooting() {
		return *(bool*)(curWeapon() + aAttacking);
	}

	vec3 getFeetPosition()
	{
		return { *(float*)(this + xPosition), *(float*)(this + yPosition), *(float*)(this + zPosition) };
	}

	vec3 getHeadPosition()
	{
		return { *(float*)(this + xHeadPosition), *(float*)(this + yHeadPosition), *(float*)(this + zHeadPosition) };
	}

	vec2 getViewAngle()
	{
		return { *(float*)(this + xViewAngle), *(float*)(this + yViewAngle)};
	}

	void setName(char* name) {
		char* namePtr = (char*)((uintptr_t)this + aName_1);
		strcpy(namePtr, name);
	}

	void setHealth(int health) {
		*(int*)(this + aHealth) = health;
	}

	void setAmmo(int ammo) {
		**(int**)(curWeapon() + aMagcontent) = ammo;
	}

	void setArmour(int armour) {
		*(int*)(this + aArmour) = armour;
	}

	void setSpread(int spread) {
		*(int*)(curWeapon() + aSpread) = spread;
	}

	void setRecoil(int recoil) {
		*(int*)(curWeapon() + aRecoil) = recoil;
	}

	void setAttack(bool attack)
	{
		*(bool*)(this + aAttacking) = attack;
	}

	void setWeaponCooldDown(int cooldown) {
		**(int**)(curWeapon() + aShotCooldown) = cooldown;
	}

	void setViewAngle(vec2 angle)
	{
		*(float*)(this + xViewAngle) = angle.x;
		*(float*)(this + yViewAngle) = angle.y;
	}

	void setPosition(vec3 position)
	{
		*reinterpret_cast<float*>(this + xPosition) = position.x;
		*reinterpret_cast<float*>(this + yPosition) = position.y;
		*reinterpret_cast<float*>(this + zPosition) = position.z;
	}

	void setHeadPosition(vec3 position)
	{
		*reinterpret_cast<float*>(this + xHeadPosition) = position.x;
		*reinterpret_cast<float*>(this + yHeadPosition) = position.y;
		*reinterpret_cast<float*>(this + zHeadPosition) = position.z;
	}

};

class offset
{
public:
	float* matrix;
	int windowHeight;
	int windowWidth;

	uintptr_t* entitylistPtr = NULL;
	uintptr_t intersectGeometryPtr = NULL;
	pEntity* localPlayer = NULL;

	int* playerCount;

	std::vector<pEntity*> getEntity();

	pEntity* getClosedTarget();

	void intersectGeometry(const vec3& from, vec3& to);

	bool isVisible(pEntity* ent);

	void init();

}; inline offset offsets;

#endif // !offsets_h
