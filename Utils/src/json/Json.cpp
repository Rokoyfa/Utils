#include "json/Json.h"
#include "json/JsonObject.h"

namespace r_utils {
    namespace json {

        Json::Json()
            : type(JsonType::Null), value(std::monostate{}) {}

        Json::Json(const std::string& value)
            : type(JsonType::String), value(value) {}

        Json::Json(int value)
            : type(JsonType::Int), value(value) {}

        Json::Json(double value)
            : type(JsonType::Double), value(value) {}

        Json::Json(bool value)
            : type(JsonType::Boolean), value(value) {}

        Json::Json(const r_utils::json::JsonObject& value)
            : type(JsonType::Object), value(value) {}


        JsonType Json::getType() const {
            return type;
        }


        bool Json::isString() const {
            return type == JsonType::String;
        }

        bool Json::isInt() const {
            return type == JsonType::Int;
        }

        bool Json::isDouble() const {
            return type == JsonType::Double;
        }

        bool Json::isBoolean() const {
            return type == JsonType::Boolean;
        }

        bool Json::isObject() const {
            return type == JsonType::Object;
        }


        std::string Json::asString() const {
            if (type == JsonType::String) {
                return std::get<std::string>(value);
            }
            throw std::runtime_error("Json is not a String");
        }


        int Json::asInt() const {
            if (type == JsonType::Int) {
                return std::get<int>(value);
            }
            throw std::runtime_error("Json is not an Int");
        }

        double Json::asDouble() const {
            if (type == JsonType::Double) {
                return std::get<double>(value);
            }
            throw std::runtime_error("Json is not a Double");
        }

        bool Json::asBoolean() const {
            if (type == JsonType::Boolean) {
                return std::get<bool>(value);
            }
            throw std::runtime_error("Json is not a Boolean");
        }

        r_utils::json::JsonObject Json::asObject() const {
            if (type == JsonType::Object) {
                return std::get<JsonObject>(value);
            }
            throw std::runtime_error("Json is not an Object");
        }

        r_utils::json::JsonObject Json::empty() const
        {
            return r_utils::json::JsonObject();
        }

        std::ostream& operator<<(std::ostream& os, const JsonType& type)
        {
            switch (type)
            {
            case JsonType::Null:    os << "Null"; break;
            case JsonType::String:  os << "String"; break;
            case JsonType::Int:     os << "Integer"; break;
            case JsonType::Double:  os << "Double"; break;
            case JsonType::Boolean: os << "Boolean"; break;
            case JsonType::Object:  os << "Object"; break;
            default: os << "Unknown JsonType!"; break;
            }

            return os;
        }

    }
}
