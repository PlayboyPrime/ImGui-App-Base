#pragma once
#include <fstream>
#include <unordered_map>

#define RESET "\x1b[0m"
#define BLACK "\x1b[30m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"

#define BRIGHT_BLACK "\x1b[301m"
#define BRIGHT_RED "\x1b[311m"
#define BRIGHT_GREEN "\x1b[321m"
#define BRIGHT_YELLOW "\x1b[331m"
#define BRIGHT_BLUE "\x1b[341m"
#define BRIGHT_MAGENTA "\x1b[351m"
#define BRIGHT_CYAN "\x1b[361m"
#define BRIGHT_WHITE "\x1b[371m"


#ifdef _DEBUG
#define LOG(level, format, ...) g_logger->log(LogLevel::##level, format, __VA_ARGS__)
#else
#define LOG(level, format, ...)
#endif

#ifdef _DEBUG
namespace logger
{
	enum LogLevel : uint8_t
	{
		Info,
		Warning,
		Error,
		Fatal
	};

	static std::unordered_map<LogLevel, const char*> level_strings
	{
		{ Info,		CYAN "Info" RESET },
		{ Warning,	YELLOW "Warning" RESET },
		{ Error,	BRIGHT_RED "Error" RESET },
		{ Fatal,	RED "Fatal" RESET }
	};

	class Logger
	{
	public:
		explicit Logger(const char* name);
		~Logger();

		template <typename... Args>
		void log(LogLevel level, std::string format, Args... args)
		{
			auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			std::cout << "[" << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S") << " | " << level_strings[level] << "] " << std::vformat(format, std::make_format_args(args...)) << '\n' << std::flush;
		}
	};
}

using LogLevel = logger::LogLevel;

inline std::unique_ptr<logger::Logger> g_logger;
#endif 