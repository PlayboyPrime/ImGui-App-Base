#include "app.h"

#include <imgui_internal.h>

#include "tabs/tabs.h"

namespace app
{
	void render()
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		dockspace = ImGui::DockSpaceOverViewport(viewport, ImGuiDockNodeFlags_NoResize | ImGuiDockNodeFlags_NoWindowMenuButton | ImGuiDockNodeFlags_NoCloseButton);

		tabs::welcome::render();
		tabs::credits::render();
		tabs::settings::render();
#ifdef _DEBUG
		tabs::debug::render();
#endif

		ImGui::GetBackgroundDrawList()->AddRectFilled(viewport->Pos, { viewport->Pos.x + viewport->Size.x, viewport->Pos.y + 40 }, bar_color);
	}
}
