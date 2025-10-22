#include <iostream>
#include "danejoe/logger/logger_manager.hpp"
#include "demo_logger.hpp"

namespace demo {

void run_logger_demo()
{
    std::cout << "Logger demo:\n";

    DANEJOE_LOG_TRACE("default", "demo", "trace message: %s", "hello");
    DANEJOE_LOG_DEBUG("default", "demo", "debug number: %d", 123);
    DANEJOE_LOG_INFO ("default", "demo", "info value: %d", 42);
    DANEJOE_LOG_WARN ("default", "demo", "warn %s", "pay attention");
    DANEJOE_LOG_ERROR("default", "demo", "error code: %d", -1);

    std::cout << "Logger demo done." << std::endl;
}

} // namespace demo
