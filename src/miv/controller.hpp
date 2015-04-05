#pragma once

#include "utils/utils.hpp"
#include "miv/input.hpp"
#include "frame/mode.hpp"

class Miv;
class Action;

class Controller {
public:
    Controller(Miv *miv);
    ~Controller();
    void init();
    void key_press(KeyCombo key);
    shared_ptr<Action> pop_next_action();
    // Note: 2015/04/04 shared_ptr is required because Action is an interface
    void register_keys(Mode mode,
                       const vector<KeyCombo> &keys,
                       shared_ptr<Action> action);

private:
    Miv *m_miv;
    queue<shared_ptr<Action>> m_actions;

    // registered keys & current key sequence
    map<pair<Mode, vector<KeyCombo>>, vector<shared_ptr<Action>>> m_keymap;
    set<pair<Mode, vector<KeyCombo>>> m_keymap_prefices;
    vector<KeyCombo> m_keys;
};
