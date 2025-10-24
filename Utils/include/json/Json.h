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

        /**
         * @class Json
         * @brief Main entry point for JSON parsing and manipulation.
         *
         * This class represents a JSON value, which can be either an object, an array, or a single element.
         * It provides parsing functionality from strings or files, type checking, and conversion to
         * JsonObject or JsonArray.
         */
        class Json
        {
        public:
            /**
             * @brief Default constructor. Creates an empty JSON element.
             */
            Json();

            /**
             * @brief Constructs a Json instance from an existing JsonElement.
             * @param element The root JsonElement to wrap.
             */
            explicit Json(JsonElement element);

            /**
             * @brief Parses a JSON-formatted string into a Json instance.
             * @param input The input string containing JSON data.
             * @return A Json object representing the parsed data.
             * @throws r_utils::exception::JsonParserException on parse errors.
             */
            static Json parse(const std::string& input);

            /**
             * @brief Parses JSON content from a file into a Json instance.
             * @param file The File object to read the JSON content from.
             * @return A Json object representing the parsed data.
             * @throws r_utils::exception::JsonParserException on parse errors.
             */
            static Json parse(const r_utils::io::File& file);

            /**
             * @brief Checks whether the root element is a JSON object.
             * @return True if the root element is an object, false otherwise.
             */
            [[nodiscard]] bool isObject() const;

            /**
             * @brief Checks whether the root element is a JSON array.
             * @return True if the root element is an array, false otherwise.
             */
            [[nodiscard]] bool isArray() const;

            /**
             * @brief Converts the root element to a JsonObject.
             * @return The root element as a JsonObject.
             * @throws r_utils::exception::JsonElementException if the root is not an object.
             */
            JsonObject asObject() const;

            /**
             * @brief Converts the root element to a JsonArray.
             * @return The root element as a JsonArray.
             * @throws r_utils::exception::JsonElementException if the root is not an array.
             */
            JsonArray asArray() const;

            /**
             * @brief Converts the JSON value to a string representation.
             * @return A string containing the serialized JSON data.
             */
            std::string toString() const;

            /**
             * @brief Creates an empty JsonObject instance.
             * @return A new empty JsonObject.
             */
            static JsonObject emptyObject();

            /**
             * @brief Creates an empty JsonArray instance.
             * @return A new empty JsonArray.
             */
            static JsonArray emptyArray();

        private:
            JsonElement root;
        };
    } // json
} // r_utils