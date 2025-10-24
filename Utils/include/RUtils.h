#pragma once

#include <memory>
#include "logger/Logger.h"
#include "gui/Application.h"

namespace r_utils
{
    /**
     * @class RUtils
     * @brief Core utility class for initializing logging and GUI components.
     *
     * Provides a builder-style interface to configure which components to initialize
     * (e.g., Logger, Application) and accessors to retrieve them.
     */
    class RUtils
    {
    public:
        RUtils() = delete;
        RUtils(const RUtils&) = delete;

        /**
         * @class build
         * @brief Builder class to configure and initialize RUtils.
         */
        class build
        {
        public:
            /** Default constructor for the builder. */
            build();

            /**
             * @brief Configures the builder to initialize a Logger.
             * @return Reference to the builder for chaining.
             */
            build& withLogger();

            /**
             * @brief Finalizes the build and returns an initialized RUtils instance.
             * @return Initialized RUtils object.
             */
            RUtils initialize();

        private:
            bool __useLogger__ = false;
            friend class RUtils;
        };

        /** @brief Creates a new builder instance. */
        static build create();

        /** @brief Checks whether RUtils has been initialized. */
        [[nodiscard]] bool isinitialized() const;

        /** @brief Returns a pointer to the Logger, if initialized. */
        r_utils::logger::Logger* getLogger() const;
        /** @brief Returns a pointer to the Application (GUI), if initialized. */
        r_utils::gui::Application* getApplication() const;

        /** @brief Assignment operator. */
        RUtils& operator=(RUtils& util);

    private:
        /** @brief Private constructor called by the builder. */
        RUtils(const build& builder);

        std::unique_ptr<r_utils::logger::Logger> __logger__;
        std::unique_ptr<r_utils::gui::Application> __app__;

        bool __useLogger__ = false;
        bool __isInitialized__ = false;
    };
} // r_utils
