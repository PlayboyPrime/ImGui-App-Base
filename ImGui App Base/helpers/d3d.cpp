#include "helpers/d3d.h"

#include <d3d9.h>

#include "imgui_impl_dx9.h"
#include "logger.h"

namespace helpers::d3d
{
	bool CreateDeviceD3D(bool vsync)
	{
		if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr)
			return false;

		ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
		g_d3dpp.Windowed = TRUE;
		g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		g_d3dpp.EnableAutoDepthStencil = TRUE;
		g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		g_d3dpp.PresentationInterval = vsync ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;
		return g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) >= 0;
	}

	void CleanupDeviceD3D()
	{
		if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
		if (g_pD3D) { g_pD3D->Release(); g_pD3D = nullptr; }
	}

	void ResetDevice()
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		if (g_pd3dDevice->Reset(&g_d3dpp) == D3DERR_INVALIDCALL)
			LOG(Warning, "ResetDevice(): D3DERR_INVALIDCALL"); //IM_ASSERT(0);

		ImGui_ImplDX9_CreateDeviceObjects();
	}
}
