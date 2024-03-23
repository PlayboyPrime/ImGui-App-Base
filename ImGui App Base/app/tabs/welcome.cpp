#include "imgui.h"
#include "tabs.h"
#include "app/app.h"

namespace tabs::welcome
{
	void render()
	{
		if (!state)
			return;

		ImGui::SetNextWindowDockID(app::dockspace, ImGuiCond_Once);
		if (ImGui::Begin("Welcome", &state, ImGuiWindowFlags_NoFocusOnAppearing))
		{
			ImGui::Text("Hello!");
		}
		ImGui::End();
	}
}
