#pragma once

#include "imgui.h"

namespace app
{
	inline ImGuiID dockspace = 0;
	inline ImVec2 min_window_size = { 240.f, 144.f };
	inline ImVec2 max_window_size = { 1080.f, 720.f };
	inline ImVec2 window_size = { 800.f, 600.f };
	inline ImColor bar_color = { 40, 40, 40, 255 };
	inline ImVec4 background_color = { 0.f, 0.f, 0.f, 255.f };

	void render();
}
