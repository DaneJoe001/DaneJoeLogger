/**
 * @file i_logger.hpp
 * @brief 日志接口类头文件
 * @details 日志接口类
 * @author DaneJoe001
 * @version 0.2.0
 * @date 2025-12-17
 */
#pragma once

#include <format>
#include <string>
#include <thread>
#include <memory>

#include "danejoe/logger/logger_config.hpp"

 /**
  * @namespace DaneJoe
  * @brief DaneJoe命名空间
  */
namespace DaneJoe
{
    /**
     * @class ILogger
     * @brief 日志接口类
     */
    class ILogger
    {
    public:
        /**
         * @brief 构造函数
         */
        ILogger();
        /**
         * @brief 构造函数
         * @param config 日志配置
         */
        ILogger(LoggerConfig config);
        /**
         * @brief 跟踪级别日志
         * @tparam Args 可变参数类型
         * @param module 模块名称
         * @param file_name 文件名称
         * @param function_name 函数名称
         * @param line_num 行号
         * @param fmt 格式化字符串
         * @param args 可变参数
         */
        template<typename... Args>
        void trace(const std::string& module,
            const std::string& file_name,
            const std::string& function_name,
            int line_num,
            std::format_string<Args...> fmt,
            Args&&... args)
        {
            std::string log_info = std::format(fmt, std::forward<Args>(args)...);
            log_msg(LogLevel::TRACE,
                module,
                log_info,
                file_name,
                function_name,
                line_num,
                get_pid(),
                to_string(std::this_thread::get_id()));
        }
        /**
         * @brief 调试级别日志
         * @tparam Args 可变参数类型
         * @param module 模块名称
         * @param file_name 文件名称
         * @param function_name 函数名称
         * @param line_num 行号
         * @param fmt 格式化字符串
         * @param args 可变参数
         */
        template<typename... Args>
        void debug(const std::string& module,
            const std::string& file_name,
            const std::string& function_name,
            int line_num,
            std::format_string<Args...> fmt,
            Args&&... args)
        {
            std::string log_info = std::format(fmt, std::forward<Args>(args)...);
            log_msg(LogLevel::DEBUG,
                module,
                log_info,
                file_name,
                function_name,
                line_num,
                get_pid(),
                to_string(std::this_thread::get_id()));
        }
        /**
         * @brief 信息级别日志
         * @tparam Args 可变参数类型
         * @param module 模块名称
         * @param file_name 文件名称
         * @param function_name 函数名称
         * @param line_num 行号
         * @param fmt 格式化字符串
         * @param args 可变参数
         */
        template<typename... Args>
        void info(const std::string& module,
            const std::string& file_name,
            const std::string& function_name,
            int line_num,
            std::format_string<Args...> fmt,
            Args&&... args)
        {
            std::string log_info = std::format(fmt, std::forward<Args>(args)...);
            log_msg(LogLevel::INFO,
                module,
                log_info,
                file_name,
                function_name,
                line_num,
                get_pid(),
                to_string(std::this_thread::get_id()));
        }
        /**
         * @brief 警告级别日志
         * @tparam Args 可变参数类型
         * @param module 模块名称
         * @param file_name 文件名称
         * @param function_name 函数名称
         * @param line_num 行号
         * @param fmt 格式化字符串
         * @param args 可变参数
          */
        template<typename... Args>
        void warn(const std::string& module,
            const std::string& file_name,
            const std::string& function_name,
            int line_num,
            std::format_string<Args...> fmt,
            Args&&... args)
        {
            std::string log_info = std::format(fmt, std::forward<Args>(args)...);
            log_msg(LogLevel::WARN,
                module,
                log_info,
                file_name,
                function_name,
                line_num,
                get_pid(),
                to_string(std::this_thread::get_id()));
        }
        /**
         * @brief 错误级别日志
         * @tparam Args 可变参数类型
         * @param module 模块名称
         * @param file_name 文件名称
         * @param function_name 函数名称
         * @param line_num 行号
         * @param fmt 格式化字符串
         * @param args 可变参数
         */
        template<typename... Args>
        void error(const std::string& module,
            const std::string& file_name,
            const std::string& function_name,
            int line_num,
            std::format_string<Args...> fmt,
            Args&&... args)
        {
            std::string log_info = std::format(fmt, std::forward<Args>(args)...);
            log_msg(LogLevel::ERROR,
                module,
                log_info,
                file_name,
                function_name,
                line_num,
                get_pid(),
                to_string(std::this_thread::get_id()));
        }
        /**
         * @brief 致命错误级别日志
         * @tparam Args 可变参数类型
         * @param module 模块名称
         * @param file_name 文件名称
         * @param function_name 函数名称
         * @param line_num 行号
         * @param fmt 格式化字符串
         * @param args 可变参数
         */
        template<typename... Args>
        void fatal(const std::string& module,
            const std::string& file_name,
            const std::string& function_name,
            int line_num,
            std::format_string<Args...> fmt,
            Args&&... args)
        {
            std::string log_info = std::format(fmt, std::forward<Args>(args)...);
            log_msg(LogLevel::FATAL,
                module,
                log_info,
                file_name,
                function_name,
                line_num,
                get_pid(),
                to_string(std::this_thread::get_id()));
        }
        /**
         * @brief 析构函数
         */
        virtual ~ILogger() = default;
        /**
         * @brief 将日志级别转换为字符串
         * @param level 日志级别
         * @return 日志级别字符串
         */
        std::string to_string(LogLevel level);
        /**
         * @brief 将字符串转换为日志级别
         * @param level_str 日志级别字符串
         * @return 日志级别
         */
        LogLevel to_log_level(std::string level_str);
        /**
         * @brief 设置日志输出设置
         * @param settings 日志输出设置
         */
        void set_output_settings(const LogOutputSetting& settings);
        /**
         * @brief 设置日志配置
         * @param config 日志配置
         */
        void set_config(const LoggerConfig& config);
        /**
         * @brief 获取进程ID
         * @return 进程ID
         */
        static int get_pid();
        /**
         * @brief 将线程ID转换为字符串
         * @param thread_id 线程ID
         * @return 线程ID字符串
         */
        std::string to_string(const std::thread::id& thread_id);
        /**
         * @brief 获取日志头
         * @param level 日志级别
         * @param module 模块名称
         * @param log_info 日志信息
         * @param file_name 文件名称
         * @param function_name 函数名称
         * @param line_num 行号
         * @param process_id 进程ID
         * @param thread_id 线程ID
         * @return 日志头
         */
        std::string get_header(LogLevel level,
            const std::string& module,
            const std::string& log_info,
            const std::string& file_name = "",
            const std::string& function_name = "",
            int line_num = -1,
            int process_id = -1,
            const std::string& thread_id = "");
    protected:
        /**
         * @brief 日志消息
         * @param level 日志级别
         * @param module 模块名称
         * @param log_info 日志信息
         * @param file_name 文件名称
         * @param function_name 函数名称
         * @param line_num 行号
         * @param process_id 进程ID
         * @param thread_id 线程ID
         */
        virtual void log_msg(LogLevel level,
            const std::string& module,
            const std::string& log_info,
            const std::string& file_name = "",
            const std::string& function_name = "",
            int line_num = -1,
            int process_id = -1,
            const std::string& thread_id = "") = 0;
    protected:
        /// @brief 日志配置
        LoggerConfig m_config = LoggerConfig();
        /// @brief 日志输出设置
        LogOutputSetting m_output_setting = LogOutputSetting();

    };
    /**
     * @class ILoggerCreator
     * @brief 日志创建器接口类
     */
    class ILoggerCreator
    {
    public:
        /**
         * @brief 创建日志器
         * @param config 日志配置
         * @return 日志器
         */
        virtual std::shared_ptr<ILogger> operator()(const LoggerConfig& config) = 0;
    };
};
