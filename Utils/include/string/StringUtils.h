#pragma once

#include <string>
#include <vector>

namespace r_utils
{
	namespace string
	{

		/**
		 * @brief Returns the length of a string.
		 * @param string The string to measure.
		 * @return Number of characters in the string.
		 */
		[[nodiscard]] size_t length(const std::string& string);

		/**
		 * @brief Returns the length of a C-style string.
		 * @param c Pointer to a null-terminated character array.
		 * @return Number of characters before the null terminator.
		 */
		[[nodiscard]] size_t length(char* c);

		/**
		 * @brief Returns the character at the specified index.
		 * @param string The string to access.
		 * @param index The index (0-based) of the character.
		 * @return The character at the given index.
		 * @throws std::out_of_range if index is invalid.
		 */
		char charAt(const std::string& string, size_t index);


		// ---------- EXAMINATION ----------

		/**
		 * @brief Checks whether the string is empty.
		 * @param string The string to check.
		 * @return True if the string is empty, otherwise false.
		 */
		[[nodiscard]] bool isEmpty(const std::string& string);

		/**
		 * @brief Checks whether a C-style string is empty.
		 * @param string The string to check.
		 * @return True if the string is empty, otherwise false.
		 */
		[[nodiscard]] bool isEmpty(char* string);

		/**
		 * @brief Checks whether the string contains a given substring.
		 * @param string The string to search in.
		 * @param contains The substring to search for.
		 * @return True if found, otherwise false.
		 */
		[[nodiscard]] bool contains(const std::string& string, const std::string& contains);

		/**
		 * @brief Checks whether the string contains a specific character.
		 * @param string The string to search in.
		 * @param contains The character to search for.
		 * @return True if found, otherwise false.
		 */
		[[nodiscard]] bool contains(const std::string& string, char contains);

		/**
		 * @brief Checks if a string starts with a given prefix.
		 * @param string The string to check.
		 * @param begins The prefix to compare.
		 * @return True if the string starts with the prefix, otherwise false.
		 */
		[[nodiscard]] bool startsWith(const std::string& string, const std::string& begins);

		/**
		 * @brief Checks if a string starts with a given character.
		 * @param string The string to check.
		 * @param begins The starting character.
		 * @return True if the string starts with the character, otherwise false.
		 */
		[[nodiscard]] bool startsWith(const std::string& string, char begins);

		/**
		 * @brief Checks if a string ends with a given suffix.
		 * @param string The string to check.
		 * @param ends The suffix to compare.
		 * @return True if the string ends with the suffix, otherwise false.
		 */
		[[nodiscard]] bool endsWith(const std::string& string, const std::string& ends);

		/**
		 * @brief Checks if a string ends with a given character.
		 * @param string The string to check.
		 * @param ends The ending character.
		 * @return True if the string ends with the character, otherwise false.
		 */
		[[nodiscard]] bool endsWith(const std::string& string, char ends);

		/**
		 * @brief Checks if all characters in the string are alphabetic.
		 * @param string The string to check.
		 * @return True if the string is alphabetic, otherwise false.
		 */
		[[nodiscard]] bool isAlpha(const std::string& string);

		/**
		 * @brief Checks if the given character is alphabetic.
		 * @param c The character to check.
		 * @return True if the character is alphabetic, otherwise false.
		 */
		[[nodiscard]] bool isAlpha(char c);


		// ---------- FORMATTING ----------

		/**
		 * @brief Converts a string to lowercase.
		 * @param string The string to convert.
		 * @return A new lowercase string.
		 */
		std::string toLowerCase(const std::string& string);

		/**
		 * @brief Converts a character to lowercase.
		 * @param c The character to convert.
		 * @return A new lowercase character as a string.
		 */
		std::string toLowerCase(char c);

		/**
		 * @brief Converts a string to uppercase.
		 * @param string The string to convert.
		 * @return A new uppercase string.
		 */
		std::string toUpperCase(const std::string& string);

		/**
		 * @brief Converts a character to uppercase.
		 * @param c The character to convert.
		 * @return A new uppercase character as a string.
		 */
		std::string toUpperCase(char c);

		/**
		 * @brief Removes leading and trailing whitespace.
		 * @param string The string to trim.
		 * @return A new trimmed string.
		 */
		std::string trim(const std::string& string);

		/**
		 * @brief Returns the reversed version of a string.
		 * @param string The string to reverse.
		 * @return A reversed copy of the string.
		 */
		std::string reverse(const std::string& string);

		/**
		 * @brief Capitalizes the first letter of the string.
		 * @param string The string to capitalize.
		 * @return A new capitalized string.
		 */
		std::string capitalize(const std::string& string);


		// ---------- MANIPULATING ----------

		/**
		 * @brief Replaces all occurrences of a substring with another substring.
		 * @param string The source string.
		 * @param replace The substring to replace.
		 * @param toReplace The replacement.
		 * @return A modified copy of the string.
		 */
		std::string replace(const std::string& string, const std::string& replace, const std::string& toReplace);

		/**
		 * @brief Replaces all occurrences of a character with a substring.
		 */
		std::string replace(const std::string& string, char replace, const std::string& toReplace);

		/**
		 * @brief Replaces all occurrences of a substring with a character.
		 */
		std::string replace(const std::string& string, const std::string& replace, char toReplace);

		/**
		 * @brief Replaces all occurrences of one character with another.
		 */
		std::string replace(const std::string& string, char replace, char toReplace);

		/**
		 * @brief Extracts a substring from the given string.
		 * @param string The source string.
		 * @param start The start position.
		 * @param length The number of characters.
		 * @return The extracted substring.
		 * @throws std::out_of_range if start or length are invalid.
		 */
		std::string substring(const std::string& string, size_t start, size_t length);

