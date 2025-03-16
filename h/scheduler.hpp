#pragma once

#include "list.hpp"

class TCB;

class Scheduler{
private:
    static List<TCB> readyThreads;

public:
    static void put(TCB* tcb);
    static TCB* get();
};