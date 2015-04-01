#include "miv/miv.hpp"
#include "miv/input.hpp"
#include "ui/ui.hpp"
#include "frame/frame.hpp"
#include "file/file.hpp"
#include "miv/controller.hpp"
#include "action/common.hpp"
#include "ui/ui.hpp"
#include "xarray/xarray.hpp"

Miv::Miv(UI *ui) :
    m_ui(ui),
    m_controller(make_unique<Controller>(this))
{
    printf("Miv.constructor\n");
}

Miv::~Miv()
{
    printf("Miv.destructor\n");
}

void Miv::init()
{
    unique_ptr<XArray> array = make_unique<XArray>();
    unique_ptr<File> file = make_unique<File>(this, array.get(), "");
    file->read();
    unique_ptr<Frame> frame = make_unique<Frame>(this, array.get());
    m_currframe = frame.get();
    m_arrays.push_back(std::move(array));
    m_frames.push_back(std::move(frame));
    m_files.push_back(std::move(file));

    m_controller->init();
}

void Miv::key_press(KeyCombo key)
{
    printf("Miv.key_press key=%c\n", key.key);
    m_controller->key_press(key);
    for (;;) {
		auto action = m_controller->pop_next_action();
		if (action == nullptr)
			break;
		action->perform();
	}
}

void Miv::redraw(Frame *frame) {
    if (frame == nullptr) {
        for (auto &fr: m_frames) {
            redraw(fr.get());
        }
        return;
    }
    auto size = m_ui->ask_size(
                frame_index(frame),
                m_currframe->gutter());
    m_currframe->set_size(size);
}

void Miv::draw(Frame *frame)
{
    std::printf("Miv::draw\n");
    if (frame == nullptr) {
        for (auto &fr: m_frames) {
            draw(fr.get());
        }
        return;
    }
    m_ui->paint(frame_index(frame), frame->draw());
}

Frame *Miv::frame(int id)
{
    if (id == -1)
        return m_currframe;
    return m_frames[id].get();
}

int Miv::frame_index(const Frame *frame) const
{
    for (size_t i = 0; i < m_frames.size(); ++i) {
        if (m_frames[i].get() == frame) {
            return i;
        }
    }
    return -1;
}
