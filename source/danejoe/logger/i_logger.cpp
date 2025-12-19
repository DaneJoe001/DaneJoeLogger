#include <sstream>
#include <chrono>

#include "danejoe/logger/i_logger.hpp"
#include "danejoe/common/system/system_info.hpp"

DaneJoe::ILogger::ILogger() {}

DaneJoe::ILogger::ILogger(LoggerConfig config) : m_config(config) {}

std::string DaneJoe::ILogger::to_string(LogLevel level)
{
    return DaneJoe::to_string(level);
}

std::string DaneJoe::ILogger::to_string(const std::thread::id& thread_id)
{
    std::ostringstream oss;
    oss << thread_id;
    return oss.str();
}

DaneJoe::LogLevel DaneJoe::ILogger::to_log_level(std::string level_str)
{
    LogLevel level = LogLevel::Unknown;
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
    else if (level_str == "NONE")
    {
        level = LogLevel::NONE;
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
    return get_process_id();
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
    std::time_t raw_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm time_info;
    std::tm* time_info_ptr = nullptr;
#if defined(_WIN32)
    localtime_s(&time_info, &raw_time_t); // Windows
    time_info_ptr = &time_info;
#elif defined(__linux__)
    localtime_r(&raw_time_t, &time_info); // Linux
    time_info_ptr = &time_info;
#elif defined(__APPLE__)
    localtime_r(&raw_time_t, &time_info); // macOS
    time_info_ptr = &time_info;
#else
    time_info_ptr = std::localtime(&raw_time_t);
#endif
    std::ostringstream oss;
    oss << std::put_time(time_info_ptr, "%Y-%m-%d %H:%M:%S");
    std::string time_str = oss.str();
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
