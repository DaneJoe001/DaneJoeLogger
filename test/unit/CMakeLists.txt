cmake_minimum_required(VERSION 3.20)

find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

add_executable(danejoe_logger_unit_tests
  "${CMAKE_CURRENT_LIST_DIR}/source/test_smoke.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/source/test_async_logger.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/source/test_logger_manager.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/source/test_logger_config.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/source/test_logger_manager_basic.cpp"
)

target_link_libraries(danejoe_logger_unit_tests
  PRIVATE
    DaneJoe::Logger
    GTest::gtest_main
)

if(MSVC)
  target_compile_options(danejoe_logger_unit_tests PRIVATE /utf-8)
endif()

gtest_discover_tests(danejoe_logger_unit_tests
  DISCOVERY_TIMEOUT 30
  PROPERTIES
    LABELS unit
)
