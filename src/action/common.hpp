#pragma once

#include "action/action.hpp"

/*!
    \class FlushAction
    \ingroup actions
    \brief Behavior: ask Miv to repaint the current frame.
*/
class FlushAction : public Action {
public:
    FlushAction(Miv *miv) : Action(miv) {}
    virtual ~FlushAction() {}
    virtual void perform();
};

/*!
    \class CursorMoveLeftAction
    \ingroup actions
    \brief Behavior: move the cursor left
*/
class CursorMoveLeftAction : public Action {
public:
    CursorMoveLeftAction(Miv *miv) : Action(miv) {}
    virtual ~CursorMoveLeftAction() {}
    virtual void perform();
};

/*!
    \class CursorMoveRightAction
    \ingroup actions
    \brief Behavior: move the cursor right
*/
class CursorMoveRightAction : public Action {
public:
    CursorMoveRightAction(Miv *miv) : Action(miv) {}
    virtual ~CursorMoveRightAction() {}
    virtual void perform();
};

/*!
    \class CursorMoveUpAction
    \ingroup actions
    \brief Behavior: move the cursor up
*/
class CursorMoveUpAction : public Action {
public:
    CursorMoveUpAction(Miv *miv) : Action(miv) {}
    virtual ~CursorMoveUpAction() {}
    virtual void perform();
};

/*!
    \class CursorMoveDownAction
    \ingroup actions
    \brief Behavior: move the cursor down
*/
class CursorMoveDownAction : public Action {
public:
    CursorMoveDownAction(Miv *miv) : Action(miv) {}
    virtual ~CursorMoveDownAction() {}
    virtual void perform();
};

/*!
    \class EnterInsertModeAction
    \ingroup actions
    \brief Behavior: enter insert mode; only valid to current frame.
*/
class EnterInsertModeAction : public Action {
public:
    EnterInsertModeAction(Miv *miv) : Action(miv) {}
    virtual ~EnterInsertModeAction() {}
    virtual void perform();
};

/*!
    \class LeaveInsertModeAction
    \ingroup actions
    \brief Behavior: enter insert mode; only valid to current frame.
*/
class LeaveInsertModeAction : public Action {
public:
    LeaveInsertModeAction(Miv *miv) : Action(miv) {}
    virtual ~LeaveInsertModeAction() {}
    virtual void perform();
};

/*!
    \class InsertAfterCursorAction
    \ingroup actions
    \brief Behavior: insert a char \a ch after current cursor.
*/
class InsertAfterCursorAction : public Action {
public:
    InsertAfterCursorAction(Miv *miv, wchar_t ch) : Action(miv), ch(ch) {}
    virtual ~InsertAfterCursorAction() {}
    virtual void perform();

private:
    wchar_t ch;
};

/*!
    \class DeleteCurrentLineAction
    \ingroup actions
    \brief Behavior: delete current line.
*/
class DeleteCurrentLineAction : public Action {
public:
    DeleteCurrentLineAction(Miv *miv) : Action(miv) {}
    virtual ~DeleteCurrentLineAction() {}
    virtual void perform();
};
