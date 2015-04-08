#pragma once

#include "utils/utils.hpp"

class SplitListBlock;

class SplitList {
public:
    SplitList();
    ~SplitList();
    void assign(const wstring &str);
    void set_tab_width(num width);

    num size() const;
    wstring get(num begin, num end) const;

    num count_newline() const;
    num count_newline(num begin, num end) const;
    num find_kth_newline(num k) const;

    num width() const;
    num width(num begin, num end) const;
    num find_visual_pos(num i, num w) const;

    void insert(num pos, const std::wstring &value);
    void erase(num pos, num len);

private:
    SplitListBlock *m_head;
    num m_size;
    num m_tab_width;

    static SplitListBlock *_make_list(const wstring &str, num begin, num end);
    static SplitListBlock *_split(SplitListBlock *cur, num pos, SplitListBlock *&tmp);
    static SplitListBlock *_concat(SplitListBlock *cur, SplitListBlock *tmp);
    static SplitListBlock *_try_merge(SplitListBlock *cur);
};
