#pragma once

#include "utils/utils.hpp"

class Miv;
class Action {
public:
    Action(Miv *miv) : m_miv(miv) {}
    virtual ~Action() {}
    virtual void perform() {}

protected:
    Miv *m_miv;
};
