#include "json/JsonElement.h"
#include "json/JsonObject.h"

#include "exception/json/JsonElementException.h"

namespace r_utils {
    namespace json {

        JsonElement::JsonElement()
            : type(JsonType::Null), value(std::monostate{}) {}

        JsonElement::JsonElement(const std::string& value)
            : type(JsonType::String), value(value) {}

        JsonElement::JsonElement(const char* value)
            : type(JsonType::String), value(std::string(value)) {}

        JsonElement::JsonElement(int value)
            : type(JsonType::Int), value(value) {}

        JsonElement::JsonElement(double value)
            : type(JsonType::Double), value(value) {}

        JsonElement::JsonElement(bool value)
            : type(JsonType::Boolean), value(value) {}

        JsonElement::JsonElement(const r_utils::json::JsonArray& value)
            : type(JsonType::Array), value(value) {}

        JsonElement::JsonElement(const r_utils::json::JsonObject& value)
            : type(JsonType::Object), value(value) {}


        JsonType JsonElement::getType() const {
            return type;
        }

        std::string JsonElement::stringify() const {
            switch (type) {
            case JsonType::Null:
                return "null";
            case JsonType::String:
                return "\"" + std::get<std::string>(value) + "\"";
            case JsonType::Int:
                return std::to_string(std::get<int>(value));
            case JsonType::Double:
                return std::to_string(std::get<double>(value));
            case JsonType::Boolean:
                return std::get<bool>(value) ? "true" : "false";
            case JsonType::Array:
                return std::get<JsonArray>(value).toString();
            case JsonType::Object:
                return std::get<JsonObject>(value).toString();
            default:
                return "null";
            }
        }

        std::variant <std::monostate, std::string, int, double, bool, r_utils::json::JsonObject, r_utils::json::JsonArray> JsonElement::getValue() const
        {
            return this->value;
        }

        bool JsonElement::isNull() const {
            return type == JsonType::Null;
        }


        bool JsonElement::isString() const {
            return type == JsonType::String;
        }

        bool JsonElement::isInt() const {
            return type == JsonType::Int;
        }

        bool JsonElement::isDouble() const {
            return type == JsonType::Double;
        }

        bool JsonElement::isBoolean() const {
            return type == JsonType::Boolean;
        }

        bool JsonElement::isArray() const
        {
            return type == JsonType::Array;
        }

        bool JsonElement::isObject() const {
            return type == JsonType::Object;
        }


        std::string JsonElement::asString() const {
            if (type == JsonType::String) {
                return std::get<std::string>(value);
            }
            throw r_utils::exception::JsonElementException("Json is not a String");
        }


        int JsonElement::asInt() const {
            if (type == JsonType::Int) {
                return std::get<int>(value);
            }
            throw r_utils::exception::JsonElementException("Json is not an Int");
        }

        double JsonElement::asDouble() const {
            if (type == JsonType::Double) {
                return std::get<double>(value);
            }
            throw r_utils::exception::JsonElementException("Json is not a Double");
        }

        bool JsonElement::asBoolean() const {
            if (type == JsonType::Boolean) {
                return std::get<bool>(value);
            }
            throw r_utils::exception::JsonElementException("Json is not a Boolean");
        }

        r_utils::json::JsonArray JsonElement::asArray() const
        {
            if (type == JsonType::Array) {
                return std::get<JsonArray>(value);
            }
            throw r_utils::exception::JsonElementException("Json is not an Array");
        }

        r_utils::json::JsonObject JsonElement::asObject() const {
            if (type == JsonType::Object) {
                return std::get<JsonObject>(value);
            }
            throw r_utils::exception::JsonElementException("Json is not an Object");
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
            case JsonType::Array:   os << "Array"; break;
            case JsonType::Object:  os << "Object"; break;
            default: os << "Unknown JsonType!"; break;
            }

            return os;
        }

        bool operator==(const r_utils::json::JsonElement& x, const r_utils::json::JsonElement& y)
        {
            return (x.getType() == y.getType()) && (x.getValue() == y.getValue());
        }

        bool operator!=(const r_utils::json::JsonElement& x, const r_utils::json::JsonElement& y)
        {
            return !(x == y);
        }

    }
}
