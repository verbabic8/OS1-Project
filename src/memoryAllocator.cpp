#include "../h/memoryAllocator.hpp"
#include "../h/print.hpp"

FreeMem* MemoryAllocator::freeMemHead = nullptr;

void MemoryAllocator::init() {
    freeMemHead = (FreeMem*)HEAP_START_ADDR;
    freeMemHead->next = nullptr;
    freeMemHead->prev = nullptr;
    freeMemHead->size = ((char*)HEAP_START_ADDR - (char*)HEAP_END_ADDR - MEM_BLOCK_SIZE);
}

//april 2014.
void *MemoryAllocator::memAlloc(size_t size) {
    uint64 numOfBlocks = ((size + MEM_BLOCK_SIZE - 1) / MEM_BLOCK_SIZE)+1;
    for(FreeMem* current = freeMemHead; current != nullptr; current = current->next){
        if(current->size < numOfBlocks*MEM_BLOCK_SIZE) continue;
        if(current->size - numOfBlocks*MEM_BLOCK_SIZE < MEM_BLOCK_SIZE){
            if(current->prev) current->prev->next = current->next;
            else freeMemHead = current->next;
            if(current->next) current->next->prev = current->prev;
            current = (FreeMem*)((char*)current + MEM_BLOCK_SIZE);
            return (char*)current;
        }
        else{
            FreeMem* newFrag = (FreeMem*)((char*)current + numOfBlocks*MEM_BLOCK_SIZE);
            if(current->prev) current->prev->next = newFrag;
            else freeMemHead = newFrag;
            if(current->next) current->next->prev = newFrag;
            newFrag->prev = current->prev;
            newFrag->next = current->next;
            newFrag->size = current->size - (numOfBlocks+1)*MEM_BLOCK_SIZE;
            current->size = numOfBlocks*MEM_BLOCK_SIZE;
            current = (FreeMem*)((char*)current + MEM_BLOCK_SIZE);
            return (char*)current;
        }
    }
    return nullptr;
}

//septembar 2015.
int MemoryAllocator::memFree(void *start) {
    if(start == nullptr) return -1;
    start = (void*)((char*)start - MEM_BLOCK_SIZE);

    FreeMem* current;

    //trazim gde da ubacim oslobodjeni prostor NAKON trenutnog elementa
    if(!freeMemHead || (char*)start < (char*)freeMemHead) current = nullptr;
    else{
        for(current = freeMemHead; current->next != nullptr && (char*)start > (char*)(current->next); current = current->next);
    }

    FreeMem* newSeg = (FreeMem*)start;
//    myPrintInt((uint64)newSeg);
//    myPrintString(" ");
//    myPrintInt((uint64)newSeg->size);
//    myPrintString(" ");
//    uint64 end = (uint64)newSeg + newSeg->size;
//    myPrintInt(end);
    newSeg->prev = current;
    if (current){
        newSeg->next = current->next;
        current->next = newSeg;
    }
    else{
        newSeg->next = freeMemHead;
        freeMemHead = newSeg;
    }
    if (newSeg->next) newSeg->next->prev = newSeg;


    //TryToJoin
    //desni
    if(newSeg->next && (char*)newSeg + newSeg->size == (char*)newSeg->next){
        newSeg->size += newSeg->next->size + 1;
        newSeg->next = newSeg->next->next;
        if(newSeg->next) newSeg->next->prev = newSeg;
    }

    //levi
    if (newSeg->prev!=0 && (char*)((char*)newSeg->prev + newSeg->prev->size) == (char*)newSeg) {
        newSeg->prev->size += newSeg->size + 1;
        newSeg->prev->next = newSeg->next;
        if (newSeg->next) newSeg->next->prev = newSeg->prev;
    }

    return 0;
}



