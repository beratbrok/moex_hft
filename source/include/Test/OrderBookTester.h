//
// Created by root on 10.10.16.
//

#ifndef HFT_ROBOT_FEEDCONNECTIONTEST_H
#define HFT_ROBOT_FEEDCONNECTIONTEST_H

#include "../FeedConnection.h"
#include <stdio.h>

class TestTemplateItemInfo {
public:
    MDUpdateAction  m_action;
    const char*     m_symbol;
    const char*     m_tradingSession;
    MDEntryType     m_entryType;
    const char*     m_entryId;
    Decimal         m_entryPx;
    Decimal         m_entrySize;
    int             m_rptSeq;

    TestTemplateItemInfo() { }

    TestTemplateItemInfo(MDUpdateAction action, MDEntryType entryType, const char *symbol, const char *sessionId, const char *entryId, int rptSeq, int pxm, INT64 pxe, int sizem, INT64 sizee) {
        this->m_action = action;
        this->m_entryType = entryType;
        this->m_symbol = symbol;
        this->m_tradingSession = sessionId;
        this->m_entryId = entryId;
        this->m_entryPx.Set(pxm, pxe);
        this->m_entrySize.Set(sizem, sizee);
        this->m_rptSeq = rptSeq;
    }
    TestTemplateItemInfo(const char *symbol, const char *entryId, int rptSeq) {
        this->m_action = MDUpdateAction::mduaAdd;
        this->m_entryType = MDEntryType::mdetBuyQuote;
        this->m_symbol = symbol;
        this->m_tradingSession = "session1";
        this->m_entryId = entryId;
        this->m_entryPx.Set(1, 1);
        this->m_entrySize.Set(1, 1);
        this->m_rptSeq = rptSeq;
    }
    TestTemplateItemInfo(const char *entryId) {
        this->m_action = MDUpdateAction::mduaAdd;
        this->m_entryType = MDEntryType::mdetBuyQuote;
        this->m_entryId = entryId;
        this->m_entryPx.Set(1, 1);
        this->m_entrySize.Set(1, 1);
    }
};

class TestTemplateInfo {
public:
    FeedConnectionMessage   m_templateId;
    int                     m_msgSeqNo;
    bool                    m_routeFirst;
    bool                    m_lastFragment;
    int                     m_itemsCount;
    int                     m_rptSec;
    int                     m_lastMsgSeqNoProcessed;
    TestTemplateItemInfo*   m_items[8];
    const char              *m_symbol;
    const char              *m_session;
    bool                    m_lost;
    bool                    m_wait;
    bool                    m_skip;

    TestTemplateInfo() {
        this->m_templateId = FeedConnectionMessage::fcmHeartBeat;
        this->m_msgSeqNo = 0;
        this->m_routeFirst = false;
        this->m_lastFragment = false;
        this->m_itemsCount = 0;
        this->m_rptSec = 0;
        this->m_lastMsgSeqNoProcessed = 0;
        this->m_symbol = 0;
        this->m_session = 0;
        this->m_lost = false;
        this->m_wait = false;
        this->m_skip = false;
    }

    TestTemplateInfo(FeedConnectionMessage templateId, int msgSeqNo) : TestTemplateInfo() {
        this->m_templateId = templateId;
        this->m_msgSeqNo = msgSeqNo;
        this->m_itemsCount = 0;
    }
    TestTemplateInfo(FeedConnectionMessage templateId, int msgSeqNo, TestTemplateItemInfo **items, int itemCount) : TestTemplateInfo(templateId, msgSeqNo) {
        this->m_itemsCount = itemCount;
        for(int i = 0; i < itemCount; i++)
            this->m_items[i] = items[i];
    }
    TestTemplateInfo(FeedConnectionMessage templateId, int msgSeqNo, TestTemplateItemInfo **items, int itemCount, int rptSeq) : TestTemplateInfo(templateId, msgSeqNo, items, itemCount) {
        this->m_rptSec = rptSeq;
    }
    TestTemplateInfo(FeedConnectionMessage templateId, int msgSeqNo, const char *symbol, const char *session, bool routeFirst, bool lastMessage, TestTemplateItemInfo **items, int itemCount, int rptSeq) :
            TestTemplateInfo(templateId, msgSeqNo, items, itemCount, rptSeq) {
        this->m_symbol = symbol;
        this->m_session = session;
        this->m_routeFirst = routeFirst;
        this->m_lastFragment = lastMessage;
    }
};

class OrderBookTester {
    FeedConnection_FOND_OBR *fcf;
    FeedConnection_FOND_OBS *fcs;
    FeedConnection_CURR_OBR *fcc;
public:
    OrderBookTester() {
        this->fcf = new FeedConnection_FOND_OBR("OBR", "Refresh Incremental", 'I',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);
        this->fcc = new FeedConnection_CURR_OBR("OBR", "Refresh Incremental", 'I',
                                                    FeedConnectionProtocol::UDP_IP,
                                                    "10.50.129.200", "239.192.113.3", 9113,
                                                    "10.50.129.200", "239.192.113.131", 9313);
        this->fcs = new FeedConnection_FOND_OBS("OBS", "Full Refresh", 'I',
                                                FeedConnectionProtocol::UDP_IP,
                                                "10.50.129.200", "239.192.113.3", 9113,
                                                "10.50.129.200", "239.192.113.131", 9313);
        this->fcs->m_fakeConnect = true;

    }
    ~OrderBookTester() {
        delete this->fcf;
        delete this->fcc;
    }

    FastOBSFONDInfo* CreateFastOBSFondInfo(const char *symbol, const char *trading) {
        FastOBSFONDInfo *info = new FastOBSFONDInfo();

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        return info;
    }

    FastOBSFONDItemInfo* CreateFastOBSFondItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        AutoAllocatePointerList<FastOBSFONDItemInfo> *list = new AutoAllocatePointerList<FastOBSFONDItemInfo>(1, 1);
        FastOBSFONDItemInfo *info = list->NewItem();

        char *id = new char[strlen(entryId) + 1];
        strcpy(id, entryId);

        char *type = new char[1];
        type[0] = (char) entryType;

        info->MDEntryID = id;
        info->MDEntryIDLength = strlen(id);
        info->MDEntryType = type;
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(priceMantissa, priceExponenta);
        info->MDEntrySize.Set(sizeMantissa, sizeExponenta);

