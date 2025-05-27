#pragma once

#include <iostream>
#include <unordered_map>
#include <sstream>

namespace r_utils {
    namespace json {

        class JsonElement;

        class Json;


        class JsonObject {
        public:
            JsonObject() = default;

            bool contains(const std::string& key) const;
            r_utils::json::JsonElement get(const std::string& key) const;
            r_utils::json::JsonElement get(const int index) const;
            r_utils::json::JsonObject& set(const std::string& key, const r_utils::json::JsonElement& value);
            [[noreturn]] void remove(const std::string& key);
            const std::unordered_map<std::string, r_utils::json::JsonElement>& getValues() const;

            size_t size() const;

            std::string toString(bool prettyPrint = false, int indentLevel = 0) const;
            r_utils::json::Json toJson() const;

        private:
            std::unordered_map<std::string, r_utils::json::JsonElement> values;

            static std::string indent(int level);
        };

        std::ostream& operator<<(std::ostream& os, const r_utils::json::JsonObject& obj);
        bool operator==(const r_utils::json::JsonObject& x, const r_utils::json::JsonObject& y);
        bool operator!=(const r_utils::json::JsonObject& x, const r_utils::json::JsonObject& y);
    } // json
} // r_utils
