#include "time/TimeUtils.h"

#include <string>

namespace r_utils
{
	namespace time
	{
		inline static std::string formatToString(TimeFormat format)
		{
			switch (format)
			{
			case DATE_ONLY:  return "%Y-%m-%d";
			case TIME_ONLY:  return "%H:%M:%S";
			case SHORT_DATE: return "%d.%m.%Y";
			case SHORT_TIME: return "%H:%M";
			case ISO:		 return "%Y-%m-%d %H:%M:%S";
			default:         return "%Y-%m-%d %H:%M:%S";
			}
		}

		std::string TimeUtils::nowString(const std::string& format)
		{
			auto now = std::chrono::system_clock::now();
			return toString(now, format);
		}

		std::string TimeUtils::nowString(TimeFormat format)
		{
			auto now = std::chrono::system_clock::now();
			return toString(now, format);
		}


		std::string TimeUtils::toString(const std::chrono::system_clock::time_point& timePoint, const std::string& format)
		{
			std::time_t t = std::chrono::system_clock::to_time_t(timePoint);
			std::tm tm_buf;
#ifdef _WIN32
			localtime_s(&tm_buf, &t);
#else
			localtime_r(&t, &tm_buf);
#endif
			std::ostringstream oss;
			oss << std::put_time(&tm_buf, format.c_str());
			return oss.str();
		}

		std::string TimeUtils::toString(const std::chrono::system_clock::time_point& timePoint, TimeFormat format)
		{
			return toString(timePoint, formatToString(format));
		}


		std::chrono::system_clock::time_point TimeUtils::fromString(const std::string& timeString, const std::string& format)
		{
			std::tm tm_buf = {};
			std::istringstream ss(timeString);
			ss >> std::get_time(&tm_buf, format.c_str());
			std::time_t tt = std::mktime(&tm_buf);
			return std::chrono::system_clock::from_time_t(tt);
		}

		std::chrono::system_clock::time_point TimeUtils::fromString(const std::string& timeString, TimeFormat format)
		{
			return fromString(timeString, formatToString(format));
		}


		std::chrono::system_clock::time_point TimeUtils::addSeconds(const std::chrono::system_clock::time_point& tp, int seconds)
		{
			return tp + std::chrono::seconds(seconds);
		}

		std::chrono::system_clock::time_point TimeUtils::addMinutes(const std::chrono::system_clock::time_point& tp, int minutes)
		{
			return tp + std::chrono::minutes(minutes);
		}

		std::chrono::system_clock::time_point TimeUtils::addHours(const std::chrono::system_clock::time_point& tp, int hours)
		{
			return tp + std::chrono::hours(hours);
		}

		std::chrono::system_clock::time_point TimeUtils::addDays(const std::chrono::system_clock::time_point& tp, int days)
		{
			return tp + std::chrono::hours(days * 24);
		}


		int TimeUtils::diffSeconds(const std::chrono::system_clock::time_point& a, const std::chrono::system_clock::time_point& b)
		{
			return std::chrono::duration_cast<std::chrono::seconds>(a - b).count();
		}

		int TimeUtils::diffMinutes(const std::chrono::system_clock::time_point& a, const std::chrono::system_clock::time_point& b)
		{
			return std::chrono::duration_cast<std::chrono::minutes>(a - b).count();
		}

		int TimeUtils::diffHours(const std::chrono::system_clock::time_point& a, const std::chrono::system_clock::time_point& b)
		{
			return std::chrono::duration_cast<std::chrono::hours>(a - b).count();
		}

		int TimeUtils::diffDays(const std::chrono::system_clock::time_point& a, const std::chrono::system_clock::time_point& b)
		{
			return diffHours(a, b) / 24;
		}


		bool TimeUtils::isLeapYear(int year)
		{
			return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		}

		int TimeUtils::dayOfWeek(const std::chrono::system_clock::time_point& tp)
		{
			std::time_t t = std::chrono::system_clock::to_time_t(tp);
			std::tm tm_buf;
#ifdef _WIN32
			localtime_s(&tm_buf, &t);
#else
			localtime_r(&t, &tm_buf);
#endif
			return tm_buf.tm_wday;
		}
	} // time
} // r_utils