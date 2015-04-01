#pragma once

#include "common.hpp"
#include "xarray/xarray.hpp"

class Frame {
    XArray* m_array;
    size_t m_cursor, m_scr_begin;
    size_t m_height, m_width;

public:
    Frame(XArray *array);
    ~Frame();

    void move_cursor(Vector offset);
};
