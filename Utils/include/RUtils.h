#pragma once

#include "logger/Logger.h"

namespace r_utils
{
	class RUtils
	{
	public:
		RUtils() = delete;

		class build
		{
		public:
			build();
			build& withLogger(bool withGUI = true);
			RUtils initialize();
		private:
			bool useLogger_ = false;
			bool useGUILogger_ = false;
			friend class RUtils;
		};

		static build create();

		[[nodiscard]] bool isinitialized() const;
		r_utils::logger::Logger& getLogger();

		RUtils& operator=(RUtils& util);
	private:
		RUtils(const build& builder);
		r_utils::logger::Logger __logger__;

		bool __useLogger__ = false;
		bool __useGUILogger__ = false;
		bool __isInitialized__ = false;
	};
}