#include "wnd_proc.h"

#include "render.h"
#include "app/app.h"
#include "helpers/d3d.h"

namespace core
{
	LRESULT WINAPI wnd_proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;

		switch (msg)
		{
		case WM_GETMINMAXINFO:
		{
			auto lpMMI = reinterpret_cast<LPMINMAXINFO>(lParam);
			lpMMI->ptMinTrackSize.x = static_cast<LONG>(app::min_window_size.x);
			lpMMI->ptMinTrackSize.y = static_cast<LONG>(app::min_window_size.y);
			lpMMI->ptMaxTrackSize.x = static_cast<LONG>(app::max_window_size.x);
			lpMMI->ptMaxTrackSize.y = static_cast<LONG>(app::max_window_size.y);

			return 0;
		}
		case WM_SIZE:
		{
			if (wParam == SIZE_MINIMIZED)
				return 0;

			g_d3dpp.BackBufferWidth = static_cast<UINT>(LOWORD(lParam));
			g_d3dpp.BackBufferHeight = static_cast<UINT>(HIWORD(lParam));
			helpers::d3d::ResetDevice();

			if (g_running)
				render();

			return 0;
		}
		case WM_SYSCOMMAND:
		{
			if ((wParam & 0xfff0) == SC_KEYMENU)
				return 0;

			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		}

		return DefWindowProcW(hWnd, msg, wParam, lParam);
	}
}