		/**
		 * @brief Appends a string to a character.
		 */
		std::string append(char c, const std::string& toAppend);

		/**
		 * @brief Appends a character to another character.
		 */
		std::string append(char c, char toAppend);

		/**
		 * @brief Appends one string to another.
		 */
		std::string append(const std::string& string, const std::string& toAppend);

		/**
		 * @brief Appends a character to a string.
		 */
		std::string append(const std::string& string, char toAppend);

		/**
		 * @brief Splits a string into tokens separated by a given delimiter.
		 * @param string The source string.
		 * @param delimiter The delimiter character.
		 * @return A vector containing all tokens.
		 */
		std::vector<std::string> split(const std::string& string, char delimiter);


		/**
		 * @class StringUtils
		 * @brief Provides chainable string manipulation and inspection utilities.
		 *
		 * Allows both inspection and modification of a string through a fluent interface,
		 * e.g. `StringUtils("Hello").toLowerCase().reverse().str();`
		 */
		class StringUtils
		{
		public:
			/**
			 * @brief Constructs a StringUtils object from a std::string.
			 */
			StringUtils(const std::string& string);

			/**
			 * @brief Constructs a StringUtils object from a C-style string.
			 */
			StringUtils(const char* c);

			/**
			 * @brief Constructs a StringUtils object from a single character.
			 */
			StringUtils(char string);

			~StringUtils() = default;


			// ---------- INFORMATION ----------

			/**
			 * @brief Returns the string length.
			 */
			size_t length() const;

			/**
			 * @brief Returns the character at the specified index.
			 * @throws std::out_of_range if index is invalid.
			 */
			char charAt(size_t index) const;


			// ---------- EXAMINATION ----------

			/**
			 * @brief Checks if the internal string is empty.
			 */
			[[nodiscard]] bool isEmpty() const;

			/**
			 * @brief Checks whether the string contains the given substring.
			 */
			[[nodiscard]] bool contains(const std::string& string) const;

			/**
			 * @brief Checks whether the string contains the given character.
			 */
			[[nodiscard]] bool contains(char string) const;

			/**
			 * @brief Checks whether the string starts with the given prefix.
			 */
			[[nodiscard]] bool startsWith(const std::string& begins) const;

			/**
			 * @brief Checks whether the string starts with the given character.
			 */
			[[nodiscard]] bool startsWith(char begins) const;

			/**
			 * @brief Checks whether the string ends with the given suffix.
			 */
			[[nodiscard]] bool endsWith(const std::string& begins) const;

			/**
			 * @brief Checks whether the string ends with the given character.
			 */
			[[nodiscard]] bool endsWith(char begins) const;

			/**
			 * @brief Checks whether all characters in the string are alphabetic.
			 */
			[[nodiscard]] bool isAlpha() const;


			// ---------- FORMATTING ----------

			/**
			 * @brief Converts the internal string to lowercase.
			 * @return Reference to this instance.
			 */
			r_utils::string::StringUtils& toLowerCase();

			/**
			 * @brief Converts the internal string to uppercase.
			 * @return Reference to this instance.
			 */
			r_utils::string::StringUtils& toUpperCase();

			/**
			 * @brief Trims leading and trailing whitespace from the internal string.
			 * @return Reference to this instance.
			 */
			r_utils::string::StringUtils& trim();

			/**
			 * @brief Reverses the internal string.
			 * @return Reference to this instance.
			 */
			r_utils::string::StringUtils& reverse();

			/**
			 * @brief Capitalizes the first letter of the internal string.
			 * @return Reference to this instance.
			 */
			r_utils::string::StringUtils& capitalize();


			// ---------- MANIPULATING ----------

			/**
			 * @brief Replaces all occurrences of one substring with another.
			 * @return Reference to this instance.
			 */
			r_utils::string::StringUtils& replace(const std::string& replace, const std::string& toReplace);

			/**
			 * @brief Replaces all occurrences of one character with another.
			 * @return Reference to this instance.
			 */
			r_utils::string::StringUtils& replace(char replace, char toReplace);

			/**
			 * @brief Replaces all occurrences of a character with a string.
			 * @return Reference to this instance.
			 */
			r_utils::string::StringUtils& replace(char replace, const std::string& toReplace);

			/**
			 * @brief Replaces all occurrences of a string with a character.
			 * @return Reference to this instance.
			 */
			r_utils::string::StringUtils& replace(const std::string& replace, char toReplace);

			/**
			 * @brief Extracts a substring from the internal string.
			 * @throws std::out_of_range if start or length are invalid.
			 * @return Reference to this instance containing the substring.
			 */
			r_utils::string::StringUtils& substring(size_t start, size_t length);

			/**
			 * @brief Appends a string to the internal string.
			 * @return Reference to this instance.
			 */
			r_utils::string::StringUtils& append(const std::string& toAppend);

			/**
			 * @brief Appends a character to the internal string.
			 * @return Reference to this instance.
			 */
			r_utils::string::StringUtils& append(char toAppend);

			/**
			 * @brief Splits the internal string by a delimiter.
			 * @param delimiter The character to split on.
			 * @return A vector of substrings.
			 */
			[[nodiscard]] std::vector<std::string> split(char delimiter) const;

			/**
			 * @brief Implicit conversion to std::string.
			 */
			[[nodiscard]] operator std::string() const;

			/**
			 * @brief Returns a const reference to the internal string.
			 */
			const std::string& str() const;

		private:
			std::string __string__;
		};
	}
}
