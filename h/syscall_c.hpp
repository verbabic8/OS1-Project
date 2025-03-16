#pragma once

#include "../lib/hw.h"
#include "../h/TCB.hpp"
#include "../h/MySemaphore.hpp"

void* mem_alloc(size_t size);
int mem_free(void* start);

typedef TCB* thread_t;
int thread_create(thread_t* handle, void(*start_routine)(void*), void* args);
int thread_exit();
void thread_dispatch();


typedef MySemaphore* sem_t;
int sem_open(sem_t* handle, unsigned init);
int sem_close(sem_t handle);
int sem_wait(sem_t id);
int sem_signal(sem_t id);
int sem_trywait(sem_t id);

typedef uint64 time_t;
int time_sleep(time_t);

char getc();
void putc(char c);