#pragma once

enum class CursorShape {
    BLOCK,
    IBLEAM,
    UNDERLINE,
};

struct ScreenCell {
	wchar_t ch;
	// TODO: {bg,fg}colors, fonts, ...
};

struct Screen {
    vector<vector<ScreenCell>> cells;
    Vector cursor;
    CursorShape cursor_shape;
};
