#pragma once

#include <chrono>
#include <thread>
#include <functional>

namespace r_utils
{
    namespace time
    {
        /**
         * @class Timer
         * @brief A flexible timer for measuring time intervals.
         *
         * Supports multiple constructors for different time specifications,
         * start/stop mechanics, querying elapsed time, and reset functionality.
         */
        class Timer
        {
        public:
            /** Constructors for different time representations */
            Timer(const int time);                                       ///< Time in milliseconds
            Timer(const double time);                                    ///< Time in seconds
            Timer(const std::chrono::milliseconds& time);               ///< Time in milliseconds
            Timer(const std::chrono::seconds& time);                    ///< Time in seconds
            Timer(const std::chrono::minutes& time);                    ///< Time in minutes
            Timer(const std::chrono::hours& time);                      ///< Time in hours
            Timer(const std::chrono::steady_clock::duration& duration); ///< Arbitrary duration
            Timer(const std::chrono::steady_clock::time_point& endTime);///< End time point
            ~Timer();

            /** Starts the timer */
            void start();
            void startInThread();
            void startInThread(long long stopAfterMs);
            void startInThread(std::function<void()> fallback, long long callFallback = 0);
            /** Stops the timer */
            void stop();
            /** Resets the timer */
            void reset();
            /** Restart the timer (reset and start immediately). */
            void restart();

            /** Checks if the timer is currently running */
            [[nodiscard]] bool isRunning() const;

            /** Returns the elapsed time in milliseconds */
            [[nodiscard]] long long elapsedMilliseconds() const;
            /** Returns the elapsed time in seconds */
            [[nodiscard]] double elapsedSeconds() const;
            /** Returns the elapsed time in minutes */
            [[nodiscard]] double elapsedMinutes() const;
            /** Returns the elapsed time in hours */
            [[nodiscard]] double elapsedHours() const;
            /** Returns the elapsed time in days */
            [[nodiscard]] double elapsedDays() const;

        private:
            std::chrono::steady_clock::duration currentDuration() const;

            std::chrono::steady_clock::time_point __startTime__;
            std::chrono::steady_clock::time_point __endTime__;
            std::chrono::steady_clock::duration __duration__; ///< Stored duration if stopped
            bool __running__ = false;
			std::thread __thread__;
        };
    } // time
} // r_utils
