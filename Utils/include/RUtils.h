#pragma once

#include <memory>
#include "logger/Logger.h"
#include "gui/Application.h"

namespace r_utils
{
	class RUtils
	{
	public:
		RUtils() = delete;
		RUtils(const RUtils&) = delete;

		class build
		{
		public:
			build();
			build& withLogger();
			RUtils initialize();
		private:
			bool __useLogger__ = false;
			friend class RUtils;
		};

		static build create();

		[[nodiscard]] bool isinitialized() const;
		r_utils::logger::Logger* getLogger() const;
		r_utils::gui::Application* getApplication() const;

		RUtils& operator=(RUtils& util);
	private:
		RUtils(const build& builder);
		std::unique_ptr<r_utils::logger::Logger> __logger__;
		std::unique_ptr<r_utils::gui::Application> __app__;

		bool __useLogger__ = false;
		bool __isInitialized__ = false;
	};
} // r_utils