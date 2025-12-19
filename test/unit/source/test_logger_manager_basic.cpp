#include <gtest/gtest.h>

#include <memory>

#include "danejoe/logger/logger_manager.hpp"

namespace
{

TEST(LoggerManagerBasicTest, GetLogger_UnknownNameFallsBackToDefault)
{
    auto default_logger = DaneJoe::LoggerManager::get_instance().get_logger("default");
    ASSERT_TRUE(static_cast<bool>(default_logger));

    auto unknown_logger = DaneJoe::LoggerManager::get_instance().get_logger("not_exist_logger_name");
    ASSERT_TRUE(static_cast<bool>(unknown_logger));

    EXPECT_EQ(default_logger.get(), unknown_logger.get());
}

TEST(LoggerManagerBasicTest, AddLogger_NewNameCreatesLogger)
{
    DaneJoe::LoggerConfig config;
    config.log_name = "unit_custom";
    config.enable_console = false;
    config.enable_file = false;
    config.enable_async = false;

    DaneJoe::LoggerManager::get_instance().add_logger("default", config);

    auto created = DaneJoe::LoggerManager::get_instance().get_logger("unit_custom");
    ASSERT_TRUE(static_cast<bool>(created));

    auto default_logger = DaneJoe::LoggerManager::get_instance().get_logger("default");
    ASSERT_TRUE(static_cast<bool>(default_logger));

    EXPECT_NE(created.get(), default_logger.get());
}

TEST(LoggerManagerBasicTest, AddLogger_SameNameDoesNotOverrideExistingLogger)
{
    DaneJoe::LoggerConfig config_1;
    config_1.log_name = "unit_keep";
    config_1.enable_console = false;
    config_1.enable_file = false;
    config_1.enable_async = false;

    DaneJoe::LoggerManager::get_instance().add_logger("default", config_1);
    auto first = DaneJoe::LoggerManager::get_instance().get_logger("unit_keep");
    ASSERT_TRUE(static_cast<bool>(first));

    DaneJoe::LoggerConfig config_2 = config_1;
    config_2.enable_async = true;

    DaneJoe::LoggerManager::get_instance().add_logger("default", config_2);
    auto second = DaneJoe::LoggerManager::get_instance().get_logger("unit_keep");
    ASSERT_TRUE(static_cast<bool>(second));

    EXPECT_EQ(first.get(), second.get());
}

} // namespace
