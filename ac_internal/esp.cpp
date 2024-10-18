#include "cheat.h"
#include "draw.h"
#include "offsets.h"
#include "string"
#include "draw.h"

#include <flogger.hpp>
#include <utility.hpp>


void iDrawDebug()
{
	vec2 boxStart = { 200.0f, 200.0f };
	vec2 boxEnd = { 100.0f, 100.0f };
	iDraw->borderedBox(boxStart, boxEnd, 1, ImColor(255, 0, 0, 255));

	vec2 circlePos = { 400.0f, 400.0f };
	iDraw->circle(circlePos, 50.0f, 24, ImColor(0, 255, 0, 255));

	vec2 lineStart = { 500.0f, 300.0f };
	vec2 lineEnd = { 600.0f, 400.0f };
	iDraw->line(lineStart, lineEnd, ImColor(0, 0, 255, 255));

	ImVec2 rectStart = { 700.0f, 500.0f };
	ImVec2 rectEnd = { 150.0f, 150.0f };
	iDraw->rectMultiColor(rectStart, rectEnd, ImColor(255, 255, 0, 255), ImColor(255, 0, 255, 0));
}

void infoDebug()
{
	iDraw->text({ 0, 10 }, ImColor(0, 0, 255, 255), "[ GAME ]");

	iDraw->text({ 0, 25 }, ImColor(255, 255, 255, 255), "window width: %d", offsets.windowWidth);
	iDraw->text({ 0, 40 }, ImColor(255, 255, 255, 255), "window height: %d", offsets.windowHeight);
	iDraw->text({ 0, 55 }, ImColor(255, 255, 255, 255), "player Count: %d", *offsets.playerCount);


	vec2 vAngle = offsets.localPlayer->getViewAngle();
	vec3 pos = offsets.localPlayer->getFeetPosition();
	iDraw->text({ 0, 75 }, ImColor(0, 0, 255, 255), "[ LOCAL PLAYER ]");

	iDraw->text({ 0, 90 }, ImColor(255, 255, 255, 255), "Name: %s", offsets.localPlayer->getName());
	iDraw->text({ 0, 105 }, ImColor(255, 255, 255, 255), "getHealth: %d", offsets.localPlayer->getHealth());
	iDraw->text({ 0, 120 }, ImColor(255, 255, 255, 255), "getArmour: %d", offsets.localPlayer->getArmour());
	iDraw->text({ 0, 135 }, ImColor(255, 255, 255, 255), "getViewAngle: %f | %f ", vAngle.x, vAngle.y);
	iDraw->text({ 0, 150 }, ImColor(255, 255, 255, 255), "getPosition: %f | %f | %f | %f |", pos.x, pos.y, pos.z);
	iDraw->text({ 0, 165 }, ImColor(255, 255, 255, 255), "getWeaponId: %d", offsets.localPlayer->getWeaponId());
	for (int i = 0; i < 16; i++)
		iDraw->text({ 0, 180 + i * 15.f }, ImColor(255, 255, 255, 255), "matrix  [%d]: %f", i, offsets.matrix[i]);


	iDraw->text({ 0, 430 }, ImColor(0, 0, 255, 255), "[ LOCAL PLAYER STATE ]");

	iDraw->text({ 0, 445 }, ImColor(255, 255, 255, 255), "isAttacking: %d", offsets.localPlayer->isAttacking());
	iDraw->text({ 0, 460 }, ImColor(255, 255, 255, 255), "isAlive: %d", offsets.localPlayer->isAlive());
	iDraw->text({ 0, 475 }, ImColor(255, 255, 255, 255), "playerState: %d", offsets.localPlayer->playerState());
	iDraw->text({ 0, 490 }, ImColor(255, 255, 255, 255), "isReloading: %d", offsets.localPlayer->isReloading());
	iDraw->text({ 0, 505 }, ImColor(255, 255, 255, 255), "getWeaponId: %d", offsets.localPlayer->getWeaponId());
}

