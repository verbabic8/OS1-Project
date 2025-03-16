#pragma once

#include "../lib/hw.h"

struct FreeMem{
    FreeMem* next;
    FreeMem* prev;
    size_t size;
};

class MemoryAllocator{
private:


public:
    static FreeMem* freeMemHead;
    static void* memAlloc(size_t size); //prosledjuje se velicina u bajtovima, potrebno mi je u blokovima
    static int memFree(void* start);
    static void init();


};