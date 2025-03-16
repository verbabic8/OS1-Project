#include "../h/syscall_cpp.hpp"

#include "../h/syscall_c.hpp"

void* operator new(size_t size) {
    return mem_alloc(size);
}
void operator delete(void* start) {
    mem_free(start);
}

void* operator new[](size_t size) {
    return mem_alloc(size);
}
void operator delete[](void* start) {
    mem_free(start);
}

Thread::Thread(){
    this->myHandle = nullptr;
    this->body = runner;
    this->arg = this;
}

void Thread::runner(void* thr)
{
    Thread* thread = (Thread*) thr;
    thread->run();
}

Thread::Thread(void (*body)(void *), void *arg) {
    this->myHandle = nullptr;
    this->body = body;
    this->arg = arg;
}

Thread::~Thread() {
}

int Thread::start() {
    return thread_create(&myHandle, body, arg);
}

void Thread::dispatch() {
    thread_dispatch();
}

char Console::getc(){
    return ::getc();
}

void Console::putc(char c) {
    ::putc(c);
}

Semaphore::Semaphore(unsigned int init) {
    sem_open(&myHandle,init);
}

Semaphore::~Semaphore() {
    sem_close(this->myHandle);
}

int Semaphore::wait() {
    return sem_wait(this->myHandle);
}

int Semaphore::signal(){
    return sem_signal(this->myHandle);
}

int Semaphore::tryWait() {
    return sem_trywait(this->myHandle);
}
