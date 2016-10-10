//
// Created by root on 28.09.16.
//

#ifndef HFT_ROBOT_SIMPLELIST_H
#define HFT_ROBOT_SIMPLELIST_H

template <typename T> class PointerList;

template <typename T> class LinkedPointer {
    PointerList<T>  *m_owner;
    LinkedPointer   *m_next;
    LinkedPointer   *m_prev;
    T               *m_data;
public:
    LinkedPointer() {
        this->m_next = 0;
        this->m_data = 0;
        this->m_prev = 0;
    }

    inline LinkedPointer* Next() { return this->m_next; }
    inline void Next(LinkedPointer *node) { this->m_next = node; }
    inline LinkedPointer* Prev() { return this->m_prev; }
    inline void Prev(LinkedPointer *node) { this->m_prev = node; }
    inline T* Data() { return this->m_data; }
    inline void Data(T *data) { this->m_data = data; }
    inline PointerList<T>* Owner() { return this->m_owner; }
    inline void Owner(PointerList<T> *owner) { this->m_owner = owner; }
};

template <typename T> class PointerList {
    int             m_capacity;

    LinkedPointer<T> *m_poolHead;
    LinkedPointer<T> *m_poolTail;

    LinkedPointer<T> *m_head;
    LinkedPointer<T> *m_tail;
    int              m_count;

public:
    inline LinkedPointer<T>* Pop() {
        LinkedPointer<T> *node = this->m_poolHead;
        this->m_poolHead = this->m_poolHead->Next();
        this->m_count++;
        return node;
    }

    inline void Push(LinkedPointer<T> *node) {
        this->m_poolTail->Next(node);
        this->m_poolTail = node;
        this->m_count--;
    }
    PointerList(int capacity) {
        this->m_capacity = capacity;
        this->m_count = 0;

        this->m_poolHead = new LinkedPointer<T>;
        this->m_poolTail = this->m_poolHead;

        for(int i = 0; i < this->m_capacity; i++) {
            LinkedPointer<T> *ptr = new LinkedPointer<T>;
            ptr->Owner(this);
            this->Push(ptr);
        }

        this->m_tail = this->m_head = this->Pop();
        this->m_head->Next(0);
        this->m_head->Prev(0);
        this->m_head->Data(0);
        this->m_count = 0;
    }
    ~PointerList() {
        while(this->m_head != this->m_tail)
            this->Remove(this->m_head->Next());

        LinkedPointer<T> *node = this->m_poolHead;
        do {
            delete node;
            node = node->Next();
        }
        while(node != this->m_tail);
    }

    inline void Add(T *data) {
        LinkedPointer<T> *node = this->Pop();
        node->Data(data);
        this->m_tail->Next(node);
        node->Prev(this->m_tail);
        this->m_tail = node;
    }

    inline void Insert(LinkedPointer<T> *before, T *data) {
        LinkedPointer<T> *node = this->Pop();
        LinkedPointer<T> *prev = before->Prev();
        prev->Next(node);
        node->Prev(prev);
        node->Next(before);
        before->Prev(node);
    }

    inline LinkedPointer<T>* Get(T *data) {
        LinkedPointer<T> *node = this->m_head;
        while(true) {
            if(node->Data() == data)
                return node;
            if(node == this->m_tail)
                break;
            node = node->Next();
        }
        return 0;
    }

    inline void Remove(LinkedPointer<T> *node) {
        LinkedPointer<T> *prev = node->Prev();
        LinkedPointer<T> *next = node->Next();
        prev->Next(next);
        next->Prev(prev);
        this->Push(node);
        this->m_count--;
    }

    inline void Remove(T *data) {
        LinkedPointer<T> *node = this->Get(data);
        this->Remove(node);
    }

    inline bool IsFull() { return this->m_poolHead == this->m_poolTail; }
    inline LinkedPointer<T>* Append(int capacity) {
        this->m_capacity += capacity;
        LinkedPointer<T> *start = new LinkedPointer<T>();
        LinkedPointer<T> *node = start;
        for(int i = 0; i < capacity; i++) {
            LinkedPointer<T> *ptr = new LinkedPointer<T>;
            ptr->Owner(this);
            node->Next(ptr);
            node = node->Next();
        }
        this->m_poolTail->Next(start);
        this->m_poolTail = node;
        return start;
    }
    inline LinkedPointer<T>* Start() { return this->m_head->Next(); }
    inline LinkedPointer<T>* End() { return this->m_tail; }
    inline LinkedPointer<T>* Next(LinkedPointer<T> *node) { return node->Next(); }
    inline LinkedPointer<T>* PoolStart() { return this->m_poolHead; }
    inline LinkedPointer<T>* PoolEnd() { return this->m_poolTail; }
    inline int Count() { return this->m_count; }

    inline void Clear() {
        if(this->m_head == this->m_tail)
            return;
        LinkedPointer<T> *st = this->m_head->Next();
        LinkedPointer<T> *end = this->m_tail;
        this->m_poolTail->Next(st);
        this->m_poolTail = end;
        this->m_count = 0;
    }
};

#endif //HFT_ROBOT_SIMPLELIST_H
