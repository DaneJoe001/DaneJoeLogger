#pragma once

#include <chrono>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

/// @brief 获取当前时间字符串
#define NOW_TIME_STR UtilTime::get_now_time_str()

/**
 * @class UtilTime
 * @brief 时间工具类
 */
class UtilTime
{
public:
    /**
     * @brief 获取当前时间字符串
     * @return std::string 时间字符串
     */
    static std::string get_now_time_str()
    {
        auto current_time = std::chrono::system_clock::now();
        return get_time_str(current_time);
    }
    /**
     * @brief 获取指定时间点对应的时间字符串
     * @param tp 时间点
     */
    static std::string get_time_str(const std::chrono::system_clock::time_point& tp)
    {
        std::time_t time_t = std::chrono::system_clock::to_time_t(tp);
        std::tm* time_tm = std::localtime(&time_t);
        std::ostringstream oss;
        oss << std::put_time(time_tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

};