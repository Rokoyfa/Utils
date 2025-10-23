#pragma once
#include "logger/Logger.h"

/**
 * @file LoggerMacros.h
 * @brief Logging helper macros for easy and consistent logging.
 *
 * These macros provide a convenient way to log messages at various levels
 * using a pointer to a Logger instance. If the pointer is null, the macros
 * do nothing. Error macros allow specifying an ErrorType.
 *
 * The macros behave identically in both debug and release builds in this implementation,
 * but you could customize them to disable certain levels in release mode.
 */
#ifdef _DEBUG
/** Logs an informational message using the provided Logger pointer.
*  @param logger_ptr Pointer to a r_utils::logger::Logger instance.
*  @param message Message string to log.
*/
#define LOG_INFO(logger_ptr, message)				do { if (logger_ptr) { (logger_ptr)->info(message); } } while(0)
/** Logs a debug message using the provided Logger pointer.
*  @param logger_ptr Pointer to a r_utils::logger::Logger instance.
*  @param message Message string to log.
*/
#define LOG_DEBUG(logger_ptr, message)				do { if (logger_ptr) { (logger_ptr)->debug(message); } } while(0)
/** Logs a warning message using the provided Logger pointer.
*  @param logger_ptr Pointer to a r_utils::logger::Logger instance.
*  @param message Message string to log.
*/
#define LOG_WARN(logger_ptr, message)				do { if (logger_ptr) { (logger_ptr)->warn(message); } } while(0)
/** Logs an error message using the provided Logger pointer, with an optional ErrorType.
*  @param logger_ptr Pointer to a r_utils::logger::Logger instance.
*  @param message Error message string to log.
*  @param type Error type from r_utils::logger::ErrorType (default: UNKNOWN_ERROR)
*/
#define LOG_ERROR(logger_ptr, message, type)		do { if (logger_ptr) { (logger_ptr)->error(message, type); } } while(0)
/** Logs a general message using the provided Logger pointer.
*  @param logger_ptr Pointer to a r_utils::logger::Logger instance.
*  @param message Message string to log.
*/
#define LOG_LOG(logger_ptr, message)				do { if (logger_ptr) { (logger_ptr)->log(message); } } while(0)
#else
/** Release build version: identical to debug version but could be modified to disable some logs. */
#define LOG_INFO(logger_ptr, message)				do { if (logger_ptr) { (logger_ptr)->info(message); } } while(0)
/** Release build version: identical to debug version but could be modified to disable some logs. */
#define LOG_DEBUG(logger_ptr, message)				do { if (logger_ptr) { (logger_ptr)->debug(message); } } while(0)
/** Release build version: identical to debug version but could be modified to disable some logs. */
#define LOG_WARN(logger_ptr, message)				do { if (logger_ptr) { (logger_ptr)->warn(message); } } while(0)
/** Release build version: identical to debug version but could be modified to disable some logs. */
#define LOG_ERROR(logger_ptr, message, type)		do { if (logger_ptr) { (logger_ptr)->error(message, type); } } while(0)
/** Release build version: identical to debug version but could be modified to disable some logs. */
#define LOG_LOG(logger_ptr, message)				do { if (logger_ptr) { (logger_ptr)->log(message); } } while(0)
#endif // DEBUG
