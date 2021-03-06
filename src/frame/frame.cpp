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

void Frame::set_mode(Mode mode)
{
    DEFINE_SCOPE_LOGGER;
    mlog->debug("mode is set to {}", MODE_TO_STRING(mode));

    m_mode = mode;
    m_miv->redraw(this);
}

void Frame::set_cursor(Point point)
{
    DIE("not implemented")
    adjust_cursor();
}

void Frame::move_cursor(Vector offset)
{
    m_cursor = m_cursor + offset;

    //printf("Frame.move_cursor.begin: (%d, %d)\n",
    //       (int)ncursor.x, (int)ncursor.y);
    adjust_cursor();
}

void Frame::adjust_cursor()
{
    Vector ncursor = m_cursor;
    Point absolute_cursor = m_page.origin + ncursor;
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

    num line_width = m_array->line_size(absolute_cursor.x);
    if (this->mode() == Mode::INSERT)
        ++line_width;
    if (line_width == 0)
        line_width = 1;
    if (absolute_cursor.y >= line_width) {
        num delta = absolute_cursor.y - line_width + 1;
        ncursor.y -= delta;
    }
    if (absolute_cursor.y < 0) {
        num delta = -absolute_cursor.y;
        ncursor.y += delta;
    }

    m_cursor = ncursor;
    adjust_page();
}

void Frame::move_page(Vector offset)
{
    (void)offset;
    DIE("Not implemented!");
}


void Frame::set_page(Rect m_page)
{
    (void)m_page;
    DIE("Not implemented!");
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
    //mlog->debug("page: {},{} - {},{}",m_page.x1(),m_page.y1(),m_page.x2(),m_page.y2());
}


void Frame::set_size(Size size)
{
    if (size == m_page.size)
        return;

    DEFINE_SCOPE_LOGGER;
    mlog->debug("size is set to ({}, {})", size.height, size.width);

    m_page.size = size;
    m_miv->redraw(this);
}

vector<ScreenCell> Frame::gutter_sample()
{
    num width = 0, tmp = 1;
    num line_count = m_array->lines();
    while (line_count >= tmp) {
        tmp *= 10, width += 1;
    }
    ScreenCell cell = ScreenCell::make_line_number(false, 0, width);
    vector<ScreenCell> line(1, cell);
    return line;
}

Screen Frame::draw()
{
    //DEFINE_SCOPE_LOGGER;
    Screen screen;
    screen.cursor = m_cursor;

    // first: make gutter
    vector<ScreenCell> gsample = gutter_sample();

    num line_count = m_array->lines();
    for (num x = m_page.x1(); x < m_page.x2(); ++x) {
        vector<ScreenCell> line = gsample;
        for (auto &cell: line) {
            if (cell.type == ScreenCellType::LINE_NUMBER) {
                if (x < line_count) {
                    cell.enabled = true;
                    cell.line_number = x + 1;
                }
            }
        }
        screen.cells.push_back(line);
    }

    // second: make text
    for (num x = m_page.x1(); x < m_page.x2(); ++x) {
        Point pos(x, m_page.y1());
        num len = m_page.width();
        auto line = m_array->get(pos, len);
        vector<ScreenCell> &target = screen.cells[x - m_page.x1()];
        for (auto &ch: line) {
            target.push_back(ScreenCell::make_text(ch));
        }
    }

    return screen;
}
