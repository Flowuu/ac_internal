#ifndef draw_h
#define draw_h

#include "imgui/imgui.h"
#include <cstdarg>
#include <cstdio>
#include <math_def.h>

class draw
{
public:
	void textEx(vec2 position, ImColor color, const char* text)
	{
		ImDrawList* drawList = ImGui::GetBackgroundDrawList();
		ImVec2 pos = { position.x, position.y };

		drawList->AddText(ImVec2(pos.x + 1, pos.y + 1), ImColor(0, 0, 0, 255), text);
		drawList->AddText(pos, color, text);
	}

	void text(vec2 position, ImColor color, const char* text, ...)
	{
		ImDrawList* drawList = ImGui::GetBackgroundDrawList();
		ImVec2 pos = { position.x, position.y };

		char buffer[1024];

		va_list args;
		va_start(args, text);

		vsnprintf(buffer, sizeof(buffer), text, args);

		va_end(args);

		drawList->AddText(ImVec2(pos.x + 1, pos.y + 1), ImColor(0, 0, 0, 255), buffer);
		drawList->AddText(pos, color, buffer);
	}

	void borderedBox(vec2 position, vec2 position2, int thickness, ImColor color)
	{
		ImDrawList* drawList = ImGui::GetBackgroundDrawList();
		ImVec2 pos = { position.x, position.y };
		ImVec2 pos2 = { position2.x, position2.y };

		drawList->AddLine(ImVec2(pos.x, pos.y - 1), ImVec2(pos.x, pos.y + pos2.y + 1), ImColor(0, 0, 0, 255), thickness + 2); //left top corner to left bottom corner (LEFT SIDE)
		drawList->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos.x + pos2.x, pos.y), ImColor(0, 0, 0, 255), thickness + 2); //left top corner to right top corner (TOP SIDE)
		drawList->AddLine(ImVec2(pos.x + pos2.x, pos.y + pos2.y), ImVec2(pos.x + pos2.x, pos.y - 1), ImColor(0, 0, 0, 255), thickness + 2); //right bottom corner to right top corner (RIGHT SIDE)
		drawList->AddLine(ImVec2(pos.x + pos2.x + 2, pos.y + pos2.y), ImVec2(pos.x, pos.y + pos2.y), ImColor(0, 0, 0, 255), thickness + 2); //right bottom corner to left bottom corner (BOTTOM SIDE)

		drawList->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos.x, pos.y + pos2.y), color, thickness); //left top corner to left bottom corner (LEFT SIDE)
		drawList->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos.x + pos2.x, pos.y), color, thickness); //left top corner to right top corner (TOP SIDE)
		drawList->AddLine(ImVec2(pos.x + pos2.x, pos.y + pos2.y), ImVec2(pos.x + pos2.x, pos.y), color, thickness); //right bottom corner to right top corner (RIGHT SIDE)
		drawList->AddLine(ImVec2(pos.x + pos2.x + 1, pos.y + pos2.y), ImVec2(pos.x, pos.y + pos2.y), color, thickness); //right bottom corner to left bottom corner (BOTTOM SIDE)
	}

	void DrawCorneredBox(vec2 position, ImVec2 position2, float thickness, ImColor color)
	{
		ImDrawList* drawList = ImGui::GetBackgroundDrawList();
		ImVec2 pos = { position.x, position.y };
		ImVec2 pos2 = { position2.x, position2.y };

		float lineW = (pos2.x / 4);
		float lineH = (pos2.y / 4);

		//black outlines
		drawList->AddLine(ImVec2(pos.x, pos.y),								ImVec2(pos.x, pos.y + lineH), ImColor(0, 0, 0, 255), 3);
		drawList->AddLine(ImVec2(pos.x, pos.y),								ImVec2(pos.x + lineW, pos.y), ImColor(0, 0, 0, 255), 3);
		drawList->AddLine(ImVec2(pos.x + pos2.x - lineW, pos.y),			ImVec2(pos.x + pos2.x, pos.y), ImColor(0, 0, 0, 255), 3);
		drawList->AddLine(ImVec2(pos.x + pos2.x, pos.y),					ImVec2(pos.x + pos2.x, pos.y + lineH), ImColor(0, 0, 0, 255), 3);
		drawList->AddLine(ImVec2(pos.x, pos.y + pos2.y - lineH),			ImVec2(pos.x, pos.y + pos2.y), ImColor(0, 0, 0, 255), 3);
		drawList->AddLine(ImVec2(pos.x, pos.y + pos2.y),					ImVec2(pos.x + lineW, pos.y + pos2.y), ImColor(0, 0, 0, 255), 3);
		drawList->AddLine(ImVec2(pos.x + pos2.x - lineW, pos.y + pos2.y),	ImVec2(pos.x + pos2.x, pos.y + pos2.y), ImColor(0, 0, 0, 255), 3);
		drawList->AddLine(ImVec2(pos.x + pos2.x, pos.y + pos2.y - lineH),	ImVec2(pos.x + pos2.x, pos.y + pos2.y), ImColor(0, 0, 0, 255), 3);

		//corners
		drawList->AddLine(ImVec2(pos.x, pos.y),								ImVec2(pos.x, pos.y + lineH), color, thickness);
		drawList->AddLine(ImVec2(pos.x, pos.y),								ImVec2(pos.x + lineW, pos.y), color, thickness);
		drawList->AddLine(ImVec2(pos.x + pos2.x - lineW, pos.y),			ImVec2(pos.x + pos2.x, pos.y), color, thickness);
		drawList->AddLine(ImVec2(pos.x + pos2.x, pos.y),					ImVec2(pos.x + pos2.x, pos.y + lineH), color, thickness);
		drawList->AddLine(ImVec2(pos.x, pos.y + pos2.y - lineH),			ImVec2(pos.x, pos.y + pos2.y), color, thickness);
		drawList->AddLine(ImVec2(pos.x, pos.y + pos2.y),					ImVec2(pos.x + lineW, pos.y + pos2.y), color, thickness);
		drawList->AddLine(ImVec2(pos.x + pos2.x - lineW, pos.y + pos2.y),	ImVec2(pos.x + pos2.x, pos.y + pos2.y), color, thickness);
		drawList->AddLine(ImVec2(pos.x + pos2.x, pos.y + pos2.y - lineH),	ImVec2(pos.x + pos2.x, pos.y + pos2.y), color, thickness);
	}

	void rectMultiColor(ImVec2 position, ImVec2 position2, ImColor color, ImColor color2)
	{
		ImDrawList* drawList = ImGui::GetBackgroundDrawList();
		ImVec2 pos = { position.x, position.y };
		ImVec2 pos2 = { position2.x, position2.y };

		drawList->AddRectFilledMultiColor(pos, ImVec2(pos2.x + 100, pos2.y + 100), color, color, color2, color2);
	}

	void circle(vec2 position, float radius, int segment, ImColor color)
	{
		ImDrawList* drawList = ImGui::GetBackgroundDrawList();
		ImVec2 pos = { position.x, position.y };

		drawList->AddCircle(pos, radius, color, segment, 1);
	}

	void line(vec2 position, vec2 position2, ImColor color)
	{
		ImDrawList* drawList = ImGui::GetBackgroundDrawList();
		ImVec2 pos = ImVec2( position.x, position.y );
		ImVec2 pos2 = ImVec2( position2.x, position2.y);

		drawList->AddLine(pos, pos2, color);
	}

}; inline draw* iDraw;

#endif // !draw_h
