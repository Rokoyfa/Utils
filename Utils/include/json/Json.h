#pragma once

#include <iostream>
#include <variant>
#include "JsonObject.h"

namespace r_utils {
    namespace json {

        enum class JsonType {
            Null,
            String,
            Int,
            Double,
            Boolean,
            Object
        };

        class Json
        {
        public:
            Json();
            Json(const std::string& value);
            Json(int value);
            Json(double value);
            Json(bool value);
            Json(const JsonObject& value);

            JsonType getType() const;

            bool isString() const;
            bool isInt() const;
            bool isDouble() const;
            bool isBoolean() const;
            bool isObject() const;

            std::string asString() const;
            int asInt() const;
            double asDouble() const;
            bool asBool() const;
            JsonObject asObject() const;

        private:
            JsonType type;
            std::variant<std::monostate, std::string, int, double, bool, JsonObject> value;
        };

    }
}