void textEsp(pEntity* ent)
{
	vec3 feetPosition = ent->getFeetPosition();
	vec3 headPosition = ent->getHeadPosition();
	vec2 feetPosition2d;
	vec2 headPosition2d;

	if (!cUtility.WorldToScreen(feetPosition, feetPosition2d) || !cUtility.WorldToScreen(headPosition, headPosition2d))
		return;

	float calc = (headPosition2d.y - feetPosition2d.y) / 4;

	if(cheat::esp::name)
		if (cheat::esp::visible)
			if(offsets.isVisible(ent))
				iDraw->text({ headPosition2d.x + calc, headPosition2d.y + (calc / 3) - 20 }, cheat::esp::nameColor, "%s", ent->getName());
			else
				iDraw->text({ headPosition2d.x + calc, headPosition2d.y + (calc / 3) - 20 }, cheat::esp::InvisibleNameColor, "%s", ent->getName());
		else
			iDraw->text({ headPosition2d.x + calc, headPosition2d.y + (calc / 3) - 20 }, cheat::esp::nameColor, "%s", ent->getName());

	if (cheat::esp::health)
		iDraw->text({ headPosition2d.x + calc - 21, headPosition2d.y + (calc / 3)}, cheat::esp::healthColor, "%d", ent->getHealth());

	if (cheat::esp::armour)
		iDraw->text({ headPosition2d.x + calc - 21, headPosition2d.y + (calc / 3) + 10}, cheat::esp::armourColor, "%d", ent->getArmour());
}

void boxEsp(pEntity* ent)
{
	vec3 feetPosition = ent->getFeetPosition();
	vec3 headPosition = ent->getHeadPosition();
	vec2 feetPosition2d;
	vec2 headPosition2d;

	if (!cUtility.WorldToScreen(feetPosition, feetPosition2d) || !cUtility.WorldToScreen(headPosition, headPosition2d))
		return;

	float boxWidth = (headPosition2d.y - feetPosition2d.y) / 4;

	if (cheat::esp::box)
	{
		if (cheat::esp::visible)
		{
			if(offsets.isVisible(ent))
				iDraw->borderedBox({ headPosition2d.x + boxWidth , headPosition2d.y + boxWidth / 3 }, { feetPosition2d.x - boxWidth, feetPosition2d.y }, 1, cheat::esp::boxColor);
			else
				iDraw->borderedBox({ headPosition2d.x + boxWidth , headPosition2d.y + boxWidth / 3 }, { feetPosition2d.x - boxWidth, feetPosition2d.y }, 1, cheat::esp::InvisibleboxColor);
		}
		else
			iDraw->borderedBox({ headPosition2d.x + boxWidth , headPosition2d.y + boxWidth / 3 }, { feetPosition2d.x - boxWidth, feetPosition2d.y }, 1, cheat::esp::boxColor);
	}

	if (cheat::esp::fillBox)
	{
		if (cheat::esp::visible)
		{
			if (offsets.isVisible(ent))
				iDraw->rectMultiColor({ headPosition2d.x + boxWidth , headPosition2d.y + boxWidth / 3 }, { feetPosition2d.x - boxWidth, feetPosition2d.y }, cheat::esp::fillBoxTopColor, cheat::esp::fillBoxBottomColor);
			else
				iDraw->rectMultiColor({ headPosition2d.x + boxWidth , headPosition2d.y + boxWidth / 3 }, { feetPosition2d.x - boxWidth, feetPosition2d.y }, cheat::esp::InvisibleFillBoxTopColor, cheat::esp::InvisibleFillBoxBottomColor);
		}
		else
			iDraw->rectMultiColor({ headPosition2d.x + boxWidth , headPosition2d.y + boxWidth / 3 }, { feetPosition2d.x - boxWidth, feetPosition2d.y }, cheat::esp::fillBoxTopColor, cheat::esp::fillBoxBottomColor);
	}
}

void cheat::esp::initAll()
{
	infoDebug();
	//iDrawDebug();

	for (pEntity* ent : offsets.getEntity())
	{
		if (!cheat::esp::enable || ent->getHealth() <= 0)
			continue;

		if (cheat::esp::teamCheck)
			if (ent->getTeam() == offsets.localPlayer->getTeam())
				continue;

		textEsp(ent);
		boxEsp(ent);
	}
}