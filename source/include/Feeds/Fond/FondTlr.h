//
// Created by root on 19.02.17.
//

#ifndef HFT_ROBOT_FONDTLR_H
#define HFT_ROBOT_FONDTLR_H

#include "../FeedConnection.h"

class FeedConnection_FOND_TLR : public FeedConnection {
public:
    FeedConnection_FOND_TLR(const char *id, const char *name, char value, FeedConnectionProtocol protocol, const char *aSourceIp, const char *aIp, int aPort, const char *bSourceIp, const char *bIp, int bPort) :
            FeedConnection(id, name, value, protocol, aSourceIp, aIp, aPort, bSourceIp, bIp, bPort) {
        this->SetType(FeedConnectionType::Incremental);
        this->m_tradeTableFond = new MarketDataTable<TradeInfo, FastTLSFONDInfo, FastTLSFONDItemInfo>();
        this->SetId(FeedConnectionId::fcidTlrFond);
        this->m_fastProtocolManager = new FastProtocolManager(this->CreateFastAllocationInfo());
        InitializePackets();
    }
    ~FeedConnection_FOND_TLR() {
        delete this->m_tradeTableFond;
    }
    ISocketBufferProvider* CreateSocketBufferProvider() {
        return new SocketBufferProvider(DefaultSocketBufferManager::Default,
                                        RobotSettings::DefaultFeedConnectionSendBufferSize,
                                        RobotSettings::DefaultFeedConnectionSendItemsCount,
                                        RobotSettings::DefaultFeedConnectionRecvBufferSize,
                                        RobotSettings::DefaultFeedConnectionRecvItemsCount);
    }
    FastObjectsAllocationInfo* CreateFastAllocationInfo() {
        FastObjectsAllocationInfo *info = new FastObjectsAllocationInfo();

#ifndef TEST
        info->m_incrementalTLRFONDCount = 1024;
        info->m_incrementalTLRFONDAddCount = 256;
        info->m_tLSFONDItemsCount = 2024;
        info->m_tLSFONDItemsAddCount = 256;
#else
        info->m_incrementalTLRFONDCount = 100;
        info->m_incrementalTLRFONDAddCount = 100;
        info->m_tLSFONDItemsCount = 100;
        info->m_tLSFONDItemsAddCount = 100;
#endif

        info->m_heartbeatCount = 10;
        info->m_heartbeatAddCount = 10;
        info->m_tradingSessionStatusCount = 10;
        info->m_tradingSessionStatusAddCount = 10;

        return info;
    }
};

#endif //HFT_ROBOT_FONDTLR_H