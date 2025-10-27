#include "string/StringUtils.h"
#include <algorithm>
#include <cctype>
#include <sstream>

namespace r_utils
{
    namespace string
    {
        // ========== INFORMATION ==========

        size_t length(const std::string& string)
        {
            return string.length();
        }

        size_t length(char* string)
        {
            size_t len = 0;
            while (string && string[len] != '\0') len++;
            return len;
        }

        char charAt(const std::string& string, size_t index)
        {
            if (index >= string.length()) return '\0';
            return string[index];
        }

        char charAt(char* string, size_t index)
        {
            if (!string) return '\0';
            size_t len = r_utils::string::length(string);
            if (index >= len) return '\0';
            return string[index];
        }


        // ========== EXAMINATION ==========

        bool isEmpty(const std::string& string)
        {
            return string.empty();
        }

        bool isEmpty(char* string)
        {
            return !string || string[0] == '\0';
        }

        bool contains(const std::string& string, const std::string& contains)
        {
            return string.find(contains) != std::string::npos;
        }

        bool contains(char string, const std::string& contains)
        {
            return contains.find(string) != std::string::npos;
        }

        bool contains(const std::string& string, char contains)
        {
            return string.find(contains) != std::string::npos;
        }

        bool contains(char string, char contains)
        {
            return string == contains;
        }

        bool startsWith(const std::string& string, const std::string& begins)
        {
            return string.rfind(begins, 0) == 0;
        }

        bool startsWith(const std::string& string, char begins)
        {
            return !string.empty() && string.front() == begins;
        }

        bool startsWith(char string, const std::string& begins)
        {
            return begins.size() == 1 && begins.front() == string;
        }

        bool startsWith(char string, char begins)
        {
            return string == begins;
        }

        bool endsWith(const std::string& string, const std::string& ends)
        {
            if (ends.size() > string.size()) return false;
            return std::equal(ends.rbegin(), ends.rend(), string.rbegin());
        }

        bool endsWith(const std::string& string, char ends)
        {
            return !string.empty() && string.back() == ends;
        }

        bool endsWith(char string, const std::string& ends)
        {
            return ends.size() == 1 && ends.back() == string;
        }

        bool endsWith(char string, char ends)
        {
            return string == ends;
        }

        bool isAlpha(const std::string& string)
        {
            return std::all_of(string.begin(), string.end(), ::isalpha);
        }

        bool isAlpha(char string)
        {
            return std::isalpha(string);
        }


        // ========== FORMATTING ==========

        std::string toLowerCase(const std::string& string)
        {
            std::string result = string;
            std::transform(result.begin(), result.end(), result.begin(), ::tolower);
            return result;
        }

        std::string toLowerCase(char string)
        {
            return std::string(1, static_cast<char>(std::tolower(string)));
        }

        std::string toUpperCase(const std::string& string)
        {
            std::string result = string;
            std::transform(result.begin(), result.end(), result.begin(), ::toupper);
            return result;
        }

        std::string toUpperCase(char string)
        {
            return std::string(1, static_cast<char>(std::toupper(string)));
        }

        std::string trim(const std::string& string)
        {
            size_t start = string.find_first_not_of(" \t\n\r");
            size_t end = string.find_last_not_of(" \t\n\r");
            if (start == std::string::npos) return "";
            return string.substr(start, end - start + 1);
        }

        std::string trim(char string)
        {
            return std::string(1, string);
        }

        std::string reverse(const std::string& string)
        {
            std::string result = string;
            std::reverse(result.begin(), result.end());
            return result;
        }

        std::string reverse(char string)
        {
            return std::string(1, string);
        }

        std::string capitalize(const std::string& string)
        {
            if (string.empty()) return string;
            std::string result = toLowerCase(string);
            result[0] = std::toupper(result[0]);
            return result;
        }

        std::string capitalize(char string)
        {
            return std::string(1, static_cast<char>(std::toupper(string)));
        }


        // ========== MANIPULATING ==========

        std::string replace(const std::string& string, const std::string& toReplace)
        {
            return toReplace;
        }

        std::string replace(char string, const std::string& toReplace)
        {
            return toReplace;
        }

        std::string replace(const std::string& string, char toReplace)
        {
            return std::string(1, toReplace);
        }

