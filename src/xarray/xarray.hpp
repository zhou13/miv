#pragma once

/*!
    \defgroup datastruct Data Structure
    \brief Internal data structure for storaging text.
*/

/*!
    \class XArray
    \ingroup datastruct

    \brief The XArray class maintains the content of editing file.
    
    You can use XArray to storage a std::wstring containing
    normal chars, tabs (whose width can be set), and Unicode chars.

    The indices in XArray are starting from \f$0\f$.
    The coordinates are row-major: \f$x\f$ is the row index and \f$y\f$ is
        the column index.

    There are two ways to locate a char in XArray:
    - by **index**. If you view all chars of the file as an array,
        then one char's index \f$i\f$ is the number of chars before it;
        this also means \f$0 \le i < n\f$ where \f$n\f$ is the total 
        number of chars.

        Note that each char is counted as *one char*, even if it is a
            newline, a tab, or an Unicode char.
    - by **real coordinate**. XArray consider '\\n' as the *newline symbol*.
        If there are \f$k\f$ newline symbols,
            there would be \f$m = k + 1\f$ *lines*.
        Obviously \f$1 \le m \le n + 1\f$.
        The length of the \f$i\f$-th line \f$l_i\f$ is the number of chars
            in that line; the newline symbols *do not* count,
            means that \f$l_i\f$ may be \f$0\f$.

        Then, a pair of integers \f$(x,y)\f$ with
            \f$0 \le x < m, 0 \le y < l_x\f$ is a *real coordinate*,
            corresponding to
            the \f$y\f$-th char in the \f$x\f$-th line.
        Additional, if \f$ x < m-1 \f$, the coordinate \f$(x, l_x)\f$
            corresponds the newline symbol at the end of that line.
    - by **visual coordinate**.
        Each char has a *visual width*.
        Unicode chars usually have a width of 2.
        Normal ascii chars usually have a width of 1.
        A newline has a width of 0.
        The tab char is quite special:
        if the tab width is \f$W\f$, then
        a tab ('\\t') char would have a dynamic width between \f$[1,W]\f$;
            the width would be determined such that its next char's
            starting \f$y\f$ coordinate (visual) is a multiple of \f$W\f$.

        We define \f$(x_v,y_v)\f$ for a char.
        \f$x_v\f$ is simply the row index, namely \f$x\f$
            defined in real coordinate before.
        \f$y_v\f$ is the total width of all chars before this char
            in that line.
        See that this char occupies visual positions \f$(x_v, [y_v,y_v+w))\f$
            where \f$w\f$ is its width.

    
    \sa SplitList
*/

#include "utils/utils.hpp"
#include <string>

class StupidXArray;
class SplitList;

class XArray {
public:
    /*!
        Construct an empty xarray.
    */
    XArray();
    /*!
        Construct a xarray with initial content \a init_value.
    */
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
