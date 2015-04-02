#include "action/common.hpp"
#include "miv/miv.hpp"
#include "frame/frame.hpp"

void FlushAction::perform()
{
    m_miv->redraw(m_miv->frame());
}

void CursorMoveLeftAction::perform()
{
    m_miv->frame()->move_cursor(Vector(0, -1));
}


void CursorMoveRightAction::perform()
{
    m_miv->frame()->move_cursor(Vector(0, +1));
}


void CursorMoveUpAction::perform()
{
    m_miv->frame()->move_cursor(Vector(-1, 0));
}


void CursorMoveDownAction::perform()
{
    m_miv->frame()->move_cursor(Vector(+1, 0));
}


void EnterInsertModeAction::perform()
{
    m_miv->frame()->set_mode(Mode::INSERT);
}


void LeaveInsertModeAction::perform()
{
    m_miv->frame()->set_mode(Mode::NORMAL);
}
