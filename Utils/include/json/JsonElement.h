#pragma once

#include <iostream>
#include <variant>

#include "json/JsonObject.h"
#include "json/JsonArray.h"

namespace r_utils {
    namespace json {

        enum class JsonType {
            Null,
            String,
            Int,
            Double,
            Boolean,
            Array,
            Object
        };

        std::ostream& operator<<(std::ostream& os, const JsonType& type);

        bool operator==(const r_utils::json::JsonElement& x, const r_utils::json::JsonElement& y);
        bool operator!=(const r_utils::json::JsonElement& x, const r_utils::json::JsonElement& y);

        class JsonElement
        {
        public:
            JsonElement();
            JsonElement(const std::string& value);
            JsonElement(int value);
            JsonElement(double value);
            JsonElement(bool value);
            JsonElement(const r_utils::json::JsonArray& value);
            JsonElement(const r_utils::json::JsonObject& value);

            JsonType getType() const;
            std::string stringify() const;
            std::variant<std::monostate, std::string, int, double, bool, r_utils::json::JsonObject, r_utils::json::JsonArray> getValue() const;

            bool isNull() const;
            bool isString() const;
            bool isInt() const;
            bool isDouble() const;
            bool isBoolean() const;
            bool isArray() const;
            bool isObject() const;

            std::string asString() const;
            int asInt() const;
            double asDouble() const;
            bool asBoolean() const;
            r_utils::json::JsonArray asArray() const;
            r_utils::json::JsonObject asObject() const;

        private:
            JsonType type;
            std::variant<std::monostate, std::string, int, double, bool, r_utils::json::JsonObject, r_utils::json::JsonArray> value;
        };

    }
}