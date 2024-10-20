#pragma once
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl2.h>
#include <imgui/imgui_impl_win32.h>
#include "offsets.h"

namespace cheat
{
    void initAll();

    namespace aimbot
    {
        void initAll();

        inline bool enable = true;
        inline bool visible = false;
        inline bool silent = true;
        inline bool teamCheck = true;
        inline float fov = 100.f;
    }

    namespace esp
    {
        void initAll();

        inline bool enable = true;
        inline bool visible = false;
        inline bool teamCheck = true;
        inline bool name = true;
        inline bool health = true;
        inline bool armour = true;
        inline bool box = true;
        inline bool fillBox = false;
        inline bool aimAngle = true;

        inline ImColor nameColor = { 255, 255, 255, 255 };
        inline ImColor invisibleNameColor = { 100, 100, 255, 255 };

        inline ImColor healthColor = { 0, 255, 0, 255 };
        inline ImColor armourColor = { 0, 0, 255, 255 };

        inline ImColor boxColor = { 255, 100, 100, 255 };
        inline ImColor invisibleBoxColor = { 100, 100, 255, 255 };

        inline ImColor fillBoxTopColor = { 255, 100, 100, 0 };
        inline ImColor fillBoxBottomColor = { 255, 100, 100, 100 };
        inline ImColor invisibleFillBoxTopColor = { 100, 100, 255, 0 };
        inline ImColor invisibleFillBoxBottomColor = { 100, 100, 255, 100 };

        inline ImColor aimAngleColor = { 255, 255, 255, 255 };
    }

    namespace misc
    {
        void initAll();

        inline bool enable = true;
        inline bool rapidFire = false;
        inline int rapidFireCooldown = 70;

        inline bool infiniteAmmo = false;
        inline bool infiniteHealth = false;
        inline bool noRecoil = false;

        inline bool reloadTimer = true;
        inline ImColor reloadTimerColor = { 255, 0, 0, 100 };

        inline bool nadeTimer = true;
        inline ImColor nadeTimerColor = { 255, 0, 0, 100 };

        inline char setName[32] = "ac_internal.dll";
        inline int clientNumber;
        inline bool playerList = true;
        inline char ipAddress[64] = "null";

        inline bool infoDebug = false;
        inline bool drawDebug = false;
    }

    namespace menu
    {
        void initImgui();
        void closeImgui();
        void mainMenu();
        inline bool menuToggle = true;
    }
}
