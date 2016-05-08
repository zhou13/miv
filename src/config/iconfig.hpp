#pragma once

#include "utils/utils.hpp"
class Config;

class IConfig {
public:
    virtual shared_ptr<Config> config() = 0;
};
