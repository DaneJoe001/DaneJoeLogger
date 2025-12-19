#include <gtest/gtest.h>

#include <string>
#include <thread>
#include <vector>

#include "danejoe/logger/logger_manager.hpp"

TEST(LoggerManagerTest, ConcurrentGetLoggerDoesNotCrash)
{
    std::vector<std::thread> threads;
    threads.reserve(8);

    for (int t = 0; t < 8; ++t)
    {
        threads.emplace_back([t]()
            {
                for (int i = 0; i < 200; ++i)
                {
                    auto logger = DaneJoe::LoggerManager::get_instance().get_logger("default");
                    EXPECT_TRUE(static_cast<bool>(logger));

                    DaneJoe::LoggerConfig config;
                    config.log_name = std::string("logger_") + std::to_string(t) + "_" + std::to_string(i);
                    config.enable_console = false;
                    config.enable_file = false;
                    config.enable_async = false;

                    DaneJoe::LoggerManager::get_instance().add_logger("default", config);
                }
            });
    }

    for (auto& th : threads)
    {
        th.join();
    }
}
