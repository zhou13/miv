#pragma once

#include "common.hpp"
#include "xarray/xarray.hpp"

class Frame {
    XArray* m_list;
    size_t m_cursor, m_scr_begin;
    size_t m_height, m_width;

public:
    Frame();
    ~Frame();

    void move_cursor(ptrdiff_t offset_x, ptrdiff_t offset_y);
};
