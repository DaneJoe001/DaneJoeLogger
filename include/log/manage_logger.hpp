#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <thread>
#include <functional>

#include "log/i_logger.hpp"

/**
 * @namespace DaneJoe
 * @brief DaneJoe命名空间
 */
namespace DaneJoe
{
    /**
     * @class ManageLog
     * @brief 日志管理单例类
     */
    class ManageLogger
    {
    public:
        /**
         * @brief 获取单例对象
         */
        static ManageLogger& get_instance();
        /**
         * @brief 获取日志对象
         * @details 当日志对象不存在时
         * @param log_name 日志名称
         */
        std::shared_ptr<DaneJoe::ILogger> get_logger(const std::string& log_name);
        /**
         * @brief 添加日志对象
         * @param log_config 日志配置
         */
        void add_logger(const std::string& logger_type, const DaneJoe::ILogger::LoggerConfig& log_config);
        /**
         * @brief 添加日志创建器
         * @param logger_type 日志类型
         * @param creator 日志创建器
         */
        void add_creator(const std::string& logger_type, std::shared_ptr<DaneJoe::ILoggerCreator> creator);
    private:
        /**
         * @brief 构造函数
         */
        ManageLogger();
        /**
         * @brief 析构函数
         */
        ~ManageLogger() = default;
        /**
         * @brief
         */
        ManageLogger(const ManageLogger&) = delete;
        /*
         * @brief 移动赋值运算符
         */
        ManageLogger(const ManageLogger&&) = delete;
        /**
         * @brief 赋值运算符
         */
        ManageLogger& operator=(const ManageLogger&) = delete;
        /**
         * @brief 移动赋值运算符
         */
        ManageLogger& operator=(const ManageLogger&&) = delete;
    private:
        /// @brief 日志记录器表
        std::unordered_map<std::string, std::shared_ptr<DaneJoe::ILogger>> m_logger_map;
        /// @brief 日志创建器表
        std::unordered_map<std::string, std::shared_ptr<ILoggerCreator>> m_logger_creator_map;
        /// @brief 默认日志配置
        DaneJoe::ILogger::LoggerConfig m_default_log_config;
    };
}

/**
 * @brief 日志宏
 * @param log_name 日志名称
 * @param module 模块名称
 * @param fmt 格式化字符串
 * @param ... 可变参数
 */
#define DANEJOE_LOG_TRACE(log_name,module,fmt,...)\
do\
{\
auto logger=DaneJoe::ManageLogger::get_instance().get_logger(log_name);\
    if(logger)\
    {\
        logger->trace(\
        std::string(module),\
        std::string(__FILE__), \
        std::string(__FUNCTION__), \
        __LINE__, \
        fmt, \
        ##__VA_ARGS__, "");\
    }\
}while (0)

 /**
  * @brief 日志宏
  * @param log_name 日志名称
  * @param module 模块名称
  * @param fmt 格式化字符串
  * @param ... 可变参数
  */
#define DANEJOE_LOG_DEBUG(log_name,module,fmt,...)\
do\
{\
auto logger=DaneJoe::ManageLogger::get_instance().get_logger(log_name);\
    if(logger)\
    {\
        logger->debug(\
    std::string(module),\
    std::string(__FILE__), \
    std::string(__FUNCTION__), \
    __LINE__, \
    fmt, \
    ##__VA_ARGS__, "");\
    }\
}while (0)

  /**
   * @brief 日志宏
   * @param log_name 日志名称
   * @param module 模块名称
   * @param fmt 格式化字符串
   * @param ... 可变参数
   */
#define DANEJOE_LOG_INFO(log_name,module,fmt,...)\
do\
{\
auto logger=DaneJoe::ManageLogger::get_instance().get_logger(log_name);\
    if(logger)\
    {\
        logger->info(\
    std::string(module),\
    std::string(__FILE__), \
    std::string(__FUNCTION__), \
    __LINE__, \
    fmt, \
    ##__VA_ARGS__, "");\
    }\
}while (0)

   /**
    * @brief 日志宏
    * @param log_name 日志名称
    * @param module 模块名称
    * @param fmt 格式化字符串
    * @param ... 可变参数
    */
#define DANEJOE_LOG_WARN(log_name,module,fmt,...)\
do\
{\
auto logger=DaneJoe::ManageLogger::get_instance().get_logger(log_name);\
    if(logger)\
    {\
        logger->warn(\
    std::string(module),\
    std::string(__FILE__), \
    std::string(__FUNCTION__), \
    __LINE__, \
    fmt, \
    ##__VA_ARGS__, "");\
    }\
}while (0)

    /**
     * @brief 日志宏
     * @param log_name 日志名称
     * @param module 模块名称
     * @param fmt 格式化字符串
     * @param ... 可变参数
     */
#define DANEJOE_LOG_ERROR(log_name,module,fmt,...)\
do\
{\
auto logger=DaneJoe::ManageLogger::get_instance().get_logger(log_name);\
    if(logger)\
    {\
        logger->error(\
    std::string(module),\
    std::string(__FILE__), \
    std::string(__FUNCTION__), \
    __LINE__, \
    fmt, \
    ##__VA_ARGS__, "");\
    }\
}while (0)

     /**
      * @brief 日志宏
      * @param log_name 日志名称
      * @param module 模块名称
      * @param fmt 格式化字符串
      * @param ... 可变参数
      */
#define DANEJOE_LOG_FATAL(log_name,module,fmt,...)\
do\
{\
auto logger=DaneJoe::ManageLogger::get_instance().get_logger(log_name);\
    if(logger)\
    {\
        logger->fatal(\
    std::string(module),\
    std::string(__FILE__), \
    std::string(__FUNCTION__), \
    __LINE__, \
    fmt, \
    ##__VA_ARGS__, "");\
    }\
}while (0)