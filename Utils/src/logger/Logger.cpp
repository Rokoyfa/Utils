#include "logger/Logger.h"
#include <iostream>
#include <ctime>
#include <string>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
void enableAnsiColorsForConsole() 
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);
}
#endif

namespace r_utils
{
	namespace logger
	{
		Logger::Logger() 
		{}

		Logger::~Logger()
		{}

		void Logger::enableColors(bool enable)
		{
			__enableColors__ = enable;

			#ifdef _WIN32
            if (enable) {
                enableAnsiColorsForConsole();
            }
            #endif
		}


		void Logger::log(const std::string& msg) const 
		{
			std::stringstream ss;
			ss << "[LOG] " << msg;
			output(ss.str(), LogLevel::LOG);
		}
		void Logger::log(const char* msg) const { log(std::string(msg)); }

		void Logger::info(const std::string& msg) const 
		{
			std::stringstream ss;
			ss << "[INFO] " << msg;
			output(ss.str(), LogLevel::INFO);
		}
		void Logger::info(const char* msg) const { info(std::string(msg)); }

		void Logger::debug(const std::string& msg) const 
		{
			std::stringstream ss;
			ss << "[DEBUG] " << msg;
			output(ss.str(), LogLevel::DEBUG);
		}
		void Logger::debug(const char* msg) const { debug(std::string(msg)); }

		void Logger::warn(const std::string& msg) const 
		{
			std::stringstream ss;
			ss << "[WARN] " << msg;
			output(ss.str(), LogLevel::WARN);
		}
		void Logger::warn(const char* msg) const { warn(std::string(msg)); }

		void Logger::error(const std::string& msg, ErrorType type) {
			std::stringstream ss;
			ss << "[ERROR " << std::to_string(type) << "] " << msg;
			output(ss.str(), LogLevel::ERR);
		}
		void Logger::error(const char* msg, ErrorType type) { error(std::string(msg), type); }


		std::string getCurrentTimestamp() 
		{
			std::time_t now = std::time(nullptr);
			std::tm tm_buf;
#ifdef _WIN32
			localtime_s(&tm_buf, &now);
#else
			localtime_r(&now, &tm_buf);
#endif

			std::ostringstream oss;
			oss << std::put_time(&tm_buf, "%Y-%m-%d %H:%M:%S");
			return oss.str();
		}

		void Logger::output(const std::string& msg, LogLevel level) const
		{
			std::string timestamp = getCurrentTimestamp();
			std::string colorCode = "";
			std::string resetCode = "\x1b[0m";

			if (__enableColors__) 
			{
				switch (level) 
				{
				case LogLevel::LOG:
					colorCode = "\x1b[37m";
					break;
				case LogLevel::INFO:
					colorCode = "\x1b[34m";
					break;
				case LogLevel::DEBUG:
					colorCode = "\x1b[35m";
					break;
				case LogLevel::WARN:
					colorCode = "\x1b[33m";
					break;
				case LogLevel::ERR:
					colorCode = "\x1b[31m";
					break;
				default:
					break;
				}
			}

			std::stringstream output;
			output << colorCode << "[" << timestamp << "] " << msg << resetCode;

			std::cout << output.str() << std::endl;
		}

		void Logger::output(const char* msg, LogLevel level) const
		{
			output(std::string(msg), level);
		}
	} // logger
} // r_utils
