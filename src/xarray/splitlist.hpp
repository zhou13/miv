#pragma once

#include "utils/common.hpp"

class SplitList {
public:
    SplitList();
    ~SplitList();
    void assign(const wstring &str);

    num size() const;
    num count_newline() const;
    num count_newline(num begin, num end) const;

    size_t find_kth_newline(size_t k) const;
};
