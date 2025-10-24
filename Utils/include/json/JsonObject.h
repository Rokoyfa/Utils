#pragma once

#include <iostream>
#include <unordered_map>
#include <sstream>

namespace r_utils {
    namespace json {

        class JsonElement;
        class Json;

        /**
         * @class JsonObject
         * @brief Represents a JSON object, which stores key-value pairs of JSON elements.
         *
         * JsonObject is a container for named JSON elements. It provides methods to
         * query, insert, update, and remove elements, as well as to convert the object
         * into a string representation or into a Json wrapper object.
         */
        class JsonObject {
        public:
            /** Default constructor. Creates an empty JSON object. */
            JsonObject() = default;

            /**
             * @brief Checks if the object contains a key.
             * @param key Key to search for.
             * @return True if the key exists, false otherwise.
             */
            bool contains(const std::string& key) const;

            /**
             * @brief Retrieves a JSON element by key.
             * @param key Key of the element.
             * @return JsonElement associated with the key.
             * @throws Exception if the key does not exist.
             */
            r_utils::json::JsonElement get(const std::string& key) const;

            /**
             * @brief Retrieves a JSON element by index (order is undefined).
             * @param index Zero-based index.
             * @return JsonElement at the given index.
             * @throws Exception if the index is out of range.
             */
            r_utils::json::JsonElement get(const int index) const;

            /**
             * @brief Inserts or updates a key-value pair in the object.
             * @param key Key to insert or update.
             * @param value JSON element to associate with the key.
             * @return Reference to this JsonObject for chaining.
             */
            r_utils::json::JsonObject& set(const std::string& key, const r_utils::json::JsonElement& value);

            /**
             * @brief Removes a key-value pair by key.
             * @param key Key to remove.
             * @throws Exception if the key does not exist.
             */
            [[noreturn]] void remove(const std::string& key);

            /**
             * @brief Returns a const reference to the internal key-value map.
             * @return Internal unordered_map of JSON elements.
             */
            const std::unordered_map<std::string, r_utils::json::JsonElement>& getValues() const;

            size_t size() const;
            std::string toString(bool prettyPrint = false, int indentLevel = 0) const;

            /**
             * @brief Converts the JsonObject into a Json wrapper object.
             * @return Json wrapper containing this object.
             */
            r_utils::json::Json toJson() const;

        private:
            std::unordered_map<std::string, r_utils::json::JsonElement> values;

            /**
             * @brief Returns indentation spaces for pretty-printing.
             * @param level Indentation level.
             * @return String of spaces corresponding to the level.
             */
            static std::string indent(int level);
        };

        std::ostream& operator<<(std::ostream& os, const r_utils::json::JsonObject& obj);
        bool operator==(const r_utils::json::JsonObject& x, const r_utils::json::JsonObject& y);
        bool operator!=(const r_utils::json::JsonObject& x, const r_utils::json::JsonObject& y);

    } // json
} // r_utils
