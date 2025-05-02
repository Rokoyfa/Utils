#include "json/JsonArray.h"

#include "json/JsonElement.h"


namespace r_utils {
	namespace json {

		r_utils::json::JsonArray JsonArray::add(const r_utils::json::JsonElement& element)
		{
			this->values.push_back(element);
			return *this;
		}

		r_utils::json::JsonArray JsonArray::remove(const r_utils::json::JsonElement& element)
		{
			auto it = std::remove(this->values.begin(), this->values.end(), element);

			this->values.erase(it, this->values.end());

			return *this;
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
	}
}
