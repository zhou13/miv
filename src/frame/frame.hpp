#pragma once
#include <string>
#include <vector>

#include "xarray/xarray.hpp"

struct screen_t {
	std::vector<std::wstring> chars;
	size_t cursor_x, cursor_y;
};

class Frame {
	XArray *m_list;
	size_t m_pos, m_scr_begin;
	size_t m_height, m_width;

public:
	Frame(XArray *list, size_t height, size_t width);
	~Frame();

	void move_cursor(ptrdiff_t offset_x, ptrdiff_t offset_y);
	screen_t dump() const;
};
