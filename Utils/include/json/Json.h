#pragma once

#include <iostream>

#include "json/JsonElement.h"
#include "json/JsonObject.h"

namespace r_utils
{
	namespace json
	{

		class Json
		{
		public:
			static r_utils::json::JsonElement parse(const std::string& input);

			static std::string stringify(const r_utils::json::JsonElement& element);

			static r_utils::json::JsonObject emptyObject();
		};
	}
}

