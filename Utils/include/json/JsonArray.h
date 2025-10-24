#pragma once

#include <vector>
#include <iostream>
#include <sstream>


namespace r_utils
{
	namespace json
	{
		class JsonElement;

        /**
         * @class JsonArray
         * @brief Represents a JSON array, which is an ordered collection of JsonElement objects.
         *
         * This class provides methods to manipulate elements in a JSON array, including
         * adding, removing, accessing by index, and converting the array to a string representation.
         */
        class JsonArray {
        public:
            /**
             * @brief Default constructor. Creates an empty JSON array.
             */
            JsonArray() = default;

            /**
             * @brief Adds an element to the JSON array.
             * @param element The JsonElement to add.
             * @return Reference to the current JsonArray (for method chaining).
             */
            r_utils::json::JsonArray& add(const r_utils::json::JsonElement& element);

            /**
             * @brief Removes an element from the JSON array.
             * @param element The JsonElement to remove.
             * @return Reference to the current JsonArray (for method chaining).
             */
            r_utils::json::JsonArray& remove(const r_utils::json::JsonElement& element);

            /**
             * @brief Accesses an element by its index.
             * @param index The zero-based index of the element.
             * @return Constant reference to the JsonElement at the given index.
             * @throws std::out_of_range if the index is invalid.
             */
            const r_utils::json::JsonElement& get(int index) const;

            size_t size() const;
            bool empty() const;

            /**
             * @brief Returns all elements of the JSON array as a vector.
             * @return Constant reference to the internal vector of JsonElement objects.
             */
            const std::vector<r_utils::json::JsonElement>& getValues() const;

            const std::string toString() const;

            /**
             * @brief Operator for accessing elements by index.
             * @param index Zero-based index of the element.
             * @return Constant reference to the JsonElement at the given index.
             */
            const r_utils::json::JsonElement& operator[](int index) const;

        private:
            std::vector<r_utils::json::JsonElement> values;
        };

        std::ostream& operator<<(std::ostream& os, const r_utils::json::JsonArray& arr);
        bool operator==(const r_utils::json::JsonArray& x, const r_utils::json::JsonArray& y);
        bool operator!=(const r_utils::json::JsonArray& x, const r_utils::json::JsonArray& y);
	} // json
} // r_utils
