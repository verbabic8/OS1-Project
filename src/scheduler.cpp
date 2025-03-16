#include "../h/scheduler.hpp"

List<TCB> Scheduler::readyThreads;

TCB* Scheduler::get() {
    return readyThreads.removeFirst();
}

void Scheduler::put(TCB *tcb) {
    readyThreads.addLast(tcb);
}