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

	size_t size() const;
    size_t lines() const;

    void assign(const std::wstring &str);

	void insert(size_t pos, const std::wstring &value);

	void erase(size_t pos, size_t len);

    wstring getline(size_t x) const;
    wstring getline(size_t x, size_t y1, size_t y2) const;

    Point cursor_to_point(size_t c) const;
    size_t point_to_cursor(Point p) const;
/*
    class iterator {
        XArray *xarray;
        size_t i;
    public:
        iterator (XArray *xarray, size_t i)
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
private:
    unique_ptr<StupidXArray> m_stupid_xarray;
};
