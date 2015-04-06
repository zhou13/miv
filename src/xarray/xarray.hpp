#pragma once

#include "utils/utils.hpp"
#include <string>

class StupidXArray;
class SplitList;

#ifdef get_line
#undef get_line
#endif

class XArray {
public:
    XArray();
	~XArray();

    void assign(const wstring &value);
    void set_tab_width(num width);

    num size() const;
    num lines() const;
    num line_size(num x) const;
    num line_size_v(num x) const;

    void insert(Point pos, const wstring &value);
    void insert_line(num x, const wstring &value);
    void erase(Point pos, num len);
    void erase_line(num x, num n);

    wstring get(Point pos, num len) const;
    wstring get_line(num x) const;

    Point visual_to_normal(Point vp) const;
    Point normal_to_visual(Point np) const;

private:
    num _size() const;
    num _lines() const;
    num _line_size(num x) const;
    num _line_size_v(num x) const;

    void _assign(const std::wstring &value);
    void _insert(num pos, const std::wstring &value);
    void _erase(num pos, num len);
    wstring _getline(num x) const;
    wstring _getline(num x, num y1, num y2) const;

    Point _c2p(num c) const;
    num _p2c(Point p) const;

    num m_tab_width;
    unique_ptr<StupidXArray> m_stupid_xarray;
    unique_ptr<SplitList> m_split_list;
};

/*
    class iterator {
        XArray *xarray;
        num i;
    public:
        iterator (XArray *xarray, num i)
            :xarray(xarray), i(i) {}
        iterator &operator++() {
            ++i;
            return *this;
        }
        iterator &operator--() {
            --i;
            return *this;
        }
        wchar_t operator*() {
            return xarray->m_str[i];
        }
    };
*/
