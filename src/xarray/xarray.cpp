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

void XArray::set_wrap(num width)
{
    mlog->warn("does not support set_wrap now");
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

void XArray::insertv(Point pos, const std::wstring &value)
{
    DIE("undefined (TODO)."); // TODO
}

void XArray::erase(Point pos, num len)
{
    num p = _p2c(pos);
    _erase(p, len);
}

void XArray::erasev(Point pos, num len)
{
    DIE("undefined (TODO)."); // TODO
}

wstring XArray::getline(num x) const
{
    if (x < 0 || x >= lines()) {
        return wstring();
    }
    return _getline(x);
}

wstring XArray::getlinev(num x) const
{
    DIE("undefined (TODO)."); // TODO
}

wstring XArray::getline(num x, num y1, num y2) const
{
    if (x < 0 || x >= lines()) {
        return wstring();
    }
    return _getline(x, y1, y2);
}

wstring XArray::getlinev(num x, num y1, num y2) const
{
    DIE("undefined (TODO)."); // TODO
}

void XArray::setline(num x, const wstring &value)
{
    num len = _line_size(x);
    setline(x, 0, len, value);
}

void XArray::setlinev(num x, const wstring &value)
{
    DIE("undefined (TODO)."); // TODO
}

void XArray::setline(num x, num y1, num y2, const wstring &value)
{
    num p = _p2c(Point(x, y1));
    _erase(p, y2 - y1);
    _insert(p, value);
}

void XArray::setlinev(num x, num y1, num y2, const wstring &value)
{
    DIE("undefined (TODO)."); // TODO
}

Point XArray::virtual_to_normal(Point vp) const
{
    DIE("undefined (TODO)."); // TODO
}

Point XArray::normal_to_virtual(Point np) const
{
    DIE("undefined (TODO)."); // TODO
}


/*
 * The following is core functions of XArray
 */

num XArray::_size() const
{
    return m_stupid_xarray->size(); /*
    num ans = m_split_list->size();
    if (ans != m_stupid_xarray->size()) {
        DIE("wrong result");
    }
    return ans;*/
}

num XArray::_lines() const
{
    //num ans = m_split_list->count_newline() + 1;
    return m_stupid_xarray->lines();
}

num XArray::_line_size(num x) const
{
    return m_stupid_xarray->line_size(x);
}

void XArray::_assign(const std::wstring &str)
{
    m_stupid_xarray->assign(str);
}


void XArray::_insert(num pos, const std::wstring &value)
{
    if (pos < 0 || pos > _size()) {
        DIE("out of bound");
    }
    m_stupid_xarray->insert(pos, value);
}


void XArray::_erase(num pos, num len)
{
    if (pos < 0 || pos + len > _size()) {
        DIE("out of bound");
    }
    m_stupid_xarray->erase(pos, len);
}

wstring XArray::_getline(num x) const
{
    if (x < 0 || x >= lines()) {
        DIE("out of bound");
    }
    return m_stupid_xarray->getline(x);
}

wstring XArray::_getline(num x, num y1, num y2) const
{
    if (x < 0 || x >= lines()) {
        DIE("out of bound");
    }
    return m_stupid_xarray->getline(x, y1, y2);
}

Point XArray::_c2p(num c) const
{
    return m_stupid_xarray->cursor_to_point(c);
}

num XArray::_p2c(Point p) const
{
    return m_stupid_xarray->point_to_cursor(p);
}
