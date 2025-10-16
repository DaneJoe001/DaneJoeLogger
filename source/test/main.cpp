#include "logger/async_logger.hpp"
#include "logger/logger_manager.hpp"
#include <thread>

int main()
{
    DaneJoe::AsyncLogger::LoggerConfig log_config;
    log_config.log_name = "DaneJoe";
    DaneJoe::ManageLogger& manage_logger = DaneJoe::ManageLogger::get_instance();
    manage_logger.add_logger("default", log_config);

    auto logger = manage_logger.get_logger("default");



    logger->trace(std::string("test"), std::string("E:\\personal_code\\code_cpp_library\\library_danejoe_log\\source\\test\\main.cpp"), std::string(__FUNCTION__), 9, "test {}", 7);

    DANEJOE_LOG_TRACE("default", "test", "测试 {}", 7);

    // std::this_thread::sleep_for(std::chrono::milliseconds(100));

    return 0;
}
