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
    //printf("Miv.constructor\n");
}

Miv::~Miv()
{
    //printf("Miv.destructor\n");
}

void Miv::init()
{
    unique_ptr<XArray> array = make_unique<XArray>();
    unique_ptr<File> file = make_unique<File>(this, array.get(), "miv.txt");
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
    //DEFINE_SCOPE_LOGGER;
    //mlog->debug("key={}", key.to_string());
    m_controller->key_press(key);
    for (;;) {
		auto action = m_controller->pop_next_action();
		if (action == nullptr)
			break;
		action->perform();
	}
    //mlog->debug("cursor=({},{})", m_currframe->cursor().x,m_currframe->cursor().y);
    //m_currframe->array()->D_print();
}

void Miv::redraw(Frame *frame) {
    if (frame == nullptr) {
        for (auto &fr: m_frames) {
            redraw(fr.get());
        }
        return;
    }

    //DEFINE_SCOPE_LOGGER;
    auto size = m_ui->ask_size(frame_index(frame),
                               m_currframe->gutter_sample());
    m_currframe->set_size(size);
    m_ui->paint(frame_index(frame), frame->draw());
}

Frame *Miv::frame(num id)
{
    if (id == -1)
        return m_currframe;
    return m_frames[id].get();
}

num Miv::frame_index(const Frame *frame) const
{
    for (num i = 0; i < (num)m_frames.size(); ++i) {
        if (m_frames[i].get() == frame) {
            return i;
        }
    }
    return -1;
}
