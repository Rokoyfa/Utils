#pragma once

#include <iostream>

#include "json/JsonElement.h"
#include "json/JsonObject.h"
#include "json/JsonParser.h"
#include "file/File.h"

namespace r_utils
{
	namespace json
	{

		class Json
		{
		public:
			Json(r_utils::json::JsonObject obj);

			static r_utils::json::JsonElement parse(const std::string& input);
			static r_utils::json::JsonElement parse(const r_utils::io::File& file);

			static r_utils::json::JsonObject emptyObject();
			std::string toString();
		private:
			r_utils::json::JsonObject obj;
		};
	}
}

