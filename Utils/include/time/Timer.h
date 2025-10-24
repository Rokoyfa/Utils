#pragma once

#include <chrono>
#include <thread>
#include <functional>
#include <atomic>
#include <mutex>
#include <memory>

namespace r_utils
{
    namespace time
    {
        /**
         * @class Timer
         * @brief A flexible, thread-safe timer for measuring time intervals and timeouts.
         *
         * Threaded operations use a shared cancellation token (std::shared_ptr<std::atomic<bool>>)
         * so threads do not access the Timer instance after it was destroyed.
         */
        class Timer
        {
        public:
            Timer() = default;
            Timer(const int time);                                       ///< Time in milliseconds
            Timer(const double time);                                    ///< Time in seconds
            Timer(const std::chrono::milliseconds& time);               ///< Time in milliseconds
            Timer(const std::chrono::seconds& time);                    ///< Time in seconds
            Timer(const std::chrono::minutes& time);                    ///< Time in minutes
            Timer(const std::chrono::hours& time);                      ///< Time in hours
            Timer(const std::chrono::steady_clock::duration& duration); ///< Arbitrary duration
            Timer(const std::chrono::steady_clock::time_point& endTime);///< End time point
            ~Timer();

            void start();

            /**
             * Start the timer and create a managed thread. The thread will run until the
             * timer is stopped (or token is canceled). The thread does NOT touch `this`.
             */
            void startInThread();

            /**
             * Start timer and run a managed thread which automatically stops after stopAfterMs milliseconds.
             */
            void startInThread(long long stopAfterMs);

            /**
             * Start timer and run a managed thread which will call `callback` once after callFallback ms.
             * The callback is executed only if the token is still active (i.e. the timer wasn't stopped).
             */
            void startInThread(std::function<void()> callback, long long callFallback = 0);

            /**
             * Start timer and run callback periodically every intervalMs milliseconds until stopped.
             */
            void startPeriodic(std::function<void()> callback, long long intervalMs);

            /** Stop the timer (accumulates elapsed duration). */
            void stop();

            /** Reset accumulated time and stop any running thread. */
            void reset();

            /** Restart the timer from zero (stops threads first). */
            void restart();

            [[nodiscard]] bool isRunning() const;

            [[nodiscard]] long long elapsedMilliseconds() const;
            [[nodiscard]] double elapsedSeconds() const;
            [[nodiscard]] double elapsedMinutes() const;
            [[nodiscard]] double elapsedHours() const;
            [[nodiscard]] double elapsedDays() const;

        private:
            std::chrono::steady_clock::duration currentDuration() const;
            void stopThread();

            std::chrono::steady_clock::time_point __startTime__;
            std::chrono::steady_clock::time_point __endTime__;
            std::chrono::steady_clock::duration __duration__{ std::chrono::steady_clock::duration::zero() };

            std::unique_ptr<std::jthread> __thread__{ nullptr };
            std::shared_ptr<std::atomic<bool>> __token__{ nullptr };

            mutable std::mutex __mtx__;
            std::atomic<bool> __running__{ false };
        };
    } // time
} // r_utils
