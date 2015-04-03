#pragma once

#include "utils/common.hpp"


enum class Key {
    KEY_0,
    KEY_1,
};

struct KeyCombo {
    bool control, alt, shift;
    char key;
    KeyCombo() = default;
    KeyCombo(char key) : control(false), alt(false), shift(false), key(key) {}

    bool operator <(const KeyCombo &k) const {
        if (control != k.control)
            return control;
        if (alt != k.alt)
            return alt;
        if (shift != k.shift)
            return shift;
        if (key != k.key)
            return key < k.key;
        return false;
    }
};

inline KeyCombo make_key_combo(string str) {
    // TODO keycombo
    return KeyCombo();
}

struct MouseCommbo {
    bool control, alt, shift;
    int status;
};

