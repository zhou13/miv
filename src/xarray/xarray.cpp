#include "xarray/xarray.hpp"
#include <cassert>

class StupidXArray {
public:
    StupidXArray() {}
    StupidXArray(const std::wstring &str) : m_str(str) {}
    ~StupidXArray() {}

    size_t size() const { return m_str.size(); }
    size_t lines() const {
        return count(m_str.begin(), m_str.end(), '\n')  + 1;
    };
    void assign(const std::wstring &str) { m_str = str; }

    void insert(size_t pos, const std::wstring &value) {
        m_str.insert(pos, value);
    }

    void erase(size_t pos, size_t len) {
        m_str.erase(pos, len);
    }

    wstring getline(size_t x) const {
        if (x >= lines())
            return wstring();
        wstring ans;
        for (size_t i = point_to_cursor(Point(x, 0));
             i < m_str.size() && m_str[i] != '\n';
             ++i) {
            ans += m_str[i];
        }
        return ans;
    }
    wstring getline(size_t x, size_t y1, size_t y2) const {
        wstring s = getline(x);
        if (y1 >= s.size() || y2 <= y1)
            return wstring();
        return s.substr(y1, y2 - y1);
    }

    Point cursor_to_point(size_t c) const {
        assert(c < size());

        Point p(0, 0);
        p.x = std::count(m_str.begin(), m_str.begin() + c, '\n');
        size_t i = c;
        while (i > 0 && m_str[i - 1] != '\n')
            -- i;
        p.y = c - i;
        return p;
    }
    size_t point_to_cursor(Point p) const {
        Point t(0, 0);
        for (size_t i = 0; i < m_str.size(); ++i) {
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
    assign(init_value);
}

XArray::~XArray()
{
}

size_t XArray::size() const
{
    return m_stupid_xarray->size();
    //return m_str.size();
}

size_t XArray::lines() const
{
    return m_stupid_xarray->lines();
    //return count(m_str.begin(), m_str.end(), '\n')  + 1;
}

void XArray::assign(const std::wstring &str)
{
    m_stupid_xarray->assign(str);
    //m_str = str;
}


void XArray::insert(size_t pos, const std::wstring &value)
{
    m_stupid_xarray->insert(pos, value);
    //m_str.insert(pos, value);
}


void XArray::erase(size_t pos, size_t len)
{
    m_stupid_xarray->erase(pos, len);
    //m_str.erase(pos, len);
}

wstring XArray::getline(size_t x) const
{
    return m_stupid_xarray->getline(x);
    /*
    if (x >= lines())
        return wstring();
    wstring ans;
    for (size_t i = point_to_cursor(Point(x, 0));
         i < m_str.size() && m_str[i] != '\n';
         ++i) {
        ans += m_str[i];
    }
    return ans;
    */
}

wstring XArray::getline(size_t x, size_t y1, size_t y2) const
{
    return m_stupid_xarray->getline(x, y1, y2);
    /*
    wstring s = getline(x);
    if (y1 >= s.size() || y2 <= y1)
        return wstring();
    return s.substr(y1, y2 - y1);
    */
}

Point XArray::cursor_to_point(size_t c) const
{
    return m_stupid_xarray->cursor_to_point(c);
    /*
    assert(c < size());

    Point p(0, 0);
    p.x = std::count(m_str.begin(), m_str.begin() + c, '\n');
    size_t i = c;
    while (i > 0 && m_str[i - 1] != '\n')
        -- i;
    p.y = c - i;
    return p;
    */
}

size_t XArray::point_to_cursor(Point p) const
{
    return m_stupid_xarray->point_to_cursor(p);
    /*
    Point t(0, 0);
    for (size_t i = 0; i < m_str.size(); ++i) {
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
