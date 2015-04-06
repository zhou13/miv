#pragma once
/*!
    \class SplitList
    \ingroup datastruct

    \brief The SplitList class provides supports for the XArray class
        by implementing a split list (functional?!).

    Use SplitList to maintain an array of wchar_t.

    \sa XArray
*/

#include "utils/utils.hpp"

class SplitListBlock;

class SplitList {
public:
    SplitList();
    ~SplitList();
    void assign(const wstring &str);

    num size() const;
    wstring get(num begin, num end) const;

    num count_newline() const;
    num count_newline(num begin, num end) const;
    /*
        return -1 if k == -1.
    */
    num find_kth_newline(num k) const;

    num width() const;
    num width(num begin, num end) const;
    /*
        find first position j that width(i,j+1)>w
    */
    num find_visual_pos(num i, num w) const;

    void insert(num pos, const std::wstring &value);
    void erase(num pos, num len);

private:
    SplitListBlock *m_head;
    num m_size;

    SplitListBlock *_make_list(const wstring &str, num begin, num end);
    SplitListBlock *_split(SplitListBlock *cur, num pos, SplitListBlock *&tmp);
    SplitListBlock *_concat(SplitListBlock *cur, SplitListBlock *tmp);
    SplitListBlock *_try_merge(SplitListBlock *cur);
};
