#include "log/manage_logger.hpp"
#include "log/danejoe_logger.hpp"


DaneJoe::ManageLogger::ManageLogger()
{
    add_creator("default", std::make_shared<DaneJoe::DaneJoeLoggerCreator>());
    add_logger("default", m_default_log_config);
}

DaneJoe::ManageLogger& DaneJoe::ManageLogger::get_instance()
{
    static ManageLogger instance;
    return instance;
}

void DaneJoe::ManageLogger::add_logger(const std::string& logger_type, const DaneJoe::ILogger::LoggerConfig& log_config)
{
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

std::shared_ptr<DaneJoe::ILogger> DaneJoe::ManageLogger::get_logger(const std::string& log_name)
{
    if (m_logger_map.find(log_name) == m_logger_map.end())
    {
        return m_logger_map[m_default_log_config.log_name];
    }
    return m_logger_map[log_name];
}

void DaneJoe::ManageLogger::add_creator(const std::string& logger_type, std::shared_ptr<DaneJoe::ILoggerCreator> creator)
{
    m_logger_creator_map[logger_type] = creator;
}