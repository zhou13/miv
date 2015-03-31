#pragma once
#include "common.hpp"

struct Gutter {
	// TOOD ~~
};

struct ScreenGrid {
	wchar_t ch;
	// TODO: {bg,fg}colors, fonts, ...
};

struct Screen {
	Gutter gutter;
	vector<vector<ScreenGrid>> grids;
};
