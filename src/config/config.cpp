#include "config/config.hpp"

boost::any Config::get(const string &key)
{
    auto it = m_fields.find(key);
    if (it != m_fields.end()) {
        return it->second;
    }

    if (m_parent != nullptr) {
        return m_parent->get(key);
    }

    DIE("Cannot find key=" + key);
}

boost::any Config::get(const string &key) const
{
    auto it = m_fields.find(key);
    if (it != m_fields.end()) {
        return it->second;
    }

    if (m_parent != nullptr) {
        return m_parent->get(key);
    }

    DIE("Cannot find key=" + key);
}

void Config::set(const std::string &key, const boost::any &value)
{
    m_fields[key] = value;
}
