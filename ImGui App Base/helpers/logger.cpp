#if _DEBUG
#include "logger.h"

namespace logger
{
	Logger::Logger(const char* name)
	{
		AllocConsole();
		SetConsoleTitleA(name);
		(void)freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD mode;
		GetConsoleMode(hConsole, &mode);
		SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

		SetConsoleCtrlHandler([](DWORD fdw_ctrl_type) -> BOOL { return fdw_ctrl_type == CTRL_C_EVENT; }, TRUE); // Disable CTRL + C closing the application
	}

	Logger::~Logger()
	{
		FreeConsole();
	}
}
#endif