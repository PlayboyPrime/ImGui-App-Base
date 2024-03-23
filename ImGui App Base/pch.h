#pragma once

#include <windows.h>
#include <consoleapi.h>
#include <d3d9.h>
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;
using namespace std::chrono_literals;

#define APP_NAME "ImGui App Base"
#define APP_VERSION "1.0.0"
#define APP_NAME_VERSION APP_NAME " v" APP_VERSION

inline bool						g_running			= false;
inline HWND						g_hWnd				= nullptr;
inline LPDIRECT3D9              g_pD3D				= nullptr;
inline LPDIRECT3DDEVICE9        g_pd3dDevice		= nullptr;
inline D3DPRESENT_PARAMETERS    g_d3dpp				= {};
