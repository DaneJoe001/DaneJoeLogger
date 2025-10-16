#include "util/time_util.hpp"

std::string DaneJoe::TimeUtil::get_now_time_str()
{
    auto current_time = std::chrono::system_clock::now();
    return get_time_str(current_time);
}

std::string DaneJoe::TimeUtil::get_time_str(const std::chrono::system_clock::time_point& tp)
{
    std::time_t time_t = std::chrono::system_clock::to_time_t(tp);
    std::tm* time_tm = std::localtime(&time_t);
    std::ostringstream oss;
    oss << std::put_time(time_tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}