#include "time/Timer.h"

namespace r_utils
{
	namespace time
	{
		Timer::Timer()
		{
		}
		Timer::Timer(const int time)
			: __duration__(std::chrono::milliseconds(time))
		{
		}
		Timer::Timer(const double time)
			: __duration__(std::chrono::milliseconds(static_cast<long long>(time * 1000.0)))
		{
		}
		Timer::Timer(const std::chrono::milliseconds& time)
			: __duration__(time)
		{
		}
		Timer::Timer(const std::chrono::seconds& time)
			: __duration__(time)
		{
		}
		Timer::Timer(const std::chrono::minutes& time)
			: __duration__(time)
		{
		}
		Timer::Timer(const std::chrono::hours& time)
			: __duration__(time)
		{
		}
		Timer::Timer(const std::chrono::steady_clock::duration& duration)
			: __duration__(duration)
		{
		}
		Timer::Timer(const std::chrono::steady_clock::time_point& endTime)
			: __endTime__(endTime), __duration__(endTime - std::chrono::steady_clock::now())
		{
		}

		Timer::~Timer()
		{}

		void Timer::start()
		{
			std::lock_guard<std::mutex> lock(__mtx__);
			if (__running__) return;
			
			__startTime__ = std::chrono::steady_clock::now();
			__running__ = true;
		}

		void Timer::startInThread()
		{
			std::lock_guard<std::mutex> lock(__mtx__);
			if (__running__) return;

			start();
			__thread__ = std::jthread([this]() {
				auto start = std::chrono::steady_clock::now();
				while (__running__) {
					std::this_thread::sleep_for(std::chrono::seconds(1));
				}
				stop();
			});
		}

		void Timer::startInThread(long long stopAfterMs)
		{
			std::lock_guard<std::mutex> lock(__mtx__);
			if (__running__) return;

			start();
			__thread__ = std::jthread([this, stopAfterMs]() 
			{
				auto start = std::chrono::steady_clock::now();
				while (__running__ && std::chrono::steady_clock::now() - start < std::chrono::milliseconds(stopAfterMs)) 
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
				}
				this->stop();
			});
		}

		void Timer::startInThread(std::function<void()> fallback, long long callFallback)
		{
			std::lock_guard<std::mutex> lock(__mtx__);
			if (__running__) return;

			start();
			if (callFallback > 0)
			{
				__thread__ = std::jthread([this, fallback, callFallback]() 
				{
					auto start = std::chrono::steady_clock::now();
					std::this_thread::sleep_for(std::chrono::milliseconds(callFallback));
					if (__running__ && std::chrono::steady_clock::now() - start >= std::chrono::milliseconds(callFallback))
					{
						fallback();
					}
				});
			}
		}

		void Timer::stop()
		{
			std::lock_guard<std::mutex> lock(__mtx__);
			if (!__running__) return;
			__endTime__ = std::chrono::steady_clock::now();
			__duration__ += (__endTime__ - __startTime__);
			__running__ = false;
		}	

		void Timer::reset()
		{
			std::lock_guard<std::mutex> lock(__mtx__);
			__duration__ = std::chrono::steady_clock::duration::zero();
			__running__ = false;
		}

		void Timer::restart()
		{
			std::lock_guard<std::mutex> lock(__mtx__);
			__duration__ = std::chrono::steady_clock::duration::zero();
			__startTime__ = std::chrono::steady_clock::now();
			__running__ = true;
		}



		bool Timer::isRunning() const
		{
			return __running__;
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
			return __running__
				? __duration__ + (std::chrono::steady_clock::now() - __startTime__)
				: __duration__;
		}

	} // time
} // r_utils