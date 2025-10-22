# DaneJoe Logger

基础日志库（同步/异步接口、日志管理器、宏封装）。

## 构建
```bash
cmake -S . -B build --preset gcc-debug -DBUILD_TESTING=ON
cmake --build build
```

## 运行示例/测试
```bash
ctest --test-dir build -V -R logger\.demo
# 或直接运行
./build/library/logger/tests/danejoe_logger_demo
```

## 作为依赖使用
CMake:
```cmake
find_package(DaneJoeLogger CONFIG REQUIRED)
add_executable(app main.cpp)
target_link_libraries(app PRIVATE DaneJoe::Logger)
```
