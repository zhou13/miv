#include "action/action.hpp"
#include "miv/miv.hpp"

void FlushAction::perform()
{
    miv->flush();
}



void MoveAction::perform()
{
    frame->move_cursor(vec);
}
