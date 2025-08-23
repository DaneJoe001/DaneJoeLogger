cmake_minimum_required(VERSION 4.0.1)

project(DaneJoeLog LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 添加编码设置
if(MSVC)
    add_compile_options(/utf-8)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

# 库源文件
file(GLOB LIB_SOURCE 
    "source/log/*.cpp"
    "source/util/*.cpp"
    # "include/log/*.hpp"
    # "include/util/*.hpp"
)

# 测试源文件
file(GLOB TEST_SOURCE
    "source/test/*.cpp"
    # "include/log/*.hpp"
    # "include/util/*.hpp"
    # "include/test/*.hpp"
)

# 创建静态库
add_library(DaneJoeLog STATIC ${LIB_SOURCE})

# 设置库的include目录
target_include_directories(DaneJoeLog PUBLIC include)

# 创建测试可执行文件
if(TEST_SOURCE)
    add_executable(DaneJoeLogTest ${TEST_SOURCE})
    # 设置测试的include目录
    target_include_directories(DaneJoeLogTest PRIVATE include)
    target_link_libraries(DaneJoeLogTest PRIVATE DaneJoeLog)
endif()