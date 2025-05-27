#include "json/JsonObject.h"
#include "json/JsonElement.h"
#include "json/Json.h"

#include "exception/json/JsonObjectException.h"

namespace r_utils 
{
    namespace json 
    {

        bool JsonObject::contains(const std::string& key) const 
        {
            return values.find(key) != values.end();
        }

        r_utils::json::JsonElement JsonObject::get(const std::string& key) const 
        {
            auto it = values.find(key);
            if (it != values.end()) {
                return it->second;
            }

            throw r_utils::exception::JsonObjectException("Key not found: " + key);;
        }

        r_utils::json::JsonElement JsonObject::get(const int index) const
        {
            if (index >= this->size()) {
                throw r_utils::exception::JsonObjectException(std::out_of_range("Index out of bounds"));
            }
            auto it = values.begin();
            std::advance(it, index);
            return it->second;
        }

        r_utils::json::JsonObject& JsonObject::set(const std::string& key, const JsonElement& value) 
        {
            if (key.empty())
            {
                throw r_utils::exception::JsonObjectException("Key value cannot be empty!");
            }

            values[key] = value;
            return *this;
        }

        void JsonObject::remove(const std::string& key)
        {
            values.erase(key);
        }

        const std::unordered_map<std::string, r_utils::json::JsonElement>& JsonObject::getValues() const
        {
            return values;
        }


        size_t JsonObject::size() const
        {
            return values.size();
        }

        std::string JsonObject::indent(int level)
        {
            return std::string(level, '\t');
        }


        std::string JsonObject::toString(bool prettyPrint, int indentLevel) const
        {
            std::stringstream result;

            result << "{";
            if (prettyPrint && !values.empty())
            {
                result << "\n";
            }

            size_t counter = 0;
            for (const auto [key, value] : values)
            {
                if (prettyPrint)
                {
                    result << indent(indentLevel + 1);
                }

                result << "\"" << key << "\":";
                if (prettyPrint)
                {
                    result << " ";
                }

                auto it = value.getType();

                switch (it)
                {
                case r_utils::json::JsonType::Null:
                    result << "null"; break;
                case r_utils::json::JsonType::String:
                    result << "\"" << value.asString() << "\""; break;
                case r_utils::json::JsonType::Int:
                    result << value.asInt(); break;
                case r_utils::json::JsonType::Double:
                    result << value.asDouble(); break;
                case r_utils::json::JsonType::Boolean:
                    result << (value.asBoolean() ? "true" : "false"); break;
                case r_utils::json::JsonType::Array:
                    result << value.asArray().toString(); break;
                case r_utils::json::JsonType::Object:
                    result << value.asObject().toString(prettyPrint, indentLevel + 1); break;
                default:
                    break;
                }


                counter++;

                if (counter < this->size())
                {
                    result << ",";
                }

                if (prettyPrint)
                {
                    result << "\n";
                }
            }

            if (prettyPrint && !values.empty())
            {
                result << indent(indentLevel);
            }

            result << "}";

            return result.str();
        }

        r_utils::json::Json JsonObject::toJson() const 
        {
            return r_utils::json::Json(*this);
        }



        std::ostream& operator<<(std::ostream& os, const r_utils::json::JsonObject& obj)
        {
            os << obj.toString();
            return os;
        }

        bool operator==(const r_utils::json::JsonObject& x, const r_utils::json::JsonObject& y)
        {   
            return (x.getValues() == y.getValues());
        }

        bool operator!=(const r_utils::json::JsonObject& x, const r_utils::json::JsonObject& y)
        {
            return !(x == y);
        }

    } // json
} // r_utils
