#include "render.h"

#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "app/app.h"
#include "helpers/d3d.h"

namespace core
{
	void render()
	{
		// Start the ImGui frame
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// App Rendering
		app::render();

		// Rendering
		ImGui::EndFrame();
		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
		D3DCOLOR clear_col_dx = D3DCOLOR_RGBA(
			static_cast<int>(app::background_color.x * app::background_color.w / 255.f),
			static_cast<int>(app::background_color.y * app::background_color.w / 255.f),
			static_cast<int>(app::background_color.z * app::background_color.w / 255.f),
			static_cast<int>(app::background_color.w)
		);
		g_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
		if (g_pd3dDevice->BeginScene() >= 0)
		{
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			g_pd3dDevice->EndScene();
		}
		
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();

		// Handle loss of D3D9 device
		if (HRESULT result = g_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr); result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
			helpers::d3d::ResetDevice();
	}
}
