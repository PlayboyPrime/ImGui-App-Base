#include "imgui.h"
#include "tabs.h"
#include "app/app.h"

namespace tabs::settings
{
	void render()
	{
		ImGui::SetNextWindowDockID(app::dockspace, ImGuiCond_Once);
		if (ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_NoFocusOnAppearing))
		{
			ImGui::Checkbox("Welcome Window", &welcome::state);
			ImGui::Checkbox("Credits Window", &credits::state);
#ifdef _DEBUG
			ImGui::Checkbox("Debug Window", &debug::state);
#endif
		}
		ImGui::End();
	}
}
