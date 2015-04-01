#pragma once
#include "common.hpp"

struct ScreenCell {
	wchar_t ch;
	// TODO: {bg,fg}colors, fonts, ...
};

struct Screen {
    vector<vector<ScreenCell>> cells;
    Vector cursor;
};
