#pragma once
#include "FeedConnections.h"

//#define ALLOW_TRADES
#define ALLOW_ORDERS
//#define ALLOW_STATISTICS
#define ALLOW_STATUS

typedef enum _FeedChannelState {
    fchSuspend,
    fchCollectSymbols,
    fchMainLoop
}FeedChannelState;

class AstsFeedChannel {
    // priority fields
    FeedConnection *olr;
    FeedConnection *ols;
    FeedConnection *isf;
    FeedConnection *hr;
    FeedConnection *msr;
    FeedConnection *mss;
    FeedConnection *tlr;
    FeedConnection *tls;
    FeedConnection *idf;

    const char                  *m_senderCompId;
    const char                  *m_password;
    char                        id[16];
    char                        name[64];
    int                         m_nameLogIndex;
    int                         m_idLogIndex;
    FeedChannelState            m_state;
    int                         m_paddingBytes;

    bool CheckConnections();

public:
    AstsFeedChannel(const char *id, const char *name);
    ~AstsFeedChannel();

    FeedConnection* Msr() { return this->msr; }
    FeedConnection* Mss() { return this->mss; }
    FeedConnection* Olr() { return this->olr; }
    FeedConnection* Ols() { return this->ols; }
    FeedConnection* Tlr() { return this->tlr; }
    FeedConnection* Tls() { return this->tls; }
    FeedConnection* Idf() { return this->idf; }
    FeedConnection* Isf() { return this->isf; }
    FeedConnection* Hr() { return this->hr; }

    void SetPassword(const char *password) {
        this->m_password = password;
        if(this->msr != NULL)
            this->msr->SetPassword(this->m_password);
        if(this->mss != NULL)
            this->mss->SetPassword(this->m_password);
        if(this->olr != NULL)
            this->olr->SetPassword(this->m_password);
        if(this->ols != NULL)
            this->ols->SetPassword(this->m_password);
        if(this->tlr != NULL)
            this->tlr->SetPassword(this->m_password);
        if(this->tls != NULL)
            this->tls->SetPassword(this->m_password);
        if(this->idf != NULL)
            this->idf->SetPassword(this->m_password);
        if(this->isf != NULL)
            this->isf->SetPassword(this->m_password);
        if(this->hr != NULL)
            this->hr->SetPassword(this->m_password);
    }

    void SetSenderCompId(const char *senderCompId) {
        this->m_senderCompId = senderCompId;

        if(this->msr != NULL)
            this->msr->SetSenderCompId(this->m_senderCompId);
        if(this->mss != NULL)
            this->mss->SetSenderCompId(this->m_senderCompId);
        if(this->olr != NULL)
            this->olr->SetSenderCompId(this->m_senderCompId);
        if(this->ols != NULL)
            this->ols->SetSenderCompId(this->m_senderCompId);
        if(this->tlr != NULL)
            this->tlr->SetSenderCompId(this->m_senderCompId);
        if(this->tls != NULL)
            this->tls->SetSenderCompId(this->m_senderCompId);
        if(this->idf != NULL)
            this->idf->SetSenderCompId(this->m_senderCompId);
        if(this->isf != NULL)
            this->isf->SetSenderCompId(this->m_senderCompId);
        if(this->hr != NULL)
            this->hr->SetSenderCompId(this->m_senderCompId);
    }

    void SetConnection(FeedConnection *conn);
    const char* Id() { return this->id; }
    const char* Name() { return this->name; }

    bool Connect(FeedConnection *conn);
    bool Disconnect(FeedConnection *conn);
    bool Connect();
    bool Disconnect();

    inline bool OnAfterGenerateSecurityDefinitions() {
        this->m_state = FeedChannelState::fchMainLoop;
        for(int i = 0; i < this->idf->ConnectionsToRecvSymbolsCount(); i++) {
            if(!this->idf->ConnectionsToRecvSymbols()[i]->Start())
                return false;
        }
        return true;
    }

    inline bool CollectSecurityDefinitions() {
        if(this->m_state == FeedChannelState::fchSuspend)
            return true;
        return this->idf->DoWorkAtomSecurityDefinition();
    }

    // WARNING!!!! use this method only if this->m_state != FeedChannelState::fchSuspend
    inline bool DoWorkAtom() {
        //if(this->m_state == FeedChannelState::fchSuspend) // small hacky optimization
        //    return true;
        bool res = true;
#ifdef ALLOW_STATISTICS
            res &= this->msr->DoWorkAtomIncremental();
            if(this->mss->State() != FeedConnectionState::fcsSuspend)
                res &= this->mss->DoWorkAtomSnapshot();
#endif
#ifdef ALLOW_ORDERS
            res &= this->olr->DoWorkAtomIncremental();
            if(this->ols->State() != FeedConnectionState::fcsSuspend)
                res &= this->ols->DoWorkAtomSnapshot();
#endif
#ifdef ALLOW_TRADES
            res &= this->tlr->DoWorkAtomIncremental();
            res &= this->tls->DoWorkAtomSnapshot();
#endif
            if(this->idf->State() != FeedConnectionState::fcsSuspend)
                res &= this->idf->DoWorkAtomSecurityDefinition();
#ifdef ALLOW_STATUS
            res &= this->isf->DoWorkAtomSecurityStatus();
#endif
            res &= this->hr->DoWorkAtomHistoricalReplay();
            return res;
    }
};

