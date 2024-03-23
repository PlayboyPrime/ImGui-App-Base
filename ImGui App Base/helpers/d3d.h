#pragma once

namespace helpers::d3d
{
	bool CreateDeviceD3D(bool vsync = true);
	void CleanupDeviceD3D();
	void ResetDevice();
}
