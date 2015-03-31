#include "miv/controller.hpp"

void Controller::key_press(KeyStatus ks, char key)
{
    (void)ks;
    (void)key;
}


shared_ptr<Action> Controller::pop_next_action()
{
    return nullptr;
}
