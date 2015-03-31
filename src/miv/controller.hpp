#pragma once
#include "common.hpp"
#include "action/action.hpp"

struct KeyStatus {
	bool control, alt, shift;
};

class Controller {
public:
	void key_press(KeyStatus ks, char key);
	shared_ptr<Action> pop_next_action();
private:
	queue<shared_ptr<Action>> m_actions;
};
