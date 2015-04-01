#include "common.hpp"
#include "miv/controller.hpp"
#include "action/action.hpp"
#include "miv/miv.hpp"

Controller::Controller(Miv *miv) :
    miv(miv)
{
}

void Controller::init()
{
//    shared_ptr<Action> flush = dynamic_pointer_cast<Action>(
//                make_shared<FlushAction>(miv));
//    shared_ptr<Action> down = dynamic_pointer_cast<Action>(
//                make_shared<MoveAction>(miv->frame(), Vector(1, 0)));
//    register_keys(vector<KeyCombo>('j'), down);
//    register_keys(vector<KeyCombo>('j'), flush);
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
                               shared_ptr<Action> action)
{
    m_keymap[keys].push_back(action);
}
