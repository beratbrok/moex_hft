#pragma once
#pragma once
#pragma once
#include "../Fix/FixTypes.h"
#include "FastTypes.h"
#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include "../ProgramStatistics.h"
#include <x86intrin.h>
#include <avx2intrin.h>

#ifdef TEST

#define ALLOW_BMI
#define ALLOW_SIMPLE

#else

#define ALLOW_BMI

#endif

#define USE_BMI

class FastProtocolManager;
class OrderTesterFond;
class OrderTesterCurr;
class TradeTesterFond;
class TradeTesterCurr;
class OrderBookTesterForts;
class StatisticsTesterFond;
class StatisticsTesterCurr;
class FeedConnection;
class TestMessagesHelper;

#pragma region Checking_Presence_GeneratedCode
#define CheckMandatoryFieldPresence(map, field) ((map & field) != 0)
#define CheckOptionalFieldPresence(map, field) ((map & field) != 0)
#pragma endregion

#ifdef COLLECT_STATISTICS
//#define COLLECT_STATISTICS_FAST
#endif

class FastProtocolManager {
    friend class OrderTesterFond;
    friend class OrderTesterCurr;
    friend class TradeTesterFond;
    friend class TradeTesterCurr;
    friend class OrderBookTesterForts;
    friend class StatisticsTesterFond;
    friend class StatisticsTesterCurr;
    friend class FeedConnection;
	friend class TestMessagesHelper;

    static const int maxBufferLength = 16000;
	BYTE                        *currentPos;
	UINT64                      m_presenceMap;
	BYTE                        *buffer;

	UINT                        m_templateId;
    int                         bufferLength;

	FILE                        *m_xmlFilePtr;
    void                        *m_lastDecodedInfo;

#pragma region Asts_Declare_AllocationInfo_GeneratedCode
	AstsObjectsAllocationInfo *m_astsAllocationInfo;
	AstsSnapshotInfo *m_astsSnapshotInfo;
#pragma endregion
#pragma region Forts_Declare_AllocationInfo_GeneratedCode
	FortsObjectsAllocationInfo *m_fortsAllocationInfo;
	FortsSnapshotInfo *m_fortsSnapshotInfo;
#pragma endregion

#pragma region String_Constant_Declaration_GeneratedCode
public:
	char	MessageEncodingConstString[8];
	static const UINT	MessageEncodingConstStringLength = 5;
private:

	void InitializeConstantStrings() {
		sprintf(MessageEncodingConstString, "UTF-8");
	}
#pragma endregion

#pragma region Asts_Structure_Objects_Declaration_GeneratedCode
	AutoAllocatePointerList<AstsLogonInfo>	*m_astsLogon;
	AutoAllocatePointerList<AstsLogoutInfo>	*m_astsLogout;
	AutoAllocatePointerList<AstsGenericItemInfo>	*m_astsGenericItems;
	AutoAllocatePointerList<AstsGenericInfo>	*m_astsGeneric;
	AutoAllocatePointerList<AstsOLSFONDItemInfo>	*m_astsOLSFONDItems;
	AutoAllocatePointerList<AstsOLSFONDInfo>	*m_astsOLSFOND;
	AutoAllocatePointerList<AstsOLSCURRItemInfo>	*m_astsOLSCURRItems;
	AutoAllocatePointerList<AstsOLSCURRInfo>	*m_astsOLSCURR;
	AutoAllocatePointerList<AstsTLSFONDItemInfo>	*m_astsTLSFONDItems;
	AutoAllocatePointerList<AstsTLSFONDInfo>	*m_astsTLSFOND;
	AutoAllocatePointerList<AstsTLSCURRItemInfo>	*m_astsTLSCURRItems;
	AutoAllocatePointerList<AstsTLSCURRInfo>	*m_astsTLSCURR;
	AutoAllocatePointerList<AstsSecurityDefinitionGroupInstrAttribItemInfo>	*m_astsSecurityDefinitionGroupInstrAttribItems;
	AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>	*m_astsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;
	AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpItemInfo>	*m_astsSecurityDefinitionMarketSegmentGrpItems;
	AutoAllocatePointerList<AstsSecurityDefinitionInfo>	*m_astsSecurityDefinition;
	AutoAllocatePointerList<AstsSecurityStatusInfo>	*m_astsSecurityStatus;
	AutoAllocatePointerList<AstsTradingSessionStatusInfo>	*m_astsTradingSessionStatus;
	AutoAllocatePointerList<AstsHeartbeatInfo>	*m_astsHeartbeat;
	AutoAllocatePointerList<AstsIncrementalGenericInfo>	*m_astsIncrementalGeneric;
	AutoAllocatePointerList<AstsIncrementalMSRFONDInfo>	*m_astsIncrementalMSRFOND;
	AutoAllocatePointerList<AstsIncrementalMSRCURRInfo>	*m_astsIncrementalMSRCURR;
	AutoAllocatePointerList<AstsIncrementalOLRFONDInfo>	*m_astsIncrementalOLRFOND;
	AutoAllocatePointerList<AstsIncrementalOLRCURRInfo>	*m_astsIncrementalOLRCURR;
	AutoAllocatePointerList<AstsIncrementalTLRFONDInfo>	*m_astsIncrementalTLRFOND;
	AutoAllocatePointerList<AstsIncrementalTLRCURRInfo>	*m_astsIncrementalTLRCURR;
	AstsGenericInfo	*m_cachedastsGenericInfo;
	AstsOLSFONDInfo	*m_cachedastsOLSFONDInfo;
	AstsOLSCURRInfo	*m_cachedastsOLSCURRInfo;
	AstsTLSFONDInfo	*m_cachedastsTLSFONDInfo;
	AstsTLSCURRInfo	*m_cachedastsTLSCURRInfo;
	AstsSecurityStatusInfo	*m_cachedastsSecurityStatusInfo;
	AstsTradingSessionStatusInfo	*m_cachedastsTradingSessionStatusInfo;
	AstsHeartbeatInfo	*m_cachedastsHeartbeatInfo;
	AstsIncrementalGenericInfo	*m_cachedastsIncrementalGenericInfo;
	AstsIncrementalMSRFONDInfo	*m_cachedastsIncrementalMSRFONDInfo;
	AstsIncrementalMSRCURRInfo	*m_cachedastsIncrementalMSRCURRInfo;
	AstsIncrementalOLRFONDInfo	*m_cachedastsIncrementalOLRFONDInfo;
	AstsIncrementalOLRCURRInfo	*m_cachedastsIncrementalOLRCURRInfo;
	AstsIncrementalTLRFONDInfo	*m_cachedastsIncrementalTLRFONDInfo;
	AstsIncrementalTLRCURRInfo	*m_cachedastsIncrementalTLRCURRInfo;
	AstsLogonInfo	*m_prevastsLogonInfo;
	AstsLogoutInfo	*m_prevastsLogoutInfo;
	AstsGenericItemInfo	*m_prevastsGenericItemInfo;
	AstsGenericInfo	*m_prevastsGenericInfo;
	AstsOLSFONDItemInfo	*m_prevastsOLSFONDItemInfo;
	AstsOLSFONDInfo	*m_prevastsOLSFONDInfo;
	AstsOLSCURRItemInfo	*m_prevastsOLSCURRItemInfo;
	AstsOLSCURRInfo	*m_prevastsOLSCURRInfo;
	AstsTLSFONDItemInfo	*m_prevastsTLSFONDItemInfo;
	AstsTLSFONDInfo	*m_prevastsTLSFONDInfo;
	AstsTLSCURRItemInfo	*m_prevastsTLSCURRItemInfo;
	AstsTLSCURRInfo	*m_prevastsTLSCURRInfo;
	AstsSecurityDefinitionGroupInstrAttribItemInfo	*m_prevastsSecurityDefinitionGroupInstrAttribItemInfo;
	AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo	*m_prevastsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo;
	AstsSecurityDefinitionMarketSegmentGrpItemInfo	*m_prevastsSecurityDefinitionMarketSegmentGrpItemInfo;
	AstsSecurityDefinitionInfo	*m_prevastsSecurityDefinitionInfo;
	AstsSecurityStatusInfo	*m_prevastsSecurityStatusInfo;
	AstsTradingSessionStatusInfo	*m_prevastsTradingSessionStatusInfo;
	AstsHeartbeatInfo	*m_prevastsHeartbeatInfo;
	AstsIncrementalGenericInfo	*m_prevastsIncrementalGenericInfo;
	AstsIncrementalMSRFONDInfo	*m_prevastsIncrementalMSRFONDInfo;
	AstsIncrementalMSRCURRInfo	*m_prevastsIncrementalMSRCURRInfo;
	AstsIncrementalOLRFONDInfo	*m_prevastsIncrementalOLRFONDInfo;
	AstsIncrementalOLRCURRInfo	*m_prevastsIncrementalOLRCURRInfo;
	AstsIncrementalTLRFONDInfo	*m_prevastsIncrementalTLRFONDInfo;
	AstsIncrementalTLRCURRInfo	*m_prevastsIncrementalTLRCURRInfo;

	void InitializeAstsMessageInfo() {
		this->m_astsLogon = this->m_astsAllocationInfo->GetAstsLogonInfoPool();
		this->m_astsLogout = this->m_astsAllocationInfo->GetAstsLogoutInfoPool();
		this->m_astsGenericItems = this->m_astsAllocationInfo->GetAstsGenericItemInfoPool();
		this->m_astsGeneric = this->m_astsAllocationInfo->GetAstsGenericInfoPool();
		this->m_astsOLSFONDItems = this->m_astsAllocationInfo->GetAstsOLSFONDItemInfoPool();
		this->m_astsOLSFOND = this->m_astsAllocationInfo->GetAstsOLSFONDInfoPool();
		this->m_astsOLSCURRItems = this->m_astsAllocationInfo->GetAstsOLSCURRItemInfoPool();
		this->m_astsOLSCURR = this->m_astsAllocationInfo->GetAstsOLSCURRInfoPool();
		this->m_astsTLSFONDItems = this->m_astsAllocationInfo->GetAstsTLSFONDItemInfoPool();
		this->m_astsTLSFOND = this->m_astsAllocationInfo->GetAstsTLSFONDInfoPool();
		this->m_astsTLSCURRItems = this->m_astsAllocationInfo->GetAstsTLSCURRItemInfoPool();
		this->m_astsTLSCURR = this->m_astsAllocationInfo->GetAstsTLSCURRInfoPool();
		this->m_astsSecurityDefinitionGroupInstrAttribItems = this->m_astsAllocationInfo->GetAstsSecurityDefinitionGroupInstrAttribItemInfoPool();
		this->m_astsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems = this->m_astsAllocationInfo->GetAstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool();
		this->m_astsSecurityDefinitionMarketSegmentGrpItems = this->m_astsAllocationInfo->GetAstsSecurityDefinitionMarketSegmentGrpItemInfoPool();
		this->m_astsSecurityDefinition = this->m_astsAllocationInfo->GetAstsSecurityDefinitionInfoPool();
		this->m_astsSecurityStatus = this->m_astsAllocationInfo->GetAstsSecurityStatusInfoPool();
		this->m_astsTradingSessionStatus = this->m_astsAllocationInfo->GetAstsTradingSessionStatusInfoPool();
		this->m_astsHeartbeat = this->m_astsAllocationInfo->GetAstsHeartbeatInfoPool();
		this->m_astsIncrementalGeneric = this->m_astsAllocationInfo->GetAstsIncrementalGenericInfoPool();
		this->m_astsIncrementalMSRFOND = this->m_astsAllocationInfo->GetAstsIncrementalMSRFONDInfoPool();
		this->m_astsIncrementalMSRCURR = this->m_astsAllocationInfo->GetAstsIncrementalMSRCURRInfoPool();
		this->m_astsIncrementalOLRFOND = this->m_astsAllocationInfo->GetAstsIncrementalOLRFONDInfoPool();
		this->m_astsIncrementalOLRCURR = this->m_astsAllocationInfo->GetAstsIncrementalOLRCURRInfoPool();
		this->m_astsIncrementalTLRFOND = this->m_astsAllocationInfo->GetAstsIncrementalTLRFONDInfoPool();
		this->m_astsIncrementalTLRCURR = this->m_astsAllocationInfo->GetAstsIncrementalTLRCURRInfoPool();
		this->m_cachedastsGenericInfo = this->m_astsGeneric->NewItemUnsafe();
		this->m_cachedastsOLSFONDInfo = this->m_astsOLSFOND->NewItemUnsafe();
		this->m_cachedastsOLSCURRInfo = this->m_astsOLSCURR->NewItemUnsafe();
		this->m_cachedastsTLSFONDInfo = this->m_astsTLSFOND->NewItemUnsafe();
		this->m_cachedastsTLSCURRInfo = this->m_astsTLSCURR->NewItemUnsafe();
		this->m_cachedastsSecurityStatusInfo = this->m_astsSecurityStatus->NewItemUnsafe();
		this->m_cachedastsTradingSessionStatusInfo = this->m_astsTradingSessionStatus->NewItemUnsafe();
		this->m_cachedastsHeartbeatInfo = this->m_astsHeartbeat->NewItemUnsafe();
		this->m_cachedastsIncrementalGenericInfo = this->m_astsIncrementalGeneric->NewItemUnsafe();
		this->m_cachedastsIncrementalMSRFONDInfo = this->m_astsIncrementalMSRFOND->NewItemUnsafe();
		this->m_cachedastsIncrementalMSRCURRInfo = this->m_astsIncrementalMSRCURR->NewItemUnsafe();
		this->m_cachedastsIncrementalOLRFONDInfo = this->m_astsIncrementalOLRFOND->NewItemUnsafe();
		this->m_cachedastsIncrementalOLRCURRInfo = this->m_astsIncrementalOLRCURR->NewItemUnsafe();
		this->m_cachedastsIncrementalTLRFONDInfo = this->m_astsIncrementalTLRFOND->NewItemUnsafe();
		this->m_cachedastsIncrementalTLRCURRInfo = this->m_astsIncrementalTLRCURR->NewItemUnsafe();
		this->m_prevastsLogonInfo = this->GetFreeAstsLogonInfo();
		this->m_prevastsLogoutInfo = this->GetFreeAstsLogoutInfo();
		this->m_prevastsGenericItemInfo = this->GetFreeAstsGenericItemInfo();
		this->m_prevastsGenericInfo = this->GetFreeAstsGenericInfo();
		this->m_prevastsOLSFONDItemInfo = this->GetFreeAstsOLSFONDItemInfo();
		this->m_prevastsOLSFONDInfo = this->GetFreeAstsOLSFONDInfo();
		this->m_prevastsOLSCURRItemInfo = this->GetFreeAstsOLSCURRItemInfo();
		this->m_prevastsOLSCURRInfo = this->GetFreeAstsOLSCURRInfo();
		this->m_prevastsTLSFONDItemInfo = this->GetFreeAstsTLSFONDItemInfo();
		this->m_prevastsTLSFONDInfo = this->GetFreeAstsTLSFONDInfo();
		this->m_prevastsTLSCURRItemInfo = this->GetFreeAstsTLSCURRItemInfo();
		this->m_prevastsTLSCURRInfo = this->GetFreeAstsTLSCURRInfo();
		this->m_prevastsSecurityDefinitionGroupInstrAttribItemInfo = this->GetFreeAstsSecurityDefinitionGroupInstrAttribItemInfo();
		this->m_prevastsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo = this->GetFreeAstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo();
		this->m_prevastsSecurityDefinitionMarketSegmentGrpItemInfo = this->GetFreeAstsSecurityDefinitionMarketSegmentGrpItemInfo();
		this->m_prevastsSecurityDefinitionInfo = this->GetFreeAstsSecurityDefinitionInfo();
		this->m_prevastsSecurityStatusInfo = this->GetFreeAstsSecurityStatusInfo();
		this->m_prevastsTradingSessionStatusInfo = this->GetFreeAstsTradingSessionStatusInfo();
		this->m_prevastsHeartbeatInfo = this->GetFreeAstsHeartbeatInfo();
		this->m_prevastsIncrementalGenericInfo = this->GetFreeAstsIncrementalGenericInfo();
		this->m_prevastsIncrementalMSRFONDInfo = this->GetFreeAstsIncrementalMSRFONDInfo();
		this->m_prevastsIncrementalMSRCURRInfo = this->GetFreeAstsIncrementalMSRCURRInfo();
		this->m_prevastsIncrementalOLRFONDInfo = this->GetFreeAstsIncrementalOLRFONDInfo();
		this->m_prevastsIncrementalOLRCURRInfo = this->GetFreeAstsIncrementalOLRCURRInfo();
		this->m_prevastsIncrementalTLRFONDInfo = this->GetFreeAstsIncrementalTLRFONDInfo();
		this->m_prevastsIncrementalTLRCURRInfo = this->GetFreeAstsIncrementalTLRCURRInfo();
	}

#pragma endregion

#pragma region Forts_Structure_Objects_Declaration_GeneratedCode
	AutoAllocatePointerList<FortsDefaultSnapshotMessageMDEntriesItemInfo>	*m_fortsDefaultSnapshotMessageMDEntriesItems;
	AutoAllocatePointerList<FortsDefaultSnapshotMessageInfo>	*m_fortsDefaultSnapshotMessage;
	AutoAllocatePointerList<FortsSecurityDefinitionMDFeedTypesItemInfo>	*m_fortsSecurityDefinitionMDFeedTypesItems;
	AutoAllocatePointerList<FortsSecurityDefinitionUnderlyingsItemInfo>	*m_fortsSecurityDefinitionUnderlyingsItems;
	AutoAllocatePointerList<FortsSecurityDefinitionInstrumentLegsItemInfo>	*m_fortsSecurityDefinitionInstrumentLegsItems;
	AutoAllocatePointerList<FortsSecurityDefinitionInstrumentAttributesItemInfo>	*m_fortsSecurityDefinitionInstrumentAttributesItems;
	AutoAllocatePointerList<FortsSecurityDefinitionEvntGrpItemInfo>	*m_fortsSecurityDefinitionEvntGrpItems;
	AutoAllocatePointerList<FortsSecurityDefinitionInfo>	*m_fortsSecurityDefinition;
	AutoAllocatePointerList<FortsSecurityDefinitionUpdateReportInfo>	*m_fortsSecurityDefinitionUpdateReport;
	AutoAllocatePointerList<FortsSecurityStatusInfo>	*m_fortsSecurityStatus;
	AutoAllocatePointerList<FortsHeartbeatInfo>	*m_fortsHeartbeat;
	AutoAllocatePointerList<FortsSequenceResetInfo>	*m_fortsSequenceReset;
	AutoAllocatePointerList<FortsTradingSessionStatusInfo>	*m_fortsTradingSessionStatus;
	AutoAllocatePointerList<FortsNewsNewsTextItemInfo>	*m_fortsNewsNewsTextItems;
	AutoAllocatePointerList<FortsNewsInfo>	*m_fortsNews;
	AutoAllocatePointerList<FortsOrdersLogMDEntriesItemInfo>	*m_fortsOrdersLogMDEntriesItems;
	AutoAllocatePointerList<FortsOrdersLogInfo>	*m_fortsOrdersLog;
	AutoAllocatePointerList<FortsOrdersBookMDEntriesItemInfo>	*m_fortsOrdersBookMDEntriesItems;
	AutoAllocatePointerList<FortsOrdersBookInfo>	*m_fortsOrdersBook;
	AutoAllocatePointerList<FortsLogonInfo>	*m_fortsLogon;
	AutoAllocatePointerList<FortsLogoutInfo>	*m_fortsLogout;
	AutoAllocatePointerList<FortsDefaultIncrementalRefreshMessageInfo>	*m_fortsDefaultIncrementalRefreshMessage;
	FortsDefaultSnapshotMessageMDEntriesItemInfo	*m_prevfortsDefaultSnapshotMessageMDEntriesItemInfo;
	FortsDefaultSnapshotMessageInfo	*m_prevfortsDefaultSnapshotMessageInfo;
	FortsSecurityDefinitionMDFeedTypesItemInfo	*m_prevfortsSecurityDefinitionMDFeedTypesItemInfo;
	FortsSecurityDefinitionUnderlyingsItemInfo	*m_prevfortsSecurityDefinitionUnderlyingsItemInfo;
	FortsSecurityDefinitionInstrumentLegsItemInfo	*m_prevfortsSecurityDefinitionInstrumentLegsItemInfo;
	FortsSecurityDefinitionInstrumentAttributesItemInfo	*m_prevfortsSecurityDefinitionInstrumentAttributesItemInfo;
	FortsSecurityDefinitionEvntGrpItemInfo	*m_prevfortsSecurityDefinitionEvntGrpItemInfo;
	FortsSecurityDefinitionInfo	*m_prevfortsSecurityDefinitionInfo;
	FortsSecurityDefinitionUpdateReportInfo	*m_prevfortsSecurityDefinitionUpdateReportInfo;
	FortsSecurityStatusInfo	*m_prevfortsSecurityStatusInfo;
	FortsHeartbeatInfo	*m_prevfortsHeartbeatInfo;
	FortsSequenceResetInfo	*m_prevfortsSequenceResetInfo;
	FortsTradingSessionStatusInfo	*m_prevfortsTradingSessionStatusInfo;
	FortsNewsNewsTextItemInfo	*m_prevfortsNewsNewsTextItemInfo;
	FortsNewsInfo	*m_prevfortsNewsInfo;
	FortsOrdersLogMDEntriesItemInfo	*m_prevfortsOrdersLogMDEntriesItemInfo;
	FortsOrdersLogInfo	*m_prevfortsOrdersLogInfo;
	FortsOrdersBookMDEntriesItemInfo	*m_prevfortsOrdersBookMDEntriesItemInfo;
	FortsOrdersBookInfo	*m_prevfortsOrdersBookInfo;
	FortsLogonInfo	*m_prevfortsLogonInfo;
	FortsLogoutInfo	*m_prevfortsLogoutInfo;
	FortsDefaultIncrementalRefreshMessageInfo	*m_prevfortsDefaultIncrementalRefreshMessageInfo;

