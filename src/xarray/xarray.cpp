#include "xarray/xarray.hpp"
#include "xarray/splitlist.hpp"
#include <cassert>

class StupidXArray {
public:
    StupidXArray() {}
    StupidXArray(const std::wstring &str) : m_str(str) {}
    ~StupidXArray() {}

    num size() const { return m_str.size(); }
    num lines() const {
        return count(m_str.begin(), m_str.end(), '\n')  + 1;
    };
    num line_size(num x) const {
        num i = point_to_cursor(Point(x, 0));
        num j = i;
        while (j < (num)m_str.size() && m_str[j] != '\n')
            ++j;
        return j - i;
    }
    void assign(const std::wstring &str) { m_str = str; }

    void insert(num pos, const std::wstring &value) {
        m_str.insert(pos, value);
    }

    void erase(num pos, num len) {
        m_str.erase(pos, len);
    }

    wstring getline(num x) const {
        if (x >= lines())
            return wstring();
        wstring ans;
        for (num i = point_to_cursor(Point(x, 0));
             i < (num)m_str.size() && m_str[i] != '\n';
             ++i) {
            ans += m_str[i];
        }
        return ans;
    }
    wstring getline(num x, num y1, num y2) const {
        wstring s = getline(x);
        if (y1 >= (num)s.size() || y2 <= y1)
            return wstring();
        return s.substr(y1, y2 - y1);
    }

    Point cursor_to_point(num c) const {
        assert(c < size());

        Point p(0, 0);
        p.x = std::count(m_str.begin(), m_str.begin() + c, '\n');
        num i = c;
        while (i > 0 && m_str[i - 1] != '\n')
            -- i;
        p.y = c - i;
        return p;
    }
    num point_to_cursor(Point p) const {
        Point t(0, 0);
        for (num i = 0; i < (num)m_str.size(); ++i) {
            if (t.x == p.x && t.y == p.y)
                return i;
            if (m_str[i] == '\n') {
                ++t.x, t.y = 0;
            } else {
                ++t.y;
            }
        }
        if (t == p)
            return (num)m_str.size();
        assert(false);
        return 0;
    }
private:
    wstring m_str;
};

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

    The content is storaged by a SplitList, namely *m_split_list*.
    For convenience, string would be appended an EOF symbol.
    Thus the size of xarray is the size of its m_split_list minus one.

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
            defined by real coordinate.
        \f$y_v\f$ is the total width of all chars before this char
            in that line.
        See that this char occupies visual positions \f$[y_v,y_v+w)\f$
            of the \f$x_v\f$-th line, where \f$w\f$ is its width.

    
    \sa SplitList
*/

/*!
    Construct an empty xarray.
    The text is empty and the tab width is 4 by default.
*/
XArray::XArray()
{
    m_stupid_xarray = make_unique<StupidXArray>();
    m_split_list = make_unique<SplitList>();
    m_tab_width = 4;
    assign(wstring());
}

/*!
    Destructor of the xarray.
*/
XArray::~XArray()
{
}

/*!
    Check if this Xarray is empty.
*/
bool XArray::empty()
{
    return size() == 0;
}

/*!
    Set this Xarray to empty.
*/
void XArray::clear()
{
    assign(wstring());
}

/*!
    Set the width of tabs. By default the width is 4.

    Time complexity: \f$O(size)\f$.
    \param[in] width Must have \f$width \ge 1\f$.
    We also assume that \f$width\f$ is a small constant
    (normally smaller than 10).
    The xarray would run slow with large tab width and many tabs.
*/
void XArray::set_tab_width(num width)
{
    m_split_list->set_tab_width(width);
}

/*!
    Size.

    Time complexity: \f$O(1)\f$.
    \return Guarantee \f$size \ge 0\f$.
*/
num XArray::size() const
{
    //DEFINE_SCOPE_LOGGER;
#ifdef ___USE_STUPID
    return m_stupid_xarray->size();
#else
    num ans = m_split_list->size() - 1;
    if (ans != m_stupid_xarray->size()) {
        DIE("wrong result");
    }
    return ans;
#endif
}

