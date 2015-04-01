#pragma once
#include <ncurses.h>
#include "ui/ui.hpp"
#include "miv/screen.hpp"

class NcursesUI: public UI {
public:
    NcursesUI();
    virtual ~NcursesUI();

    virtual void run();
    virtual void paint(int frame_id, const Screen &screen);
    virtual Size ask_size(int frame_id,
                          const vector<ScreenCell> &gutter_sample);
};
