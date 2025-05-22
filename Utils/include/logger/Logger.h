#pragma once
#include <iostream>

namespace r_utils
{
	namespace logger
	{
		enum ErrorType
		{
			UNKNOWN_ERROR = 0,
			FILE_NOT_FOUND = 404,
			NETWORK_ERROR = 503,
			INVALID_INPUT = 1001
		};

		class Logger
		{
		public:
			Logger(bool withGUI = true);

			void log(const std::string& msg) const;
			void log(const char* msg) const;

			void info(const std::string& msg) const;
			void info(const char* msg) const;

			void debug(const std::string& msg) const;
			void debug(const char* msg) const;

			void warn(const std::string& msg) const;
			void warn(const char* msg) const;

			void error(const std::string& msg, ErrorType type = ErrorType::UNKNOWN_ERROR);
			void error(const char* msg, ErrorType type = ErrorType::UNKNOWN_ERROR);

		private:
			bool __useGUI__;

			void output(const std::string& formattedMessage) const;
			void output(const char* formattedMessage) const;
		};
	}
}

