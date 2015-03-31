#pragma once
#include "common.hpp"
#include "miv/miv.hpp"
#include "miv/screen.hpp"

class Miv;

class UI {
public:
	virtual UI() = 0;
	virtual ~UI() = 0;

	virtual void void run() = 0;

	virtual void paint(int frame_id, const Screen &screen) = 0;

	// TODO: add gutter_sample
	virtual Size ask_size(int frame_id, ScreenGrid grid_sample) = 0;

	//virtual void open_file();
private:
	Miv *m_miv;
};
