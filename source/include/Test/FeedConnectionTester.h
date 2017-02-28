//
// Created by root on 26.10.16.
//

#ifndef HFT_ROBOT_FEEDCONNECTIONTESTER_H
#define HFT_ROBOT_FEEDCONNECTIONTESTER_H
#include "Settings.h"

#ifdef TEST

#include "Feeds/FeedConnections.h"
#include "SecurityDefinitionTester.h"
#include "OrderTesterFond.h"
#include "OrderTesterCurr.h"
#include "TradeTesterFond.h"
#include "TradeTesterCurr.h"
#include "StatisticsTesterFond.h"
#include "StatisticsTesterCurr.h"
#include "SymbolManagerTester.h"
#include "PointerListTester.h"
#include "SecurityStatusTester.h"
#include "HistoricalReplayTester.h"

class TestFeedMessage{
public:
    AutoAllocatePointerList<TestFeedMessage>    *Allocator;
    LinkedPointer<TestFeedMessage>              *Pointer;
    bool                                        Used;
    char                                        Type[10];
    int                                         TemplateId;
    int                                         Count;

    unsigned char                               Bytes[1700];
    char                                        Text[1700];
};

class FeedConnectionTester {

    TestMessagesHelper      *m_helper;
    FeedConnection_CURR_OLR *inc;
    FeedConnection_CURR_OLS *snap;

