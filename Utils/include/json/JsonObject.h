#pragma once

#include <iostream>
#include <unordered_map>
#include <sstream>

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
            void remove(const std::string& key);

            size_t size() const;

            std::string toString(bool prettyPrint = false, int indentLevel = 0) const;
            r_utils::json::Json toJson() const;

        private:
            std::unordered_map<std::string, Json> values;

            static std::string indent(int level);
        };

    }
}
