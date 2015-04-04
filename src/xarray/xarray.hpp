#pragma once

#include "utils/common.hpp"
#include <string>

class StupidXArray;

// maintain an array of char: S[0..n-1]
class XArray {
public:
    XArray();
    XArray(const std::wstring &init_value);
	~XArray();

    void set_wrap(num width);

    num size() const;
    num lines() const;

    void assign(const std::wstring &value);
    void insert(Point pos, const std::wstring &value);
    void insertv(Point pos, const std::wstring &value);
    void erase(Point pos, num len);
    void erasev(Point pos, num len);

    wstring getline(num x) const;
    wstring getlinev(num x) const;
    wstring getline(num x, num y1, num y2) const;
    wstring getlinev(num x, num y1, num y2) const;

    void setline(num x, const wstring &value);
    void setlinev(num x, const wstring &value);

    void virtual_to_normal();
    void normal_to_virtual();

private:
    num _size() const;
    num _lines() const;

    void _assign(const std::wstring &value);
    void _insert(num pos, const std::wstring &value);
    void _erase(num pos, num len);
    wstring _getline(num x) const;
    wstring _getline(num x, num y1, num y2) const;
    wstring _setline(num x, const wstring &value) const;

    Point _c2p(num c) const;
    num _p2c(Point p) const;


    unique_ptr<StupidXArray> m_stupid_xarray;
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
