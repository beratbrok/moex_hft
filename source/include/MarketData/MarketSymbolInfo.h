//
// Created by root on 17.12.16.
//

#ifndef HFT_ROBOT_MARKETSYMBOLINFO_H
#define HFT_ROBOT_MARKETSYMBOLINFO_H

#include "../Lib/StringIdComparer.h"
#include "../FastTypes.h"

template <typename T> class MarketSymbolInfo {
    T                                  **m_items;
    SizedArray                         *m_symbol;
    int                                 m_count;
    int                                 m_sessionsToRecvSnapshot;
public:
    MarketSymbolInfo() {
        this->m_count = 0;
        this->m_items = new T*[RobotSettings::MarketDataMaxSessionsCount];
        for(int i = 0; i < RobotSettings::MarketDataMaxSessionsCount; i++) {
            this->m_items[i] = new T();
            this->m_items[i]->SymbolInfo(this);
        }
        this->m_symbol = new SizedArray();
    }
    ~MarketSymbolInfo() {
        for(int i = 0; i < RobotSettings::MarketDataMaxSessionsCount; i++)
            delete this->m_items[i];
        delete this->m_symbol;
        delete this->m_items;
    }
    inline int Count() { return this->m_count; }
    inline T* Session(int index) { return this->m_items[index]; }
    inline T* GetSession(const char *session, int sessionLength) {
        T **item = this->m_items;
        for(int i = 0; i < this->m_count; i++, item++) {
            if((*item)->TradingSession()->Equal(session, sessionLength))
                return *item;
        }
        T* res = this->m_items[this->m_count];
        res->TradingSession()->Set(session, sessionLength);
        this->m_count++;
        return res;
    }
    inline SizedArray *Symbol() { return this->m_symbol; }
    inline bool Equals(const char *symbol, int symbolLen) { return this->m_symbol->Equal(symbol, symbolLen); }
    inline void Clear() {
        T **item = this->m_items;
        for(int i = 0; i < this->m_count; i++, item++) {
            (*item)->Used(false);
            (*item)->Clear();
        }
        this->m_count = 0;
    }
    inline T* AddSession(const char *session, int sessionLength) {
        return GetSession(session, sessionLength);
    }
    inline T* AddSession(const char *session) {
        return AddSession(session, strlen(session));
    }
    inline void EnterSnapshotMode() {
        this->m_sessionsToRecvSnapshot = this->m_count;
        T **item = this->m_items;
        for(int i = 0; i < this->m_count; i++, item++)
            (*item)->EnterSnapshotMode();
    }
    inline void ExitSnapshotMode() {
        T **item = this->m_items;
        for(int i = 0; i < this->m_count; i++, item++)
            (*item)->ExitSnapshotMode();
    }
    inline int SessionsToRecvSnapshotCount() { return this->m_sessionsToRecvSnapshot; }
    inline bool AllSessionsRecvSnapshot() { return this->m_sessionsToRecvSnapshot == 0; }
    inline void DecSessionsToRecvSnapshotCount() { this->m_sessionsToRecvSnapshot--; }
};

#endif //HFT_ROBOT_MARKETSYMBOLINFO_H