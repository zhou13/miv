#include "frame/frame.hpp"

Frame::Frame(XArray *array) :
    m_array(array),
    m_mode(Mode::INSERT),
    m_size(0, 0),
    m_cursor(0, 0),
    m_position(0, 0, 0, 0)
{
}

Frame::~Frame()
{
}

void Frame::move_cursor(Vector offset)
{
    (void)offset;
}

void Frame::set_mode(Mode mode)
{
    m_mode = mode;
}

void Frame::set_size(Size size)
{
    m_size = size;
}

Screen Frame::draw()
{
    return Screen();
}
