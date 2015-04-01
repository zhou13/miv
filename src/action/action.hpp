#pragma once

class Action {
public:
    Action() {}
    virtual ~Action() {}
    virtual void perform() {}
};

class Miv;
class Frame;

class FlushAction : Action {
    Miv *miv;
public:
    FlushAction(Miv *miv) : miv(miv) {}
    virtual ~FlushAction() {}
    virtual void perform();
};

class MoveAction : Action {
    Frame *frame;
    Vector vec;
public:
    MoveAction(Frame *frame, Vector vec) : frame(frame), vec(vec) {}
    virtual ~MoveAction() {}
    virtual void perform();
};
