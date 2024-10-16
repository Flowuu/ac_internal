#include "cheat.h"
#include "draw.h"
#include "offsets.hpp"
#include "string"
#include <flogger.hpp>
#include "draw.h"

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
	iDraw->text({ 0, 10 }, ImColor(255, 255, 255, 255), "window width: %d", vMatrix.windowWidth);
	iDraw->text({ 0, 25 }, ImColor(255, 255, 255, 255), "window height: %d", vMatrix.windowHeight);

	iDraw->text({ 0, 35 }, ImColor(255, 255, 255, 255), "Name: %s", offsets.localPlayer->getName());
	iDraw->text({ 0, 60 }, ImColor(255, 255, 255, 255), "getHealth: %d", offsets.localPlayer->getHealth());
	iDraw->text({ 0, 75 }, ImColor(255, 255, 255, 255), "getArmour: %d", offsets.localPlayer->getArmour());
	//iDraw->text({ 0, 60 }, ImColor(255, 255, 255, 255), "getMagcontent: %d", offsets.localPlayer->getMagcontent());

	vec2 vAngle = offsets.localPlayer->getViewAngle();
	vec3 pos = offsets.localPlayer->getPosition();

	iDraw->text({ 0, 90 }, ImColor(255, 255, 255, 255), "getViewAngle: %f | %f ", vAngle.x, vAngle.y);
	iDraw->text({ 0, 105 }, ImColor(255, 255, 255, 255), "getPosition: %f | %f | %f | %f |", pos.x, pos.y, pos.z);

	iDraw->text({ 0, 125 }, ImColor(255, 255, 255, 255), "isAttacking: %d", offsets.localPlayer->isAttacking());
	iDraw->text({ 0, 140 }, ImColor(255, 255, 255, 255), "isAlive: %d", offsets.localPlayer->isAlive());
	iDraw->text({ 0, 155 }, ImColor(255, 255, 255, 255), "playerState: %d", offsets.localPlayer->playerState());

	iDraw->text({ 0, 190 }, ImColor(255, 255, 255, 255), "Player Count: %d", offsets.playerCount);

}

void box()
{
	
}

void cheat::esp::initAll()
{
	infoDebug();
	//iDrawDebug();

	for (pEntity* ent : offsets.entitylist())
	{
		vec3 pos = ent->getPosition();
		vec2 pos2d{};

		iDraw->text({ 0, 200 }, ImColor(255, 255, 255, 255), "pos2d: %f | %f ", pos2d.x, pos2d.y);

		if (vMatrix.WorldToScreen(pos, pos2d))
			iDraw->line(vec2{ vMatrix.windowHeight / 2.f, vMatrix.windowWidth / 2.f }, pos2d, ImColor(255, 255, 255, 255));
	}
}