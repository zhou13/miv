#pragma once

#include "utils/utils.hpp"
#include "boost/any.hpp"

enum class ConfigLevel {
    FRAME,
    FILE,
    PROJECT,
    GLOBAL,
};

class Config {
public:
    Config(ConfigLevel level, shared_ptr<Config> parent) :
        m_level(level), m_parent(parent) {}
    void set_default();

    boost::any get(const string &key);
    boost::any get(const string &key) const;
    void set(const string &key, const boost::any &value);
    boost::any operator [](const string &key) const {
        return get(key);
    }
    boost::any operator [](const string &key) {
        return get(key);
    }

private:
    ConfigLevel m_level;
    shared_ptr<Config> m_parent;
    map<string, boost::any> m_fields;
};
