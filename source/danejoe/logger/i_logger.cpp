#include <sstream>

#include "danejoe/logger/i_logger.hpp"
#include "danejoe/common/process_util.hpp"
#include "danejoe/common/time_util.hpp"

DaneJoe::ILogger::ILogger() {}

DaneJoe::ILogger::ILogger(LoggerConfig config) : m_config(config) {}

std::string DaneJoe::ILogger::to_string(LogLevel level)
{
    std::string log_level_str = "UNKNOWN";
    switch (level)
    {
    case LogLevel::TRACE:log_level_str = "TRACE";break;
    case LogLevel::DEBUG:log_level_str = "DEBUG";break;
    case LogLevel::INFO: log_level_str = "INFO";break;
    case LogLevel::WARN: log_level_str = "WARN";break;
    case LogLevel::ERROR:log_level_str = "ERROR";break;
    case LogLevel::FATAL:log_level_str = "FATAL";break;
    default: break;
    }
    return log_level_str;
}

std::string DaneJoe::ILogger::to_string(const std::thread::id& thread_id)
{
    std::ostringstream oss;
    oss << thread_id;
    return oss.str();
}

DaneJoe::ILogger::LogLevel DaneJoe::ILogger::to_log_level(std::string level_str)
{
    LogLevel level = LogLevel::NONE;
    if (level_str == "TRACE")
    {
        level = LogLevel::TRACE;
    }
    else if (level_str == "DEBUG")
    {
        level = LogLevel::DEBUG;
    }
    else if (level_str == "INFO")
    {
        level = LogLevel::INFO;
    }
    else if (level_str == "WARN")
    {
        level = LogLevel::WARN;
    }
    else if (level_str == "ERROR")
    {
        level = LogLevel::ERROR;
    }
    else if (level_str == "FATAL")
    {
        level = LogLevel::FATAL;
    }
    return level;
}

void DaneJoe::ILogger::set_config(const LoggerConfig& config)
{
    m_config = config;
}

void DaneJoe::ILogger::set_output_settings(const LogOutputSetting& settings)
{
    m_output_setting = settings;
}

int DaneJoe::ILogger::get_pid()
{
    return ProcessUtil::get_pid();
}

std::string DaneJoe::ILogger::get_header(LogLevel level,
    const std::string& module,
    const std::string& log_info,
    const std::string& file_name,
    const std::string& function_name,
    int line_num,
    int process_id,
    const std::string& thread_id)
{
    std::string time_str = DANEJOE_NOW_TIME_STR;
    std::string header;
    if (m_output_setting.enable_time)
        header += std::format("[{}] ", time_str);
    if (m_output_setting.enable_level)
        header += std::format("[{}] ", to_string(level));
    if (m_output_setting.enable_module)
        header += std::format("[{}] ", module);
    if (m_output_setting.enable_file_name && file_name != "")
        header += std::format("[{}] ", file_name);
    if (m_output_setting.enable_function_name && function_name != "")
        header += std::format("[{}] ", function_name);
    if (m_output_setting.enable_line_num && line_num != -1)
        header += std::format("[{}] ", line_num);
    if (m_output_setting.enable_proceed_id && process_id != -1)
        header += std::format("[{}] ", process_id);
    if (m_output_setting.enable_thread_id && thread_id != "")
        header += std::format("[{}] ", thread_id);

    return header;
}