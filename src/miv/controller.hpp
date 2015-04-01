#pragma once

#include "common.hpp"
#include "action/action.hpp"'
#include "miv/input.hpp"

class Miv;

class Controller {
public:
    Controller(Miv *miv);
    void init();
    void key_press(KeyCombo key);
    Action *pop_next_action();
    void register_keys(const vector<KeyCombo> &keys,
                       shared_ptr<Action> action);

private:
    Miv *miv;
    queue<Action *> m_actions;
    map<vector<KeyCombo>, vector<shared_ptr<Action>>> m_keymap;
};
