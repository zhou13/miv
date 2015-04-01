#pragma once

#include "utils/common.hpp"
#include <string>

// maintain an array of char: S[0..n-1]
class XArray {
public:
    XArray();
    XArray(const std::wstring &init_value);
	~XArray();

	// length
	size_t size() const;
    size_t lines() const;

    void assign(const std::wstring &str);

	// insert $value before S[$pos]
	// - $pos in [0, n]
	void insert(size_t pos, const std::wstring &value);

	// delete elements [$pos, $pos+$len)
	// - $pos in [0, size-$len]
	void erase(size_t pos, size_t len);

//    // find the $k-th ($ starting from 0) newline starting from pos;
//    // return size if none
//    size_t find_newline(size_t pos, size_t k);
    wstring getline(size_t x) const;
    wstring getline(size_t x, size_t y1, size_t y2) const;

private:
    wstring m_str;

    Point cur_to_point(size_t c) const;
    size_t point_to_cur(Point p) const;
};
