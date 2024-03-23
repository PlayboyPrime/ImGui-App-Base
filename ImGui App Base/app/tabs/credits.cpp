#include "imgui.h"
#include "tabs.h"
#include "app/app.h"

namespace tabs::credits
{
	void render()
	{
		if (!state)
			return;

		ImGui::SetNextWindowDockID(app::dockspace, ImGuiCond_Once);
		if (ImGui::Begin("Credits", &state, ImGuiWindowFlags_NoFocusOnAppearing))
		{
			// https://github.com/ocornut/imgui
			ImGui::Text("This project uses ImGui v" IMGUI_VERSION " by Ocornut");
			if (ImGui::Button("ImGui"))
			{
				ShellExecute(nullptr, nullptr, "https://github.com/ocornut/imgui", nullptr, nullptr, SW_SHOW);
			}
			ImGui::Separator();

			// https://github.com/PlayboyPrime/ImGui-App-Base
			ImGui::Text("ImGui App Base made by PlayboyPrime");
			if (ImGui::Button("ImGui App Base"))
			{
				ShellExecute(nullptr, nullptr, "https://github.com/PlayboyPrime/ImGui-App-Base", nullptr, nullptr, SW_SHOW);
			}
			ImGui::Separator();
		}
		ImGui::End();
	}
}
