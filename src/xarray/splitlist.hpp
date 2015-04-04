#pragma once

#include "utils/common.hpp"

class SplitList {
public:
    SplitList();
    ~SplitList();
    void assign(const wstring &str);

    size_t size() const;
    size_t count_newline() const;
    size_t count_newline(size_t begin, size_t end) const;

};
