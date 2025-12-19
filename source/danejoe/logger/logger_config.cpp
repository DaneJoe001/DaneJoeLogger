#include "danejoe/logger/logger_config.hpp"

std::string DaneJoe::to_string(LogLevel level)
{
    switch (level)
    {
    case LogLevel::TRACE:
        return ENUM_TO_STRING(LogLevel::TRACE);
    case LogLevel::DEBUG:
        return ENUM_TO_STRING(LogLevel::DEBUG);
    case LogLevel::INFO:
        return ENUM_TO_STRING(LogLevel::INFO);
    case LogLevel::WARN:
        return ENUM_TO_STRING(LogLevel::WARN);
    case LogLevel::ERROR:
        return ENUM_TO_STRING(LogLevel::ERROR);
    case LogLevel::FATAL:
        return ENUM_TO_STRING(LogLevel::FATAL);
    case LogLevel::NONE:
        return ENUM_TO_STRING(LogLevel::NONE);
    case LogLevel::Unknown:
    default:
        return ENUM_TO_STRING(LogLevel::Unknown);
    }
}

template<>
DaneJoe::LogLevel DaneJoe::enum_cast<DaneJoe::LogLevel>(const std::string& enum_string)
{
    if (enum_string == ENUM_TO_STRING(LogLevel::TRACE))
    {
        return LogLevel::TRACE;
    }
    else if (enum_string == ENUM_TO_STRING(LogLevel::DEBUG))
    {
        return LogLevel::DEBUG;
    }
    else if (enum_string == ENUM_TO_STRING(LogLevel::INFO))
    {
        return LogLevel::INFO;
    }
    else if (enum_string == ENUM_TO_STRING(LogLevel::WARN))
    {
        return LogLevel::WARN;
    }
    else if (enum_string == ENUM_TO_STRING(LogLevel::ERROR))
    {
        return LogLevel::ERROR;
    }
    else if (enum_string == ENUM_TO_STRING(LogLevel::FATAL))
    {
        return LogLevel::FATAL;
    }
    else if (enum_string == ENUM_TO_STRING(LogLevel::NONE))
    {
        return LogLevel::NONE;
    }
    else if (enum_string == ENUM_TO_STRING(LogLevel::Unknown))
    {
        return LogLevel::Unknown;
    }
    return LogLevel::Unknown;
}
