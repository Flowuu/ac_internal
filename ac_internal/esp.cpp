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
	vec3 pos = offsets.localPlayer->getPosition();
	iDraw->text({ 0, 75 }, ImColor(0, 0, 255, 255), "[ LOCAL PLAYER ]");

	iDraw->text({ 0, 90 }, ImColor(255, 255, 255, 255), "Name: %s", offsets.localPlayer->getName());
	iDraw->text({ 0, 105 }, ImColor(255, 255, 255, 255), "getHealth: %d", offsets.localPlayer->getHealth());
	iDraw->text({ 0, 120 }, ImColor(255, 255, 255, 255), "getArmour: %d", offsets.localPlayer->getArmour());
	iDraw->text({ 0, 135 }, ImColor(255, 255, 255, 255), "getViewAngle: %f | %f ", vAngle.x, vAngle.y);
	iDraw->text({ 0, 150 }, ImColor(255, 255, 255, 255), "getPosition: %f | %f | %f | %f |", pos.x, pos.y, pos.z);
	//iDraw->text({ 0, 60 }, ImColor(255, 255, 255, 255), "getMagcontent: %d", offsets.localPlayer->getMagcontent());
	for (int i = 0; i < 16; i++)
		iDraw->text({ 0, 165 + i * 15.f }, ImColor(255, 255, 255, 255), "matrix  [%d]: %d", i, offsets.matrix[i]);


	iDraw->text({ 0, 430 }, ImColor(0, 0, 255, 255), "[ LOCAL PLAYER STATE ]");

	iDraw->text({ 0, 445 }, ImColor(255, 255, 255, 255), "isAttacking: %d", offsets.localPlayer->isAttacking());
	iDraw->text({ 0, 460 }, ImColor(255, 255, 255, 255), "isAlive: %d", offsets.localPlayer->isAlive());
	iDraw->text({ 0, 475 }, ImColor(255, 255, 255, 255), "playerState: %d", offsets.localPlayer->playerState());


}

void box(vec2 position, ImColor color)
{
	
}

void cheat::esp::initAll()
{
	//infoDebug();
	//iDrawDebug();

	for (pEntity* ent : offsets.getEntity())
	{
		vec3 pos3d = ent->getPosition();
		vec2 pos2d;

		if (cUtility.WorldToScreen(pos3d, pos2d))
			iDraw->circle(pos2d, 5, 6, ImColor(255, 0, 255, 255));
	}
}