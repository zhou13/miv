#pragma once

#include "utils/utils.hpp"
#include "frame/mode.hpp"
#include "miv/screen.hpp"

class Miv;
class XArray;
class Frame {
public:
    Frame(Miv *miv, XArray *array);
    ~Frame();

    Mode mode() const { return m_mode; }
    void set_mode(Mode mode);

    // cursor/page control
    Vector cursor() const { return m_cursor; }
    void set_cursor(Point point);
    void move_cursor(Vector offset);
    void adjust_cursor();

    Rect page() const { return m_page; }
    void set_page(Rect m_page);
    void move_page(Vector offset);
    void adjust_page();

    // edit
    XArray *array() { return m_array; }

    // render
    vector<ScreenCell> gutter_sample();
    Size size() const { return m_page.size; }
    void set_size(Size size);
    Screen draw();

private:
    Miv *m_miv;
    XArray* m_array;
    Mode m_mode;

    Vector m_cursor;
    Rect m_page;
};
