#include "../h/MySemaphore.hpp"
#include "../h/syscall_c.hpp"
#include "../h/scheduler.hpp"

int MySemaphore::close(){
    while(waiting.peakFirst()){
        TCB* temp = waiting.removeFirst();
        temp->setBlocked(false);
        temp->setClosed(true);
        Scheduler::put(temp);
    }
    return 0;
}

int MySemaphore::wait() {
    value--;
    if(value < 0){
        TCB::running->setBlocked(true);  
        waiting.addLast(TCB::running);
        thread_dispatch();
    }
    return TCB::running->getClosed() ? -1 : 0;
}

int MySemaphore::signal(){
    value++;
    if(value <= 0){
        TCB* temp = waiting.removeFirst();
        temp->setBlocked(false);
        Scheduler::put(temp);
    }
    return 0;
}

int MySemaphore::trywait() {
    if(value > 0){
        value--;
        return 0;
    }
    else{
        return 1;
    }
}

MySemaphore* MySemaphore::semOpen(unsigned init) {
    return new MySemaphore(init);
}
