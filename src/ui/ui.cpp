#include "ui/ui.hpp"
#include "miv/miv.hpp"

UI::UI()
{
    m_miv = make_unique<Miv>(this);
}

UI::~UI() {}
