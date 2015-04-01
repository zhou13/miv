#pragma once

#include "utils/common.hpp"
#include "miv/input.hpp"

class Frame;
class XArray;
class File;
class Controller;
class UI;

class Miv {
public:
    Miv(UI *ui);
	~Miv();
	void init();

    void key_press(KeyCombo key);
    // void mouse_down(KeyStatus ks, Vector p);
    // void mouse_move(KeyStatus ks, Vector p);
    // void mouse_up();
    // void menu_click(int memu_id);

    void draw(Frame *frame = nullptr);
    void redraw(Frame *frame = nullptr);

    Frame *frame(int id = -1);
    int frame_index(const Frame *frame) const;

private:
    UI *m_ui;
    Frame *m_currframe;
    vector<unique_ptr<Frame>> m_frames;
    vector<unique_ptr<XArray>> m_arrays;
    vector<unique_ptr<File>> m_files;
    unique_ptr<Controller> m_controller;
};
