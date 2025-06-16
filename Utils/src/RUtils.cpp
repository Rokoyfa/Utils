#include "RUtils.h"
#include <iostream>

#include "logger/LoggerMakro.h"

namespace r_utils
{
	RUtils::RUtils(const build& builder)
		: __useLogger__(builder.__useLogger__),
		__isInitialized__(true)
	{
		if (__useLogger__)
		{
			__logger__ = std::make_unique<r_utils::logger::Logger>();
			__app__ = std::make_unique<r_utils::gui::Application>(__logger__.get());
			LOG_DEBUG(__logger__, "RUtils initialized with Console Logger.");
			
		}
	}

	bool RUtils::isinitialized() const
	{
		return __isInitialized__;
	}

	r_utils::gui::Application* RUtils::getApplication() const
	{
		return __app__.get();
	}

	r_utils::logger::Logger* RUtils::getLogger() const
	{
		return __logger__.get();
	}

	RUtils& RUtils::operator=(RUtils& util)
	{
		__isInitialized__ = util.__isInitialized__;
		__useLogger__ = util.__useLogger__;
		return *this;
	}

	RUtils::build::build() {}

	RUtils::build& RUtils::build::withLogger()
	{
		__useLogger__ = true;
		return *this;
	}

	RUtils RUtils::build::initialize()
	{
		return RUtils(*this);
	}

	RUtils::build RUtils::create()
	{
		return build();
	}


}