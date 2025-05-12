#include "logger/Logger.h"
#include <iostream>
#include <ctime>
#include <string>

namespace r_utils
{
	namespace logger
	{
		Logger::Logger(bool withGUI)
			: __useGUI__(withGUI) {}


		void Logger::log(const std::string& msg) const
		{
		}

		void Logger::log(const char* msg) const
		{
		}


		void Logger::info(const std::string& msg) const
		{
		}

		void Logger::info(const char* msg) const
		{
		}


		void Logger::debug(const std::string& msg) const
		{
		}
			
		void Logger::debug(const char* msg) const
		{
		}


		void Logger::error(const std::string& msg, ErrorType type)
		{
		}

		void Logger::error(const char* msg, ErrorType type)
		{
		}


		void Logger::output(const std::string& msg) const
		{
			std::time_t now;
			std::time(&now);
			std::string timestamp = std::ctime(&now);

			if (!timestamp.empty() && timestamp.back() == '\n') 
			{
				timestamp.pop_back();
			}
			if (__useGUI__) 
			{
				std::cout << "[GUI] [" << timestamp << "] " << msg << std::endl;
			}
			else 
			{
				std::cout << "[" << timestamp << "] " << msg << std::endl;
			}
		}

		void Logger::output(const char* msg) const
		{
			output(std::string(msg));
		}
	}
}
