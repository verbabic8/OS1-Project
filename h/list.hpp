#pragma once
#include "../lib/hw.h"
#include "../h/memoryAllocator.hpp"

template <typename T>
class List{
private:
    struct Elem{
        T* data;
        Elem* next;

        void* operator new(size_t size) {
            return MemoryAllocator::memAlloc(size);
        }
        void operator delete(void *ptr) {
            MemoryAllocator::memFree(ptr);
        }

        Elem(T* data, Elem* next) : data(data), next(next) {}
    };

    Elem* head, *tail;

public:
    List() : head(0), tail(0) {}

    List(const List<T> &) = delete;
    List<T> &operator=(const List<T> &) = delete;

    void addFirst(T* data){
        Elem* elem = new Elem(data, head);
        head = elem;
        if(!tail) tail = head;
    }

    void addLast(T* data){
        Elem* elem = new Elem(data, nullptr);
        if(tail){
            tail->next = elem;
            tail=elem;
        }
        else{
            head = tail = elem;
        }
    }

    T *removeFirst(){
        if(!head) return 0;

        Elem* elem = head;
        head = head->next;

        if(!head) tail = 0;

        T* ret = elem->data;
        delete elem;

        return ret;
    }

    T* peakFirst(){
        if(!head) return 0;
        return head->data;
    }

    T* removeLast(){
        if(!head) return 0;

        Elem* prev = 0;
        for(Elem* curr = head; curr && curr!=tail; curr = curr->next) prev = curr;

        Elem* elem = tail;

        if(prev) prev->next = 0;
        else head = 0;
        tail = prev;

        T* ret = elem->data;
        delete elem;
        return ret;
    }

    T* peekLast(){
        if(!tail) return 0;
        return tail->data;
    }
};