#pragma once

#include <vector>
#include <iostream>
#include <sstream>


namespace r_utils
{
	namespace json
	{
		class JsonElement;

		class JsonArray {
		public:
			JsonArray() = default;

			r_utils::json::JsonArray& add(const r_utils::json::JsonElement& element);
			r_utils::json::JsonArray& remove(const r_utils::json::JsonElement& element);
			const r_utils::json::JsonElement& get(int index) const;
			size_t size() const;
			bool empty() const;

			const std::vector<r_utils::json::JsonElement>& getValues() const;
			const std::string toString() const;

			const r_utils::json::JsonElement& operator[](int index) const;
		private:
			std::vector<r_utils::json::JsonElement> values;
		};

		std::ostream& operator<<(std::ostream& os, const r_utils::json::JsonArray& arr);
		bool operator==(const r_utils::json::JsonArray& x, const r_utils::json::JsonArray& y);
		bool operator!=(const r_utils::json::JsonArray& x, const r_utils::json::JsonArray& y);
	} // json
} // r_utils
