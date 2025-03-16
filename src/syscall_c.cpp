#include "../h/syscall_c.hpp"
#include "../h/memoryAllocator.hpp"

void* mem_alloc(size_t size){
    if(!size) return nullptr;

    size = (size + MEM_BLOCK_SIZE - 1) / MEM_BLOCK_SIZE;
    __asm__ volatile("mv a1, %0" : : "r" (size));
    __asm__ volatile("mv a0, %0" : : "r" (0x01));
    __asm__ volatile("ecall");

    void* addr;
    __asm__ volatile("mv %0, a0" : "=r"(addr));
    return addr;
}
int mem_free(void* start){
    if(!start) return -1;

    __asm__ volatile("mv a1, %0" : : "r"(start));
    __asm__ volatile("li a0, 0x02");
    __asm__ volatile("ecall");

    uint64 code;
    __asm__ volatile("mv %0, a0" : "=r"(code));
    return (int)code;
}

int thread_create(thread_t* handle, void(*start_routine)(void*), void* args){
    uint64* stack = (uint64*)(mem_alloc(DEFAULT_STACK_SIZE));
    __asm__ volatile("mv a4, %0" : : "r"(stack));
    __asm__ volatile("mv a3, %0" : : "r"(args));
    __asm__ volatile("mv a2, %0" : : "r"(start_routine));
    __asm__ volatile("mv a1, %0" : : "r"(handle));
    __asm__ volatile("li a0, 0x11");
    __asm__ volatile("ecall");

    uint64 code;
    __asm__ volatile("mv %0, a0" : "=r"(code));
    return (int)code;
}
int thread_exit(){
    __asm__ volatile("mv a0, %0" : : "r" (0x12));
    __asm__ volatile("ecall");

    uint64 code;
    __asm__ volatile("mv %0, a0" : "=r" (code));
    return (int)code;
}
void thread_dispatch(){
    __asm__ volatile("mv a0, %0" : : "r" (0x13));
    __asm__ volatile("ecall");
}

int time_sleep(time_t time)
{
    return 0;
}

char getc()
{
    __asm__ volatile("mv a0, %0" : : "r" (0x41));
    __asm__ volatile("ecall");

    char c;
    __asm__ volatile("mv %0, a0" : "=r" (c));
    return c;
}

void putc(char c) {

    __asm__ volatile("mv a1, %0" : : "r"(c));
    __asm__ volatile("mv a0, %0" : : "r" (0x42));
    __asm__ volatile("ecall");
}

int sem_open(sem_t* handle, unsigned init) {
    __asm__ volatile ("mv a2, %0" : : "r" (init));
    __asm__ volatile ("mv a1, %0" : : "r" (handle));
    __asm__ volatile("mv a0, %0" : : "r" (0x21));
    __asm__ volatile ("ecall");

    uint64 code;
    __asm__ volatile("mv %0, a0" : "=r"(code));
    return (int)code;
}

int sem_close(sem_t handle) {
    __asm__ volatile ("mv a1, %0" : : "r" (handle));
    __asm__ volatile("mv a0, %0" : : "r" (0x22));
    __asm__ volatile ("ecall");

    uint64 code;
    __asm__ volatile("mv %0, a0" : "=r"(code));
    return (int)code;
}

int sem_wait(sem_t id) {
    __asm__ volatile ("mv a1, %0" : : "r" (id));
    __asm__ volatile("mv a0, %0" : : "r" (0x23));
    __asm__ volatile ("ecall");

    uint64 code;
    __asm__ volatile("mv %0, a0" : "=r"(code));
    return (int)code;
}

int sem_signal(sem_t id) {
    __asm__ volatile ("mv a1, %0" : : "r" (id));
    __asm__ volatile("mv a0, %0" : : "r" (0x24));
    __asm__ volatile ("ecall");

    uint64 code;
    __asm__ volatile("mv %0, a0" : "=r"(code));
    return (int)code;
}

int sem_trywait(sem_t id){
    __asm__ volatile ("mv a1, %0" : : "r" (id));
    __asm__ volatile("mv a0, %0" : : "r" (0x26));
    __asm__ volatile ("ecall");

    uint64 code;
    __asm__ volatile("mv %0, a0" : "=r"(code));
    return (int)code;
}

