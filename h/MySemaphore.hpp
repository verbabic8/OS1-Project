#pragma once

#include "../h/TCB.hpp"
#include "../h/list.hpp"


class MySemaphore{
public:
    MySemaphore(unsigned init = 1):value(init){};
    ~MySemaphore();
    int close();
    int wait();
    int signal();
    int trywait();
    static MySemaphore* semOpen(unsigned init);

private:

    List<TCB> waiting;
    int value;
};