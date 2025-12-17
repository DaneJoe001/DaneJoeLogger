#include <gtest/gtest.h>

#include "danejoe/logger/logger_manager.hpp"

TEST(LoggerSmokeTest, CanGetDefaultLogger)
{
    auto logger = DaneJoe::LoggerManager::get_instance().get_logger("default");
    EXPECT_TRUE(static_cast<bool>(logger));
}
