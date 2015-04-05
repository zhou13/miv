#pragma once

#include "utils/utils.hpp"

struct SplitListBlock;

class SplitList {
public:
    SplitList();
    ~SplitList();
    void assign(const wstring &str);

    num size() const;
    num count_newline() const;
    num count_newline(num begin, num end) const;
    wstring get(num begin, num end) const;

    void insert(num pos, const std::wstring &value);
    void erase(num pos, num len);

    // k starting from 0; return size() if not found
    num find_kth_newline(num k) const;

private:
    //wstring m_str;
    SplitListBlock *m_head;
    num m_size;

    SplitListBlock *_make_list(const wstring &str, num begin, num end);
    SplitListBlock *_split(SplitListBlock *cur, num pos, SplitListBlock *&tmp);
    SplitListBlock *_concat(SplitListBlock *cur, SplitListBlock *tmp);
    SplitListBlock *_try_merge(SplitListBlock *cur);
};
