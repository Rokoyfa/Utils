#pragma once

#include <chrono>
#include <thread>
#include <functional>
#include <atomic>
#include <mutex>

namespace r_utils
{
    namespace time
    {
        /**
         * @class Timer
         * @brief A flexible, thread-safe timer for measuring time intervals and timeouts.
         *
         */
        class Timer
        {
        public:
            /** Constructors for different time representations */
            Timer();
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

            /**
            * @brief Starts the timer asynchronously in a managed thread.
            *
            * This method launches the timer in a separate `std::jthread` without blocking
            * the main execution flow. The timer will begin counting time and must be
            * stopped manually using `stop()`.
            *
            * @note The thread is automatically joined on destruction (`std::jthread`).
            *       This prevents detached-thread issues and ensures clean resource management.
            * @threadsafe
            */
            void startInThread();
            /**
            * @brief Starts the timer asynchronously and automatically stops after a specific duration.
            *
            * This method launches the timer in a managed thread and stops it automatically
            * after the specified duration (`stopAfterMs` milliseconds). The main thread
            * continues execution without waiting.
            *
            * @param stopAfterMs The time in milliseconds after which the timer will automatically stop.
            *
            * @note Useful for timeout or auto-expiration scenarios.
            * @threadsafe
            */
            void startInThread(long long stopAfterMs);
            /**
            * @brief Starts the timer asynchronously with a callback that triggers after a delay.
            *
            * Launches the timer in a separate `std::jthread` and executes a user-defined callback
            * (`fallback`) after a specified delay (`callFallback` milliseconds). The callback
            * executes only if the timer is still running at that time.
            *
            * @param fallback The function to execute after the specified delay.
            * @param callFallback The delay (in milliseconds) after which to call the fallback function.
            *
            * @note Ideal for timeout or watchdog-style behavior.
            * @warning The callback runs in a separate thread — ensure proper synchronization
            *          when accessing shared data.
            * @threadsafe
            */
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
            std::chrono::steady_clock::duration __duration__;
			std::jthread __thread__;
            mutable std::mutex __mtx__;
            std::atomic<bool> __running__{ false };
        };
    } // time
} // r_utils
