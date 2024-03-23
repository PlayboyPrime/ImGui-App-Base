#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>

#include "fonts.h"
#include "app/app.h"
#include "core/render.h"
#include "core/wnd_proc.h"
#include "helpers/d3d.h"
#include "helpers/logger.h"
#include "resource/resource.h"

#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0 // From Windows SDK 8.1+ headers
#endif


// Entry Point
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
{
#ifdef _DEBUG
	g_logger = std::make_unique<logger::Logger>(APP_NAME_VERSION);
	LOG(Info, "Starting application...");
#endif

	ImGui_ImplWin32_EnableDpiAwareness();
	WNDCLASSEXW wc = {
		sizeof(wc),
		CS_CLASSDC,
		core::wnd_proc,
		0L,
		0L,
		hInstance,
		LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)),
		nullptr,
		nullptr,
		nullptr,
		L"" APP_NAME,
		LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1))
	};
	RegisterClassExW(&wc);

	g_hWnd = CreateWindowEx(
		0,
		APP_NAME,
		APP_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		static_cast<int>(app::window_size.x), static_cast<int>(app::window_size.y),
		nullptr, nullptr,
		wc.hInstance, nullptr
	);

	if (!helpers::d3d::CreateDeviceD3D())
	{
		LOG(Fatal, "Failed to create Direct3D device");
		helpers::d3d::CleanupDeviceD3D();
		DestroyWindow(g_hWnd);
		UnregisterClassW(wc.lpszClassName, wc.hInstance);
		MessageBoxW(nullptr, L"Failed to create Direct3D device", L"" APP_NAME_VERSION, MB_OK | MB_ICONERROR);
		return EXIT_FAILURE;
	}

	ShowWindow(g_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(g_hWnd);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.IniFilename = nullptr;

	ImGuiStyle& style = ImGui::GetStyle();
	style.ScaleAllSizes(1.3f);
	ImGui::StyleColorsDark(&style);
	style.WindowRounding = 0.0f;
	style.Colors[ImGuiCol_WindowBg].w = 1.0f;

	// Setup Platform and Renderer Backends
	ImGui_ImplWin32_Init(g_hWnd);
	ImGui_ImplDX9_Init(g_pd3dDevice);
	g_running = true;

	// Setup Fonts
	io.Fonts->AddFontDefault();
	io.Fonts->AddFontFromMemoryCompressedBase85TTF(impact_compressed_data_base85, 17.f);

	// Main loop
	while (g_running)
	{
		MSG msg;
		while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				g_running = false;
				break;
			}
		}

		if (!g_running)
			break;

		core::render();
	}

	// Cleanup
	LOG(Info, "Shutting down application...");
#ifdef _DEBUG
	g_logger.reset();
#endif
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	helpers::d3d::CleanupDeviceD3D();
	DestroyWindow(g_hWnd);
	UnregisterClassW(wc.lpszClassName, wc.hInstance);

	// Exit
	return EXIT_SUCCESS;
}