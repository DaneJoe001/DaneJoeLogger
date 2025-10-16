# DaneJoe Logger

一个轻量的 C++ 异步日志库：包含日志接口、异步实现与管理器以及便捷日志宏。

## 特性
- 提供 CMake 目标与别名：真实目标 `danejoe_logger`，命名空间别名 `danejoe::logger`
- 支持安装并通过 `find_package(DaneJoeLogger CONFIG)` 消费
- C++20（使用 `std::format`）
- 异步控制台/文件输出，最小依赖
- 单例管理器按名称获取/创建日志器，支持注册自定义创建器
- 日志宏封装：`DANEJOE_LOG_TRACE/DEBUG/INFO/WARN/ERROR/FATAL`
- 可配置输出头部字段（时间、级别、模块、文件、函数、行号、线程/进程）

## 目录结构
```text
include/
  logger/
    i_logger.hpp          # 日志接口与配置/输出设置
    async_logger.hpp      # 异步日志实现
    logger_manager.hpp    # 日志管理器与日志宏
  util/
    time_util.hpp         # 时间工具（格式化当前时间）
    process_util.hpp      # 进程工具（获取 pid）
  version/
    logger_version.h.in   # 由 CMake 生成版本头的模板
source/
  logger/
    i_logger.cpp
    async_logger.cpp
    logger_manager.cpp
  util/
    time_util.cpp
    process_util.cpp
  test/
    main.cpp              # 简单示例/测试
CMakeLists.txt
cmake/
  danejoe_install_export.cmake  # 安装/导出封装
README.md
```

## 快速开始

### 方式一：作为子目录使用（推荐用于同仓开发）
```cmake
add_subdirectory(path/to/library_danejoe_log)

add_executable(MyApp main.cpp)
target_link_libraries(MyApp PRIVATE danejoe::logger)
```

### 方式二：本库本地构建
```bash
cmake -S . -B build/gcc-debug -D CMAKE_BUILD_TYPE=Debug -D DANEJOE_LOGGER_BUILD_TESTS=ON
cmake --build build/gcc-debug -j
```

### 方式三：FetchContent 引入（无需安装）
```cmake
include(FetchContent)

FetchContent_Declare(DaneJoeLogger
  GIT_REPOSITORY https://github.com/DaneJoe001/DaneJoeLogger.git
  GIT_TAG        v1.0.0
)
FetchContent_MakeAvailable(DaneJoeLogger)

add_executable(MyApp main.cpp)
target_link_libraries(MyApp PRIVATE danejoe::logger)
```

### 方式四：安装后 find_package 消费
先在库根目录安装：
```bash
cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
cmake --build build -j
cmake --install build
```
消费者工程中：
```cmake
find_package(DaneJoeLogger CONFIG REQUIRED)
add_executable(MyApp main.cpp)
target_link_libraries(MyApp PRIVATE danejoe::logger)
```

> 说明：安装/导出流程仅在作为顶层工程时启用；作为子项目/FetchContent 引入时不会执行安装步骤。

## CMake 目标与选项
- 目标：`danejoe_logger`（别名：`danejoe::logger`）
- C++ 标准：通过目标特性声明 `cxx_std_20`
- 选项：
  - `DANEJOE_LOGGER_BUILD_TESTS`（默认 ON）：构建示例测试，可在顶层或父工程中设为 `OFF`
  - `BUILD_SHARED_LIBS`（默认 OFF）：控制生成动态/静态库

## API 概览
头文件位于 `include/logger`。

- 命名空间：`DaneJoe`

