#pragma once

#include "utils/utils.hpp"
#include "miv/screen.hpp"

class Miv;
class UI {
public:
    UI();
    virtual ~UI();

    virtual void run() = 0;

    // Draw screen on screen
	virtual void paint(int frame_id, const Screen &screen) = 0;

	// TODO: add gutter_sample
    virtual Size ask_size(int frame_id,
                          const vector<ScreenCell> &gutter_sample) = 0;
	//virtual void open_file();

protected:
    unique_ptr<Miv> m_miv;
};
