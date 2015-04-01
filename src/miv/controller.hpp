#pragma once

#include "utils/common.hpp"
#include "miv/input.hpp"
#include "frame/mode.hpp"

class Miv;
class Action;

class Controller {
public:
    Controller(Miv *miv);
    void init();
    void key_press(KeyCombo key);
    shared_ptr<Action> pop_next_action();
    void register_keys(Mode mode,
                       const vector<KeyCombo> &keys,
                       shared_ptr<Action> action);

private:
    Miv *m_miv;
    queue<shared_ptr<Action>> m_actions;
    map<pair<Mode, vector<KeyCombo>>, vector<shared_ptr<Action>>> m_keymap;
    vector<KeyCombo> m_keys;
};
