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
    array->insert(cursor, wstring(1, ch)); // TODO

    mlog->debug("inserted {} at ({}, {})", (char)ch, cursor.x, cursor.y);
}


void DeleteCurrentLineAction::perform()
{
    auto frame = m_miv->frame();
    XArray *array = frame->array();
    num line_number = frame->page().origin.x + frame->cursor().x;
    XArray::iterator first = array->line_begin(line_number);
    XArray::iterator last = array->line_end(line_number);

    if (line_number > 0) {
        --first;
    }
    else if (line_number < array->lines() - 1) {
        ++last;
    }
    array->erase(first, last);
    frame->adjust_cursor();

    mlog->debug("deleted line {}", line_number);
}


void DeleteToLineEndAction::perform()
{

}
