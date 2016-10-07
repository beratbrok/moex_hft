//
// Created by root on 29.09.16.
//

#ifndef HFT_ROBOT_ORDERBOOKINFOLIST_H
#define HFT_ROBOT_ORDERBOOKINFOLIST_H

#include "Lib/PointerList.h"
#include "FastTypes.h"

template<typename T> class AutoAllocatePointerList {
    PointerList<T> *m_list;
    int             m_addCapacity;

    inline void Allocate(LinkedPointer<T> *start, LinkedPointer<T> *end) {
        do {
            T *t = new T;
            t->Pointer = start;
            start->Data(t);
            start = start->Next();
        }
        while(start != end);
    }
public:
    AutoAllocatePointerList(int capacity, int additionalCapacity) {
        this->m_addCapacity = additionalCapacity;
        this->m_list = new PointerList<T>(capacity);
        this->Allocate(this->m_list->PoolStart(), this->m_list->PoolEnd());
    }
    inline T* NewItem() {
        if(this->m_list->IsFull()) {
            LinkedPointer<T> *node = this->m_list->Append(this->m_addCapacity);
            this->Allocate(node, this->m_list->PoolEnd());
        }
        return (T*)this->m_list->Pop()->Data();
    }
    inline PointerList<T>* ListCore() { return this->m_list; }
    inline void FreeItem(LinkedPointer *node) {
        this->m_list->Push(node);
    }
    inline int Count() { return this->m_list->Count(); }
};

#endif //HFT_ROBOT_ORDERBOOKINFOLIST_H
