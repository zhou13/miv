#pragma once

#include "utils/common.hpp"
#include "frame/mode.hpp"
#include "miv/screen.hpp"

class Miv;
class XArray;
class Frame {
public:
    Frame(Miv *miv, XArray *array);
    ~Frame();

    Vector cursor() const { return m_cursor; }
    void set_cursor(Point point);
    void move_cursor(Vector offset);
    void move_page(ptrdiff_t offset);
    void adjust_page();

    Mode mode() const { return m_mode; }
    void set_mode(Mode mode);
    Size size() const { return m_page.size; }
    void set_size(Size size);
    vector<ScreenCell> gutter_sample();
    Screen draw();

private:
    Miv *m_miv;
    XArray* m_array;
    Mode m_mode;

    Vector m_cursor;
    Rect m_page;
};
