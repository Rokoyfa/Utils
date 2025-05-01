#pragma once

#include <iostream>

#include "json/JsonObject.h"
#include "json/JsonElement.h"
#include "json/JsonArray.h"
#include "file/File.h"

namespace r_utils 
{
	namespace json 
	{
		class JsonParser
		{
		public:
			JsonParser() = default;

			static JsonObject parse(std::string input);
			static JsonObject parse(const r_utils::io::File file);

		private:
			explicit JsonParser(std::string input);

			char peek() const;
			char next();
			bool eof() const;
			void skipWhitespace();

			JsonElement parseValue();
			JsonElement parseNull();
			JsonElement parseBool();
			JsonElement parseNumber();
			JsonElement parseString();
			JsonArray parseArray();
			JsonObject  parseObject();

			std::string input;
			size_t pos;
		};
	}
}
