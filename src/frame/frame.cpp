#include "frame/frame.hpp"

Frame::Frame(XArray *array) :
    m_array(array)
{
}

Frame::~Frame()
{
}

void Frame::move_cursor(Vector offset)
{
    (void)offset;
}
