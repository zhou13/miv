#pragma once

/*!
    \defgroup actions Actions
    \brief For performing operations.
*/

/*!
    \class Action
    \ingroup actions

    \brief Base class of all actions.

    \sa FlushAction, CursorMoveLeftAction, CursorMoveRightAction, 
        CursorMoveUpAction, CursorMoveDownAction, EnterInsertModeAction,
        LeaveInsertModeAction, InsertAfterCursorAction, DeleteCurrentLineAction
*/

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
