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

    Mode mode() const { return m_mode; }
    void set_mode(Mode mode);

    // cursor/page control
    Vector cursor() const { return m_cursor; }
    void set_cursor(Point point);
    void move_cursor(Vector offset);
    void move_page(ptrdiff_t offset);
    void adjust_page();

    // edit
    wchar_t getchar(Point point);
    void setchar(Point point, wchar_t ch);
    wstring getline(ptrdiff_t line_number);
    void setline(ptrdiff_t line_number, wstring str);
    void insert(Point point, wstring str);
    void erase(Point point, size_t );

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
