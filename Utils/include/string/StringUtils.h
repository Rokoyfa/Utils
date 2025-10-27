#pragma once

#include <string>
#include <vector>

namespace r_utils
{
	namespace string
	{
		// ========== INFORMATION ==========

		size_t length(const std::string& string);
		size_t length(char* string);

		char charAt(const std::string& string, size_t index);
		char charAt(char* string, size_t index);


		// ========== EXAMINATION ==========

		bool isEmpty(const std::string& string);
		bool isEmpty(char* string);

		bool contains(const std::string& string, const std::string& contains);
		bool contains(char string, const std::string& contains);
		bool contains(const std::string& string, char contains);
		bool contains(char string, char contains);

		bool startsWith(const std::string& string, const std::string& begins);
		bool startsWith(const std::string& string, char begins);
		bool startsWith(char string, const std::string& begins);
		bool startsWith(char string, char begins);

		bool endsWith(const std::string& string, const std::string& begins);
		bool endsWith(const std::string& string, char begins);
		bool endsWith(char string, const std::string& begins);
		bool endsWith(char string, char begins);

		bool isAlpha(const std::string& string);
		bool isAlpha(char string);


		// ========== FORMATTING ==========

		std::string toLowerCase(const std::string& string);
		std::string toLowerCase(char string);

		std::string toUpperCase(const std::string& string);
		std::string toUpperCase(char string);

		std::string trim(const std::string& string);
		std::string trim(char string);

		std::string reverse(const std::string& string);
		std::string reverse(char string);

		std::string capitalize(const std::string& string);
		std::string capitalize(char string);


		// ========== MANIPULATING ==========

		std::string replace(const std::string& string, const std::string& toReplace);
		std::string replace(char string, const std::string& toReplace);
		std::string replace(const std::string& string, char toReplace);
		std::string replace(char string, char toReplace);

		std::string substring(const std::string& string, size_t start, size_t length);
		std::string substring(char string, size_t start, size_t length);

		std::string append(const std::string& string, const std::string& toAppend);
		std::string append(char string, const std::string& toAppend);
		std::string append(const std::string& string, char toAppend);
		std::string append(char string, char toAppend);

		std::vector<std::string> split(const std::string& string, char delimiter);
		std::vector<std::string> split(char string, char delimiter);



		class StringUtils
		{
		public:
			StringUtils(const std::string& string);
			StringUtils(const char* string);
			StringUtils(char string);
			~StringUtils() = default;


			// ========== INFORMATION ==========

			size_t length() const;
			char charAt(size_t index) const;


			// ========== EXAMINATION ==========

			bool isEmpty() const;

			bool contains(const std::string& string) const;
			bool contains(char string) const;

			bool startsWith(const std::string& begins) const;
			bool startsWith(char begins) const;

			bool endsWith(const std::string& begins) const;
			bool endsWith(char begins) const;

			bool isAlpha() const;


			// ========== FORMATTING ==========

			r_utils::string::StringUtils& toLowerCase();
			r_utils::string::StringUtils& toUpperCase();
			r_utils::string::StringUtils& trim();
			r_utils::string::StringUtils& reverse();
			r_utils::string::StringUtils& capitalize();


			// ========== MANIPULATING ==========

			r_utils::string::StringUtils& replace(const std::string& toReplace);
			r_utils::string::StringUtils& replace(char toReplace);

			r_utils::string::StringUtils& substring(size_t start, size_t length);

			r_utils::string::StringUtils& append(const std::string& toAppend);
			r_utils::string::StringUtils& append(char toAppend);

			const std::vector<std::string> split(char delimiter) const;

			operator std::string() const;
			const std::string& str() const;
		private:
			std::string __string__;
		};
	}
}