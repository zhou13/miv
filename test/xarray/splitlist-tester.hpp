#pragma once

#include <sstream>
#include "xarray/splitlist.hpp"

class SplitList2;

class SplitListTester {
public:
    SplitListTester();
    ~SplitListTester();
    void config(string ind, num val);
    void run();
private:
    num get_setting(string ind) const;
    void dump_all(std::stringstream &ss);
    unique_ptr<SplitList> obj;
    unique_ptr<SplitList2> ref;
    map<string, num> settings;
};