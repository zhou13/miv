#pragma once

enum class Mode {
    NORMAL,
    INSERT,
    REPLACE,
    VISUAL,
    BLOCK,
    VBLOCK, // visual block
};

inline string MODE_TO_STRING(Mode mode)
{
#define f(x) case Mode::x: return #x
    switch (mode) {
        f(NORMAL);
        f(INSERT);
        f(REPLACE);
        f(VISUAL);
        f(BLOCK);
        f(VBLOCK);
    }
    return "ERROR";
#undef f
}
