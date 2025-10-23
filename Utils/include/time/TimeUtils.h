#pragma once

#include <chrono>
#include <string>

namespace r_utils
{
    namespace time
    {
        /**
         * @enum TimeFormat
         * @brief Defines common date/time output formats for TimeUtils.
         */
        enum TimeFormat
        {
            ISO,        /**< "YYYY-MM-DD HH:MM:SS" -> Standard */
            DATE_ONLY,  /**< "YYYY-MM-DD" */
            TIME_ONLY,  /**< "HH:MM:SS" */
            SHORT_DATE, /**< "DD.MM.YYYY" */
            SHORT_TIME  /**< "HH:MM" */
        };

        /**
         * @class TimeUtils
         * @brief Utility class for working with system time and conversions.
         *
         * Provides functions to get the current time, format it as a string,
         * parse strings to time points, perform arithmetic (add/subtract time),
         * calculate differences, and extract date information such as day of week or leap year checks.
         */
        class TimeUtils
        {
        public:
            /**
             * @brief Returns the current system time as a time_point.
             * @return std::chrono::system_clock::time_point representing now.
             */
            static std::chrono::system_clock::time_point now();

            /**
             * @brief Returns the current system time formatted as a string.
             * @param format Format string for std::strftime (default ISO "YYYY-MM-DD HH:MM:SS").
             * @return Formatted current time string.
             */
            static std::string nowString(const std::string& format = "%Y-%m-%d %H:%M:%S");
            /**
             * @brief Returns the current system time formatted according to a TimeFormat enum.
             * @param format TimeFormat enum specifying the format.
             * @return Formatted current time string.
             */
            static std::string nowString(TimeFormat format);

            /**
             * @brief Converts a time_point to a formatted string.
             * @param timePoint Time point to format.
             * @param format Format string for std::strftime (default ISO "YYYY-MM-DD HH:MM:SS").
             * @return Formatted time string.
             */
            static std::string toString(const std::chrono::system_clock::time_point& timePoint,
                const std::string& format = "%Y-%m-%d %H:%M:%S");
            /**
             * @brief Converts a time_point to a string according to a TimeFormat enum.
             * @param timePoint Time point to format.
             * @param format TimeFormat enum specifying the format.
             * @return Formatted time string.
             */
            static std::string toString(const std::chrono::system_clock::time_point& timePoint,
                TimeFormat format);

            /**
             * @brief Parses a formatted time string to a time_point.
             * @param timeString Input string representing a time.
             * @param format Format string for std::get_time (default ISO "YYYY-MM-DD HH:MM:SS").
             * @return std::chrono::system_clock::time_point corresponding to the string.
             */
            static std::chrono::system_clock::time_point fromString(const std::string& timeString,
                const std::string& format = "%Y-%m-%d %H:%M:%S");
            /**
             * @brief Parses a formatted time string using a TimeFormat enum.
             * @param timeString Input string representing a time.
             * @param format TimeFormat enum specifying the format.
             * @return std::chrono::system_clock::time_point corresponding to the string.
             */
            static std::chrono::system_clock::time_point fromString(const std::string& timeString,
                TimeFormat format);

            /**
             * @brief Adds seconds to a time_point.
             * @param tp Base time_point.
             * @param seconds Number of seconds to add (can be negative to subtract).
             * @return New time_point after addition.
             */
            static std::chrono::system_clock::time_point addSeconds(const std::chrono::system_clock::time_point& tp, int seconds);
            /**
             * @brief Adds minutes to a time_point.
             * @param tp Base time_point.
             * @param minutes Number of minutes to add (can be negative to subtract).
             * @return New time_point after addition.
             */
            static std::chrono::system_clock::time_point addMinutes(const std::chrono::system_clock::time_point& tp, int minutes);
            /**
             * @brief Adds hours to a time_point.
             * @param tp Base time_point.
             * @param hours Number of hours to add (can be negative to subtract).
             * @return New time_point after addition.
             */
            static std::chrono::system_clock::time_point addHours(const std::chrono::system_clock::time_point& tp, int hours);
            /**
             * @brief Adds days to a time_point.
             * @param tp Base time_point.
             * @param days Number of days to add (can be negative to subtract).
             * @return New time_point after addition.
             */
            static std::chrono::system_clock::time_point addDays(const std::chrono::system_clock::time_point& tp, int days);

            /**
             * @brief Computes the difference in seconds between two time_points.
             * @param a First time_point.
             * @param b Second time_point.
             * @return Number of seconds (a - b).
             */
            static int diffSeconds(const std::chrono::system_clock::time_point& a, const std::chrono::system_clock::time_point& b);
            /**
             * @brief Computes the difference in minutes between two time_points.
             * @param a First time_point.
             * @param b Second time_point.
             * @return Number of minutes (a - b).
             */
            static int diffMinutes(const std::chrono::system_clock::time_point& a, const std::chrono::system_clock::time_point& b);
            /**
             * @brief Computes the difference in hours between two time_points.
             * @param a First time_point.
             * @param b Second time_point.
             * @return Number of hours (a - b).
             */
            static int diffHours(const std::chrono::system_clock::time_point& a, const std::chrono::system_clock::time_point& b);
            /**
             * @brief Computes the difference in days between two time_points.
             * @param a First time_point.
             * @param b Second time_point.
             * @return Number of days (a - b).
             */
            static int diffDays(const std::chrono::system_clock::time_point& a, const std::chrono::system_clock::time_point& b);

            /**
             * @brief Checks if a year is a leap year.
             * @param year Year to check.
             * @return True if leap year, false otherwise.
             */
            static bool isLeapYear(int year);

            /**
             * @brief Returns the day of the week for a time_point.
             * @param tp Time point.
             * @return Day of the week as integer (0=Sunday, 1=Monday, ..., 6=Saturday).
             */
            static int dayOfWeek(const std::chrono::system_clock::time_point& tp);
        };
    } // time
} // r_utils
