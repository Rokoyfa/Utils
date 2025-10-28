#pragma once

#include "exception/ExceptionInclude.h"

namespace r_utils
{
	namespace exception
	{
		DEFINE_EXCEPTION(IndexOutOfRangeException);
		DEFINE_EXCEPTION(NullPointerException);
		DEFINE_EXCEPTION(InvalidArgumentException);
		DEFINE_EXCEPTION(IllegalStateException);
		DEFINE_EXCEPTION(UnsupportedOperationException);
	} // exception
} // r_utils