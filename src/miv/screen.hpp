#pragma once

enum class CursorShape {
    BLOCK,
    IBLEAM,
    UNDERLINE,
};

enum class ScreenCellType {
    TEXT,
    LINENUMBER
};

struct ScreenCell {
    ScreenCellType type;
    union {
        struct {
            wchar_t ch;
        };
        struct {
            bool enabled;
            ptrdiff_t line_number;
            size_t width;
        };
    };
    static ScreenCell make_text(wchar_t ch) {
        ScreenCell cell;
        cell.type = ScreenCellType::TEXT;
        cell.ch = ch;
        return cell;
    }
    static ScreenCell make_line_number(bool e, ptrdiff_t num, size_t w) {
        ScreenCell cell;
        cell.type = ScreenCellType::LINENUMBER;
        cell.enabled = e;
        cell.line_number = num;
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
