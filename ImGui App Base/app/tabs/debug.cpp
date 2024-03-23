#ifdef _DEBUG
#include "imgui.h"
#include "tabs.h"
#include "app/app.h"

namespace tabs::debug
{
	void render()
	{
		if (about_window)				ImGui::ShowAboutWindow(&about_window);
		if (debug_log_window)			ImGui::ShowDebugLogWindow(&debug_log_window);
		if (demo_window)				ImGui::ShowDemoWindow(&demo_window);
		if (font_selector_window)		ImGui::ShowFontSelector("Font Selector");
		if (id_stacktool_window)		ImGui::ShowIDStackToolWindow(&id_stacktool_window);
		if (metrics_window)				ImGui::ShowMetricsWindow(&metrics_window);
		if (stacktool_window)			ImGui::ShowStackToolWindow(&stacktool_window);
		if (style_editor_windww)		ImGui::ShowStyleEditor();
		if (user_guide)					ImGui::ShowUserGuide();

		if (!state)
			return;

		ImGui::SetNextWindowDockID(app::dockspace, ImGuiCond_Once);
		if (ImGui::Begin("Debug", &state, ImGuiWindowFlags_NoFocusOnAppearing))
		{
			ImGui::Checkbox("About Window", &about_window);
			ImGui::Checkbox("Debug Log Window", &debug_log_window);
			ImGui::Checkbox("Demo Window", &demo_window);
			ImGui::Checkbox("Font Selector Window", &font_selector_window);
			ImGui::Checkbox("ID StackTool Window", &id_stacktool_window);
			ImGui::Checkbox("Metrics Window", &metrics_window);
			ImGui::Checkbox("StackTool Window", &stacktool_window);
			ImGui::Checkbox("Style Editor Window", &style_editor_windww);
			ImGui::Checkbox("User Guide", &user_guide);
		}
		ImGui::End();
	}
}
#endif