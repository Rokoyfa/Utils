#pragma once

#define DEFINE_EXCEPTION(name) \
class name : public r_utils::exception::Exception { \
public: \
    explicit name(const std::string& message) : Exception(#name, message) {} \
    explicit name(const char* message) : Exception(#name, message) {} \
    explicit name(const std::string_view& message) : Exception(#name, message) {} \
    explicit name(const std::exception& exception) : Exception(#name, exception) {} \
};