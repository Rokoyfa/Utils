#pragma once

#include <exception>
#include <iostream>

namespace r_utils
{
	namespace exception
	{

		class Exception : public std::exception
		{
		public:
			Exception(std::string typeName, const std::string& message) noexcept : _message("[" + typeName + "] " + message) {};
			Exception(std::string typeName, const char* message) : _message("[" + typeName + "] " + std::string(message)) {};
			Exception(std::string typeName, const std::string_view& message) : _message("[" + typeName + "] " + std::string(message)) {};
			Exception(std::string typeName, const std::exception& exception) : _message("[" + typeName + "] " + exception.what()) {};

			[[nodiscard]] virtual const char* what() const noexcept override
			{
				return this->_message.c_str();
			}
		protected:
			std::string _message;
		};
	}
}

