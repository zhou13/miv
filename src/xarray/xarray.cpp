#include "xarray/xarray.hpp"
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
             i < m_str.size() && m_str[i] != '\n';
             ++i) {
            ans += m_str[i];
        }
        return ans;
    }
    wstring getline(num x, num y1, num y2) const {
        wstring s = getline(x);
        if (y1 >= s.size() || y2 <= y1)
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
        for (num i = 0; i < m_str.size(); ++i) {
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
}

XArray::XArray(const std::wstring &init_value)
    : XArray()
{
    _assign(init_value);
}

XArray::~XArray()
{
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

void XArray::erase(num pos, num len)
{
    return _erase(pos, len);
}

std::wstring XArray::getline(num x) const
{
    return _getline(x);
}

std::wstring XArray::getline(num x, num y1, num y2) const
{
    return _getline(x, y1, y2);
}

Point XArray::c2p(num c) const
{
    return _c2p(c);
}

num XArray::p2c(Point p) const
{
    return _p2c(p);
}

num XArray::_size() const
{
    return m_stupid_xarray->size();
    //return m_str.size();
}

num XArray::_lines() const
{
    return m_stupid_xarray->lines();
    //return count(m_str.begin(), m_str.end(), '\n')  + 1;
}

void XArray::_assign(const std::wstring &str)
{
    m_stupid_xarray->assign(str);
    //m_str = str;
}


void XArray::_insert(num pos, const std::wstring &value)
{
    m_stupid_xarray->insert(pos, value);
    //m_str.insert(pos, value);
}


void XArray::_erase(num pos, num len)
{
    m_stupid_xarray->erase(pos, len);
    //m_str.erase(pos, len);
}

wstring XArray::_getline(num x) const
{
    return m_stupid_xarray->getline(x);
    /*
    if (x >= lines())
        return wstring();
    wstring ans;
    for (num i = point_to_cursor(Point(x, 0));
         i < m_str.size() && m_str[i] != '\n';
         ++i) {
        ans += m_str[i];
    }
    return ans;
    */
}

wstring XArray::_getline(num x, num y1, num y2) const
{
    return m_stupid_xarray->getline(x, y1, y2);
    /*
    wstring s = getline(x);
    if (y1 >= s.size() || y2 <= y1)
        return wstring();
    return s.substr(y1, y2 - y1);
    */
}

Point XArray::_c2p(num c) const
{
    return m_stupid_xarray->cursor_to_point(c);
    /*
    assert(c < size());

    Point p(0, 0);
    p.x = std::count(m_str.begin(), m_str.begin() + c, '\n');
    num i = c;
    while (i > 0 && m_str[i - 1] != '\n')
        -- i;
    p.y = c - i;
    return p;
    */
}

num XArray::_p2c(Point p) const
{
    return m_stupid_xarray->point_to_cursor(p);
    /*
    Point t(0, 0);
    for (num i = 0; i < m_str.size(); ++i) {
        if (t.x == p.x && t.y == p.y)
            return i;
        if (m_str[i] == '\n') {
            ++t.x, t.y = 0;
        } else {
            ++t.y;
        }
    }
    if (size() == 0)
        return 0;
    return cursor_to_point(size() - 1).x + 1;
    assert(false);
    return 0;
    */
}
