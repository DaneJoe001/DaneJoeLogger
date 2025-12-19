#include <gtest/gtest.h>

#include <chrono>
#include <filesystem>
#include <future>
#include <string>
#include <thread>
#include <vector>

#include "danejoe/logger/async_logger.hpp"

TEST(AsyncLoggerTest, DestructorFlushDoesNotHang)
{
    namespace fs = std::filesystem;

    DaneJoe::LoggerConfig config;
    config.log_name = "async_test";
    config.enable_async = true;
    config.enable_console = false;
    config.enable_file = true;

    fs::path log_path = fs::temp_directory_path() / "danejoe_logger_tests" / "async_logger_flush.log";
    config.log_path = log_path.string();

    auto logger = std::make_shared<DaneJoe::AsyncLogger>(config);

    std::vector<std::thread> writers;
    writers.reserve(4);
    for (int t = 0; t < 4; ++t)
    {
        writers.emplace_back([logger, t]()
            {
                for (int i = 0; i < 2000; ++i)
                {
                    logger->info("unit", "", "", -1, "t={} i={}", t, i);
                }
            });
    }

    for (auto& th : writers)
    {
        th.join();
    }

    auto fut = std::async(std::launch::async, [logger]() mutable
        {
            logger.reset();
        });

    const auto status = fut.wait_for(std::chrono::seconds(3));
    EXPECT_EQ(status, std::future_status::ready);
}
