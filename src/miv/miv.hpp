#pragma once

#include "utils/utils.hpp"
#include "miv/input.hpp"
#include "config/iconfig.hpp"

class Frame;
class XArray;
class File;
class Controller;
class UI;

class Miv : public IConfig {
public:
    Miv(UI *ui);
	~Miv();
	void init();

    void key_press(KeyCombo key);
    // void mouse_down(KeyStatus ks, Vector p);
    // void mouse_move(KeyStatus ks, Vector p);
    // void mouse_up();
    // void menu_click(int memu_id);

    //void draw(Frame *frame = nullptr);
    void redraw(Frame *frame = nullptr);

    Frame *frame(num id = -1);
    num frame_index(const Frame *frame) const;

    shared_ptr<Config> config() {
        return m_config;
    }

private:
    UI *m_ui;
    Frame *m_currframe;
    vector<unique_ptr<Frame>> m_frames;
    vector<unique_ptr<XArray>> m_arrays;
    vector<unique_ptr<File>> m_files;
    unique_ptr<Controller> m_controller;
    shared_ptr<Config> m_config;
};
