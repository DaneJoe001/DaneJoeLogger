#include <gtest/gtest.h>

#include "danejoe/logger/logger_config.hpp"

namespace
{

TEST(LoggerConfigTest, DefaultValues_AreExpected)
{
    DaneJoe::LoggerConfig config;

    EXPECT_EQ(config.log_name, "default");
    EXPECT_EQ(config.log_path, "./log/default.log");

    EXPECT_EQ(config.console_level, DaneJoe::LogLevel::TRACE);
    EXPECT_EQ(config.file_level, DaneJoe::LogLevel::TRACE);

    EXPECT_TRUE(config.enable_console);
    EXPECT_TRUE(config.enable_file);
    EXPECT_TRUE(config.enable_async);

    EXPECT_EQ(config.max_file_size, static_cast<std::size_t>(10 * 1024 * 1024));
    EXPECT_EQ(config.max_file_num, static_cast<std::size_t>(5));

    EXPECT_FALSE(config.use_daily_log);
    EXPECT_FALSE(config.enable_backtrace);
    EXPECT_EQ(config.backtrace_size, static_cast<std::size_t>(0));
}

TEST(LogLevelTest, ToStringAndEnumCast_RoundTrip)
{
    EXPECT_EQ(DaneJoe::enum_cast<DaneJoe::LogLevel>(DaneJoe::to_string(DaneJoe::LogLevel::TRACE)), DaneJoe::LogLevel::TRACE);
    EXPECT_EQ(DaneJoe::enum_cast<DaneJoe::LogLevel>(DaneJoe::to_string(DaneJoe::LogLevel::DEBUG)), DaneJoe::LogLevel::DEBUG);
    EXPECT_EQ(DaneJoe::enum_cast<DaneJoe::LogLevel>(DaneJoe::to_string(DaneJoe::LogLevel::INFO)), DaneJoe::LogLevel::INFO);
    EXPECT_EQ(DaneJoe::enum_cast<DaneJoe::LogLevel>(DaneJoe::to_string(DaneJoe::LogLevel::WARN)), DaneJoe::LogLevel::WARN);
    EXPECT_EQ(DaneJoe::enum_cast<DaneJoe::LogLevel>(DaneJoe::to_string(DaneJoe::LogLevel::ERROR)), DaneJoe::LogLevel::ERROR);
    EXPECT_EQ(DaneJoe::enum_cast<DaneJoe::LogLevel>(DaneJoe::to_string(DaneJoe::LogLevel::FATAL)), DaneJoe::LogLevel::FATAL);
    EXPECT_EQ(DaneJoe::enum_cast<DaneJoe::LogLevel>(DaneJoe::to_string(DaneJoe::LogLevel::NONE)), DaneJoe::LogLevel::NONE);

    EXPECT_EQ(DaneJoe::enum_cast<DaneJoe::LogLevel>("LogLevel::Unknown"), DaneJoe::LogLevel::Unknown);
}

} // namespace
