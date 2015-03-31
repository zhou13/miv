#pragma once
#include <ncurses.h>
#include "ui/ui.hpp"

class NcursesUI: public UI {
public:
    NcursesUI();
    virtual ~NcursesUI();

    virtual void run();
    virtual void paint(int frame_id, const Screen &screen);
    virtual Size ask_size(int frame_id, ScreenGrid grid_sample);
};
