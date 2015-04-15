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

    void insert(num pos, const wstring &value);
    void erase(num begin, num end);

    vector<pair<wchar_t, num>> D_dump() const;
    string D_test() const;
    bool D_check_w(SplitListBlock *cur, num cw) const;

private:
    SplitListBlock *m_head;
    num m_size;
    num m_tab_width;

    SplitListBlock *_resize_tabs(SplitListBlock *cur, num cw) const;
    SplitListBlock *_resize_single_tab(SplitListBlock *cur, num cw) const;
    SplitListBlock *_make_list(const wstring &str, num begin, num end, num cw) const;
    SplitListBlock *_split(SplitListBlock *cur, num pos, SplitListBlock *&tmp) const;
    SplitListBlock *_concat(SplitListBlock *cur, SplitListBlock *tmp, num cw) const;
    SplitListBlock *_try_merge(SplitListBlock *cur) const;
};
