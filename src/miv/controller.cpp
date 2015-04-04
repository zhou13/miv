#include "utils/common.hpp"

#include "miv/controller.hpp"
#include "frame/frame.hpp"
#include "miv/miv.hpp"
#include "action/common.hpp"


Controller::Controller(Miv *miv) :
    m_miv(miv)
{
}

Controller::~Controller()
{

}

void Controller::init()
{
    register_keys(Mode::NORMAL, { KeyCombo("h") },
                  make_shared<CursorMoveLeftAction>(m_miv));
    register_keys(Mode::NORMAL, { KeyCombo("h") },
                  make_shared<FlushAction>(m_miv));
    register_keys(Mode::NORMAL, { KeyCombo("j") },
                  make_shared<CursorMoveDownAction>(m_miv));
    register_keys(Mode::NORMAL, { KeyCombo("j") },
                  make_shared<FlushAction>(m_miv));
    register_keys(Mode::NORMAL, { KeyCombo("k") },
                  make_shared<CursorMoveUpAction>(m_miv));
    register_keys(Mode::NORMAL, { KeyCombo("k") },
                  make_shared<FlushAction>(m_miv));
    register_keys(Mode::NORMAL, { KeyCombo("l") },
                  make_shared<CursorMoveRightAction>(m_miv));
    register_keys(Mode::NORMAL, { KeyCombo("l") },
                  make_shared<FlushAction>(m_miv));
    register_keys(Mode::NORMAL, { KeyCombo("i") },
                  make_shared<EnterInsertModeAction>(m_miv));
    register_keys(Mode::INSERT, { KeyCombo("~") },
                  make_shared<LeaveInsertModeAction>(m_miv));
    register_keys(Mode::NORMAL, { KeyCombo("d"), KeyCombo("d") },
                  make_shared<EnterInsertModeAction>(m_miv));

    for (char ch = 'a'; ch <= 'z'; ++ch) {
        auto action = make_shared<InsertAfterCursorAction>(m_miv, (wchar_t)ch);
        register_keys(Mode::INSERT, { KeyCombo(string(1, 'a')) }, action);
    }
}

void Controller::key_press(KeyCombo key)
{
    //std::printf("Controller.key_press\n");
    m_keys.push_back(key);
    Mode mode = m_miv->frame()->mode();
    auto id = make_pair(mode, m_keys);

    if (m_keymap.find(id) != m_keymap.end()) {
        //std::printf("Controller.key_press: found shortcut\n");
        for (auto &action: m_keymap[id]) {
            m_actions.push(action);
        }
        m_keys.clear(); // TODO: add option (clear or not clear)
    }
    // no this prefix exists
    while (m_keys.size() > 0) {
        auto prefix = make_pair(mode, m_keys);
        if (m_keymap_prefices.find(prefix) != m_keymap_prefices.end())
            break;
        string str = "";
        for (auto &c : m_keys)
            str += c.to_string() + " ";
        mlog->debug("erase key={}, all={}",
                    m_keys.begin()->to_string(), str);
        m_keys.erase(m_keys.begin());
    }
}


shared_ptr<Action> Controller::pop_next_action()
{
    if (m_actions.empty())
        return nullptr;
    auto first = m_actions.front();
    m_actions.pop();
    return first;
}

void Controller::register_keys(Mode mode,
                               const vector<KeyCombo> &keys,
                               shared_ptr<Action> action)
{
    m_keymap[make_pair(mode, keys)].push_back(action);
    vector<KeyCombo> prefix;
    for (auto &k: keys) {
        prefix.push_back(k);
        m_keymap_prefices.insert(make_pair(mode, prefix));
    }
}
