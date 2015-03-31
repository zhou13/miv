#pragma once
#include "common.hpp"
#include "miv/miv.hpp"

class UI {
public:
	UI();
	virtual ~UI();

	virtual void paint(int frame_id, const Screen &screen) = 0;
	virtual Size ask_size(int frame_id,
	/* TODO: gutter_example, w, h */) = 0;

	//virtual void open_file();
private:
	Miv *m_miv;
};
