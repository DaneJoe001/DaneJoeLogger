cmake_minimum_required(VERSION 3.20)
project(DaneJoeLogger VERSION 0.2.0 LANGUAGES CXX)
option(DANEJOE_LOGGER_BUILD_TESTS "Build tests for DaneJoeLogger" ${BUILD_TESTING})
option(DANEJOE_LOGGER_BUILD_EXAMPLES "Build examples for DaneJoeLogger" OFF)

if(PROJECT_IS_TOP_LEVEL)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

  if(CMAKE_EXPORT_COMPILE_COMMANDS AND CMAKE_GENERATOR MATCHES "Ninja|Makefiles")
    if(NOT TARGET update_compile_commands_${PROJECT_NAME})
      add_custom_target(update_compile_commands_${PROJECT_NAME} ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/compile_commands.json"
                "${CMAKE_CURRENT_LIST_DIR}/compile_commands.json")
    endif()
  endif()
endif()

if(PROJECT_IS_TOP_LEVEL)
  if(NOT TARGET DaneJoe::Common)
    if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/../common/CMakeLists.txt")
      add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../common" "${CMAKE_CURRENT_BINARY_DIR}/_deps/common")
    endif()
  endif()
endif()

# @brief 定义基础日志库目标
# @note 对外通过命名空间别名 `DaneJoe::Logger` 暴露
add_library(DaneJoeLogger
  "source/danejoe/logger/async_logger.cpp"
  "source/danejoe/logger/i_logger.cpp"
  "source/danejoe/logger/logger_config.cpp"
  "source/danejoe/logger/logger_manager.cpp"
)
add_library(DaneJoe::Logger ALIAS DaneJoeLogger)

set_target_properties(DaneJoeLogger PROPERTIES EXPORT_NAME Logger)

# @brief 公开头文件目录
# @note BUILD_INTERFACE 指向源码树；INSTALL_INTERFACE 指向安装树
target_include_directories(DaneJoeLogger
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(MSVC)
  target_compile_options(DaneJoeLogger PRIVATE /utf-8)
endif()

# @brief 以目标特性声明 C++20
target_compile_features(DaneJoeLogger PUBLIC cxx_std_20)

# 版本与 SOVERSION
set_target_properties(DaneJoeLogger PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 0)

# @brief 依赖 Common 组件（使用 TimeUtil/ProcessUtil）
target_link_libraries(DaneJoeLogger PUBLIC DaneJoe::Common)

# @brief 安装目标与头文件
include(GNUInstallDirs)
install(
  TARGETS DaneJoeLogger
  EXPORT DaneJoeLoggerTargets
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

install(
  DIRECTORY
    "include/"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# 生成版本头并安装
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/include/danejoe/version/logger_version.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/include/danejoe/version/logger_version.h"
  @ONLY
)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/include/danejoe/version/logger_version.h"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/danejoe/version"
)

# @brief 生成并安装 CMake 包配置（Config + Version + Targets）
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/DaneJoeLoggerConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

configure_file(
  "cmake/DaneJoeLoggerConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/DaneJoeLoggerConfig.cmake"
  @ONLY
)

install(EXPORT DaneJoeLoggerTargets
  NAMESPACE DaneJoe::
  FILE DaneJoeLoggerTargets.cmake
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/DaneJoeLogger"
)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/DaneJoeLoggerConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/DaneJoeLoggerConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/DaneJoeLogger"
)

if(DANEJOE_LOGGER_BUILD_TESTS)
  include(CTest)
  enable_testing()
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt")
    add_subdirectory(test)
  endif()
endif()

if(DANEJOE_LOGGER_BUILD_EXAMPLES)
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/example/CMakeLists.txt")
    add_subdirectory(example)
  endif()
endif()
