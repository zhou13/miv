#pragma once

#include "utils/common.hpp"

enum class Key {
    ESCAPE,
    TAB,
    BACKTAB,
    BACKSPACE,
    RETURN,
    ENTER,
    INSERT,
    DELETE,
    PAUSE,
    PRINT,
    SYSREQ,
    CLEAR,
    HOME,
    END,
    LEFT,
    UP,
    RIGHT,
    DOWN,
    PAGE_UP,
    PAGE_DOWN,
    SHIFT,
    CONTROL,
    META,
    ALT,
    ALTGR,
    CAPS_LOCK,
    NUM_LOCK,
    SCROLL_LOCK,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    F16,
    F17,
    F18,
    F19,
    F20,
    F21,
    F22,
    F23,
    F24,
    F25,
    F26,
    F27,
    F28,
    F29,
    F30,
    F31,
    F32,
    F33,
    F34,
    F35,
    SUPER_L,
    SUPER_R,
    MENU,
    HYPER_L,
    HYPER_R,
    HELP,
    DIRECTION_L,
    DIRECTION_R,
    SPACE,
    ANY,
    EXCLAM,
    QUOTE_DBL,
    NUMBER_SIGN,
    DOLLAR,
    PERCENT,
    AMPERSAND,
    APOSTROPHE,
    PAREN_LEFT,
    PAREN_RIGHT,
    ASTERISK,
    PLUS,
    COMMA,
    MINUS,
    PERIOD,
    SLASH,
    NUM_0,
    NUM_1,
    NUM_2,
    NUM_3,
    NUM_4,
    NUM_5,
    NUM_6,
    NUM_7,
    NUM_8,
    NUM_9,
    COLON,
    SEMICOLON,
    LESS,
    EQUAL,
    GREATER,
    QUESTION,
    AT,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    BRACKET_LEFT,
    BACKSLASH,
    BRACKET_RIGHT,
    ASCII_CIRCUM,
    UNDERSCORE,
    QUOTE_LEFT,
    BRACE_LEFT,
    BAR,
    BRACE_RIGHT,
    ASCII_TILDE,
    NOBREAKSPACE,
    EXCLAMDOWN,
    CENT,
    STERLING,
    CURRENCY,
    YEN,
    BROKENBAR,
    SECTION,
    DIAERESIS,
    COPYRIGHT,
    ORDFEMININE,
    GUILLEMOTLEFT,
    NOTSIGN,
    HYPHEN,
    REGISTERED,
    MACRON,
    DEGREE,
    PLUSMINUS,
    TWOSUPERIOR,
    THREESUPERIOR,
    ACUTE,
    MU,
    PARAGRAPH,
    PERIODCENTERED,
    CEDILLA,
    ONESUPERIOR,
    MASCULINE,
    GUILLEMOTRIGHT,
    ONEQUARTER,
    ONEHALF,
    THREEQUARTERS,
    QUESTIONDOWN,
    AGRAVE,
    AACUTE,
    ACIRCUMFLEX,
    ATILDE,
    ADIAERESIS,
    ARING,
    AE,
    CCEDILLA,
    EGRAVE,
    EACUTE,
    ECIRCUMFLEX,
    EDIAERESIS,
    IGRAVE,
    IACUTE,
    ICIRCUMFLEX,
    IDIAERESIS,
    ETH,
    NTILDE,
    OGRAVE,
    OACUTE,
    OCIRCUMFLEX,
    OTILDE,
    ODIAERESIS,
    MULTIPLY,
    OOBLIQUE,
    UGRAVE,
    UACUTE,
    UCIRCUMFLEX,
    UDIAERESIS,
    YACUTE,
    THORN,
    SSHARP,
    DIVISION,
    YDIAERESIS,
    MULTI_KEY,
    CODEINPUT,
    SINGLE_CANDIDATE,
    MULTIPLE_CANDIDATE,
    PREVIOUS_CANDIDATE,
    MODE_SWITCH,
    KANJI,
    MUHENKAN,
    HENKAN,
    ROMAJI,
    HIRAGANA,
    KATAKANA,
    HIRAGANA_KATAKANA,
    ZENKAKU,
    HANKAKU,
    ZENKAKU_HANKAKU,
    TOUROKU,
    MASSYO,
    KANA_LOCK,
    KANA_SHIFT,
    EISU_SHIFT,
    EISU_TOGGLE,
    HANGUL,
    HANGUL_START,
    HANGUL_END,
    HANGUL_HANJA,
    HANGUL_JAMO,
    HANGUL_ROMAJA,
    HANGUL_JEONJA,
    HANGUL_BANJA,
    HANGUL_PREHANJA,
    HANGUL_POSTHANJA,
    HANGUL_SPECIAL,
    DEAD_GRAVE,
    DEAD_ACUTE,
    DEAD_CIRCUMFLEX,
    DEAD_TILDE,
    DEAD_MACRON,
    DEAD_BREVE,
    DEAD_ABOVEDOT,
    DEAD_DIAERESIS,
    DEAD_ABOVERING,
    DEAD_DOUBLEACUTE,
    DEAD_CARON,
    DEAD_CEDILLA,
    DEAD_OGONEK,
    DEAD_IOTA,
    DEAD_VOICED_SOUND,
    DEAD_SEMIVOICED_SOUND,
    DEAD_BELOWDOT,
    DEAD_HOOK,
    DEAD_HORN,
    BACK,
    FORWARD,
    STOP,
    REFRESH,
    VOLUME_DOWN,
    VOLUME_MUTE,
    VOLUME_UP,
    BASS_BOOST,
    BASS_UP,
    BASS_DOWN,
    TREBLE_UP,
    TREBLE_DOWN,
    MEDIA_PLAY,
    MEDIA_STOP,
    MEDIA_PREVIOUS,
    MEDIA_NEXT,
    MEDIA_RECORD,
    MEDIA_PAUSE,
    MEDIA_TOGGLE_PLAY_PAUSE,
    HOME_PAGE,
    FAVORITES,
    SEARCH,
    STANDBY,
    OPEN_URL,
    LAUNCH_MAIL,
    LAUNCH_MEDIA,
    LAUNCH_0,
    LAUNCH_1,
    LAUNCH_2,
    LAUNCH_3,
    LAUNCH_4,
    LAUNCH_5,
    LAUNCH_6,
    LAUNCH_7,
    LAUNCH_8,
    LAUNCH_9,
    LAUNCH_A,
    LAUNCH_B,
    LAUNCH_C,
    LAUNCH_D,
    LAUNCH_E,
    LAUNCH_F,
    LAUNCH_G,
    LAUNCH_H,
    MON_BRIGHTNESS_UP,
    MON_BRIGHTNESS_DOWN,
    KEYBOARD_LIGHT_ON_OFF,
    KEYBOARD_BRIGHTNESS_UP,
    KEYBOARD_BRIGHTNESS_DOWN,
    POWER_OFF,
    WAKE_UP,
    EJECT,
    SCREEN_SAVER,
    WWW,
    MEMO,
    LIGHT_BULB,
    SHOP,
    HISTORY,
    ADD_FAVORITE,
    HOT_LINKS,
    BRIGHTNESS_ADJUST,
    FINANCE,
    COMMUNITY,
    AUDIO_REWIND,
    BACK_FORWARD,
    APPLICATION_LEFT,
    APPLICATION_RIGHT,
    BOOK,
    CD,
    CALCULATOR,
    TO_DO_LIST,
    CLEAR_GRAB,
    CLOSE,
    COPY,
    CUT,
    DISPLAY,
    DOS,
    DOCUMENTS,
    EXCEL,
    EXPLORER,
    GAME,
    GO,
    ITOUCH,
    LOG_OFF,
    MARKET,
    MEETING,
    MENU_KB,
    MENU_PB,
    MY_SITES,
    NEWS,
    OFFICEHOME,
    OPTION,
    PASTE,
    PHONE,
    CALENDAR,
    REPLY,
    RELOAD,
    ROTATE_WINDOWS,
    ROTATION_PB,
    ROTATION_KB,
    SAVE,
    SEND,
    SPELL,
    SPLIT_SCREEN,
    SUPPORT,
    TASK_PANE,
    TERMINAL,
    TOOLS,
    TRAVEL,
    VIDEO,
    WORD,
    XFER,
    ZOOM_IN,
    ZOOM_OUT,
    AWAY,
    MESSENGER,
    WEB_CAM,
    MAIL_FORWARD,
    PICTURES,
    MUSIC,
    BATTERY,
    BLUETOOTH,
    WLAN,
    UWB,
    AUDIO_FORWARD,
    AUDIO_REPEAT,
    AUDIO_RANDOM_PLAY,
    SUBTITLE,
    AUDIO_CYCLE_TRACK,
    TIME,
    HIBERNATE,
    VIEW,
    TOP_MENU,
    POWER_DOWN,
    SUSPEND,
    CONTRAST_ADJUST,
    MEDIA_LAST,
    UNKNOWN,
    CALL,
    CAMERA,
    CAMERA_FOCUS,
    CONTEXT_1,
    CONTEXT_2,
    CONTEXT_3,
    CONTEXT_4,
    FLIP,
    HANGUP,
    NO,
    SELECT,
    YES,
    TOGGLE_CALL_HANGUP,
    VOICE_DIAL,
    LAST_NUMBER_REDIAL,
    EXECUTE,
    PRINTER,
    PLAY,
    SLEEP,
    ZOOM,
    CANCEL,
};

struct KeyCombo {
    bool control, super, alt, shift;
    Key key;

    KeyCombo() = default;
    KeyCombo(Key key);
    KeyCombo(string str);
    string to_string();

    bool operator<(const KeyCombo& k) const {
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

namespace std {
template <>
struct hash<KeyCombo> {
    size_t operator()(const KeyCombo& k) const
    {
        return (hash<int>()((int)k.key)
            ^ (hash<bool>()(k.control) >> 10)
            ^ (hash<bool>()(k.alt) >> 11)
            ^ (hash<bool>()(k.super) >> 12)
            ^ (hash<bool>()(k.shift) >> 13));
    }
};
}