- 核心类：`ILogger`
  - 模板成员：`trace/debug/info/warn/error/fatal`
    - 形如：
      ```cpp
      template<typename... Args>
      void info(const std::string& module,
                const std::string& file,
                const std::string& function,
                int line,
                std::format_string<Args...> fmt,
                Args&&... args);
      ```
    - 内部使用 `std::format` 生成消息并调用虚函数 `log_msg(...)`
  - 配置体：`ILogger::LoggerConfig`
    - `log_name`、`log_path`、`console_level`、`file_level`
    - `enable_console`、`enable_file`、`enable_async`
    - 预留：`max_file_size`、`max_file_num`、`use_daily_log`、`enable_backtrace`、`backtrace_size`（当前未实现滚动/按日切分/回溯）
  - 输出设置：`ILogger::LogOutputSetting`
    - 控制是否输出时间/级别/模块/文件/函数/行号/线程ID/进程ID
  - 其它：`set_config(...)`、`set_output_settings(...)`、`get_header(...)`、`get_pid()`、`to_string(LogLevel)` 等

- 实现类：`AsyncLogger`（继承 `ILogger`）
  - 将消息推入控制台/文件队列，由后台线程异步输出
  - 若未启用异步，则在调用线程直接输出

- 管理器：`ManageLogger`
  - `static ManageLogger& get_instance()` 获取单例
  - `add_logger(const std::string& logger_type, const ILogger::LoggerConfig& config)`
  - `std::shared_ptr<ILogger> get_logger(const std::string& log_name)`
  - `add_creator(const std::string& logger_type, std::shared_ptr<ILoggerCreator> creator)`

- 宏：定义在 `logger_manager.hpp`
  - `DANEJOE_LOG_TRACE/DEBUG/INFO/WARN/ERROR/FATAL(log_name, module, fmt, ...)`

## 示例
```cpp
#include "logger/async_logger.hpp"
#include "logger/logger_manager.hpp"

int main() {
    // 1) 配置并注册日志器
    DaneJoe::ILogger::LoggerConfig cfg;
    cfg.log_name = "default";
    cfg.log_path = "./logs/app.log";
    cfg.console_level = DaneJoe::ILogger::LogLevel::TRACE;
    cfg.file_level    = DaneJoe::ILogger::LogLevel::INFO;
    cfg.enable_async  = true; // 启动异步输出线程

    auto& mgr = DaneJoe::ManageLogger::get_instance();
    mgr.add_logger("default", cfg); // 使用内置默认创建器（AsyncLogger）

    // 可选：设置输出头部字段
    auto logger = mgr.get_logger("default");
    DaneJoe::ILogger::LogOutputSetting out;
    out.enable_time = true;
    out.enable_level = true;
    out.enable_module = true;
    out.enable_file_name = true;
    out.enable_function_name = true;
    out.enable_line_num = true;
    logger->set_output_settings(out);

    // 2) 直接调用成员模板（使用 std::format）
    logger->info("bootstrap", __FILE__, __FUNCTION__, __LINE__, "hello {}", 42);

    // 3) 使用便捷宏（自动从管理器取 logger）
    DANEJOE_LOG_INFO("default", "demo", "user {} logged in", "alice");

    return 0;
}
```

## 版本宏
配置/安装后可包含：
```cpp
#include <version/logger_version.h>

// 可用宏：
// LOGGER_VERSION_MAJOR / LOGGER_VERSION_MINOR / LOGGER_VERSION_PATCH / LOGGER_VERSION_STR
```

## 构建与测试
- 在顶层工程启用测试：`-D DANEJOE_LOGGER_BUILD_TESTS=ON`
- 运行：
```bash
cmake -S . -B build -D DANEJOE_LOGGER_BUILD_TESTS=ON
cmake --build build -j
ctest --test-dir build
```

## 兼容性
- 要求 C++20 及以上（因使用 `std::format`）
- MSVC/GCC/Clang 均可
- Windows/Linux（`getpid` 平台分支已处理）

## 局限与注意事项
- `max_file_size`/`max_file_num`/`use_daily_log`/`enable_backtrace` 等尚未实现对应功能
- 日志文件为追加模式；如需滚动/按日切分，请在上层实现或贡献 PR
- 异步输出在程序退出时会等待队列清空并回收线程

## 许可证
暂未设立
