#include "string/StringUtils.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <exception/string/StringException.h>

namespace r_utils
{
    namespace string
    {
        // ========== INFORMATION ==========

        size_t length(const std::string& string)
        {
            return string.length();
        }

        size_t length(char* c)
        {
            if (!c)
                throw r_utils::exception::NullPointerException("Null string pointer in length(char*)");

            size_t len = 0;
            while (c[len] != '\0') len++;
            return len;
        }

        char charAt(const std::string& string, size_t index)
        {
            if (index >= string.length())
                throw r_utils::exception::IndexOutOfRangeException("Index out of range in charAt()");
            return string[index];
        }


        // ========== EXAMINATION ==========

        bool isEmpty(const std::string& string)
        {
            return string.empty();
        }

        bool isEmpty(char* c)
        {
            if (!c)
                throw r_utils::exception::NullPointerException("Null string pointer in isEmpty(char*)");
            return c[0] == '\0';
        }

        bool contains(const std::string& string, const std::string& contains)
        {
            if (contains.empty())
                throw r_utils::exception::InvalidArgumentException("Cannot search for empty substring in contains()");
            return string.find(contains) != std::string::npos;
        }

        bool contains(const std::string& string, char contains)
        {
			return r_utils::string::contains(string, std::string(1, contains));
        }

        bool startsWith(const std::string& string, const std::string& begins)
        {
            if (begins.empty())
                throw r_utils::exception::InvalidArgumentException("Cannot check startsWith() with empty prefix");
            return string.rfind(begins, 0) == 0;
        }

        bool startsWith(const std::string& string, char begins)
        {
            return r_utils::string::startsWith(string, std::string(1, begins));
        }

        bool endsWith(const std::string& string, const std::string& ends)
        {
            if (string.size() < ends.size()) return false;
            if (ends.empty())
                throw r_utils::exception::InvalidArgumentException("Cannot check endsWith() with empty prefix");
            return std::equal(ends.rbegin(), ends.rend(), string.rbegin());
        }

        bool endsWith(const std::string& string, char ends)
        {
            return r_utils::string::endsWith(string, std::string(1, ends));
        }

        bool isAlpha(const std::string& string)
        {
            if (string.empty())
                throw r_utils::exception::InvalidArgumentException("Cannot check isAlpha() on empty string");
            return std::all_of(string.begin(), string.end(), ::isalpha);
        }

        bool isAlpha(char string)
        {
            return r_utils::string::isAlpha(std::string(1, string));
        }


        // ========== FORMATTING ==========

        std::string toLowerCase(const std::string& string)
        {
            std::string result = string;
            std::transform(result.begin(), result.end(), result.begin(), ::tolower);
            return result;
        }

        std::string toLowerCase(char c)
        {
            return std::string(1, static_cast<char>(::tolower(c)));
        }

        std::string toUpperCase(const std::string& string)
        {
            std::string result = string;
            std::transform(result.begin(), result.end(), result.begin(), ::toupper);
            return result;
        }

        std::string toUpperCase(char c)
        {
            return std::string(1, static_cast<char>(::toupper(c)));
        }

        std::string trim(const std::string& string)
        {
            size_t start = string.find_first_not_of(" \t\n\r");
            size_t end = string.find_last_not_of(" \t\n\r");
            if (start == std::string::npos) return "";
            return string.substr(start, end - start + 1);
        }

        std::string reverse(const std::string& string)
        {
            std::string result = string;
            std::reverse(result.begin(), result.end());
            return result;
        }

        std::string capitalize(const std::string& string)
        {
            if (string.empty())
                throw r_utils::exception::InvalidArgumentException("Cannot capitalize an empty string");
            std::string result = toLowerCase(string);
            result[0] = std::toupper(result[0]);
            return result;
        }


        // ========== MANIPULATING ==========

        std::string replace(const std::string& string, const std::string& replace, const std::string& toReplace)
        {
            if (replace.empty())
                throw r_utils::exception::InvalidArgumentException("Replace target cannot be empty");

            std::string result = string;
            size_t pos = 0;
            while ((pos = result.find(replace, pos)) != std::string::npos)
            {
                result.replace(pos, replace.length(), toReplace);
                pos += toReplace.length();
            }
            return result;
        }

        std::string replace(const std::string& string, char replace, const std::string& toReplace)
        {
			return r_utils::string::replace(string, std::string(1, replace), toReplace);
        }

        std::string replace(const std::string& string, const std::string& replace, char toReplace)
        {
			return r_utils::string::replace(string, replace, std::string(1, toReplace));
        }

        std::string replace(const std::string& string, char replace, char toReplace)
        {
			return r_utils::string::replace(string, std::string(1, replace), std::string(1, toReplace));
        }

        std::string substring(const std::string& string, size_t start, size_t length)
        {
            if (start > string.size())
                throw r_utils::exception::IndexOutOfRangeException("Start index out of range in substring()");
            return string.substr(start, length);
        }

        std::string append(const std::string& string, const std::string& toAppend)
        {
            return string + toAppend;
        }

        std::string append(char c, const std::string& toAppend)
        {
            return std::string(1, c) + toAppend;
        }

        std::string append(const std::string& string, char toAppend)
        {
            return string + toAppend;
        }

        std::string append(char c, char toAppend)
        {
            return std::string(1, c) + toAppend;
        }

        std::vector<std::string> split(const std::string& string, char delimiter)
        {
            if (string.empty())
                throw r_utils::exception::InvalidArgumentException("Cannot split empty string");

            std::vector<std::string> parts;
            std::stringstream ss(string);
            std::string item;
            while (std::getline(ss, item, delimiter))
                parts.push_back(item);
            return parts;
        }


        // ========== CLASS IMPLEMENTATION ==========

        StringUtils::StringUtils(const std::string& string) : __string__(string) {}
        StringUtils::StringUtils(const char* c)
        {
            if (!c)
                throw r_utils::exception::NullPointerException("Null pointer passed to StringUtils(const char*)");
            __string__ = c;
        }
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

        r_utils::string::StringUtils& StringUtils::replace(const std::string& replace, const std::string& toReplace)
        {
			__string__ = r_utils::string::replace(__string__, replace, toReplace);
            return *this;
        }

        r_utils::string::StringUtils& StringUtils::replace(char replace, char toReplace)
        {
            __string__ = r_utils::string::replace(__string__, replace, toReplace);
            return *this;
        }

        r_utils::string::StringUtils& StringUtils::replace(char replace, const std::string& toReplace)
        {
            __string__ = r_utils::string::replace(__string__, replace, toReplace);
            return *this;
        }

        r_utils::string::StringUtils& StringUtils::replace(const std::string& replace, char toReplace)
        {
            __string__ = r_utils::string::replace(__string__, replace, toReplace);
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

        std::vector<std::string> StringUtils::split(char delimiter) const
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
    } // string
} //r_utils