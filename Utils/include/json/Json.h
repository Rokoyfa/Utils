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
            Json();
            explicit Json(JsonElement element);

            static Json parse(const std::string& input);
            static Json parse(const r_utils::io::File& file);

            [[nodiscard]] bool isObject() const;
            [[nodiscard]] bool isArray() const;
            JsonObject asObject() const;
            JsonArray asArray() const;

            std::string toString() const;

            static JsonObject emptyObject();
            static JsonArray emptyArray();

        private:
            JsonElement root;
        };
    }
}