        std::string replace(char string, char toReplace)
        {
            return std::string(1, toReplace);
        }

        std::string substring(const std::string& string, size_t start, size_t length)
        {
            if (start >= string.size()) return "";
            return string.substr(start, length);
        }

        std::string substring(char string, size_t start, size_t length)
        {
            return std::string(1, string);
        }

        std::string append(const std::string& string, const std::string& toAppend)
        {
            return string + toAppend;
        }

        std::string append(char string, const std::string& toAppend)
        {
            return std::string(1, string) + toAppend;
        }

        std::string append(const std::string& string, char toAppend)
        {
            return string + toAppend;
        }

        std::string append(char string, char toAppend)
        {
            return std::string(1, string) + toAppend;
        }

        std::vector<std::string> split(const std::string& string, char delimiter)
        {
            std::vector<std::string> parts;
            std::stringstream ss(string);
            std::string item;
            while (std::getline(ss, item, delimiter))
                parts.push_back(item);
            return parts;
        }

        std::vector<std::string> split(char string, char delimiter)
        {
            std::vector<std::string> result;
            result.push_back(std::string(1, string));
            return result;
        }


        // ========== CLASS IMPLEMENTATION ==========

        StringUtils::StringUtils(const std::string& string) : __string__(string) {}
        StringUtils::StringUtils(const char* string) : __string__(string) {}
        StringUtils::StringUtils(char string) : __string__(1, string) {}

        size_t StringUtils::length() const
        {
            return __string__.length();
        }

        char StringUtils::charAt(size_t index) const
        {
            return r_utils::string::charAt(__string__, index);
        }

        bool StringUtils::isEmpty() const
        {
            return r_utils::string::isEmpty(__string__);
        }

        bool StringUtils::contains(const std::string& s) const
        {
            return r_utils::string::contains(__string__, s);
        }

        bool StringUtils::contains(char s) const
        {
            return r_utils::string::contains(__string__, s);
        }

        bool StringUtils::startsWith(const std::string& begins) const
        {
            return r_utils::string::startsWith(__string__, begins);
        }

        bool StringUtils::startsWith(char begins) const
        {
            return r_utils::string::startsWith(__string__, begins);
        }

        bool StringUtils::endsWith(const std::string& ends) const
        {
            return r_utils::string::endsWith(__string__, ends);
        }

        bool StringUtils::endsWith(char ends) const
        {
            return r_utils::string::endsWith(__string__, ends);
        }

        bool StringUtils::isAlpha() const
        {
            return r_utils::string::isAlpha(__string__);
        }

        StringUtils& StringUtils::toLowerCase()
        {
            __string__ = r_utils::string::toLowerCase(__string__);
            return *this;
        }

        StringUtils& StringUtils::toUpperCase()
        {
            __string__ = r_utils::string::toUpperCase(__string__);
            return *this;
        }

        StringUtils& StringUtils::trim()
        {
            __string__ = r_utils::string::trim(__string__);
            return *this;
        }

        StringUtils& StringUtils::reverse()
        {
            __string__ = r_utils::string::reverse(__string__);
            return *this;
        }

        StringUtils& StringUtils::capitalize()
        {
            __string__ = r_utils::string::capitalize(__string__);
            return *this;
        }

        StringUtils& StringUtils::replace(const std::string& toReplace)
        {
            __string__ = toReplace;
            return *this;
        }

        StringUtils& StringUtils::replace(char toReplace)
        {
            __string__ = std::string(1, toReplace);
            return *this;
        }

        StringUtils& StringUtils::substring(size_t start, size_t length)
        {
            __string__ = r_utils::string::substring(__string__, start, length);
            return *this;
        }

        StringUtils& StringUtils::append(const std::string& toAppend)
        {
            __string__ = r_utils::string::append(__string__, toAppend);
            return *this;
        }

        StringUtils& StringUtils::append(char toAppend)
        {
            __string__ = r_utils::string::append(__string__, toAppend);
            return *this;
        }

        const std::vector<std::string> StringUtils::split(char delimiter) const
        {
            return r_utils::string::split(__string__, delimiter);
        }

        StringUtils::operator std::string() const
        {
            return __string__;
        }

        const std::string& StringUtils::str() const
        {
            return __string__;
        }
    }
}