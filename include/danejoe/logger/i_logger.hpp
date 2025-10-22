#pragma once

/**
 * @file i_logger.hpp
 * @brief 日志接口类头文件
 * @details 日志接口类
 * @author DaneJoe001
 */

#include <format>
#include <string>
#include <thread>
#include <memory>

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
            NONE
        };
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
        void set_output_settings(const LogOutputSetting& settings);
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
        virtual std::shared_ptr<ILogger> operator()(const ILogger::LoggerConfig& config) = 0;
    };
};