#pragma once

#include "common.hpp"
#include "action/action.hpp"'
#include "miv/input.hpp"


class Controller {
public:
    Controller();
    void key_press(KeyCombo key);
    Action *pop_next_action();
    void register_keys(const vector<KeyCombo> &keys,
                       vector<Action> actions);

private:
    queue<Action *> m_actions;
    map<vector<KeyCombo>, vector<Action>> m_keymap;
};
