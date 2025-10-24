#pragma once

#include <iostream>

#include "json/JsonObject.h"
#include "json/JsonElement.h"
#include "json/JsonArray.h"
#include "file/File.h"

namespace r_utils
{
	namespace json
	{
		/**
		 * @class JsonParser
		 * @brief Parses JSON-formatted strings or files into JsonElement objects.
		 *
		 * JsonParser provides static methods to parse JSON data from strings or files
		 * and returns the result as a JsonElement. It also contains internal methods
		 * for parsing specific JSON types, including objects, arrays, strings, numbers,
		 * booleans, and null values.
		 */
		class JsonParser
		{
		public:
			/** Default constructor. Creates a parser without any input. */
			JsonParser() = default;

			/**
			 * @brief Parses a JSON string into a JsonElement.
			 * @param input JSON string to parse.
			 * @return JsonElement representing the parsed JSON data.
			 * @throws JsonParserException if parsing fails.
			 */
			static JsonElement parse(const std::string& input);

			/**
			 * @brief Parses a JSON file into a JsonElement.
			 * @param file File object containing JSON data.
			 * @return JsonElement representing the parsed JSON data.
			 * @throws JsonParserException if parsing fails.
			 */
			static JsonElement parse(const r_utils::io::File& file);

		private:
			/**
			 * @brief Private constructor for internal parsing from a string.
			 * @param input JSON string to parse.
			 */
			explicit JsonParser(std::string input);

			/** @brief Returns the next character without advancing the position. */
			char peek() const;
			/** @brief Returns the next character and advances the position. */
			char next();
			/** @brief Checks if the end of input has been reached. */
			bool eof() const;
			/** @brief Skips whitespace characters in the input. */
			void skipWhitespace();

			/** @brief Parses a generic JSON value (object, array, string, number, bool, or null). */
			JsonElement parseValue();
			/** @brief Parses a JSON null value. */
			JsonElement parseNull();
			/** @brief Parses a JSON boolean value (true or false). */
			JsonElement parseBool();
			/** @brief Parses a JSON number (integer or floating-point). */
			JsonElement parseNumber();
			/** @brief Parses a JSON string. */
			JsonElement parseString();
			/** @brief Parses a JSON array. */
			JsonArray parseArray();
			/** @brief Parses a JSON object. */
			JsonObject parseObject();

			std::string input;
			size_t pos;
		};
	} // json
} // r_utils
