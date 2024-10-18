#ifndef draw_h
#define draw_h

#include "imgui/imgui.h"
#include <cstdarg>
#include <cstdio>
#include <math_def.h>
#include <chrono>

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

		drawList->AddRect({ position.x + 1, position.y + 1}, { position2.x + 1, position2.y + 1}, ImGui::ColorConvertFloat4ToU32({ 0, 0, 0, color.Value.w }), 0, 0, 1);
		drawList->AddRect({ position.x - 1, position.y - 1 }, { position2.x - 1, position2.y - 1 }, ImGui::ColorConvertFloat4ToU32({ 0, 0, 0, color.Value.w }), 0, 0, 1);
		drawList->AddRect({ position.x, position.y }, { position2.x, position2.y }, color, 0, 0, 1);
	}

	void corneredBox(vec2 position, vec2 position2, float thickness, ImColor color)
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

		drawList->AddRectFilledMultiColor(pos, ImVec2(pos2.x, pos2.y), color, color, color2, color2);
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

	void drawTimerLine(vec2 position, vec2 position2, float durationSecond, float lineThickness, bool followLine, ImColor color)
	{
		ImDrawList* drawList = ImGui::GetBackgroundDrawList();
		static auto start_time = std::chrono::high_resolution_clock::now();
		auto current_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> elapsed = current_time - start_time;

		float progress = elapsed.count() / durationSecond;
		float remainingTime = durationSecond - elapsed.count();

		if (remainingTime == 0.0f) return;

		if (remainingTime <= 0.0f)
		{
			remainingTime = 0.0f;
			progress = 1.0f;
		}

		float lineWidth = position2.x - position.x;  // Calculate width based on position

		ImVec2 lineStart = ImVec2(position.x, position.y);
		ImVec2 lineEnd = ImVec2(lineStart.x + lineWidth * progress, lineStart.y);
		ImVec2 lineFullEnd = ImVec2(lineStart.x + lineWidth, lineStart.y);

		// Draw the black background line
		drawList->AddLine(lineStart, lineFullEnd, ImColor(0, 0, 0, 255), lineThickness + 2.0f);

		// Draw the progress line ensuring it does not overlap the black line
		drawList->AddLine({ lineStart.x + 1, lineStart.y }, { lineEnd.x - 1, lineEnd.y }, color, lineThickness);

		char time_text[16];
		snprintf(time_text, sizeof(time_text), "%.1f sec", remainingTime);

		ImVec2 textSize = ImGui::CalcTextSize(time_text);
		ImVec2 textPos;

		if (followLine)
			textPos = lineEnd;
		else
			textPos = ImVec2(lineStart.x + (lineWidth - textSize.x) * 0.5f, lineStart.y - textSize.y - 10.0f);

		drawList->AddText(textPos, ImColor(255, 255, 255, 255), time_text);

		if (remainingTime == 0.0f)
		{
			start_time = std::chrono::high_resolution_clock::now();
		}
	}

	void drawTimerLine(vec2 position, float durationSecond, ImColor color)
	{
		float lineWidth = 300.0f;  // Desired width of the timer line
		float lineThickness = 1.0f;
		bool followLine = false;

		// Center the start position by moving it to the left by half the line width
		vec2 centeredPosition = vec2(position.x - lineWidth / 2, position.y);

		// Calculate position2 as the endpoint, based on the centered start position
		vec2 position2 = vec2(centeredPosition.x + lineWidth, centeredPosition.y);

		drawTimerLine(centeredPosition, position2, durationSecond, lineThickness, followLine, color);
	}

}; inline draw* iDraw;

#endif // !draw_h