	void InitializeFortsMessageInfo() {
		this->m_fortsDefaultSnapshotMessageMDEntriesItems = this->m_fortsAllocationInfo->GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool();
		this->m_fortsDefaultSnapshotMessage = this->m_fortsAllocationInfo->GetFortsDefaultSnapshotMessageInfoPool();
		this->m_fortsSecurityDefinitionMDFeedTypesItems = this->m_fortsAllocationInfo->GetFortsSecurityDefinitionMDFeedTypesItemInfoPool();
		this->m_fortsSecurityDefinitionUnderlyingsItems = this->m_fortsAllocationInfo->GetFortsSecurityDefinitionUnderlyingsItemInfoPool();
		this->m_fortsSecurityDefinitionInstrumentLegsItems = this->m_fortsAllocationInfo->GetFortsSecurityDefinitionInstrumentLegsItemInfoPool();
		this->m_fortsSecurityDefinitionInstrumentAttributesItems = this->m_fortsAllocationInfo->GetFortsSecurityDefinitionInstrumentAttributesItemInfoPool();
		this->m_fortsSecurityDefinitionEvntGrpItems = this->m_fortsAllocationInfo->GetFortsSecurityDefinitionEvntGrpItemInfoPool();
		this->m_fortsSecurityDefinition = this->m_fortsAllocationInfo->GetFortsSecurityDefinitionInfoPool();
		this->m_fortsSecurityDefinitionUpdateReport = this->m_fortsAllocationInfo->GetFortsSecurityDefinitionUpdateReportInfoPool();
		this->m_fortsSecurityStatus = this->m_fortsAllocationInfo->GetFortsSecurityStatusInfoPool();
		this->m_fortsHeartbeat = this->m_fortsAllocationInfo->GetFortsHeartbeatInfoPool();
		this->m_fortsSequenceReset = this->m_fortsAllocationInfo->GetFortsSequenceResetInfoPool();
		this->m_fortsTradingSessionStatus = this->m_fortsAllocationInfo->GetFortsTradingSessionStatusInfoPool();
		this->m_fortsNewsNewsTextItems = this->m_fortsAllocationInfo->GetFortsNewsNewsTextItemInfoPool();
		this->m_fortsNews = this->m_fortsAllocationInfo->GetFortsNewsInfoPool();
		this->m_fortsOrdersLogMDEntriesItems = this->m_fortsAllocationInfo->GetFortsOrdersLogMDEntriesItemInfoPool();
		this->m_fortsOrdersLog = this->m_fortsAllocationInfo->GetFortsOrdersLogInfoPool();
		this->m_fortsOrdersBookMDEntriesItems = this->m_fortsAllocationInfo->GetFortsOrdersBookMDEntriesItemInfoPool();
		this->m_fortsOrdersBook = this->m_fortsAllocationInfo->GetFortsOrdersBookInfoPool();
		this->m_fortsLogon = this->m_fortsAllocationInfo->GetFortsLogonInfoPool();
		this->m_fortsLogout = this->m_fortsAllocationInfo->GetFortsLogoutInfoPool();
		this->m_fortsDefaultIncrementalRefreshMessage = this->m_fortsAllocationInfo->GetFortsDefaultIncrementalRefreshMessageInfoPool();
		this->m_prevfortsDefaultSnapshotMessageMDEntriesItemInfo = this->GetFreeFortsDefaultSnapshotMessageMDEntriesItemInfo();
		this->m_prevfortsDefaultSnapshotMessageInfo = this->GetFreeFortsDefaultSnapshotMessageInfo();
		this->m_prevfortsSecurityDefinitionMDFeedTypesItemInfo = this->GetFreeFortsSecurityDefinitionMDFeedTypesItemInfo();
		this->m_prevfortsSecurityDefinitionUnderlyingsItemInfo = this->GetFreeFortsSecurityDefinitionUnderlyingsItemInfo();
		this->m_prevfortsSecurityDefinitionInstrumentLegsItemInfo = this->GetFreeFortsSecurityDefinitionInstrumentLegsItemInfo();
		this->m_prevfortsSecurityDefinitionInstrumentAttributesItemInfo = this->GetFreeFortsSecurityDefinitionInstrumentAttributesItemInfo();
		this->m_prevfortsSecurityDefinitionEvntGrpItemInfo = this->GetFreeFortsSecurityDefinitionEvntGrpItemInfo();
		this->m_prevfortsSecurityDefinitionInfo = this->GetFreeFortsSecurityDefinitionInfo();
		this->m_prevfortsSecurityDefinitionUpdateReportInfo = this->GetFreeFortsSecurityDefinitionUpdateReportInfo();
		this->m_prevfortsSecurityStatusInfo = this->GetFreeFortsSecurityStatusInfo();
		this->m_prevfortsHeartbeatInfo = this->GetFreeFortsHeartbeatInfo();
		this->m_prevfortsSequenceResetInfo = this->GetFreeFortsSequenceResetInfo();
		this->m_prevfortsTradingSessionStatusInfo = this->GetFreeFortsTradingSessionStatusInfo();
		this->m_prevfortsNewsNewsTextItemInfo = this->GetFreeFortsNewsNewsTextItemInfo();
		this->m_prevfortsNewsInfo = this->GetFreeFortsNewsInfo();
		this->m_prevfortsOrdersLogMDEntriesItemInfo = this->GetFreeFortsOrdersLogMDEntriesItemInfo();
		this->m_prevfortsOrdersLogInfo = this->GetFreeFortsOrdersLogInfo();
		this->m_prevfortsOrdersBookMDEntriesItemInfo = this->GetFreeFortsOrdersBookMDEntriesItemInfo();
		this->m_prevfortsOrdersBookInfo = this->GetFreeFortsOrdersBookInfo();
		this->m_prevfortsLogonInfo = this->GetFreeFortsLogonInfo();
		this->m_prevfortsLogoutInfo = this->GetFreeFortsLogoutInfo();
		this->m_prevfortsDefaultIncrementalRefreshMessageInfo = this->GetFreeFortsDefaultIncrementalRefreshMessageInfo();
	}

#pragma endregion

#pragma region Decode_Method_Pointer_Arrays_GeneratedCode
#pragma endregion

#pragma region Get_Free_Item_Methods_GeneratedCode
public:
	inline FortsSnapshotInfo* GetFreeFortsSnapshotInfo() {
		this->m_fortsSnapshotInfo->LastFragment = 0;
		this->m_fortsSnapshotInfo->LastMsgSeqNumProcessed = -1;
		this->m_fortsSnapshotInfo->RptSeq = -1;
		return this->m_fortsSnapshotInfo;
	}
	inline FortsDefaultSnapshotMessageMDEntriesItemInfo* GetFreeFortsDefaultSnapshotMessageMDEntriesItemInfo() {
		return this->m_fortsDefaultSnapshotMessageMDEntriesItems->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<FortsDefaultSnapshotMessageMDEntriesItemInfo>* GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool() {
		return this->m_fortsDefaultSnapshotMessageMDEntriesItems;
	}

	inline FortsDefaultSnapshotMessageInfo* GetFreeFortsDefaultSnapshotMessageInfo() {
		return this->m_fortsDefaultSnapshotMessage->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<FortsDefaultSnapshotMessageInfo>* GetFortsDefaultSnapshotMessageInfoPool() {
		return this->m_fortsDefaultSnapshotMessage;
	}

	inline FortsSecurityDefinitionMDFeedTypesItemInfo* GetFreeFortsSecurityDefinitionMDFeedTypesItemInfo() {
		return this->m_fortsSecurityDefinitionMDFeedTypesItems->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<FortsSecurityDefinitionMDFeedTypesItemInfo>* GetFortsSecurityDefinitionMDFeedTypesItemInfoPool() {
		return this->m_fortsSecurityDefinitionMDFeedTypesItems;
	}

	inline FortsSecurityDefinitionUnderlyingsItemInfo* GetFreeFortsSecurityDefinitionUnderlyingsItemInfo() {
		return this->m_fortsSecurityDefinitionUnderlyingsItems->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<FortsSecurityDefinitionUnderlyingsItemInfo>* GetFortsSecurityDefinitionUnderlyingsItemInfoPool() {
		return this->m_fortsSecurityDefinitionUnderlyingsItems;
	}

	inline FortsSecurityDefinitionInstrumentLegsItemInfo* GetFreeFortsSecurityDefinitionInstrumentLegsItemInfo() {
		return this->m_fortsSecurityDefinitionInstrumentLegsItems->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<FortsSecurityDefinitionInstrumentLegsItemInfo>* GetFortsSecurityDefinitionInstrumentLegsItemInfoPool() {
		return this->m_fortsSecurityDefinitionInstrumentLegsItems;
	}

	inline FortsSecurityDefinitionInstrumentAttributesItemInfo* GetFreeFortsSecurityDefinitionInstrumentAttributesItemInfo() {
		return this->m_fortsSecurityDefinitionInstrumentAttributesItems->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<FortsSecurityDefinitionInstrumentAttributesItemInfo>* GetFortsSecurityDefinitionInstrumentAttributesItemInfoPool() {
		return this->m_fortsSecurityDefinitionInstrumentAttributesItems;
	}

	inline FortsSecurityDefinitionEvntGrpItemInfo* GetFreeFortsSecurityDefinitionEvntGrpItemInfo() {
		return this->m_fortsSecurityDefinitionEvntGrpItems->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<FortsSecurityDefinitionEvntGrpItemInfo>* GetFortsSecurityDefinitionEvntGrpItemInfoPool() {
		return this->m_fortsSecurityDefinitionEvntGrpItems;
	}

	inline FortsSecurityDefinitionInfo* GetFreeFortsSecurityDefinitionInfo() {
		return this->m_fortsSecurityDefinition->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<FortsSecurityDefinitionInfo>* GetFortsSecurityDefinitionInfoPool() {
		return this->m_fortsSecurityDefinition;
	}

	inline FortsSecurityDefinitionUpdateReportInfo* GetFreeFortsSecurityDefinitionUpdateReportInfo() {
		return this->m_fortsSecurityDefinitionUpdateReport->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<FortsSecurityDefinitionUpdateReportInfo>* GetFortsSecurityDefinitionUpdateReportInfoPool() {
		return this->m_fortsSecurityDefinitionUpdateReport;
	}

	inline FortsSecurityStatusInfo* GetFreeFortsSecurityStatusInfo() {
		return this->m_fortsSecurityStatus->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<FortsSecurityStatusInfo>* GetFortsSecurityStatusInfoPool() {
		return this->m_fortsSecurityStatus;
	}

	inline FortsHeartbeatInfo* GetFreeFortsHeartbeatInfo() {
		return this->m_fortsHeartbeat->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<FortsHeartbeatInfo>* GetFortsHeartbeatInfoPool() {
		return this->m_fortsHeartbeat;
	}

	inline FortsSequenceResetInfo* GetFreeFortsSequenceResetInfo() {
		return this->m_fortsSequenceReset->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<FortsSequenceResetInfo>* GetFortsSequenceResetInfoPool() {
		return this->m_fortsSequenceReset;
	}

	inline FortsTradingSessionStatusInfo* GetFreeFortsTradingSessionStatusInfo() {
		return this->m_fortsTradingSessionStatus->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<FortsTradingSessionStatusInfo>* GetFortsTradingSessionStatusInfoPool() {
		return this->m_fortsTradingSessionStatus;
	}

	inline FortsNewsNewsTextItemInfo* GetFreeFortsNewsNewsTextItemInfo() {
		return this->m_fortsNewsNewsTextItems->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<FortsNewsNewsTextItemInfo>* GetFortsNewsNewsTextItemInfoPool() {
		return this->m_fortsNewsNewsTextItems;
	}

	inline FortsNewsInfo* GetFreeFortsNewsInfo() {
		return this->m_fortsNews->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<FortsNewsInfo>* GetFortsNewsInfoPool() {
		return this->m_fortsNews;
	}

	inline FortsOrdersLogMDEntriesItemInfo* GetFreeFortsOrdersLogMDEntriesItemInfo() {
		return this->m_fortsOrdersLogMDEntriesItems->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<FortsOrdersLogMDEntriesItemInfo>* GetFortsOrdersLogMDEntriesItemInfoPool() {
		return this->m_fortsOrdersLogMDEntriesItems;
	}

	inline FortsOrdersLogInfo* GetFreeFortsOrdersLogInfo() {
		return this->m_fortsOrdersLog->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<FortsOrdersLogInfo>* GetFortsOrdersLogInfoPool() {
		return this->m_fortsOrdersLog;
	}

	inline FortsOrdersBookMDEntriesItemInfo* GetFreeFortsOrdersBookMDEntriesItemInfo() {
		return this->m_fortsOrdersBookMDEntriesItems->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<FortsOrdersBookMDEntriesItemInfo>* GetFortsOrdersBookMDEntriesItemInfoPool() {
		return this->m_fortsOrdersBookMDEntriesItems;
	}

	inline FortsOrdersBookInfo* GetFreeFortsOrdersBookInfo() {
		return this->m_fortsOrdersBook->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<FortsOrdersBookInfo>* GetFortsOrdersBookInfoPool() {
		return this->m_fortsOrdersBook;
	}

	inline FortsLogonInfo* GetFreeFortsLogonInfo() {
		return this->m_fortsLogon->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<FortsLogonInfo>* GetFortsLogonInfoPool() {
		return this->m_fortsLogon;
	}

	inline FortsLogoutInfo* GetFreeFortsLogoutInfo() {
		return this->m_fortsLogout->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<FortsLogoutInfo>* GetFortsLogoutInfoPool() {
		return this->m_fortsLogout;
	}

	inline FortsDefaultIncrementalRefreshMessageInfo* GetFreeFortsDefaultIncrementalRefreshMessageInfo() {
		return this->m_fortsDefaultIncrementalRefreshMessage->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<FortsDefaultIncrementalRefreshMessageInfo>* GetFortsDefaultIncrementalRefreshMessageInfoPool() {
		return this->m_fortsDefaultIncrementalRefreshMessage;
	}

	inline void PrefetchFortsDefaultSnapshotMessageMDEntriesItemInfo() {
		FortsDefaultSnapshotMessageMDEntriesItemInfo *item = this->m_fortsDefaultSnapshotMessageMDEntriesItems->Start()->Data();
		for(int i = 0; i < sizeof(FortsDefaultSnapshotMessageMDEntriesItemInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchFortsDefaultSnapshotMessageInfo() {
		FortsDefaultSnapshotMessageInfo *item = this->m_fortsDefaultSnapshotMessage->Start()->Data();
		for(int i = 0; i < sizeof(FortsDefaultSnapshotMessageInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchFortsSecurityDefinitionMDFeedTypesItemInfo() {
		FortsSecurityDefinitionMDFeedTypesItemInfo *item = this->m_fortsSecurityDefinitionMDFeedTypesItems->Start()->Data();
		for(int i = 0; i < sizeof(FortsSecurityDefinitionMDFeedTypesItemInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchFortsSecurityDefinitionUnderlyingsItemInfo() {
		FortsSecurityDefinitionUnderlyingsItemInfo *item = this->m_fortsSecurityDefinitionUnderlyingsItems->Start()->Data();
		for(int i = 0; i < sizeof(FortsSecurityDefinitionUnderlyingsItemInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchFortsSecurityDefinitionInstrumentLegsItemInfo() {
		FortsSecurityDefinitionInstrumentLegsItemInfo *item = this->m_fortsSecurityDefinitionInstrumentLegsItems->Start()->Data();
		for(int i = 0; i < sizeof(FortsSecurityDefinitionInstrumentLegsItemInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchFortsSecurityDefinitionInstrumentAttributesItemInfo() {
		FortsSecurityDefinitionInstrumentAttributesItemInfo *item = this->m_fortsSecurityDefinitionInstrumentAttributesItems->Start()->Data();
		for(int i = 0; i < sizeof(FortsSecurityDefinitionInstrumentAttributesItemInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchFortsSecurityDefinitionEvntGrpItemInfo() {
		FortsSecurityDefinitionEvntGrpItemInfo *item = this->m_fortsSecurityDefinitionEvntGrpItems->Start()->Data();
		for(int i = 0; i < sizeof(FortsSecurityDefinitionEvntGrpItemInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchFortsSecurityDefinitionInfo() {
		FortsSecurityDefinitionInfo *item = this->m_fortsSecurityDefinition->Start()->Data();
		for(int i = 0; i < sizeof(FortsSecurityDefinitionInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchFortsSecurityDefinitionUpdateReportInfo() {
		FortsSecurityDefinitionUpdateReportInfo *item = this->m_fortsSecurityDefinitionUpdateReport->Start()->Data();
		for(int i = 0; i < sizeof(FortsSecurityDefinitionUpdateReportInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchFortsSecurityStatusInfo() {
		FortsSecurityStatusInfo *item = this->m_fortsSecurityStatus->Start()->Data();
		for(int i = 0; i < sizeof(FortsSecurityStatusInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchFortsHeartbeatInfo() {
		FortsHeartbeatInfo *item = this->m_fortsHeartbeat->Start()->Data();
		for(int i = 0; i < sizeof(FortsHeartbeatInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchFortsSequenceResetInfo() {
		FortsSequenceResetInfo *item = this->m_fortsSequenceReset->Start()->Data();
		for(int i = 0; i < sizeof(FortsSequenceResetInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchFortsTradingSessionStatusInfo() {
		FortsTradingSessionStatusInfo *item = this->m_fortsTradingSessionStatus->Start()->Data();
		for(int i = 0; i < sizeof(FortsTradingSessionStatusInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchFortsNewsNewsTextItemInfo() {
		FortsNewsNewsTextItemInfo *item = this->m_fortsNewsNewsTextItems->Start()->Data();
		for(int i = 0; i < sizeof(FortsNewsNewsTextItemInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchFortsNewsInfo() {
		FortsNewsInfo *item = this->m_fortsNews->Start()->Data();
		for(int i = 0; i < sizeof(FortsNewsInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchFortsOrdersLogMDEntriesItemInfo() {
		FortsOrdersLogMDEntriesItemInfo *item = this->m_fortsOrdersLogMDEntriesItems->Start()->Data();
		for(int i = 0; i < sizeof(FortsOrdersLogMDEntriesItemInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchFortsOrdersLogInfo() {
		FortsOrdersLogInfo *item = this->m_fortsOrdersLog->Start()->Data();
		for(int i = 0; i < sizeof(FortsOrdersLogInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchFortsOrdersBookMDEntriesItemInfo() {
		FortsOrdersBookMDEntriesItemInfo *item = this->m_fortsOrdersBookMDEntriesItems->Start()->Data();
		for(int i = 0; i < sizeof(FortsOrdersBookMDEntriesItemInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchFortsOrdersBookInfo() {
		FortsOrdersBookInfo *item = this->m_fortsOrdersBook->Start()->Data();
		for(int i = 0; i < sizeof(FortsOrdersBookInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchFortsLogonInfo() {
		FortsLogonInfo *item = this->m_fortsLogon->Start()->Data();
		for(int i = 0; i < sizeof(FortsLogonInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchFortsLogoutInfo() {
		FortsLogoutInfo *item = this->m_fortsLogout->Start()->Data();
		for(int i = 0; i < sizeof(FortsLogoutInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchFortsDefaultIncrementalRefreshMessageInfo() {
		FortsDefaultIncrementalRefreshMessageInfo *item = this->m_fortsDefaultIncrementalRefreshMessage->Start()->Data();
		for(int i = 0; i < sizeof(FortsDefaultIncrementalRefreshMessageInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

private:
	void ReleaseFortsDefaultSnapshotMessageMDEntriesItemInfo() {
		static_cast<FortsDefaultSnapshotMessageMDEntriesItemInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFortsDefaultSnapshotMessageInfo() {
		static_cast<FortsDefaultSnapshotMessageInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFortsSecurityDefinitionMDFeedTypesItemInfo() {
		static_cast<FortsSecurityDefinitionMDFeedTypesItemInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFortsSecurityDefinitionUnderlyingsItemInfo() {
		static_cast<FortsSecurityDefinitionUnderlyingsItemInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFortsSecurityDefinitionInstrumentLegsItemInfo() {
		static_cast<FortsSecurityDefinitionInstrumentLegsItemInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFortsSecurityDefinitionInstrumentAttributesItemInfo() {
		static_cast<FortsSecurityDefinitionInstrumentAttributesItemInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFortsSecurityDefinitionEvntGrpItemInfo() {
		static_cast<FortsSecurityDefinitionEvntGrpItemInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFortsSecurityDefinitionInfo() {
		static_cast<FortsSecurityDefinitionInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFortsSecurityDefinitionUpdateReportInfo() {
		static_cast<FortsSecurityDefinitionUpdateReportInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFortsSecurityStatusInfo() {
		static_cast<FortsSecurityStatusInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFortsHeartbeatInfo() {
		static_cast<FortsHeartbeatInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFortsSequenceResetInfo() {
		static_cast<FortsSequenceResetInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFortsTradingSessionStatusInfo() {
		static_cast<FortsTradingSessionStatusInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFortsNewsNewsTextItemInfo() {
		static_cast<FortsNewsNewsTextItemInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFortsNewsInfo() {
		static_cast<FortsNewsInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFortsOrdersLogMDEntriesItemInfo() {
		static_cast<FortsOrdersLogMDEntriesItemInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFortsOrdersLogInfo() {
		static_cast<FortsOrdersLogInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFortsOrdersBookMDEntriesItemInfo() {
		static_cast<FortsOrdersBookMDEntriesItemInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFortsOrdersBookInfo() {
		static_cast<FortsOrdersBookInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFortsLogonInfo() {
		static_cast<FortsLogonInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFortsLogoutInfo() {
		static_cast<FortsLogoutInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseFortsDefaultIncrementalRefreshMessageInfo() {
		static_cast<FortsDefaultIncrementalRefreshMessageInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	inline void ResetForts() {
		if(this->m_templateId <= 9) {
			if(this->m_templateId <= 6) {
				if(this->m_templateId <= 4) {
					if(this->m_templateId == 3) {
						this->ReleaseFortsSecurityDefinitionInfo();
					}
					else { // 4
						this->ReleaseFortsSecurityDefinitionUpdateReportInfo();
					}
				}
				else {
					if(this->m_templateId <= 5) {
						if(this->m_templateId == 4) {
							this->ReleaseFortsSecurityDefinitionUpdateReportInfo();
						}
						else { // 5
							this->ReleaseFortsSecurityStatusInfo();
						}
					}
					else {
						if(this->m_templateId == 5) {
							this->ReleaseFortsSecurityStatusInfo();
						}
						else { // 6
							this->ReleaseFortsHeartbeatInfo();
						}
					}
				}
			}
			else {
				if(this->m_templateId <= 7) {
					if(this->m_templateId == 6) {
						this->ReleaseFortsHeartbeatInfo();
					}
					else { // 7
						this->ReleaseFortsSequenceResetInfo();
					}
				}
				else {
					if(this->m_templateId <= 8) {
						if(this->m_templateId == 7) {
							this->ReleaseFortsSequenceResetInfo();
						}
						else { // 8
							this->ReleaseFortsTradingSessionStatusInfo();
						}
					}
					else {
						if(this->m_templateId == 8) {
							this->ReleaseFortsTradingSessionStatusInfo();
						}
						else { // 9
							this->ReleaseFortsNewsInfo();
						}
					}
				}
			}
		}
		else {
			if(this->m_templateId <= 14) {
				if(this->m_templateId <= 12) {
					if(this->m_templateId == 9) {
						this->ReleaseFortsNewsInfo();
					}
					else { // 12
						this->ReleaseFortsDefaultIncrementalRefreshMessageInfo();
					}
				}
				else {
					if(this->m_templateId <= 13) {
						if(this->m_templateId == 12) {
							this->ReleaseFortsDefaultIncrementalRefreshMessageInfo();
						}
						else { // 13
							this->ReleaseFortsDefaultSnapshotMessageInfo();
						}
					}
					else {
						if(this->m_templateId == 13) {
							this->ReleaseFortsDefaultSnapshotMessageInfo();
						}
						else { // 14
							this->ReleaseFortsOrdersLogInfo();
						}
					}
				}
			}
			else {
				if(this->m_templateId <= 15) {
					if(this->m_templateId == 14) {
						this->ReleaseFortsOrdersLogInfo();
					}
					else { // 15
						this->ReleaseFortsOrdersBookInfo();
					}
				}
				else {
					if(this->m_templateId <= 1000) {
						if(this->m_templateId == 15) {
							this->ReleaseFortsOrdersBookInfo();
						}
						else { // 1000
							this->ReleaseFortsLogonInfo();
						}
					}
					else {
						if(this->m_templateId == 1000) {
							this->ReleaseFortsLogonInfo();
						}
						else { // 1001
							this->ReleaseFortsLogoutInfo();
						}
					}
				}
			}
		}
	}
public:
	inline AstsSnapshotInfo* GetFreeAstsSnapshotInfo() {
		this->m_astsSnapshotInfo->LastFragment = 0;
		this->m_astsSnapshotInfo->LastMsgSeqNumProcessed = -1;
		this->m_astsSnapshotInfo->RouteFirst = 0;
		this->m_astsSnapshotInfo->RptSeq = -1;
		return this->m_astsSnapshotInfo;
	}
	inline AstsLogonInfo* GetFreeAstsLogonInfo() {
		return this->m_astsLogon->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<AstsLogonInfo>* GetAstsLogonInfoPool() {
		return this->m_astsLogon;
	}

	inline AstsLogoutInfo* GetFreeAstsLogoutInfo() {
		return this->m_astsLogout->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<AstsLogoutInfo>* GetAstsLogoutInfoPool() {
		return this->m_astsLogout;
	}

	inline AstsGenericItemInfo* GetFreeAstsGenericItemInfo() {
		return this->m_astsGenericItems->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<AstsGenericItemInfo>* GetAstsGenericItemInfoPool() {
		return this->m_astsGenericItems;
	}

	inline AstsGenericInfo* GetFreeAstsGenericInfo() {
		return this->m_cachedastsGenericInfo;
	}

	inline AutoAllocatePointerList<AstsGenericInfo>* GetAstsGenericInfoPool() {
		return this->m_astsGeneric;
	}

	inline AstsOLSFONDItemInfo* GetFreeAstsOLSFONDItemInfo() {
		return this->m_astsOLSFONDItems->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<AstsOLSFONDItemInfo>* GetAstsOLSFONDItemInfoPool() {
		return this->m_astsOLSFONDItems;
	}

	inline AstsOLSFONDInfo* GetFreeAstsOLSFONDInfo() {
		return this->m_cachedastsOLSFONDInfo;
	}

	inline AutoAllocatePointerList<AstsOLSFONDInfo>* GetAstsOLSFONDInfoPool() {
		return this->m_astsOLSFOND;
	}

	inline AstsOLSCURRItemInfo* GetFreeAstsOLSCURRItemInfo() {
		return this->m_astsOLSCURRItems->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<AstsOLSCURRItemInfo>* GetAstsOLSCURRItemInfoPool() {
		return this->m_astsOLSCURRItems;
	}

	inline AstsOLSCURRInfo* GetFreeAstsOLSCURRInfo() {
		return this->m_cachedastsOLSCURRInfo;
	}

	inline AutoAllocatePointerList<AstsOLSCURRInfo>* GetAstsOLSCURRInfoPool() {
		return this->m_astsOLSCURR;
	}

	inline AstsTLSFONDItemInfo* GetFreeAstsTLSFONDItemInfo() {
		return this->m_astsTLSFONDItems->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<AstsTLSFONDItemInfo>* GetAstsTLSFONDItemInfoPool() {
		return this->m_astsTLSFONDItems;
	}

	inline AstsTLSFONDInfo* GetFreeAstsTLSFONDInfo() {
		return this->m_cachedastsTLSFONDInfo;
	}

	inline AutoAllocatePointerList<AstsTLSFONDInfo>* GetAstsTLSFONDInfoPool() {
		return this->m_astsTLSFOND;
	}

	inline AstsTLSCURRItemInfo* GetFreeAstsTLSCURRItemInfo() {
		return this->m_astsTLSCURRItems->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<AstsTLSCURRItemInfo>* GetAstsTLSCURRItemInfoPool() {
		return this->m_astsTLSCURRItems;
	}

	inline AstsTLSCURRInfo* GetFreeAstsTLSCURRInfo() {
		return this->m_cachedastsTLSCURRInfo;
	}

	inline AutoAllocatePointerList<AstsTLSCURRInfo>* GetAstsTLSCURRInfoPool() {
		return this->m_astsTLSCURR;
	}

	inline AstsSecurityDefinitionGroupInstrAttribItemInfo* GetFreeAstsSecurityDefinitionGroupInstrAttribItemInfo() {
		return this->m_astsSecurityDefinitionGroupInstrAttribItems->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<AstsSecurityDefinitionGroupInstrAttribItemInfo>* GetAstsSecurityDefinitionGroupInstrAttribItemInfoPool() {
		return this->m_astsSecurityDefinitionGroupInstrAttribItems;
	}

	inline AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* GetFreeAstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo() {
		return this->m_astsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>* GetAstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool() {
		return this->m_astsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;
	}

	inline AstsSecurityDefinitionMarketSegmentGrpItemInfo* GetFreeAstsSecurityDefinitionMarketSegmentGrpItemInfo() {
		return this->m_astsSecurityDefinitionMarketSegmentGrpItems->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpItemInfo>* GetAstsSecurityDefinitionMarketSegmentGrpItemInfoPool() {
		return this->m_astsSecurityDefinitionMarketSegmentGrpItems;
	}

	inline AstsSecurityDefinitionInfo* GetFreeAstsSecurityDefinitionInfo() {
		return this->m_astsSecurityDefinition->NewItemUnsafe();
	}

	inline AutoAllocatePointerList<AstsSecurityDefinitionInfo>* GetAstsSecurityDefinitionInfoPool() {
		return this->m_astsSecurityDefinition;
	}

	inline AstsSecurityStatusInfo* GetFreeAstsSecurityStatusInfo() {
		return this->m_cachedastsSecurityStatusInfo;
	}

	inline AutoAllocatePointerList<AstsSecurityStatusInfo>* GetAstsSecurityStatusInfoPool() {
		return this->m_astsSecurityStatus;
	}

	inline AstsTradingSessionStatusInfo* GetFreeAstsTradingSessionStatusInfo() {
		return this->m_cachedastsTradingSessionStatusInfo;
	}

	inline AutoAllocatePointerList<AstsTradingSessionStatusInfo>* GetAstsTradingSessionStatusInfoPool() {
		return this->m_astsTradingSessionStatus;
	}

	inline AstsHeartbeatInfo* GetFreeAstsHeartbeatInfo() {
		return this->m_cachedastsHeartbeatInfo;
	}

	inline AutoAllocatePointerList<AstsHeartbeatInfo>* GetAstsHeartbeatInfoPool() {
		return this->m_astsHeartbeat;
	}

	inline AstsIncrementalGenericInfo* GetFreeAstsIncrementalGenericInfo() {
		return this->m_cachedastsIncrementalGenericInfo;
	}

	inline AutoAllocatePointerList<AstsIncrementalGenericInfo>* GetAstsIncrementalGenericInfoPool() {
		return this->m_astsIncrementalGeneric;
	}

	inline AstsIncrementalMSRFONDInfo* GetFreeAstsIncrementalMSRFONDInfo() {
		return this->m_cachedastsIncrementalMSRFONDInfo;
	}

	inline AutoAllocatePointerList<AstsIncrementalMSRFONDInfo>* GetAstsIncrementalMSRFONDInfoPool() {
		return this->m_astsIncrementalMSRFOND;
	}

	inline AstsIncrementalMSRCURRInfo* GetFreeAstsIncrementalMSRCURRInfo() {
		return this->m_cachedastsIncrementalMSRCURRInfo;
	}

	inline AutoAllocatePointerList<AstsIncrementalMSRCURRInfo>* GetAstsIncrementalMSRCURRInfoPool() {
		return this->m_astsIncrementalMSRCURR;
	}

	inline AstsIncrementalOLRFONDInfo* GetFreeAstsIncrementalOLRFONDInfo() {
		return this->m_cachedastsIncrementalOLRFONDInfo;
	}

	inline AutoAllocatePointerList<AstsIncrementalOLRFONDInfo>* GetAstsIncrementalOLRFONDInfoPool() {
		return this->m_astsIncrementalOLRFOND;
	}

	inline AstsIncrementalOLRCURRInfo* GetFreeAstsIncrementalOLRCURRInfo() {
		return this->m_cachedastsIncrementalOLRCURRInfo;
	}

	inline AutoAllocatePointerList<AstsIncrementalOLRCURRInfo>* GetAstsIncrementalOLRCURRInfoPool() {
		return this->m_astsIncrementalOLRCURR;
	}

	inline AstsIncrementalTLRFONDInfo* GetFreeAstsIncrementalTLRFONDInfo() {
		return this->m_cachedastsIncrementalTLRFONDInfo;
	}

	inline AutoAllocatePointerList<AstsIncrementalTLRFONDInfo>* GetAstsIncrementalTLRFONDInfoPool() {
		return this->m_astsIncrementalTLRFOND;
	}

	inline AstsIncrementalTLRCURRInfo* GetFreeAstsIncrementalTLRCURRInfo() {
		return this->m_cachedastsIncrementalTLRCURRInfo;
	}

	inline AutoAllocatePointerList<AstsIncrementalTLRCURRInfo>* GetAstsIncrementalTLRCURRInfoPool() {
		return this->m_astsIncrementalTLRCURR;
	}

	inline void PrefetchAstsLogonInfo() {
		AstsLogonInfo *item = this->m_astsLogon->Start()->Data();
		for(int i = 0; i < sizeof(AstsLogonInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsLogoutInfo() {
		AstsLogoutInfo *item = this->m_astsLogout->Start()->Data();
		for(int i = 0; i < sizeof(AstsLogoutInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsGenericItemInfo() {
		AstsGenericItemInfo *item = this->m_astsGenericItems->Start()->Data();
		for(int i = 0; i < sizeof(AstsGenericItemInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsGenericInfo() {
		AstsGenericInfo *item = this->m_cachedastsGenericInfo;
		for(int i = 0; i < sizeof(AstsGenericInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsOLSFONDItemInfo() {
		AstsOLSFONDItemInfo *item = this->m_astsOLSFONDItems->Start()->Data();
		for(int i = 0; i < sizeof(AstsOLSFONDItemInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsOLSFONDInfo() {
		AstsOLSFONDInfo *item = this->m_cachedastsOLSFONDInfo;
		for(int i = 0; i < sizeof(AstsOLSFONDInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsOLSCURRItemInfo() {
		AstsOLSCURRItemInfo *item = this->m_astsOLSCURRItems->Start()->Data();
		for(int i = 0; i < sizeof(AstsOLSCURRItemInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsOLSCURRInfo() {
		AstsOLSCURRInfo *item = this->m_cachedastsOLSCURRInfo;
		for(int i = 0; i < sizeof(AstsOLSCURRInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsTLSFONDItemInfo() {
		AstsTLSFONDItemInfo *item = this->m_astsTLSFONDItems->Start()->Data();
		for(int i = 0; i < sizeof(AstsTLSFONDItemInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsTLSFONDInfo() {
		AstsTLSFONDInfo *item = this->m_cachedastsTLSFONDInfo;
		for(int i = 0; i < sizeof(AstsTLSFONDInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsTLSCURRItemInfo() {
		AstsTLSCURRItemInfo *item = this->m_astsTLSCURRItems->Start()->Data();
		for(int i = 0; i < sizeof(AstsTLSCURRItemInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsTLSCURRInfo() {
		AstsTLSCURRInfo *item = this->m_cachedastsTLSCURRInfo;
		for(int i = 0; i < sizeof(AstsTLSCURRInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsSecurityDefinitionGroupInstrAttribItemInfo() {
		AstsSecurityDefinitionGroupInstrAttribItemInfo *item = this->m_astsSecurityDefinitionGroupInstrAttribItems->Start()->Data();
		for(int i = 0; i < sizeof(AstsSecurityDefinitionGroupInstrAttribItemInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo() {
		AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo *item = this->m_astsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems->Start()->Data();
		for(int i = 0; i < sizeof(AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsSecurityDefinitionMarketSegmentGrpItemInfo() {
		AstsSecurityDefinitionMarketSegmentGrpItemInfo *item = this->m_astsSecurityDefinitionMarketSegmentGrpItems->Start()->Data();
		for(int i = 0; i < sizeof(AstsSecurityDefinitionMarketSegmentGrpItemInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsSecurityDefinitionInfo() {
		AstsSecurityDefinitionInfo *item = this->m_astsSecurityDefinition->Start()->Data();
		for(int i = 0; i < sizeof(AstsSecurityDefinitionInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsSecurityStatusInfo() {
		AstsSecurityStatusInfo *item = this->m_cachedastsSecurityStatusInfo;
		for(int i = 0; i < sizeof(AstsSecurityStatusInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsTradingSessionStatusInfo() {
		AstsTradingSessionStatusInfo *item = this->m_cachedastsTradingSessionStatusInfo;
		for(int i = 0; i < sizeof(AstsTradingSessionStatusInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsHeartbeatInfo() {
		AstsHeartbeatInfo *item = this->m_cachedastsHeartbeatInfo;
		for(int i = 0; i < sizeof(AstsHeartbeatInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsIncrementalGenericInfo() {
		AstsIncrementalGenericInfo *item = this->m_cachedastsIncrementalGenericInfo;
		for(int i = 0; i < sizeof(AstsIncrementalGenericInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsIncrementalMSRFONDInfo() {
		AstsIncrementalMSRFONDInfo *item = this->m_cachedastsIncrementalMSRFONDInfo;
		for(int i = 0; i < sizeof(AstsIncrementalMSRFONDInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsIncrementalMSRCURRInfo() {
		AstsIncrementalMSRCURRInfo *item = this->m_cachedastsIncrementalMSRCURRInfo;
		for(int i = 0; i < sizeof(AstsIncrementalMSRCURRInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsIncrementalOLRFONDInfo() {
		AstsIncrementalOLRFONDInfo *item = this->m_cachedastsIncrementalOLRFONDInfo;
		for(int i = 0; i < sizeof(AstsIncrementalOLRFONDInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsIncrementalOLRCURRInfo() {
		AstsIncrementalOLRCURRInfo *item = this->m_cachedastsIncrementalOLRCURRInfo;
		for(int i = 0; i < sizeof(AstsIncrementalOLRCURRInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsIncrementalTLRFONDInfo() {
		AstsIncrementalTLRFONDInfo *item = this->m_cachedastsIncrementalTLRFONDInfo;
		for(int i = 0; i < sizeof(AstsIncrementalTLRFONDInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

	inline void PrefetchAstsIncrementalTLRCURRInfo() {
		AstsIncrementalTLRCURRInfo *item = this->m_cachedastsIncrementalTLRCURRInfo;
		for(int i = 0; i < sizeof(AstsIncrementalTLRCURRInfo); i+= 64)
			__builtin_prefetch(((char*)item) + i, 0, _MM_HINT_T0);
	}

private:
	void ReleaseAstsLogonInfo() {
		static_cast<AstsLogonInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsLogoutInfo() {
		static_cast<AstsLogoutInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsGenericItemInfo() {
		static_cast<AstsGenericItemInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsGenericInfo() {
		static_cast<AstsGenericInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsOLSFONDItemInfo() {
		static_cast<AstsOLSFONDItemInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsOLSFONDInfo() {
		static_cast<AstsOLSFONDInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsOLSCURRItemInfo() {
		static_cast<AstsOLSCURRItemInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsOLSCURRInfo() {
		static_cast<AstsOLSCURRInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsTLSFONDItemInfo() {
		static_cast<AstsTLSFONDItemInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsTLSFONDInfo() {
		static_cast<AstsTLSFONDInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsTLSCURRItemInfo() {
		static_cast<AstsTLSCURRItemInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsTLSCURRInfo() {
		static_cast<AstsTLSCURRInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsSecurityDefinitionGroupInstrAttribItemInfo() {
		static_cast<AstsSecurityDefinitionGroupInstrAttribItemInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo() {
		static_cast<AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsSecurityDefinitionMarketSegmentGrpItemInfo() {
		static_cast<AstsSecurityDefinitionMarketSegmentGrpItemInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsSecurityDefinitionInfo() {
		static_cast<AstsSecurityDefinitionInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsSecurityStatusInfo() {
		static_cast<AstsSecurityStatusInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsTradingSessionStatusInfo() {
		static_cast<AstsTradingSessionStatusInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsHeartbeatInfo() {
		static_cast<AstsHeartbeatInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsIncrementalGenericInfo() {
		static_cast<AstsIncrementalGenericInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsIncrementalMSRFONDInfo() {
		static_cast<AstsIncrementalMSRFONDInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsIncrementalMSRCURRInfo() {
		static_cast<AstsIncrementalMSRCURRInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsIncrementalOLRFONDInfo() {
		static_cast<AstsIncrementalOLRFONDInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsIncrementalOLRCURRInfo() {
		static_cast<AstsIncrementalOLRCURRInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsIncrementalTLRFONDInfo() {
		static_cast<AstsIncrementalTLRFONDInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	void ReleaseAstsIncrementalTLRCURRInfo() {
		static_cast<AstsIncrementalTLRCURRInfo*>(this->LastDecodeInfo())->ReleaseUnused();
	}
	inline void ResetAsts() {
		if(this->m_templateId <= 2510) {
			if(this->m_templateId <= 2106) {
				if(this->m_templateId <= 2103) {
					if(this->m_templateId <= 2102) {
						if(this->m_templateId == 2101) {
							this->ReleaseAstsLogonInfo();
						}
						else { // 2102
							this->ReleaseAstsLogoutInfo();
						}
					}
					else {
						if(this->m_templateId == 2102) {
							this->ReleaseAstsLogoutInfo();
						}
						else { // 2103
							this->ReleaseAstsGenericInfo();
						}
					}
				}
				else {
					if(this->m_templateId <= 2104) {
						if(this->m_templateId == 2103) {
							this->ReleaseAstsGenericInfo();
						}
						else { // 2104
							this->ReleaseAstsIncrementalGenericInfo();
						}
					}
					else {
						if(this->m_templateId == 2104) {
							this->ReleaseAstsIncrementalGenericInfo();
						}
						else { // 2106
							this->ReleaseAstsSecurityStatusInfo();
						}
					}
				}
			}
			else {
				if(this->m_templateId <= 2108) {
					if(this->m_templateId <= 2107) {
						if(this->m_templateId == 2106) {
							this->ReleaseAstsSecurityStatusInfo();
						}
						else { // 2107
							this->ReleaseAstsTradingSessionStatusInfo();
						}
					}
					else {
						if(this->m_templateId == 2107) {
							this->ReleaseAstsTradingSessionStatusInfo();
						}
						else { // 2108
							this->ReleaseAstsHeartbeatInfo();
						}
					}
				}
				else {
					if(this->m_templateId <= 2115) {
						if(this->m_templateId == 2108) {
							this->ReleaseAstsHeartbeatInfo();
						}
						else { // 2115
							this->ReleaseAstsSecurityDefinitionInfo();
						}
					}
					else {
						if(this->m_templateId == 2115) {
							this->ReleaseAstsSecurityDefinitionInfo();
						}
						else { // 2510
							this->ReleaseAstsOLSFONDInfo();
						}
					}
				}
			}
		}
		else {
			if(this->m_templateId <= 2523) {
				if(this->m_templateId <= 2520) {
					if(this->m_templateId <= 2511) {
						if(this->m_templateId == 2510) {
							this->ReleaseAstsOLSFONDInfo();
						}
						else { // 2511
							this->ReleaseAstsTLSFONDInfo();
						}
					}
					else {
						if(this->m_templateId == 2511) {
							this->ReleaseAstsTLSFONDInfo();
						}
						else { // 2520
							this->ReleaseAstsIncrementalOLRFONDInfo();
						}
					}
				}
				else {
					if(this->m_templateId <= 2521) {
						if(this->m_templateId == 2520) {
							this->ReleaseAstsIncrementalOLRFONDInfo();
						}
						else { // 2521
							this->ReleaseAstsIncrementalTLRFONDInfo();
						}
					}
					else {
						if(this->m_templateId == 2521) {
							this->ReleaseAstsIncrementalTLRFONDInfo();
						}
						else { // 2523
							this->ReleaseAstsIncrementalMSRFONDInfo();
						}
					}
				}
			}
			else {
				if(this->m_templateId <= 3601) {
					if(this->m_templateId <= 3600) {
						if(this->m_templateId == 2523) {
							this->ReleaseAstsIncrementalMSRFONDInfo();
						}
						else { // 3600
							this->ReleaseAstsOLSCURRInfo();
						}
					}
					else {
						if(this->m_templateId == 3600) {
							this->ReleaseAstsOLSCURRInfo();
						}
						else { // 3601
							this->ReleaseAstsTLSCURRInfo();
						}
					}
				}
				else {
					if(this->m_templateId <= 3610) {
						if(this->m_templateId == 3601) {
							this->ReleaseAstsTLSCURRInfo();
						}
						else { // 3610
							this->ReleaseAstsIncrementalOLRCURRInfo();
						}
					}
					else {
						if(this->m_templateId <= 3611) {
							if(this->m_templateId == 3610) {
								this->ReleaseAstsIncrementalOLRCURRInfo();
							}
							else { // 3611
								this->ReleaseAstsIncrementalTLRCURRInfo();
							}
						}
						else {
							if(this->m_templateId == 3611) {
								this->ReleaseAstsIncrementalTLRCURRInfo();
							}
							else { // 3613
								this->ReleaseAstsIncrementalMSRCURRInfo();
							}
						}
					}
				}
			}
		}
	}
#pragma endregion

public:

    inline void* LastDecodeInfo() { return this->m_lastDecodedInfo; }
    inline void LastDecodeInfo(void *info) { this->m_lastDecodedInfo = info; }

#pragma region Core_Methods
    inline bool FastCompareString1(char *str1, char *str2) { return *str1 == *str2; }
    inline bool FastCompareString4(char *str1, char *str2) { return *((int*)str1) == *((int*)str2); }
    inline bool FastCompareString8(char *str1, char *str2) { return *((UINT64*)str1) == *((UINT64*)str2); }
    inline void ResetBuffer() { this->currentPos = this->buffer; }
    inline void SetNewBuffer(BYTE *buffer) {
        this->buffer = buffer;
        this->currentPos = buffer;
    }
    inline void SetNewBuffer(BYTE *buffer, int length) {
		this->buffer = buffer;
        __builtin_prefetch(buffer, 0, _MM_HINT_T0);
        for(int i = 64; i < length; i+= 64, buffer += 64)
            __builtin_prefetch(buffer, 0, _MM_HINT_T0);
        this->bufferLength = length;
        this->ResetBuffer();
    }
    inline void Prefetch(BYTE *buffer, int length) {
        __builtin_prefetch(buffer, 0, _MM_HINT_T0);
        for(int i = 64; i < length; i+= 64, buffer += 64)
            __builtin_prefetch(buffer, 0, _MM_HINT_T0);
    }
    inline void ClearBuffer() { memset(this->buffer, 0, this->bufferLength); }

    inline bool CheckBuffer(BYTE *arrayToCompare, int length) {
        int lengthInt = length / 4;
        for (int i = 0; i < lengthInt; i++)
            if (((int*)this->buffer)[i] != ((int*)arrayToCompare)[i])
                return false;
        for (int i = lengthInt * 4; i < length; i++)
            if (this->buffer[i] != arrayToCompare[i])
                return false;
        return true;
    }
    inline bool CheckBufferFromCurrent(BYTE *arrayToCompare, int length) { 
        int lengthInt = length / 4;
        for (int i = 0; i < lengthInt; i++)
            if (((int*)this->currentPos)[i] != ((int*)arrayToCompare)[i])
                return false;
        for (int i = lengthInt * 4; i < length; i++)
            if (this->currentPos[i] != arrayToCompare[i])
                return false;
        return true;
    }
    
    inline void WriteMsgSeqNumber(int msgSeqNumber) {
        *((int*)this->currentPos) = msgSeqNumber;
        this->currentPos += 4;
    }


    inline void WritePresenceMap1(UINT64 map) {
        *((UINT64*)this->currentPos) = map;
        this->currentPos++;
    }

    inline void WritePresenceMap2(UINT64 map) {
        *((UINT64*)this->currentPos) = map;
        this->currentPos+=2;
    }

    inline void WritePresenceMap3(UINT64 map) {
        *((UINT64*)this->currentPos) = map;
        this->currentPos+=3;
    }

    inline void WritePresenceMap4(UINT64 map) {
        *((UINT64*)this->currentPos) = map;
        this->currentPos+=4;
    }

    inline void WritePresenceMap5(UINT64 map) {
        *((UINT64*)this->currentPos) = map;
        this->currentPos+=5;
    }

    inline void WritePresenceMap6(UINT64 map) {
        *((UINT64*)this->currentPos) = map;
        this->currentPos+=6;
    }

    inline void WritePresenceMap7(UINT64 map) {
        *((UINT64*)this->currentPos) = map;
        this->currentPos+=7;
    }

    inline void WritePresenceMap8(UINT64 map) {
        *((UINT64*)this->currentPos) = map;
        this->currentPos+=8;
    }

    inline void WritePresenceMap(UINT64 map) {
        if(map < 0x0000000080000000) {
            if(map < 0x00008000) {
                if(map < 0x80) {
                    map |= 0x80;
                    WritePresenceMap1(map);
                }
                else {
                    map |= 0x8000;
                    WritePresenceMap2(map);
                }
            }
            else {
                if(map < 0x800000) {
                    map |= 0x800000;
                    WritePresenceMap3(map);
                }
                else {
                    map |= 0x80000000;
                    WritePresenceMap4(map);
                }
            }
        }
        else {
            if(map < 0x0000800000000000) {
                if(map < 0x0000008000000000) {
                    map |= 0x0000008000000000;
                    WritePresenceMap5(map);
                }
                else {
                    map |= 0x0000800000000000;
                    WritePresenceMap6(map);
                }
            }
            else {
                if(map < 0x0080000000000000) {
                    map |= 0x0080000000000000;
                    WritePresenceMap7(map);
                }
                else {
                    map |= 0x8000000000000000;
                    WritePresenceMap8(map);
                }
            }
        }
    }

    inline int ReadMsgSeqNumber() {
        int result = *(int*)this->currentPos;
        this->currentPos += 4;
        return result;
    }

	inline UINT32 ReadPacketTemplateId() {
		UINT32 result = *(UINT32*)this->currentPos;
		if((result & 0x8080) == 0x8000) {  // 2byte value
			this->currentPos += 2;
			return result & 0xffff;
		}
		this->currentPos ++;
		return result & 0xff;
	}

	inline UINT32 ParseHeaderFast() {
		UINT32 result = *(UINT32*)this->currentPos;

        UINT32 mask = 0xffff; mask >>= (result & 0x80) >> 4;
        this->m_presenceMap = result & mask;
        int count = 1 + (mask >> 15);
        result >>= 8 + ((mask & 0x8000) >> 12);

        result &= 0xffff;
        mask = 0xffff; mask >>= (result & 0x80) >> 4;

        count += 1 + (mask >> 15);
        this->currentPos += count;
        this->m_templateId = result & mask;
		return result;

        /*
        if((result & 0x80) != 0) {
			count = 1; this->m_presenceMap = result & 0x7f;
			result >>= 8;
		}
		else { // most probably 2 bytes
			count = 2; this->m_presenceMap = result & 0x7f7f;
			result >>= 16;
		}

        if((result & 0x8080) == 0x8000) {  // 2byte value
			this->currentPos += count + 2;
			result &= 0xffff;
			this->m_templateId = result;
			return result;
		}
		this->currentPos += count + 1;
		result &= 0xff;
		this->m_templateId = result;
		return result;
        */
	}

    inline void SkipMsgSeqNumber() {
        this->currentPos += 4;
    }

    inline UINT TemplateId() const { return this->m_templateId; }
    inline UINT64 PresenceMap() const { return this->m_presenceMap; }

    inline bool IsNull() const {  return *(this->currentPos) == 0x80; }

    void PrintTabs(int tabCount);
    void PrintPresenceMap(UINT64 map, int count, int tabsCount);
    void PrintXmlPresenceMap(UINT64 map, int count);
    void PrintXmlInt32(const char *name, int value);
    void PrintXmlUInt32(const char *name, UINT value);
    void PrintXmlInt64(const char *name, INT64 value);
    void PrintXmlUInt64(const char *name, UINT64 value);
    void PrintXmlItemBegin(const char *name);
    void PrintXmlItemEnd(const char *name);
    void PrintXmlItemBegin(const char *name, int index);
    void PrintXmlItemEnd(const char *name, int index);
    void PrintXmlString(const char *name, char *str, int count);
    void PrintXmlByteVector(const char *name, unsigned char *data, int count);
    void PrintXmlDecimal(const char *name, Decimal *value);
    bool BeginExportXml(const char *fileName);
    void EndExportXml();
    void PrintInt32(const char *name, int value, int tabCount);
    void PrintUInt32(const char *name, UINT value, int tabCount);
    void PrintInt64(const char *name, INT64 value, int tabCount);
    void PrintUInt64(const char *name, UINT64 value, int tabCount);
    void PrintItemBegin(const char *name, int index, int tabsCount);
    void PrintItemEnd(int tabsCount);
    void PrintString(const char *name, char *str, int count, int tabCount);
    void PrintByteVector(const char *name, unsigned char *data, int count, int tabCount);
    void PrintDecimal(const char *name, Decimal *value, int tabCount);

    inline void WriteNullString() {
        *(this->currentPos) = 0x00;
        *(this->currentPos + 1) = 0x80;
        this->currentPos += 2;
    }
    inline void WriteNull() {
        *(this->currentPos) = 0x80;
        this->currentPos++;
    }

    inline bool CheckProcessNullInt32() {
        if (*(this->currentPos) == 0x80) {
            this->currentPos++;
            return true;
        }
        return false;
    }
    inline bool CheckProcessNullUInt32() { 
        if (*(this->currentPos) == 0x80) {
            this->currentPos++;
            return true;
        }
        return false;
    }
    inline bool CheckProcessNullInt64() {
        if (*(this->currentPos) == 0x80) {
            this->currentPos++;
            return true;
        }
        return false;
    }
    inline bool CheckProcessNullUInt64() {
        if (*(this->currentPos) == 0x80) {
            this->currentPos++;
            return true;
        }
        return false;
    }
    inline bool CheckProcessNullString() {
        WORD str = *((WORD*)this->currentPos);
        //if (str == 0x0000)
        //  return false;
        if(str == 0x8000) {
            this->currentPos+=2;
            return true;
        }
        /*
        if ((str & 0xFF) == 0x00) {
            this->currentPos++;
            return true;
        }*/
        return false;
    }
    inline bool CheckProcessNullByteVector() {
        return CheckProcessNullUInt32();
    }
    inline bool CheckProcessNullDecimal() {
        return CheckProcessNullInt32();
    }

    void WriteInt32_Mandatory(INT32 value) {
        int encoded = 0;
        if (value >= 0) {

            encoded |= ((value & 0x7f) | 0x80);
            value >>= 7;

            if (value == 0) {
                if ((encoded & 0x40) != 0) {
                    encoded <<= 8;
                    *((int*)this->currentPos) = encoded;
                    this->currentPos += 2;
                    return;
                }
                else {
                    *((int*)this->currentPos) = encoded;
                    this->currentPos++;
                    return;
                }
            }

            encoded <<= 8;
            encoded |= value & 0x7f;
            value >>= 7;

            if (value == 0) {
                if ((encoded & 0x40) != 0) {
                    encoded <<= 8;
                    *((int*)this->currentPos) = encoded;
                    this->currentPos += 3;
                    return;
                }
                else {
                    *((int*)this->currentPos) = encoded;
                    this->currentPos += 2;
                    return;
                }
            }

            encoded <<= 8;
            encoded |= value & 0x7f;
            value >>= 7;

            if (value == 0) {
                if ((encoded & 0x40) != 0) {
                    encoded <<= 8;
                    *((int*)this->currentPos) = encoded;
                    this->currentPos += 4;
                    return;
                }
                else {
                    *((int*)this->currentPos) = encoded;
                    this->currentPos += 3;
                    return;
                }
            }

            encoded <<= 8;
            encoded |= value & 0x7f;
            value >>= 7;

            if (value == 0) {
                if ((encoded & 0x40) != 0) {
                    *(this->currentPos) = 0x00;
                    this->currentPos++;
                    *((int*)this->currentPos) = encoded;
                    this->currentPos += 4;
                    return;
                }
                else {
                    *((int*)this->currentPos) = encoded;
                    this->currentPos += 4;
                    return;
                }
            }

            if ((value & 0x40) != 0) { 
                *(this->currentPos) = 0x00;
                this->currentPos++;
            }

            *(this->currentPos) = value;
            this->currentPos++;

            *((int*)this->currentPos) = encoded;
            this->currentPos += 4;
        }
        else {
            encoded |= ((value & 0x7f) | 0x80);
            value >>= 7;

            if (value == 0xffffffff) {
                if ((encoded & 0x40) == 0) {
                    encoded <<= 8;
                    encoded |= 0x7f;
                    *((int*)this->currentPos) = encoded;
                    this->currentPos += 2;
                    return;
                }
                *((int*)this->currentPos) = encoded;
                this->currentPos++;
                return;
            }

            encoded <<= 8;
            encoded |= value & 0x7f;
            value >>= 7;

            if (value == 0xffffffff) {
                if ((encoded & 0x40) == 0) {
                    encoded <<= 8;
                    encoded |= 0x7f;
                    *((int*)this->currentPos) = encoded;
                    this->currentPos += 3;
                    return;
                }
                *((int*)this->currentPos) = encoded;
                this->currentPos += 2;
                return;
            }

            encoded <<= 8;
            encoded |= value & 0x7f;
            value >>= 7;

            if (value == 0xffffffff) {
                if ((encoded & 0x40) == 0) {
                    encoded <<= 8;
                    encoded |= 0x7f;
                    *((int*)this->currentPos) = encoded;
                    this->currentPos += 4;
                    return;
                }
                *((int*)this->currentPos) = encoded;
                this->currentPos += 3;
                return;
            }

            encoded <<= 8;
            encoded |= value & 0x7f;
            value >>= 7;

            if (value == 0xffffffff) {
                if ((encoded & 0x40) == 0) {
                    *this->currentPos = 0x7f;
                    this->currentPos++;
                    *((int*)this->currentPos) = encoded;
                    this->currentPos += 4;
                    return;
                }
                *((int*)this->currentPos) = encoded;
                this->currentPos += 4;
                return;
            }

            if ((value & 0x40) == 0) { 
                (*this->currentPos) = 0x7f;
                this->currentPos++;
            }
            *(this->currentPos) = (BYTE)(value & 0x7f);
            this->currentPos++;

            *((int*)this->currentPos) = encoded;
            this->currentPos += 4;
        }
    }
    void WriteInt32_Optional(INT32 value) {
        if (value >= 0)
            value++;
        WriteInt32_Mandatory(value);
    }
    void WriteUInt32_Mandatory(UINT32 value) {
        UINT encoded = 0;

        encoded |= ((value & 0x7f) | 0x80);
        value >>= 7;

        if (value == 0) {
            *((int*)this->currentPos) = encoded;
            this->currentPos++;
            return;
        }

        encoded <<= 8;
        encoded |= value & 0x7f;
        value >>= 7;

        if (value == 0) {
            *((int*)this->currentPos) = encoded;
            this->currentPos += 2;
            return;
        }

        encoded <<= 8;
        encoded |= value & 0x7f;
        value >>= 7;

        if (value == 0) {
            *((int*)this->currentPos) = encoded;
            this->currentPos += 3;
            return;
        }

        encoded <<= 8;
        encoded |= value & 0x7f;
        value >>= 7;

        if (value == 0) {
            *((int*)this->currentPos) = encoded;
            this->currentPos += 4;
            return;
        }

        *(this->currentPos) = value;
        this->currentPos++;

        *((int*)this->currentPos) = encoded;
        this->currentPos += 4;
    }
    void WriteUInt32_Optional(UINT32 value) {
        value++;
        WriteUInt32_Mandatory(value);
    }

	void WriteInt64_Optional(INT64 value) {
		if (value > 0)
			value++;
		WriteInt64_Mandatory(value);
	}
	void WriteInt64_Mandatory(INT64 value) {
		INT64 encoded = 0;
		INT32 encoded2;
		if (value >= 0) {
			encoded |= ((value & 0x7f) | 0x80);
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 2;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos++;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 3;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 2;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 4;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 3;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 5;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 4;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 6;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 5;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 7;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 6;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					encoded <<= 8;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 7;
					return;
				}
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0) {
				if ((encoded & 0x40) != 0) {
					*((INT64*)this->currentPos) = 0x00;
					this->currentPos++;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
			}

			encoded2 = value & 0x7f;
			value >>= 7;
			if (value == 0) {
				if ((encoded2 & 0x40) != 0) {
					encoded2 <<= 8;
					*((INT32*)(this->currentPos)) = encoded2;
					this->currentPos += 2;

					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
				else {
					*((INT32*)(this->currentPos)) = encoded2;
					this->currentPos++;

					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
			}

			encoded2 <<= 8;
			encoded2 |= value & 0x7f;

			*((INT32*)(this->currentPos)) = encoded2;
			this->currentPos += 2;

			*((INT64*)this->currentPos) = encoded;
			this->currentPos += 8;
		}
		else {
			encoded |= ((value & 0x7f) | 0x80);
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 2;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos++;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 3;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos += 2;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 4;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos += 3;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 5;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos += 4;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 6;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos += 5;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 7;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos += 6;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					encoded <<= 8;
					encoded |= 0x7f;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos += 7;
				return;
			}

			encoded <<= 8;
			encoded |= value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded & 0x40) == 0) {
					(*this->currentPos) = 0x7f;
					this->currentPos++;
					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
				*((INT64*)this->currentPos) = encoded;
				this->currentPos += 8;
				return;
			}

			encoded2 = value & 0x7f;
			value >>= 7;

			if (value == 0xffffffffffffffff) {
				if ((encoded2 & 0x40) == 0) {
					encoded2 <<= 8;
					encoded2 |= 0x7f;

					*((INT64*)this->currentPos) = encoded2;
					this->currentPos += 2;

					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
				else {
					*((INT64*)this->currentPos) = encoded2;
					this->currentPos++;

					*((INT64*)this->currentPos) = encoded;
					this->currentPos += 8;
					return;
				}
			}

			encoded2 <<= 8;
			encoded2 |= value & 0x7f;

			*((INT64*)this->currentPos) = encoded2;
			this->currentPos += 2;

			*((INT64*)this->currentPos) = encoded;
			this->currentPos += 8;
			return;
		}
	}
	void WriteUInt64_Optional(UINT64 value) {
		value++;
		WriteUInt64_Mandatory(value);
	}
	void WriteUInt64_Mandatory(UINT64 value) {
		UINT64 encoded = 0;
		UINT encoded2;

		encoded |= ((value & 0x7f) | 0x80);
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos++;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos += 2;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos += 3;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos += 4;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos += 5;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos += 6;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos += 7;
			return;
		}

		encoded <<= 8;
		encoded |= value & 0x7f;
		value >>= 7;

		if (value == 0) {
			*((UINT64*)this->currentPos) = encoded;
			this->currentPos += 8;
			return;
		}

		encoded2 = value & 0x7f;
		value >>= 7;
		if (value == 0) {
			*((UINT*)this->currentPos) = encoded2;
			this->currentPos ++;
			*((UINT64*)this->currentPos) = encoded;
			return;
		}

		encoded2 <<= 8;
		encoded2 |= value;

		*((UINT*)this->currentPos) = encoded2;
		this->currentPos +=2;
		*((UINT64*)this->currentPos) = encoded;
		return;
	}

    __attribute_noinline__
    INT64 ReadInt64_Mandatory_Full() {
        INT64 result = 0;
        __int128 memory = *((__int128 *) (this->currentPos));

        unsigned char valueMasked = memory & 0xff;
        int addLength = (valueMasked == 0x00) || (valueMasked == 0x7f);
        memory >>= (addLength << 3);
        UINT64 mask = 0 - ((valueMasked == 0x7f) || ((valueMasked & 0x40) != 0));
        result = mask & 0xffffffffffffff80;

        unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080808080);
        if(count == 64) {
            addLength += 8;
            for(count = 0; count < 8; count++) {
                result |= memory & 0x7f;
                memory >>= 8;
                result <<= 7;
            }
            count = my_tzcnt_u64(memory & 0x80808080);

        }
        count++;
        count >>= 3;
        this->currentPos += addLength + count;

        while(true) {
            result |= memory & 0x7f;
            count--;
            if(count == 0)
                return result;
            memory >>= 8;
            result <<= 7;
        }
        return result;
    }

#ifdef ALLOW_BMI
    inline UINT64 my_tzcnt_u64(UINT64 x) {
        UINT64 result;
        __asm__ ("tzcntq %1, %0" : "=r" (result) : "r" (x));
        return result;
    }
    inline UINT64 my_pext_u64(UINT64 x, UINT64 mask) {
        UINT64 result;
        __asm__ ("pext %2, %1, %0" : "=r" (result) : "r" (x), "r" (mask));
        return result;
    }
	__attribute__((__always_inline__, __nodebug__, __target__("bmi2")))
    inline INT32 ReadInt32_Mandatory_BMI() {
        UINT64 memory = *((UINT64 *) (this->currentPos));

        UINT64 result = memory & 0xff;
        int addLength = (result == 0x00) || (result == 0x7f);
        memory >>= addLength << 3;
        result = 0 - ((result == 0x7f) || ((result & 0x40) != 0));

        unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080) + 1;
        memory = __bswap_64(memory);
        memory >>= (64 - count);
        result <<= count - (count >> 3);
        result |= my_pext_u64(memory, 0x7f7f7f7f7f);
        this->currentPos += addLength + (count >> 3);
        return (INT32)result;
    }
    inline INT32 ReadInt32_Mandatory_Predict1_BMI() {
        return ReadInt32_Mandatory_BMI();
    }
    inline INT32 ReadInt32_Optional_BMI() {
        INT32 result = ReadInt32_Mandatory_BMI();
        result = result + ((((UINT32)result) >> 31) - 1);
        return result;
    }
	__attribute__((__always_inline__, __nodebug__, __target__("bmi2")))
    inline bool ReadInt32_Optional_BMI(INT32 *value) {
        UINT64 memory = *((UINT64*)(this->currentPos));
        if((memory & 0xff) == 0x80) {
            this->currentPos++;
            return false;
        }
        UINT64 result = memory & 0xff;
        int addLength = (result == 0x00) || (result == 0x7f);
        memory >>= addLength << 3;
        result = 0 - ((result == 0x7f) || ((result & 0x40) != 0));

        unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080) + 1;
        memory = __bswap_64(memory);
        memory >>= (64 - count);
        result <<= count - (count >> 3);
        result |= my_pext_u64(memory, 0x7f7f7f7f7f);
        this->currentPos += addLength + (count >> 3);
        *value = (INT32)result + ((((UINT32)result) >> 31) - 1);
        return true;
    }
    inline bool ReadInt32_Optional_Predict1_BMI(INT32 *value) {
		UINT64 memory = *((UINT64*)(this->currentPos));
		if((memory & 0xff) == 0x80) {
			this->currentPos++;
			return false;
		}
		UINT32 result = memory & 0xff;
		int addLength = (result == 0x00) || (result == 0x7f);
		memory >>= addLength << 3;
		result = 0 - ((result == 0x7f) || ((result & 0x40) != 0));
		result <<= 7;
        result |= memory & 0x7f;
		*value = result + ((result >> 31) - 1);
		this->currentPos += addLength + 1;
		return true;
    }
    inline UINT32 ReadUInt32_Mandatory_Fixed1_BMI() {
        UINT32 memory = *((UINT32*)(this->currentPos));
        this->currentPos++;
        return memory & 0x7f;
    }
    inline UINT32 ReadUInt32_Mandatory_Predict1_BMI() {
        return ReadUInt32_Mandatory_BMI();
    }
	__attribute__((__always_inline__, __nodebug__, __target__("bmi2")))
    inline UINT32 ReadUInt32_Mandatory_Predict12_BMI() {
		UINT64 memory = *((UINT64 *) (this->currentPos));

		unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080) + 1;
		memory = __bswap_64(memory);
		memory >>= (64 - count);
		this->currentPos += count >> 3;
		return (UINT32)my_pext_u64(memory, 0x7f7f7f7f7f);
    }
	__attribute__((__always_inline__, __nodebug__, __target__("bmi2")))
    inline UINT32 ReadUInt32_Mandatory_BMI() {
        UINT64 memory = *((UINT64 *) (this->currentPos));

        unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080) + 1;
        memory = __bswap_64(memory);
        memory >>= (64 - count);
        this->currentPos += count >> 3;
        return (UINT32)my_pext_u64(memory, 0x7f7f7f7f7f);
    }
	__attribute__((__always_inline__, __nodebug__, __target__("bmi2")))
    inline UINT32 ReadUInt32_Optional_BMI() {
        UINT64 memory = *((UINT64 *) (this->currentPos));

        unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080) + 1;
        memory = __bswap_64(memory);
        memory >>= (64 - count);
        this->currentPos += count >> 3;
        return (UINT32)(my_pext_u64(memory, 0x7f7f7f7f7f) - 1);
    }
    inline UINT32 ReadUInt32_Optional_Fixed1_BMI() {
        return ReadUInt32_Mandatory_Fixed1_BMI() - 1;
    }
    inline UINT32 ReadUInt32_Optional_Predict1_BMI() {
        return ReadUInt32_Mandatory_Predict1_BMI() - 1;
    }
	__attribute__((__always_inline__, __nodebug__, __target__("bmi2")))
    inline bool ReadUInt32_Optional_BMI(UINT32 *value) {
        UINT64 memory = *((UINT64*)(this->currentPos));
        if((memory & 0xff) == 0x80) {
            this->currentPos++;
            return false;
        }
        unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080) + 1;
        memory = __bswap_64(memory);
        memory >>= (64 - count);
        this->currentPos += count >> 3;
        *value = (UINT32)(my_pext_u64(memory, 0x7f7f7f7f7f) - 1);
        return true;
    }
    inline bool ReadUInt32_Optional_Fixed1_BMI(UINT32 *result) {
        UINT32 val = (UINT32)*(this->currentPos) & 0x7f;
        this->currentPos++;
        (*result) = val - 1;
        return val > 0;
    }
    inline bool ReadUInt32_Optional_Predict1_BMI(UINT32 *value) {
        return ReadUInt32_Optional_BMI(value);
    }
    inline bool ReadUInt32_Optional_Predict12_BMI(UINT32 *value) {
        return ReadUInt32_Optional_BMI(value);
    }
    __attribute__((__always_inline__, __nodebug__, __target__("bmi2")))
    inline UINT64 ReadUInt64_Mandatory_BMI() {
        UINT64 result = 0;
        UINT64 memory = *((UINT64 *) (this->currentPos));

        unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080808080) + 1;
        int addLength = 0;
        if(count == 65) {
            addLength = 8;
            memory = __bswap_64(memory);
            result = (UINT64)my_pext_u64(memory, 0x7f7f7f7f7f7f7f7f);
            memory = *((UINT64 *) (this->currentPos + 8));
            count = my_tzcnt_u64(memory & 0x80808080) + 1;
            result <<= count - (count >> 3);
        }
        memory = __bswap_64(memory);
        memory >>= (64 - count);
        result |= (UINT64)my_pext_u64(memory, 0x7f7f7f7f7f7f7f7f);
        this->currentPos += addLength + (count >> 3);
        return result;
    }
    __attribute__((__always_inline__, __nodebug__, __target__("bmi2")))
    inline UINT64 ReadUInt64_Optional_BMI() {
        return ReadUInt64_Mandatory_BMI() - 1;
    }
    __attribute__((__always_inline__, __nodebug__, __target__("bmi2")))
    inline INT64 ReadInt64_Mandatory_BMI() {
        UINT64 memory = *((UINT64*) (this->currentPos));

        UINT64 result = memory & 0xff;
        int addLength = (result == 0x00) || (result == 0x7f);
        memory >>= addLength << 3;
        result = 0 - ((result == 0x7f) || ((result & 0x40) != 0));

        unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080808080) + 1;
        if(count == 65)
            return ReadInt64_Mandatory_Full();

        memory = __bswap_64(memory);
        memory >>= (64 - count);
        result <<= (count - (count >> 3));
		result |= my_pext_u64(memory, 0x7f7f7f7f7f7f7f7f);

        this->currentPos += addLength + (count >> 3);
        return (INT64)result;
    }
    inline INT64 ReadInt64_Optional_BMI() {
        INT64 value = ReadInt64_Mandatory_BMI();
        return value + ((((UINT64)value) >> 63) - 1);
    }
    // for decima exponent we use predict 1 because power of 10 will fit almost always in one byte
    inline bool ReadDecimal_Optional_BMI(Decimal *value) {
        if(!ReadInt32_Optional_Predict1_BMI(&(value->Exponent)))
            return false;
        value->Mantissa = ReadInt64_Mandatory_BMI();
        return true;
    }
    inline void ReadDecimal_Mandatory_BMI(Decimal *value) {
        value->Exponent = ReadInt32_Mandatory_Predict1_BMI();
        value->Mantissa = ReadInt64_Mandatory_BMI();
    }
#endif

#ifdef ALLOW_SIMPLE
    inline INT32 ReadInt32_Mandatory_Simple() {
		INT32 result = 0;
		UINT64 memory = *((UINT64 *) (this->currentPos));

		unsigned char valueMasked = memory & 0xff;
		int addLength = (valueMasked == 0x00) || (valueMasked == 0x7f);
		memory >>= (addLength << 3);
		UINT32 mask = 0 - ((valueMasked == 0x7f) || ((valueMasked & 0x40) != 0));
		result = mask & 0xffffff80;

        unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080808080);
        count++;
        count >>= 3;
		this->currentPos += addLength + count;

		while(true) {
			result |= memory & 0x7f;
			count--;
			if(count == 0)
				return result;
			memory >>= 8;
			result <<= 7;
		}
		return result;
	}
    inline INT32 ReadInt32_Mandatory_Predict1_Simple() {
		return ReadInt32_Mandatory_Simple();
	}
	inline INT32 ReadInt32_Optional_Simple() {
        INT32 result = ReadInt32_Mandatory_Simple();
        result = result + ((((UINT32)result) >> 31) - 1);
        return result;
    }
	inline bool ReadInt32_Optional_Simple(INT32 *value) {
		INT32 result = 0;
		UINT64 memory = *((UINT64*)(this->currentPos));
		if((memory & 0xff) == 0x80) {
			this->currentPos++;
			return false;
		}

		unsigned char valueMasked = memory & 0xff;
		int addLength = (valueMasked == 0x00) || (valueMasked == 0x7f);
		memory >>= (addLength << 3);
		UINT32 mask = 0 - ((valueMasked == 0x7f) || ((valueMasked & 0x40) != 0));
		result = mask & 0xffffff80;

		unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080808080);
		count++;
		count >>= 3;
		this->currentPos += addLength + count;

		while(true) {
			result |= memory & 0x7f;
			count--;
			if(count == 0)
				break;
			memory >>= 8;
			result <<= 7;
		}
		*value = result + ((((UINT32)result) >> 31) - 1);
		return true;
	}
	inline bool ReadInt32_Optional_Predict1_Simple(INT32 *value) {
		return ReadInt32_Optional_Simple(value);
	}
    inline UINT32 ReadUInt32_Mandatory_Fixed1_Simple() {
		UINT32 memory = *((UINT32*)(this->currentPos));
		this->currentPos++;
		return memory & 0x7f;
	}
    inline UINT32 ReadUInt32_Mandatory_Predict1_Simple() {
		return ReadUInt32_Mandatory_Simple();
	}
	inline UINT32 ReadUInt32_Mandatory_Predict12_Simple() {
		UINT32 memory = *((UINT32 *) (this->currentPos));
		if((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
			ProgramStatistics::Total->Inc(Counters::cReadUInt32Mandatory_1Byte);
#endif
			this->currentPos++;
			return memory & 0x7f;
		}
#ifdef COLLECT_STATISTICS_FAST
		ProgramStatistics::Total->Inc(Counters::cReadUInt32Mandatory_2Byte);
#endif
		this->currentPos += 2;
		UINT32 result = memory & 0x7f;
		memory >>= 8;
		result <<= 7;
		result |= memory & 0x7f;
		return result;
	}
    inline UINT32 ReadUInt32_Mandatory_Simple() {
        UINT32 result = 0;
        UINT64 memory = *((UINT64*)(this->currentPos));

		unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080808080);
		count++;
		count >>= 3;
		this->currentPos += count;

		while(true) {
			result |= memory & 0x7f;
			count--;
			if(count == 0)
				return result;
			memory >>= 8;
			result <<= 7;
		}
		return result;
    }
    inline UINT32 ReadUInt32_Optional_Simple() {
        UINT32 result = 0;
        UINT64 memory = *((UINT64*)(this->currentPos));

        unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080);
        count++;
        count >>= 3;
        this->currentPos += count;

        while(true) {
            result |= memory & 0x7f;
            count--;
            if(count == 0)
                break;
            memory >>= 8;
            result <<= 7;
        }
        return result - 1;
    }
    inline UINT32 ReadUInt32_Optional_Fixed1_Simple() {
		return ReadUInt32_Mandatory_Fixed1_Simple() - 1;
	}
    inline UINT32 ReadUInt32_Optional_Predict1_Simple() {
        return ReadUInt32_Mandatory_Predict1_Simple() - 1;
    }
    inline bool ReadUInt32_Optional_Simple(UINT32 *value) {
        UINT32 result = 0;
        UINT64 memory = *((UINT64*)(this->currentPos));
        if((memory & 0xff) == 0x80) {
            this->currentPos++;
            return false;
        }
        unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080);
        count++;
        count >>= 3;
        this->currentPos += count;

        while(true) {
            result |= memory & 0x7f;
            count--;
            if(count == 0)
                break;
            memory >>= 8;
            result <<= 7;
        }
        *value = result - 1;
        return true;
    }
    inline bool ReadUInt32_Optional_Fixed1_Simple(UINT32 *result) {
        UINT32 val = (UINT32)*(this->currentPos) & 0x7f;
        this->currentPos++;
        (*result) = val - 1;
        return val > 0;
    }
    inline bool ReadUInt32_Optional_Predict1_Simple(UINT32 *value) {
		UINT32 result = 0;
		UINT64 memory = *((UINT64*)(this->currentPos));
		if((memory & 0xff) == 0x80) {
			this->currentPos++;
			return false;
		}
        unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080);
        count++;
        count >>= 3;
        this->currentPos += count;

        while(true) {
            result |= memory & 0x7f;
            count--;
            if(count == 0)
                break;
            memory >>= 8;
            result <<= 7;
        }
        *value = result - 1;
        return true;
	}
	inline bool ReadUInt32_Optional_Predict12_Simple(UINT32 *value) {
		UINT64 memory = *((UINT64 *) (this->currentPos));
		if((memory & 0xff) == 0x80) {
			this->currentPos++;
			return false;
		}
		if((memory & 0x80) == 0x80) { // one byte
#ifdef COLLECT_STATISTICS_FAST
			ProgramStatistics::Total->Inc(Counters::cReadUInt32Mandatory_1Byte);
#endif
			this->currentPos++;
			*value = (memory & 0x7f) - 1;
			return true;
		}
#ifdef COLLECT_STATISTICS_FAST
		ProgramStatistics::Total->Inc(Counters::cReadUInt32Mandatory_2Byte);
#endif
		this->currentPos += 2;
		UINT32 result = memory & 0x7f;
		memory >>= 8;
		result <<= 7;
		result |= memory & 0x7f;
		*value = result - 1;
		return true;
	}
    inline UINT64 ReadUInt64_Mandatory_Simple() {
        UINT64 result = 0;
        __int128 memory = *((__int128 *) (this->currentPos));

        if ((memory & 0x80) != 0) {
            this->currentPos++;
            return result;
        }

        unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080808080);
        int addLength = 0;
        if(count == 64) {
            addLength += 8;
            for(count = 0; count < 8; count++) {
                result |= memory & 0x7f;
                memory >>= 8;
                result <<= 7;
            }
            count = my_tzcnt_u64(memory & 0x80808080);

        }
        count++;
        count >>= 3;
        this->currentPos += addLength + count;

        while(true) {
            result |= memory & 0x7f;
            count--;
            if(count == 0)
                return result;
            memory >>= 8;
            result <<= 7;
        }
        return result;
    }
    inline UINT64 ReadUInt64_Optional_Simple() {
        return ReadUInt64_Mandatory_Simple() - 1;
    }
	inline INT64 ReadInt64_Mandatory_Simple() {
		INT64 result = 0;
		UINT64 memory = *((UINT64*) (this->currentPos));

		unsigned char valueMasked = memory & 0xff;
		int addLength = (valueMasked == 0x00) || (valueMasked == 0x7f);
		memory >>= (addLength << 3);
		UINT64 mask = 0 - ((valueMasked == 0x7f) || ((valueMasked & 0x40) != 0));
		result = mask & 0xffffffffffffff80;

		unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080808080);
		if(count == 64)
			return ReadInt64_Mandatory_Full();

		count++;
		count >>= 3;
		this->currentPos += addLength + count;

		while(true) {
			result |= memory & 0x7f;
			count--;
			if(count == 0)
				return result;
			memory >>= 8;
			result <<= 7;
		}
		return result;
	}
    inline INT64 ReadInt64_Optional_Simple() {
        INT64 value = ReadInt64_Mandatory_Simple();
        return value + ((((UINT64)value) >> 63) - 1);
    }
    // for decima exponent we use predict 1 because power of 10 will fit almost always in one byte
    inline bool ReadDecimal_Optional_Simple(Decimal *value) {
        if(!ReadInt32_Optional_Predict1_Simple(&(value->Exponent)))
            return false;
        value->Mantissa = ReadInt64_Mandatory_Simple();
        return true;
    }
    inline void ReadDecimal_Mandatory_Simple(Decimal *value) {
        value->Exponent = ReadInt32_Mandatory_Predict1_Simple();
        value->Mantissa = ReadInt64_Mandatory_Simple();
    }
#endif

    inline void WriteDecimal_Optional(Decimal *value) {
        WriteInt32_Optional(value->Exponent);
        WriteInt64_Mandatory(value->Mantissa);
        return;
    }
    inline void WriteDecimal_Mandatory(Decimal *value) {
        WriteInt32_Mandatory(value->Exponent);
        WriteInt64_Mandatory(value->Mantissa);
        return;
    }

    inline void WriteString_Optional(char *str, int length) { 
        if(0 == str) {
            *(this->currentPos) = 0x80;
            this->currentPos++;
            return;
        }
        if (length == 0) {
            *((int*)this->currentPos) = 0x8000;
            this->currentPos += 2;
            return;
        }
        memcpy(this->currentPos, str, length);
        this->currentPos[length - 1] |= 0x80;
        this->currentPos += length;
    }
    inline void WriteString_Mandatory(char *str, int length) {
        if(0 == str || length == 0) {
            *((int*)this->currentPos) = 0x80;
            this->currentPos ++;
            return;
        }
        memcpy(this->currentPos, str, length);
        this->currentPos[length - 1] |= 0x80;
        this->currentPos += length;
    }

    inline void WriteString_Optional(const char *str, int length) {
        if (str == NULL) {
            *(this->currentPos) = 0x80;
            this->currentPos++;
        }
        else if (length == 0) {
            *((int*)this->currentPos) = 0x8000;
            this->currentPos += 2;
            return;
        }
        memcpy(this->currentPos, str, length);
        this->currentPos[length - 1] |= 0x80;
        this->currentPos += length;
    }
    inline void WriteString_Mandatory(const char *str, int length) {
        if (length == 0) {
            *((int*)this->currentPos) = 0x80;
            this->currentPos ++;
            return;
        }
        memcpy(this->currentPos, str, length);
        this->currentPos[length - 1] |= 0x80;
        this->currentPos += length;
    }

    inline void CopyToBuffer(BYTE *value, int length) {
        memcpy(this->buffer, value, length);
    }

	inline void CopyString_Fixed1(char *dst, char *src) {
		(*dst) = (*src);
	}
	inline void CopyString_Fixed4(char *dst, char *src) {
		*((UINT32*)dst) = *((UINT32*)src);
	}
	inline void CopyString_Predict12(char *dst, char *src) {
		*((UINT32*)dst) = *((UINT32*)src);
	}
	inline void CopyString_PredictMax16(char *dst, char *src) {
		*((UINT64*)dst) = *((UINT64*)src);
		*((UINT64*)(dst + 8)) = *((UINT64*)(src + 8));
	}
    inline void CopyString(char *dst, char *src, int count) {
		while(count >= 8) {
            *((UINT64*)dst) = *((UINT64*)src);
            count -= 8;
            dst += 8; src += 8;
        }
        if(count >= 4) {
            *((UINT32*)dst) = *((UINT32*)src);
            count -= 4;
            dst += 4; src += 4;
        }
        if(count >= 2) {
            *((unsigned short*)dst) = *((unsigned short*)src);
            count -= 2;
            dst += 2; src += 2;
        }
        if(count > 0)
            *dst = *src;
    }

	inline void SkipToNextField() {
		UINT64 memory = *((UINT64*)this->currentPos);
		UINT64 memory2 = *((UINT64*)(this->currentPos + 8));
		unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080808080);
		unsigned long long int count2 = my_tzcnt_u64(memory2 & 0x8080808080808080);
		int length = ((count + 1) >> 3) + (((count2 + 1) >> 3) & (0 - (count >> 6)));
		this->currentPos += length;
	}

	inline bool ReadString_Optional_Fixed1(char *str) {
		UINT64 memory = *((UINT64*)this->currentPos);
		if((memory & 0x80) != 0) {
			*str = (char)(memory & 0x7f);
			this->currentPos++;
            return true;
		}
		this->currentPos += 2;
		return false;
    }
	inline bool ReadString_Optional_Fixed4(char *str) {
		UINT64 memory = *((UINT64*)this->currentPos);
		if((memory & 0xffff) == 0x8000) {
			this->currentPos += 2;
			return false;
		}
		*((UINT32*)str) = (UINT32)(memory & 0x7fffffff);
		this->currentPos += 4;
		return true;
	}

	inline bool ReadString_Optional_Predict12(char *str, int *lengthAddress) {
		UINT64 memory = *((UINT64*)this->currentPos);

		if((memory & 0x80) != 0) {
			*str = (char)(memory & 0x7f);
			*lengthAddress = 1;
			this->currentPos++;
            return true;
		}
		else if((memory & 0xffff) == 0x8000) {
			*lengthAddress = 0;
			this->currentPos += 2;
			return false;
		}
		else {
			*((unsigned short*)str) = memory & 0x7fff;
			*lengthAddress = 2;
			this->currentPos += 2;
            return true;
		}
	}
    inline bool ReadString_Optional_PredictMax8(char *str, int *lengthAddress) {
        UINT64 memory = *((UINT64*)this->currentPos);
        if ((memory & 0xffff) == 0x8000) {
            *lengthAddress = 0;
            this->currentPos += 2;
            return false;
        }
        unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080808080);
        *((UINT64*)str) = memory & 0x7f7f7f7f7f7f7f7f;
        int length = (count + 1) >> 3;
        *lengthAddress = length;
        this->currentPos += length;
        return true;
    }
    inline bool ReadString_Optional_PredictMax16(char *str, int *lengthAddress) {
        UINT64 memory = *((UINT64*)this->currentPos);
        UINT64 memory2 = *((UINT64*)(this->currentPos + 8));
        if ((memory & 0xffff) == 0x8000) {
            *lengthAddress = 0;
            this->currentPos += 2;
            return false;
        }
        unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080808080);
        unsigned long long int count2 = my_tzcnt_u64(memory2 & 0x8080808080808080);
        *((UINT64*)str) = memory & 0x7f7f7f7f7f7f7f7f;
        *((UINT64*)(str + 8)) = memory2 & 0x7f7f7f7f7f7f7f7f;
        int length = ((count + 1) >> 3) + (((count2 + 1) >> 3) & (0 - (count >> 6)));
        *lengthAddress = length;
        this->currentPos += length;
        return true;
    }
    inline bool ReadString_Optional(char *str, int *lengthAddress) {
        UINT64 memory = *((UINT64*)this->currentPos);
        int length = 0;
        if ((memory & 0xffff) == 0x8000) { 
            *lengthAddress = 0;
            this->currentPos += 2;
            return false;
        }

        while (true) {
            unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080808080);
            if (count != 64) {
				count++; count >>= 3;
				if(count <= 4)
					*((UINT32*)str) = memory & 0x7f7f7f7f;
				else
					*((UINT64*)str) = memory & 0x7f7f7f7f7f7f7f7f;
				length += count;
				*lengthAddress = length;
				this->currentPos += count;
            	return true;
			}
            *((UINT64*)str) = memory;
            str += 8;
            length += 8;
            this->currentPos += 8;
            memory = *((UINT64*)this->currentPos);
        }
    }

	inline void ReadString_Mandatory_Fixed1(char *str) {
		unsigned char memory = *(this->currentPos);
        this->currentPos ++;
		*str = (char)(memory & 0x7f);
	}
	inline void ReadString_Mandatory_Fixed4(char *str) {
		UINT32 memory = *((UINT32*)this->currentPos);
		if ((memory & 0x80) == 0x80) {
			this->currentPos ++;
			return;
		}
		*((UINT32*)str) = memory & 0x7fffffff;
		this->currentPos += 4;
	}
    inline void ReadString_Mandatory_PredictMax16(char *str, int *lengthAddress) {
        UINT64 memory = *((UINT64*)this->currentPos);
        UINT64 memory2 = *((UINT64*)(this->currentPos + 8));
        if ((memory & 0xff) == 0x80) {
            *lengthAddress = 0;
            this->currentPos ++;
            return;
        }
        unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080808080);
        unsigned long long int count2 = my_tzcnt_u64(memory2 & 0x8080808080808080);
        *((UINT64*)str) = memory & 0x7f7f7f7f7f7f7f7f;
        *((UINT64*)(str + 8)) = memory2 & 0x7f7f7f7f7f7f7f7f;
        int length = ((count + 1) >> 3) + (((count2 + 1) >> 3) & (0 - (count >> 6)));
        *lengthAddress = length;
        this->currentPos += length;
        return;
    }
	inline void ReadString_Mandatory(char *str, int *lengthAddress) {
        UINT64 memory = *((UINT64*)this->currentPos);
        int length = 0;
        if ((memory & 0xff) == 0x80) {
            *lengthAddress = 0;
            this->currentPos ++;
            return;
        }
		while (true) {
			unsigned long long int count = my_tzcnt_u64(memory & 0x8080808080808080);
			if (count != 64) {
				count++; count >>= 3;
				if(count <= 4)
					*((UINT32*)str) = memory & 0x7f7f7f7f;
				else
					*((UINT64*)str) = memory & 0x7f7f7f7f7f7f7f7f;
				length += count;
				*lengthAddress = length;
				this->currentPos += count;
				return;
			}
			*((UINT64*)str) = memory;
			str += 8;
			length += 8;
			this->currentPos += 8;
			memory = *((UINT64*)this->currentPos);
		}
    }

    inline void ReadByteVector_Optional(BYTE *vecPtrAddress, int *lengthAddress, int maxLength) {
#ifdef USE_BMI
        int length = ReadUInt32_Optional_BMI();
#else
        int length = ReadUInt32_Optional_Simple();
#endif
        int copyLength = length > maxLength? maxLength: length;
        this->CopyString((char*)vecPtrAddress, (char*)(this->currentPos), copyLength);
        this->currentPos += length;
        *lengthAddress = copyLength;
    }
    inline void ReadByteVector_Mandatory(BYTE *vecPtrAddress, int *lengthAddress, int maxLength) {
#ifdef USE_BMI
        int length = ReadUInt32_Mandatory_BMI();
#else
        int length = ReadUInt32_Mandatory_Simple();
#endif
        int copyLength = length > maxLength? maxLength: length;
        this->CopyString((char*)vecPtrAddress, (char*)(this->currentPos), copyLength);
        this->currentPos += length;
        *lengthAddress = copyLength;
    }

    inline void WriteByteVector_Optional(BYTE *vecPtr, int length) { 
        if (vecPtr == NULL) { 
            *(this->currentPos) = 0x80;
            this->currentPos++;
            return;
        }
        WriteInt32_Optional(length);
        memcpy(this->currentPos, vecPtr, length);
        this->currentPos += length;
    }
    inline void WriteByteVector_Mandatory(BYTE *vecPtr, int length) {
        WriteInt32_Mandatory(length);
        memcpy(this->currentPos, vecPtr, length);
        this->currentPos += length;
    }

	inline UINT64 ParsePresenceMap0() {
		this->currentPos++;
		return 0;
	}

	inline UINT64 ParsePresenceMap1() {
		UINT32 value = (*(this->currentPos)) & 0x7f;
		this->currentPos++;
		return value;
	}

	/*
	inline UINT64 ParsePresenceMap2() {
		UINT32 value = *((UINT32*)this->currentPos);
        unsigned long long int count = _tzcnt_u32(value & 0x80808080);
        this->currentPos += (count + 1) >> 3;
        return value & 0x7f7f;
	}

	inline UINT64 ParsePresenceMap3() {
        UINT32 value = *((UINT32*)this->currentPos);
        unsigned long long int count = _tzcnt_u32(value & 0x80808080);
        this->currentPos += (count + 1) >> 3;
        return value & 0x7f7f7f;
	}
	*/
	inline UINT64 ParsePresenceMap2() {
		UINT32 value = *((UINT32*)this->currentPos);
		value |= 0x10000;
		int count = my_tzcnt_u64(value & 0x18080) + 1;
		this->currentPos += count >> 3;
		return value & (0x7f7f >> (16 - count));
	}

	inline UINT64 ParsePresenceMap3() {
		UINT32 value = *((UINT32*)this->currentPos);
		if((value & 0x80) != 0) {
			this->currentPos++;
			return value & 0x0000007f;
		}
		if((value & 0x8000) != 0) {
			this->currentPos += 2;
			return value & 0x00007f7f;
		}
		this->currentPos += 3;
		return value & 0x007f7f7f;
	}

	inline UINT64 ParsePresenceMap() {
		UINT64 value = *((UINT*)this->currentPos);
		if((value & FAST_STOPBIT_FIRST_BYTE) != 0) {
			this->currentPos++;
			return value & 0x000000000000007f;
		}
		if((value & FAST_STOPBIT_SECOND_BYTE) != 0) {
			this->currentPos += 2;
			return value & 0x0000000000007f7f;
		}
		if((value & FAST_STOPBIT_THIRD_BYTE) != 0) {
			this->currentPos += 3;
			return value & 0x00000000007f7f7f;
		}
		if((value & FAST_STOPBIT_FORTH_BYTE) != 0) {
			this->currentPos += 4;
			return value & 0x000000007f7f7f7f;
		}
		if((value & FAST_STOPBIT_FIFTH_BYTE) != 0) {
			this->currentPos += 5;
			return value & 0x0000007f7f7f7f7f;
		}
		if((value & FAST_STOPBIT_SIXSTH_BYTE) != 0) {
			this->currentPos += 6;
			return value & 0x00007f7f7f7f7f7f;
		}
		if((value & FAST_STOPBIT_SEVENTH_BYTE) != 0) {
			this->currentPos += 7;
			return value & 0x007f7f7f7f7f7f7f;
		}
		this->currentPos += 8;
		return value & 0x7f7f7f7f7f7f7f7f;
	}

    inline void ParsePresenceMap(UINT64 *map) {
        UINT64 value = *((UINT*)this->currentPos);
        if((value & FAST_STOPBIT_FIRST_BYTE) != 0) {
            value &= 0x000000000000007f;
            *map = value;
            this->currentPos++;
            return;
        }
        if((value & FAST_STOPBIT_SECOND_BYTE) != 0) {
            value &= 0x0000000000007f7f;
            *map = value;
            this->currentPos += 2;
            return;
        }
        if((value & FAST_STOPBIT_THIRD_BYTE) != 0) {
            value &= 0x00000000007f7f7f;
            *map = value;
            this->currentPos += 3;
            return;
        }
        if((value & FAST_STOPBIT_FORTH_BYTE) != 0) {
            value &= 0x000000007f7f7f7f;
            *map = value;
            this->currentPos += 4;
            return;
        }
        if((value & FAST_STOPBIT_FIFTH_BYTE) != 0) {
            value &= 0x0000007f7f7f7f7f;
            *map = value;
            this->currentPos += 5;
            return;
        }
        if((value & FAST_STOPBIT_SIXSTH_BYTE) != 0) {
            value &= 0x00007f7f7f7f7f7f;
            *map = value;
            this->currentPos += 6;
            return;
        }
        if((value & FAST_STOPBIT_SEVENTH_BYTE) != 0) {
            value &= 0x007f7f7f7f7f7f7f;
            *map = value;
            this->currentPos += 7;
            return;
        }
        value &= 0x7f7f7f7f7f7f7f7f;
        *map = value;
        this->currentPos += 8;
        return;
    }

    FastProtocolManager(AstsObjectsAllocationInfo *astsInfo, FortsObjectsAllocationInfo *spectraInfo);
    FastProtocolManager();
    ~FastProtocolManager();

    inline BYTE* Buffer() { return this->buffer; }
    inline BYTE* CurrentPos() { return this->currentPos; }
    inline int BufferLength() const { return this->bufferLength; }
    inline int MessageLength() const { return this->currentPos - this->buffer; }
    inline void SetBufferLength(int value) { this->bufferLength = value; }

#pragma region Asts_Encode_Methods_Declaration_GeneratedCode
	void EncodeAstsLogonInfo(AstsLogonInfo* info);
	void EncodeAstsLogoutInfo(AstsLogoutInfo* info);
	void EncodeAstsGenericInfo(AstsGenericInfo* info);
	void EncodeAstsOLSFONDInfo(AstsOLSFONDInfo* info);
	void EncodeAstsOLSCURRInfo(AstsOLSCURRInfo* info);
	void EncodeAstsTLSFONDInfo(AstsTLSFONDInfo* info);
	void EncodeAstsTLSCURRInfo(AstsTLSCURRInfo* info);
	void EncodeAstsSecurityDefinitionInfo(AstsSecurityDefinitionInfo* info);
	void EncodeAstsSecurityStatusInfo(AstsSecurityStatusInfo* info);
	void EncodeAstsTradingSessionStatusInfo(AstsTradingSessionStatusInfo* info);
	void EncodeAstsHeartbeatInfo(AstsHeartbeatInfo* info);
	void EncodeAstsIncrementalGenericInfo(AstsIncrementalGenericInfo* info);
	void EncodeAstsIncrementalMSRFONDInfo(AstsIncrementalMSRFONDInfo* info);
	void EncodeAstsIncrementalMSRCURRInfo(AstsIncrementalMSRCURRInfo* info);
	void EncodeAstsIncrementalOLRFONDInfo(AstsIncrementalOLRFONDInfo* info);
	void EncodeAstsIncrementalOLRCURRInfo(AstsIncrementalOLRCURRInfo* info);
	void EncodeAstsIncrementalTLRFONDInfo(AstsIncrementalTLRFONDInfo* info);
	void EncodeAstsIncrementalTLRCURRInfo(AstsIncrementalTLRCURRInfo* info);
#pragma endregion

#pragma region Forts_Encode_Methods_Declaration_GeneratedCode
	void EncodeFortsDefaultSnapshotMessageInfo(FortsDefaultSnapshotMessageInfo* info);
	void EncodeFortsSecurityDefinitionInfo(FortsSecurityDefinitionInfo* info);
	void EncodeFortsSecurityDefinitionUpdateReportInfo(FortsSecurityDefinitionUpdateReportInfo* info);
	void EncodeFortsSecurityStatusInfo(FortsSecurityStatusInfo* info);
	void EncodeFortsHeartbeatInfo(FortsHeartbeatInfo* info);
	void EncodeFortsSequenceResetInfo(FortsSequenceResetInfo* info);
	void EncodeFortsTradingSessionStatusInfo(FortsTradingSessionStatusInfo* info);
	void EncodeFortsNewsInfo(FortsNewsInfo* info);
	void EncodeFortsOrdersLogInfo(FortsOrdersLogInfo* info);
	void EncodeFortsOrdersBookInfo(FortsOrdersBookInfo* info);
	void EncodeFortsLogonInfo(FortsLogonInfo* info);
	void EncodeFortsLogoutInfo(FortsLogoutInfo* info);
	void EncodeFortsDefaultIncrementalRefreshMessageInfo(FortsDefaultIncrementalRefreshMessageInfo* info);
#pragma endregion

#pragma region Asts_Print_Methods_Declaration_GeneratedCode
	void PrintAstsLogon(AstsLogonInfo *info);
	void PrintAstsLogout(AstsLogoutInfo *info);
	void PrintAstsGeneric(AstsGenericInfo *info);
	void PrintAstsIncrementalGeneric(AstsIncrementalGenericInfo *info);
	void PrintAstsOLSFOND(AstsOLSFONDInfo *info);
	void PrintAstsOLSCURR(AstsOLSCURRInfo *info);
	void PrintAstsTLSFOND(AstsTLSFONDInfo *info);
	void PrintAstsTLSCURR(AstsTLSCURRInfo *info);
	void PrintAstsIncrementalMSRFOND(AstsIncrementalMSRFONDInfo *info);
	void PrintAstsIncrementalMSRCURR(AstsIncrementalMSRCURRInfo *info);
	void PrintAstsIncrementalOLRFOND(AstsIncrementalOLRFONDInfo *info);
	void PrintAstsIncrementalOLRCURR(AstsIncrementalOLRCURRInfo *info);
	void PrintAstsIncrementalTLRFOND(AstsIncrementalTLRFONDInfo *info);
	void PrintAstsIncrementalTLRCURR(AstsIncrementalTLRCURRInfo *info);
	void PrintAstsSecurityDefinition(AstsSecurityDefinitionInfo *info);
	void PrintAstsSecurityStatus(AstsSecurityStatusInfo *info);
	void PrintAstsTradingSessionStatus(AstsTradingSessionStatusInfo *info);
	void PrintAstsHeartbeat(AstsHeartbeatInfo *info);
	void PrintXmlAstsLogon(AstsLogonInfo *info);
	void PrintXmlAstsLogout(AstsLogoutInfo *info);
	void PrintXmlAstsGeneric(AstsGenericInfo *info);
	void PrintXmlAstsIncrementalGeneric(AstsIncrementalGenericInfo *info);
	void PrintXmlAstsOLSFOND(AstsOLSFONDInfo *info);
	void PrintXmlAstsOLSCURR(AstsOLSCURRInfo *info);
	void PrintXmlAstsTLSFOND(AstsTLSFONDInfo *info);
	void PrintXmlAstsTLSCURR(AstsTLSCURRInfo *info);
	void PrintXmlAstsIncrementalMSRFOND(AstsIncrementalMSRFONDInfo *info);
	void PrintXmlAstsIncrementalMSRCURR(AstsIncrementalMSRCURRInfo *info);
	void PrintXmlAstsIncrementalOLRFOND(AstsIncrementalOLRFONDInfo *info);
	void PrintXmlAstsIncrementalOLRCURR(AstsIncrementalOLRCURRInfo *info);
	void PrintXmlAstsIncrementalTLRFOND(AstsIncrementalTLRFONDInfo *info);
	void PrintXmlAstsIncrementalTLRCURR(AstsIncrementalTLRCURRInfo *info);
	void PrintXmlAstsSecurityDefinition(AstsSecurityDefinitionInfo *info);
	void PrintXmlAstsSecurityStatus(AstsSecurityStatusInfo *info);
	void PrintXmlAstsTradingSessionStatus(AstsTradingSessionStatusInfo *info);
	void PrintXmlAstsHeartbeat(AstsHeartbeatInfo *info);
#pragma endregion

#pragma region Forts_Print_Methods_Declaration_GeneratedCode
	void PrintFortsDefaultIncrementalRefreshMessage(FortsDefaultIncrementalRefreshMessageInfo *info);
	void PrintFortsDefaultSnapshotMessage(FortsDefaultSnapshotMessageInfo *info);
	void PrintFortsSecurityDefinition(FortsSecurityDefinitionInfo *info);
	void PrintFortsSecurityDefinitionUpdateReport(FortsSecurityDefinitionUpdateReportInfo *info);
	void PrintFortsSecurityStatus(FortsSecurityStatusInfo *info);
	void PrintFortsHeartbeat(FortsHeartbeatInfo *info);
	void PrintFortsSequenceReset(FortsSequenceResetInfo *info);
	void PrintFortsTradingSessionStatus(FortsTradingSessionStatusInfo *info);
	void PrintFortsNews(FortsNewsInfo *info);
	void PrintFortsOrdersLog(FortsOrdersLogInfo *info);
	void PrintFortsOrdersBook(FortsOrdersBookInfo *info);
	void PrintFortsLogon(FortsLogonInfo *info);
	void PrintFortsLogout(FortsLogoutInfo *info);
	void PrintXmlFortsDefaultIncrementalRefreshMessage(FortsDefaultIncrementalRefreshMessageInfo *info);
	void PrintXmlFortsDefaultSnapshotMessage(FortsDefaultSnapshotMessageInfo *info);
	void PrintXmlFortsSecurityDefinition(FortsSecurityDefinitionInfo *info);
	void PrintXmlFortsSecurityDefinitionUpdateReport(FortsSecurityDefinitionUpdateReportInfo *info);
	void PrintXmlFortsSecurityStatus(FortsSecurityStatusInfo *info);
	void PrintXmlFortsHeartbeat(FortsHeartbeatInfo *info);
	void PrintXmlFortsSequenceReset(FortsSequenceResetInfo *info);
	void PrintXmlFortsTradingSessionStatus(FortsTradingSessionStatusInfo *info);
	void PrintXmlFortsNews(FortsNewsInfo *info);
	void PrintXmlFortsOrdersLog(FortsOrdersLogInfo *info);
	void PrintXmlFortsOrdersBook(FortsOrdersBookInfo *info);
	void PrintXmlFortsLogon(FortsLogonInfo *info);
	void PrintXmlFortsLogout(FortsLogoutInfo *info);
#pragma endregion

#pragma region Asts_Decode_Methods_Definition_GeneratedCode
	inline void DecodeAstsHeader() {

		this->m_presenceMap = this->ParsePresenceMap();
		this->m_templateId = ReadUInt32_Mandatory_BMI();
	}

	int GetAstsTotalNumReports() {
		// ReadMsgNumber and DecodeHeader should be called first
		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		return ReadInt32_Optional_BMI();
	}
	inline void* DecodeAstsUnsupportedMessage() { return 0; }
	inline AstsSnapshotInfo* GetAstsSnapshotInfoUnsupported() { return 0; }
	inline AstsLogonInfo* DecodeAstsLogon() {
		AstsLogonInfo* info = GetFreeAstsLogonInfo();
		UINT64 nmap1 = 0;

		ReadString_Mandatory(info->TargetCompID, &(info->TargetCompIDLength));
		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		info->HeartBtInt = ReadInt32_Mandatory_BMI();
		nmap1 |= NULL_MAP_INDEX0 & (ReadString_Optional(info->Username, &(info->UsernameLength)) - 1);
		nmap1 |= NULL_MAP_INDEX1 & (ReadString_Optional(info->Password, &(info->PasswordLength)) - 1);
		ReadString_Mandatory(info->DefaultApplVerID, &(info->DefaultApplVerIDLength));
		info->NullMap = nmap1;
		this->m_prevastsLogonInfo = info;
		return info;
	}
	inline AstsLogoutInfo* DecodeAstsLogout() {
		AstsLogoutInfo* info = GetFreeAstsLogoutInfo();
		UINT64 nmap1 = 0;

		ReadString_Mandatory(info->TargetCompID, &(info->TargetCompIDLength));
		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		nmap1 |= NULL_MAP_INDEX0 & (ReadString_Optional(info->Text, &(info->TextLength)) - 1);
		info->NullMap = nmap1;
		this->m_prevastsLogoutInfo = info;
		return info;
	}
	inline AstsGenericInfo* DecodeAstsGeneric() {
		AstsGenericInfo* info = GetFreeAstsGenericInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		nmap1 |= NULL_MAP_INDEX0 & (ReadString_Optional_Fixed4(info->TradingSessionID) - 1);
		ReadString_Mandatory_PredictMax16(info->Symbol, &(info->SymbolLength));
		nmap1 |= NULL_MAP_INDEX1 & (ReadUInt32_Optional_BMI(&(info->LastMsgSeqNumProcessed)) - 1);
		info->RptSeq = ReadInt32_Mandatory_BMI();
		nmap1 |= NULL_MAP_INDEX2 & (ReadUInt32_Optional_BMI(&(info->LastFragment)) - 1);
		nmap1 |= NULL_MAP_INDEX3 & (ReadUInt32_Optional_BMI(&(info->RouteFirst)) - 1);
		nmap1 |= NULL_MAP_INDEX4 & (ReadInt32_Optional_BMI(&(info->TradSesStatus)) - 1);
		nmap1 |= NULL_MAP_INDEX5 & (ReadInt32_Optional_BMI(&(info->MDSecurityTradingStatus)) - 1);
		nmap1 |= NULL_MAP_INDEX6 & (ReadUInt32_Optional_BMI(&(info->AuctionIndicator)) - 1);
		nmap1 |= NULL_MAP_INDEX7 & (ReadDecimal_Optional_BMI(&(info->NetChgPrevDay)) - 1);

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict12_BMI();
		AstsGenericItemInfo* gmdeItemInfo = NULL;

		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = GetFreeAstsGenericItemInfo();
			for(int i = 0; i < sizeof(AstsGenericItemInfo); i += 64)
				__builtin_prefetch(((char*)gmdeItemInfo) + i, 0, _MM_HINT_T0);
			info->GroupMDEntries[gmdeItemInfoIndex] = gmdeItemInfo;
		}
		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = info->GroupMDEntries[gmdeItemInfoIndex];
			UINT64 nmap2 = 0;

			nmap2 |= NULL_MAP_INDEX0 & (ReadString_Optional_Fixed1(gmdeItemInfo->MDEntryType) - 1);
			nmap2 |= NULL_MAP_INDEX1 & (ReadString_Optional_PredictMax8(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength)) - 1);
			nmap2 |= NULL_MAP_INDEX2 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryDate)) - 1);
			nmap2 |= NULL_MAP_INDEX3 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryTime)) - 1);
			nmap2 |= NULL_MAP_INDEX4 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->OrigTime)) - 1);
			nmap2 |= NULL_MAP_INDEX5 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntryPx)) - 1);
			nmap2 |= NULL_MAP_INDEX6 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntrySize)) - 1);
			nmap2 |= NULL_MAP_INDEX7 & (ReadString_Optional(gmdeItemInfo->QuoteCondition, &(gmdeItemInfo->QuoteConditionLength)) - 1);
			nmap2 |= NULL_MAP_INDEX8 & (ReadString_Optional(gmdeItemInfo->TradeCondition, &(gmdeItemInfo->TradeConditionLength)) - 1);
			nmap2 |= NULL_MAP_INDEX9 & (ReadString_Optional(gmdeItemInfo->OpenCloseSettlFlag, &(gmdeItemInfo->OpenCloseSettlFlagLength)) - 1);
			nmap2 |= NULL_MAP_INDEX10 & (ReadString_Optional_Fixed1(gmdeItemInfo->OrdType) - 1);
			nmap2 |= NULL_MAP_INDEX11 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->EffectiveTime)) - 1);
			nmap2 |= NULL_MAP_INDEX12 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->StartTime)) - 1);
			nmap2 |= NULL_MAP_INDEX13 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->AccruedInterestAmt)) - 1);
			nmap2 |= NULL_MAP_INDEX14 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->ChgFromWAPrice)) - 1);
			nmap2 |= NULL_MAP_INDEX15 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->ChgOpenInterest)) - 1);
			nmap2 |= NULL_MAP_INDEX16 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->BidMarketSize)) - 1);
			nmap2 |= NULL_MAP_INDEX17 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->AskMarketSize)) - 1);
			nmap2 |= NULL_MAP_INDEX18 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->TotalNumOfTrades)) - 1);
			nmap2 |= NULL_MAP_INDEX19 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->TradeValue)) - 1);
			nmap2 |= NULL_MAP_INDEX20 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->Yield)) - 1);
			nmap2 |= NULL_MAP_INDEX21 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->TotalVolume)) - 1);
			nmap2 |= NULL_MAP_INDEX22 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->OfferNbOr)) - 1);
			nmap2 |= NULL_MAP_INDEX23 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->BidNbOr)) - 1);
			nmap2 |= NULL_MAP_INDEX24 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->ChgFromSettlmnt)) - 1);
			nmap2 |= NULL_MAP_INDEX25 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->SettlDate)) - 1);
			nmap2 |= NULL_MAP_INDEX26 & (ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength)) - 1);
			nmap2 |= NULL_MAP_INDEX27 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->SumQtyOfBest)) - 1);
			nmap2 |= NULL_MAP_INDEX28 & (ReadString_Optional(gmdeItemInfo->OrderSide, &(gmdeItemInfo->OrderSideLength)) - 1);
			nmap2 |= NULL_MAP_INDEX29 & (ReadString_Optional_Fixed1(gmdeItemInfo->OrderStatus) - 1);
			nmap2 |= NULL_MAP_INDEX30 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MinCurrPx)) - 1);
			nmap2 |= NULL_MAP_INDEX31 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MinCurrPxChgTime)) - 1);
			nmap2 |= NULL_MAP_INDEX32 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->VolumeIndicator)) - 1);
			nmap2 |= NULL_MAP_INDEX33 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->Price)) - 1);
			nmap2 |= NULL_MAP_INDEX34 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->PriceType)) - 1);
			nmap2 |= NULL_MAP_INDEX35 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->NominalValue)) - 1);
			nmap2 |= NULL_MAP_INDEX36 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->RepoToPx)) - 1);
			nmap2 |= NULL_MAP_INDEX37 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->BuyBackPx)) - 1);
			nmap2 |= NULL_MAP_INDEX38 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->BuyBackDate)) - 1);
			nmap2 |= NULL_MAP_INDEX39 & (ReadString_Optional(gmdeItemInfo->CXFlag, &(gmdeItemInfo->CXFlagLength)) - 1);
			nmap2 |= NULL_MAP_INDEX40 & (ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength)) - 1);
			gmdeItemInfo->NullMap = nmap2;
			this->m_prevastsGenericItemInfo = gmdeItemInfo;
		}

		info->NullMap = nmap1;
		this->m_prevastsGenericInfo = info;
		return info;
	}
	inline AstsIncrementalGenericInfo* DecodeAstsIncrementalGeneric() {
		AstsIncrementalGenericInfo* info = GetFreeAstsIncrementalGenericInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict12_BMI();
		AstsGenericItemInfo* gmdeItemInfo = NULL;

		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = GetFreeAstsGenericItemInfo();
			for(int i = 0; i < sizeof(AstsGenericItemInfo); i += 64)
				__builtin_prefetch(((char*)gmdeItemInfo) + i, 0, _MM_HINT_T0);
			info->GroupMDEntries[gmdeItemInfoIndex] = gmdeItemInfo;
		}
		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = info->GroupMDEntries[gmdeItemInfoIndex];
			UINT64 nmap2 = 0;

			nmap2 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_Fixed1_BMI(&(gmdeItemInfo->MDUpdateAction)) - 1);
			nmap2 |= NULL_MAP_INDEX1 & (ReadString_Optional_Fixed1(gmdeItemInfo->MDEntryType) - 1);
			nmap2 |= NULL_MAP_INDEX2 & (ReadString_Optional_PredictMax8(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength)) - 1);
			nmap2 |= NULL_MAP_INDEX3 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->RptSeq)) - 1);
			nmap2 |= NULL_MAP_INDEX4 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryDate)) - 1);
			nmap2 |= NULL_MAP_INDEX5 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->OrigTime)) - 1);
			nmap2 |= NULL_MAP_INDEX6 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->SettlDate)) - 1);
			nmap2 |= NULL_MAP_INDEX7 & (ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength)) - 1);
			nmap2 |= NULL_MAP_INDEX8 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryTime)) - 1);
			nmap2 |= NULL_MAP_INDEX9 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->EffectiveTime)) - 1);
			nmap2 |= NULL_MAP_INDEX10 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->StartTime)) - 1);
			nmap2 |= NULL_MAP_INDEX11 & (ReadString_Optional_PredictMax16(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength)) - 1);
			nmap2 |= NULL_MAP_INDEX12 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntryPx)) - 1);
			nmap2 |= NULL_MAP_INDEX13 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntrySize)) - 1);
			nmap2 |= NULL_MAP_INDEX14 & (ReadString_Optional(gmdeItemInfo->QuoteCondition, &(gmdeItemInfo->QuoteConditionLength)) - 1);
			nmap2 |= NULL_MAP_INDEX15 & (ReadString_Optional(gmdeItemInfo->TradeCondition, &(gmdeItemInfo->TradeConditionLength)) - 1);
			nmap2 |= NULL_MAP_INDEX16 & (ReadString_Optional(gmdeItemInfo->OpenCloseSettlFlag, &(gmdeItemInfo->OpenCloseSettlFlagLength)) - 1);
			nmap2 |= NULL_MAP_INDEX17 & (ReadString_Optional_Fixed1(gmdeItemInfo->OrdType) - 1);
			nmap2 |= NULL_MAP_INDEX18 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->NetChgPrevDay)) - 1);
			nmap2 |= NULL_MAP_INDEX19 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->AccruedInterestAmt)) - 1);
			nmap2 |= NULL_MAP_INDEX20 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->ChgFromWAPrice)) - 1);
			nmap2 |= NULL_MAP_INDEX21 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->ChgOpenInterest)) - 1);
			nmap2 |= NULL_MAP_INDEX22 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->BidMarketSize)) - 1);
			nmap2 |= NULL_MAP_INDEX23 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->AskMarketSize)) - 1);
			nmap2 |= NULL_MAP_INDEX24 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->TotalNumOfTrades)) - 1);
			nmap2 |= NULL_MAP_INDEX25 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->TradeValue)) - 1);
			nmap2 |= NULL_MAP_INDEX26 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->Yield)) - 1);
			nmap2 |= NULL_MAP_INDEX27 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->TotalVolume)) - 1);
			nmap2 |= NULL_MAP_INDEX28 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->OfferNbOr)) - 1);
			nmap2 |= NULL_MAP_INDEX29 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->BidNbOr)) - 1);
			nmap2 |= NULL_MAP_INDEX30 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->ChgFromSettlmnt)) - 1);
			nmap2 |= NULL_MAP_INDEX31 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->SumQtyOfBest)) - 1);
			nmap2 |= NULL_MAP_INDEX32 & (ReadString_Optional(gmdeItemInfo->OrderSide, &(gmdeItemInfo->OrderSideLength)) - 1);
			nmap2 |= NULL_MAP_INDEX33 & (ReadString_Optional_Fixed1(gmdeItemInfo->OrderStatus) - 1);
			nmap2 |= NULL_MAP_INDEX34 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MinCurrPx)) - 1);
			nmap2 |= NULL_MAP_INDEX35 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MinCurrPxChgTime)) - 1);
			nmap2 |= NULL_MAP_INDEX36 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->VolumeIndicator)) - 1);
			nmap2 |= NULL_MAP_INDEX37 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->Price)) - 1);
			nmap2 |= NULL_MAP_INDEX38 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->PriceType)) - 1);
			nmap2 |= NULL_MAP_INDEX39 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->NominalValue)) - 1);
			nmap2 |= NULL_MAP_INDEX40 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->RepoToPx)) - 1);
			nmap2 |= NULL_MAP_INDEX41 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->BuyBackPx)) - 1);
			nmap2 |= NULL_MAP_INDEX42 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->BuyBackDate)) - 1);
			nmap2 |= NULL_MAP_INDEX43 & (ReadString_Optional(gmdeItemInfo->CXFlag, &(gmdeItemInfo->CXFlagLength)) - 1);
			nmap2 |= NULL_MAP_INDEX44 & (ReadString_Optional_Fixed4(gmdeItemInfo->TradingSessionID) - 1);
			nmap2 |= NULL_MAP_INDEX45 & (ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength)) - 1);
			gmdeItemInfo->NullMap = nmap2;
			this->m_prevastsGenericItemInfo = gmdeItemInfo;
		}

		info->NullMap = nmap1;
		this->m_prevastsIncrementalGenericInfo = info;
		return info;
	}
	inline AstsOLSFONDInfo* DecodeAstsOLSFOND() {
		AstsOLSFONDInfo* info = GetFreeAstsOLSFONDInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		nmap1 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_BMI(&(info->LastMsgSeqNumProcessed)) - 1);
		info->RptSeq = ReadInt32_Mandatory_BMI();
		nmap1 |= NULL_MAP_INDEX1 & (ReadUInt32_Optional_BMI(&(info->LastFragment)) - 1);
		nmap1 |= NULL_MAP_INDEX2 & (ReadUInt32_Optional_BMI(&(info->RouteFirst)) - 1);
		nmap1 |= NULL_MAP_INDEX3 & (ReadInt32_Optional_BMI(&(info->TradSesStatus)) - 1);
		nmap1 |= NULL_MAP_INDEX4 & (ReadString_Optional_Fixed4(info->TradingSessionID) - 1);
		ReadString_Mandatory_PredictMax16(info->Symbol, &(info->SymbolLength));
		nmap1 |= NULL_MAP_INDEX5 & (ReadInt32_Optional_BMI(&(info->MDSecurityTradingStatus)) - 1);
		nmap1 |= NULL_MAP_INDEX6 & (ReadUInt32_Optional_BMI(&(info->AuctionIndicator)) - 1);

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict12_BMI();
		AstsOLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = GetFreeAstsOLSFONDItemInfo();
			for(int i = 0; i < sizeof(AstsOLSFONDItemInfo); i += 64)
				__builtin_prefetch(((char*)gmdeItemInfo) + i, 0, _MM_HINT_T0);
			info->GroupMDEntries[gmdeItemInfoIndex] = gmdeItemInfo;
		}
		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = info->GroupMDEntries[gmdeItemInfoIndex];

			UINT64 pmap2 = this->ParsePresenceMap2();
			UINT64 nmap2 = 0;

			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX0)) {
				nmap2 |= NULL_MAP_INDEX0 & (ReadString_Optional_Fixed1(gmdeItemInfo->MDEntryType) - 1);
			}
			else {
				this->CopyString_Fixed1(gmdeItemInfo->MDEntryType, m_prevastsOLSFONDItemInfo->MDEntryType);
			}
			nmap2 |= NULL_MAP_INDEX1 & (ReadString_Optional_PredictMax8(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength)) - 1);
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX1)) {
				nmap2 |= NULL_MAP_INDEX2 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryDate)) - 1);
			}
			else {
				gmdeItemInfo->MDEntryDate = this->m_prevastsOLSFONDItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX2)) {
				nmap2 |= NULL_MAP_INDEX3 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryTime)) - 1);
			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevastsOLSFONDItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX3)) {
				nmap2 |= NULL_MAP_INDEX4 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->OrigTime)) - 1);
			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevastsOLSFONDItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX4)) {
				nmap2 |= NULL_MAP_INDEX5 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntryPx)) - 1);
			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevastsOLSFONDItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX5)) {
				nmap2 |= NULL_MAP_INDEX6 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntrySize)) - 1);
			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevastsOLSFONDItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX6)) {
				nmap2 |= NULL_MAP_INDEX7 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->Yield)) - 1);
			}
			else {
				gmdeItemInfo->Yield = this->m_prevastsOLSFONDItemInfo->Yield;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX7)) {
				nmap2 |= NULL_MAP_INDEX8 & (ReadString_Optional_Fixed1(gmdeItemInfo->OrderStatus) - 1);
			}
			else {
				this->CopyString_Fixed1(gmdeItemInfo->OrderStatus, m_prevastsOLSFONDItemInfo->OrderStatus);
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX8)) {
				nmap2 |= NULL_MAP_INDEX9 & (ReadString_Optional_Fixed1(gmdeItemInfo->OrdType) - 1);
			}
			else {
				this->CopyString_Fixed1(gmdeItemInfo->OrdType, m_prevastsOLSFONDItemInfo->OrdType);
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX9)) {
				nmap2 |= NULL_MAP_INDEX10 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->TotalVolume)) - 1);
			}
			else {
				gmdeItemInfo->TotalVolume = this->m_prevastsOLSFONDItemInfo->TotalVolume;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX10)) {
				nmap2 |= NULL_MAP_INDEX11 & (ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength)) - 1);
			}
			else {
				this->CopyString_Predict12(gmdeItemInfo->TradingSessionSubID, m_prevastsOLSFONDItemInfo->TradingSessionSubID);
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevastsOLSFONDItemInfo->TradingSessionSubIDLength;
			}
			gmdeItemInfo->PresenceMap = pmap2;
			gmdeItemInfo->NullMap = nmap2;
			this->m_prevastsOLSFONDItemInfo = gmdeItemInfo;
		}

		info->NullMap = nmap1;
		this->m_prevastsOLSFONDInfo = info;
		return info;
	}
	inline AstsOLSCURRInfo* DecodeAstsOLSCURR() {
		AstsOLSCURRInfo* info = GetFreeAstsOLSCURRInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		nmap1 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_BMI(&(info->LastMsgSeqNumProcessed)) - 1);
		info->RptSeq = ReadInt32_Mandatory_BMI();
		nmap1 |= NULL_MAP_INDEX1 & (ReadUInt32_Optional_BMI(&(info->LastFragment)) - 1);
		nmap1 |= NULL_MAP_INDEX2 & (ReadUInt32_Optional_BMI(&(info->RouteFirst)) - 1);
		nmap1 |= NULL_MAP_INDEX3 & (ReadInt32_Optional_BMI(&(info->TradSesStatus)) - 1);
		nmap1 |= NULL_MAP_INDEX4 & (ReadString_Optional_Fixed4(info->TradingSessionID) - 1);
		ReadString_Mandatory_PredictMax16(info->Symbol, &(info->SymbolLength));
		nmap1 |= NULL_MAP_INDEX5 & (ReadInt32_Optional_BMI(&(info->MDSecurityTradingStatus)) - 1);

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict12_BMI();
		AstsOLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = GetFreeAstsOLSCURRItemInfo();
			for(int i = 0; i < sizeof(AstsOLSCURRItemInfo); i += 64)
				__builtin_prefetch(((char*)gmdeItemInfo) + i, 0, _MM_HINT_T0);
			info->GroupMDEntries[gmdeItemInfoIndex] = gmdeItemInfo;
		}
		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = info->GroupMDEntries[gmdeItemInfoIndex];

			UINT64 pmap2 = this->ParsePresenceMap2();
			UINT64 nmap2 = 0;

			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX0)) {
				nmap2 |= NULL_MAP_INDEX0 & (ReadString_Optional_Fixed1(gmdeItemInfo->MDEntryType) - 1);
			}
			else {
				this->CopyString_Fixed1(gmdeItemInfo->MDEntryType, m_prevastsOLSCURRItemInfo->MDEntryType);
			}
			nmap2 |= NULL_MAP_INDEX1 & (ReadString_Optional_PredictMax8(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength)) - 1);
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX1)) {
				nmap2 |= NULL_MAP_INDEX2 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryDate)) - 1);
			}
			else {
				gmdeItemInfo->MDEntryDate = this->m_prevastsOLSCURRItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX2)) {
				nmap2 |= NULL_MAP_INDEX3 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryTime)) - 1);
			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevastsOLSCURRItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX3)) {
				nmap2 |= NULL_MAP_INDEX4 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->OrigTime)) - 1);
			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevastsOLSCURRItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX4)) {
				nmap2 |= NULL_MAP_INDEX5 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntryPx)) - 1);
			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevastsOLSCURRItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX5)) {
				nmap2 |= NULL_MAP_INDEX6 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntrySize)) - 1);
			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevastsOLSCURRItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX6)) {
				nmap2 |= NULL_MAP_INDEX7 & (ReadString_Optional_Fixed1(gmdeItemInfo->OrderStatus) - 1);
			}
			else {
				this->CopyString_Fixed1(gmdeItemInfo->OrderStatus, m_prevastsOLSCURRItemInfo->OrderStatus);
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX7)) {
				nmap2 |= NULL_MAP_INDEX8 & (ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength)) - 1);
			}
			else {
				this->CopyString_Predict12(gmdeItemInfo->TradingSessionSubID, m_prevastsOLSCURRItemInfo->TradingSessionSubID);
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevastsOLSCURRItemInfo->TradingSessionSubIDLength;
			}
			gmdeItemInfo->PresenceMap = pmap2;
			gmdeItemInfo->NullMap = nmap2;
			this->m_prevastsOLSCURRItemInfo = gmdeItemInfo;
		}

		info->NullMap = nmap1;
		this->m_prevastsOLSCURRInfo = info;
		return info;
	}
	inline AstsTLSFONDInfo* DecodeAstsTLSFOND() {
		AstsTLSFONDInfo* info = GetFreeAstsTLSFONDInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		nmap1 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_BMI(&(info->LastMsgSeqNumProcessed)) - 1);
		info->RptSeq = ReadInt32_Mandatory_BMI();
		nmap1 |= NULL_MAP_INDEX1 & (ReadUInt32_Optional_BMI(&(info->LastFragment)) - 1);
		nmap1 |= NULL_MAP_INDEX2 & (ReadUInt32_Optional_BMI(&(info->RouteFirst)) - 1);
		nmap1 |= NULL_MAP_INDEX3 & (ReadInt32_Optional_BMI(&(info->TradSesStatus)) - 1);
		nmap1 |= NULL_MAP_INDEX4 & (ReadString_Optional_Fixed4(info->TradingSessionID) - 1);
		ReadString_Mandatory_PredictMax16(info->Symbol, &(info->SymbolLength));
		nmap1 |= NULL_MAP_INDEX5 & (ReadInt32_Optional_BMI(&(info->MDSecurityTradingStatus)) - 1);
		nmap1 |= NULL_MAP_INDEX6 & (ReadUInt32_Optional_BMI(&(info->AuctionIndicator)) - 1);

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict12_BMI();
		AstsTLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = GetFreeAstsTLSFONDItemInfo();
			for(int i = 0; i < sizeof(AstsTLSFONDItemInfo); i += 64)
				__builtin_prefetch(((char*)gmdeItemInfo) + i, 0, _MM_HINT_T0);
			info->GroupMDEntries[gmdeItemInfoIndex] = gmdeItemInfo;
		}
		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = info->GroupMDEntries[gmdeItemInfoIndex];

			UINT64 pmap2 = this->ParsePresenceMap3();
			UINT64 nmap2 = 0;

			ReadString_Mandatory_Fixed1(gmdeItemInfo->MDEntryType);
			nmap2 |= NULL_MAP_INDEX0 & (ReadString_Optional_PredictMax8(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength)) - 1);
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX0)) {
				nmap2 |= NULL_MAP_INDEX1 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryDate)) - 1);
			}
			else {
				gmdeItemInfo->MDEntryDate = this->m_prevastsTLSFONDItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX1)) {
				nmap2 |= NULL_MAP_INDEX2 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryTime)) - 1);
			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevastsTLSFONDItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX2)) {
				nmap2 |= NULL_MAP_INDEX3 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->OrigTime)) - 1);
			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevastsTLSFONDItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX3)) {
				nmap2 |= NULL_MAP_INDEX4 & (ReadString_Optional(gmdeItemInfo->OrderSide, &(gmdeItemInfo->OrderSideLength)) - 1);
			}
			else {
				this->CopyString(gmdeItemInfo->OrderSide, m_prevastsTLSFONDItemInfo->OrderSide, m_prevastsTLSFONDItemInfo->OrderSideLength);
				gmdeItemInfo->OrderSideLength = this->m_prevastsTLSFONDItemInfo->OrderSideLength;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX4)) {
				nmap2 |= NULL_MAP_INDEX5 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntryPx)) - 1);
			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevastsTLSFONDItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX5)) {
				nmap2 |= NULL_MAP_INDEX6 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntrySize)) - 1);
			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevastsTLSFONDItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX6)) {
				nmap2 |= NULL_MAP_INDEX7 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->AccruedInterestAmt)) - 1);
			}
			else {
				gmdeItemInfo->AccruedInterestAmt = this->m_prevastsTLSFONDItemInfo->AccruedInterestAmt;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX7)) {
				nmap2 |= NULL_MAP_INDEX8 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->TradeValue)) - 1);
			}
			else {
				gmdeItemInfo->TradeValue = this->m_prevastsTLSFONDItemInfo->TradeValue;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX8)) {
				nmap2 |= NULL_MAP_INDEX9 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->Yield)) - 1);
			}
			else {
				gmdeItemInfo->Yield = this->m_prevastsTLSFONDItemInfo->Yield;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX9)) {
				nmap2 |= NULL_MAP_INDEX10 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->SettlDate)) - 1);
			}
			else {
				gmdeItemInfo->SettlDate = this->m_prevastsTLSFONDItemInfo->SettlDate;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX10)) {
				nmap2 |= NULL_MAP_INDEX11 & (ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength)) - 1);
			}
			else {
				this->CopyString(gmdeItemInfo->SettleType, m_prevastsTLSFONDItemInfo->SettleType, m_prevastsTLSFONDItemInfo->SettleTypeLength);
				gmdeItemInfo->SettleTypeLength = this->m_prevastsTLSFONDItemInfo->SettleTypeLength;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX11)) {
				nmap2 |= NULL_MAP_INDEX12 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->Price)) - 1);
			}
			else {
				gmdeItemInfo->Price = this->m_prevastsTLSFONDItemInfo->Price;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX12)) {
				nmap2 |= NULL_MAP_INDEX13 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->PriceType)) - 1);
			}
			else {
				gmdeItemInfo->PriceType = this->m_prevastsTLSFONDItemInfo->PriceType;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX13)) {
				nmap2 |= NULL_MAP_INDEX14 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->RepoToPx)) - 1);
			}
			else {
				gmdeItemInfo->RepoToPx = this->m_prevastsTLSFONDItemInfo->RepoToPx;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX14)) {
				nmap2 |= NULL_MAP_INDEX15 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->BuyBackPx)) - 1);
			}
			else {
				gmdeItemInfo->BuyBackPx = this->m_prevastsTLSFONDItemInfo->BuyBackPx;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX15)) {
				nmap2 |= NULL_MAP_INDEX16 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->BuyBackDate)) - 1);
			}
			else {
				gmdeItemInfo->BuyBackDate = this->m_prevastsTLSFONDItemInfo->BuyBackDate;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX16)) {
				nmap2 |= NULL_MAP_INDEX17 & (ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength)) - 1);
			}
			else {
				this->CopyString_Predict12(gmdeItemInfo->TradingSessionSubID, m_prevastsTLSFONDItemInfo->TradingSessionSubID);
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevastsTLSFONDItemInfo->TradingSessionSubIDLength;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX17)) {
				nmap2 |= NULL_MAP_INDEX18 & (ReadString_Optional(gmdeItemInfo->RefOrderID, &(gmdeItemInfo->RefOrderIDLength)) - 1);
			}
			else {
				this->CopyString(gmdeItemInfo->RefOrderID, m_prevastsTLSFONDItemInfo->RefOrderID, m_prevastsTLSFONDItemInfo->RefOrderIDLength);
				gmdeItemInfo->RefOrderIDLength = this->m_prevastsTLSFONDItemInfo->RefOrderIDLength;
			}
			gmdeItemInfo->PresenceMap = pmap2;
			gmdeItemInfo->NullMap = nmap2;
			this->m_prevastsTLSFONDItemInfo = gmdeItemInfo;
		}

		info->NullMap = nmap1;
		this->m_prevastsTLSFONDInfo = info;
		return info;
	}
	inline AstsTLSCURRInfo* DecodeAstsTLSCURR() {
		AstsTLSCURRInfo* info = GetFreeAstsTLSCURRInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		nmap1 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_BMI(&(info->LastMsgSeqNumProcessed)) - 1);
		info->RptSeq = ReadInt32_Mandatory_BMI();
		nmap1 |= NULL_MAP_INDEX1 & (ReadUInt32_Optional_BMI(&(info->LastFragment)) - 1);
		nmap1 |= NULL_MAP_INDEX2 & (ReadUInt32_Optional_BMI(&(info->RouteFirst)) - 1);
		nmap1 |= NULL_MAP_INDEX3 & (ReadInt32_Optional_BMI(&(info->TradSesStatus)) - 1);
		nmap1 |= NULL_MAP_INDEX4 & (ReadString_Optional_Fixed4(info->TradingSessionID) - 1);
		ReadString_Mandatory_PredictMax16(info->Symbol, &(info->SymbolLength));
		nmap1 |= NULL_MAP_INDEX5 & (ReadInt32_Optional_BMI(&(info->MDSecurityTradingStatus)) - 1);

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict12_BMI();
		AstsTLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = GetFreeAstsTLSCURRItemInfo();
			for(int i = 0; i < sizeof(AstsTLSCURRItemInfo); i += 64)
				__builtin_prefetch(((char*)gmdeItemInfo) + i, 0, _MM_HINT_T0);
			info->GroupMDEntries[gmdeItemInfoIndex] = gmdeItemInfo;
		}
		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = info->GroupMDEntries[gmdeItemInfoIndex];

			UINT64 pmap2 = this->ParsePresenceMap3();
			UINT64 nmap2 = 0;

			ReadString_Mandatory_Fixed1(gmdeItemInfo->MDEntryType);
			nmap2 |= NULL_MAP_INDEX0 & (ReadString_Optional_PredictMax8(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength)) - 1);
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX0)) {
				nmap2 |= NULL_MAP_INDEX1 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryDate)) - 1);
			}
			else {
				gmdeItemInfo->MDEntryDate = this->m_prevastsTLSCURRItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX1)) {
				nmap2 |= NULL_MAP_INDEX2 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryTime)) - 1);
			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevastsTLSCURRItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX2)) {
				nmap2 |= NULL_MAP_INDEX3 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->OrigTime)) - 1);
			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevastsTLSCURRItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX3)) {
				nmap2 |= NULL_MAP_INDEX4 & (ReadString_Optional(gmdeItemInfo->OrderSide, &(gmdeItemInfo->OrderSideLength)) - 1);
			}
			else {
				this->CopyString(gmdeItemInfo->OrderSide, m_prevastsTLSCURRItemInfo->OrderSide, m_prevastsTLSCURRItemInfo->OrderSideLength);
				gmdeItemInfo->OrderSideLength = this->m_prevastsTLSCURRItemInfo->OrderSideLength;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX4)) {
				nmap2 |= NULL_MAP_INDEX5 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntryPx)) - 1);
			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevastsTLSCURRItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX5)) {
				nmap2 |= NULL_MAP_INDEX6 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntrySize)) - 1);
			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevastsTLSCURRItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX6)) {
				nmap2 |= NULL_MAP_INDEX7 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->TradeValue)) - 1);
			}
			else {
				gmdeItemInfo->TradeValue = this->m_prevastsTLSCURRItemInfo->TradeValue;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX7)) {
				nmap2 |= NULL_MAP_INDEX8 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->SettlDate)) - 1);
			}
			else {
				gmdeItemInfo->SettlDate = this->m_prevastsTLSCURRItemInfo->SettlDate;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX8)) {
				nmap2 |= NULL_MAP_INDEX9 & (ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength)) - 1);
			}
			else {
				this->CopyString(gmdeItemInfo->SettleType, m_prevastsTLSCURRItemInfo->SettleType, m_prevastsTLSCURRItemInfo->SettleTypeLength);
				gmdeItemInfo->SettleTypeLength = this->m_prevastsTLSCURRItemInfo->SettleTypeLength;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX9)) {
				nmap2 |= NULL_MAP_INDEX10 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->Price)) - 1);
			}
			else {
				gmdeItemInfo->Price = this->m_prevastsTLSCURRItemInfo->Price;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX10)) {
				nmap2 |= NULL_MAP_INDEX11 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->PriceType)) - 1);
			}
			else {
				gmdeItemInfo->PriceType = this->m_prevastsTLSCURRItemInfo->PriceType;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX11)) {
				nmap2 |= NULL_MAP_INDEX12 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->RepoToPx)) - 1);
			}
			else {
				gmdeItemInfo->RepoToPx = this->m_prevastsTLSCURRItemInfo->RepoToPx;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX12)) {
				nmap2 |= NULL_MAP_INDEX13 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->BuyBackPx)) - 1);
			}
			else {
				gmdeItemInfo->BuyBackPx = this->m_prevastsTLSCURRItemInfo->BuyBackPx;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX13)) {
				nmap2 |= NULL_MAP_INDEX14 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->BuyBackDate)) - 1);
			}
			else {
				gmdeItemInfo->BuyBackDate = this->m_prevastsTLSCURRItemInfo->BuyBackDate;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX14)) {
				nmap2 |= NULL_MAP_INDEX15 & (ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength)) - 1);
			}
			else {
				this->CopyString_Predict12(gmdeItemInfo->TradingSessionSubID, m_prevastsTLSCURRItemInfo->TradingSessionSubID);
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevastsTLSCURRItemInfo->TradingSessionSubIDLength;
			}
			if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX15)) {
				nmap2 |= NULL_MAP_INDEX16 & (ReadString_Optional(gmdeItemInfo->RefOrderID, &(gmdeItemInfo->RefOrderIDLength)) - 1);
			}
			else {
				this->CopyString(gmdeItemInfo->RefOrderID, m_prevastsTLSCURRItemInfo->RefOrderID, m_prevastsTLSCURRItemInfo->RefOrderIDLength);
				gmdeItemInfo->RefOrderIDLength = this->m_prevastsTLSCURRItemInfo->RefOrderIDLength;
			}
			gmdeItemInfo->PresenceMap = pmap2;
			gmdeItemInfo->NullMap = nmap2;
			this->m_prevastsTLSCURRItemInfo = gmdeItemInfo;
		}

		info->NullMap = nmap1;
		this->m_prevastsTLSCURRInfo = info;
		return info;
	}
	inline AstsIncrementalMSRFONDInfo* DecodeAstsIncrementalMSRFOND() {
		AstsIncrementalMSRFONDInfo* info = GetFreeAstsIncrementalMSRFONDInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		if(CheckProcessNullUInt64())
			nmap1 |= NULL_MAP_INDEX0;
		else
			info->LastUpdateTime = ReadUInt64_Optional_BMI();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict12_BMI();
		AstsGenericItemInfo* gmdeItemInfo = NULL;

		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = GetFreeAstsGenericItemInfo();
			for(int i = 0; i < sizeof(AstsGenericItemInfo); i += 64)
				__builtin_prefetch(((char*)gmdeItemInfo) + i, 0, _MM_HINT_T0);
			info->GroupMDEntries[gmdeItemInfoIndex] = gmdeItemInfo;
		}
		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = info->GroupMDEntries[gmdeItemInfoIndex];
			UINT64 nmap2 = 0;

			nmap2 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_Fixed1_BMI(&(gmdeItemInfo->MDUpdateAction)) - 1);
			nmap2 |= NULL_MAP_INDEX1 & (ReadString_Optional_Fixed1(gmdeItemInfo->MDEntryType) - 1);
			nmap2 |= NULL_MAP_INDEX2 & (ReadString_Optional_PredictMax8(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength)) - 1);
			nmap2 |= NULL_MAP_INDEX3 & (ReadString_Optional_PredictMax16(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength)) - 1);
			nmap2 |= NULL_MAP_INDEX4 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->RptSeq)) - 1);
			nmap2 |= NULL_MAP_INDEX5 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntryPx)) - 1);
			nmap2 |= NULL_MAP_INDEX6 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntrySize)) - 1);
			nmap2 |= NULL_MAP_INDEX7 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryDate)) - 1);
			nmap2 |= NULL_MAP_INDEX8 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryTime)) - 1);
			nmap2 |= NULL_MAP_INDEX9 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->StartTime)) - 1);
			nmap2 |= NULL_MAP_INDEX10 & (ReadString_Optional(gmdeItemInfo->QuoteCondition, &(gmdeItemInfo->QuoteConditionLength)) - 1);
			nmap2 |= NULL_MAP_INDEX11 & (ReadString_Optional(gmdeItemInfo->TradeCondition, &(gmdeItemInfo->TradeConditionLength)) - 1);
			nmap2 |= NULL_MAP_INDEX12 & (ReadString_Optional(gmdeItemInfo->OpenCloseSettlFlag, &(gmdeItemInfo->OpenCloseSettlFlagLength)) - 1);
			nmap2 |= NULL_MAP_INDEX13 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->NetChgPrevDay)) - 1);
			nmap2 |= NULL_MAP_INDEX14 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->AccruedInterestAmt)) - 1);
			nmap2 |= NULL_MAP_INDEX15 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->ChgFromWAPrice)) - 1);
			nmap2 |= NULL_MAP_INDEX16 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->ChgOpenInterest)) - 1);
			nmap2 |= NULL_MAP_INDEX17 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->BidMarketSize)) - 1);
			nmap2 |= NULL_MAP_INDEX18 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->AskMarketSize)) - 1);
			nmap2 |= NULL_MAP_INDEX19 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->TotalNumOfTrades)) - 1);
			nmap2 |= NULL_MAP_INDEX20 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->TradeValue)) - 1);
			nmap2 |= NULL_MAP_INDEX21 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->Yield)) - 1);
			nmap2 |= NULL_MAP_INDEX22 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->OfferNbOr)) - 1);
			nmap2 |= NULL_MAP_INDEX23 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->BidNbOr)) - 1);
			nmap2 |= NULL_MAP_INDEX24 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->ChgFromSettlmnt)) - 1);
			nmap2 |= NULL_MAP_INDEX25 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MinCurrPx)) - 1);
			nmap2 |= NULL_MAP_INDEX26 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MinCurrPxChgTime)) - 1);
			nmap2 |= NULL_MAP_INDEX27 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->VolumeIndicator)) - 1);
			nmap2 |= NULL_MAP_INDEX28 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->SettlDate)) - 1);
			nmap2 |= NULL_MAP_INDEX29 & (ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength)) - 1);
			nmap2 |= NULL_MAP_INDEX30 & (ReadString_Optional(gmdeItemInfo->CXFlag, &(gmdeItemInfo->CXFlagLength)) - 1);
			nmap2 |= NULL_MAP_INDEX31 & (ReadString_Optional_Fixed4(gmdeItemInfo->TradingSessionID) - 1);
			nmap2 |= NULL_MAP_INDEX32 & (ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength)) - 1);
			gmdeItemInfo->NullMap = nmap2;
			this->m_prevastsGenericItemInfo = gmdeItemInfo;
		}

		info->NullMap = nmap1;
		this->m_prevastsIncrementalMSRFONDInfo = info;
		return info;
	}
	inline AstsIncrementalMSRCURRInfo* DecodeAstsIncrementalMSRCURR() {
		AstsIncrementalMSRCURRInfo* info = GetFreeAstsIncrementalMSRCURRInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		if(CheckProcessNullUInt64())
			nmap1 |= NULL_MAP_INDEX0;
		else
			info->LastUpdateTime = ReadUInt64_Optional_BMI();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict12_BMI();
		AstsGenericItemInfo* gmdeItemInfo = NULL;

		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = GetFreeAstsGenericItemInfo();
			for(int i = 0; i < sizeof(AstsGenericItemInfo); i += 64)
				__builtin_prefetch(((char*)gmdeItemInfo) + i, 0, _MM_HINT_T0);
			info->GroupMDEntries[gmdeItemInfoIndex] = gmdeItemInfo;
		}
		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = info->GroupMDEntries[gmdeItemInfoIndex];
			UINT64 nmap2 = 0;

			nmap2 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_Fixed1_BMI(&(gmdeItemInfo->MDUpdateAction)) - 1);
			nmap2 |= NULL_MAP_INDEX1 & (ReadString_Optional_Fixed1(gmdeItemInfo->MDEntryType) - 1);
			nmap2 |= NULL_MAP_INDEX2 & (ReadString_Optional_PredictMax8(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength)) - 1);
			nmap2 |= NULL_MAP_INDEX3 & (ReadString_Optional_PredictMax16(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength)) - 1);
			nmap2 |= NULL_MAP_INDEX4 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->RptSeq)) - 1);
			nmap2 |= NULL_MAP_INDEX5 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntryPx)) - 1);
			nmap2 |= NULL_MAP_INDEX6 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntrySize)) - 1);
			nmap2 |= NULL_MAP_INDEX7 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryDate)) - 1);
			nmap2 |= NULL_MAP_INDEX8 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryTime)) - 1);
			nmap2 |= NULL_MAP_INDEX9 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->StartTime)) - 1);
			nmap2 |= NULL_MAP_INDEX10 & (ReadString_Optional(gmdeItemInfo->QuoteCondition, &(gmdeItemInfo->QuoteConditionLength)) - 1);
			nmap2 |= NULL_MAP_INDEX11 & (ReadString_Optional(gmdeItemInfo->TradeCondition, &(gmdeItemInfo->TradeConditionLength)) - 1);
			nmap2 |= NULL_MAP_INDEX12 & (ReadString_Optional(gmdeItemInfo->OpenCloseSettlFlag, &(gmdeItemInfo->OpenCloseSettlFlagLength)) - 1);
			nmap2 |= NULL_MAP_INDEX13 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->NetChgPrevDay)) - 1);
			nmap2 |= NULL_MAP_INDEX14 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->ChgFromWAPrice)) - 1);
			nmap2 |= NULL_MAP_INDEX15 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->ChgOpenInterest)) - 1);
			nmap2 |= NULL_MAP_INDEX16 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->BidMarketSize)) - 1);
			nmap2 |= NULL_MAP_INDEX17 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->AskMarketSize)) - 1);
			nmap2 |= NULL_MAP_INDEX18 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->TotalNumOfTrades)) - 1);
			nmap2 |= NULL_MAP_INDEX19 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->TradeValue)) - 1);
			nmap2 |= NULL_MAP_INDEX20 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->OfferNbOr)) - 1);
			nmap2 |= NULL_MAP_INDEX21 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->BidNbOr)) - 1);
			nmap2 |= NULL_MAP_INDEX22 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->ChgFromSettlmnt)) - 1);
			nmap2 |= NULL_MAP_INDEX23 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->SettlDate)) - 1);
			nmap2 |= NULL_MAP_INDEX24 & (ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength)) - 1);
			nmap2 |= NULL_MAP_INDEX25 & (ReadString_Optional(gmdeItemInfo->CXFlag, &(gmdeItemInfo->CXFlagLength)) - 1);
			nmap2 |= NULL_MAP_INDEX26 & (ReadString_Optional_Fixed4(gmdeItemInfo->TradingSessionID) - 1);
			nmap2 |= NULL_MAP_INDEX27 & (ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength)) - 1);
			gmdeItemInfo->NullMap = nmap2;
			this->m_prevastsGenericItemInfo = gmdeItemInfo;
		}

		info->NullMap = nmap1;
		this->m_prevastsIncrementalMSRCURRInfo = info;
		return info;
	}
	inline AstsIncrementalOLRFONDInfo* DecodeAstsIncrementalOLRFOND() {
		AstsIncrementalOLRFONDInfo* info = GetFreeAstsIncrementalOLRFONDInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict12_BMI();
		AstsOLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = GetFreeAstsOLSFONDItemInfo();
			for(int i = 0; i < sizeof(AstsOLSFONDItemInfo); i += 64)
				__builtin_prefetch(((char*)gmdeItemInfo) + i, 0, _MM_HINT_T0);
			info->GroupMDEntries[gmdeItemInfoIndex] = gmdeItemInfo;
		}
		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = info->GroupMDEntries[gmdeItemInfoIndex];

			UINT64 pmap2 = this->ParsePresenceMap2();
			UINT64 nmap2 = 0;

			if(pmap2 != 0) {
				nmap2 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_Fixed1_BMI(&(gmdeItemInfo->MDUpdateAction)) - 1);
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX0)) {
					nmap2 |= NULL_MAP_INDEX1 & (ReadString_Optional_Fixed1(gmdeItemInfo->MDEntryType) - 1);
				}
				else {
					this->CopyString_Fixed1(gmdeItemInfo->MDEntryType, m_prevastsOLSFONDItemInfo->MDEntryType);
				}
				nmap2 |= NULL_MAP_INDEX2 & (ReadString_Optional_PredictMax8(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength)) - 1);
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX1)) {
					nmap2 |= NULL_MAP_INDEX3 & (ReadString_Optional_PredictMax16(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength)) - 1);
				}
				else {
					this->CopyString_PredictMax16(gmdeItemInfo->Symbol, m_prevastsOLSFONDItemInfo->Symbol);
					gmdeItemInfo->SymbolLength = this->m_prevastsOLSFONDItemInfo->SymbolLength;
				}
				nmap2 |= NULL_MAP_INDEX4 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->RptSeq)) - 1);
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX2)) {
					nmap2 |= NULL_MAP_INDEX5 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryDate)) - 1);
				}
				else {
					gmdeItemInfo->MDEntryDate = this->m_prevastsOLSFONDItemInfo->MDEntryDate;
				}
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX3)) {
					nmap2 |= NULL_MAP_INDEX6 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryTime)) - 1);
				}
				else {
					gmdeItemInfo->MDEntryTime = this->m_prevastsOLSFONDItemInfo->MDEntryTime;
				}
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX4)) {
					nmap2 |= NULL_MAP_INDEX7 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->OrigTime)) - 1);
				}
				else {
					gmdeItemInfo->OrigTime = this->m_prevastsOLSFONDItemInfo->OrigTime;
				}
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX5)) {
					nmap2 |= NULL_MAP_INDEX8 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntryPx)) - 1);
				}
				else {
					gmdeItemInfo->MDEntryPx = this->m_prevastsOLSFONDItemInfo->MDEntryPx;
				}
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX6)) {
					nmap2 |= NULL_MAP_INDEX9 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntrySize)) - 1);
				}
				else {
					gmdeItemInfo->MDEntrySize = this->m_prevastsOLSFONDItemInfo->MDEntrySize;
				}
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX7)) {
					nmap2 |= NULL_MAP_INDEX10 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->Yield)) - 1);
				}
				else {
					gmdeItemInfo->Yield = this->m_prevastsOLSFONDItemInfo->Yield;
				}
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX8)) {
					nmap2 |= NULL_MAP_INDEX11 & (ReadString_Optional_Fixed1(gmdeItemInfo->OrderStatus) - 1);
				}
				else {
					this->CopyString_Fixed1(gmdeItemInfo->OrderStatus, m_prevastsOLSFONDItemInfo->OrderStatus);
				}
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX9)) {
					nmap2 |= NULL_MAP_INDEX12 & (ReadString_Optional_Fixed1(gmdeItemInfo->OrdType) - 1);
				}
				else {
					this->CopyString_Fixed1(gmdeItemInfo->OrdType, m_prevastsOLSFONDItemInfo->OrdType);
				}
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX10)) {
					nmap2 |= NULL_MAP_INDEX13 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->TotalVolume)) - 1);
				}
				else {
					gmdeItemInfo->TotalVolume = this->m_prevastsOLSFONDItemInfo->TotalVolume;
				}
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX11)) {
					nmap2 |= NULL_MAP_INDEX14 & (ReadString_Optional_Fixed4(gmdeItemInfo->TradingSessionID) - 1);
				}
				else {
					gmdeItemInfo->TradingSessionIDUint = this->m_prevastsOLSFONDItemInfo->TradingSessionIDUint;
				}
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX12)) {
					nmap2 |= NULL_MAP_INDEX15 & (ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength)) - 1);
				}
				else {
					this->CopyString_Predict12(gmdeItemInfo->TradingSessionSubID, m_prevastsOLSFONDItemInfo->TradingSessionSubID);
					gmdeItemInfo->TradingSessionSubIDLength = this->m_prevastsOLSFONDItemInfo->TradingSessionSubIDLength;
				}
				gmdeItemInfo->PresenceMap = pmap2;
				gmdeItemInfo->NullMap = nmap2;
			}
			else {
				gmdeItemInfo->Assign(this->m_prevastsOLSFONDItemInfo);
				nmap2 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_Fixed1_BMI(&(gmdeItemInfo->MDUpdateAction)) - 1);
				nmap2 |= NULL_MAP_INDEX2 & (ReadString_Optional_PredictMax8(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength)) - 1);
				nmap2 |= NULL_MAP_INDEX4 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->RptSeq)) - 1);
				gmdeItemInfo->PresenceMap = pmap2;
				gmdeItemInfo->NullMap = this->m_prevastsOLSFONDItemInfo->NullMap;
			}
			this->m_prevastsOLSFONDItemInfo = gmdeItemInfo;
		}

		info->NullMap = nmap1;
		this->m_prevastsIncrementalOLRFONDInfo = info;
		return info;
	}
	inline AstsIncrementalOLRCURRInfo* DecodeAstsIncrementalOLRCURR() {
		AstsIncrementalOLRCURRInfo* info = GetFreeAstsIncrementalOLRCURRInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict12_BMI();
		AstsOLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = GetFreeAstsOLSCURRItemInfo();
			for(int i = 0; i < sizeof(AstsOLSCURRItemInfo); i += 64)
				__builtin_prefetch(((char*)gmdeItemInfo) + i, 0, _MM_HINT_T0);
			info->GroupMDEntries[gmdeItemInfoIndex] = gmdeItemInfo;
		}
		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = info->GroupMDEntries[gmdeItemInfoIndex];

			UINT64 pmap2 = this->ParsePresenceMap2();
			UINT64 nmap2 = 0;

			if(pmap2 != 0) {
				if(pmap2 == 6263) {
					nmap2 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_Fixed1_BMI(&(gmdeItemInfo->MDUpdateAction)) - 1);
					nmap2 |= NULL_MAP_INDEX1 & (ReadString_Optional_Fixed1(gmdeItemInfo->MDEntryType) - 1);
					nmap2 |= NULL_MAP_INDEX2 & (ReadString_Optional_PredictMax8(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength)) - 1);
					nmap2 |= NULL_MAP_INDEX3 & (ReadString_Optional_PredictMax16(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength)) - 1);
					nmap2 |= NULL_MAP_INDEX4 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->RptSeq)) - 1);
					gmdeItemInfo->MDEntryDate = this->m_prevastsOLSCURRItemInfo->MDEntryDate;
					nmap2 |= NULL_MAP_INDEX6 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryTime)) - 1);
					nmap2 |= NULL_MAP_INDEX7 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->OrigTime)) - 1);
					nmap2 |= NULL_MAP_INDEX8 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntryPx)) - 1);
					gmdeItemInfo->MDEntrySize = this->m_prevastsOLSCURRItemInfo->MDEntrySize;
					this->CopyString_Fixed1(gmdeItemInfo->OrderStatus, m_prevastsOLSCURRItemInfo->OrderStatus);
					nmap2 |= NULL_MAP_INDEX11 & (ReadString_Optional_Fixed4(gmdeItemInfo->TradingSessionID) - 1);
					nmap2 |= NULL_MAP_INDEX12 & (ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength)) - 1);
					gmdeItemInfo->PresenceMap = pmap2;
					gmdeItemInfo->NullMap = nmap2;
					this->m_prevastsOLSCURRItemInfo = gmdeItemInfo;
					continue;
				}
				if(pmap2 == 30839) {
					nmap2 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_Fixed1_BMI(&(gmdeItemInfo->MDUpdateAction)) - 1);
					nmap2 |= NULL_MAP_INDEX1 & (ReadString_Optional_Fixed1(gmdeItemInfo->MDEntryType) - 1);
					nmap2 |= NULL_MAP_INDEX2 & (ReadString_Optional_PredictMax8(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength)) - 1);
					nmap2 |= NULL_MAP_INDEX3 & (ReadString_Optional_PredictMax16(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength)) - 1);
					nmap2 |= NULL_MAP_INDEX4 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->RptSeq)) - 1);
					gmdeItemInfo->MDEntryDate = this->m_prevastsOLSCURRItemInfo->MDEntryDate;
					nmap2 |= NULL_MAP_INDEX6 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryTime)) - 1);
					nmap2 |= NULL_MAP_INDEX7 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->OrigTime)) - 1);
					nmap2 |= NULL_MAP_INDEX8 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntryPx)) - 1);
					nmap2 |= NULL_MAP_INDEX9 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntrySize)) - 1);
					nmap2 |= NULL_MAP_INDEX10 & (ReadString_Optional_Fixed1(gmdeItemInfo->OrderStatus) - 1);
					nmap2 |= NULL_MAP_INDEX11 & (ReadString_Optional_Fixed4(gmdeItemInfo->TradingSessionID) - 1);
					nmap2 |= NULL_MAP_INDEX12 & (ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength)) - 1);
					gmdeItemInfo->PresenceMap = pmap2;
					gmdeItemInfo->NullMap = nmap2;
					this->m_prevastsOLSCURRItemInfo = gmdeItemInfo;
					continue;
				}
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX0)) {
					nmap2 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_Fixed1_BMI(&(gmdeItemInfo->MDUpdateAction)) - 1);
				}
				else {
					gmdeItemInfo->MDUpdateAction = this->m_prevastsOLSCURRItemInfo->MDUpdateAction;
				}
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX1)) {
					nmap2 |= NULL_MAP_INDEX1 & (ReadString_Optional_Fixed1(gmdeItemInfo->MDEntryType) - 1);
				}
				else {
					this->CopyString_Fixed1(gmdeItemInfo->MDEntryType, m_prevastsOLSCURRItemInfo->MDEntryType);
				}
				nmap2 |= NULL_MAP_INDEX2 & (ReadString_Optional_PredictMax8(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength)) - 1);
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX2)) {
					nmap2 |= NULL_MAP_INDEX3 & (ReadString_Optional_PredictMax16(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength)) - 1);
				}
				else {
					this->CopyString_PredictMax16(gmdeItemInfo->Symbol, m_prevastsOLSCURRItemInfo->Symbol);
					gmdeItemInfo->SymbolLength = this->m_prevastsOLSCURRItemInfo->SymbolLength;
				}
				nmap2 |= NULL_MAP_INDEX4 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->RptSeq)) - 1);
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX3)) {
					nmap2 |= NULL_MAP_INDEX5 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryDate)) - 1);
				}
				else {
					gmdeItemInfo->MDEntryDate = this->m_prevastsOLSCURRItemInfo->MDEntryDate;
				}
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX4)) {
					nmap2 |= NULL_MAP_INDEX6 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryTime)) - 1);
				}
				else {
					gmdeItemInfo->MDEntryTime = this->m_prevastsOLSCURRItemInfo->MDEntryTime;
				}
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX5)) {
					nmap2 |= NULL_MAP_INDEX7 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->OrigTime)) - 1);
				}
				else {
					gmdeItemInfo->OrigTime = this->m_prevastsOLSCURRItemInfo->OrigTime;
				}
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX6)) {
					nmap2 |= NULL_MAP_INDEX8 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntryPx)) - 1);
				}
				else {
					gmdeItemInfo->MDEntryPx = this->m_prevastsOLSCURRItemInfo->MDEntryPx;
				}
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX7)) {
					nmap2 |= NULL_MAP_INDEX9 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntrySize)) - 1);
				}
				else {
					gmdeItemInfo->MDEntrySize = this->m_prevastsOLSCURRItemInfo->MDEntrySize;
				}
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX8)) {
					nmap2 |= NULL_MAP_INDEX10 & (ReadString_Optional_Fixed1(gmdeItemInfo->OrderStatus) - 1);
				}
				else {
					this->CopyString_Fixed1(gmdeItemInfo->OrderStatus, m_prevastsOLSCURRItemInfo->OrderStatus);
				}
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX9)) {
					nmap2 |= NULL_MAP_INDEX11 & (ReadString_Optional_Fixed4(gmdeItemInfo->TradingSessionID) - 1);
				}
				else {
					gmdeItemInfo->TradingSessionIDUint = this->m_prevastsOLSCURRItemInfo->TradingSessionIDUint;
				}
				if(CheckOptionalFieldPresence(pmap2, PRESENCE_MAP_INDEX10)) {
					nmap2 |= NULL_MAP_INDEX12 & (ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength)) - 1);
				}
				else {
					this->CopyString_Predict12(gmdeItemInfo->TradingSessionSubID, m_prevastsOLSCURRItemInfo->TradingSessionSubID);
					gmdeItemInfo->TradingSessionSubIDLength = this->m_prevastsOLSCURRItemInfo->TradingSessionSubIDLength;
				}
				gmdeItemInfo->PresenceMap = pmap2;
				gmdeItemInfo->NullMap = nmap2;
			}
			else {
				gmdeItemInfo->Assign(this->m_prevastsOLSCURRItemInfo);
				nmap2 |= NULL_MAP_INDEX2 & (ReadString_Optional_PredictMax8(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength)) - 1);
				nmap2 |= NULL_MAP_INDEX4 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->RptSeq)) - 1);
				gmdeItemInfo->PresenceMap = pmap2;
				gmdeItemInfo->NullMap = this->m_prevastsOLSCURRItemInfo->NullMap;
			}
			this->m_prevastsOLSCURRItemInfo = gmdeItemInfo;
		}

		info->NullMap = nmap1;
		this->m_prevastsIncrementalOLRCURRInfo = info;
		return info;
	}
	inline AstsIncrementalTLRFONDInfo* DecodeAstsIncrementalTLRFOND() {
		AstsIncrementalTLRFONDInfo* info = GetFreeAstsIncrementalTLRFONDInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict12_BMI();
		AstsTLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = GetFreeAstsTLSFONDItemInfo();
			for(int i = 0; i < sizeof(AstsTLSFONDItemInfo); i += 64)
				__builtin_prefetch(((char*)gmdeItemInfo) + i, 0, _MM_HINT_T0);
			info->GroupMDEntries[gmdeItemInfoIndex] = gmdeItemInfo;
		}
		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = info->GroupMDEntries[gmdeItemInfoIndex];
			UINT64 nmap2 = 0;

			nmap2 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_Fixed1_BMI(&(gmdeItemInfo->MDUpdateAction)) - 1);
			ReadString_Mandatory_Fixed1(gmdeItemInfo->MDEntryType);
			nmap2 |= NULL_MAP_INDEX1 & (ReadString_Optional_PredictMax8(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength)) - 1);
			nmap2 |= NULL_MAP_INDEX2 & (ReadString_Optional_PredictMax16(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength)) - 1);
			nmap2 |= NULL_MAP_INDEX3 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->RptSeq)) - 1);
			nmap2 |= NULL_MAP_INDEX4 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryDate)) - 1);
			nmap2 |= NULL_MAP_INDEX5 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryTime)) - 1);
			nmap2 |= NULL_MAP_INDEX6 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->OrigTime)) - 1);
			nmap2 |= NULL_MAP_INDEX7 & (ReadString_Optional(gmdeItemInfo->OrderSide, &(gmdeItemInfo->OrderSideLength)) - 1);
			nmap2 |= NULL_MAP_INDEX8 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntryPx)) - 1);
			nmap2 |= NULL_MAP_INDEX9 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntrySize)) - 1);
			nmap2 |= NULL_MAP_INDEX10 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->AccruedInterestAmt)) - 1);
			nmap2 |= NULL_MAP_INDEX11 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->TradeValue)) - 1);
			nmap2 |= NULL_MAP_INDEX12 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->Yield)) - 1);
			nmap2 |= NULL_MAP_INDEX13 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->SettlDate)) - 1);
			nmap2 |= NULL_MAP_INDEX14 & (ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength)) - 1);
			nmap2 |= NULL_MAP_INDEX15 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->Price)) - 1);
			nmap2 |= NULL_MAP_INDEX16 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->PriceType)) - 1);
			nmap2 |= NULL_MAP_INDEX17 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->RepoToPx)) - 1);
			nmap2 |= NULL_MAP_INDEX18 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->BuyBackPx)) - 1);
			nmap2 |= NULL_MAP_INDEX19 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->BuyBackDate)) - 1);
			nmap2 |= NULL_MAP_INDEX20 & (ReadString_Optional_Fixed4(gmdeItemInfo->TradingSessionID) - 1);
			nmap2 |= NULL_MAP_INDEX21 & (ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength)) - 1);
			nmap2 |= NULL_MAP_INDEX22 & (ReadString_Optional(gmdeItemInfo->RefOrderID, &(gmdeItemInfo->RefOrderIDLength)) - 1);
			gmdeItemInfo->NullMap = nmap2;
			this->m_prevastsTLSFONDItemInfo = gmdeItemInfo;
		}

		info->NullMap = nmap1;
		this->m_prevastsIncrementalTLRFONDInfo = info;
		return info;
	}
	inline AstsIncrementalTLRCURRInfo* DecodeAstsIncrementalTLRCURR() {
		AstsIncrementalTLRCURRInfo* info = GetFreeAstsIncrementalTLRCURRInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict12_BMI();
		AstsTLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = GetFreeAstsTLSCURRItemInfo();
			for(int i = 0; i < sizeof(AstsTLSCURRItemInfo); i += 64)
				__builtin_prefetch(((char*)gmdeItemInfo) + i, 0, _MM_HINT_T0);
			info->GroupMDEntries[gmdeItemInfoIndex] = gmdeItemInfo;
		}
		for(int gmdeItemInfoIndex = 0; gmdeItemInfoIndex < info->GroupMDEntriesCount; gmdeItemInfoIndex++) {
			gmdeItemInfo = info->GroupMDEntries[gmdeItemInfoIndex];
			UINT64 nmap2 = 0;

			nmap2 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_Fixed1_BMI(&(gmdeItemInfo->MDUpdateAction)) - 1);
			ReadString_Mandatory_Fixed1(gmdeItemInfo->MDEntryType);
			nmap2 |= NULL_MAP_INDEX1 & (ReadString_Optional_PredictMax8(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength)) - 1);
			nmap2 |= NULL_MAP_INDEX2 & (ReadString_Optional_PredictMax16(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength)) - 1);
			nmap2 |= NULL_MAP_INDEX3 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->RptSeq)) - 1);
			nmap2 |= NULL_MAP_INDEX4 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryDate)) - 1);
			nmap2 |= NULL_MAP_INDEX5 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->MDEntryTime)) - 1);
			nmap2 |= NULL_MAP_INDEX6 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->OrigTime)) - 1);
			nmap2 |= NULL_MAP_INDEX7 & (ReadString_Optional(gmdeItemInfo->OrderSide, &(gmdeItemInfo->OrderSideLength)) - 1);
			nmap2 |= NULL_MAP_INDEX8 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntryPx)) - 1);
			nmap2 |= NULL_MAP_INDEX9 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->MDEntrySize)) - 1);
			nmap2 |= NULL_MAP_INDEX10 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->TradeValue)) - 1);
			nmap2 |= NULL_MAP_INDEX11 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->SettlDate)) - 1);
			nmap2 |= NULL_MAP_INDEX12 & (ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength)) - 1);
			nmap2 |= NULL_MAP_INDEX13 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->Price)) - 1);
			nmap2 |= NULL_MAP_INDEX14 & (ReadInt32_Optional_BMI(&(gmdeItemInfo->PriceType)) - 1);
			nmap2 |= NULL_MAP_INDEX15 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->RepoToPx)) - 1);
			nmap2 |= NULL_MAP_INDEX16 & (ReadDecimal_Optional_BMI(&(gmdeItemInfo->BuyBackPx)) - 1);
			nmap2 |= NULL_MAP_INDEX17 & (ReadUInt32_Optional_BMI(&(gmdeItemInfo->BuyBackDate)) - 1);
			nmap2 |= NULL_MAP_INDEX18 & (ReadString_Optional_Fixed4(gmdeItemInfo->TradingSessionID) - 1);
			nmap2 |= NULL_MAP_INDEX19 & (ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength)) - 1);
			nmap2 |= NULL_MAP_INDEX20 & (ReadString_Optional(gmdeItemInfo->RefOrderID, &(gmdeItemInfo->RefOrderIDLength)) - 1);
			gmdeItemInfo->NullMap = nmap2;
			this->m_prevastsTLSCURRItemInfo = gmdeItemInfo;
		}

		info->NullMap = nmap1;
		this->m_prevastsIncrementalTLRCURRInfo = info;
		return info;
	}
	inline AstsSecurityDefinitionInfo* DecodeAstsSecurityDefinition() {
		AstsSecurityDefinitionInfo* info = GetFreeAstsSecurityDefinitionInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		nmap1 |= NULL_MAP_INDEX0 & (ReadInt32_Optional_BMI(&(info->TotNumReports)) - 1);
		nmap1 |= NULL_MAP_INDEX1 & (ReadString_Optional_PredictMax16(info->Symbol, &(info->SymbolLength)) - 1);
		if(CheckProcessNullByteVector())
			nmap1 |= NULL_MAP_INDEX2;
		else
			ReadByteVector_Optional(info->SecurityID, &(info->SecurityIDLength), 128);
		if(CheckProcessNullByteVector())
			nmap1 |= NULL_MAP_INDEX3;
		else
			ReadByteVector_Optional(info->SecurityIDSource, &(info->SecurityIDSourceLength), 128);
		nmap1 |= NULL_MAP_INDEX4 & (ReadInt32_Optional_BMI(&(info->Product)) - 1);
		if(CheckProcessNullByteVector())
			nmap1 |= NULL_MAP_INDEX5;
		else
			ReadByteVector_Optional(info->CFICode, &(info->CFICodeLength), 128);
		if(CheckProcessNullByteVector())
			nmap1 |= NULL_MAP_INDEX6;
		else
			ReadByteVector_Optional(info->SecurityType, &(info->SecurityTypeLength), 128);
		nmap1 |= NULL_MAP_INDEX7 & (ReadUInt32_Optional_BMI(&(info->MaturityDate)) - 1);
		nmap1 |= NULL_MAP_INDEX8 & (ReadUInt32_Optional_BMI(&(info->SettlDate)) - 1);
		nmap1 |= NULL_MAP_INDEX9 & (ReadString_Optional(info->SettleType, &(info->SettleTypeLength)) - 1);
		nmap1 |= NULL_MAP_INDEX10 & (ReadDecimal_Optional_BMI(&(info->OrigIssueAmt)) - 1);
		nmap1 |= NULL_MAP_INDEX11 & (ReadUInt32_Optional_BMI(&(info->CouponPaymentDate)) - 1);
		nmap1 |= NULL_MAP_INDEX12 & (ReadDecimal_Optional_BMI(&(info->CouponRate)) - 1);
		nmap1 |= NULL_MAP_INDEX13 & (ReadUInt32_Optional_BMI(&(info->SettlFixingDate)) - 1);
		nmap1 |= NULL_MAP_INDEX14 & (ReadDecimal_Optional_BMI(&(info->DividendNetPx)) - 1);
		if(CheckProcessNullByteVector())
			nmap1 |= NULL_MAP_INDEX15;
		else
			ReadByteVector_Optional(info->SecurityDesc, &(info->SecurityDescLength), 128);
		if(CheckProcessNullByteVector())
			nmap1 |= NULL_MAP_INDEX16;
		else
			ReadByteVector_Optional(info->EncodedSecurityDesc, &(info->EncodedSecurityDescLength), 128);
		if(CheckProcessNullByteVector())
			nmap1 |= NULL_MAP_INDEX17;
		else
			ReadByteVector_Optional(info->QuoteText, &(info->QuoteTextLength), 128);

		if(!ReadUInt32_Optional_Predict12_BMI((UINT32*)&(info->GroupInstrAttribCount))) {
			info->GroupInstrAttribCount = 0;
			nmap1 |= NULL_MAP_INDEX18;
		}
		AstsSecurityDefinitionGroupInstrAttribItemInfo* giaItemInfo = NULL;

		for(int giaItemInfoIndex = 0; giaItemInfoIndex < info->GroupInstrAttribCount; giaItemInfoIndex++) {
			giaItemInfo = GetFreeAstsSecurityDefinitionGroupInstrAttribItemInfo();
			for(int i = 0; i < sizeof(AstsSecurityDefinitionGroupInstrAttribItemInfo); i += 64)
				__builtin_prefetch(((char*)giaItemInfo) + i, 0, _MM_HINT_T0);
			info->GroupInstrAttrib[giaItemInfoIndex] = giaItemInfo;
		}
		for(int giaItemInfoIndex = 0; giaItemInfoIndex < info->GroupInstrAttribCount; giaItemInfoIndex++) {
			giaItemInfo = info->GroupInstrAttrib[giaItemInfoIndex];
			UINT64 nmap2 = 0;

			giaItemInfo->InstrAttribType = ReadInt32_Mandatory_BMI();
			if(CheckProcessNullByteVector())
				nmap2 |= NULL_MAP_INDEX0;
			else
				ReadByteVector_Optional(giaItemInfo->InstrAttribValue, &(giaItemInfo->InstrAttribValueLength), 128);
			giaItemInfo->NullMap = nmap2;
			this->m_prevastsSecurityDefinitionGroupInstrAttribItemInfo = giaItemInfo;
		}

		nmap1 |= NULL_MAP_INDEX19 & (ReadString_Optional(info->Currency, &(info->CurrencyLength)) - 1);

		if(!ReadUInt32_Optional_Predict12_BMI((UINT32*)&(info->MarketSegmentGrpCount))) {
			info->MarketSegmentGrpCount = 0;
			nmap1 |= NULL_MAP_INDEX20;
		}
		AstsSecurityDefinitionMarketSegmentGrpItemInfo* msgItemInfo = NULL;

		for(int msgItemInfoIndex = 0; msgItemInfoIndex < info->MarketSegmentGrpCount; msgItemInfoIndex++) {
			msgItemInfo = GetFreeAstsSecurityDefinitionMarketSegmentGrpItemInfo();
			for(int i = 0; i < sizeof(AstsSecurityDefinitionMarketSegmentGrpItemInfo); i += 64)
				__builtin_prefetch(((char*)msgItemInfo) + i, 0, _MM_HINT_T0);
			info->MarketSegmentGrp[msgItemInfoIndex] = msgItemInfo;
		}
		for(int msgItemInfoIndex = 0; msgItemInfoIndex < info->MarketSegmentGrpCount; msgItemInfoIndex++) {
			msgItemInfo = info->MarketSegmentGrp[msgItemInfoIndex];
			UINT64 nmap2 = 0;

			nmap2 |= NULL_MAP_INDEX0 & (ReadDecimal_Optional_BMI(&(msgItemInfo->RoundLot)) - 1);

			if(!ReadUInt32_Optional_Predict12_BMI((UINT32*)&(msgItemInfo->TradingSessionRulesGrpCount))) {
				msgItemInfo->TradingSessionRulesGrpCount = 0;
				nmap2 |= NULL_MAP_INDEX1;
			}
			AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* tsrgItemInfo = NULL;

			for(int tsrgItemInfoIndex = 0; tsrgItemInfoIndex < msgItemInfo->TradingSessionRulesGrpCount; tsrgItemInfoIndex++) {
				tsrgItemInfo = GetFreeAstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo();
				for(int i = 0; i < sizeof(AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo); i += 64)
					__builtin_prefetch(((char*)tsrgItemInfo) + i, 0, _MM_HINT_T0);
				msgItemInfo->TradingSessionRulesGrp[tsrgItemInfoIndex] = tsrgItemInfo;
			}
			for(int tsrgItemInfoIndex = 0; tsrgItemInfoIndex < msgItemInfo->TradingSessionRulesGrpCount; tsrgItemInfoIndex++) {
				tsrgItemInfo = msgItemInfo->TradingSessionRulesGrp[tsrgItemInfoIndex];
				UINT64 nmap3 = 0;

				ReadString_Mandatory_Fixed4(tsrgItemInfo->TradingSessionID);
				nmap3 |= NULL_MAP_INDEX0 & (ReadString_Optional_Predict12(tsrgItemInfo->TradingSessionSubID, &(tsrgItemInfo->TradingSessionSubIDLength)) - 1);
				nmap3 |= NULL_MAP_INDEX1 & (ReadInt32_Optional_BMI(&(tsrgItemInfo->SecurityTradingStatus)) - 1);
				nmap3 |= NULL_MAP_INDEX2 & (ReadInt32_Optional_BMI(&(tsrgItemInfo->OrderNote)) - 1);
				tsrgItemInfo->NullMap = nmap3;
				this->m_prevastsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo = tsrgItemInfo;
			}

			msgItemInfo->NullMap = nmap2;
			this->m_prevastsSecurityDefinitionMarketSegmentGrpItemInfo = msgItemInfo;
		}

		nmap1 |= NULL_MAP_INDEX21 & (ReadString_Optional(info->SettlCurrency, &(info->SettlCurrencyLength)) - 1);
		nmap1 |= NULL_MAP_INDEX22 & (ReadInt32_Optional_BMI(&(info->PriceType)) - 1);
		nmap1 |= NULL_MAP_INDEX23 & (ReadString_Optional(info->StateSecurityID, &(info->StateSecurityIDLength)) - 1);
		if(CheckProcessNullByteVector())
			nmap1 |= NULL_MAP_INDEX24;
		else
			ReadByteVector_Optional(info->EncodedShortSecurityDesc, &(info->EncodedShortSecurityDescLength), 128);
		if(CheckProcessNullByteVector())
			nmap1 |= NULL_MAP_INDEX25;
		else
			ReadByteVector_Optional(info->MarketCode, &(info->MarketCodeLength), 128);
		nmap1 |= NULL_MAP_INDEX26 & (ReadDecimal_Optional_BMI(&(info->MinPriceIncrement)) - 1);
		nmap1 |= NULL_MAP_INDEX27 & (ReadDecimal_Optional_BMI(&(info->MktShareLimit)) - 1);
		nmap1 |= NULL_MAP_INDEX28 & (ReadDecimal_Optional_BMI(&(info->MktShareThreshold)) - 1);
		nmap1 |= NULL_MAP_INDEX29 & (ReadDecimal_Optional_BMI(&(info->MaxOrdersVolume)) - 1);
		nmap1 |= NULL_MAP_INDEX30 & (ReadDecimal_Optional_BMI(&(info->PriceMvmLimit)) - 1);
		nmap1 |= NULL_MAP_INDEX31 & (ReadDecimal_Optional_BMI(&(info->FaceValue)) - 1);
		nmap1 |= NULL_MAP_INDEX32 & (ReadDecimal_Optional_BMI(&(info->BaseSwapPx)) - 1);
		nmap1 |= NULL_MAP_INDEX33 & (ReadDecimal_Optional_BMI(&(info->RepoToPx)) - 1);
		nmap1 |= NULL_MAP_INDEX34 & (ReadDecimal_Optional_BMI(&(info->BuyBackPx)) - 1);
		nmap1 |= NULL_MAP_INDEX35 & (ReadUInt32_Optional_BMI(&(info->BuyBackDate)) - 1);
		nmap1 |= NULL_MAP_INDEX36 & (ReadDecimal_Optional_BMI(&(info->NoSharesIssued)) - 1);
		nmap1 |= NULL_MAP_INDEX37 & (ReadDecimal_Optional_BMI(&(info->HighLimit)) - 1);
		nmap1 |= NULL_MAP_INDEX38 & (ReadDecimal_Optional_BMI(&(info->LowLimit)) - 1);
		nmap1 |= NULL_MAP_INDEX39 & (ReadInt32_Optional_BMI(&(info->NumOfDaysToMaturity)) - 1);
		info->NullMap = nmap1;
		this->m_prevastsSecurityDefinitionInfo = info;
		return info;
	}
	inline AstsSecurityStatusInfo* DecodeAstsSecurityStatus() {
		AstsSecurityStatusInfo* info = GetFreeAstsSecurityStatusInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		ReadString_Mandatory_PredictMax16(info->Symbol, &(info->SymbolLength));
		nmap1 |= NULL_MAP_INDEX0 & (ReadString_Optional_Fixed4(info->TradingSessionID) - 1);
		nmap1 |= NULL_MAP_INDEX1 & (ReadString_Optional_Predict12(info->TradingSessionSubID, &(info->TradingSessionSubIDLength)) - 1);
		nmap1 |= NULL_MAP_INDEX2 & (ReadInt32_Optional_BMI(&(info->SecurityTradingStatus)) - 1);
		nmap1 |= NULL_MAP_INDEX3 & (ReadUInt32_Optional_BMI(&(info->AuctionIndicator)) - 1);
		info->NullMap = nmap1;
		this->m_prevastsSecurityStatusInfo = info;
		return info;
	}
	inline AstsTradingSessionStatusInfo* DecodeAstsTradingSessionStatus() {
		AstsTradingSessionStatusInfo* info = GetFreeAstsTradingSessionStatusInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		info->TradSesStatus = ReadInt32_Mandatory_BMI();
		nmap1 |= NULL_MAP_INDEX0 & (ReadString_Optional(info->Text, &(info->TextLength)) - 1);
		ReadString_Mandatory_Fixed4(info->TradingSessionID);
		info->NullMap = nmap1;
		this->m_prevastsTradingSessionStatusInfo = info;
		return info;
	}
	inline AstsHeartbeatInfo* DecodeAstsHeartbeat() {
		AstsHeartbeatInfo* info = GetFreeAstsHeartbeatInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		info->NullMap = nmap1;
		this->m_prevastsHeartbeatInfo = info;
		return info;
	}
	inline AstsSnapshotInfo* GetAstsSnapshotInfoGeneric() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		UINT64 nmap1 = 0;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		nmap1 |= NULL_MAP_INDEX0 & (ReadString_Optional_Fixed4(info->TradingSessionID) - 1);
		ReadString_Mandatory_PredictMax16(info->Symbol, &(info->SymbolLength));
		nmap1 |= NULL_MAP_INDEX1 & (ReadUInt32_Optional_BMI(&(info->LastMsgSeqNumProcessed)) - 1);
		info->RptSeq = ReadInt32_Mandatory_BMI();
		nmap1 |= NULL_MAP_INDEX2 & (ReadUInt32_Optional_BMI(&(info->LastFragment)) - 1);
		nmap1 |= NULL_MAP_INDEX3 & (ReadUInt32_Optional_BMI(&(info->RouteFirst)) - 1);
		info->NullMap = nmap1;
		return info;
	}
	inline AstsSnapshotInfo* GetAstsSnapshotInfoOLSFOND() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		UINT64 nmap1 = 0;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		nmap1 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_BMI(&(info->LastMsgSeqNumProcessed)) - 1);
		info->RptSeq = ReadInt32_Mandatory_BMI();
		nmap1 |= NULL_MAP_INDEX1 & (ReadUInt32_Optional_BMI(&(info->LastFragment)) - 1);
		nmap1 |= NULL_MAP_INDEX2 & (ReadUInt32_Optional_BMI(&(info->RouteFirst)) - 1);
		SkipToNextField(); // TradSesStatus
		nmap1 |= NULL_MAP_INDEX4 & (ReadString_Optional_Fixed4(info->TradingSessionID) - 1);
		ReadString_Mandatory_PredictMax16(info->Symbol, &(info->SymbolLength));
		info->NullMap = nmap1;
		return info;
	}
	inline AstsSnapshotInfo* GetAstsSnapshotInfoOLSCURR() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		UINT64 nmap1 = 0;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		nmap1 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_BMI(&(info->LastMsgSeqNumProcessed)) - 1);
		info->RptSeq = ReadInt32_Mandatory_BMI();
		nmap1 |= NULL_MAP_INDEX1 & (ReadUInt32_Optional_BMI(&(info->LastFragment)) - 1);
		nmap1 |= NULL_MAP_INDEX2 & (ReadUInt32_Optional_BMI(&(info->RouteFirst)) - 1);
		SkipToNextField(); // TradSesStatus
		nmap1 |= NULL_MAP_INDEX4 & (ReadString_Optional_Fixed4(info->TradingSessionID) - 1);
		ReadString_Mandatory_PredictMax16(info->Symbol, &(info->SymbolLength));
		info->NullMap = nmap1;
		return info;
	}
	inline AstsSnapshotInfo* GetAstsSnapshotInfoTLSFOND() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		UINT64 nmap1 = 0;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		nmap1 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_BMI(&(info->LastMsgSeqNumProcessed)) - 1);
		info->RptSeq = ReadInt32_Mandatory_BMI();
		nmap1 |= NULL_MAP_INDEX1 & (ReadUInt32_Optional_BMI(&(info->LastFragment)) - 1);
		nmap1 |= NULL_MAP_INDEX2 & (ReadUInt32_Optional_BMI(&(info->RouteFirst)) - 1);
		SkipToNextField(); // TradSesStatus
		nmap1 |= NULL_MAP_INDEX4 & (ReadString_Optional_Fixed4(info->TradingSessionID) - 1);
		ReadString_Mandatory_PredictMax16(info->Symbol, &(info->SymbolLength));
		info->NullMap = nmap1;
		return info;
	}
	inline AstsSnapshotInfo* GetAstsSnapshotInfoTLSCURR() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		UINT64 nmap1 = 0;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		nmap1 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_BMI(&(info->LastMsgSeqNumProcessed)) - 1);
		info->RptSeq = ReadInt32_Mandatory_BMI();
		nmap1 |= NULL_MAP_INDEX1 & (ReadUInt32_Optional_BMI(&(info->LastFragment)) - 1);
		nmap1 |= NULL_MAP_INDEX2 & (ReadUInt32_Optional_BMI(&(info->RouteFirst)) - 1);
		SkipToNextField(); // TradSesStatus
		nmap1 |= NULL_MAP_INDEX4 & (ReadString_Optional_Fixed4(info->TradingSessionID) - 1);
		ReadString_Mandatory_PredictMax16(info->Symbol, &(info->SymbolLength));
		info->NullMap = nmap1;
		return info;
	}
	inline void* DecodeAsts() {
		this->DecodeAstsHeader();
		if(this->m_templateId <= 2510) {
			if(this->m_templateId <= 2106) {
				if(this->m_templateId <= 2103) {
					if(this->m_templateId <= 2102) {
						if(this->m_templateId == 2101) {
							this->m_lastDecodedInfo = this->DecodeAstsLogon();
							return this->m_lastDecodedInfo;
						}
						else { // 2102
							this->m_lastDecodedInfo = this->DecodeAstsLogout();
							return this->m_lastDecodedInfo;
						}
					}
					else {
						if(this->m_templateId == 2102) {
							this->m_lastDecodedInfo = this->DecodeAstsLogout();
							return this->m_lastDecodedInfo;
						}
						else { // 2103
							this->m_lastDecodedInfo = this->DecodeAstsGeneric();
							return this->m_lastDecodedInfo;
						}
					}
				}
				else {
					if(this->m_templateId <= 2104) {
						if(this->m_templateId == 2103) {
							this->m_lastDecodedInfo = this->DecodeAstsGeneric();
							return this->m_lastDecodedInfo;
						}
						else { // 2104
							this->m_lastDecodedInfo = this->DecodeAstsIncrementalGeneric();
							return this->m_lastDecodedInfo;
						}
					}
					else {
						if(this->m_templateId == 2104) {
							this->m_lastDecodedInfo = this->DecodeAstsIncrementalGeneric();
							return this->m_lastDecodedInfo;
						}
						else { // 2106
							this->m_lastDecodedInfo = this->DecodeAstsSecurityStatus();
							return this->m_lastDecodedInfo;
						}
					}
				}
			}
			else {
				if(this->m_templateId <= 2108) {
					if(this->m_templateId <= 2107) {
						if(this->m_templateId == 2106) {
							this->m_lastDecodedInfo = this->DecodeAstsSecurityStatus();
							return this->m_lastDecodedInfo;
						}
						else { // 2107
							this->m_lastDecodedInfo = this->DecodeAstsTradingSessionStatus();
							return this->m_lastDecodedInfo;
						}
					}
					else {
						if(this->m_templateId == 2107) {
							this->m_lastDecodedInfo = this->DecodeAstsTradingSessionStatus();
							return this->m_lastDecodedInfo;
						}
						else { // 2108
							this->m_lastDecodedInfo = this->DecodeAstsHeartbeat();
							return this->m_lastDecodedInfo;
						}
					}
				}
				else {
					if(this->m_templateId <= 2115) {
						if(this->m_templateId == 2108) {
							this->m_lastDecodedInfo = this->DecodeAstsHeartbeat();
							return this->m_lastDecodedInfo;
						}
						else { // 2115
							this->m_lastDecodedInfo = this->DecodeAstsSecurityDefinition();
							return this->m_lastDecodedInfo;
						}
					}
					else {
						if(this->m_templateId == 2115) {
							this->m_lastDecodedInfo = this->DecodeAstsSecurityDefinition();
							return this->m_lastDecodedInfo;
						}
						else { // 2510
							this->m_lastDecodedInfo = this->DecodeAstsOLSFOND();
							return this->m_lastDecodedInfo;
						}
					}
				}
			}
		}
		else {
			if(this->m_templateId <= 2523) {
				if(this->m_templateId <= 2520) {
					if(this->m_templateId <= 2511) {
						if(this->m_templateId == 2510) {
							this->m_lastDecodedInfo = this->DecodeAstsOLSFOND();
							return this->m_lastDecodedInfo;
						}
						else { // 2511
							this->m_lastDecodedInfo = this->DecodeAstsTLSFOND();
							return this->m_lastDecodedInfo;
						}
					}
					else {
						if(this->m_templateId == 2511) {
							this->m_lastDecodedInfo = this->DecodeAstsTLSFOND();
							return this->m_lastDecodedInfo;
						}
						else { // 2520
							this->m_lastDecodedInfo = this->DecodeAstsIncrementalOLRFOND();
							return this->m_lastDecodedInfo;
						}
					}
				}
				else {
					if(this->m_templateId <= 2521) {
						if(this->m_templateId == 2520) {
							this->m_lastDecodedInfo = this->DecodeAstsIncrementalOLRFOND();
							return this->m_lastDecodedInfo;
						}
						else { // 2521
							this->m_lastDecodedInfo = this->DecodeAstsIncrementalTLRFOND();
							return this->m_lastDecodedInfo;
						}
					}
					else {
						if(this->m_templateId == 2521) {
							this->m_lastDecodedInfo = this->DecodeAstsIncrementalTLRFOND();
							return this->m_lastDecodedInfo;
						}
						else { // 2523
							this->m_lastDecodedInfo = this->DecodeAstsIncrementalMSRFOND();
							return this->m_lastDecodedInfo;
						}
					}
				}
			}
			else {
				if(this->m_templateId <= 3601) {
					if(this->m_templateId <= 3600) {
						if(this->m_templateId == 2523) {
							this->m_lastDecodedInfo = this->DecodeAstsIncrementalMSRFOND();
							return this->m_lastDecodedInfo;
						}
						else { // 3600
							this->m_lastDecodedInfo = this->DecodeAstsOLSCURR();
							return this->m_lastDecodedInfo;
						}
					}
					else {
						if(this->m_templateId == 3600) {
							this->m_lastDecodedInfo = this->DecodeAstsOLSCURR();
							return this->m_lastDecodedInfo;
						}
						else { // 3601
							this->m_lastDecodedInfo = this->DecodeAstsTLSCURR();
							return this->m_lastDecodedInfo;
						}
					}
				}
				else {
					if(this->m_templateId <= 3610) {
						if(this->m_templateId == 3601) {
							this->m_lastDecodedInfo = this->DecodeAstsTLSCURR();
							return this->m_lastDecodedInfo;
						}
						else { // 3610
							this->m_lastDecodedInfo = this->DecodeAstsIncrementalOLRCURR();
							return this->m_lastDecodedInfo;
						}
					}
					else {
						if(this->m_templateId <= 3611) {
							if(this->m_templateId == 3610) {
								this->m_lastDecodedInfo = this->DecodeAstsIncrementalOLRCURR();
								return this->m_lastDecodedInfo;
							}
							else { // 3611
								this->m_lastDecodedInfo = this->DecodeAstsIncrementalTLRCURR();
								return this->m_lastDecodedInfo;
							}
						}
						else {
							if(this->m_templateId == 3611) {
								this->m_lastDecodedInfo = this->DecodeAstsIncrementalTLRCURR();
								return this->m_lastDecodedInfo;
							}
							else { // 3613
								this->m_lastDecodedInfo = this->DecodeAstsIncrementalMSRCURR();
								return this->m_lastDecodedInfo;
							}
						}
					}
				}
			}
		}
	}
	void PrintAsts() {

		switch(this->m_templateId) {
			case 2101:
				PrintAstsLogon(static_cast<AstsLogonInfo*>(this->m_lastDecodedInfo));
				break;
			case 2102:
				PrintAstsLogout(static_cast<AstsLogoutInfo*>(this->m_lastDecodedInfo));
				break;
			case 2103:
				PrintAstsGeneric(static_cast<AstsGenericInfo*>(this->m_lastDecodedInfo));
				break;
			case 2104:
				PrintAstsIncrementalGeneric(static_cast<AstsIncrementalGenericInfo*>(this->m_lastDecodedInfo));
				break;
			case 2510:
				PrintAstsOLSFOND(static_cast<AstsOLSFONDInfo*>(this->m_lastDecodedInfo));
				break;
			case 3600:
				PrintAstsOLSCURR(static_cast<AstsOLSCURRInfo*>(this->m_lastDecodedInfo));
				break;
			case 2511:
				PrintAstsTLSFOND(static_cast<AstsTLSFONDInfo*>(this->m_lastDecodedInfo));
				break;
			case 3601:
				PrintAstsTLSCURR(static_cast<AstsTLSCURRInfo*>(this->m_lastDecodedInfo));
				break;
			case 2523:
				PrintAstsIncrementalMSRFOND(static_cast<AstsIncrementalMSRFONDInfo*>(this->m_lastDecodedInfo));
				break;
			case 3613:
				PrintAstsIncrementalMSRCURR(static_cast<AstsIncrementalMSRCURRInfo*>(this->m_lastDecodedInfo));
				break;
			case 2520:
				PrintAstsIncrementalOLRFOND(static_cast<AstsIncrementalOLRFONDInfo*>(this->m_lastDecodedInfo));
				break;
			case 3610:
				PrintAstsIncrementalOLRCURR(static_cast<AstsIncrementalOLRCURRInfo*>(this->m_lastDecodedInfo));
				break;
			case 2521:
				PrintAstsIncrementalTLRFOND(static_cast<AstsIncrementalTLRFONDInfo*>(this->m_lastDecodedInfo));
				break;
			case 3611:
				PrintAstsIncrementalTLRCURR(static_cast<AstsIncrementalTLRCURRInfo*>(this->m_lastDecodedInfo));
				break;
			case 2115:
				PrintAstsSecurityDefinition(static_cast<AstsSecurityDefinitionInfo*>(this->m_lastDecodedInfo));
				break;
			case 2106:
				PrintAstsSecurityStatus(static_cast<AstsSecurityStatusInfo*>(this->m_lastDecodedInfo));
				break;
			case 2107:
				PrintAstsTradingSessionStatus(static_cast<AstsTradingSessionStatusInfo*>(this->m_lastDecodedInfo));
				break;
			case 2108:
				PrintAstsHeartbeat(static_cast<AstsHeartbeatInfo*>(this->m_lastDecodedInfo));
				break;
		}
	}
	void PrintXmlAsts() {

		switch(this->m_templateId) {
			case 2101:
				PrintXmlAstsLogon(static_cast<AstsLogonInfo*>(this->m_lastDecodedInfo));
				break;
			case 2102:
				PrintXmlAstsLogout(static_cast<AstsLogoutInfo*>(this->m_lastDecodedInfo));
				break;
			case 2103:
				PrintXmlAstsGeneric(static_cast<AstsGenericInfo*>(this->m_lastDecodedInfo));
				break;
			case 2104:
				PrintXmlAstsIncrementalGeneric(static_cast<AstsIncrementalGenericInfo*>(this->m_lastDecodedInfo));
				break;
			case 2510:
				PrintXmlAstsOLSFOND(static_cast<AstsOLSFONDInfo*>(this->m_lastDecodedInfo));
				break;
			case 3600:
				PrintXmlAstsOLSCURR(static_cast<AstsOLSCURRInfo*>(this->m_lastDecodedInfo));
				break;
			case 2511:
				PrintXmlAstsTLSFOND(static_cast<AstsTLSFONDInfo*>(this->m_lastDecodedInfo));
				break;
			case 3601:
				PrintXmlAstsTLSCURR(static_cast<AstsTLSCURRInfo*>(this->m_lastDecodedInfo));
				break;
			case 2523:
				PrintXmlAstsIncrementalMSRFOND(static_cast<AstsIncrementalMSRFONDInfo*>(this->m_lastDecodedInfo));
				break;
			case 3613:
				PrintXmlAstsIncrementalMSRCURR(static_cast<AstsIncrementalMSRCURRInfo*>(this->m_lastDecodedInfo));
				break;
			case 2520:
				PrintXmlAstsIncrementalOLRFOND(static_cast<AstsIncrementalOLRFONDInfo*>(this->m_lastDecodedInfo));
				break;
			case 3610:
				PrintXmlAstsIncrementalOLRCURR(static_cast<AstsIncrementalOLRCURRInfo*>(this->m_lastDecodedInfo));
				break;
			case 2521:
				PrintXmlAstsIncrementalTLRFOND(static_cast<AstsIncrementalTLRFONDInfo*>(this->m_lastDecodedInfo));
				break;
			case 3611:
				PrintXmlAstsIncrementalTLRCURR(static_cast<AstsIncrementalTLRCURRInfo*>(this->m_lastDecodedInfo));
				break;
			case 2115:
				PrintXmlAstsSecurityDefinition(static_cast<AstsSecurityDefinitionInfo*>(this->m_lastDecodedInfo));
				break;
			case 2106:
				PrintXmlAstsSecurityStatus(static_cast<AstsSecurityStatusInfo*>(this->m_lastDecodedInfo));
				break;
			case 2107:
				PrintXmlAstsTradingSessionStatus(static_cast<AstsTradingSessionStatusInfo*>(this->m_lastDecodedInfo));
				break;
			case 2108:
				PrintXmlAstsHeartbeat(static_cast<AstsHeartbeatInfo*>(this->m_lastDecodedInfo));
				break;
		}
	}
	inline AstsSnapshotInfo* GetAstsSnapshotInfo() {
		this->DecodeAstsHeader();
		if(this->m_templateId <= 2511) {
			if(this->m_templateId <= 2510) {
				if(this->m_templateId == 2103) {
					return this->GetAstsSnapshotInfoGeneric();
				}
				else { // 2510
					return this->GetAstsSnapshotInfoOLSFOND();
				}
			}
			else {
				if(this->m_templateId == 2510) {
					return this->GetAstsSnapshotInfoOLSFOND();
				}
				else { // 2511
					return this->GetAstsSnapshotInfoTLSFOND();
				}
			}
		}
		else {
			if(this->m_templateId <= 3600) {
				if(this->m_templateId == 2511) {
					return this->GetAstsSnapshotInfoTLSFOND();
				}
				else { // 3600
					return this->GetAstsSnapshotInfoOLSCURR();
				}
			}
			else {
				if(this->m_templateId == 3600) {
					return this->GetAstsSnapshotInfoOLSCURR();
				}
				else { // 3601
					return this->GetAstsSnapshotInfoTLSCURR();
				}
			}
		}
		return this->GetAstsSnapshotInfoUnsupported();
	}
