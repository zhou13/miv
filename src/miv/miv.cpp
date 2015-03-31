#include "miv/miv.hpp"

void Miv::init() {
}

void Miv::key_press(KeyStatus ks, char key) {
	m_controller->key_press(ks, key);
	while (1) {
		auto action = m_controller->pop_next_action();
		if (action == nullptr)
			break;
		action->perform();
	}
}

void Miv::repaint(int frame_id) {
}