        return info;
    }

    FastOBSFONDItemInfo* CreateFastOBRFondItemInfo(const char *symbol, const char *trading, INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDUpdateAction updateAction, MDEntryType entryType, const char *entryId, int rptSeq) {
        FastOBSFONDItemInfo *info = CreateFastOBSFondItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        info->MDUpdateAction = updateAction;
        info->RptSeq = rptSeq;

        return info;
    }

    FastOBSFONDItemInfo* CreateFastOBRFondItemInfo(const char *symbol, const char *trading, const char *entryId) {
        return CreateFastOBRFondItemInfo(symbol, trading, 1, 1, 1, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, entryId, 1);
    }
    FastOBSCURRInfo* CreateFastOBSCurrInfo(const char *symbol, const char *trading) {
        FastOBSCURRInfo *info = new FastOBSCURRInfo();

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        return info;
    }

    FastOBSCURRItemInfo* CreateFastOBSCurrItemInfo(INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDEntryType entryType, const char *entryId) {

        AutoAllocatePointerList<FastOBSCURRItemInfo> *list = new AutoAllocatePointerList<FastOBSCURRItemInfo>(1, 1);
        FastOBSCURRItemInfo *info = list->NewItem();

        char *id = new char[strlen(entryId) + 1];
        strcpy(id, entryId);

        char *type = new char[1];
        type[0] = (char) entryType;

        info->MDEntryID = id;
        info->MDEntryIDLength = strlen(id);
        info->MDEntryType = type;
        info->MDEntryTypeLength = 1;
        info->MDEntryPx.Set(priceMantissa, priceExponenta);
        info->MDEntrySize.Set(sizeMantissa, sizeExponenta);

        return info;
    }

    FastOBSCURRItemInfo* CreateFastOBRCurrItemInfo(const char *symbol, const char *trading, INT64 priceMantissa, INT32 priceExponenta, INT64 sizeMantissa, INT64 sizeExponenta, MDUpdateAction updateAction, MDEntryType entryType, const char *entryId, int rptSeq) {
        FastOBSCURRItemInfo *info = CreateFastOBSCurrItemInfo(priceMantissa, priceExponenta, sizeMantissa, sizeExponenta, entryType, entryId);

        char *smb = new char[strlen(symbol) + 1];
        strcpy(smb, symbol);

        char *trd = new char[strlen(trading) + 1];
        strcpy(trd, trading);

        info->Symbol = smb;
        info->SymbolLength = strlen(smb);

        info->TradingSessionID = trd;
        info->TradingSessionIDLength = strlen(trd);

        info->MDUpdateAction = updateAction;

        return info;
    }

    void TestItem(OrderBookInfo<FastOBSFONDItemInfo> *tableItem) {
        for(int i = 0; i < tableItem->BuyQuotes()->Count(); i++)
            if(tableItem->BuyQuotes()->Item(i)->Allocator == 0)
                throw;
        for(int i = 0; i < tableItem->SellQuotes()->Count(); i++)
            if(tableItem->SellQuotes()->Item(i)->Allocator == 0)
                throw;
    }

    void TestTableItemsAllocator(MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo> *table) {
        for(int i = 0; i < table->SymbolsCount(); i++) {
            for(int j = 0; j < table->Symbol(i)->Count(); j++) {
                OrderBookInfo<FastOBSFONDItemInfo> *item = table->Item(i, j);
                TestItem(item);
            }
        }
        /*for(int i = 0; i < MAX_SYMBOLS_COUNT; i++) {
            for(int j = 0; j < MAX_TRADING_SESSIONS_COUNT; j++) {
                bool found = false;
                OrderBookInfo<FastOBSFONDItemInfo> *titem = table->Item(i, j);
                for(int u = 0; u < table->UsedItemCount(); u++) {
                    OrderBookInfo<FastOBSFONDItemInfo> *item = table->UsedItem(i);

                    if(item == titem)
                        found = true;
                }

                if(titem->Used() != found)
                    throw;
            }
        }*/
    }

    void Clear() {
        fcf->SetSnapshot(this->fcs);
        fcf->OrderBookFond()->Clear();
        fcc->OrderBookCurr()->Clear();
        fcf->ClearMessages();
        fcf->WaitIncrementalMaxTimeMs(50);
        fcf->m_waitTimer->Stop();
        fcf->m_waitTimer->Stop(1);
        fcs->ClearMessages();
        fcs->WaitSnapshotMaxTimeMs(50);
        fcf->StartListenSnapshot();
        fcs->m_waitTimer->Stop();
        fcs->Stop();
        fcf->Stop();
        this->symbolsCount = 0;
        for(int i = 0; i < 100; i++) {
            this->symbols[i] = 0;
            this->rptSeq[i] = 0;
        }
        fcf->Start();
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Add() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;

        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001", 1);
        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002", 2);
        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003", 3);
        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004", 4);

        if(item4->Used)
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(!item1->Used)
            throw;
        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->Symbol(0)->Count() != 1)
            throw;
        OrderBookInfo<FastOBSFONDItemInfo> *obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        FastOBSFONDItemInfo *quote = obi->BuyQuotes()->Start()->Data();
        Decimal price(3, -2);
        Decimal size(1, 2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        quote = obi->BuyQuotes()->Start()->Data();
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 3)
            throw;

        quote = obi->BuyQuotes()->Start()->Data();
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID002", 10))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID001", 10))
            throw;

        quote = obi->BuyQuotes()->End()->Data();
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID003", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;

        quote = obi->BuyQuotes()->Start()->Data();
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID002", 10))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID001", 10))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Next()->Data();
        price.Set(25, -3);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID004", 10))
            throw;

        quote = obi->BuyQuotes()->End()->Data();
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, quote->MDEntryIDLength, "ENTRYID003", 10))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Remove() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001", 1);
        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002", 2);
        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003", 3);
        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;
        item4->RptSeq = 5;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);
        if(item4->Used)
            throw;
        if(item4->Allocator->Count() != 0)
            throw;

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;

        OrderBookInfo<FastOBSFONDItemInfo> *obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 3)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(2)->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;
        item3->RptSeq = 6;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;
        item2->RptSeq = 7;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;
        item1->RptSeq = 8;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Change() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001", 1);
        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002", 2);
        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003", 3);
        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        OrderBookInfo<FastOBSFONDItemInfo> *obi2 = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(1)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(2)->MDEntryID, 10, "ENTRYID004", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(3)->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        FastOBSFONDItemInfo *item5 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 24, -3, 1, 3, mduaChange, mdetBuyQuote, "ENTRYID002", 5);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;
        item5->RptSeq = 5;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(item2->Used || item2->Allocator->Count() != 0)
            throw;
        if(!item5->Used)
            throw;
        if(item5->Allocator->Count() != 1)
            throw;

        OrderBookInfo<FastOBSFONDItemInfo> *obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);

        FastOBSFONDItemInfo *qt1 = obi->BuyQuotes()->Item(0);
        FastOBSFONDItemInfo *qt2 = obi->BuyQuotes()->Item(1);
        FastOBSFONDItemInfo *qt3 = obi->BuyQuotes()->Item(2);
        FastOBSFONDItemInfo *qt4 = obi->BuyQuotes()->Item(3);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 10, "ENTRYID004", 10))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        if(qt1->MDEntryPx.Mantissa != item1->MDEntryPx.Mantissa)
            throw;
        if(qt1->MDEntryPx.Exponent != item1->MDEntryPx.Exponent)
            throw;

        if(qt3->MDEntryPx.Mantissa != item5->MDEntryPx.Mantissa)
            throw;
        if(qt3->MDEntryPx.Exponent != item5->MDEntryPx.Exponent)
            throw;
    }

    void Test_Clear() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001", 1);
        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002", 2);
        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003", 3);
        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        this->fcf->OrderBookFond()->Clear();
        if(item1->Used || item2->Used || item3->Used || item4->Used)
            throw;
        if(item1->Allocator->Count() != 0 ||
                item2->Allocator->Count() != 0 ||
                item3->Allocator->Count() != 0 ||
                item4->Allocator->Count() != 0)
            throw;
        if(this->fcf->OrderBookFond()->UsedItemCount() != 0)
            throw;

        OrderBookInfo<FastOBSFONDItemInfo> *obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OBS_FOND() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001", 1);
        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002", 2);
        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003", 3);
        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        OrderBookInfo<FastOBSFONDItemInfo> *obi2 = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi2->BuyQuotes()->Count() != 4)
            throw;

        FastOBSFONDInfo *info2 = CreateFastOBSFondInfo("SMB2", "TRADING001");
        FastOBSFONDItemInfo *newItem1 = CreateFastOBSFondItemInfo(7,-2, 1, 2, mdetBuyQuote, "ENTRYID007");
        FastOBSFONDItemInfo *newItem2 = CreateFastOBSFondItemInfo(8,-2, 1, 2, mdetBuyQuote, "ENTRYID008");
        info2->RptSeq = 5;

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->fcf->OrderBookFond()->ProcessSnapshot(info2);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 2)
            throw;

        OrderBookInfo<FastOBSFONDItemInfo> *obi3 = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi3->BuyQuotes()->Count() != 4)
            throw;

        OrderBookInfo<FastOBSFONDItemInfo> *obi = this->fcf->OrderBookFond()->GetItem("SMB2", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 2)
            throw;

        FastOBSFONDItemInfo *qt1 = obi->BuyQuotes()->Start()->Data();
        FastOBSFONDItemInfo *qt2 = obi->BuyQuotes()->Start()->Next()->Data();

        if(!StringIdComparer::Equal(qt1->MDEntryID, 10, "ENTRYID008", 10))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 10, "ENTRYID007", 10))
            throw;
        if(!qt1->MDEntryPx.Equal(8, -2))
            throw;
        if(!qt1->MDEntrySize.Equal(1, 2))
            throw;
        if(!qt2->MDEntryPx.Equal(7, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Add_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;

        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001", 1);
        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002", 2);
        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003", 3);
        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004", 4);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->Symbol(0)->Count() != 1)
            throw;
        OrderBookInfo<FastOBSFONDItemInfo> *obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 1)
            throw;
        FastOBSFONDItemInfo *quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 2)
            throw;
        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        quote = obi->SellQuotes()->Item(1);
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 3)
            throw;

        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        quote = obi->SellQuotes()->End()->Data();
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->SymbolsCount() != 1)
            throw;
        if(this->fcf->OrderBookFond()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;

        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Data();
        if(!quote->MDEntryPx.Equal(25, -3))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID004", 10))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Next()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        quote = obi->SellQuotes()->End()->Data();
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Remove_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001", 1);
        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002", 2);
        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003", 3);
        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;
        item4->RptSeq = 5;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;

        OrderBookInfo<FastOBSFONDItemInfo> *obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 3)
            throw;

        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 10,"ENTRYID003", 10))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 10,"ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(2)->MDEntryID, 10,"ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;
        item3->RptSeq = 6;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 10,"ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 10,"ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;
        item2->RptSeq = 7;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 10,"ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;
        item1->RptSeq = 8;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;

        obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND_Change_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001", 1);
        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002", 2);
        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003", 3);
        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        OrderBookInfo<FastOBSFONDItemInfo> *obi2 = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(0)->MDEntryID, 10, "ENTRYID003", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(1)->MDEntryID, 10, "ENTRYID004", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(2)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(3)->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        FastOBSFONDItemInfo *item5 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 24, -3, 1, 3, mduaChange, mdetSellQuote, "ENTRYID002", 5);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        OrderBookInfo<FastOBSFONDItemInfo> *obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);

        FastOBSFONDItemInfo *qt1 = obi->SellQuotes()->Item(0);
        FastOBSFONDItemInfo *qt2 = obi->SellQuotes()->Item(1);
        FastOBSFONDItemInfo *qt3 = obi->SellQuotes()->Item(2);
        FastOBSFONDItemInfo *qt4 = obi->SellQuotes()->Item(3);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 10, "ENTRYID003", 10))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 10, "ENTRYID004", 10))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        if(qt1->MDEntryPx.Mantissa != item3->MDEntryPx.Mantissa)
            throw;
        if(qt1->MDEntryPx.Exponent != item3->MDEntryPx.Exponent)
            throw;

        if(qt2->MDEntryPx.Mantissa != item5->MDEntryPx.Mantissa)
            throw;
        if(qt2->MDEntryPx.Exponent != item5->MDEntryPx.Exponent)
            throw;
    }

    void Test_Clear_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001", 1);
        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002", 2);
        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003", 3);
        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        this->fcf->OrderBookFond()->Clear();
        if(this->fcf->OrderBookFond()->UsedItemCount() != 0)
            throw;

        OrderBookInfo<FastOBSFONDItemInfo> *obi = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OBS_FOND_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo;
        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001", 1);
        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002", 2);
        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003", 3);
        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcf->OnIncrementalRefresh_OBR_FOND(info);

        FastOBSFONDInfo *info2 = CreateFastOBSFondInfo("SMB2", "TRADING001");
        FastOBSFONDItemInfo *newItem1 = CreateFastOBSFondItemInfo(7,-2, 1, 2, mdetSellQuote, "ENTRYID007");
        FastOBSFONDItemInfo *newItem2 = CreateFastOBSFondItemInfo(8,-2, 1, 2, mdetSellQuote, "ENTRYID008");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->fcf->OrderBookFond()->ProcessSnapshot(info2);

        if(this->fcf->OrderBookFond()->UsedItemCount() != 2)
            throw;

        OrderBookInfo<FastOBSFONDItemInfo> *obi3 = this->fcf->OrderBookFond()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi3->SellQuotes()->Count() != 4)
            throw;

        OrderBookInfo<FastOBSFONDItemInfo> *obi = this->fcf->OrderBookFond()->GetItem("SMB2", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 2)
            throw;

        FastOBSFONDItemInfo *qt1 = obi->SellQuotes()->Start()->Data();
        FastOBSFONDItemInfo *qt2 = obi->SellQuotes()->Start()->Next()->Data();

        if(!StringIdComparer::Equal(qt1->MDEntryID, 10, "ENTRYID007", 10))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 10, "ENTRYID008", 10))
            throw;
        if(!qt1->MDEntryPx.Equal(7, -2))
            throw;
        if(!qt1->MDEntrySize.Equal(1, 2))
            throw;
        if(!qt2->MDEntryPx.Equal(8, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_Add() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;

        FastOBSCURRItemInfo *item1 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001", 1);
        FastOBSCURRItemInfo *item2 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002", 2);
        FastOBSCURRItemInfo *item3 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003", 3);
        FastOBSCURRItemInfo *item4 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004", 4);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->Symbol(0)->Count() != 1)
            throw;
        OrderBookInfo<FastOBSCURRItemInfo> *obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        FastOBSCURRItemInfo *quote = obi->BuyQuotes()->Start()->Data();
        Decimal price(3, -2);
        Decimal size(1, 2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        quote = obi->BuyQuotes()->Start()->Data();
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 3)
            throw;

        quote = obi->BuyQuotes()->Start()->Data();
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        quote = obi->BuyQuotes()->End()->Data();
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;

        quote = obi->BuyQuotes()->Start()->Data();
        price.Set(4, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Data();
        price.Set(3, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        quote = obi->BuyQuotes()->Start()->Next()->Next()->Data();
        price.Set(25, -3);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID004", 10))
            throw;

        quote = obi->BuyQuotes()->End()->Data();
        price.Set(2, -2);
        if(!quote->MDEntryPx.Equal(&price))
            throw;
        if(!quote->MDEntrySize.Equal(&size))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID003", 10))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_Remove() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001", 1);
        FastOBSCURRItemInfo *item2 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002", 2);
        FastOBSCURRItemInfo *item3 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003", 3);
        FastOBSCURRItemInfo *item4 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        OrderBookInfo<FastOBSCURRItemInfo> *obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 3)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(2)->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(1)->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_Change() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001", 1);
        FastOBSCURRItemInfo *item2 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002", 2);
        FastOBSCURRItemInfo *item3 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003", 3);
        FastOBSCURRItemInfo *item4 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        OrderBookInfo<FastOBSCURRItemInfo> *obi2 = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(0)->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(1)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(2)->MDEntryID, 10, "ENTRYID004", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->BuyQuotes()->Item(3)->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        FastOBSCURRItemInfo *item5 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 24, -3, 1, 3, mduaChange, mdetBuyQuote, "ENTRYID002", 5);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        OrderBookInfo<FastOBSCURRItemInfo> *obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);

        FastOBSCURRItemInfo *qt1 = obi->BuyQuotes()->Item(0);
        FastOBSCURRItemInfo *qt2 = obi->BuyQuotes()->Item(1);
        FastOBSCURRItemInfo *qt3 = obi->BuyQuotes()->Item(2);
        FastOBSCURRItemInfo *qt4 = obi->BuyQuotes()->Item(3);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(obi->BuyQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 10, "ENTRYID004", 10))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        if(qt1->MDEntryPx.Mantissa != item1->MDEntryPx.Mantissa)
            throw;
        if(qt1->MDEntryPx.Exponent != item1->MDEntryPx.Exponent)
            throw;

        if(qt3->MDEntryPx.Mantissa != item5->MDEntryPx.Mantissa)
            throw;
        if(qt3->MDEntryPx.Exponent != item5->MDEntryPx.Exponent)
            throw;
    }

    void Test_Clear_Curr() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001", 1);
        FastOBSCURRItemInfo *item2 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002", 2);
        FastOBSCURRItemInfo *item3 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003", 3);
        FastOBSCURRItemInfo *item4 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        this->fcc->OrderBookCurr()->Clear();
        if(this->fcc->OrderBookCurr()->UsedItemCount() != 0)
            throw;

        OrderBookInfo<FastOBSCURRItemInfo> *obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OBS_CURR() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID001", 1);
        FastOBSCURRItemInfo *item2 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID002", 2);
        FastOBSCURRItemInfo *item3 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID003", 3);
        FastOBSCURRItemInfo *item4 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetBuyQuote, "ENTRYID004", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        FastOBSCURRInfo *info2 = CreateFastOBSCurrInfo("SMB2", "TRADING001");
        FastOBSCURRItemInfo *newItem1 = CreateFastOBSCurrItemInfo(7,-2, 1, 2, mdetBuyQuote, "ENTRYID007");
        FastOBSCURRItemInfo *newItem2 = CreateFastOBSCurrItemInfo(8,-2, 1, 2, mdetBuyQuote, "ENTRYID008");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->fcc->OrderBookCurr()->ProcessSnapshot(info2);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        OrderBookInfo<FastOBSCURRItemInfo> *obi3 = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi3->BuyQuotes()->Count() != 0)
            throw;

        OrderBookInfo<FastOBSCURRItemInfo> *obi = this->fcc->OrderBookCurr()->GetItem("SMB2", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 2)
            throw;

        FastOBSCURRItemInfo *qt1 = obi->BuyQuotes()->Start()->Data();
        FastOBSCURRItemInfo *qt2 = obi->BuyQuotes()->Start()->Next()->Data();

        if(!StringIdComparer::Equal(qt1->MDEntryID, 10, "ENTRYID008", 10))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 10, "ENTRYID007", 10))
            throw;
        if(!qt1->MDEntryPx.Equal(8, -2))
            throw;
        if(!qt1->MDEntrySize.Equal(1, 2))
            throw;
        if(!qt2->MDEntryPx.Equal(7, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_Add_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;

        FastOBSCURRItemInfo *item1 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001", 1);
        FastOBSCURRItemInfo *item2 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002", 2);
        FastOBSCURRItemInfo *item3 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003", 3);
        FastOBSCURRItemInfo *item4 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004", 4);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->Symbol(0)->Count() != 1)
            throw;
        OrderBookInfo<FastOBSCURRItemInfo> *obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 1)
            throw;
        FastOBSCURRItemInfo *quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 2)
            throw;
        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        quote = obi->SellQuotes()->Item(1);
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 3)
            throw;

        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        quote = obi->SellQuotes()->End()->Data();
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->SymbolsCount() != 1)
            throw;
        if(this->fcc->OrderBookCurr()->Symbol(0)->Count() != 1)
            throw;
        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi == 0)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;

        quote = obi->SellQuotes()->Start()->Data();
        if(!quote->MDEntryPx.Equal(2, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID003", 10))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Data();
        if(!quote->MDEntryPx.Equal(25, -3))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID004", 10))
            throw;

        quote = obi->SellQuotes()->Start()->Next()->Next()->Data();
        if(!quote->MDEntryPx.Equal(3, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        quote = obi->SellQuotes()->End()->Data();
        if(!quote->MDEntryPx.Equal(4, -2))
            throw;
        if(!quote->MDEntrySize.Equal(1, 2))
            throw;
        if(!StringIdComparer::Equal(quote->MDEntryID, 10, "ENTRYID002", 10))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_Remove_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001", 1);
        FastOBSCURRItemInfo *item2 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002", 2);
        FastOBSCURRItemInfo *item3 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003", 3);
        FastOBSCURRItemInfo *item4 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        item1->MDUpdateAction = mduaDelete;
        item2->MDUpdateAction = mduaDelete;
        item3->MDUpdateAction = mduaDelete;
        item4->MDUpdateAction = mduaDelete;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item4;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        OrderBookInfo<FastOBSCURRItemInfo> *obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 3)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 10, "ENTRYID003", 10))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(2)->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item3;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 2)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(1)->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item2;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 1)
            throw;
        if(!StringIdComparer::Equal(obi->SellQuotes()->Item(0)->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item1;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 0)
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_CURR_Change_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001", 1);
        FastOBSCURRItemInfo *item2 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002", 2);
        FastOBSCURRItemInfo *item3 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003", 3);
        FastOBSCURRItemInfo *item4 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        OrderBookInfo<FastOBSCURRItemInfo> *obi2 = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(0)->MDEntryID, 10, "ENTRYID003", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(1)->MDEntryID, 10, "ENTRYID004", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(2)->MDEntryID, 10, "ENTRYID001", 10))
            throw;
        if(!StringIdComparer::Equal(obi2->SellQuotes()->Item(3)->MDEntryID, 10, "ENTRYID002", 10))
            throw;

        FastOBSCURRItemInfo *item5 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 24, -3, 1, 3, mduaChange, mdetSellQuote, "ENTRYID002", 5);

        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        OrderBookInfo<FastOBSCURRItemInfo> *obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);

        FastOBSCURRItemInfo *qt1 = obi->SellQuotes()->Item(0);
        FastOBSCURRItemInfo *qt2 = obi->SellQuotes()->Item(1);
        FastOBSCURRItemInfo *qt3 = obi->SellQuotes()->Item(2);
        FastOBSCURRItemInfo *qt4 = obi->SellQuotes()->Item(3);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;
        if(obi->SellQuotes()->Count() != 4)
            throw;
        if(!StringIdComparer::Equal(qt1->MDEntryID, 10, "ENTRYID003", 10))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 10, "ENTRYID002", 10))
            throw;
        if(!StringIdComparer::Equal(qt3->MDEntryID, 10, "ENTRYID004", 10))
            throw;
        if(!StringIdComparer::Equal(qt4->MDEntryID, 10, "ENTRYID001", 10))
            throw;

        if(qt1->MDEntryPx.Mantissa != item3->MDEntryPx.Mantissa)
            throw;
        if(qt1->MDEntryPx.Exponent != item3->MDEntryPx.Exponent)
            throw;

        if(qt2->MDEntryPx.Mantissa != item5->MDEntryPx.Mantissa)
            throw;
        if(qt2->MDEntryPx.Exponent != item5->MDEntryPx.Exponent)
            throw;
    }

    void Test_Clear_Curr_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001", 1);
        FastOBSCURRItemInfo *item2 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002", 2);
        FastOBSCURRItemInfo *item3 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003", 3);
        FastOBSCURRItemInfo *item4 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        this->fcc->OrderBookCurr()->Clear();
        if(this->fcc->OrderBookCurr()->UsedItemCount() != 0)
            throw;

        OrderBookInfo<FastOBSCURRItemInfo> *obi = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi->BuyQuotes()->Count() != 0)
            throw;
    }

    void Test_OnFullRefresh_OBS_CURR_SellQuotes() {
        this->Clear();
        this->TestDefaults();

        FastIncrementalOBRCURRInfo *info = new FastIncrementalOBRCURRInfo;
        FastOBSCURRItemInfo *item1 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 3, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID001", 1);
        FastOBSCURRItemInfo *item2 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 4, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID002", 2);
        FastOBSCURRItemInfo *item3 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 2, -2, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID003", 3);
        FastOBSCURRItemInfo *item4 = CreateFastOBRCurrItemInfo("SMB1", "TRADING001", 25, -3, 1, 2, mduaAdd, mdetSellQuote, "ENTRYID004", 4);

        info->GroupMDEntriesCount = 4;
        info->GroupMDEntries[0] = item1;
        info->GroupMDEntries[1] = item2;
        info->GroupMDEntries[2] = item3;
        info->GroupMDEntries[3] = item4;

        this->fcc->OnIncrementalRefresh_OBR_CURR(info);

        FastOBSCURRInfo *info2 = CreateFastOBSCurrInfo("SMB2", "TRADING001");
        FastOBSCURRItemInfo *newItem1 = CreateFastOBSCurrItemInfo(7,-2, 1, 2, mdetSellQuote, "ENTRYID007");
        FastOBSCURRItemInfo *newItem2 = CreateFastOBSCurrItemInfo(8,-2, 1, 2, mdetSellQuote, "ENTRYID008");

        info2->GroupMDEntriesCount = 2;
        info2->GroupMDEntries[0] = newItem1;
        info2->GroupMDEntries[1] = newItem2;

        this->fcc->OrderBookCurr()->ProcessSnapshot(info2);

        if(this->fcc->OrderBookCurr()->UsedItemCount() != 1)
            throw;

        OrderBookInfo<FastOBSCURRItemInfo> *obi3 = this->fcc->OrderBookCurr()->GetItem("SMB1", 4, "TRADING001", 10);
        if(obi3->SellQuotes()->Count() != 0)
            throw;

        OrderBookInfo<FastOBSCURRItemInfo> *obi = this->fcc->OrderBookCurr()->GetItem("SMB2", 4, "TRADING001", 10);
        if(obi->SellQuotes()->Count() != 2)
            throw;

        FastOBSCURRItemInfo *qt1 = obi->SellQuotes()->Item(0);
        FastOBSCURRItemInfo *qt2 = obi->SellQuotes()->Item(1);

        if(!StringIdComparer::Equal(qt1->MDEntryID, 10, "ENTRYID007", 10))
            throw;
        if(!StringIdComparer::Equal(qt2->MDEntryID, 10, "ENTRYID008", 10))
            throw;
        if(!qt1->MDEntryPx.Equal(7, -2))
            throw;
        if(!qt1->MDEntrySize.Equal(1, 2))
            throw;
        if(!qt2->MDEntryPx.Equal(8, -2))
            throw;
    }

    void Test_OnIncrementalRefresh_OBR_FOND() {
        printf("Test_OnIncrementalRefresh_OBR_FOND_Add\n");
        Test_OnIncrementalRefresh_OBR_FOND_Add();
        printf("Test_OnIncrementalRefresh_OBR_FOND_Remove\n");
        Test_OnIncrementalRefresh_OBR_FOND_Remove();
        printf("Test_OnIncrementalRefresh_OBR_FOND_Change\n");
        Test_OnIncrementalRefresh_OBR_FOND_Change();
        printf("Test_Clear\n");
        Test_Clear();
    }

    void Test_OnIncrementalRefresh_OBR_FOND_SellQuotes() {
        printf("Test_OnIncrementalRefresh_OBR_FOND_Add_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_FOND_Add_SellQuotes();
        printf("Test_OnIncrementalRefresh_OBR_FOND_Remove_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_FOND_Remove_SellQuotes();
        printf("Test_OnIncrementalRefresh_OBR_FOND_Change_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_FOND_Change_SellQuotes();
        printf("Test_Clear_SellQuotes\n");
        Test_Clear_SellQuotes();
    }

    void Test_OnIncrementalRefresh_OBR_CURR() {
        printf("Test_OnIncrementalRefresh_OBR_CURR_Add\n");
        Test_OnIncrementalRefresh_OBR_CURR_Add();
        printf("Test_OnIncrementalRefresh_OBR_CURR_Remove\n");
        Test_OnIncrementalRefresh_OBR_CURR_Remove();
        printf("Test_OnIncrementalRefresh_OBR_CURR_Change\n");
        Test_OnIncrementalRefresh_OBR_CURR_Change();
        printf("Test_Clear_Curr\n");
        Test_Clear_Curr();
    }

    void Test_OnIncrementalRefresh_OBR_CURR_SellQuotes() {
        printf("Test_OnIncrementalRefresh_OBR_CURR_Add_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_CURR_Add_SellQuotes();
        printf("Test_OnIncrementalRefresh_OBR_CURR_Remove_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_CURR_Remove_SellQuotes();
        printf("Test_OnIncrementalRefresh_OBR_CURR_Change_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_CURR_Change_SellQuotes();
        printf("Test_Clear_SellQuotes\n");
        Test_Clear_SellQuotes();
    }

    void Test_OBR_CURR() {
        printf("Test_OnIncrementalRefresh_OBR_CURR\n");
        Test_OnIncrementalRefresh_OBR_CURR();
        printf("Test_OnFullRefresh_OBS_CURR\n");
        Test_OnFullRefresh_OBS_CURR();
        printf("Test_OnIncrementalRefresh_OBR_CURR_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_CURR_SellQuotes();
        printf("Test_OnFullRefresh_OBS_CURR_SellQuotes\n");
        Test_OnFullRefresh_OBS_CURR_SellQuotes();
    }

    void Test_OBR_FOND() {
        printf("Test_OnIncrementalRefresh_OBR_FOND\n");
        Test_OnIncrementalRefresh_OBR_FOND();
        printf("Test_OnFullRefresh_OBS_FOND\n");
        Test_OnFullRefresh_OBS_FOND();
        printf("Test_OnIncrementalRefresh_OBR_FOND_SellQuotes\n");
        Test_OnIncrementalRefresh_OBR_FOND_SellQuotes();
        printf("Test_OnFullRefresh_OBS_FOND_SellQuotes\n");
        Test_OnFullRefresh_OBS_FOND_SellQuotes();
    }

    void TestDefaults() {
        if(this->fcf->OrderBookFond()->SymbolsCount() != 0)
            throw;
        if(this->fcc->OrderBookCurr()->SymbolsCount() != 0)
            throw;
        this->TestTableItemsAllocator(fcf->OrderBookFond());
        //this->TestTableItemsAllocator(fcc->OrderBookCurr());
    }

    void TestTableItem_CorrectBegin() {
        OrderBookInfo<FastOBSFONDItemInfo> *tb = new OrderBookInfo<FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = CreateFastOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "ENTRYID001");
        item1->RptSeq = 1;
        item1->MDUpdateAction = mduaAdd;

        if(!tb->ProcessIncrementalMessage(item1))
            throw;
        if(tb->EntriesQueue()->MaxIndex() != -1)
            throw;
        if(tb->EntriesQueue()->RptSeq() != 0)
            throw;
        if(tb->RptSeq() != 1)
            throw;

        delete tb;
    }

    void TestTableItem_IncorrectBegin() {
        OrderBookInfo<FastOBSFONDItemInfo> *tb = new OrderBookInfo<FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = CreateFastOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "ENTRYID001");
        item1->RptSeq = 2;
        item1->MDUpdateAction = mduaAdd;

        if(tb->ProcessIncrementalMessage(item1))
            throw;
        if(tb->EntriesQueue()->MaxIndex() != 1)
            throw;
        if(tb->EntriesQueue()->StartRptSeq() != 1)
            throw;
        if(tb->EntriesQueue()->RptSeq() != 1)
            throw;
        if(tb->RptSeq() != 0)
            throw;

        delete tb;
    }

    void TestTableItem_SkipMessage() {
        OrderBookInfo<FastOBSFONDItemInfo> *tb = new OrderBookInfo<FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = CreateFastOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "ENTRYID001");
        item1->RptSeq = 1;
        item1->MDUpdateAction = mduaAdd;

        tb->ProcessIncrementalMessage(item1);

        FastOBSFONDItemInfo *item2 = CreateFastOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "ENTRYID002");
        item2->RptSeq = 3;
        item2->MDUpdateAction = mduaAdd;

        if(tb->ProcessIncrementalMessage(item2))
            throw;
        if(tb->EntriesQueue()->MaxIndex() != 1)
            throw;
        if(tb->EntriesQueue()->RptSeq() != 2)
            throw;
        if(tb->RptSeq() != 1)
            throw;

        FastOBSFONDItemInfo *item3 = CreateFastOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "ENTRYID003");
        item3->RptSeq = 4;
        item3->MDUpdateAction = mduaAdd;

        if(tb->ProcessIncrementalMessage(item3))
            throw;
        if(tb->EntriesQueue()->MaxIndex() != 2)
            throw;
        if(tb->EntriesQueue()->RptSeq() != 2)
            throw;
        if(tb->RptSeq() != 1)
            throw;

        delete tb;
    }

    void TestTable_Default() {

        MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo> *table = new MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo>();

        TestTableItemsAllocator(table);

        delete table;
    }

    void TestTable_AfterClear() {
        MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo> *table = new MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item = CreateFastOBRFondItemInfo("symbol1", "session1", "entry1");
        item->RptSeq = 1;

        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("symbol1", "session1", "entry1");
        item2->RptSeq = 2;

        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("symbol1", "session1", "entry1");
        item3->RptSeq = 4;

        table->ProcessIncremental(item);
        table->ProcessIncremental(item2);
        table->ProcessIncremental(item3);

        if(table->UsedItemCount() != 1)
            throw;
        OrderBookInfo<FastOBSFONDItemInfo> *tableItem = table->GetItem("symbol1", "session1");
        if(tableItem->EntriesQueue()->MaxIndex() != 1) // 3 is empty and 4 has value
            throw;
        table->Clear();
        if(table->UsedItemCount() != 0)
            throw;
        if(tableItem->RptSeq() != 0)
            throw;
        if(tableItem->BuyQuotes()->Count() != 0)
            throw;
        if(tableItem->EntriesQueue()->MaxIndex() != -1)
            throw;

        delete table;
    }

    void TestTable_CorrectBegin() {

        MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo> *table = new MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID001", 1);
        item1->RptSeq = 1;

        if(!table->ProcessIncremental(item1))
            throw;

        delete table;
    }

    void TestTable_IncorrectBegin() {
        MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo> *table = new MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID001", 1);
        item1->RptSeq = 2;

        if(table->ProcessIncremental(item1))
            throw;

        delete table;
    }

    void TestTable_SkipMessages() {
        MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo> *table = new MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID001", 1);
        item1->RptSeq = 1;

        if(!table->ProcessIncremental(item1))
            throw;

        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID001", 3);
        item2->RptSeq = 3;

        if(table->ProcessIncremental(item2))
            throw;

        delete table;
    }

    void Test_2UsedItemsAfter2IncrementalMessages() {
        MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo> *table = new MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID001", 1);
        item1->RptSeq = 1;

        if(!table->ProcessIncremental(item1))
            throw;

        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SYMBOL2", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID001", 1);
        item2->RptSeq = 1;

        if(!table->ProcessIncremental(item2))
            throw;

        if(table->UsedItemCount() != 2)
            throw;

        delete table;
    }

    void TestTable_CorrectApplySnapshot() {
        MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo> *table = new MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID001", 1);
        item1->RptSeq = 1;

        table->ProcessIncremental(item1);

        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID002", 3);
        item2->RptSeq = 3;

        if(table->ProcessIncremental(item2))
            throw;

        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID003", 4);
        item3->RptSeq = 4;

        if(table->ProcessIncremental(item3))
            throw;

        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID004", 5);
        item4->RptSeq = 5;

        if(table->ProcessIncremental(item4))
            throw;

        FastOBSFONDItemInfo *item5 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID005", 3);
        item5->RptSeq = 3;

        FastOBSFONDInfo *info = CreateFastOBSFondInfo("SYMBOL", "TRADING");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        OrderBookInfo<FastOBSFONDItemInfo> *tb = table->GetItem("SYMBOL", 6, "TRADING", 7);

        table->StartProcessSnapshot(info);
        if(tb != table->SnapshotItem())
            throw;
        if(tb->BuyQuotes()->Count() != 0)
            throw;
        if(tb->SellQuotes()->Count() != 0)
            throw;

        table->ProcessSnapshot(info->GroupMDEntries, 1, 3);
        if(tb->BuyQuotes()->Count() != 1)
            throw;
        if(tb->RptSeq() != 3)
            throw;
        if(!table->EndProcessSnapshot())
            throw;

        if(tb->RptSeq() != 5)
            throw;
        if(tb->BuyQuotes()->Count() != 3)
            throw;
        if(tb->EntriesQueue()->RptSeq() != 0)
            throw;
        if(tb->EntriesQueue()->MaxIndex() != -1)
            throw;
    }

    void TestTable_CorrectApplySnapshot_2() {

        MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo> *table = new MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID001", 1);
        item1->RptSeq = 1;

        table->ProcessIncremental(item1);

        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID003", 4);
        item3->RptSeq = 4;

        if(table->ProcessIncremental(item3))
            throw;

        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID004", 5);
        item4->RptSeq = 5;

        if(table->ProcessIncremental(item4))
            throw;

        FastOBSFONDInfo *info1 = CreateFastOBSFondInfo("SYMBOL", "TRADING");
        info1->GroupMDEntriesCount = 1;
        info1->RptSeq = 3;
        info1->RouteFirst = true;
        info1->GroupMDEntries[0] = CreateFastOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "ENTRYID002");

        FastOBSFONDInfo *info2 = CreateFastOBSFondInfo("SYMBOL", "TRADING");
        info2->GroupMDEntriesCount = 1;
        info2->RptSeq = 3;
        info2->RouteFirst = true;
        info2->GroupMDEntries[0] = CreateFastOBSFondItemInfo(8, 1, 8, 1, MDEntryType::mdetBuyQuote, "ENTRYID002");

        OrderBookInfo<FastOBSFONDItemInfo> *tb = table->GetItem("SYMBOL", 6, "TRADING", 7);

        table->StartProcessSnapshot(info1);
        if(tb != table->SnapshotItem())
            throw;
        if(tb->BuyQuotes()->Count() != 0)
            throw;
        if(tb->SellQuotes()->Count() != 0)
            throw;

        table->ProcessSnapshot(info1);
        table->ProcessSnapshot(info2);
        if(!table->EndProcessSnapshot())
            throw;
        if(tb->RptSeq() != 5)
            throw;
        if(tb->BuyQuotes()->Count() != 4)
            throw;
    }

    void TestTable_IncorrectApplySnapshot() {
        MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo> *table = new MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID001", 1);
        item1->RptSeq = 1;

        table->ProcessIncremental(item1);

        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID002", 4);
        item2->RptSeq = 4;

        if(table->ProcessIncremental(item2))
            throw;

        FastOBSFONDItemInfo *item3 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID003", 5);
        item3->RptSeq = 5;

        if(table->ProcessIncremental(item3))
            throw;

        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID004", 6);
        item4->RptSeq = 6;

        if(table->ProcessIncremental(item4))
            throw;

        FastOBSFONDItemInfo *item5 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID005", 2);
        item5->RptSeq = 2;

        FastOBSFONDInfo *info = CreateFastOBSFondInfo("SYMBOL", "TRADING");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        OrderBookInfo<FastOBSFONDItemInfo> *tb = table->GetItem("SYMBOL", 6, "TRADING", 7);

        table->StartProcessSnapshot(info);
        if(tb != table->SnapshotItem())
            throw;
        if(tb->BuyQuotes()->Count() != 0)
            throw;
        if(tb->SellQuotes()->Count() != 0)
            throw;

        table->ProcessSnapshot(info->GroupMDEntries, 1, 2);
        if(tb->BuyQuotes()->Count() != 1)
            throw;
        if(tb->RptSeq() != 2)
            throw;
        if(table->EndProcessSnapshot())
            throw;

        if(tb->RptSeq() != 2)
            throw;
    }

    void TestTable_IncorrectApplySnapshot_WhenMessageSkipped() {
        MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo> *table = new MarketDataTable<OrderBookInfo, FastOBSFONDInfo, FastOBSFONDItemInfo>();

        FastOBSFONDItemInfo *item1 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID001", 1);
        item1->RptSeq = 1;

        table->ProcessIncremental(item1);

        FastOBSFONDItemInfo *item2 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID002", 4);
        item2->RptSeq = 4;

        if(table->ProcessIncremental(item2))
            throw;

        FastOBSFONDItemInfo *item4 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID004", 6);
        item4->RptSeq = 6;

        if(table->ProcessIncremental(item4))
            throw;

        FastOBSFONDItemInfo *item5 = CreateFastOBRFondItemInfo("SYMBOL", "TRADING", 8, 1, 8, 1, MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "ENTRYID005", 3);
        item5->RptSeq = 3;

        FastOBSFONDInfo *info = CreateFastOBSFondInfo("SYMBOL", "TRADING");
        info->GroupMDEntriesCount = 1;
        info->GroupMDEntries[0] = item5;

        OrderBookInfo<FastOBSFONDItemInfo> *tb = table->GetItem("SYMBOL", 6, "TRADING", 7);

        table->StartProcessSnapshot(info);
        if(tb != table->SnapshotItem())
            throw;
        if(tb->BuyQuotes()->Count() != 0)
            throw;
        if(tb->SellQuotes()->Count() != 0)
            throw;

        table->ProcessSnapshot(info->GroupMDEntries, 1, 3);
        if(tb->BuyQuotes()->Count() != 1)
            throw;
        if(tb->RptSeq() != 3)
            throw;
        if(table->EndProcessSnapshot())
            throw;
        if(tb->RptSeq() != 4)
            throw;
        if(table->EndProcessSnapshot())
            throw;
    }

    void SendHearthBeatMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastHeartbeatInfo *info = new FastHeartbeatInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeHeartbeatInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    FastOBSFONDItemInfo* CreateObrFondItemInfo(TestTemplateItemInfo *tmp) {
        FastOBSFONDItemInfo *info = new FastOBSFONDItemInfo();
        info->AllowMDUpdateAction = true;
        info->MDUpdateAction = tmp->m_action;
        info->AllowMDEntryType = true;
        info->MDEntryType = new char[1];
        info->MDEntryType[0] = (char)tmp->m_entryType;
        info->MDEntryTypeLength = 1;
        info->AllowMDEntryPx = true;
        info->MDEntryPx.Assign(&tmp->m_entryPx);
        info->AllowMDEntrySize = true;
        info->MDEntrySize.Assign(&tmp->m_entrySize);
        info->AllowRptSeq = true;
        info->RptSeq = tmp->m_rptSeq;
        if(tmp->m_symbol != 0) {
            info->AllowSymbol = true;
            info->SymbolLength = strlen(tmp->m_symbol);
            info->Symbol = new char[info->SymbolLength + 1];
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_tradingSession != 0) {
            info->AllowTradingSessionID = true;
            info->TradingSessionIDLength = strlen(tmp->m_tradingSession);
            info->TradingSessionID = new char[info->TradingSessionIDLength + 1];
            strcpy(info->TradingSessionID, tmp->m_tradingSession);
        }
        if(tmp->m_entryId != 0) {
            info->AllowMDEntryID = true;
            info->MDEntryIDLength = strlen(tmp->m_entryId);
            info->MDEntryID = new char[info->MDEntryIDLength + 1];
            strcpy(info->MDEntryID, tmp->m_entryId);
        }
        return info;
    }

    void SendObrFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastIncrementalOBRFONDInfo *info = new FastIncrementalOBRFONDInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateObrFondItemInfo(tmp->m_items[i]);
        }
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeIncrementalOBRFONDInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());

    }
    void SendObsFondMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        FastOBSFONDInfo *info = new FastOBSFONDInfo();
        info->MsgSeqNum = tmp->m_msgSeqNo;
        info->GroupMDEntriesCount = tmp->m_itemsCount;
        info->AllowRouteFirst = true;
        info->AllowLastFragment = true;
        info->AllowLastMsgSeqNumProcessed = true;
        info->LastMsgSeqNumProcessed = tmp->m_lastMsgSeqNoProcessed;

        if(tmp->m_symbol != 0) {
            info->SymbolLength = strlen(tmp->m_symbol);
            info->Symbol = new char[info->SymbolLength + 1];
            strcpy(info->Symbol, tmp->m_symbol);
        }
        if(tmp->m_session != 0) {
            info->AllowTradingSessionID = true;
            info->TradingSessionIDLength = strlen(tmp->m_session);
            info->TradingSessionID = new char[info->TradingSessionIDLength + 1];
            strcpy(info->TradingSessionID, tmp->m_session);
        }

        info->RptSeq = tmp->m_rptSec;
        info->RouteFirst = tmp->m_routeFirst;
        info->LastFragment = tmp->m_lastFragment;
        for(int i = 0; i < tmp->m_itemsCount; i++) {
            info->GroupMDEntries[i] = CreateObrFondItemInfo(tmp->m_items[i]);
        }
        conn->m_fastProtocolManager->SetNewBuffer(conn->m_recvABuffer->CurrentPos(), 2000);
        conn->m_fastProtocolManager->EncodeOBSFONDInfo(info);
        conn->ProcessServerCore(conn->m_fastProtocolManager->MessageLength());
    }

    void SendMessage(FeedConnection *conn, TestTemplateInfo *tmp) {
        switch(tmp->m_templateId) {
            case FeedConnectionMessage::fcmHeartBeat:
                SendHearthBeatMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND:
                SendObrFondMessage(conn, tmp);
                break;
            case FeedConnectionMessage::fmcFullRefresh_OBS_FOND:
                SendObsFondMessage(conn, tmp);
            default:
                break;
        }
    }

    void SendMessages(FeedConnection *conn, TestTemplateInfo **templates, int templatesCount) {
        for(int i = 0; i < templatesCount; i++)
            SendMessage(conn, templates[i]);
    }


    void SendSimpleIncrementalMessage(FeedConnection *fc, FeedConnectionMessage msg, const char *symbol, int msgSeqNum, int rptSeq) {
        TestTemplateItemInfo *item = new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, symbol, "session1", "entry1", rptSeq, 1, 1, 1, 1);
        TestTemplateInfo *info = new TestTemplateInfo(msg, msgSeqNum, &item, 1);
        SendMessages(fc, &info, 1);
    }

    void TestConnection_EmptyTest() {
        this->Clear();

        SendMessages(fcf, new TestTemplateInfo*[3] {
                new TestTemplateInfo(FeedConnectionMessage::fcmHeartBeat, 1),
                new TestTemplateInfo(FeedConnectionMessage::fcmHeartBeat, 2),
                new TestTemplateInfo(FeedConnectionMessage::fcmHeartBeat, 3)}, 3);

    }

    void TestConnection_TestCorrectIncMessages() {
        this->Clear();

        SendMessages(fcf, new TestTemplateInfo*[3] {
            new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                 new TestTemplateItemInfo*[2] {
                                    new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "SYMBOL1", "SESSION1", "ENTRY1", 1, 1, 1, 1, 1),
                                    new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "SYMBOL1", "SESSION1", "ENTRY2", 2, 2, 1, 2, 1),
                                 }, 2),
            new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 2,
                                 new TestTemplateItemInfo*[1] {
                                         new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "SYMBOL1", "SESSION1", "ENTRY3", 3, 3, 1, 3, 1),
                                 }, 1),
            new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                 new TestTemplateItemInfo*[1] {
                                         new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "SYMBOL1", "SESSION1", "ENTRY4", 4, 3, 1, 3, 1),
                                 }, 1)
        }, 3);


        if(!fcf->ProcessIncrementalMessages())
            throw;

        this->TestTableItemsAllocator(fcf->OrderBookFond());

        if(fcf->m_waitTimer->Active()) // everything is ok = timer should not be activated
            throw;
        if(fcf->OrderBookFond()->GetItem("SYMBOL1", "SESSION1")->BuyQuotes()->Count() != 4)
            throw;
    }

    /*
     * Incremental message num 2 is lost. This means that for item symbol1 and session1 only first two MDEntryItems will be applied and
     * MDEntryItem with rptseq = 4 will be added to que
     * and then we receive msg num 3 and apply all
     * */
    void TestConnection_TestIncMessagesLost_AndWhenAppeared() {
        this->Clear();

        SendMessages(fcf, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry3", 4, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!fcf->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(fcf->OrderBookFond());

        OrderBookInfo<FastOBSFONDItemInfo> *item = fcf->OrderBookFond()->GetItem("symbol1", "session1");
        if(item->BuyQuotes()->Count() != 2)
            throw;
        if(!fcf->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 1) // cell for rptseq 3 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(item->EntriesQueue()->Entries()[1]->RptSeq != 4)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(fcf, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry4", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!fcf->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(fcf->OrderBookFond());

        if(fcf->m_waitTimer->Active()) // wait timer should be deactivated because we received all lost messages
            throw;
        if(item->BuyQuotes()->Count() != 4) // all messages from que should be applied
            throw;
        if(item->EntriesQueue()->MaxIndex() != -1) // should be reset
            throw;
    }

    void TestConnection_TestInc2MessagesLost_AppearedThen2Messages() {
        this->Clear();

        SendMessages(fcf, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry5", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!fcf->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(fcf->OrderBookFond());

        OrderBookInfo<FastOBSFONDItemInfo> *item = fcf->OrderBookFond()->GetItem("symbol1", "session1");
        if(item->BuyQuotes()->Count() != 2)
            throw;
        if(!fcf->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // cells for rptseq 3 and 4 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(item->EntriesQueue()->Entries()[1] != 0) // cell for rptseq 4 is empty
            throw;
        if(item->EntriesQueue()->Entries()[2]->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(fcf, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 2,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry3", 3, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry4", 4, 1, 1, 1, 1),
                                     }, 2)
        }, 1);

        if(!fcf->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(fcf->OrderBookFond());

        if(fcf->m_waitTimer->Active()) // wait timer should be deactivated because we received all lost messages
            throw;
        if(item->BuyQuotes()->Count() != 5) // all messages from que should be applied
            throw;
        if(item->EntriesQueue()->MaxIndex() != -1) // should be reset
            throw;
    }

    void TestConnection_TestInc2MessagesLost_AppearedSeparately_1_2() {
        this->Clear();

        SendMessages(fcf, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry5", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!fcf->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(fcf->OrderBookFond());

        OrderBookInfo<FastOBSFONDItemInfo> *item = fcf->OrderBookFond()->GetItem("symbol1", "session1");
        if(item->BuyQuotes()->Count() != 2)
            throw;
        if(!fcf->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // cells for rptseq 3 and 4 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(item->EntriesQueue()->Entries()[1] != 0) // cell for rptseq 4 is empty
            throw;
        if(item->EntriesQueue()->Entries()[2]->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(fcf, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry3", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!fcf->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(fcf->OrderBookFond());

        if(!fcf->m_waitTimer->Active()) // wait timer should be active because 2 messages lost but received 1
            throw;
        if(item->BuyQuotes()->Count() != 3) // at least one message is applied
            throw;
        if(!item->EntriesQueue()->HasEntries()) // should have entries
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // should be reset
            throw;
        if(item->RptSeq() != 3) // now rpt seq should be 3
            throw;

        SendMessages(fcf, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry3", 4, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!fcf->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(fcf->OrderBookFond());

        if(fcf->m_waitTimer->Active()) // now wait timer should be deactivated because we received all messages
            throw;
        if(item->BuyQuotes()->Count() != 5) // all messages applied
            throw;
        if(item->EntriesQueue()->HasEntries()) // should have entries
            throw;
        if(item->RptSeq() != 5) // last processed msg
            throw;
    }

    void TestConnection_TestInc2MessagesLost_AppearedSeparately_2_1() {
        this->Clear();

        SendMessages(fcf, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry5", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!fcf->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(fcf->OrderBookFond());

        OrderBookInfo<FastOBSFONDItemInfo> *item = fcf->OrderBookFond()->GetItem("symbol1", "session1");
        if(item->BuyQuotes()->Count() != 2)
            throw;
        if(!fcf->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        if(item->EntriesQueue()->StartRptSeq() != 3) // should be first lost RptSeq
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2) // cells for rptseq 3 and 4 is empty but cell for pushed message is filled with mdentry 4
            throw;
        if(item->EntriesQueue()->Entries()[0] != 0) // cell for rptseq 3 is empty
            throw;
        if(item->EntriesQueue()->Entries()[1] != 0) // cell for rptseq 4 is empty
            throw;
        if(item->EntriesQueue()->Entries()[2]->RptSeq != 5)
            throw;

        // lost message finally appeared before wait timer elapsed
        SendMessages(fcf, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry3", 4, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!fcf->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(fcf->OrderBookFond());

        if(!fcf->m_waitTimer->Active()) // wait timer should be active because 2 messages lost but received 1
            throw;
        if(item->BuyQuotes()->Count() != 2) // nothing encreased because first message skipped
            throw;
        if(!item->EntriesQueue()->HasEntries()) // should have entries
            throw;
        if(item->EntriesQueue()->MaxIndex() != 2)
            throw;
        if(item->RptSeq() != 2) // because nothing was applied
            throw;

        SendMessages(fcf, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 2,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry3", 3, 1, 1, 1, 1),
                                     }, 1)
        }, 1);

        if(!fcf->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(fcf->OrderBookFond());

        if(fcf->m_waitTimer->Active()) // now wait timer should be deactivated because we received all messages
            throw;
        if(item->BuyQuotes()->Count() != 5) // applied two messages
            throw;
        if(item->EntriesQueue()->HasEntries()) // should have entries
            throw;
        if(item->RptSeq() != 5) // last processed msg
            throw;
    }

    void TestConnection_TestIncMessageLost_AndWaitTimerElapsed() {
        this->Clear();

        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;

        SendMessages(fcf, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry1", 1, 1, 1, 1, 1),
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry2", 2, 2, 1, 2, 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 4,
                                     new TestTemplateItemInfo*[1] {
                                             new TestTemplateItemInfo(MDUpdateAction::mduaAdd, MDEntryType::mdetBuyQuote, "symbol1", "session1", "entry5", 5, 3, 1, 3, 1),
                                     }, 1)
        }, 2);
        if(!fcf->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(fcf->OrderBookFond());

        OrderBookInfo<FastOBSFONDItemInfo> *item = fcf->OrderBookFond()->GetItem("symbol1", "session1");
        if(!fcf->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        // wait
        while(fcf->m_waitTimer->ElapsedMilliseconds() < fcf->WaitIncrementalMaxTimeMs());
        if(!fcf->Listen_Atom_Incremental_Core())
            throw;
        //entering snapshot mode
        if(fcs->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!fcs->m_waitTimer->Active())
            throw;
        // timer should be stopped
        if(fcf->m_waitTimer->Active())
            throw;
        if(fcs->m_startMsgSeqNum != -1)
            throw;
        if(fcs->m_endMsgSeqNum != -1)
            throw;
    }

    void TestConnection_TestSnapshotNoMessagesAtAll() {
        this->Clear();

        fcf->StartListenSnapshot();
        if(!fcs->m_waitTimer->Active()) // start wait timer immediately
            throw;

        //no messages
        while(fcs->m_waitTimer->ElapsedMilliseconds() <= fcs->WaitSnapshotMaxTimeMs()) {
            if(!fcs->m_waitTimer->Active())
                throw;
            if(!fcs->Listen_Atom_Snapshot_Core())
                throw; // nothing should be happens
            if(fcs->m_endMsgSeqNum != -1)
                throw;
            if(fcs->m_startMsgSeqNum != -1)
                throw;
        }

        if(!fcs->Listen_Atom_Snapshot_Core()) // reconnect
            throw;
        if(fcs->m_waitTimer->Active())
            throw;
        if(fcs->m_state != FeedConnectionState::fcsConnect)
            throw;
        if(fcs->m_nextState != FeedConnectionState::fcsListenSnapshot)
            throw;

        // now we should restart?
        if(!fcs->Reconnect_Atom())
            throw;
        if(!fcs->m_waitTimer->Active())
            throw;
        if(fcs->m_startMsgSeqNum != -1)
            throw;
        if(fcs->m_endMsgSeqNum != -1)
            throw;
    }

    void TestConnection_OneMessageReceived() {
        this->Clear();
        fcf->StartListenSnapshot();

        //no messages first half time
        while(fcs->m_waitTimer->ElapsedMilliseconds() < fcs->WaitSnapshotMaxTimeMs() / 2) {
            if(!fcs->m_waitTimer->Active())
                throw;
            if(!fcs->Listen_Atom_Snapshot_Core())
                throw; // nothing should be happens
            if(fcs->m_endMsgSeqNum != -1)
                throw;
            if(fcs->m_startMsgSeqNum != -1)
                throw;
        }

        SendMessages(fcs, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 2, "symbol1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("entry1"),
                                             new TestTemplateItemInfo("entry2"),
                                     }, 2, 4)
        }, 1);

        if(fcs->m_startMsgSeqNum != 2)
            throw;
        if(fcs->m_endMsgSeqNum != 2)
            throw;
        if(!fcs->m_waitTimer->Active())
            throw;
        //timer should be active but reset
        if(fcs->m_waitTimer->ElapsedMilliseconds() >= fcs->WaitSnapshotMaxTimeMs() / 2)
            throw;

        if(!fcs->Listen_Atom_Snapshot_Core())
            throw; // nothing should be happens
    }

    void TestConnection_RouteFirstReceived_Empty() {

        this->Clear();
        fcf->StartListenSnapshot();

        SendMessages(fcs, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 2, "symbol1", "session1", true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("entry1"),
                                             new TestTemplateItemInfo("entry2"),
                                     }, 2, 4)
        }, 1);

        if(!fcs->Listen_Atom_Snapshot_Core())
            throw;
        if(fcs->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(fcs->m_startMsgSeqNum != 3)
            throw;
        if(fcs->m_endMsgSeqNum != 2)
            throw;
        if(fcs->m_snapshotRouteFirst != 2)
            throw;
        if(!fcs->m_waitTimer->Active())
            throw;

        // just empty cyccle - nothing should be changed
        if(!fcs->Listen_Atom_Snapshot_Core())
            throw;
        if(!fcs->Listen_Atom_Snapshot_Core())
            throw;
        if(!fcs->Listen_Atom_Snapshot_Core())
            throw;

        if(fcs->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;

        if(fcs->m_startMsgSeqNum != 3)
            throw;
        if(fcs->m_endMsgSeqNum != 2)
            throw;
        if(fcs->m_snapshotRouteFirst != 2)
            throw;
        if(!fcs->m_waitTimer->Active())
            throw;
    }

    void TestConnection_RouteFirstReceived_AfterSomeDummyMessages() {
        this->Clear();
        fcf->StartListenSnapshot();

        SendMessages(fcs, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 1, "symbol1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("entry1"),
                                             new TestTemplateItemInfo("entry2"),
                                     }, 2, 4)
        }, 1);

        if(!fcs->Listen_Atom_Snapshot_Core())
            throw;
        if(fcs->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(fcs->m_startMsgSeqNum != 2)
            throw;
        if(fcs->m_endMsgSeqNum != 1)
            throw;
        if(fcs->m_snapshotRouteFirst != -1)
            throw;
        if(!fcs->m_waitTimer->Active())
            throw;

        SendMessages(fcs, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 2, "symbol1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("entry1"),
                                             new TestTemplateItemInfo("entry2"),
                                     }, 2, 4)
        }, 1);

        if(!fcs->Listen_Atom_Snapshot_Core())
            throw;
        if(fcs->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(fcs->m_startMsgSeqNum != 3)
            throw;
        if(fcs->m_endMsgSeqNum != 2)
            throw;
        if(fcs->m_snapshotRouteFirst != -1)
            throw;
        if(!fcs->m_waitTimer->Active())
            throw;

        SendMessages(fcs, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 3, "symbol1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("entry1"),
                                             new TestTemplateItemInfo("entry2"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 4, "symbol1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("entry1"),
                                             new TestTemplateItemInfo("entry2"),
                                     }, 2, 4)
        }, 2);

        if(!fcs->Listen_Atom_Snapshot_Core())
            throw;
        if(fcs->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(fcs->m_startMsgSeqNum != 5)
            throw;
        if(fcs->m_endMsgSeqNum != 4)
            throw;
        if(fcs->m_snapshotRouteFirst != -1)
            throw;
        if(!fcs->m_waitTimer->Active())
            throw;

        SendMessages(fcs, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 5, "symbol1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("entry1"),
                                             new TestTemplateItemInfo("entry2"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 6, "symbol1", "session1", true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("entry1"),
                                             new TestTemplateItemInfo("entry2"),
                                     }, 2, 4)
        }, 2);

        if(!fcs->Listen_Atom_Snapshot_Core())
            throw;
        if(fcs->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(fcs->m_startMsgSeqNum != 7)
            throw;
        if(fcs->m_endMsgSeqNum != 6)
            throw;
        if(fcs->m_snapshotRouteFirst != 6)
            throw;
        if(!fcs->m_waitTimer->Active())
            throw;

        // just empty cyccle - nothing should be changed
        if(!fcs->Listen_Atom_Snapshot_Core())
            throw;
        if(!fcs->Listen_Atom_Snapshot_Core())
            throw;
        if(!fcs->Listen_Atom_Snapshot_Core())
            throw;

        if(fcs->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(fcs->m_startMsgSeqNum != 7)
            throw;
        if(fcs->m_endMsgSeqNum != 6)
            throw;
        if(fcs->m_snapshotRouteFirst != 6)
            throw;
        if(!fcs->m_waitTimer->Active())
            throw;
    }

    void TestConnection_LastFragmentReceivedBeforeRouteFirst() {
        this->Clear();
        fcf->StartListenSnapshot();

        SendMessages(fcs, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 1, "symbol1", "session1", false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("entry1"),
                                             new TestTemplateItemInfo("entry2"),
                                     }, 2, 4)
        }, 1);

        if(!fcs->Listen_Atom_Snapshot_Core())
            throw;
        if(fcs->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(fcs->m_startMsgSeqNum != 2)
            throw;
        if(fcs->m_endMsgSeqNum != 1)
            throw;
        if(fcs->m_snapshotRouteFirst != -1)
            throw;
        if(fcs->m_snapshotLastFragment != -1)
            throw;
        if(!fcs->m_waitTimer->Active())
            throw;
    }

    void TestConnection_SnapshotSomeMessagesNotReceived() {
        this->Clear();
        fcf->StartListenSnapshot();

        SendMessages(fcs, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 1, "symbol1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("entry1"),
                                             new TestTemplateItemInfo("entry2"),
                                     }, 2, 4)
        }, 1);

        fcs->Listen_Atom_Snapshot_Core();

        // message seq 2 lost
        SendMessages(fcs, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 3, "symbol1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("entry1"),
                                             new TestTemplateItemInfo("entry2"),
                                     }, 2, 4)
        }, 1);

        fcs->Listen_Atom_Snapshot_Core();

        if(fcs->m_startMsgSeqNum != 2)
            throw;
        if(fcs->m_endMsgSeqNum != 3)
            throw;
        if(fcs->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!fcs->m_waitTimer->Active())
            throw;
        if(!fcs->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;

        fcs->m_waitTimer->Stop(); // reset timer 0 to avoid simulate situation when no packet received
        // now wait some time and after that we have to skip lost message to get other snapshot
        while(!fcs->m_waitTimer->IsElapsedMilliseconds(1, fcs->WaitSnapshotMaxTimeMs())) {
            fcs->Listen_Atom_Snapshot_Core();
        }

        fcs->Listen_Atom_Snapshot_Core();
        if(fcs->m_startMsgSeqNum != 4)
            throw;
        if(fcs->m_endMsgSeqNum != 3)
            throw;
        if(fcs->m_waitTimer->Active(1))
            throw;
    }

    void TestConnection_SnapshotSomeMessagesReceivedLater() {
        this->Clear();
        fcf->StartListenSnapshot();

        SendMessages(fcs, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 1, "symbol1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("entry1"),
                                             new TestTemplateItemInfo("entry2"),
                                     }, 2, 4)
        }, 1);

        fcs->Listen_Atom_Snapshot_Core();

        // message seq 2 lost
        SendMessages(fcs, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 3, "symbol1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("entry1"),
                                             new TestTemplateItemInfo("entry2"),
                                     }, 2, 4)
        }, 1);

        if(!fcs->Listen_Atom_Snapshot_Core())
            throw;

        if(fcs->m_startMsgSeqNum != 2)
            throw;
        if(fcs->m_endMsgSeqNum != 3)
            throw;
        if(fcs->m_state != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!fcs->m_waitTimer->Active())
            throw;
        if(!fcs->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;

        // wait some time and then receive lost packet
        while(!fcs->m_waitTimer->IsElapsedMilliseconds(1, fcs->WaitSnapshotMaxTimeMs() / 2)) {
            fcs->m_waitTimer->Start(); // reset timer 0 to avoid simulate situation when no packet received
            if(!fcs->Listen_Atom_Snapshot_Core())
                throw;
        }

        if(!fcs->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;

        SendMessages(fcs, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 2, "symbol1", "session1", false, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("entry1"),
                                             new TestTemplateItemInfo("entry2"),
                                     }, 2, 4)
        }, 1);

        if(!fcs->Listen_Atom_Snapshot_Core())
            throw;
        if(fcs->m_startMsgSeqNum != 4)
            throw;
        if(fcs->m_endMsgSeqNum != 3)
            throw;
        if(fcs->m_waitTimer->Active(1)) // we have to activate another timer to watch lost message
            throw;
    }

    void TestConnection_StopTimersAfterReconnect() {
        this->Clear();
        fcf->StartListenSnapshot();

        // manually activate timer 1
        fcs->m_waitTimer->Activate(1);
        fcs->ReconnectSetNextState(FeedConnectionState::fcsListenSnapshot);
        fcs->DoWorkAtom();

        if(!fcs->m_waitTimer->Active())
            throw;
        if(fcs->m_waitTimer->Active(1))
            throw;
    }

    void TestConnection_TestSnapshotCollect() {
        this->Clear();
        fcf->StartListenSnapshot();

        SendMessages(fcs, new TestTemplateInfo*[1] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 2, "symbol1", "session1", true, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("entry1"),
                                             new TestTemplateItemInfo("entry2"),
                                     }, 2, 4)
        }, 1);

        if(fcs->m_startMsgSeqNum != 2)
            throw;
        if(fcs->m_endMsgSeqNum != 2)
            throw;

        fcs->Listen_Atom_Snapshot_Core();
        //snapshot received and should be applied
        OrderBookInfo<FastOBSFONDItemInfo> *tableItem = fcf->OrderBookFond()->GetItem("symbol1", "session1");

        this->TestTableItemsAllocator(fcf->OrderBookFond());

        if(fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;

        if(tableItem->BuyQuotes()->Count() != 2)
            throw;
        if(fcs->m_snapshotRouteFirst != -1)
            throw;
        if(fcs->m_snapshotLastFragment != -1)
            throw;
        if(fcs->m_startMsgSeqNum != 3)
            throw;
        if(fcs->m_endMsgSeqNum != 2)
            throw;
    }

    void TestConnection_TestSnapshotMessageLostAndTimeExpired() {
        this->Clear();
        fcs->WaitSnapshotMaxTimeMs(100);
        fcf->StartListenSnapshot();

        if(!fcs->m_waitTimer->Active())
            throw;

        fcs->m_waitTimer->Stop();
        SendMessages(fcs, new TestTemplateInfo*[2] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 2, "symbol1", "session1", true, false,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("entry1"),
                                             new TestTemplateItemInfo("entry2"),
                                     }, 2, 4),
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 4, "symbol1", "session1", false, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("entry1"),
                                             new TestTemplateItemInfo("entry2"),
                                     }, 2, 6),
        }, 2);

        if(fcs->m_packets[3]->m_item != 0)
            throw;
        if(fcs->m_startMsgSeqNum != 2)
            throw;
        if(fcs->m_endMsgSeqNum != 4)
            throw;
        if(!fcs->m_waitTimer->Active())
            throw;

        fcs->m_waitTimer->Reset();
        fcs->Listen_Atom_Snapshot_Core();

        if(!fcs->m_waitTimer->Active())
            throw;
        if(fcs->m_waitTimer->Active(1))
            throw;
        if(fcs->m_startMsgSeqNum != 3)
            throw;
        if(fcs->m_snapshotRouteFirst != 2)
            throw;
        if(fcs->m_snapshotLastFragment != -1)
            throw;

        fcs->Listen_Atom_Snapshot_Core();
        if(!fcs->m_waitTimer->Active(1))
            throw;
        while(fcs->m_waitTimer->ElapsedMilliseconds(1) <= fcs->WaitSnapshotMaxTimeMs())
            fcs->Listen_Atom_Snapshot_Core();

        fcs->Listen_Atom_Snapshot_Core();
        // reset
        if(fcs->m_snapshotRouteFirst != -1)
            throw;
        if(fcs->m_snapshotLastFragment != -1)
            throw;
        if(fcs->m_waitTimer->Active(1))
            throw;
    }
    /*
     * Snapshot received for only one item, this means that snapshot connection should not be stopped
     * */
    void TestConnection_TestMessagesLost_2Items_SnapshotReceivedForOneItem() {
        this->Clear();
        fcf->StartListenSnapshot();

        this->TestTableItemsAllocator(fcf->OrderBookFond());

        SendMessages(fcf, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", "entry1", 1),
                                             new TestTemplateItemInfo("symbol2", "entry1", 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", "entry1", 4),
                                             new TestTemplateItemInfo("symbol2", "entry1", 4),
                                     }, 2)
        }, 2);

        if(!fcf->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(fcf->OrderBookFond());

        if(fcf->OrderBookFond()->UsedItemCount() != 2)
            throw;

        if(!fcf->m_waitTimer->Active()) // not all messages was processed - some messages was skipped
            throw;
        // wait
        while(fcf->m_waitTimer->ElapsedMilliseconds() < fcf->WaitIncrementalMaxTimeMs());

        // sending snapshot for only one item and rpt seq before last incremental message
        SendMessages(fcs, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedConnectionMessage::fmcFullRefresh_OBS_FOND, 2, "symbol1", "session1", true, true,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("entry1"),
                                             new TestTemplateItemInfo("entry1"),
                                     }, 2, 4)
        }, 1);
        if(!fcs->Listen_Atom_Snapshot_Core())
            throw;

        this->TestTableItemsAllocator(fcf->OrderBookFond());

        // snapshot for first item should be received and immediately applied then, should be applied incremental messages in que,
        // but connection should not be closed - because not all items were updated
        OrderBookInfo<FastOBSFONDItemInfo> *item1 = fcf->OrderBookFond()->GetItem("symbol1", "session1");
        OrderBookInfo<FastOBSFONDItemInfo> *item2 = fcf->OrderBookFond()->GetItem("symbol2", "session1");
        if(item1->EntriesQueue()->HasEntries())
            throw;
        if(!item2->EntriesQueue()->HasEntries())
            throw;

        for(int i = 0; i < item1->BuyQuotes()->Count(); i++)
            if(item1->BuyQuotes()->Item(i)->Allocator == 0)
                throw;
        for(int i = 0; i < item2->BuyQuotes()->Count(); i++)
            if(item2->BuyQuotes()->Item(i)->Allocator == 0)
                throw;
    }

    int CalcMsgCount(const char *msg) {
        int len = strlen(msg);
        if(len == 0)
            return 0;
        int res = 0;
        for(int i = 0; i < len; i++) {
            if(msg[i] == ',')
                res++;
        }
        return res + 1;
    }

    int CalcWordLength(const char *msg, int startIndex) {
        int res = 0;
        for(int i = startIndex; msg[i] != ',' && msg[i] != '\0'; i++)
            res++;
        return res;
    }

    void TrimWord(const char *msg, int startIndex, int len, int *start, int *end) {
        *start = startIndex;
        *end = startIndex + len - 1;

        while(msg[*start] == ' ')
            (*start)++;
        while(msg[*end] == ' ')
            (*end)--;
        return ;
    }

    int SkipToNextWord(const char *msg, int start) {
        while(msg[start] == ' ')
            start++;
        return start;
    }

    char** Split(const char *msg, int start, int end, int *count) {
        char **keys = new char*[100];
        *count = 0;
        for(int i = start; i <= end; i++) {
            if(msg[i] == ' ' || i == end) {
                if(i == end) i++;
                keys[*count] = new char[i - start + 1];
                memcpy(keys[*count], &msg[start], i - start);
                keys[*count][i-start] = '\0';
                if(i == end)
                    break;
                (*count)++;
                start = SkipToNextWord(msg, i);
                i = start - 1;
            }
        }
        return keys;
    }

    int KeyIndex(char **keys, int keysCount, const char *key) {
        for(int i = 0; i < keysCount; i++) {
            if(StringIdComparer::Equal(keys[i], key))
                return i;
        }
        return -1;
    }

    int KeyIndex(char **keys, int keysCount, const char *key, int startIndex) {
        for(int i = startIndex; i < keysCount; i++) {
            if(StringIdComparer::Equal(keys[i], key))
                return i;
        }
        return -1;
    }

    bool HasKey(char **keys, int keysCount, const char *key) {
        return KeyIndex(keys, keysCount, key) != -1;
    }

    TestTemplateInfo *CreateTemplate(char **keys, int keysCount) {
        TestTemplateInfo *info = new TestTemplateInfo();

        info->m_lost = HasKey(keys, keysCount, "lost");
        info->m_skip = HasKey(keys, keysCount, "skip_if_suspend");
        if(HasKey(keys, keysCount, "obr")) {
            info->m_templateId = FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND;
        }
        else if(HasKey(keys, keysCount, "obs")) {
            info->m_templateId = FeedConnectionMessage::fmcFullRefresh_OBS_FOND;
            info->m_symbol = keys[KeyIndex(keys, keysCount, "obs") + 1];
            info->m_session = "session1";
            if(HasKey(keys, keysCount, "begin")) {
                info->m_routeFirst = true;
                //info->m_symbol = keys[KeyIndex(keys, keysCount, "rpt") + 2];
            }
            if(HasKey(keys, keysCount, "rpt")) {
                info->m_rptSec = atoi((const char *)(keys[KeyIndex(keys, keysCount, "rpt") + 1]));
            }
            if(HasKey(keys, keysCount, "lastmsg")) {
                info->m_lastMsgSeqNoProcessed = atoi((const char *)(keys[KeyIndex(keys, keysCount, "lastmsg") + 1]));
            }
            else info->m_lastMsgSeqNoProcessed = 1;
            if(HasKey(keys, keysCount, "end"))
                info->m_lastFragment = true;
        }
        else if(HasKey(keys, keysCount, "wait_snap")) {
            info->m_templateId = FeedConnectionMessage::fcmHeartBeat;
            info->m_wait = true;
            return info;
        }
        else if(HasKey(keys, keysCount, "hbeat")) {
            info->m_templateId = FeedConnectionMessage::fcmHeartBeat;
            return info;
        }

        int entryIndex = -1;
        int itemIndex = 0;
        while((entryIndex = KeyIndex(keys, keysCount, "entry", entryIndex + 1)) != -1) {
            TestTemplateItemInfo *item = new TestTemplateItemInfo();
            item->m_tradingSession = "session1";
            item->m_symbol = keys[entryIndex + 1];
            item->m_action = MDUpdateAction::mduaAdd;
            item->m_entryId = keys[entryIndex + 2];
            item->m_entryType = MDEntryType::mdetBuyQuote;
            item->m_entryPx.Set(1, 1);
            item->m_entrySize.Set(1, 1);
            info->m_items[itemIndex] = item;
            info->m_itemsCount++;

            itemIndex++;
        }

        return info;
    }

    void FillMsg(TestTemplateInfo **temp, int count, const char *msg) {
        int startIndex = 0;
        for(int i = 0; i < count; i++) {
            int len = CalcWordLength(msg, startIndex);
            int start = 0, end = 0;
            TrimWord(msg, startIndex, len, &start, &end);
            int keysCount = 0;
            char **keys = Split(msg, start, end, &keysCount);
            temp[i] = CreateTemplate(keys, keysCount);
            startIndex += len + 1;
        }
    }

    const char *symbols[100];
    int rptSeq[100];
    int symbolsCount = 0;

    int GetRptSeqFor(const char *symbol) {
        for(int i = 0; i < this->symbolsCount; i++) {
            if(StringIdComparer::Equal(this->symbols[i], symbol)) {
                rptSeq[i]++;
                return rptSeq[i];
            }
        }
        rptSeq[symbolsCount] = 1;
        symbols[symbolsCount] = symbol;
        symbolsCount++;
        return 1;
    }

    void FillRptSeq(TestTemplateInfo **msg, int count) {
        for(int i = 0; i < count; i++) {
            for(int j = 0; j < msg[i]->m_itemsCount; j++) {
                msg[i]->m_items[j]->m_rptSeq = GetRptSeqFor(msg[i]->m_items[j]->m_symbol);
            }
        }
    }

    void SendMessages(FeedConnection *fci, FeedConnection *fcs, const char *inc, const char *snap, int delay) {
        int incMsgCount = CalcMsgCount(inc);
        int snapMsgCount = CalcMsgCount(snap);

        TestTemplateInfo **inc_msg = new TestTemplateInfo*[incMsgCount];
        TestTemplateInfo **snap_msg = new TestTemplateInfo*[snapMsgCount];

        FillMsg(inc_msg, incMsgCount, inc);
        FillMsg(snap_msg, snapMsgCount, snap);
        FillRptSeq(inc_msg, incMsgCount);

        int inc_index = 0;
        int snap_index = 0;

        Stopwatch w;
        w.Start(1);
        while(inc_index < incMsgCount || snap_index < snapMsgCount) {
            if(inc_index < incMsgCount && !inc_msg[inc_index]->m_lost) {
                inc_msg[inc_index]->m_msgSeqNo = inc_index + 1;
                SendMessage(fci, inc_msg[inc_index]);
            }
            fci->Listen_Atom_Incremental_Core();
            if(inc_index < incMsgCount && inc_msg[inc_index]->m_wait) {
                if(!fcf->m_waitTimer->Active())
                    throw;
                while(!fci->m_waitTimer->IsElapsedMilliseconds(fci->WaitIncrementalMaxTimeMs()) && fcs->State() == FeedConnectionState::fcsSuspend)
                    fci->Listen_Atom_Incremental_Core();
                fci->Listen_Atom_Incremental_Core();
            }
            if(inc_index < incMsgCount)
                inc_index++;
            if(fcs->State() == FeedConnectionState::fcsListenSnapshot) {
                if (snap_index < snapMsgCount && !snap_msg[snap_index]->m_lost) {
                    snap_msg[snap_index]->m_msgSeqNo = snap_index + 1;
                    if(snap_msg[snap_index]->m_templateId != FeedConnectionMessage::fcmHeartBeat && (snap_msg[snap_index]->m_symbol == 0 || snap_msg[snap_index]->m_session == 0))
                        throw;
                    SendMessage(fcs, snap_msg[snap_index]);
                }
                if(snap_index < snapMsgCount)
                    snap_index++;
                fcs->Listen_Atom_Snapshot_Core();
            }
            else {
                if (snap_index < snapMsgCount && snap_msg[snap_index]->m_skip) {
                    snap_index++;
                }
            }
            w.Start();
            while(!w.IsElapsedMilliseconds(delay));
            w.Stop();
            if(w.ElapsedMilliseconds(1) > 5000)
                throw;
        }
        fci->Listen_Atom_Incremental_Core(); // emulate endless loop
        this->TestSnapshotPacketsCleared();
    }

    void TestConnection_SkipHearthBeatMessages_Incremental() {
        this->Clear();

        this->fcf->OrderBookFond()->Add("s1", "session1");
        this->fcf->StartListenSnapshot();
        if(fcs->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        SendMessages(fcf, fcs,
                     "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat, hbeat, hbeat",
                     "                                                  hbeat, hbeat, hbeat",
                     30);
        if(fcf->m_packets[4]->m_item == 0 || fcf->m_packets[5]->m_item == 0 || fcf->m_packets[6]->m_item == 0)
            throw;
        if(!fcf->m_packets[4]->m_processed || !fcf->m_packets[5]->m_processed || !fcf->m_packets[6]->m_processed)
            throw;
        // do not check Snapshot Feed Connection because it immediately cleares packets after processing,
        // because it can receive packet with the same message number again and again (cycle)
        //if(fcs->m_packets[1]->m_item == 0 || fcs->m_packets[2]->m_item == 0 || fcs->m_packets[3]->m_item == 0)
        //    throw;
        //if(!fcs->m_packets[1]->m_processed || !fcs->m_packets[2]->m_processed || !fcs->m_packets[3]->m_processed)
        //    throw;
    }

    void TestConnection_AllSymbolsAreOk() {
        this->Clear();

        SendMessages(fcf, fcs,
                     "obr entry symbol1 e1, obr entry symbol1 e2, obr entry symbol1 e3, obr entry symbol2 e1, obr entry symbol2 e2",
                     "",
                     30);
        if(fcf->m_orderBookTableFond->UsedItemCount() != 2)
            throw;
        if(fcf->m_orderBookTableFond->Symbol(0)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(fcf->m_orderBookTableFond->Symbol(1)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(fcf->OrderBookFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(!fcf->CanStopListeningSnapshot())
            throw;
    }

    void TestConnection_NotAllSymbolsAreOk() {
        this->Clear();

        SendMessages(fcf, fcs,
                     "obr entry symbol1 e1, lost obr entry symbol1 e2, obr entry symbol1 e3, obr entry symbol2 e1, obr entry symbol2 e2",
                     "",
                     30);
        if(fcf->m_orderBookTableFond->UsedItemCount() != 2)
            throw;
        if(!fcf->m_orderBookTableFond->Symbol(0)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(fcf->m_orderBookTableFond->Symbol(1)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(!fcf->ShouldStartSnapshot())
            throw;
        if(fcf->CanStopListeningSnapshot())
            throw;
    }

    void TestConnection_AllSymbolsAreOkButOneMessageLost() {
        this->Clear();

        SendMessages(fcf, fcs,
                     "obr entry symbol1 e1, lost obr entry symbol3 e2, obr entry symbol1 e3, obr entry symbol2 e1, obr entry symbol2 e2",
                     "",
                     30);

        if(fcf->m_orderBookTableFond->UsedItemCount() != 2)
            throw;
        if(fcf->m_orderBookTableFond->Symbol(0)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(fcf->m_orderBookTableFond->Symbol(1)->Session(0)->EntriesQueue()->HasEntries())
            throw;
        if(!fcf->ShouldStartSnapshot())
            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_1() {
        this->Clear();

        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(fcf, fcs,
                     "obr entry symbol1 e1, lost obr entry symbol3 e1",
                     "",
                     30);
        if(fcf->HasPotentiallyLostPackets())
            throw;
        if(fcf->ShouldStartSnapshot())
            throw;
        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_2() {
        this->Clear();

        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(fcf, fcs,
                     "obr entry symbol1 e1, lost obr entry symbol3 e1, hbeat",
                     "",
                     30);
        if(!fcf->HasPotentiallyLostPackets())
            throw;
        if(!fcf->ShouldStartSnapshot())
            throw;
        if(!fcf->m_waitTimer->Active())
            throw;
        if(fcf->m_waitTimer->IsElapsedMilliseconds(fcf->m_waitIncrementalMaxTimeMs))
            throw;
        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_2_1() {
        this->Clear();

        fcf->OrderBookFond()->Add("symbol1", "session1");
        fcf->OrderBookFond()->Add("symbol3", "session1");

        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(fcf, fcs,
                     "obr entry symbol1 e1, lost obr entry symbol3 e1, hbeat, hbeat",
                     "",
                     30);
        if(fcf->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(!fcf->HasPotentiallyLostPackets())
            throw;
        if(!fcf->ShouldStartSnapshot())
            throw;
        if(fcf->m_waitTimer->Active())
            throw;
        if(fcs->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(fcf->OrderBookFond()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(fcf->OrderBookFond()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(fcf->OrderBookFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // snapshot should not be stopped
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_3() {
        this->Clear();

        fcf->OrderBookFond()->Add("symbol1", "session1");
        fcf->OrderBookFond()->Add("symbol3", "session1");

        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(fcf, fcs,
                     "obr entry symbol1 e1, lost obr entry symbol3 e1, hbeat, hbeat, hbeat",
                     "",
                     30);
        if(fcf->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(!fcf->HasPotentiallyLostPackets())
            throw;
        if(!fcf->ShouldStartSnapshot())
            throw;
        if(fcf->m_waitTimer->Active())
            throw;
        if(fcs->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(fcf->OrderBookFond()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(fcf->OrderBookFond()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(fcf->OrderBookFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // exceeded connection time
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_3_1() {
        this->Clear();

        fcf->OrderBookFond()->Add("symbol1", "session1");
        fcf->OrderBookFond()->Add("symbol3", "session1");

        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(fcf, fcs,
                     "obr entry symbol1 e1, lost obr entry symbol3 e1, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat, hbeat",
                     "",
                     30);
        if(fcf->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(!fcf->HasPotentiallyLostPackets())
            throw;
        if(!fcf->ShouldStartSnapshot())
            throw;
        if(fcf->m_waitTimer->Active())
            throw;
        if(fcs->State() != FeedConnectionState::fcsConnect)
            throw;
        if(fcf->OrderBookFond()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(fcf->OrderBookFond()->Symbol(0)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(fcf->OrderBookFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }

    void TestConnection_ParallelWorkingIncrementalAndSnapshot_4() {
        this->Clear();

        fcf->OrderBookFond()->Add("symbol1", "session1");
        fcf->OrderBookFond()->Add("symbol3", "session1");

        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(fcf, fcs,
                     "obr entry symbol1 e1, lost obr entry symbol3 e1, wait_snap",
                     "",
                     30);
        if(fcf->m_waitTimer->Active())
            throw;
        if(fcf->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(fcs->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!fcf->ShouldStartSnapshot())
            throw;
        if(fcf->OrderBookFond()->SymbolsToRecvSnapshotCount() != 2)
            throw;
        if(fcf->OrderBookFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
        if(fcf->OrderBookFond()->Symbol(1)->SessionsToRecvSnapshotCount() != 1)
            throw;
    }
    // we should receive at least one snapshot for all items
    // we received snapshot for one item
    // and we did not receive incremental messages for symbol 2 after snapshot
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5() {
        this->Clear();

        fcf->OrderBookFond()->Add("symbol1", "session1");
        fcf->OrderBookFond()->Add("symbol2", "session1");
        fcf->OrderBookFond()->Add("symbol3", "session1");

        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(fcf, fcs,
                     "obr entry symbol1 e1, lost obr entry symbol3 e1, wait_snap, obr entry symbol1 e3,    hbeat,                              hbeat",
                     "                                                            obs symbol3 begin rpt 1, obs symbol3 rpt 1 entry symbol3 e1, obs symbol3 rpt 1 end",
                     30);
        if(fcf->HasQueueEntries())
            throw;
        if(fcf->CanStopListeningSnapshot()) // because we did not receive all snapshots for all symbols
            throw;
        if(fcs->State() == FeedConnectionState::fcsSuspend)
            throw;
        if(fcf->m_orderBookTableFond->UsedItemCount() != 3)
            throw;
        if(fcf->m_orderBookTableFond->GetItem("symbol1", "session1")->BuyQuotes()->Count() != 2)
            throw;
        if(fcf->m_orderBookTableFond->GetItem("symbol2", "session1")->BuyQuotes()->Count() != 0)
            throw;
        if(fcf->m_orderBookTableFond->GetItem("symbol3", "session1")->BuyQuotes()->Count() != 1)
            throw;
        if(fcf->m_startMsgSeqNum != 2)
            throw;
        if(fcf->m_endMsgSeqNum != 6)
            throw;
        if(fcs->m_startMsgSeqNum != 4)
            throw;
        if(fcs->m_endMsgSeqNum != 3)
            throw;
    }
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_1() {
        this->Clear();

        fcf->OrderBookFond()->Add("symbol1", "session1");

        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;
        SendMessages(fcf, fcs,
                     "lost obr entry symbol1 e1, lost hbeat, wait_snap",
                     "obs symbol1 begin rpt 1, obs symbol1 rpt 1 entry symbol1 e1, obs symbol1 rpt 1 end",
                     30);
        if(fcf->HasQueueEntries())
            throw;
        if(fcf->OrderBookFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(fcf->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(!fcf->CanStopListeningSnapshot())
            throw;
        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(fcf->m_orderBookTableFond->UsedItemCount() != 1)
            throw;
        if(fcf->m_orderBookTableFond->GetItem("symbol1", "session1")->BuyQuotes()->Count() != 1)
            throw;
        if(fcf->m_startMsgSeqNum != 4)
            throw;
        if(fcf->m_endMsgSeqNum != 3)
            throw;
        if(fcs->m_startMsgSeqNum != 4)
            throw;
        if(fcs->m_endMsgSeqNum != 3)
            throw;
    }
    // snapshot completed because we received snapshot for all items
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2() {
        this->Clear();

        fcf->OrderBookFond()->Add("symbol1", "session1");
        fcf->OrderBookFond()->Add("symbol2", "session1");
        fcf->OrderBookFond()->Add("symbol3", "session1");

        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(fcf->OrderBookFond()->UsedItemCount() != 3)
            throw;
        SendMessages(fcf, fcs,
                     "obr entry symbol1 e1, lost obr entry symbol3 e1, wait_snap, obr entry symbol1 e3,                         hbeat,                                        hbeat",
                     "                                                            obs symbol3 begin rpt 1 end entry symbol3 e1, obs symbol1 begin rpt 2 end entry symbol1 e1, hbeat, obs symbol2 begin rpt 2 end entry symbol2 e1",
                     30);
        if(fcf->HasQueueEntries())
            throw;
        if(fcf->m_orderBookTableFond->GetItem("symbol1", "session1")->RptSeq() != 2)
            throw;
        if(fcf->m_orderBookTableFond->GetItem("symbol3", "session1")->RptSeq() != 1)
            throw;
        if(fcf->m_orderBookTableFond->GetItem("symbol2", "session1")->RptSeq() != 2)
            throw;
        if(!fcf->CanStopListeningSnapshot())
            throw;
        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(fcf->m_orderBookTableFond->UsedItemCount() != 3)
            throw;
        if(fcf->m_orderBookTableFond->GetItem("symbol1", "session1")->BuyQuotes()->Count() != 2) // snapshot applied virtually actually skipped
            throw;
        if(fcf->m_orderBookTableFond->GetItem("symbol2", "session1")->BuyQuotes()->Count() != 1)
            throw;
        if(fcf->m_orderBookTableFond->GetItem("symbol3", "session1")->BuyQuotes()->Count() != 1)
            throw;
        if(fcf->m_startMsgSeqNum != 7)
            throw;
        if(fcf->m_endMsgSeqNum != 6)
            throw;
        if(fcs->m_startMsgSeqNum != 5)
            throw;
        if(fcs->m_endMsgSeqNum != 4)
            throw;
    }
    // snapshot completed because we received snapshot for all items
    // almost the same as TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2
    // however there is no heartbeat msg in snap channel so symbol 2 receives snapshot earlier than his second message so it buyquotes count == 1
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2_2() {
        this->Clear();

        fcf->OrderBookFond()->Add("symbol1", "session1");
        fcf->OrderBookFond()->Add("symbol2", "session1");
        fcf->OrderBookFond()->Add("symbol3", "session1");

        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(fcf->OrderBookFond()->UsedItemCount() != 3)
            throw;
        SendMessages(fcf, fcs,
                     "obr entry symbol1 e1, lost obr entry symbol3 e1, wait_snap, obr entry symbol1 e3,                         obr entry symbol2 e1,                         obr entry symbol2 e2",
                     "                                                            obs symbol3 begin rpt 1 end entry symbol3 e1, obs symbol1 begin rpt 2 end entry symbol1 e1, obs symbol2 begin rpt 2 end entry symbol2 e1 skip_if_suspend",
                     30);
        if(fcf->HasQueueEntries())
            throw;
        if(fcf->m_orderBookTableFond->GetItem("symbol1", "session1")->RptSeq() != 2)
            throw;
        if(fcf->m_orderBookTableFond->GetItem("symbol3", "session1")->RptSeq() != 1)
            throw;
        if(fcf->m_orderBookTableFond->GetItem("symbol2", "session1")->RptSeq() != 2)
            throw;
        if(!fcf->CanStopListeningSnapshot())
            throw;
        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(fcf->m_orderBookTableFond->UsedItemCount() != 3)
            throw;
        if(fcf->m_orderBookTableFond->GetItem("symbol1", "session1")->BuyQuotes()->Count() != 2) // snapshot applied virtually actually skipped
            throw;
        if(fcf->m_orderBookTableFond->GetItem("symbol2", "session1")->BuyQuotes()->Count() != 2)
            throw;
        if(fcf->m_orderBookTableFond->GetItem("symbol3", "session1")->BuyQuotes()->Count() != 1)
            throw;
        if(fcf->m_startMsgSeqNum != 7)
            throw;
        if(fcf->m_endMsgSeqNum != 6)
            throw;
        if(fcs->m_startMsgSeqNum != 3)
            throw;
        if(fcs->m_endMsgSeqNum != 2)
            throw;
    }
    // we receive snapshot which rpt seq is less than incremental actual rpt seq
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_3() {
        this->Clear();

        fcf->OrderBookFond()->Add("s1", "session1");

        fcf->Start();
        if(!fcf->m_waitTimer->Active())
            throw;
        SendMessages(fcf, fcs,
                     "obr entry s1 e1, obr entry s1 e2, obr entry s1 e3, lost hbeat, wait_snap, hbeat",
                     "                                                                          obs s1 begin rpt 1 entry s1 e1 end",
                     50);
        if(fcf->HasQueueEntries())
            throw;
        if(fcf->OrderBookFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(fcf->CanStopListeningSnapshot())
            throw;
        if(fcf->OrderBookFond()->GetItem("s1", "session1")->RptSeq() != 3)
            throw;
        if(fcf->OrderBookFond()->GetItem("s1", "session1")->BuyQuotes()->Count() != 3)
            throw;
        if(fcs->m_startMsgSeqNum != 2)
            throw;
        if(fcs->m_endMsgSeqNum != 1)
            throw;
        if(fcs->State() == FeedConnectionState::fcsSuspend)
            throw;
        if(fcs->m_startMsgSeqNum != 2) // detect that
            throw;
    }
    // we received snapshot for item but item has 2 gaps and snapshot is partially actual
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4() {
        this->Clear();

        fcf->WaitIncrementalMaxTimeMs(500);
        fcf->OrderBookFond()->Add("s1", "session1");
        fcf->Start();

        SendMessages(fcf, fcs,
                     "obr entry s1 e1, obr entry s1 e2, lost obr entry s1 e3, obr entry s1 e4, lost obr entry s1 e5, obr entry s1 e6, wait_snap, ",
                     "                                                                                                                           obs s1 begin rpt 4 entry s1 e4 end",
        30);
        if(fcf->OrderBookFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(fcf->CanStopListeningSnapshot())
            throw;
        if(fcs->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(!fcf->OrderBookFond()->GetItem("s1", "session1")->QueueEntries()->HasEntries())
            throw;
        if(fcf->OrderBookFond()->GetItem("s1", "session1")->RptSeq() != 4)
            throw;
        if(fcf->OrderBookFond()->GetItem("s1", "session1")->BuyQuotes()->Count() != 1)
            throw;
    }
    // almost the same as 5_4 but we received new snapshot for item but item has 2 gaps and snapshot is fully actual
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_1() {
        this->Clear();

        fcf->WaitIncrementalMaxTimeMs(500);
        fcf->OrderBookFond()->Add("s1", "session1");
        fcf->Start();

        SendMessages(fcf, fcs,
                     "obr entry s1 e1, obr entry s1 e2, lost obr entry s1 e3, obr entry s1 e4, lost obr entry s1 e5, obr entry s1 e6, wait_snap, ",
                     "                                                                                                                           obs s1 begin rpt 5 entry s1 e5 end",
                     30);
        if(fcf->OrderBookFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(fcf->HasQueueEntries())
            throw;
        if(!fcf->CanStopListeningSnapshot())
            throw;
        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(fcf->OrderBookFond()->GetItem("s1", "session1")->QueueEntries()->HasEntries())
            throw;
        if(fcf->OrderBookFond()->GetItem("s1", "session1")->RptSeq() != 6)
            throw;
        if(fcf->OrderBookFond()->GetItem("s1", "session1")->BuyQuotes()->Count() != 2)
            throw;
    }
    // almost the same as 5_4_1 but we received new snapshot with rptseq 6
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_2() {
        this->Clear();

        fcf->WaitIncrementalMaxTimeMs(500);
        fcf->OrderBookFond()->Add("s1", "session1");
        fcf->Start();

        SendMessages(fcf, fcs,
                     "obr entry s1 e1, obr entry s1 e2, lost obr entry s1 e3, obr entry s1 e4, lost obr entry s1 e5, obr entry s1 e6, wait_snap, ",
                     "                                                                                                                           obs s1 begin rpt 6 entry s1 e6 end",
                     30);
        if(fcf->OrderBookFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(fcf->HasQueueEntries())
            throw;
        if(!fcf->CanStopListeningSnapshot())
            throw;
        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(fcf->OrderBookFond()->GetItem("s1", "session1")->QueueEntries()->HasEntries())
            throw;
        if(fcf->OrderBookFond()->GetItem("s1", "session1")->RptSeq() != 6)
            throw;
        if(fcf->OrderBookFond()->GetItem("s1", "session1")->BuyQuotes()->Count() != 1)
            throw;
    }
    // we have received snapshot and almost ok but next incremental message during snapshot has greater RptSeq
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5() {
        this->Clear();

        fcf->WaitIncrementalMaxTimeMs(500);
        fcf->OrderBookFond()->Add("s1", "session1");
        fcf->OrderBookFond()->Add("s2", "session1");
        fcf->Start();

        SendMessages(fcf, fcs,
                     "obr entry s1 e1, obr entry s2 e1, lost obr entry s1 e2, wait_snap, hbeat                               lost obr entry s1 e3,               obr entry s1 e4",
                     "                                                                   obs s1 begin rpt 2 entry s1 e2 end, obs s2 begin rpt 1 entry s2 e1 end, hbeat",
                     30);
        if(fcf->CanStopListeningSnapshot())
            throw;
        if(fcs->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(fcf->OrderBookFond()->GetItem("s1", "session1")->RptSeq() != 2)
            throw;
        if(!fcf->OrderBookFond()->GetItem("s1", "session1")->QueueEntries()->HasEntries())
            throw;
        if(fcf->OrderBookFond()->GetItem("s1", "session1")->QueueEntries()->StartRptSeq() != 3)
            throw;
        if(fcf->OrderBookFond()->GetItem("s1", "session1")->QueueEntries()->MaxIndex() != 1)
            throw;
        if(fcf->OrderBookFond()->GetItem("s2", "session1")->RptSeq() != 1)
            throw;
        if(fcf->OrderBookFond()->QueueEntriesCount() != 1)
            throw;
    }
    // we have received snapshot and almost ok but next incremental message during snapshot has greater RptSeq
    // and we receive second time snapshot for s1
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5_1() {
        this->Clear();

        fcf->OrderBookFond()->Add("s1", "session1");
        fcf->OrderBookFond()->Add("s2", "session1");
        fcf->Start();

        SendMessages(fcf, fcs,
                     "obr entry s1 e1, obr entry s2 e1, lost obr entry s1 e2, wait_snap, hbeat                               lost obr entry s1 e3,               obr entry s1 e4, hbeat ",
                     "                                                                   obs s1 begin rpt 2 entry s1 e2 end, obs s2 begin rpt 1 entry s2 e1 end, hbeat          , obs s1 begin rpt 3 entry s1 e3 end",
                     30);
        if(!fcf->CanStopListeningSnapshot())
            throw;
        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(fcf->OrderBookFond()->GetItem("s1", "session1")->RptSeq() != 4)
            throw;
        if(fcf->OrderBookFond()->GetItem("s1", "session1")->QueueEntries()->HasEntries())
            throw;
        if(fcf->OrderBookFond()->QueueEntriesCount() != 0)
            throw;
        if(fcf->OrderBookFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
    }
    // we have received incremental message after entering snapshot mode for item and item in is actual state - so it do not need snapshot
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_6() {
        this->Clear();

        fcf->OrderBookFond()->Add("s1", "session1");
        fcf->OrderBookFond()->Add("s2", "session1");
        fcf->Start();

        SendMessages(fcf, fcs,
                     "obr entry s1 e1, obr entry s2 e1, lost obr entry s1 e2, wait_snap, obr entry s2 e2, hbeat",
                     "                                                        hbeat,     hbeat,           hbeat",
                     30);
        if(fcf->CanStopListeningSnapshot())
            throw;
        if(fcs->State() != FeedConnectionState::fcsListenSnapshot)
            throw;
        if(fcf->OrderBookFond()->SymbolsToRecvSnapshotCount() != 1)
            throw;
        if(fcf->OrderBookFond()->GetItem("s2", "session1")->ShouldProcessSnapshot())
            throw;
    }
    // we have received twice the same snapshot (rpt seq num = the same value) which means that item did not receive incremental message so item state is actual
    void TestConnection_ParallelWorkingIncrementalAndSnapshot_5_7() {
        // do nothing. lets consider that after receiving snapshot item will be in actual state if there is no queue entries
    }
    // we can receive null snapshot i.e. snapshot with LastMsgSeqNumProcessed = 0 RptSeq = 0
    // this means that item has NO DATA
    // so just clear queue entries and decrease session to recv snapshot value
    void TestConnection_ResetEntriesQueueIfNullSnapshotIsReceived() {
        this->Clear();

        /*
        unsigned char *msg = new unsigned char[52] {
                0x65, 0x23, 0x00, 0x00, 0xe0, 0x12, 0xec, 0x46, 0xe5, 0x23,
                0x68, 0x08, 0x12, 0x7f, 0x4c, 0x74, 0xc0, 0x81, 0x80, 0x00,
                0xe5, 0x52, 0x50, 0x4d, 0xcf, 0x52, 0x55, 0x30, 0x30, 0x30,
                0x41, 0x30, 0x4a, 0x54, 0x5a, 0x46, 0xb1, 0x82, 0x82, 0x93,
                0x80, 0x81, 0xca, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
                0x80, 0x80
        };
        fcf->m_fastProtocolManager->SetNewBuffer(msg, 52);
        fcf->m_fastProtocolManager->ReadMsgSeqNumber();
        fcf->m_fastProtocolManager->Decode();
        fcf->m_fastProtocolManager->Print();
        */

        fcf->OrderBookFond()->Add("s1", "session1");
        fcf->Start();

        SendMessages(fcf, fcs,
                     "obr entry s1 e1, lost obr entry s1 e2, obr entry s1 e2, wait_snap, hbeat",
                     "                                       hbeat,           hbeat,     obs s1 begin rpt 0 lastmsg 0 entry s1 e1 end",
                     30);
        if(fcf->OrderBookFond()->SymbolsToRecvSnapshotCount() != 0)
            throw;
        if(!fcf->CanStopListeningSnapshot())
            throw;
        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;
    }
    void TestConnection_StopListeningSnapshotBecauseAllItemsIsUpToDate() {

    }
    void TestConnection_EnterSnapshotMode() {
        this->Clear();

        fcf->OrderBookFond()->Add("s1", "session1");
        fcf->OrderBookFond()->EnterSnapshotMode();
        if(!fcf->OrderBookFond()->GetItem("s1", "session1")->ShouldProcessSnapshot())
            throw;
    }
    // clear after apply snapshot
    void TestConnection_ClearSnapshotMessages_1() {
        this->Clear();

        fcf->OrderBookFond()->Add("s1", "session1");
        SendMessages(fcf, fcs,
                     "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat",
                     "                                                  obs s1 begin rpt 2 entry s1 e2 end",
                     30);
        if(fcs->m_packets[1]->m_item != 0)
            throw;
        if(fcs->m_packets[1]->m_processed != false)
            throw;
    }
    // clear unitl not found route first
    void TestConnection_ClearSnapshotMessages_2() {
        this->Clear();

        fcf->OrderBookFond()->Add("s1", "session1");
        SendMessages(fcf, fcs,
                     "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat",
                     "                                                  hbeat, hbeat, obs s1 begin rpt 2 entry s1 e2 end",
                     30);
        if(fcs->m_packets[1]->m_item != 0 ||
                fcs->m_packets[2]->m_item != 0 ||
                fcs->m_packets[3]->m_item != 0)
            throw;
        if(fcs->m_packets[1]->m_processed != false ||
           fcs->m_packets[2]->m_processed != false ||
           fcs->m_packets[3]->m_processed != false)
            throw;
    }
    // clear if skip lost packets in snapshot
    void TestConnection_ClearSnapshotMessages_3() {
        this->Clear();

        fcf->OrderBookFond()->Add("s1", "session1");
        fcs->WaitSnapshotMaxTimeMs(50);
        SendMessages(fcf, fcs,
                     "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat",
                     "                                                  obs s1 begin rpt 2 entry s1 e2, lost obs s1 rpt 2 entry s1 e2, hbeat, hbeat, hbeat, hbeat, hbeat",
                     30);
        for(int i = 1; i < 100; i++) {
            if(fcs->m_packets[i]->m_item != 0 || fcs->m_packets[i]->m_processed != false)
                throw;
        }
    }
    // clear if skip lost packets in snapshot and apply snapshot
    void TestConnection_ClearSnapshotMessages_4() {
        this->Clear();

        fcf->OrderBookFond()->Add("s1", "session1");
        fcs->WaitSnapshotMaxTimeMs(50);
        SendMessages(fcf, fcs,
                     "obr entry s1 e1, lost obr entry s1 e2, wait_snap, hbeat                           hbeat,                         hbeat, hbeat, hbeat, hbeat, hbeat,                           hbeat",
                     "                                                  obs s1 begin rpt 2 entry s1 e2, lost obs s1 rpt 2 entry s1 e2, hbeat, hbeat, hbeat, hbeat, hbeat, obs s1 rpt 2 entry s1 e2, obs s1 begin rpt 2 entry s1 e2 end",
                     30);
        if(fcf->OrderBookFond()->UsedItemCount() != 1)
            throw;
        if(fcs->State() != FeedConnectionState::fcsSuspend)
            throw;
        if(!fcf->CanStopListeningSnapshot())
            throw;
        TestSnapshotPacketsCleared();
    }
    void TestSnapshotPacketsCleared() {
        for(int i = 1; i < 100; i++) {
            if(fcs->m_packets[i]->m_item != 0 || fcs->m_packets[i]->m_processed != false)
                throw;
        }
    }
    // messages should be clear in snapshot connection because the are repeat
    void TestConnection_ClearSnapshotMessages() {
        printf("TestConnection_ClearSnapshotMessages_1\n");
        TestConnection_ClearSnapshotMessages_1();
        printf("TestConnection_ClearSnapshotMessages_2\n");
        TestConnection_ClearSnapshotMessages_2();
        printf("TestConnection_ClearSnapshotMessages_3\n");
        TestConnection_ClearSnapshotMessages_3();
        printf("TestConnection_ClearSnapshotMessages_4\n");
        TestConnection_ClearSnapshotMessages_4();
    }
    void TestConnection_ParallelWorkingIncrementalAndSnapshot() {
        printf("TestConnection_EnterSnapshotMode\n");
        TestConnection_EnterSnapshotMode();
        printf("TestConnection_ClearSnapshotMessages\n");
        TestConnection_ClearSnapshotMessages();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_1();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_2();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_2_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_2_1();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_3\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_3();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_3_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_3_1();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_4\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_4();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_1();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_2_2();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5_3\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_3();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_1();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_2\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_4_2();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5_1\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_5_1();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5_6\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_6();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot_5_7\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot_5_7();
    }

    void TestConnection_Clear_AfterIncremental() {
        this->TestTableItemsAllocator(fcf->OrderBookFond());
        this->Clear();
        fcf->StartListenSnapshot();

        this->TestTableItemsAllocator(fcf->OrderBookFond());

        SendMessages(fcf, new TestTemplateInfo*[4] {
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 1,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", "entry1", 1),
                                             new TestTemplateItemInfo("symbol2", "entry1", 1),
                                     }, 2),
                new TestTemplateInfo(FeedConnectionMessage::fmcIncrementalRefresh_OBR_FOND, 3,
                                     new TestTemplateItemInfo*[2] {
                                             new TestTemplateItemInfo("symbol1", "entry1", 4),
                                             new TestTemplateItemInfo("symbol2", "entry1", 4),
                                     }, 2)
        }, 2);

        if(!fcf->Listen_Atom_Incremental_Core())
            throw;

        this->TestTableItemsAllocator(fcf->OrderBookFond());

        fcf->OrderBookFond()->Clear();
    }

    void TestConnection() {
        printf("TestConnection_AllSymbolsAreOk\n");
        TestConnection_AllSymbolsAreOk();
        printf("TestConnection_ResetEntriesQueueIfNullSnapshotIsReceived\n");
        TestConnection_ResetEntriesQueueIfNullSnapshotIsReceived();
        printf("TestConnection_AllSymbolsAreOkButOneMessageLost\n");
        TestConnection_AllSymbolsAreOkButOneMessageLost();
        printf("TestConnection_SkipHearthBeatMessages_Incremental\n");
        TestConnection_SkipHearthBeatMessages_Incremental();
        printf("TestConnection_ParallelWorkingIncrementalAndSnapshot\n");
        TestConnection_ParallelWorkingIncrementalAndSnapshot();
        printf("TestConnection_NotAllSymbolsAreOk\n");
        TestConnection_NotAllSymbolsAreOk();
        printf("TestConnection_StopListeningSnapshotBecauseAllItemsIsUpToDate\n");
        TestConnection_StopListeningSnapshotBecauseAllItemsIsUpToDate();
        printf("TestConnection_StopTimersAfterReconnect\n");
        TestConnection_StopTimersAfterReconnect();
        printf("TestConnection_SnapshotSomeMessagesReceivedLater\n");
        TestConnection_SnapshotSomeMessagesReceivedLater();
        printf("TestConnection_SnapshotSomeMessagesNotReceived\n");
        TestConnection_SnapshotSomeMessagesNotReceived();
        printf("TestConnection_LastFragmentReceivedBeforeRouteFirst\n");
        TestConnection_LastFragmentReceivedBeforeRouteFirst();
        printf("TestConnection_RouteFirstReceived_AfterSomeDummyMessages\n");
        TestConnection_RouteFirstReceived_AfterSomeDummyMessages();
        printf("TestConnection_RouteFirstReceived_Empty\n");
        TestConnection_RouteFirstReceived_Empty();
        printf("TestConnection_TestSnapshotNoMessagesAtAll\n");
        TestConnection_TestSnapshotNoMessagesAtAll();
        printf("TestConnection_OneMessageReceived\n");
        TestConnection_OneMessageReceived();
        printf("TestConnection_Clear_AfterIncremental\n");
        TestConnection_Clear_AfterIncremental();
        printf("TestConnection_TestIncMessageLost_AndWaitTimerElapsed\n");
        TestConnection_TestIncMessageLost_AndWaitTimerElapsed();
        printf("TestConnection_TestSnapshotCollect\n");
        TestConnection_TestSnapshotCollect();
        printf("TestConnection_TestSnapshotNotCollect\n");
        TestConnection_TestSnapshotMessageLostAndTimeExpired();
        printf("TestConnection_TestMessagesLost_2Items_SnapshotReceivedForOneItem\n");
        TestConnection_TestMessagesLost_2Items_SnapshotReceivedForOneItem();

        printf("TestConnection_EmptyTest\n");
        TestConnection_EmptyTest();
        printf("TestConnection_TestCorrectIncMessages\n");
        TestConnection_TestCorrectIncMessages();
        printf("TestConnection_TestIncMessagesLost_AndWhenAppeared\n");
        TestConnection_TestIncMessagesLost_AndWhenAppeared();
        printf("TestConnection_TestInc2MessagesLost_AppearedThen2Messages\n");
        TestConnection_TestInc2MessagesLost_AppearedThen2Messages();
        printf("TestConnection_TestInc2MessagesLost_AppearedSeparately_1_2\n");
        TestConnection_TestInc2MessagesLost_AppearedSeparately_1_2();
        printf("TestConnection_TestInc2MessagesLost_AppearedSeparately_2_1\n");
        TestConnection_TestInc2MessagesLost_AppearedSeparately_2_1();
    }

    void TestOrderBookTableItem() {
        printf("TestTableItem_CorrectBegin\n");
        TestTableItem_CorrectBegin();
        printf("TestTableItem_IncorrectBegin\n");
        TestTableItem_IncorrectBegin();
        printf("TestTableItem_SkipMessage\n");
        TestTableItem_SkipMessage();
        printf("TestTable_Default\n");
        TestTable_Default();
        printf("TestTable_AfterClear\n");
        TestTable_AfterClear();
        printf("TestTable_CorrectBegin\n");
        TestTable_CorrectBegin();
        printf("TestTable_IncorrectBegin\n");
        TestTable_IncorrectBegin();
        printf("TestTable_SkipMessages\n");
        TestTable_SkipMessages();
        printf("Test_2UsedItemsAfter2IncrementalMessages\n");
        Test_2UsedItemsAfter2IncrementalMessages();
        printf("TestTable_CorrectApplySnapshot\n");
        TestTable_CorrectApplySnapshot();
        printf("TestTable_CorrectApplySnapshot_2\n");
        TestTable_CorrectApplySnapshot_2();
        printf("TestTable_IncorrectApplySnapshot\n");
        TestTable_IncorrectApplySnapshot();
        printf("TestTable_IncorrectApplySnapshot_WhenMessageSkipped\n");
        TestTable_IncorrectApplySnapshot_WhenMessageSkipped();
    }

    void TestStringIdComparer() {
        char buf[128];
        for(int i = 1; i < 128; i++) {
            buf[i] = (char)(0x30 + i);
        }
        for(int i = 1; i < 128; i++) {
            if(!StringIdComparer::Equal(buf, i, buf, i))
                throw;
        }
    }

    void Test() {
        TestDefaults();
        TestStringIdComparer();
        TestConnection();
        TestOrderBookTableItem();
        Test_OBR_FOND();
        Test_OBR_CURR();
    }
};

#endif //HFT_ROBOT_FEEDCONNECTIONTEST_H
