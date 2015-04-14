#pragma once

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
    unique_ptr<SplitList> obj;
    unique_ptr<SplitList2> ref;
    map<string, num> settings;
};