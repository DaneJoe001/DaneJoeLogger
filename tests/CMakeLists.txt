cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(danejoe_logger_demo
  "${CMAKE_CURRENT_LIST_DIR}/source/main.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/source/demo_logger.cpp"
)

target_link_libraries(danejoe_logger_demo PRIVATE DaneJoe::Logger)
target_include_directories(danejoe_logger_demo PRIVATE
  "${CMAKE_CURRENT_LIST_DIR}/include"
)

add_test(NAME logger.demo COMMAND danejoe_logger_demo)
