#pragma once

#include "utils/utils.hpp"

class Config {
public:
    Config() : m_parent(nullptr) {}
    Config(shared_ptr<Config> parent) : m_parent(parent) {}
    void set_default();

    string get(const string &key) const;
    string operator [](const string &key) const {
        return get(key);
    }
private:
    shared_ptr<Config> m_parent;
    map<string, string> m_fields;
};

