#pragma once
#include "logger/Logger.h"

#ifdef _DEBUG
#define LOG_INFO(logger_ptr, message)				do { if (logger_ptr) { (logger_ptr)->info(message); } } while(0)
#define LOG_DEBUG(logger_ptr, message)				do { if (logger_ptr) { (logger_ptr)->debug(message); } } while(0)
#define LOG_WARN(logger_ptr, message)				do { if (logger_ptr) { (logger_ptr)->warn(message); } } while(0)
#define LOG_ERROR(logger_ptr, message, type)		do { if (logger_ptr) { (logger_ptr)->error(message, type); } } while(0)
#define LOG_ERROR(logger_ptr, message)				do { if (logger_ptr) { (logger_ptr)->error(message); } } while(0)
#define LOG_LOG(logger_ptr, message)				do { if (logger_ptr) { (logger_ptr)->log(message); } } while(0)
#else
#define LOG_INFO(logger_ptr, message)				do { if (logger_ptr) { (logger_ptr)->info(message); } } while(0)
#define LOG_DEBUG(logger_ptr, message)				do { if (logger_ptr) { (logger_ptr)->debug(message); } } while(0)
#define LOG_WARN(logger_ptr, message)				do { if (logger_ptr) { (logger_ptr)->warn(message); } } while(0)
#define LOG_ERROR(logger_ptr, message, type)		do { if (logger_ptr) { (logger_ptr)->error(message, type); } } while(0)
#define LOG_ERROR(logger_ptr, message)				do { if (logger_ptr) { (logger_ptr)->error(message); } } while(0)
#define LOG_LOG(logger_ptr, message)				do { if (logger_ptr) { (logger_ptr)->log(message); } } while(0)
#endif // DEBUG
