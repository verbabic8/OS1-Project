#include "../lib/mem.h"
#include "../h/TCB.hpp"


#include "../h/riscV.hpp"
#include "../h/syscall_c.hpp"

#include "../h/print.hpp"
#include "../lib/console.h"


extern void userMain(void*);

int main(){

    MemoryAllocator::init();
    TCB* threads[3];

    RiscV::w_stvec((uint64)&RiscV::supervisorTrap);

    threads[0] = TCB::createThread(nullptr, nullptr, nullptr);
    TCB::running = threads[0];

    thread_create(&threads[1], &userMain, nullptr);
//    printString("ThreadA created!\n");
//    threads[2] = TCB::createThread(reinterpret_cast<void (*)(void *)>(funb), nullptr);
//    printString("ThreadB created!\n");



    while(!(threads[1]->isFinished())) TCB::dispatch();


    for(auto &thread : threads){
        delete thread;
    }
    myPrintString("Finished!\n");

//
//    printInteger((uint64)MemoryAllocator::freeMemHead);
//    printString("\n");
//    void* allocatedAddresses[5];
//    printInteger((uint64)MemoryAllocator::freeMemHead);
//    printString("\n");
//
//
//    allocatedAddresses[0] = MemoryAllocator::memAlloc(100);
//    allocatedAddresses[1] = MemoryAllocator::memAlloc(200);
//    allocatedAddresses[2] = MemoryAllocator::memAlloc(50);
//    allocatedAddresses[3] = MemoryAllocator::memAlloc(150);
//    allocatedAddresses[4] = MemoryAllocator::memAlloc(300);
//
//    printInteger((uint64)MemoryAllocator::freeMemHead);
//    printString("\n");
//
//
//    for(int i = 0; i<5; i++){
//        printString("AllocatedMemory");
//        printInteger((uint64)allocatedAddresses[i]);
//        printString("\n");
//    }
//    printString("\n"); printString("\n");
//
//    printString("\nFree memory blocks after allocation:");
//    FreeMem* current1 = MemoryAllocator::freeMemHead;
//    while(current1){
//        printInteger((uint64)current1);
//        printString(" ");
//        printInteger(current1->size);
//        printString("\n");
//        current1 = current1->next;
//    }
//
//    MemoryAllocator::memFree(allocatedAddresses[0]);
//    MemoryAllocator::memFree(allocatedAddresses[2]);
//    MemoryAllocator::memFree(allocatedAddresses[4]);
//    printString("\n");printString("\n");printString("\n");
//
//    printString("\nFree memory blocks after freeing some blocks:");
//    FreeMem* current2 = MemoryAllocator::freeMemHead;
//    while(current2){
//        printInteger((uint64)current2);
//        printString(" ");
//        printInteger(current2->size);
//        printString("\n");
//        current2 = current2->next;
//    }

    return 0;
}