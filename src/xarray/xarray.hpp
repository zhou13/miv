#pragma once

#include "utils/utils.hpp"
#include <string>

class StupidXArray;
class SplitList;
class SplitListBlock;

class XArray {
public:
    class iterator {
    public:
        iterator(const XArray *xarray, Point p) : xa(xarray), p(p) {}
        bool operator ==(const iterator &it) const { return xa == it.xa && p == it.p; }
        bool operator !=(const iterator &it) const { return xa != it.xa || p != it.p; }
        iterator &operator ++() { ++p.y; if (p.y > xa->line_size(p.x)) ++p.x, p.y = 0; return *this; }
        iterator &operator --() { --p.y; if (p.y < 0) --p.x, p.y = xa->line_size(p.x); return *this; }
        iterator operator +(num i) const { iterator t = *this; while (i--) ++t; return t; }
        iterator operator -(num i) const { iterator t = *this; while (i--) --t; return t; }
        num operator -(iterator it) const { num n = 0; while (it != *this) ++it, ++n; return n; }
        wchar_t operator*() const { return (xa->get(p, 1))[0]; }
        Point to_point() const { return p; }
    private:
        const XArray *xa; Point p;
    };

    XArray();
	~XArray();
    void assign(const wstring &value);
    void set_tab_width(num width);

    num size() const;
    num lines() const;
    num line_size(num x) const;
    num line_size_v(num x) const;
    iterator begin() const;
    iterator end() const;
    iterator line_begin(num x) const;
    iterator line_end(num x) const;

    wstring get(Point pos, num len) const;
    wstring get(iterator first, iterator last) const;
    void insert(Point pos, const wstring &value);
    void insert(iterator p, const wstring &value);
    void erase(Point pos, num len);
    void erase(iterator first, iterator last);

    Point visual_to_normal(Point vp) const;
    Point normal_to_visual(Point np) const;

private:
    wstring _get(num x, num y1, num y2) const;

    Point _c2p(num c) const;
    num _p2c(Point p) const;

    num m_tab_width;
    unique_ptr<StupidXArray> m_stupid_xarray;
    unique_ptr<SplitList> m_split_list;
};

/*
*/