/*!
    Number of lines.

    Time complexity: \f$O(\sqrt{size})\f$.
    \return Guarantee \f$lines \ge 1\f$.
*/
num XArray::lines() const
{
    //DEFINE_SCOPE_LOGGER;
#ifdef ___USE_STUPID
    return m_stupid_xarray->lines();
#else
    num ans = m_split_list->count_newline();
    if (ans != m_stupid_xarray->lines()) {
        DIE("wrong result");
    }
    return ans;
#endif
}

/*!
    Number of chars in that line.

    Time complexity: \f$O(\sqrt{size})\f$.

    \param[in] x Must have \f$0 \le x < lines\f$.
    \return Guarantee \f$linesize_x \ge 0\f$.
*/
num XArray::line_size(num x) const
{
    //DEFINE_SCOPE_LOGGER;
#ifdef ___USE_STUPID
    return m_stupid_xarray->line_size(x);
#else
    if (x < 0 || x >= lines()) {
        DIE("out of bound");
    }
    num i = m_split_list->find_kth_newline(x - 1) + 1;
    num j = m_split_list->find_kth_newline(x);
    num ans = j - i;
    if (ans != m_stupid_xarray->line_size(x)) {
        DIE("wrong result");
    }
    return ans;
#endif
}

/*!
    Total width of chars in that line; i.e., its visual size.

    Time complexity: \f$O(\sqrt{size})\f$.

    \param[in] x Must have \f$0 \le x < lines\f$.
    \return Guarantee \f$linesize_x \ge 0\f$.
*/
num XArray::line_size_v(num x) const
{
    if (x < 0 || x >= lines()) {
        DIE("out of bound");
    }
    num i = m_split_list->find_kth_newline(x - 1) + 1;
    num j = m_split_list->find_kth_newline(x);
    return m_split_list->width(i, j);
}

XArray::iterator XArray::begin() const
{
    return iterator(this, Point(0, 0));
}

XArray::iterator XArray::end() const
{
    return iterator(this, Point(lines() - 1, line_size(lines() - 1)));
}

XArray::iterator XArray::line_begin(num x) const
{
    return iterator(this, Point(x, 0));
}

XArray::iterator XArray::line_end(num x) const
{
    return iterator(this, Point(x, line_size(x)));
}

/*!
    Clear the xarray and assign its text value.
    By default the text is empty.

    Time complexity: \f$O(oldsize + newsize)\f$.
    \param[in] value After the operation,
    the text in xarray would be \f$value\f$.
*/
void XArray::assign(const std::wstring &value)
{
    //DEFINE_SCOPE_LOGGER;
#ifdef ___USE_STUPID
    m_stupid_xarray->assign(value);
#else
    m_split_list->assign(value + (wchar_t)('\n'));
    m_stupid_xarray->assign(value);
#endif
}

/*!
    Insert some text before a position.

    Time complexity: \f$O(\sqrt{size} + valuesize)\f$.
    \param[in] pos
    Real coordinate.
    Must have \f$0 \le x < lines, 0 \le y \le linesize_x\f$.
    If \f$y = linesize_x\f$, it means to insert at the end of the line.
    \param[in] value
    Can contain any char: tabs, newlines, etc.
*/
void XArray::insert(Point pos, const wstring &value)
{
    //DEFINE_SCOPE_LOGGER;
    if (value.size() == 0) {
        return;
    }
    num p = _p2c(pos);
#ifdef ___USE_STUPID
    m_stupid_xarray->insert(p, value);
#else
    m_split_list->insert(p, value);
    m_stupid_xarray->insert(p, value);
#endif
}

void XArray::insert(iterator p, const wstring &value)
{
    insert(p.to_point(), value);
}

