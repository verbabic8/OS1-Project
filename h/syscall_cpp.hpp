#pragma once

#include "syscall_c.hpp"
#include "../lib/hw.h"

void* operator new (size_t);
void operator delete (void*);

class Thread {
public:
    Thread (void (*body)(void*), void* arg);
    virtual ~Thread ();
    int start ();
    static void dispatch ();
    //static int sleep (time_t);
protected:
    Thread ();
    virtual void run () {}
private:
    thread_t myHandle;
    static void runner(void* thr);
    void (*body)(void*);
    void* arg;
};

class Console {
public:
    static char getc ();
    static void putc (char);
};

class Semaphore {
public:
    Semaphore (unsigned int init = 1);
    virtual ~Semaphore ();
    int wait ();
    int signal ();
    //int timedWait (time_t);
    int tryWait();
private:
    sem_t myHandle;
};
