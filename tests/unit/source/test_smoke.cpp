#include <gtest/gtest.h>

namespace
{

TEST(LoggerSmokeTest, Dummy)
{
    EXPECT_TRUE(true) << "logger unit smoke test";
}

} // namespace
