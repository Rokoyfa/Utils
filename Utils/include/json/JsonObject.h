#pragma once

#include <iostream>
#include <unordered_map>

#include "Json.h"

namespace r_utils {
    namespace json {

        class JsonObject {
        public:
            JsonObject() = default;

            bool contains(const std::string& key) const;
            Json get(const std::string& key) const;
            r_utils::json::Json get(const int index) const;
            r_utils::json::JsonObject set(const std::string& key, const r_utils::json::Json& value);

            size_t size() const;

        private:
            std::unordered_map<std::string, Json> values;
        };

    }
}
