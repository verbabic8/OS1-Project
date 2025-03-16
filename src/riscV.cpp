#include "../h/riscV.hpp"
#include "../h/TCB.hpp"
#include "../test/printing.hpp"
#include "../lib/console.h"
#include "../h/memoryAllocator.hpp"

void RiscV::handleSupervisorTrap() {
    uint64 scause = r_scause();
    uint64 volatile sepc = r_sepc();
    uint64 volatile sstatus = r_sstatus();
    //ecall iz U-moda ili S-moda
    if(scause == 0x0000000000000008UL || scause == 0x0000000000000009UL){
        sepc += 4;
        uint64 op;
        __asm__ volatile("ld %0, 80(fp)" : "=r" (op));
        switch(op) {
            //memAlloc
            case 0x01: {
                size_t size;
                void *addr;
                __asm__ volatile("ld %0, 88(fp)" : "=r" (size));
                addr = MemoryAllocator::memAlloc(size * MEM_BLOCK_SIZE);
                __asm__ volatile("sd %0, 80(fp)"::"r" (addr));
                break;
            }
            //memFree
            case 0x02: {
                void *start;
                int err;
                __asm__ volatile("ld %0, 88(fp)" : "=r" (start));
                err = MemoryAllocator::memFree(start);
                __asm__ volatile("sd %0, 80(fp)"::"r" (err));
                break;
            }
            //thread_create
            case 0x11:{
                TCB **tcb;
                TCB::Body body;
                void *arg;
                uint64* stack;
                __asm__ volatile ("ld %0, 88(fp)" : "=r" (tcb));
                __asm__ volatile ("ld %0, 96(fp)" : "=r" (body));
                __asm__ volatile ("ld %0, 104(fp)" : "=r" (arg));
                __asm__ volatile ("ld %0, 112(fp)" : "=r" (stack));
                *tcb = TCB::createThread(body, stack, arg);
                if (*tcb != nullptr) {
                    __asm__ volatile("sd %0, 80(fp)"::"r" (0));
                } else {
                    __asm__ volatile("sd %0, 80(fp)"::"r" (-1));
                }
                break;
            }
            //thread_exit
            case 0x12: {
                TCB::running->setFinished(true);
                TCB::dispatch();
                __asm__ volatile("sd %0, 80(fp)"::"r" (0));
                break;
            }
            //thread_dispatch
            case 0x13: {
                TCB::dispatch();
                break;
            }
            //sem_open
            case 0x21:{
                unsigned init;
                MySemaphore** semaphore;
                __asm__ volatile ("ld %0, 88(fp)" : "=r" (semaphore));
                __asm__ volatile ("ld %0, 96(fp)" : "=r" (init));
                *semaphore = MySemaphore::semOpen(init);
                if (*semaphore != nullptr) {
                    __asm__ volatile("sd %0, 80(fp)"::"r" (0));
                } else {
                    __asm__ volatile("sd %0, 80(fp)"::"r" (-1));
                }
                break;
            }
            //sem_close
            case 0x22:{
                MySemaphore* handle;
                __asm__ volatile ("ld %0, 88(fp)" : "=r" (handle));
                int ret = handle->close();
                __asm__ volatile("sd %0, 80(fp)"::"r" (ret));
                break;
            }
            //sem_wait
            case 0x23:{
                MySemaphore* handle;
                __asm__ volatile ("ld %0, 88(fp)" : "=r" (handle));
                int ret = handle->wait();
                __asm__ volatile("sd %0, 80(fp)"::"r" (ret));
                break;
            }
            //sem_signal
            case 0x24:{
                MySemaphore* handle;
                __asm__ volatile ("ld %0, 88(fp)" : "=r" (handle));
                int ret = handle->signal();
                __asm__ volatile("sd %0, 80(fp)"::"r" (ret));
                break;
            }
            //sem_trywait
            case 0x26:{
                MySemaphore* handle;
                __asm__ volatile ("ld %0, 88(fp)" : "=r" (handle));
                int ret = handle->trywait();
                __asm__ volatile("sd %0, 80(fp)"::"r" (ret));
                break;
            }
            //getC()
            case 0x41: {
                char c = __getc();
                __asm__ volatile("sd %0, 80(fp)"::"r" (c));
                break;
            }
            //putC()
            case 0x42: {
                char c;
                __asm__ volatile("ld %0, 88(fp)":"=r" (c));
                __putc(c);
                break;
            }
        }
    }
    //od tajmera
    else if(scause == (1ULL<<63 | 1)){
        mc_sip(SIP_SSIE);
    }
    //od tastature
    else if(scause==(1ULL<<63 |9)){
        console_handler();
    }
    else{
        printString("SCAUSE:");
        printInt(scause);
        printString("\n");
        printString("SEPC:");
        printInt(sepc, 16, 0);
        printString("\n");
        while(1);
    }
    w_sepc(sepc);
    w_sstatus(sstatus);
}

void RiscV::popSppSpie() {
    mc_sstatus(SSTATUS_SPP);
    __asm__ volatile ("csrw sepc, ra");
    __asm__ volatile ("sret");
}