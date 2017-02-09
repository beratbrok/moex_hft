//
// Created by root on 09.02.17.
//

#ifndef HFT_ROBOT_DEBUGINFOMANAGER_H
#define HFT_ROBOT_DEBUGINFOMANAGER_H

#include "../Fast/FastTypes.h"
#include "../Fast/FastProtocolManager.h"

class DebugInfoManager {

    MDEntryType MDEntryTypes[39] {
            mdetBuyQuote,
            mdetSellQuote,
            mdetLastDealInfo,
            mdetIndicesList,
            mdetPriceOpenFirst,
            mdetPriceCloseLast,
            mdetPriceMax,
            mdetPriceMin,
            mdetPriceAve,
            mdetDisbalance, // A
            mdetTransactionsMagnitude, //B
            mdetEmptyBook, // J
            mdetOfferPriceMax,
            mdetBidPriceMin,
            mdetAuctionPriceCalculated,
            mdetAuctionPriceClose,
            mdetAuctionMagnitudeClose,
            mdetMSSTradingDenyNotEnoughMoney,
            mdetMSSTradeOfferAuctionMagnitudeOpenClose,
            mdetOLSTradeOfferAuctionOpenClose,
            mdetMSSTradeBidAuctionMagnitudeOpenClose,
            mdetOLSTradeBidAuctionOpenClose,
            mdetSessionOffer,
            mdetSessionBid,
            mdetPreTradePeriodPrice,
            mdetPostTradePeriodPrice,
            mdetTradePrice2,
            mdetTradePrice,
            mdetPriceOpenOfficial,
            mdetPriceCurrentOfficial,
            mdetLegitimQuote,
            mdetPriceCloseOfficial,
            mdetOfferTotal,
            mdetBidTotal,
            mdetAuctionPriceBigPackets,
            mdetAuctionMagnitudeBigPackets,
            mdetCumulativeCouponDebit,
            mdetDuration,
            mdetAllDeals
    };

    int MDEntryTypeRecv[39] {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0 };

public:
    static DebugInfoManager *Default;

    DebugInfoManager() { }
    ~DebugInfoManager() { }
    template<typename T> void PrintStatisticsOnce(FastProtocolManager *manager, T *info) {
        bool shouldPrint = false;
        for(int i = 0; i < info->GroupMDEntriesCount; i++) {
            for (int e = 0; e < 39; e++) {
                if (this->MDEntryTypes[e] != info->GroupMDEntries[i]->MDEntryType[0])
                    continue;

                if (this->MDEntryTypeRecv[e] > 0)
                    continue;

                this->MDEntryTypeRecv[e]++;
                shouldPrint = true;
                break;
            }
        }
        if(shouldPrint)
            manager->Print();
    }
};

/*class DefaultDebugInfoManager {
public:
    static DebugInfoManager *Default;
};*/

#endif //HFT_ROBOT_DEBUGINFOMANAGER_H
