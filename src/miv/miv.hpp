#pragma once
#include "common.hpp"
#include "ui/ui.hpp"
#include "frame/frame.hpp"
#include "file/file.hpp"
#include "miv/controller.hpp"

class UI;

class Miv {
public:
	Miv();
	~Miv();
	void init();

	void key_press(KeyStatus ks, char key);
	//void mouse_down(KeyStatus ks, Vector p);
	//void mouse_move(KeyStatus ks, Vector p);
	//void mouse_up();
	//void menu_click(int memu_id);
	void repaint(int frame_id);
private:
	vector<unique_ptr<Frame>> m_frames;
	vector<unique_ptr<XArray>> m_xarrays;
	vector<unique_ptr<File>> m_files;
	Controller *m_controller;
	Frame *m_currframe;
};
