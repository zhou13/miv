#pragma once

#include "utils/utils.hpp"
#include "config/iconfig.hpp"

class Miv;
class XArray;
class Config;

class File : IConfig {
public:
    File(Miv *m_miv, XArray *array, string filename);
    ~File();
    void read();
    void write();
    shared_ptr<Config> config() {
        return m_config;
    }

private:
    Miv *m_miv;
    XArray *m_array;
    string m_filename;
    shared_ptr<Config> m_config;
};
