#pragma once

#include <iostream>
#include <variant>

#include "json/JsonObject.h"
#include "json/JsonArray.h"

namespace r_utils {
    namespace json {

        /**
         * @enum JsonType
         * @brief Defines the type of a JSON element.
         */
        enum class JsonType {
            Null,    /**< Represents a null value */
            String,  /**< Represents a string value */
            Int,     /**< Represents an integer value */
            Double,  /**< Represents a floating-point value */
            Boolean, /**< Represents a boolean value */
            Array,   /**< Represents a JSON array */
            Object   /**< Represents a JSON object */
        };

        /**
         * @brief Inserts a JsonType into an output stream.
         * @param os Output stream.
         * @param type The JsonType to output.
         * @return Reference to the output stream.
         */
        std::ostream& operator<<(std::ostream& os, const JsonType& type);

        /**
         * @brief Compares two JsonElements for equality.
         * @param x First JsonElement.
         * @param y Second JsonElement.
         * @return True if elements are equal, false otherwise.
         */
        bool operator==(const r_utils::json::JsonElement& x, const r_utils::json::JsonElement& y);

        /**
         * @brief Compares two JsonElements for inequality.
         * @param x First JsonElement.
         * @param y Second JsonElement.
         * @return True if elements are not equal, false otherwise.
         */
        bool operator!=(const r_utils::json::JsonElement& x, const r_utils::json::JsonElement& y);

        /**
         * @class JsonElement
         * @brief Represents a single JSON value of any valid type (string, number, boolean, null, array, object).
         *
         * JsonElement is the core building block for JSON handling. It stores a single
         * value of one of the supported JSON types and provides methods to query its type,
         * convert to a string, and extract the underlying value.
         */
        class JsonElement
        {
        public:
            /** Default constructor. Creates a null JSON element. */
            JsonElement();
            /** Constructs a JSON string element. */
            JsonElement(const std::string& value);
            JsonElement(const char* value);
            /** Constructs a JSON integer element. */
            JsonElement(int value);
            /** Constructs a JSON double element. */
            JsonElement(double value);
            /** Constructs a JSON boolean element. */
            JsonElement(bool value);
            /** Constructs a JSON null element. */
            JsonElement(nullptr_t value);
            /** Constructs a JSON array element. */
            JsonElement(const r_utils::json::JsonArray& value);
            /** Constructs a JSON object element. */
            JsonElement(const r_utils::json::JsonObject& value);


            [[nodiscard]] JsonType getType() const;
            [[nodiscard]] std::string stringify() const;
            [[nodiscard]] std::variant<std::monostate, std::string, int, double, bool, nullptr_t, r_utils::json::JsonObject, r_utils::json::JsonArray> getValue() const;

            [[nodiscard]] bool isNull() const;
            [[nodiscard]] bool isString() const;
            [[nodiscard]] bool isInt() const;
            [[nodiscard]] bool isDouble() const;
            [[nodiscard]] bool isBoolean() const;
            [[nodiscard]] bool isArray() const;
            [[nodiscard]] bool isObject() const;

            /** Returns the element as a string. Throws if the type does not match. */
            std::string asString() const;
            /** Returns the element as an integer. Throws if the type does not match. */
            int asInt() const;
            /** Returns the element as a double. Throws if the type does not match. */
            double asDouble() const;
            /** Returns the element as a boolean. Throws if the type does not match. */
            bool asBoolean() const;
            /** Returns the element as a JSON array. Throws if the type does not match. */
            r_utils::json::JsonArray asArray() const;
            /** Returns the element as a JSON object. Throws if the type does not match. */
            r_utils::json::JsonObject asObject() const;

        private:
            JsonType type;
            std::variant<std::monostate, std::string, int, double, bool, nullptr_t, r_utils::json::JsonObject, r_utils::json::JsonArray> value;
        };

    } // json
} // r_utils