    bool ReadNextQuote(FILE *fp) {
        while(!feof(fp)) {
            int chr = fgetc(fp);
            if(chr == '\'')
                return true;
        }
        return false;
    }
    const char* IsFeedName(const char *feed_abr) {
        static const char* feeds[7] {
                "OBR",
                "OBS",
                "TLR",
                "TLS",
                "OLS",
                "OLR",
                "IDF"
        };

        for(int i = 0; i < 7; i++) {
            if(feeds[i][0] == feed_abr[0] && feeds[i][1] == feed_abr[1] && feeds[i][2] == feed_abr[2] && feed_abr[3] == '\'')
                return feeds[i];
        }
        return 0;
    }
    int AsciToValue(char ascii) {
        char asci_table[16] { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

        for(int i = 0; i < 16; i++) {
            if(ascii == asci_table[i])
                return i;
        }
        return 0;
    }
public:
    FeedConnectionTester() {
        RobotSettings::Default->DefaultFeedConnectionSendBufferSize = 1 * 1024 * 1024;
        RobotSettings::Default->DefaultFeedConnectionSendItemsCount = 100;
        RobotSettings::Default->DefaultFeedConnectionRecvBufferSize = 2 * 1024 * 1024;
        RobotSettings::Default->DefaultFeedConnectionRecvItemsCount = 500;

        this->m_helper = new TestMessagesHelper();
        this->m_helper->SetCurrMode();
        this->inc = new FeedConnection_CURR_OLR("OLR", "Refresh Incremental", 'I',
                                                    FeedConnectionProtocol::UDP_IP,
                                                    "10.50.129.200", "239.192.113.3", 9113,
                                                    "10.50.129.200", "239.192.113.131", 9313);
        this->snap = new FeedConnection_CURR_OLS("OLS", "Full Refresh", 'I',
                                                     FeedConnectionProtocol::UDP_IP,
                                                     "10.50.129.200", "239.192.113.3", 9113,
                                                     "10.50.129.200", "239.192.113.131", 9313);

        this->inc->OrderCurr()->InitSymbols(10, 10);
        this->inc->SetSnapshot(this->snap);
    }

    void TestDefaults() {
        if(this->inc->m_windowMsgSeqNum != 0)
            throw;
    }

    void TestPacketsCleared(int start, int end) {
        for(int i = start; i <= end; i++) {
            if(!this->inc->m_packets[i]->IsCleared())
                throw;
        }
    }

    void TestWindowStartMsgSeqNo_CorrectIncremental() {
        TestTemplateInfo *info = new TestTemplateInfo();
        TestTemplateItemInfo *item = new TestTemplateItemInfo();

        info->m_templateId = FeedConnectionMessage::fmcIncrementalRefresh_OLR_CURR;
        info->m_itemsCount = 1;
        info->m_items[0] = item;

        item->m_symbol = "symbol1";
        item->m_tradingSession = "session1";
        item->m_entryId = "entry1";
        item->m_action = MDUpdateAction::mduaAdd;
        item->m_entryType = MDEntryType::mdetBuyQuote;

        for(int i = 0; i < 2000; i++) {
            item->m_rptSeq = i + 1;
            info->m_msgSeqNo = i + 1;

            this->m_helper->SendMessage(this->inc, info);
            this->inc->Listen_Atom_Incremental_Core();
        }
        if(this->inc->OrderCurr()->Symbol(0)->Session(0)->BuyQuotes()->Count() != 2000)
            throw;
        if(this->inc->m_startMsgSeqNum != 2000 + 1)
            throw;
        if(this->inc->m_endMsgSeqNum != 2000)
            throw;
        if(this->inc->m_windowMsgSeqNum != this->inc->m_startMsgSeqNum)
            throw;
        TestPacketsCleared(0, 2000);
    }

    void TestWindowStartMsgSeqNo_MessageLost() {
        this->inc->ClearMessages();
        this->inc->OrderCurr()->Clear();

        TestTemplateInfo *info = new TestTemplateInfo();
        TestTemplateItemInfo *item = new TestTemplateItemInfo();

        info->m_templateId = FeedConnectionMessage::fmcIncrementalRefresh_OLR_CURR;
        info->m_itemsCount = 1;
        info->m_items[0] = item;

        item->m_symbol = "symbol1";
        item->m_tradingSession = "session1";
        item->m_entryId = "entry1";
        item->m_action = MDUpdateAction::mduaAdd;
        item->m_entryType = MDEntryType::mdetBuyQuote;

        for(int i = 0; i < 10; i++) {
            item->m_rptSeq = i + 1;
            info->m_msgSeqNo = i + 1;

            this->m_helper->SendMessage(this->inc, info);
            this->inc->Listen_Atom_Incremental_Core();
        }
        TestPacketsCleared(0, 10);
        for(int i = 11; i < 20; i++) {
            item->m_rptSeq = i + 1;
            info->m_msgSeqNo = i + 1;

            this->m_helper->SendMessage(this->inc, info);
            this->inc->Listen_Atom_Incremental_Core();
        }

        if(this->inc->OrderCurr()->Symbol(0)->Session(0)->BuyQuotes()->Count() != 10)
            throw;
        if(this->inc->m_startMsgSeqNum != 10 + 1)
            throw;
        if(this->inc->m_endMsgSeqNum != 20)
            throw;
        if(this->inc->m_windowMsgSeqNum != this->inc->m_startMsgSeqNum)
            throw;
        for(int i = 12; i < 20; i++)
            if(inc->m_packets[i - 11]->IsCleared())
                throw;

        item->m_rptSeq = 11; // lost message
        info->m_msgSeqNo = 11;

        this->m_helper->SendMessage(this->inc, info);
        this->inc->Listen_Atom_Incremental_Core();

        TestPacketsCleared(0, 10);
        if(this->inc->m_startMsgSeqNum != 20 + 1)
            throw;
        if(this->inc->m_endMsgSeqNum != 20)
            throw;
        if(this->inc->m_windowMsgSeqNum != this->inc->m_startMsgSeqNum)
            throw;
    }

    void TestFeedConnectionBase() {
        TestDefaults();
        TestWindowStartMsgSeqNo_CorrectIncremental();
        TestWindowStartMsgSeqNo_MessageLost();
    }

    void Test() {
        RobotSettings::Default->MarketDataMaxSymbolsCount = 10;
        RobotSettings::Default->MarketDataMaxSessionsCount = 32;
        RobotSettings::Default->MarketDataMaxEntriesCount = 32 * 10;
        RobotSettings::Default->DefaultFeedConnectionPacketCount = 1100;
        RobotSettings::Default->MDEntryQueueItemsCount = 100;

        TestFeedConnectionBase();

        PointerListTester pt;
        pt.Test();

        SymbolManagerTester ht;
        ht.Test();

        TradeTesterCurr ttCurr;
        ttCurr.Test();
        TradeTesterFond ttFond;
        ttFond.Test();

        OrderTesterCurr otCurr;
        otCurr.Test();
        OrderTesterFond otFond;
        otFond.Test();

        SecurityStatusTester ist;
        ist.Test();

        SecurityDefinitionTester ids;
        ids.Test();

        HistoricalReplayTester hrt;
        hrt.Test();

        StatisticsTesterFond stFond;
        stFond.Test();
    }
};

#endif
#endif //HFT_ROBOT_FEEDCONNECTIONTESTER_H
