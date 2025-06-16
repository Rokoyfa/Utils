#pragma once
#include <iostream>
#include <string>

namespace r_utils
{
	namespace logger
	{
		enum ErrorType
		{
			UNKNOWN_ERROR = 0,				// An unspecified or generic error.
			FILE_NOT_FOUND = 404,			// Indicates that a required file could not be located.
			NETWORK_ERROR = 503,			// Denotes a problem with network communication.
			INVALID_INPUT = 1001,			// Signifies that provided input data is incorrect or malformed.
			PERMISSION_DENIED = 1002,		// Access to a resource or operation was denied due to insufficient permissions.
			OUT_OF_MEMORY = 1003,			// The system or application ran out of available memory.
			TIMEOUT = 1004,					// An operation did not complete within a specified time limit.
			UNSUPPORTED_OPERATION = 1005,	// The requested operation is not supported.
			DATABASE_ERROR = 1006,			// An error occurred during a database operation.
			AUTHENTICATION_FAILED = 1007,	// User authentication failed (e.g., incorrect credentials).
			AUTHORIZATION_FAILED = 1008,	// User is authenticated but not authorized to perform the action.
			RESOURCE_CONFLICT = 1009,		// A conflict occurred when trying to access or modify a resource.
			RESOURCE_LOCKED = 1010,			// A required resource is currently locked and cannot be accessed.
			DEPENDENCY_FAILURE = 1011,		// A required dependency (e.g., library, service) failed.
			PARSE_ERROR = 1012,				// An error occurred during parsing of data (e.g., configuration, message).
			CONFIGURATION_ERROR = 1013,		// An issue with the application's configuration.
			SERVICE_UNAVAILABLE = 1014,		// A required service is currently unavailable.
			RATE_LIMIT_EXCEEDED = 1015,		// The number of requests exceeded the allowed rate limit.
			VERSION_MISMATCH = 1016,		// Incompatible versions of components or data.
			DISK_FULL = 1017,				// The storage disk is full.
			ILLEGAL_STATE = 1018,			// An operation was attempted when the object or system was in an invalid state.

			RUNTIME_ERROR = 2000,           // A generic error that occurs during the execution of the program.
			STACK_OVERFLOW = 2001,          // The program's call stack exceeded its allocated size.
			BUFFER_OVERFLOW = 2002,         // An attempt was made to write data beyond the bounds of a buffer.
			OUT_OF_BOUNDS = 2003,           // An attempt was made to access an array, vector, or other data structure element outside its valid range.
			NULL_POINTER_DEREFERENCE = 2004,// An attempt was made to access memory through a null pointer.
			DIVIDE_BY_ZERO = 2005,          // An attempt was made to divide a number by zero.
			ARITHMETIC_OVERFLOW = 2006,     // An arithmetic operation resulted in a value too large to be represented.
			ARITHMETIC_UNDERFLOW = 2007,    // An arithmetic operation resulted in a value too small to be represented (loss of precision).
			DEADLOCK = 2008,                // A situation where two or more threads are blocked indefinitely, waiting for each other.
			RACE_CONDITION = 2009,          // The outcome of a program depends on the sequence or timing of uncontrollable events, leading to unpredictable results.
			CORRUPTED_DATA = 2010,          // Data has become unreadable or unusable due to a system or application error.
			INVALID_OPERATION = 2011,       // An operation was performed that is not valid in the current context or for the given data.
			RESOURCE_EXHAUSTION = 2012,     // A system resource (e.g., file handles, threads, memory) has been depleted.
			CONCURRENCY_ERROR = 2013,       // A general error related to concurrent execution, including race conditions and deadlocks.
			LOGIC_ERROR = 2014,             // An error due to incorrect program logic, often leading to unexpected behavior.
			ASSERTION_FAILED = 2015,        // An assertion in the code (e.g., `assert()`) failed, indicating a logical error.
			INVALID_HANDLE = 2016,          // An invalid or uninitialized handle was used to access a resource.
			UNSUPPORTED_ENCODING = 2017     // Data uses an encoding that is not supported by the system or application.
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

