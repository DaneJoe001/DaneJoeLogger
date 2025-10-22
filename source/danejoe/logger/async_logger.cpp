#include <iostream>
#include <format>
#include <string>
#include <filesystem>

#include "danejoe/logger/async_logger.hpp"

namespace fs = std::filesystem;

DaneJoe::AsyncLogger::AsyncLogger()
{
    if (m_config.enable_async)
    {
        start_async_log();
    }
}

DaneJoe::AsyncLogger::~AsyncLogger()
{
    stop_async_log();
}

DaneJoe::AsyncLogger::AsyncLogger(const LoggerConfig& config) :ILogger(config)
{
    if (config.enable_async)
    {
        start_async_log();
    }
}

void DaneJoe::AsyncLogger::stop_async_log()
{
    {
        std::unique_lock<std::mutex> lock(m_console_log_queue_mutex);
        m_console_log_queue_cond.wait(lock, [this]()
            {
                return m_console_log_queue.empty();
            });
        m_async_console_log_flag.store(false);
        m_console_log_queue_cond.notify_all();
    }
    {
        std::unique_lock<std::mutex> lock(m_file_log_queue_mutex);
        m_file_log_queue_cond.wait(lock, [this]()
            {
                return m_file_log_queue.empty();
            });
        m_async_file_log_flag.store(false);
        m_file_log_queue_cond.notify_all();
    }
    if (m_async_file_log_thread.joinable())
    {
        m_async_file_log_thread.join();
    }
    if (m_async_console_log_thread.joinable())
    {
        m_async_console_log_thread.join();
    }
}

void DaneJoe::AsyncLogger::log_msg(LogLevel level,
    const std::string& module,
    const std::string& log_info,
    const std::string& file_name,
    const std::string& function_name,
    int line_num,
    int process_id,
    const std::string& thread_id)
{
    std::string header = get_header(level, module, log_info, file_name, function_name, line_num, process_id, thread_id);
    std::string log_str = std::format("{}[:] [{}] ", header, log_info);
    if (m_config.enable_console && m_config.console_level <= level)
    {
        if (m_async_console_log_flag.load())
        {
            std::lock_guard<std::mutex> lock(m_console_log_queue_mutex);
            m_console_log_queue.push(log_str);
            std::atomic_thread_fence(std::memory_order_seq_cst);
            m_console_log_queue_cond.notify_one();
        }
        else
        {
            std::lock_guard<std::mutex> lock(m_console_mutex);
            std::cout << log_str << std::endl;
        }
    }
    if (m_config.enable_file && m_config.file_level <= level)
    {
        if (m_async_file_log_flag.load())
        {
            std::lock_guard<std::mutex> lock(m_file_log_queue_mutex);
            m_file_log_queue.push(log_str);
            std::atomic_thread_fence(std::memory_order_seq_cst);
            m_file_log_queue_cond.notify_one();
        }
        else
        {
            std::lock_guard<std::mutex> lock(m_file_mutex);
            if (open_log_file())
            {
                m_log_file << log_str << std::endl;
            }
        }
    }
}

bool DaneJoe::AsyncLogger::open_log_file()
{
    if (m_log_file.is_open())
    {
        return true;
    }
    /// @brief 确认目录存在，当目录不存在时创建目录
    fs::path full_path(m_config.log_path);
    fs::path path = full_path.parent_path();
    if (!fs::exists(path))
    {
        fs::create_directories(path);
    }
    m_log_file.open(m_config.log_path, std::ios::app);
    if (m_log_file.is_open())
    {
        return true;
    }
    return false;
}

std::shared_ptr<DaneJoe::ILogger> DaneJoe::DaneJoeLoggerCreator::operator()(const ILogger::LoggerConfig& config)
{
    return std::make_shared<AsyncLogger>(config);
}

void DaneJoe::AsyncLogger::async_file_log_handler()
{
    while (true)
    {
        if (!m_async_file_log_flag.load())
        {
            return;
        }
        std::unique_lock<std::mutex> lock(m_file_log_queue_mutex);
        m_file_log_queue_cond.wait(
            lock,
            [this]
            {
                return !m_file_log_queue.empty() || !m_async_file_log_flag.load();
            });
        if (!m_file_log_queue.empty())
        {
            std::string log_str = m_file_log_queue.front();
            m_file_log_queue.pop();
            std::atomic_thread_fence(std::memory_order_seq_cst);
            if (open_log_file())
            {
                m_log_file << log_str << std::endl;
                std::flush(m_log_file);
            }
            m_file_log_queue_cond.notify_all();
        }
    }
}

void DaneJoe::AsyncLogger::async_console_log_handler()
{
    while (true)
    {
        if (!m_async_console_log_flag.load())
        {
            return;
        }
        std::unique_lock<std::mutex> lock(m_console_log_queue_mutex);
        m_console_log_queue_cond.wait(lock, [this]()
            {
                return !m_console_log_queue.empty() || !m_async_console_log_flag.load();
            });
        if (!m_console_log_queue.empty())
        {
            std::string log_str = m_console_log_queue.front();
            m_console_log_queue.pop();
            std::atomic_thread_fence(std::memory_order_seq_cst);
            std::cout << log_str << std::endl;
            std::flush(std::cout);
            m_console_log_queue_cond.notify_all();
        }
    }
}

void DaneJoe::AsyncLogger::start_async_log()
{
    if (!m_async_file_log_flag.load())
    {
        m_async_file_log_flag.store(true);
        m_async_file_log_thread = std::thread(&AsyncLogger::async_file_log_handler, this);
    }
    if (!m_async_console_log_flag.load())
    {
        m_async_console_log_flag.store(true);
        m_async_console_log_thread = std::thread(&AsyncLogger::async_console_log_handler, this);
    }

}