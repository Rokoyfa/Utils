#pragma once
#include <iostream>
#include <string>

namespace r_utils
{
	namespace logger
	{
		enum ErrorType
		{
			UNKNOWN_ERROR = 0,
			FILE_NOT_FOUND = 404,
			NETWORK_ERROR = 503,
			INVALID_INPUT = 1001,
			PERMISSION_DENIED = 1002,
			OUT_OF_MEMORY = 1003,
			TIMEOUT = 1004,
			UNSUPPORTED_OPERATION = 1005,
			DATABASE_ERROR = 1006,
			AUTHENTICATION_FAILED = 1007,
			AUTHORIZATION_FAILED = 1008,
			RESOURCE_CONFLICT = 1009,
			RESOURCE_LOCKED = 1010,
			DEPENDENCY_FAILURE = 1011,
			PARSE_ERROR = 1012,
			CONFIGURATION_ERROR = 1013,
			SERVICE_UNAVAILABLE = 1014,
			RATE_LIMIT_EXCEEDED = 1015,
			VERSION_MISMATCH = 1016,
			DISK_FULL = 1017,
			ILLEGAL_STATE = 1018
		};

		enum class LogLevel {
			LOG,
			INFO,
			DEBUG,
			WARN,
			ERR
		};

		class Logger
		{
		public:
			Logger();
			~Logger();

			void enableColors(bool enable);

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
			bool __enableColors__ = true;

			void output(const std::string& formattedMessage, LogLevel level) const;
			void output(const char* formattedMessage, LogLevel level) const;
		};
	} // logger
} // r_utils

