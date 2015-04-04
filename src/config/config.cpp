#include "config/config.hpp"


void Config::set_default()
{
    /* TODO: make table of basic config items here & set their default value */
}

string Config::get(const string &key) const
{
    auto it = m_fields.find(key);
    if (it != m_fields.end()) {
        return it->second;
    }

    if (m_parent != nullptr) {
        return m_parent->get(key);
    }

    mlog->error("cannot find key=" + key);
    exit(1); // TODO: better exception handling?
}
