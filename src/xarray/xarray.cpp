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
        assert(false);
        return 0;
    }
private:
    wstring m_str;
};


XArray::XArray()
{
    m_stupid_xarray = make_unique<StupidXArray>();
    m_split_list = make_unique<SplitList>();
}

XArray::XArray(const std::wstring &init_value)
    : XArray()
{
    _assign(init_value);
}

XArray::~XArray()
{
}

void XArray::set_tab_width(num width)
{
    mlog->warn("does not support now");
}

num XArray::size() const
{
    return _size();
}

num XArray::lines() const
{
    return _lines();
}

void XArray::assign(const std::wstring &value)
{
    return _assign(value);
}

void XArray::insert(Point pos, const std::wstring &value)
{
    num p = _p2c(pos);
    _insert(p, value);
}

void XArray::erase(Point pos, num len)
{
    num p = _p2c(pos);
    _erase(p, len);
}

void XArray::delete_line(num x)
{
    assert(x >= 0 && x < _lines());
    if (_lines() == 1) {
        _erase(0, _size());
        return;
    }
    num p1 = _p2c(Point(x, 0));
    num p2 = _p2c(Point(x, _line_size(x) - 1)) + 1;
    if (x == 0) {
        ++p2;
    }
    else {
        --p1;
    }
    _erase(p1, p2 - p1);
}

wstring XArray::getline(num x) const
{
    if (x < 0 || x >= _lines()) {
        return wstring();
    }
    return _getline(x);
}

wstring XArray::getline(num x, num y1, num y2) const
{
    DEFINE_SCOPE_LOGGER;
    if (x < 0 || x >= _lines()) {
        return wstring();
    }
    y1 = max(y1, (num)0);
    y2 = min(y2, _line_size(x));
    if (y1 > y2) {
        return wstring();
    }
    return _getline(x, y1, y2);
}

void XArray::setline(num x, const wstring &value)
{
    num len = _line_size(x);
    setline(x, 0, len, value);
}

void XArray::setline(num x, num y1, num y2, const wstring &value)
{
    if (x < 0 || x >= lines()) {
        DIE("out of bound");
    }
    y1 = max(y1, (num)0);
    y2 = min(y2, _line_size(x));
    if (y1 > y2) {
        DIE("out of bound");
    }
    num p = _p2c(Point(x, y1));
    _erase(p, y2 - y1);
    _insert(p, value);
}

Point XArray::virtual_to_normal(Point vp) const
{
    DIE("undefined (TODO)."); // TODO
}

Point XArray::normal_to_virtual(Point np) const
{
    DIE("undefined (TODO)."); // TODO
}


/* *************************************************************************
 *
 * The following is core functions of XArray
 *
 * *************************************************************************
 */

//#define ___USE_STUPID

num XArray::_size() const
{
    //DEFINE_SCOPE_LOGGER;
#ifdef ___USE_STUPID
    return m_stupid_xarray->size();
#else
    num ans = m_split_list->size();
    if (ans != m_stupid_xarray->size()) {
        DIE("wrong result");
    }
    return ans;
#endif
}

num XArray::_lines() const
{
    //DEFINE_SCOPE_LOGGER;
#ifdef ___USE_STUPID
    return m_stupid_xarray->lines();
#else
    num ans = m_split_list->count_newline() + 1;
    if (ans != m_stupid_xarray->lines()) {
        DIE("wrong result");
    }
    return ans;
#endif
}

num XArray::_line_size(num x) const
{
    //DEFINE_SCOPE_LOGGER;
#ifdef ___USE_STUPID
    return m_stupid_xarray->line_size(x);
#else
    if (x < 0 || x >= _lines()) {
        DIE("out of bound");
    }
    num i = (x == 0 ? 0 : m_split_list->find_kth_newline(x - 1) + 1);
    num j = m_split_list->find_kth_newline(x);
    num ans = j - i;
    if (ans != m_stupid_xarray->line_size(x)) {
        DIE("wrong result");
    }
    return ans;
#endif
}

void XArray::_assign(const std::wstring &str)
{
    //DEFINE_SCOPE_LOGGER;
#ifdef ___USE_STUPID
    m_stupid_xarray->assign(str);
#else
    m_split_list->assign(str);
    m_stupid_xarray->assign(str);
#endif
}


void XArray::_insert(num pos, const std::wstring &value)
{
    //DEFINE_SCOPE_LOGGER;
    if (pos < 0 || pos > _size()) {
        DIE("out of bound");
    }
    if (value.size() == 0) {
        return;
    }
#ifdef ___USE_STUPID
    m_stupid_xarray->insert(pos, value);
#else
    m_split_list->insert(pos, value);
    m_stupid_xarray->insert(pos, value);
#endif
}


void XArray::_erase(num pos, num len)
{
    //DEFINE_SCOPE_LOGGER;
    if (pos < 0 || pos + len > _size()) {
        DIE("out of bound");
    }
#ifdef ___USE_STUPID
    m_stupid_xarray->erase(pos, len);
#else
    m_split_list->erase(pos, len);
    m_stupid_xarray->erase(pos, len);
#endif
}

wstring XArray::_getline(num x) const
{
    //DEFINE_SCOPE_LOGGER;
#ifdef ___USE_STUPID
    return m_stupid_xarray->getline(x);
#else
    if (x < 0 || x >= _lines()) {
        DIE("out of bound");
    }
    num i = (x == 0 ? 0 : m_split_list->find_kth_newline(x - 1) + 1);
    num j = m_split_list->find_kth_newline(x);
    wstring ans = m_split_list->get(i, j);
    if (ans != m_stupid_xarray->getline(x)) { // TODO delete
        DIE("wrong result");
    }
    return ans;
#endif
}

wstring XArray::_getline(num x, num y1, num y2) const
{
    //DEFINE_SCOPE_LOGGER;
#ifdef ___USE_STUPID
    return m_stupid_xarray->getline(x, y1, y2);
#else
    if (x < 0 || x >= _lines()) {
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
    if (c < 0 || c >= _size()) {
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
    if (p.x < 0 || p.x >= _lines()) {
        DIE("out of bound");
    }
    if (p.y < 0 || p.y > _line_size(p.x)) {
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
