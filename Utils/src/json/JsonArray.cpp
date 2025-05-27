#include "json/JsonArray.h"
#include "json/JsonElement.h"

#include "exception/json/JsonArrayException.h"


namespace r_utils {
	namespace json {

		r_utils::json::JsonArray& JsonArray::add(const r_utils::json::JsonElement& element)
		{
			this->values.push_back(element);
			return *this;
		}

		r_utils::json::JsonArray& JsonArray::remove(const r_utils::json::JsonElement& element)
		{
			auto size = values.size();

			auto it = std::remove(values.begin(), values.end(), element);
			values.erase(it, values.end());

			if (values.size() == size)
			{
				throw r_utils::exception::JsonArrayException("Element not found in array");
			}

			return *this;
		}

		const r_utils::json::JsonElement& JsonArray::get(int index) const
		{
			if (index < 0 || index >= static_cast<int>(values.size()))
			{
				throw r_utils::exception::JsonArrayException("Index out of bounds: " + std::to_string(index));
			}
			return values.at(index);
		}

		size_t JsonArray::size() const
		{
			return this->values.size();
		}

		bool JsonArray::empty() const
		{
			return this->size() == 0;
		}

		const std::vector<r_utils::json::JsonElement>& JsonArray::getValues() const
		{
			return this->values;
		}

		const std::string JsonArray::toString() const
		{
			std::stringstream ss;

			ss << "[";

			size_t counter = 0;
			for (auto& it : this->getValues())
			{
				switch (it.getType())
				{
					case JsonType::String: ss << "\"" << it.asString() << "\""; break;
					case JsonType::Int: ss << it.asInt(); break;
					case JsonType::Double: ss << it.asDouble(); break;
					case JsonType::Boolean: ss << (it.asBoolean() ? "true" : "false"); break;
					case JsonType::Array: ss << it.asArray().toString(); break;
					case JsonType::Object: ss << it.asObject().toString(); break;
					case JsonType::Null: ss << "null"; break;
				}

				counter++;

				if (counter < this->size())
				{
					ss << ",";
				}
			}

			ss << "]";
			return ss.str();
		}

		const r_utils::json::JsonElement& JsonArray::operator[](int index) const
		{
			return this->get(index);
		}


		std::ostream& operator<<(std::ostream& os, const r_utils::json::JsonArray& arr)
		{
			os << arr.toString();
			return os;
		}

		bool operator==(const r_utils::json::JsonArray& x, const r_utils::json::JsonArray& y)
		{
			return (x.getValues() == y.getValues());
		}

		bool operator!=(const r_utils::json::JsonArray& x, const r_utils::json::JsonArray& y)
		{
			return !(x == y);
		}
	} // json
} // r_utils
