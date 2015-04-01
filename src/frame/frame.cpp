#include "frame/frame.hpp"
#include "miv/miv.hpp"
#include "xarray/xarray.hpp"

Frame::Frame(Miv *miv, XArray *array) :
    m_miv(miv),
    m_array(array),
    m_mode(Mode::NORMAL),
    m_cursor(0, 0),
    m_page(0, 0, 0, 0)
{
}

Frame::~Frame()
{
}

void Frame::set_cursor(Point point)
{
    (void)point;
    // todo
}

void Frame::move_cursor(Vector offset)
{
    Vector ncursor = m_cursor + offset;
    Point absolute_cursor = m_page.origin + ncursor;

    printf("Frame.move_cursor.begin: (%d, %d)\n",
           (int)ncursor.x, (int)ncursor.y);

    ptrdiff_t lines = m_array->lines();
    if (absolute_cursor.x >= lines) {
        ptrdiff_t delta = absolute_cursor.x - lines + 1;
        ncursor.x -= delta;
        absolute_cursor.x -= delta;
    }
    if (absolute_cursor.x < 0) {
        ptrdiff_t delta = -absolute_cursor.x;
        ncursor.x += delta;
        absolute_cursor.x += delta;
    }

    printf("Frame.move_cursor.middle: (%d, %d)\n",
           (int)ncursor.x, (int)ncursor.y);

    ptrdiff_t line_width = m_array->getline(absolute_cursor.x).length();
    if (absolute_cursor.y >= line_width) {
        ptrdiff_t delta = absolute_cursor.y - line_width + 1;
        ncursor.y -= delta;
    }
    if (absolute_cursor.y < 0) {
        ptrdiff_t delta = -absolute_cursor.y;
        ncursor.y += delta;
    }

    m_cursor = ncursor;
    printf("Frame.move_cursor.end: (%d, %d)\n",
           (int)ncursor.x, (int)ncursor.y);
    adjust_page();
}

void Frame::move_page(ptrdiff_t offset)
{
    (void)offset;
    // todo
}

void Frame::adjust_page()
{
    if (m_cursor.x < 0) {
        m_page += Vector(m_cursor.x, 0);
        m_cursor.x = 0;
    }
    if ((size_t)m_cursor.x >= m_page.height()) {
        m_page += Vector(m_cursor.x - m_page.height(), 0);
        m_cursor.x = m_page.height()-1;
    }
    // TODO horizontal scroll
}

void Frame::set_mode(Mode mode)
{
    std::printf("Frame.set_mode: %s\n", MODE_TO_STRING(mode).c_str());
    m_mode = mode;
    m_miv->draw(this);
}

void Frame::set_size(Size size)
{
    std::printf("Frame.set_size: (%d %d)\n",
                (int)size.height, (int)size.width);
    m_page.size = size;
    m_miv->draw(this);
}

vector<ScreenCell> Frame::gutter()
{
    return vector<ScreenCell>();
}

Screen Frame::draw()
{
    Screen screen;
    screen.cursor = m_cursor;
    screen.cells.resize(m_page.height());
    for (auto &line: screen.cells)
        line.resize(m_page.width());

    for (size_t x = m_page.x1(); x < m_page.x2(); ++x) {
        auto line = m_array->getline(x, m_page.y1(), m_page.y2());
        auto iter = screen.cells[x - m_page.x1()].begin();
        for (auto &ch: line) {
            (*iter++).ch = ch;
        }
    }

    return screen;
}
