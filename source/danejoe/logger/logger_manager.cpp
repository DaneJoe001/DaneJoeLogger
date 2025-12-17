#include "danejoe/logger/logger_manager.hpp"
#include "danejoe/logger/async_logger.hpp"


DaneJoe::LoggerManager::LoggerManager()
{
    add_creator("default", std::make_shared<DaneJoe::DaneJoeLoggerCreator>());
    add_logger("default", m_default_log_config);
}

DaneJoe::LoggerManager& DaneJoe::LoggerManager::get_instance()
{
    static LoggerManager instance;
    return instance;
}

void DaneJoe::LoggerManager::add_logger(const std::string& logger_type, const DaneJoe::LoggerConfig& log_config)
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_logger_map.find(log_config.log_name) != m_logger_map.end())
        {
            return;
        }
        if (m_logger_creator_map.find(logger_type) == m_logger_creator_map.end())
        {
            auto default_creator = m_logger_creator_map["default"];
            m_logger_map[log_config.log_name] = (*default_creator)(log_config);
            return;
        }
        auto creator = m_logger_creator_map[logger_type];
        m_logger_map[log_config.log_name] = (*creator)(log_config);
    }
}

std::shared_ptr<DaneJoe::ILogger> DaneJoe::LoggerManager::get_logger(const std::string& log_name)
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_logger_map.find(log_name) == m_logger_map.end())
        {
            return m_logger_map[m_default_log_config.log_name];
        }
        return m_logger_map[log_name];
    }
}

void DaneJoe::LoggerManager::add_creator(const std::string& logger_type, std::shared_ptr<DaneJoe::ILoggerCreator> creator)
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_logger_creator_map[logger_type] = creator;
    }
}
