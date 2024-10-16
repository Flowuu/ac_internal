#ifndef offsets_h
#define offsets_h

#include <Windows.h>
#include <flogger.hpp>
#include <math_def.h>
#include "utility.hpp"

#define aHealth 0xEC
#define aArmour 0xF0
#define aAttacking 0x204	//sub_4D68A0(*(unsigned __int8*)(v3 + 516));
#define aScoping 0x66		//sub_4D68A0(*(unsigned __int8 *)(v3 + 102));

#define aCurweapon 0x0	//(*(void **)(*(_DWORD *)(v3 + 0x364) + 4));
#define aNextprimary 0xF8		//(*(void **)(v3 + 0xF8));
#define aMagcontent 0x14		//(**(_DWORD **)(*(_DWORD *)(player + 0x364) + 20));
#define aAmmo 0x10

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

#define xPosition 0x4
#define yPosition 0x8
#define zPosition 0xc

#define xViewAngle 0x34
#define yViewAngle 0x38


class pEntity
{
private:

	uintptr_t curWeapon() {
		return *(uintptr_t*)(*(DWORD*)((uintptr_t)this + 0x364) + 4);
	}

public:
	char* getName()
	{
		return *(char**)(this + aName_1);
	}

	bool isAlive() {
		return !*(bool*)(this + aAlive);
	}

	int playerState() {
		return *(int*)(this + aState);
	}

	int getHealth() {
		return *(int*)(this + aHealth);
	}

	int getArmour() {
		return *(int*)(this + aArmour);
	}

	bool isAttacking() {
		return *(bool*)(this + aAttacking);
	}

	bool isScopig() {
		return *(bool*)(this + aScoping);
	}

	bool getMagcontent() {
		return **(bool**)(curWeapon() + aMagcontent);
	}

	vec3 getPosition()
	{
		return { *(float*)(this + xPosition), *(float*)(this + yPosition), *(float*)(this + zPosition) };
	}

	vec2 getViewAngle()
	{
		return { *(float*)(this + xViewAngle), *(float*)(this + yViewAngle)};
	}

	void setHealth(int health) {
		*(int*)(this + aHealth) = health;
	}

	void setArmour(int armour) {
		*(int*)(this + aArmour) = armour;
	}

	void setViewAngle(vec2 angle)
	{
		*reinterpret_cast<float*>(this + xViewAngle) = angle.x;
		*reinterpret_cast<float*>(this + yViewAngle) = angle.y;
	}

	void setPosition(vec3 position)
	{
		*reinterpret_cast<float*>(this + 0x4) = position.x;
		*reinterpret_cast<float*>(this + 0x8) = position.y;
		*reinterpret_cast<float*>(this + 0xc) = position.z;
	}
};

class offset
{
public:
	uintptr_t entitylistPtr;
	pEntity* localPlayer;
	int playerCount;

}; inline offset offsets;

#endif // !offsets_h
