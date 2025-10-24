#include "time/Timer.h"
#include <algorithm>

namespace r_utils
{
    namespace time
    {
        Timer::Timer(const int time) : __duration__(std::chrono::milliseconds(time)) {}
        Timer::Timer(const double time) : __duration__(std::chrono::milliseconds(static_cast<long long>(time * 1000.0))) {}
        Timer::Timer(const std::chrono::milliseconds& time) : __duration__(time) {}
        Timer::Timer(const std::chrono::seconds& time) : __duration__(time) {}
        Timer::Timer(const std::chrono::minutes& time) : __duration__(time) {}
        Timer::Timer(const std::chrono::hours& time) : __duration__(time) {}
        Timer::Timer(const std::chrono::steady_clock::duration& duration) : __duration__(duration) {}
        Timer::Timer(const std::chrono::steady_clock::time_point& endTime)
            : __endTime__(endTime), __duration__(endTime - std::chrono::steady_clock::now()) {
        }

        Timer::~Timer()
        {
            stopThread(); // ensure thread exits and is joined
        }

        void Timer::start()
        {
            std::lock_guard<std::mutex> lock(__mtx__);
            if (__running__) return;
            __startTime__ = std::chrono::steady_clock::now();
            __running__.store(true, std::memory_order_release);
        }

        void Timer::startInThread()
        {
            stopThread();
            start();

            __token__ = std::make_shared<std::atomic<bool>>(true);

            __thread__ = std::make_unique<std::jthread>([token = __token__]() mutable {
                while (token->load(std::memory_order_acquire)) {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
                // thread ends cleanly
                });
        }

        void Timer::startInThread(long long stopAfterMs)
        {
            stopThread();
            start();

            __token__ = std::make_shared<std::atomic<bool>>(true);

            __thread__ = std::make_unique<std::jthread>([token = __token__, stopAfterMs]() mutable {
                auto startPoint = std::chrono::steady_clock::now();
                while (token->load(std::memory_order_acquire) &&
                    std::chrono::steady_clock::now() - startPoint < std::chrono::milliseconds(stopAfterMs))
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                }
                token->store(false, std::memory_order_release);
                });
        }

        void Timer::startInThread(std::function<void()> callback, long long callFallback)
        {
            if (!callback) return;
            stopThread();
            start();

            __token__ = std::make_shared<std::atomic<bool>>(true);

            __thread__ = std::make_unique<std::jthread>([token = __token__, callback, callFallback]() mutable {
                if (callFallback > 0) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(callFallback));
                    if (token->load(std::memory_order_acquire)) {
                        callback();
                    }
                }
                else {
                    if (token->load(std::memory_order_acquire)) callback();
                }
                token->store(false, std::memory_order_release);
                });
        }

        void Timer::startPeriodic(std::function<void()> callback, long long intervalMs)
        {
            if (!callback) return;
            stopThread();
            start();

            __token__ = std::make_shared<std::atomic<bool>>(true);

            __thread__ = std::make_unique<std::jthread>([token = __token__, callback, intervalMs]() mutable {
                while (token->load(std::memory_order_acquire)) {
                    auto start = std::chrono::steady_clock::now();
                    callback();

                    auto end = std::chrono::steady_clock::now();
                    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                    auto sleepTime = std::max(intervalMs - elapsed, 0LL);

                    for (long long slept = 0; slept < sleepTime && token->load(std::memory_order_acquire); slept += 50) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(std::min(50LL, sleepTime - slept)));
                    }
                }
                token->store(false, std::memory_order_release);
                });
        }

        void Timer::stop()
        {
            std::lock_guard<std::mutex> lock(__mtx__);
            if (!__running__) return;
            __endTime__ = std::chrono::steady_clock::now();
            __duration__ += (__endTime__ - __startTime__);
            __running__.store(false, std::memory_order_release);

            if (__token__) __token__->store(false, std::memory_order_release);
        }

        void Timer::reset()
        {
            stopThread();
            std::lock_guard<std::mutex> lock(__mtx__);
            __duration__ = std::chrono::steady_clock::duration::zero();
            __running__.store(false, std::memory_order_release);
        }

        void Timer::restart()
        {
            stopThread();
            std::lock_guard<std::mutex> lock(__mtx__);
            __duration__ = std::chrono::steady_clock::duration::zero();
            __startTime__ = std::chrono::steady_clock::now();
            __running__.store(true, std::memory_order_release);
        }

        bool Timer::isRunning() const
        {
            return __running__.load(std::memory_order_acquire);
        }

        long long Timer::elapsedMilliseconds() const
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(currentDuration()).count();
        }

        double Timer::elapsedSeconds() const
        {
            return std::chrono::duration_cast<std::chrono::duration<double>>(currentDuration()).count();
        }

        double Timer::elapsedMinutes() const
        {
            return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<60>>>(currentDuration()).count();
        }

        double Timer::elapsedHours() const
        {
            return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<3600>>>(currentDuration()).count();
        }

        double Timer::elapsedDays() const
        {
            return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<86400>>>(currentDuration()).count();
        }

        std::chrono::steady_clock::duration Timer::currentDuration() const
        {
            std::lock_guard<std::mutex> lock(__mtx__);
            return __running__.load(std::memory_order_acquire)
                ? __duration__ + (std::chrono::steady_clock::now() - __startTime__)
                : __duration__;
        }

        void Timer::stopThread()
        {
            if (__token__) {
                __token__->store(false, std::memory_order_release);
            }

            if (__thread__ && __thread__->joinable()) {
                __thread__->join();
                __thread__.reset();
            }

            __token__.reset();
        }
    } // time
} // r_utils