#pragma endregion

#pragma region Forts_Decode_Methods_Definition_GeneratedCode
	inline void DecodeFortsHeader() {

		this->m_presenceMap = this->ParsePresenceMap();
		this->m_templateId = ReadUInt32_Mandatory_BMI();
	}

	int GetFortsTotalNumReports() {
		// ReadMsgNumber and DecodeHeader should be called first
		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		return ReadInt32_Mandatory_BMI();
	}
	inline void* DecodeFortsUnsupportedMessage() { return 0; }
	inline FortsSnapshotInfo* GetFortsSnapshotInfoUnsupported() { return 0; }
	inline FortsDefaultIncrementalRefreshMessageInfo* DecodeFortsDefaultIncrementalRefreshMessage() {
		FortsDefaultIncrementalRefreshMessageInfo* info = GetFreeFortsDefaultIncrementalRefreshMessageInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		nmap1 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_BMI(&(info->LastFragment)) - 1);

		info->MDEntriesCount = ReadUInt32_Mandatory_Predict12_BMI();
		FortsDefaultSnapshotMessageMDEntriesItemInfo* mdeItemInfo = NULL;

		for(int mdeItemInfoIndex = 0; mdeItemInfoIndex < info->MDEntriesCount; mdeItemInfoIndex++) {
			mdeItemInfo = GetFreeFortsDefaultSnapshotMessageMDEntriesItemInfo();
			for(int i = 0; i < sizeof(FortsDefaultSnapshotMessageMDEntriesItemInfo); i += 64)
				__builtin_prefetch(((char*)mdeItemInfo) + i, 0, _MM_HINT_T0);
			info->MDEntries[mdeItemInfoIndex] = mdeItemInfo;
		}
		for(int mdeItemInfoIndex = 0; mdeItemInfoIndex < info->MDEntriesCount; mdeItemInfoIndex++) {
			mdeItemInfo = info->MDEntries[mdeItemInfoIndex];
			UINT64 nmap2 = 0;

			mdeItemInfo->MDUpdateAction = ReadUInt32_Mandatory_BMI();
			ReadString_Mandatory(mdeItemInfo->MDEntryType, &(mdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullUInt64())
				nmap2 |= NULL_MAP_INDEX0;
			else
				mdeItemInfo->SecurityID = ReadUInt64_Optional_BMI();
			nmap2 |= NULL_MAP_INDEX1 & (ReadString_Optional(mdeItemInfo->Symbol, &(mdeItemInfo->SymbolLength)) - 1);
			nmap2 |= NULL_MAP_INDEX2 & (ReadString_Optional(mdeItemInfo->SecurityGroup, &(mdeItemInfo->SecurityGroupLength)) - 1);
			nmap2 |= NULL_MAP_INDEX3 & (ReadUInt32_Optional_BMI(&(mdeItemInfo->ExchangeTradingSessionID)) - 1);
			mdeItemInfo->RptSeq = ReadUInt32_Mandatory_BMI();
			nmap2 |= NULL_MAP_INDEX4 & (ReadUInt32_Optional_BMI(&(mdeItemInfo->MarketDepth)) - 1);
			nmap2 |= NULL_MAP_INDEX5 & (ReadUInt32_Optional_BMI(&(mdeItemInfo->MDPriceLevel)) - 1);
			if(CheckProcessNullInt64())
				nmap2 |= NULL_MAP_INDEX6;
			else
				mdeItemInfo->MDEntryID = ReadInt64_Optional_BMI();
			nmap2 |= NULL_MAP_INDEX7 & (ReadDecimal_Optional_BMI(&(mdeItemInfo->MDEntryPx)) - 1);
			if(CheckProcessNullInt64())
				nmap2 |= NULL_MAP_INDEX8;
			else
				mdeItemInfo->MDEntrySize = ReadInt64_Optional_BMI();
			nmap2 |= NULL_MAP_INDEX9 & (ReadUInt32_Optional_BMI(&(mdeItemInfo->MDEntryDate)) - 1);
			mdeItemInfo->MDEntryTime = ReadUInt64_Mandatory_BMI();
			nmap2 |= NULL_MAP_INDEX10 & (ReadInt32_Optional_BMI(&(mdeItemInfo->NumberOfOrders)) - 1);
			nmap2 |= NULL_MAP_INDEX11 & (ReadString_Optional(mdeItemInfo->MDEntryTradeType, &(mdeItemInfo->MDEntryTradeTypeLength)) - 1);
			nmap2 |= NULL_MAP_INDEX12 & (ReadInt32_Optional_BMI(&(mdeItemInfo->TrdType)) - 1);
			nmap2 |= NULL_MAP_INDEX13 & (ReadDecimal_Optional_BMI(&(mdeItemInfo->LastPx)) - 1);
			nmap2 |= NULL_MAP_INDEX14 & (ReadInt32_Optional_BMI(&(mdeItemInfo->MDFlags)) - 1);
			nmap2 |= NULL_MAP_INDEX15 & (ReadString_Optional(mdeItemInfo->Currency, &(mdeItemInfo->CurrencyLength)) - 1);
			if(CheckProcessNullUInt64())
				nmap2 |= NULL_MAP_INDEX16;
			else
				mdeItemInfo->Revision = ReadUInt64_Optional_BMI();
			nmap2 |= NULL_MAP_INDEX17 & (ReadString_Optional(mdeItemInfo->OrderSide, &(mdeItemInfo->OrderSideLength)) - 1);
			mdeItemInfo->NullMap = nmap2;
			this->m_prevfortsDefaultSnapshotMessageMDEntriesItemInfo = mdeItemInfo;
		}

		info->NullMap = nmap1;
		this->m_prevfortsDefaultIncrementalRefreshMessageInfo = info;
		return info;
	}
	inline FortsDefaultSnapshotMessageInfo* DecodeFortsDefaultSnapshotMessage() {
		FortsDefaultSnapshotMessageInfo* info = GetFreeFortsDefaultSnapshotMessageInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		nmap1 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_BMI(&(info->LastFragment)) - 1);
		info->RptSeq = ReadUInt32_Mandatory_BMI();
		info->TotNumReports = ReadUInt32_Mandatory_BMI();
		info->LastMsgSeqNumProcessed = ReadUInt32_Mandatory_BMI();
		if(CheckProcessNullUInt64())
			nmap1 |= NULL_MAP_INDEX1;
		else
			info->SecurityID = ReadUInt64_Optional_BMI();
		nmap1 |= NULL_MAP_INDEX2 & (ReadString_Optional(info->Symbol, &(info->SymbolLength)) - 1);
		nmap1 |= NULL_MAP_INDEX3 & (ReadString_Optional(info->SecurityGroup, &(info->SecurityGroupLength)) - 1);

		info->MDEntriesCount = ReadUInt32_Mandatory_Predict12_BMI();
		FortsDefaultSnapshotMessageMDEntriesItemInfo* mdeItemInfo = NULL;

		for(int mdeItemInfoIndex = 0; mdeItemInfoIndex < info->MDEntriesCount; mdeItemInfoIndex++) {
			mdeItemInfo = GetFreeFortsDefaultSnapshotMessageMDEntriesItemInfo();
			for(int i = 0; i < sizeof(FortsDefaultSnapshotMessageMDEntriesItemInfo); i += 64)
				__builtin_prefetch(((char*)mdeItemInfo) + i, 0, _MM_HINT_T0);
			info->MDEntries[mdeItemInfoIndex] = mdeItemInfo;
		}
		for(int mdeItemInfoIndex = 0; mdeItemInfoIndex < info->MDEntriesCount; mdeItemInfoIndex++) {
			mdeItemInfo = info->MDEntries[mdeItemInfoIndex];
			UINT64 nmap2 = 0;

			ReadString_Mandatory(mdeItemInfo->MDEntryType, &(mdeItemInfo->MDEntryTypeLength));
			nmap2 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_BMI(&(mdeItemInfo->ExchangeTradingSessionID)) - 1);
			if(CheckProcessNullInt64())
				nmap2 |= NULL_MAP_INDEX1;
			else
				mdeItemInfo->MDEntryID = ReadInt64_Optional_BMI();
			nmap2 |= NULL_MAP_INDEX2 & (ReadUInt32_Optional_BMI(&(mdeItemInfo->MarketDepth)) - 1);
			nmap2 |= NULL_MAP_INDEX3 & (ReadDecimal_Optional_BMI(&(mdeItemInfo->MDEntryPx)) - 1);
			nmap2 |= NULL_MAP_INDEX4 & (ReadUInt32_Optional_BMI(&(mdeItemInfo->MDEntryDate)) - 1);
			mdeItemInfo->MDEntryTime = ReadUInt64_Mandatory_BMI();
			if(CheckProcessNullInt64())
				nmap2 |= NULL_MAP_INDEX5;
			else
				mdeItemInfo->MDEntrySize = ReadInt64_Optional_BMI();
			nmap2 |= NULL_MAP_INDEX6 & (ReadUInt32_Optional_BMI(&(mdeItemInfo->MDPriceLevel)) - 1);
			nmap2 |= NULL_MAP_INDEX7 & (ReadInt32_Optional_BMI(&(mdeItemInfo->NumberOfOrders)) - 1);
			nmap2 |= NULL_MAP_INDEX8 & (ReadString_Optional(mdeItemInfo->MDEntryTradeType, &(mdeItemInfo->MDEntryTradeTypeLength)) - 1);
			nmap2 |= NULL_MAP_INDEX9 & (ReadInt32_Optional_BMI(&(mdeItemInfo->TrdType)) - 1);
			nmap2 |= NULL_MAP_INDEX10 & (ReadInt32_Optional_BMI(&(mdeItemInfo->MDFlags)) - 1);
			nmap2 |= NULL_MAP_INDEX11 & (ReadString_Optional(mdeItemInfo->Currency, &(mdeItemInfo->CurrencyLength)) - 1);
			nmap2 |= NULL_MAP_INDEX12 & (ReadString_Optional(mdeItemInfo->OrderSide, &(mdeItemInfo->OrderSideLength)) - 1);
			mdeItemInfo->NullMap = nmap2;
			this->m_prevfortsDefaultSnapshotMessageMDEntriesItemInfo = mdeItemInfo;
		}

		info->NullMap = nmap1;
		this->m_prevfortsDefaultSnapshotMessageInfo = info;
		return info;
	}
	inline FortsSecurityDefinitionInfo* DecodeFortsSecurityDefinition() {
		FortsSecurityDefinitionInfo* info = GetFreeFortsSecurityDefinitionInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		info->TotNumReports = ReadUInt32_Mandatory_BMI();
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		if(CheckProcessNullByteVector())
			nmap1 |= NULL_MAP_INDEX0;
		else
			ReadByteVector_Optional(info->SecurityDesc, &(info->SecurityDescLength), 128);
		info->SecurityID = ReadUInt64_Mandatory_BMI();
		nmap1 |= NULL_MAP_INDEX1 & (ReadString_Optional(info->SecurityAltID, &(info->SecurityAltIDLength)) - 1);
		nmap1 |= NULL_MAP_INDEX2 & (ReadString_Optional(info->SecurityAltIDSource, &(info->SecurityAltIDSourceLength)) - 1);
		nmap1 |= NULL_MAP_INDEX3 & (ReadString_Optional(info->SecurityType, &(info->SecurityTypeLength)) - 1);
		nmap1 |= NULL_MAP_INDEX4 & (ReadString_Optional(info->CFICode, &(info->CFICodeLength)) - 1);
		nmap1 |= NULL_MAP_INDEX5 & (ReadDecimal_Optional_BMI(&(info->StrikePrice)) - 1);
		nmap1 |= NULL_MAP_INDEX6 & (ReadDecimal_Optional_BMI(&(info->ContractMultiplier)) - 1);
		nmap1 |= NULL_MAP_INDEX7 & (ReadUInt32_Optional_BMI(&(info->SecurityTradingStatus)) - 1);
		nmap1 |= NULL_MAP_INDEX8 & (ReadString_Optional(info->Currency, &(info->CurrencyLength)) - 1);
		ReadString_Mandatory(info->MarketSegmentID, &(info->MarketSegmentIDLength));
		nmap1 |= NULL_MAP_INDEX9 & (ReadUInt32_Optional_BMI(&(info->TradingSessionID)) - 1);
		nmap1 |= NULL_MAP_INDEX10 & (ReadUInt32_Optional_BMI(&(info->ExchangeTradingSessionID)) - 1);
		nmap1 |= NULL_MAP_INDEX11 & (ReadDecimal_Optional_BMI(&(info->Volatility)) - 1);

		info->MDFeedTypesCount = ReadUInt32_Mandatory_Predict12_BMI();
		FortsSecurityDefinitionMDFeedTypesItemInfo* mdftItemInfo = NULL;

		for(int mdftItemInfoIndex = 0; mdftItemInfoIndex < info->MDFeedTypesCount; mdftItemInfoIndex++) {
			mdftItemInfo = GetFreeFortsSecurityDefinitionMDFeedTypesItemInfo();
			for(int i = 0; i < sizeof(FortsSecurityDefinitionMDFeedTypesItemInfo); i += 64)
				__builtin_prefetch(((char*)mdftItemInfo) + i, 0, _MM_HINT_T0);
			info->MDFeedTypes[mdftItemInfoIndex] = mdftItemInfo;
		}
		for(int mdftItemInfoIndex = 0; mdftItemInfoIndex < info->MDFeedTypesCount; mdftItemInfoIndex++) {
			mdftItemInfo = info->MDFeedTypes[mdftItemInfoIndex];
			UINT64 nmap2 = 0;

			ReadString_Mandatory(mdftItemInfo->MDFeedType, &(mdftItemInfo->MDFeedTypeLength));
			nmap2 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_BMI(&(mdftItemInfo->MarketDepth)) - 1);
			nmap2 |= NULL_MAP_INDEX1 & (ReadUInt32_Optional_BMI(&(mdftItemInfo->MDBookType)) - 1);
			mdftItemInfo->NullMap = nmap2;
			this->m_prevfortsSecurityDefinitionMDFeedTypesItemInfo = mdftItemInfo;
		}


		if(!ReadUInt32_Optional_Predict12_BMI((UINT32*)&(info->UnderlyingsCount))) {
			info->UnderlyingsCount = 0;
			nmap1 |= NULL_MAP_INDEX12;
		}
		FortsSecurityDefinitionUnderlyingsItemInfo* uItemInfo = NULL;

		for(int uItemInfoIndex = 0; uItemInfoIndex < info->UnderlyingsCount; uItemInfoIndex++) {
			uItemInfo = GetFreeFortsSecurityDefinitionUnderlyingsItemInfo();
			for(int i = 0; i < sizeof(FortsSecurityDefinitionUnderlyingsItemInfo); i += 64)
				__builtin_prefetch(((char*)uItemInfo) + i, 0, _MM_HINT_T0);
			info->Underlyings[uItemInfoIndex] = uItemInfo;
		}
		for(int uItemInfoIndex = 0; uItemInfoIndex < info->UnderlyingsCount; uItemInfoIndex++) {
			uItemInfo = info->Underlyings[uItemInfoIndex];
			UINT64 nmap2 = 0;

			ReadString_Mandatory(uItemInfo->UnderlyingSymbol, &(uItemInfo->UnderlyingSymbolLength));
			if(CheckProcessNullUInt64())
				nmap2 |= NULL_MAP_INDEX0;
			else
				uItemInfo->UnderlyingSecurityID = ReadUInt64_Optional_BMI();
			uItemInfo->NullMap = nmap2;
			this->m_prevfortsSecurityDefinitionUnderlyingsItemInfo = uItemInfo;
		}

		nmap1 |= NULL_MAP_INDEX13 & (ReadDecimal_Optional_BMI(&(info->HighLimitPx)) - 1);
		nmap1 |= NULL_MAP_INDEX14 & (ReadDecimal_Optional_BMI(&(info->LowLimitPx)) - 1);
		nmap1 |= NULL_MAP_INDEX15 & (ReadDecimal_Optional_BMI(&(info->MinPriceIncrement)) - 1);
		nmap1 |= NULL_MAP_INDEX16 & (ReadDecimal_Optional_BMI(&(info->MinPriceIncrementAmount)) - 1);
		nmap1 |= NULL_MAP_INDEX17 & (ReadDecimal_Optional_BMI(&(info->InitialMarginOnBuy)) - 1);
		nmap1 |= NULL_MAP_INDEX18 & (ReadDecimal_Optional_BMI(&(info->InitialMarginOnSell)) - 1);
		nmap1 |= NULL_MAP_INDEX19 & (ReadDecimal_Optional_BMI(&(info->InitialMarginSyntetic)) - 1);
		nmap1 |= NULL_MAP_INDEX20 & (ReadString_Optional(info->QuotationList, &(info->QuotationListLength)) - 1);
		nmap1 |= NULL_MAP_INDEX21 & (ReadDecimal_Optional_BMI(&(info->TheorPrice)) - 1);
		nmap1 |= NULL_MAP_INDEX22 & (ReadDecimal_Optional_BMI(&(info->TheorPriceLimit)) - 1);

		if(!ReadUInt32_Optional_Predict12_BMI((UINT32*)&(info->InstrumentLegsCount))) {
			info->InstrumentLegsCount = 0;
			nmap1 |= NULL_MAP_INDEX23;
		}
		FortsSecurityDefinitionInstrumentLegsItemInfo* ilItemInfo = NULL;

		for(int ilItemInfoIndex = 0; ilItemInfoIndex < info->InstrumentLegsCount; ilItemInfoIndex++) {
			ilItemInfo = GetFreeFortsSecurityDefinitionInstrumentLegsItemInfo();
			for(int i = 0; i < sizeof(FortsSecurityDefinitionInstrumentLegsItemInfo); i += 64)
				__builtin_prefetch(((char*)ilItemInfo) + i, 0, _MM_HINT_T0);
			info->InstrumentLegs[ilItemInfoIndex] = ilItemInfo;
		}
		for(int ilItemInfoIndex = 0; ilItemInfoIndex < info->InstrumentLegsCount; ilItemInfoIndex++) {
			ilItemInfo = info->InstrumentLegs[ilItemInfoIndex];
			UINT64 nmap2 = 0;

			ReadString_Mandatory(ilItemInfo->LegSymbol, &(ilItemInfo->LegSymbolLength));
			ilItemInfo->LegSecurityID = ReadUInt64_Mandatory_BMI();
			ReadDecimal_Mandatory_BMI(&(ilItemInfo->LegRatioQty));
			ilItemInfo->NullMap = nmap2;
			this->m_prevfortsSecurityDefinitionInstrumentLegsItemInfo = ilItemInfo;
		}


		if(!ReadUInt32_Optional_Predict12_BMI((UINT32*)&(info->InstrumentAttributesCount))) {
			info->InstrumentAttributesCount = 0;
			nmap1 |= NULL_MAP_INDEX24;
		}
		FortsSecurityDefinitionInstrumentAttributesItemInfo* iaItemInfo = NULL;

		for(int iaItemInfoIndex = 0; iaItemInfoIndex < info->InstrumentAttributesCount; iaItemInfoIndex++) {
			iaItemInfo = GetFreeFortsSecurityDefinitionInstrumentAttributesItemInfo();
			for(int i = 0; i < sizeof(FortsSecurityDefinitionInstrumentAttributesItemInfo); i += 64)
				__builtin_prefetch(((char*)iaItemInfo) + i, 0, _MM_HINT_T0);
			info->InstrumentAttributes[iaItemInfoIndex] = iaItemInfo;
		}
		for(int iaItemInfoIndex = 0; iaItemInfoIndex < info->InstrumentAttributesCount; iaItemInfoIndex++) {
			iaItemInfo = info->InstrumentAttributes[iaItemInfoIndex];
			UINT64 nmap2 = 0;

			iaItemInfo->InstrAttribType = ReadInt32_Mandatory_BMI();
			ReadString_Mandatory(iaItemInfo->InstrAttribValue, &(iaItemInfo->InstrAttribValueLength));
			iaItemInfo->NullMap = nmap2;
			this->m_prevfortsSecurityDefinitionInstrumentAttributesItemInfo = iaItemInfo;
		}

		nmap1 |= NULL_MAP_INDEX25 & (ReadDecimal_Optional_BMI(&(info->UnderlyingQty)) - 1);
		nmap1 |= NULL_MAP_INDEX26 & (ReadString_Optional(info->UnderlyingCurrency, &(info->UnderlyingCurrencyLength)) - 1);

		if(!ReadUInt32_Optional_Predict12_BMI((UINT32*)&(info->EvntGrpCount))) {
			info->EvntGrpCount = 0;
			nmap1 |= NULL_MAP_INDEX27;
		}
		FortsSecurityDefinitionEvntGrpItemInfo* egItemInfo = NULL;

		for(int egItemInfoIndex = 0; egItemInfoIndex < info->EvntGrpCount; egItemInfoIndex++) {
			egItemInfo = GetFreeFortsSecurityDefinitionEvntGrpItemInfo();
			for(int i = 0; i < sizeof(FortsSecurityDefinitionEvntGrpItemInfo); i += 64)
				__builtin_prefetch(((char*)egItemInfo) + i, 0, _MM_HINT_T0);
			info->EvntGrp[egItemInfoIndex] = egItemInfo;
		}
		for(int egItemInfoIndex = 0; egItemInfoIndex < info->EvntGrpCount; egItemInfoIndex++) {
			egItemInfo = info->EvntGrp[egItemInfoIndex];
			UINT64 nmap2 = 0;

			egItemInfo->EventType = ReadInt32_Mandatory_BMI();
			egItemInfo->EventDate = ReadUInt32_Mandatory_BMI();
			egItemInfo->EventTime = ReadUInt64_Mandatory_BMI();
			egItemInfo->NullMap = nmap2;
			this->m_prevfortsSecurityDefinitionEvntGrpItemInfo = egItemInfo;
		}

		nmap1 |= NULL_MAP_INDEX28 & (ReadUInt32_Optional_BMI(&(info->MaturityDate)) - 1);
		nmap1 |= NULL_MAP_INDEX29 & (ReadUInt32_Optional_BMI(&(info->MaturityTime)) - 1);
		info->NullMap = nmap1;
		this->m_prevfortsSecurityDefinitionInfo = info;
		return info;
	}
	inline FortsSecurityDefinitionUpdateReportInfo* DecodeFortsSecurityDefinitionUpdateReport() {
		FortsSecurityDefinitionUpdateReportInfo* info = GetFreeFortsSecurityDefinitionUpdateReportInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		info->SecurityID = ReadUInt64_Mandatory_BMI();
		nmap1 |= NULL_MAP_INDEX0 & (ReadDecimal_Optional_BMI(&(info->Volatility)) - 1);
		nmap1 |= NULL_MAP_INDEX1 & (ReadDecimal_Optional_BMI(&(info->TheorPrice)) - 1);
		nmap1 |= NULL_MAP_INDEX2 & (ReadDecimal_Optional_BMI(&(info->TheorPriceLimit)) - 1);
		info->NullMap = nmap1;
		this->m_prevfortsSecurityDefinitionUpdateReportInfo = info;
		return info;
	}
	inline FortsSecurityStatusInfo* DecodeFortsSecurityStatus() {
		FortsSecurityStatusInfo* info = GetFreeFortsSecurityStatusInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		info->SecurityID = ReadUInt64_Mandatory_BMI();
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		nmap1 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_BMI(&(info->SecurityTradingStatus)) - 1);
		nmap1 |= NULL_MAP_INDEX1 & (ReadDecimal_Optional_BMI(&(info->HighLimitPx)) - 1);
		nmap1 |= NULL_MAP_INDEX2 & (ReadDecimal_Optional_BMI(&(info->LowLimitPx)) - 1);
		nmap1 |= NULL_MAP_INDEX3 & (ReadDecimal_Optional_BMI(&(info->InitialMarginOnBuy)) - 1);
		nmap1 |= NULL_MAP_INDEX4 & (ReadDecimal_Optional_BMI(&(info->InitialMarginOnSell)) - 1);
		nmap1 |= NULL_MAP_INDEX5 & (ReadDecimal_Optional_BMI(&(info->InitialMarginSyntetic)) - 1);
		info->NullMap = nmap1;
		this->m_prevfortsSecurityStatusInfo = info;
		return info;
	}
	inline FortsHeartbeatInfo* DecodeFortsHeartbeat() {
		FortsHeartbeatInfo* info = GetFreeFortsHeartbeatInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		info->NullMap = nmap1;
		this->m_prevfortsHeartbeatInfo = info;
		return info;
	}
	inline FortsSequenceResetInfo* DecodeFortsSequenceReset() {
		FortsSequenceResetInfo* info = GetFreeFortsSequenceResetInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		info->NewSeqNo = ReadUInt32_Mandatory_BMI();
		info->NullMap = nmap1;
		this->m_prevfortsSequenceResetInfo = info;
		return info;
	}
	inline FortsTradingSessionStatusInfo* DecodeFortsTradingSessionStatus() {
		FortsTradingSessionStatusInfo* info = GetFreeFortsTradingSessionStatusInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		info->TradSesOpenTime = ReadUInt64_Mandatory_BMI();
		info->TradSesCloseTime = ReadUInt64_Mandatory_BMI();
		if(CheckProcessNullUInt64())
			nmap1 |= NULL_MAP_INDEX0;
		else
			info->TradSesIntermClearingStartTime = ReadUInt64_Optional_BMI();
		if(CheckProcessNullUInt64())
			nmap1 |= NULL_MAP_INDEX1;
		else
			info->TradSesIntermClearingEndTime = ReadUInt64_Optional_BMI();
		info->TradingSessionID = ReadUInt32_Mandatory_BMI();
		nmap1 |= NULL_MAP_INDEX2 & (ReadUInt32_Optional_BMI(&(info->ExchangeTradingSessionID)) - 1);
		info->TradSesStatus = ReadUInt32_Mandatory_BMI();
		ReadString_Mandatory(info->MarketSegmentID, &(info->MarketSegmentIDLength));
		nmap1 |= NULL_MAP_INDEX3 & (ReadInt32_Optional_BMI(&(info->TradSesEvent)) - 1);
		info->NullMap = nmap1;
		this->m_prevfortsTradingSessionStatusInfo = info;
		return info;
	}
	inline FortsNewsInfo* DecodeFortsNews() {
		FortsNewsInfo* info = GetFreeFortsNewsInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		nmap1 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_BMI(&(info->LastFragment)) - 1);
		nmap1 |= NULL_MAP_INDEX1 & (ReadString_Optional(info->NewsId, &(info->NewsIdLength)) - 1);
		if(CheckProcessNullUInt64())
			nmap1 |= NULL_MAP_INDEX2;
		else
			info->OrigTime = ReadUInt64_Optional_BMI();
		nmap1 |= NULL_MAP_INDEX3 & (ReadString_Optional(info->LanguageCode, &(info->LanguageCodeLength)) - 1);
		nmap1 |= NULL_MAP_INDEX4 & (ReadUInt32_Optional_BMI(&(info->Urgency)) - 1);
		ReadByteVector_Mandatory(info->Headline, &(info->HeadlineLength), 128);
		nmap1 |= NULL_MAP_INDEX5 & (ReadString_Optional(info->MarketSegmentID, &(info->MarketSegmentIDLength)) - 1);

		info->NewsTextCount = ReadUInt32_Mandatory_Predict12_BMI();
		FortsNewsNewsTextItemInfo* ntItemInfo = NULL;

		for(int ntItemInfoIndex = 0; ntItemInfoIndex < info->NewsTextCount; ntItemInfoIndex++) {
			ntItemInfo = GetFreeFortsNewsNewsTextItemInfo();
			for(int i = 0; i < sizeof(FortsNewsNewsTextItemInfo); i += 64)
				__builtin_prefetch(((char*)ntItemInfo) + i, 0, _MM_HINT_T0);
			info->NewsText[ntItemInfoIndex] = ntItemInfo;
		}
		for(int ntItemInfoIndex = 0; ntItemInfoIndex < info->NewsTextCount; ntItemInfoIndex++) {
			ntItemInfo = info->NewsText[ntItemInfoIndex];
			UINT64 nmap2 = 0;

			ReadByteVector_Mandatory(ntItemInfo->Text, &(ntItemInfo->TextLength), 128);
			ntItemInfo->NullMap = nmap2;
			this->m_prevfortsNewsNewsTextItemInfo = ntItemInfo;
		}

		info->NullMap = nmap1;
		this->m_prevfortsNewsInfo = info;
		return info;
	}
	inline FortsOrdersLogInfo* DecodeFortsOrdersLog() {
		FortsOrdersLogInfo* info = GetFreeFortsOrdersLogInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		info->LastFragment = ReadUInt32_Mandatory_BMI();

		info->MDEntriesCount = ReadUInt32_Mandatory_Predict12_BMI();
		FortsOrdersLogMDEntriesItemInfo* mdeItemInfo = NULL;

		for(int mdeItemInfoIndex = 0; mdeItemInfoIndex < info->MDEntriesCount; mdeItemInfoIndex++) {
			mdeItemInfo = GetFreeFortsOrdersLogMDEntriesItemInfo();
			for(int i = 0; i < sizeof(FortsOrdersLogMDEntriesItemInfo); i += 64)
				__builtin_prefetch(((char*)mdeItemInfo) + i, 0, _MM_HINT_T0);
			info->MDEntries[mdeItemInfoIndex] = mdeItemInfo;
		}
		for(int mdeItemInfoIndex = 0; mdeItemInfoIndex < info->MDEntriesCount; mdeItemInfoIndex++) {
			mdeItemInfo = info->MDEntries[mdeItemInfoIndex];
			UINT64 nmap2 = 0;

			mdeItemInfo->MDUpdateAction = ReadUInt32_Mandatory_BMI();
			ReadString_Mandatory(mdeItemInfo->MDEntryType, &(mdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullInt64())
				nmap2 |= NULL_MAP_INDEX0;
			else
				mdeItemInfo->MDEntryID = ReadInt64_Optional_BMI();
			if(CheckProcessNullUInt64())
				nmap2 |= NULL_MAP_INDEX1;
			else
				mdeItemInfo->SecurityID = ReadUInt64_Optional_BMI();
			nmap2 |= NULL_MAP_INDEX2 & (ReadUInt32_Optional_BMI(&(mdeItemInfo->RptSeq)) - 1);
			nmap2 |= NULL_MAP_INDEX3 & (ReadUInt32_Optional_BMI(&(mdeItemInfo->MDEntryDate)) - 1);
			mdeItemInfo->MDEntryTime = ReadUInt64_Mandatory_BMI();
			nmap2 |= NULL_MAP_INDEX4 & (ReadDecimal_Optional_BMI(&(mdeItemInfo->MDEntryPx)) - 1);
			if(CheckProcessNullInt64())
				nmap2 |= NULL_MAP_INDEX5;
			else
				mdeItemInfo->MDEntrySize = ReadInt64_Optional_BMI();
			nmap2 |= NULL_MAP_INDEX6 & (ReadDecimal_Optional_BMI(&(mdeItemInfo->LastPx)) - 1);
			if(CheckProcessNullInt64())
				nmap2 |= NULL_MAP_INDEX7;
			else
				mdeItemInfo->LastQty = ReadInt64_Optional_BMI();
			if(CheckProcessNullInt64())
				nmap2 |= NULL_MAP_INDEX8;
			else
				mdeItemInfo->TradeID = ReadInt64_Optional_BMI();
			nmap2 |= NULL_MAP_INDEX9 & (ReadUInt32_Optional_BMI(&(mdeItemInfo->ExchangeTradingSessionID)) - 1);
			if(CheckProcessNullInt64())
				nmap2 |= NULL_MAP_INDEX10;
			else
				mdeItemInfo->MDFlags = ReadInt64_Optional_BMI();
			if(CheckProcessNullUInt64())
				nmap2 |= NULL_MAP_INDEX11;
			else
				mdeItemInfo->Revision = ReadUInt64_Optional_BMI();
			mdeItemInfo->NullMap = nmap2;
			this->m_prevfortsOrdersLogMDEntriesItemInfo = mdeItemInfo;
		}

		info->NullMap = nmap1;
		this->m_prevfortsOrdersLogInfo = info;
		return info;
	}
	inline FortsOrdersBookInfo* DecodeFortsOrdersBook() {
		FortsOrdersBookInfo* info = GetFreeFortsOrdersBookInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		info->LastMsgSeqNumProcessed = ReadUInt32_Mandatory_BMI();
		nmap1 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_BMI(&(info->RptSeq)) - 1);
		info->LastFragment = ReadUInt32_Mandatory_BMI();
		info->RouteFirst = ReadUInt32_Mandatory_BMI();
		info->ExchangeTradingSessionID = ReadUInt32_Mandatory_BMI();
		if(CheckProcessNullUInt64())
			nmap1 |= NULL_MAP_INDEX1;
		else
			info->SecurityID = ReadUInt64_Optional_BMI();

		info->MDEntriesCount = ReadUInt32_Mandatory_Predict12_BMI();
		FortsOrdersBookMDEntriesItemInfo* mdeItemInfo = NULL;

		for(int mdeItemInfoIndex = 0; mdeItemInfoIndex < info->MDEntriesCount; mdeItemInfoIndex++) {
			mdeItemInfo = GetFreeFortsOrdersBookMDEntriesItemInfo();
			for(int i = 0; i < sizeof(FortsOrdersBookMDEntriesItemInfo); i += 64)
				__builtin_prefetch(((char*)mdeItemInfo) + i, 0, _MM_HINT_T0);
			info->MDEntries[mdeItemInfoIndex] = mdeItemInfo;
		}
		for(int mdeItemInfoIndex = 0; mdeItemInfoIndex < info->MDEntriesCount; mdeItemInfoIndex++) {
			mdeItemInfo = info->MDEntries[mdeItemInfoIndex];
			UINT64 nmap2 = 0;

			ReadString_Mandatory(mdeItemInfo->MDEntryType, &(mdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullInt64())
				nmap2 |= NULL_MAP_INDEX0;
			else
				mdeItemInfo->MDEntryID = ReadInt64_Optional_BMI();
			nmap2 |= NULL_MAP_INDEX1 & (ReadUInt32_Optional_BMI(&(mdeItemInfo->MDEntryDate)) - 1);
			mdeItemInfo->MDEntryTime = ReadUInt64_Mandatory_BMI();
			nmap2 |= NULL_MAP_INDEX2 & (ReadDecimal_Optional_BMI(&(mdeItemInfo->MDEntryPx)) - 1);
			if(CheckProcessNullInt64())
				nmap2 |= NULL_MAP_INDEX3;
			else
				mdeItemInfo->MDEntrySize = ReadInt64_Optional_BMI();
			if(CheckProcessNullInt64())
				nmap2 |= NULL_MAP_INDEX4;
			else
				mdeItemInfo->TradeID = ReadInt64_Optional_BMI();
			if(CheckProcessNullInt64())
				nmap2 |= NULL_MAP_INDEX5;
			else
				mdeItemInfo->MDFlags = ReadInt64_Optional_BMI();
			mdeItemInfo->NullMap = nmap2;
			this->m_prevfortsOrdersBookMDEntriesItemInfo = mdeItemInfo;
		}

		info->NullMap = nmap1;
		this->m_prevfortsOrdersBookInfo = info;
		return info;
	}
	inline FortsLogonInfo* DecodeFortsLogon() {
		FortsLogonInfo* info = GetFreeFortsLogonInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		info->NullMap = nmap1;
		this->m_prevfortsLogonInfo = info;
		return info;
	}
	inline FortsLogoutInfo* DecodeFortsLogout() {
		FortsLogoutInfo* info = GetFreeFortsLogoutInfo();
		UINT64 nmap1 = 0;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		nmap1 |= NULL_MAP_INDEX0 & (ReadString_Optional(info->Text, &(info->TextLength)) - 1);
		info->NullMap = nmap1;
		this->m_prevfortsLogoutInfo = info;
		return info;
	}
	inline FortsSnapshotInfo* GetFortsSnapshotInfoDefaultSnapshotMessage() {
		FortsSnapshotInfo *info = GetFreeFortsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		UINT64 nmap1 = 0;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		nmap1 |= NULL_MAP_INDEX0 & (ReadUInt32_Optional_BMI(&(info->LastFragment)) - 1);
		info->RptSeq = ReadUInt32_Mandatory_BMI();
		SkipToNextField(); // TotNumReports
		info->LastMsgSeqNumProcessed = ReadUInt32_Mandatory_BMI();
		if(CheckProcessNullUInt64())
			nmap1 |= NULL_MAP_INDEX1;
		else
			info->SecurityID = ReadUInt64_Optional_BMI();
		info->NullMap = nmap1;
		return info;
	}
	inline void* DecodeForts() {
		this->DecodeFortsHeader();
		if(this->m_templateId <= 9) {
			if(this->m_templateId <= 6) {
				if(this->m_templateId <= 4) {
					if(this->m_templateId == 3) {
						this->m_lastDecodedInfo = this->DecodeFortsSecurityDefinition();
						return this->m_lastDecodedInfo;
					}
					else { // 4
						this->m_lastDecodedInfo = this->DecodeFortsSecurityDefinitionUpdateReport();
						return this->m_lastDecodedInfo;
					}
				}
				else {
					if(this->m_templateId <= 5) {
						if(this->m_templateId == 4) {
							this->m_lastDecodedInfo = this->DecodeFortsSecurityDefinitionUpdateReport();
							return this->m_lastDecodedInfo;
						}
						else { // 5
							this->m_lastDecodedInfo = this->DecodeFortsSecurityStatus();
							return this->m_lastDecodedInfo;
						}
					}
					else {
						if(this->m_templateId == 5) {
							this->m_lastDecodedInfo = this->DecodeFortsSecurityStatus();
							return this->m_lastDecodedInfo;
						}
						else { // 6
							this->m_lastDecodedInfo = this->DecodeFortsHeartbeat();
							return this->m_lastDecodedInfo;
						}
					}
				}
			}
			else {
				if(this->m_templateId <= 7) {
					if(this->m_templateId == 6) {
						this->m_lastDecodedInfo = this->DecodeFortsHeartbeat();
						return this->m_lastDecodedInfo;
					}
					else { // 7
						this->m_lastDecodedInfo = this->DecodeFortsSequenceReset();
						return this->m_lastDecodedInfo;
					}
				}
				else {
					if(this->m_templateId <= 8) {
						if(this->m_templateId == 7) {
							this->m_lastDecodedInfo = this->DecodeFortsSequenceReset();
							return this->m_lastDecodedInfo;
						}
						else { // 8
							this->m_lastDecodedInfo = this->DecodeFortsTradingSessionStatus();
							return this->m_lastDecodedInfo;
						}
					}
					else {
						if(this->m_templateId == 8) {
							this->m_lastDecodedInfo = this->DecodeFortsTradingSessionStatus();
							return this->m_lastDecodedInfo;
						}
						else { // 9
							this->m_lastDecodedInfo = this->DecodeFortsNews();
							return this->m_lastDecodedInfo;
						}
					}
				}
			}
		}
		else {
			if(this->m_templateId <= 14) {
				if(this->m_templateId <= 12) {
					if(this->m_templateId == 9) {
						this->m_lastDecodedInfo = this->DecodeFortsNews();
						return this->m_lastDecodedInfo;
					}
					else { // 12
						this->m_lastDecodedInfo = this->DecodeFortsDefaultIncrementalRefreshMessage();
						return this->m_lastDecodedInfo;
					}
				}
				else {
					if(this->m_templateId <= 13) {
						if(this->m_templateId == 12) {
							this->m_lastDecodedInfo = this->DecodeFortsDefaultIncrementalRefreshMessage();
							return this->m_lastDecodedInfo;
						}
						else { // 13
							this->m_lastDecodedInfo = this->DecodeFortsDefaultSnapshotMessage();
							return this->m_lastDecodedInfo;
						}
					}
					else {
						if(this->m_templateId == 13) {
							this->m_lastDecodedInfo = this->DecodeFortsDefaultSnapshotMessage();
							return this->m_lastDecodedInfo;
						}
						else { // 14
							this->m_lastDecodedInfo = this->DecodeFortsOrdersLog();
							return this->m_lastDecodedInfo;
						}
					}
				}
			}
			else {
				if(this->m_templateId <= 15) {
					if(this->m_templateId == 14) {
						this->m_lastDecodedInfo = this->DecodeFortsOrdersLog();
						return this->m_lastDecodedInfo;
					}
					else { // 15
						this->m_lastDecodedInfo = this->DecodeFortsOrdersBook();
						return this->m_lastDecodedInfo;
					}
				}
				else {
					if(this->m_templateId <= 1000) {
						if(this->m_templateId == 15) {
							this->m_lastDecodedInfo = this->DecodeFortsOrdersBook();
							return this->m_lastDecodedInfo;
						}
						else { // 1000
							this->m_lastDecodedInfo = this->DecodeFortsLogon();
							return this->m_lastDecodedInfo;
						}
					}
					else {
						if(this->m_templateId == 1000) {
							this->m_lastDecodedInfo = this->DecodeFortsLogon();
							return this->m_lastDecodedInfo;
						}
						else { // 1001
							this->m_lastDecodedInfo = this->DecodeFortsLogout();
							return this->m_lastDecodedInfo;
						}
					}
				}
			}
		}
	}
	void PrintForts() {

		switch(this->m_templateId) {
			case 12:
				PrintFortsDefaultIncrementalRefreshMessage(static_cast<FortsDefaultIncrementalRefreshMessageInfo*>(this->m_lastDecodedInfo));
				break;
			case 13:
				PrintFortsDefaultSnapshotMessage(static_cast<FortsDefaultSnapshotMessageInfo*>(this->m_lastDecodedInfo));
				break;
			case 3:
				PrintFortsSecurityDefinition(static_cast<FortsSecurityDefinitionInfo*>(this->m_lastDecodedInfo));
				break;
			case 4:
				PrintFortsSecurityDefinitionUpdateReport(static_cast<FortsSecurityDefinitionUpdateReportInfo*>(this->m_lastDecodedInfo));
				break;
			case 5:
				PrintFortsSecurityStatus(static_cast<FortsSecurityStatusInfo*>(this->m_lastDecodedInfo));
				break;
			case 6:
				PrintFortsHeartbeat(static_cast<FortsHeartbeatInfo*>(this->m_lastDecodedInfo));
				break;
			case 7:
				PrintFortsSequenceReset(static_cast<FortsSequenceResetInfo*>(this->m_lastDecodedInfo));
				break;
			case 8:
				PrintFortsTradingSessionStatus(static_cast<FortsTradingSessionStatusInfo*>(this->m_lastDecodedInfo));
				break;
			case 9:
				PrintFortsNews(static_cast<FortsNewsInfo*>(this->m_lastDecodedInfo));
				break;
			case 14:
				PrintFortsOrdersLog(static_cast<FortsOrdersLogInfo*>(this->m_lastDecodedInfo));
				break;
			case 15:
				PrintFortsOrdersBook(static_cast<FortsOrdersBookInfo*>(this->m_lastDecodedInfo));
				break;
			case 1000:
				PrintFortsLogon(static_cast<FortsLogonInfo*>(this->m_lastDecodedInfo));
				break;
			case 1001:
				PrintFortsLogout(static_cast<FortsLogoutInfo*>(this->m_lastDecodedInfo));
				break;
		}
	}
	void PrintXmlForts() {

		switch(this->m_templateId) {
			case 12:
				PrintXmlFortsDefaultIncrementalRefreshMessage(static_cast<FortsDefaultIncrementalRefreshMessageInfo*>(this->m_lastDecodedInfo));
				break;
			case 13:
				PrintXmlFortsDefaultSnapshotMessage(static_cast<FortsDefaultSnapshotMessageInfo*>(this->m_lastDecodedInfo));
				break;
			case 3:
				PrintXmlFortsSecurityDefinition(static_cast<FortsSecurityDefinitionInfo*>(this->m_lastDecodedInfo));
				break;
			case 4:
				PrintXmlFortsSecurityDefinitionUpdateReport(static_cast<FortsSecurityDefinitionUpdateReportInfo*>(this->m_lastDecodedInfo));
				break;
			case 5:
				PrintXmlFortsSecurityStatus(static_cast<FortsSecurityStatusInfo*>(this->m_lastDecodedInfo));
				break;
			case 6:
				PrintXmlFortsHeartbeat(static_cast<FortsHeartbeatInfo*>(this->m_lastDecodedInfo));
				break;
			case 7:
				PrintXmlFortsSequenceReset(static_cast<FortsSequenceResetInfo*>(this->m_lastDecodedInfo));
				break;
			case 8:
				PrintXmlFortsTradingSessionStatus(static_cast<FortsTradingSessionStatusInfo*>(this->m_lastDecodedInfo));
				break;
			case 9:
				PrintXmlFortsNews(static_cast<FortsNewsInfo*>(this->m_lastDecodedInfo));
				break;
			case 14:
				PrintXmlFortsOrdersLog(static_cast<FortsOrdersLogInfo*>(this->m_lastDecodedInfo));
				break;
			case 15:
				PrintXmlFortsOrdersBook(static_cast<FortsOrdersBookInfo*>(this->m_lastDecodedInfo));
				break;
			case 1000:
				PrintXmlFortsLogon(static_cast<FortsLogonInfo*>(this->m_lastDecodedInfo));
				break;
			case 1001:
				PrintXmlFortsLogout(static_cast<FortsLogoutInfo*>(this->m_lastDecodedInfo));
				break;
		}
	}
	inline FortsSnapshotInfo* GetFortsSnapshotInfo() {
		this->DecodeFortsHeader();
		if(this->m_templateId == 13)
			return this->GetFortsSnapshotInfoDefaultSnapshotMessage();
		return this->GetFortsSnapshotInfoUnsupported();
	}
#pragma endregion
};

