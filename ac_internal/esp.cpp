#include "cheat.h"
#include "draw.h"
#include "offsets.h"
#include <string>
#include <flogger.hpp>
#include <utility.hpp>

void iDrawDebug() {
    iDraw->borderedBox({ 200.0f, 200.0f }, { 100.0f, 100.0f }, 1, ImColor(255, 0, 0, 255));
    iDraw->circle({ 400.0f, 400.0f }, 50.0f, 24, ImColor(0, 255, 0, 255));
    iDraw->line({ 500.0f, 300.0f }, { 600.0f, 400.0f }, ImColor(0, 0, 255, 255));
    iDraw->rectMultiColor({ 700.0f, 500.0f }, { 150.0f, 150.0f }, ImColor(255, 255, 0, 255), ImColor(255, 0, 255, 0));
}

void infoDebug() {
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
    iDraw->text({ 0, 135 }, ImColor(255, 255, 255, 255), "getViewAngle: %f | %f", vAngle.x, vAngle.y);
    iDraw->text({ 0, 150 }, ImColor(255, 255, 255, 255), "getPosition: %f | %f | %f", pos.x, pos.y, pos.z);
    iDraw->text({ 0, 165 }, ImColor(255, 255, 255, 255), "getWeaponId: %d", offsets.localPlayer->getWeaponId());

    for (int i = 0; i < 16; i++)
        iDraw->text({ 0, 180 + i * 15.f }, ImColor(255, 255, 255, 255), "matrix[%d]: %f", i, offsets.matrix[i]);

    iDraw->text({ 0, 430 }, ImColor(0, 0, 255, 255), "[ LOCAL PLAYER STATE ]");
    iDraw->text({ 0, 445 }, ImColor(255, 255, 255, 255), "isAttacking: %d", offsets.localPlayer->isAttacking());
    iDraw->text({ 0, 460 }, ImColor(255, 255, 255, 255), "isAlive: %d", offsets.localPlayer->isAlive());
    iDraw->text({ 0, 475 }, ImColor(255, 255, 255, 255), "playerState: %d", offsets.localPlayer->playerState());
    iDraw->text({ 0, 490 }, ImColor(255, 255, 255, 255), "isReloading: %d", offsets.localPlayer->isReloading());
    iDraw->text({ 0, 505 }, ImColor(255, 255, 255, 255), "getWeaponId: %d", offsets.localPlayer->getWeaponId());
    iDraw->text({ 0, 520 }, ImColor(255, 255, 255, 255), "curWeapon: 0x%x", offsets.localPlayer->curWeapon());
}

vec3 angleToDirection(vec2 viewAngle) {
    float pitch = viewAngle.x * (M_PI / 180.0f);
    float yaw = viewAngle.y * (M_PI / 180.0f);
    return { cosf(pitch) * cosf(yaw), cosf(pitch) * sinf(yaw), -sinf(pitch) };
}

void drawAimLine(pEntity* ent) {
    if (!cheat::esp::aimAngle) return;

    vec3 playerPos = ent->getHeadPosition();
    vec3 direction = angleToDirection(ent->getViewAngle());
    vec3 endPoint = { playerPos.x + direction.x * 2, playerPos.y + direction.y * 2, playerPos.z + direction.z * 2 };

    vec2 playerScreenPos, endScreenPos;
    if (cUtility.WorldToScreen(playerPos, playerScreenPos) && cUtility.WorldToScreen(endPoint, endScreenPos)) {
        iDraw->line(playerScreenPos, endScreenPos, cheat::esp::aimAngleColor);
    }
}

void textEsp(pEntity* ent) {
    vec3 feetPosition = ent->getFeetPosition();
    vec3 headPosition = ent->getHeadPosition();
    vec2 feetPosition2d, headPosition2d;

    if (!cUtility.WorldToScreen(feetPosition, feetPosition2d) || !cUtility.WorldToScreen(headPosition, headPosition2d)) return;

    float offset = (headPosition2d.y - feetPosition2d.y) / 4;

    if (cheat::esp::name) {
        ImColor nameColor = (cheat::esp::visible && offsets.isVisible(ent)) ? cheat::esp::nameColor : cheat::esp::invisibleNameColor;
        iDraw->text({ headPosition2d.x + offset, headPosition2d.y + (offset / 3) - 20 }, nameColor, "%s", ent->getName());
    }

    if (cheat::esp::health) {
        iDraw->text({ headPosition2d.x + offset - 21, headPosition2d.y + (offset / 3) }, cheat::esp::healthColor, "%d", ent->getHealth());
    }

    if (cheat::esp::armour) {
        iDraw->text({ headPosition2d.x + offset - 21, headPosition2d.y + (offset / 3) + 10 }, cheat::esp::armourColor, "%d", ent->getArmour());
    }
}

void boxEsp(pEntity* ent) {
    vec3 feetPosition = ent->getFeetPosition();
    vec3 headPosition = ent->getHeadPosition();
    vec2 feetPosition2d, headPosition2d;

    if (!cUtility.WorldToScreen(feetPosition, feetPosition2d) || !cUtility.WorldToScreen(headPosition, headPosition2d)) return;

    float boxWidth = (headPosition2d.y - feetPosition2d.y) / 4;

    if (cheat::esp::box) {
        ImColor boxColor = (cheat::esp::visible && offsets.isVisible(ent)) ? cheat::esp::boxColor : cheat::esp::invisibleBoxColor;
        iDraw->borderedBox({ headPosition2d.x + boxWidth, headPosition2d.y + boxWidth / 3 }, { feetPosition2d.x - boxWidth, feetPosition2d.y }, 1, boxColor);
    }

    if (cheat::esp::fillBox) {
        ImColor fillBoxTopColor = (cheat::esp::visible && offsets.isVisible(ent)) ? cheat::esp::fillBoxTopColor : cheat::esp::invisibleFillBoxTopColor;
        ImColor fillBoxBottomColor = (cheat::esp::visible && offsets.isVisible(ent)) ? cheat::esp::fillBoxBottomColor : cheat::esp::invisibleFillBoxBottomColor;
        iDraw->rectMultiColor({ headPosition2d.x + boxWidth, headPosition2d.y + boxWidth / 3 }, { feetPosition2d.x - boxWidth, feetPosition2d.y }, fillBoxTopColor, fillBoxBottomColor);
    }
}

void cheat::esp::initAll() {
    if (cheat::misc::infoDebug) infoDebug();
    if (cheat::misc::drawDebug) iDrawDebug();

    for (pEntity* ent : offsets.getEntity()) {
        if (!cheat::esp::enable || ent->getHealth() <= 0) continue;
        if (cheat::esp::teamCheck && ent->getTeam() == offsets.localPlayer->getTeam()) continue;

        drawAimLine(ent);
        textEsp(ent);
        boxEsp(ent);
    }
}