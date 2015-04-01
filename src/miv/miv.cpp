#include "miv/miv.hpp"

Miv::Miv()
{
    printf("Miv.constructor\n");

    unique_ptr<File> file = make_unique<File>("_"); // TODO: using default now
    wstring file_content = file->read();

    unique_ptr<XArray> array = make_unique<XArray>(file_content);
    unique_ptr<Frame> frame = make_unique<Frame>(array.get());
    m_arrays.push_back(std::move(array));
    m_frames.push_back(std::move(frame));
    m_files.push_back(std::move(file));


    m_controller = make_unique<Controller>(this);
    m_controller->init();
}

Miv::~Miv()
{
    printf("Miv.destructor\n");

}

void Miv::init() {
}

void Miv::key_press(KeyCombo key) {
    printf("Miv.key_press key=%c\n", key.key);
    m_controller->key_press(key);
    for (;;) {
		auto action = m_controller->pop_next_action();
		if (action == nullptr)
			break;
		action->perform();
	}
}

void Miv::repaint(int frame_id) {
    (void)frame_id;
    // TODO
}

void Miv::flush()
{
    // TODO
}

Frame *Miv::frame(int id)
{
    if (id == -1)
        return m_currframe;
    return m_frames[id].get();
}
