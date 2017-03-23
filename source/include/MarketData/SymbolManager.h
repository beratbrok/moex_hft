//
// Created by root on 31.12.16.
//

#ifndef HFT_ROBOT_SYMBOLMANAGER_H
#define HFT_ROBOT_SYMBOLMANAGER_H

#include "../Lib/StringHash.h"
#include "../Lib/PointerList.h"
#include "../Lib/StringIdComparer.h"
#include <memory.h>

class SymbolInfo {
public:
    int                         m_index;
    int                         m_length;
    char                        m_text[17];

    SymbolInfo() {
        this->m_length = 0;
        this->m_index = -1;
    }
    void Set(const char *symbol, int length, int index) {
        memcpy(this->m_text, symbol, length);
        this->m_text[length] = '\0';
        this->m_length = length;
        this->m_index = index;
    }
};

class SymbolManagerTester;
class SecurityDefinitionTester;
class SymbolManager {
    friend class SymbolManagerTester;
    friend class SecurityDefinitionTester;

    const int                   BucketList2Count = 1000000;

    int                         m_capacity;
    int                         m_count;
    short                       m_freeIndex;

    PointerList<SymbolInfo>      *m_pool;
    LinkedPointer<SymbolInfo>   **m_bucketList;
    SymbolInfo                  **m_bucketList2;
    inline short GetFreeIndex() {
        this->m_freeIndex++;
        return this->m_freeIndex;
    }
    inline void AddBucket(LinkedPointer<SymbolInfo> *ptr, int hash) {
        this->m_bucketList[hash] = ptr;
    }
    inline LinkedPointer<SymbolInfo>* AddFirstSymbol(const char *symbol, int length, int hash) {
        LinkedPointer<SymbolInfo> *ptr = GetPtrFromPool();
        ptr->Data()->Set(symbol, length, GetFreeIndex());
        AddBucket(ptr, hash);
        this->m_count++;
        return ptr;
    }
    inline void ClearBucketList() {
        if(this->m_bucketList != 0) {
            for (int i = 0; i < StringHash::HashArrayItemsCount; i++) {
                LinkedPointer<SymbolInfo> *ptr = this->m_bucketList[i];
                LinkedPointer<SymbolInfo> *prevPtr = 0;
                if (ptr == 0)
                    continue;
                while (ptr != 0) {
                    prevPtr = ptr;
                    ptr = ptr->Next();
                    this->m_pool->Push(prevPtr);
                }
                this->m_bucketList[i] = 0;
            }
        }
        else if(this->m_bucketList2 != 0)
            bzero(this->m_bucketList2, sizeof(SymbolInfo*) * BucketList2Count);
        this->m_pool->Clear();
    }
    inline LinkedPointer<SymbolInfo>* GetBucket(int hash) {
        return this->m_bucketList[hash];
    }
    inline LinkedPointer<SymbolInfo>* GetPtrFromPool() {
        LinkedPointer<SymbolInfo> *res = this->m_pool->Pop();
        this->m_pool->Add(res);
        res->Next(0);
        return res;
    }
    inline bool FindSymbol(LinkedPointer<SymbolInfo> *start, const char *symbol, int length, LinkedPointer<SymbolInfo> **found) {
        while(true) {
            SymbolInfo *s = start->Data();
            if(StringIdComparer::Equal(s->m_text, s->m_length, symbol, length)) {
                *found = start;
                return true;
            }
            if(!start->HasNext()) {
                *found = start;
                return false;
            }
            start = start->Next();
        }
    }
    inline void AppendSymbol(LinkedPointer<SymbolInfo> *current, LinkedPointer<SymbolInfo> *next) {
        current->Next(next);
        next->Next(0);
        this->m_count++;
    }
public:
    SymbolManager(int capacity) {
        this->m_capacity = capacity;
        this->m_count = 0;
        this->m_freeIndex = -1;

        this->m_pool = new PointerList<SymbolInfo>(capacity + 10);
        this->m_pool->AllocData();
        this->m_bucketList = new LinkedPointer<SymbolInfo>*[StringHash::HashArrayItemsCount];
        this->m_bucketList2 = 0;
    }
    SymbolManager(int capacity, bool useUint64Hash) {
        this->m_capacity = capacity;
        this->m_count = 0;
        this->m_freeIndex = -1;

        this->m_pool = new PointerList<SymbolInfo>(capacity + 10);
        this->m_pool->AllocData();
        this->m_bucketList = 0;
        this->m_bucketList2 = new SymbolInfo*[1000000];
        bzero(this->m_bucketList2, sizeof(SymbolInfo*) * BucketList2Count);
    }
    ~SymbolManager() {
        delete this->m_pool;
        if(this->m_bucketList2 != 0)
            delete this->m_bucketList2;
    }
    inline void Clear() {
        this->m_freeIndex = -1;
        this->m_count = 0;
        ClearBucketList();
    }
    inline int SymbolCount() {
        return this->m_count;
    }
    inline int BucketListCount() { return StringHash::HashArrayItemsCount; }
    inline int CalcBucketCollisitonCount(int index) {
        LinkedPointer<SymbolInfo> *ptr = this->m_bucketList[index];
        if(ptr == 0) return 0;
        int count = 1;
        while(ptr->HasNext()) {
            count++; ptr = ptr->Next();
        }
        return count;
    }
    inline int GetSymbolIndex(const char *symbol, bool *wasNewlyAdded) {
        return GetSymbolIndex(symbol, strlen(symbol), wasNewlyAdded);
    }
    inline int GetSymbolIndex(const char *symbol, int length, bool *wasNewlyAdded) {
        SymbolInfo *info = GetSymbol(symbol, length, wasNewlyAdded);
        return info->m_index;
    }
    inline SymbolInfo* GetSymbol(const char *symbol, bool *wasNewlyAdded) {
        return this->GetSymbol(symbol, strlen(symbol), wasNewlyAdded);
    }
    inline SymbolInfo* AddSymbol(const char *symbol) {
        bool wasNewlyAdded = false;
        SymbolInfo *res = this->GetSymbol(symbol, strlen(symbol), &wasNewlyAdded);
#ifdef TEST
        if(!wasNewlyAdded)
            throw;
#endif
        return res;
    }
    inline SymbolInfo* GetSymbol(UINT64 securityId, bool *wasNewlyAdded) {
        if(this->m_bucketList2[securityId] == 0) {
            *wasNewlyAdded = true;
            SymbolInfo *smb = GetPtrFromPool()->Data();
            smb->m_index = GetFreeIndex();
            this->m_bucketList2[securityId] = smb;
            this->m_count++;
            return smb;
        }
        *wasNewlyAdded = false;
        return this->m_bucketList2[securityId];
    }
    inline SymbolInfo* GetSymbol(UINT64 securityId) {
        bool wasNewlyAdded;
        SymbolInfo *info = this->GetSymbol(securityId, &wasNewlyAdded);
        if(wasNewlyAdded) { //TODO remove debug
            printf("!!!unexpected add %" PRIu64 "\n", securityId);
        }
        return info;
    }
    inline SymbolInfo* AddSymbol(UINT64 securityId) {
        bool wasNewlyAdded;
        SymbolInfo *info = this->GetSymbol(securityId, &wasNewlyAdded);
        if(!wasNewlyAdded) { //TODO remove debug
            printf("!!!already added %" PRIu64 "\n", securityId);
        }
        return info;
    }
    inline SymbolInfo* GetSymbol(const char *symbol, int length) {
        bool wasNewlyAdded = false;
        SymbolInfo *res = this->GetSymbol(symbol, length, &wasNewlyAdded);
        if(wasNewlyAdded) { //TODO remove debug
            printf("!!!unexpected add %s\n", DebugInfoManager::Default->GetString(symbol, length, 0));
            return 0;
            //throw;
        }
        return res;
    }
    inline SymbolInfo* GetSymbol(const char *symbol, int length, bool *wasNewlyAdded) {
        int hash = StringHash::GetHash(symbol, length);
        LinkedPointer<SymbolInfo> *bucket = GetBucket(hash);
        if(bucket == 0) {
            *wasNewlyAdded = true;
            return AddFirstSymbol(symbol, length, hash)->Data();
        }
        LinkedPointer<SymbolInfo> *sptr = 0;
        if(FindSymbol(bucket, symbol, length, &sptr)) {
            *wasNewlyAdded = false;
            return sptr->Data();
        }
        *wasNewlyAdded = true;
        LinkedPointer<SymbolInfo> *newPtr = GetPtrFromPool();
        newPtr->Data()->Set(symbol, length, GetFreeIndex());
        AppendSymbol(sptr, newPtr);
        return newPtr->Data();
    }
};

#endif //HFT_ROBOT_SYMBOLMANAGER_H
