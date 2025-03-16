#pragma once

#include "../lib/hw.h"
#include "../h/scheduler.hpp"

class TCB{

public:

    static TCB* running;

    ~TCB() { delete[] stack; }

    using Body = void(*)(void*);

    static TCB* createThread(Body body, uint64* stack, void* args);

    bool isFinished() const { return finished; }

    void setFinished(bool finished) { TCB::finished = finished; }

    static void dispatch();

    bool getBlocked(){return blocked;}

    void setBlocked(bool value){blocked = value;}

    bool getClosed(){return closed;}

    void setClosed(bool value){closed = value;}



private:

    TCB(Body body, uint64* stack, void* args);

    struct Context{
        uint64 ra;
        uint64 sp;
    };
    Body body;
    uint64* stack;
    Context context;
    bool finished;
    void* args;
    bool blocked;
    bool closed;


    static void threadWrapper();

    static void contextSwitch(Context* oldContext, Context* runningContext);
};