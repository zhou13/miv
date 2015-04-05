#pragma once
/**
 *
 * \class XArray
 * \defgroup XArray
 * \ingroup XArray
 *
 * \brief
 * Maintain the content of editing file.
 *
 * \author $Author: bv $
 *
 * \version $Revision: 1.5 $
 *
 * \date $Date: 2005/04/14 14:16:20 $
 *
 * Contact: bv@bnl.gov
 *
 * Created on: Wed Apr 13 18:39:37 2005
 *
 *
 */

#include "utils/utils.hpp"
#include <string>

class StupidXArray;
class SplitList;

// maintain an array of char: S[0..n-1]
class XArray {
public:
    XArray();
    XArray(const std::wstring &init_value);
	~XArray();

    void set_tab_width(num width);

    num size() const;
    num lines() const;

    void assign(const std::wstring &value);
    void insert(Point pos, const std::wstring &value);
    void erase(Point pos, num len);

    void delete_line(num x);
    wstring getline(num x) const;
    wstring getline(num x, num y1, num y2) const;
    void setline(num x, const wstring &value);
    void setline(num x, num y1, num y2, const wstring &value);

    Point virtual_to_normal(Point vp) const;
    Point normal_to_virtual(Point np) const;

private:
    num _size() const;
    num _lines() const;
    num _line_size(num x) const;

    void _assign(const std::wstring &value);
    void _insert(num pos, const std::wstring &value);
    void _erase(num pos, num len);
    wstring _getline(num x) const;
    wstring _getline(num x, num y1, num y2) const;

    Point _c2p(num c) const;
    num _p2c(Point p) const;


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
