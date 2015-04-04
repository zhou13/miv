#include "action/common.hpp"
#include "miv/miv.hpp"
#include "xarray/xarray.hpp"
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


void InsertAfterCursorAction::perform()
{
    DEFINE_SCOPE_LOGGER;

    auto frame = m_miv->frame();
    XArray *array = frame->array();
    Point cursor = frame->page().origin + frame->cursor();
    array->insertv(cursor, wstring(1, ch));

    mlog->debug("insert {} at ({}, {})", (char)ch, cursor.x, cursor.y);

    CursorMoveRightAction(m_miv).perform();
}


void DeleteCurrentLineAction::perform()
{
    auto frame = m_miv->frame();
    XArray *array = frame->array();
    num line_number = frame->page().origin.x + frame->cursor().x;
}
