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

    //printf("Frame.move_cursor.begin: (%d, %d)\n",
    //       (int)ncursor.x, (int)ncursor.y);

    num lines = m_array->lines();
    if (absolute_cursor.x >= lines) {
        num delta = absolute_cursor.x - lines + 1;
        ncursor.x -= delta;
        absolute_cursor.x -= delta;
    }
    if (absolute_cursor.x < 0) {
        num delta = -absolute_cursor.x;
        ncursor.x += delta;
        absolute_cursor.x += delta;
    }

    //printf("Frame.move_cursor.middle: (%d, %d)\n",
   //        (int)ncursor.x, (int)ncursor.y);

    num line_width = m_array->getline(absolute_cursor.x).length();
    if (absolute_cursor.y >= line_width) {
        num delta = absolute_cursor.y - line_width + 1;
        ncursor.y -= delta;
    }
    if (absolute_cursor.y < 0) {
        num delta = -absolute_cursor.y;
        ncursor.y += delta;
    }

    m_cursor = ncursor;
    //printf("Frame.move_cursor.end: (%d, %d)\n",
    //       (int)ncursor.x, (int)ncursor.y);
    adjust_page();
}

void Frame::move_page(num offset)
{
    (void)offset;
    mlog->critical("Not implemented!");
}

void Frame::adjust_page()
{
    if (m_cursor.x < 0) {
        m_page += Vector(m_cursor.x, 0);
        m_cursor.x = 0;
    }
    if ((num)m_cursor.x >= m_page.height()) {
        m_page += Vector(m_cursor.x - m_page.height() + 1, 0);
        m_cursor.x = m_page.height() - 1;
        //printf("!!!!!!!!!!!!\n!!!!!!!!!!! x1=%d x2=%d\n",(int)m_page.x1(),(int)m_page.x2());
    }
    if (m_cursor.y < 0) {
        m_page += Vector(0, m_cursor.y);
        m_cursor.y = 0;
    }
    if ((num)m_cursor.y >= m_page.width()) {
        m_page += Vector(0, m_cursor.y - m_page.width() + 1);
        m_cursor.y = m_page.width() - 1;
    }
}

void Frame::set_mode(Mode mode)
{
    DEFINE_SCOPE_LOGGER;
    mlog->debug("mode is set to {}", MODE_TO_STRING(mode));

    m_mode = mode;
    m_miv->redraw(this);
}

void Frame::set_size(Size size)
{
    DEFINE_SCOPE_LOGGER;
    mlog->debug("size is set to ({}, {})", size.height, size.width);

    if (size == m_page.size)
        return;
    m_page.size = size;
    m_miv->redraw(this);
}

vector<ScreenCell> Frame::gutter_sample()
{
    num width = 0, tmp = 1;
    while (m_array->lines() >= tmp) {
        tmp *= 10, width += 1;
    }
    ScreenCell cell = ScreenCell::make_line_number(false, 0, width);
    vector<ScreenCell> line(1, cell);
    return line;
}

Screen Frame::draw()
{
    Screen screen;
    screen.cursor = m_cursor;

    // first: make gutter
    vector<ScreenCell> gsample = gutter_sample();

    for (num x = m_page.x1(); x < m_page.x2(); ++x) {
        vector<ScreenCell> line = gsample;
        for (auto &cell: line) {
            if (cell.type == ScreenCellType::LINE_NUMBER) {
                if (x < m_array->lines()) {
                    cell.enabled = true;
                    cell.line_number = x + 1;
                }
            }
        }
        screen.cells.push_back(line);
    }

    // second: make text
    for (num x = m_page.x1(); x < m_page.x2(); ++x) {
        auto line = m_array->getline(x, m_page.y1(), m_page.y2());
        vector<ScreenCell> &target = screen.cells[x - m_page.x1()];
        for (auto &ch: line) {
            target.push_back(ScreenCell::make_text(ch));
        }
    }

    return screen;
}
