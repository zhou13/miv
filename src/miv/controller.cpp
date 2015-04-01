#include "miv/controller.hpp"
#include "action/action.hpp"

Controller::Controller()
{
    vector<Action *> actions;

    actions.clear();
    actions.push_back(FlushAction());
    actions.push_back(FlushAction());
    register_keys(vector<KeyCombo>('w'), make_unique<FlushAction>())
}

void Controller::key_press(KeyCombo key)
{
    (void)key;
}


Action *Controller::pop_next_action()
{
    if (m_actions.empty())
        return nullptr;
    auto first = m_actions.front();
    m_actions.pop();
    return first;
}

void Controller::register_keys(const vector<KeyCombo> &keys,
                               vector<Action> actions)
{
    m_keymap[keys] = actions;
}
