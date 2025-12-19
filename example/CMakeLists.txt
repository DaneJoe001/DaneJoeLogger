cmake_minimum_required(VERSION 3.20)

add_executable(danejoe_logger_example
  "${CMAKE_CURRENT_LIST_DIR}/source/main.cpp"
)

target_link_libraries(danejoe_logger_example
  PRIVATE
    DaneJoe::Logger
)

if(MSVC)
  target_compile_options(danejoe_logger_example PRIVATE /utf-8)
endif()
