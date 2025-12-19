/**
 * @file logger_config.hpp
 * @brief 日志配置头文件
 * @author DaneJoe001
 * @version 0.2.0
 * @date 2025-12-17
 */
#pragma once

#include <string>

#include "danejoe/common/enum/enum_convert.hpp"

/**
 * @namespace DaneJoe
 * @brief DaneJoe命名空间
 */
namespace DaneJoe
{
    /**
     * @enum LogLevel
     * @brief 日志级别枚举
     */
    enum class LogLevel
    {
        /// @brief 跟踪级别
        TRACE,
        /// @brief 调试级别
        DEBUG,
        /// @brief 信息级别
        INFO,
        /// @brief 警告级别
        WARN,
        /// @brief 错误级别
        ERROR,
        /// @brief 致命错误级别
        FATAL,
        /// @brief 未知级别
        Unknown,
        /// @brief 无输出级别
        NONE
    };

    /**
     * @brief 将日志级别转换为字符串（调试用）
     * @param level 日志级别
     * @return 对应的枚举字符串
     */
    std::string to_string(LogLevel level);
    /**
     * @brief 从字符串转换为日志级别
     * @param enum_string 由 ENUM_TO_STRING 生成的枚举字符串
     * @return 对应的枚举值，未知时返回 LogLevel::Unknown
     */
    template<>
    LogLevel enum_cast<LogLevel>(const std::string& enum_string);
    /**
     * @struct LoggerConfig
     * @brief 日志配置结构体
     */
    struct LoggerConfig
    {
        /// @brief 日志名称
        std::string log_name = "default";
        /// @brief 日志文件路径
        std::string log_path = "./log/default.log";
        /// @brief 控制台日志级别
        LogLevel console_level = LogLevel::TRACE;
        /// @brief 文件日志级别
        LogLevel file_level = LogLevel::TRACE;
        /// @brief 是否启用控制台日志
        bool enable_console = true;
        /// @brief 是否启用文件日志
        bool enable_file = true;
        /// @brief 是否启用异步日志
        bool enable_async = true;
        /// @brief 最大文件大小
        std::size_t max_file_size = 10 * 1024 * 1024;
        /// @brief 最大文件数量
        std::size_t max_file_num = 5;
        /// @brief 是否使用按天分割日志
        bool use_daily_log = false;
        /// @brief 是否启用堆栈回溯
        bool enable_backtrace = false;
        /// @brief 堆栈回溯大小
        std::size_t backtrace_size = 0;
    };
    /**
     * @struct LogOutputSetting
     * @brief 日志输出设置结构体
     */
    struct LogOutputSetting
    {
        /// @brief 是否启用时间
        bool enable_time = true;
        /// @brief 是否启用日志级别
        bool enable_level = true;
        /// @brief 是否启用模块名称
        bool enable_module = true;
        /// @brief 是否启用文件名称
        bool enable_file_name = false;
        /// @brief 是否启用函数名称
        bool enable_function_name = false;
        /// @brief 是否启用行号
        bool enable_line_num = false;
        /// @brief 是否启用线程ID
        bool enable_thread_id = false;
        /// @brief 是否启用进程ID
        bool enable_proceed_id = false;
    };
}
