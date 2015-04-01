#pragma once

#include "utils/common.hpp"
#include "frame/mode.hpp"
#include "miv/screen.hpp"

class XArray;
class Frame {
public:
    Frame(XArray *array);
    ~Frame();

    void move_cursor(Vector offset);
    Mode mode() const { return m_mode; }
    void set_mode(Mode mode);
    Size size() { return m_size; }
    void set_size(Size size);
    Screen draw();

private:
    XArray* m_array;
    Mode m_mode;
    Size m_size;
    Point m_cursor;
    Rect m_position;
};