///*
//    Insert some text before a line.
//    It would create a new line containing \f$value\f$
//    and make it becomes the \f$x\f$-th line.
//    If \f$value\f$ contain newline symbols,
//    this would insert multiple lines.
//
//    Note that if \f$value\f$ is ending with a newline symbol,
//    an empty line would be inserted before the \f$(x+1)\f$-th line
//    (if exists);
//    for example, insert(5, "a\n") would make the 5-th line becomes "a" and
//        6-th lines become empty, where the former 5-th line becomes the 7-th line.
//
//    Time complexity: \f$O(\sqrt{size} + valuesize)\f$.
//    \param[in] x
//    Must have \f$0 \le x \le lines\f$.
//    \f$x = lines\f$ means to insert at the end of the file.
//    \param[in] value
//    Can contain any char: tabs, newlines, etc.
//*/

/*!
    Erase.
*/
void XArray::erase(Point pos, num len)
{
    num p = _p2c(pos);
    if (p < 0 || p + len > size()) {
        DIE("out of bound");
    }
#ifdef ___USE_STUPID
    m_stupid_xarray->erase(p, len);
#else
    m_split_list->erase(p, p + len);
    m_stupid_xarray->erase(p, len);
#endif
}

void XArray::erase(iterator first, iterator last)
{
    erase(first.to_point(), last - first);
}

wstring XArray::get(Point pos, num len) const
{
    //DEFINE_SCOPE_LOGGER;

    if (pos.x < 0 || pos.x >= lines()) {
        return wstring();
    }
    num n = line_size(pos.x);
    num y1 = pos.y, y2 = pos.y + len;
    y1 = max(y1, (num)0);
    y2 = min(y2, n);
    if (y1 > y2) {
        return wstring();
    }
    return _get(pos.x, y1, y2);
}


wstring XArray::get(iterator first, iterator last) const
{
    return get(first.to_point(), last - first);
}

Point XArray::visual_to_normal(Point vp) const
{
    num i = m_split_list->find_kth_newline(vp.x - 1) + 1;
    num j = m_split_list->find_visual_pos(i, vp.y);
    return Point(vp.x, j - i);
}

Point XArray::normal_to_visual(Point np) const
{
    num i = m_split_list->find_kth_newline(np.x - 1) + 1;
    num j = _p2c(np);
    num x = np.x;
    num y = m_split_list->width(i, j);
    return Point(x, y);
}

void XArray::D_print() const
{
    num _; mlog->debug("- lines={}", _ = lines());
    for (num i = 0; i < _; ++i) mlog->debug(" - line[{}].n={}", i, line_size(i));
}

wstring XArray::_get(num x, num y1, num y2) const
{
    //DEFINE_SCOPE_LOGGER;
#ifdef ___USE_STUPID
    return m_stupid_xarray->getline(x, y1, y2);
#else
    if (x < 0 || x >= lines()) {
        DIE("out of bound");
    }
    num i = (x == 0 ? 0 : m_split_list->find_kth_newline(x - 1) + 1);
    wstring ans = m_split_list->get(i + y1, i + y2);
    if (ans != m_stupid_xarray->getline(x, y1, y2)) {
        DIE("wrong result");
    }
    return ans;
#endif
}

Point XArray::_c2p(num c) const
{
    if (c < 0 || c >= size()) {
        DIE("out of bound");
    }
    //DEFINE_SCOPE_LOGGER;
#ifdef ___USE_STUPID
    return m_stupid_xarray->cursor_to_point(c);
#else
    num x = m_split_list->count_newline(0, c);
    num i = (x == 0 ? 0 : m_split_list->find_kth_newline(x - 1) + 1);
    num y = c - i;
    Point ans(x, y);
    if (ans != m_stupid_xarray->cursor_to_point(c)) {
        DIE("wrong result");
    }
    return ans;
#endif
}

num XArray::_p2c(Point p) const
{
    if (p.x < 0 || p.x >= lines()) {
        DIE("out of bound");
    }
    if (p.y < 0 || p.y > line_size(p.x)) {
        DIE("out of bound");
    }
    //DEFINE_SCOPE_LOGGER;
#ifdef ___USE_STUPID
    return m_stupid_xarray->point_to_cursor(p);
#else
    num i = (p.x == 0 ? 0 : m_split_list->find_kth_newline(p.x - 1) + 1);
    num ans = i + p.y;
    if (ans != m_stupid_xarray->point_to_cursor(p)) {
        DIE("wrong result");
    }
    return ans;
#endif
}
