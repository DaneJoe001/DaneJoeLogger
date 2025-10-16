#pragma once

#include <chrono>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

/// @brief 获取当前时间字符串
#define DANEJOE_NOW_TIME_STR DaneJoe::TimeUtil::get_now_time_str()

namespace DaneJoe
{
    /**
     * @class TimeUtil
     * @brief 时间工具类
     */
    class TimeUtil
    {
    public:
        /**
         * @brief 获取当前时间字符串
         * @return std::string 时间字符串
         */
        static std::string get_now_time_str();
        /**
         * @brief 获取指定时间点对应的时间字符串
         * @param tp 时间点
         */
        static std::string get_time_str(const std::chrono::system_clock::time_point& tp);
    };
}