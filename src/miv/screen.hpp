#pragma once

#include "utils/utils.hpp"

enum class CursorShape {
    BLOCK,
    IBLEAM,
    UNDERLINE,
};

enum class ScreenCellType {
    TEXT = 0,
    LINE_NUMBER,
};

struct ScreenCell {
    ScreenCellType type;
    union {
        struct {
            wchar_t ch;
        };
        struct {
            bool enabled;
            num line_number;
            num width;
        };
    };
    ScreenCell() = default;
    static ScreenCell make_text(wchar_t ch) {
        ScreenCell cell;
        cell.type = ScreenCellType::TEXT;
        cell.ch = ch;
        return cell;
    }
    static ScreenCell make_line_number(bool e, num n, num w) {
        ScreenCell cell;
        cell.type = ScreenCellType::LINE_NUMBER;
        cell.enabled = e;
        cell.line_number = n;
        cell.width = w;
        return cell;
    }

	// TODO: {bg,fg}colors, fonts, ...
};

struct Screen {
    vector<vector<ScreenCell>> cells;
    Vector cursor;
    CursorShape cursor_shape;
};
