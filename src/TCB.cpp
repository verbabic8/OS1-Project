#include "../h/TCB.hpp"

#include "../h/riscV.hpp"
#include "../h/syscall_c.hpp"

TCB* TCB::running = nullptr;

TCB::TCB(Body body, uint64* stack, void* args):
        body(body),
        stack(body != nullptr ? stack : nullptr),
        context({(uint64)&threadWrapper,
                 stack != nullptr ? (uint64)&stack[DEFAULT_STACK_SIZE>>3] : 0}),
        finished(false),
        args(args),
        blocked(false)
        {
            if(body != nullptr){
                Scheduler::put(this);
            }
}

TCB* TCB::createThread(TCB::Body body, uint64* stack, void* args) {
    return new TCB(body, stack, args);
}

void TCB::dispatch() {
    TCB* old = TCB::running;
    if(!old->isFinished() && !old->getBlocked()){
        Scheduler::put(old);
    }
    running = Scheduler::get();

    if(old != running) TCB::contextSwitch(&old->context, &running->context);
}

void TCB::threadWrapper() {
    RiscV::popSppSpie();
    TCB::running->body(TCB::running->args);
    thread_exit();
}