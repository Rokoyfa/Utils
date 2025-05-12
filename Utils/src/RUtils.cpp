#include "RUtils.h"
#include <iostream>

namespace r_utils
{
	RUtils::RUtils(const build& builder)
		: __useLogger__(builder.useLogger_),
		__useGUILogger__(builder.useGUILogger_),
		__isInitialized__(true)
	{
		if (__useLogger__)
		{
			if (__useGUILogger__) {
				std::cout << "Initializing RUtils with GUI Logger" << std::endl;
				__logger__ = r_utils::logger::Logger(true);
			}
			else {
				std::cout << "Initializing RUtils with Console Logger" << std::endl;
				__logger__ = r_utils::logger::Logger(false);
			}
		}
	}

	bool RUtils::isinitialized() const
	{
		return __isInitialized__;
	}

	r_utils::logger::Logger& RUtils::getLogger()
	{
		return __logger__;
	}

	RUtils& RUtils::operator=(RUtils& util)
	{
		__isInitialized__ = util.__isInitialized__;
		__useLogger__ = util.__useLogger__;
		__useGUILogger__ = util.__useGUILogger__;
		return *this;
	}

	RUtils::build::build() {}

	RUtils::build& RUtils::build::withLogger(bool withGUI)
	{
		useLogger_ = true;
		useGUILogger_ = withGUI;
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