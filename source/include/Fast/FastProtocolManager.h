#pragma once
#pragma once
#include "../Fix/FixTypes.h"
#include "FastTypes.h"
#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include "../ProgramStatistics.h"
#include <immintrin.h>

class FastProtocolManager;
class OrderTesterFond;
class OrderTesterCurr;
class TradeTesterFond;
class TradeTesterCurr;
class OrderBookTesterForts;
class StatisticsTesterFond;
class StatisticsTesterCurr;
class FeedConnection;

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

    const int maxBufferLength = 16000;
    BYTE                        *buffer;
    BYTE                        *currentPos;
    int                         bufferLength;
    UINT                        m_templateId;
    UINT64                      m_presenceMap;

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
	char	MessageEncodingConstString[6];
	const UINT	MessageEncodingConstStringLength = 5;
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
		this->m_prevastsLogonInfo = this->GetFreeAstsLogonInfo();
		this->m_prevastsLogonInfo->Used = true;
		this->m_prevastsLogoutInfo = this->GetFreeAstsLogoutInfo();
		this->m_prevastsLogoutInfo->Used = true;
		this->m_prevastsGenericItemInfo = this->GetFreeAstsGenericItemInfo();
		this->m_prevastsGenericItemInfo->Used = true;
		this->m_prevastsGenericInfo = this->GetFreeAstsGenericInfo();
		this->m_prevastsGenericInfo->Used = true;
		this->m_prevastsOLSFONDItemInfo = this->GetFreeAstsOLSFONDItemInfo();
		this->m_prevastsOLSFONDItemInfo->Used = true;
		this->m_prevastsOLSFONDInfo = this->GetFreeAstsOLSFONDInfo();
		this->m_prevastsOLSFONDInfo->Used = true;
		this->m_prevastsOLSCURRItemInfo = this->GetFreeAstsOLSCURRItemInfo();
		this->m_prevastsOLSCURRItemInfo->Used = true;
		this->m_prevastsOLSCURRInfo = this->GetFreeAstsOLSCURRInfo();
		this->m_prevastsOLSCURRInfo->Used = true;
		this->m_prevastsTLSFONDItemInfo = this->GetFreeAstsTLSFONDItemInfo();
		this->m_prevastsTLSFONDItemInfo->Used = true;
		this->m_prevastsTLSFONDInfo = this->GetFreeAstsTLSFONDInfo();
		this->m_prevastsTLSFONDInfo->Used = true;
		this->m_prevastsTLSCURRItemInfo = this->GetFreeAstsTLSCURRItemInfo();
		this->m_prevastsTLSCURRItemInfo->Used = true;
		this->m_prevastsTLSCURRInfo = this->GetFreeAstsTLSCURRInfo();
		this->m_prevastsTLSCURRInfo->Used = true;
		this->m_prevastsSecurityDefinitionGroupInstrAttribItemInfo = this->GetFreeAstsSecurityDefinitionGroupInstrAttribItemInfo();
		this->m_prevastsSecurityDefinitionGroupInstrAttribItemInfo->Used = true;
		this->m_prevastsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo = this->GetFreeAstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo();
		this->m_prevastsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo->Used = true;
		this->m_prevastsSecurityDefinitionMarketSegmentGrpItemInfo = this->GetFreeAstsSecurityDefinitionMarketSegmentGrpItemInfo();
		this->m_prevastsSecurityDefinitionMarketSegmentGrpItemInfo->Used = true;
		this->m_prevastsSecurityDefinitionInfo = this->GetFreeAstsSecurityDefinitionInfo();
		this->m_prevastsSecurityDefinitionInfo->Used = true;
		this->m_prevastsSecurityStatusInfo = this->GetFreeAstsSecurityStatusInfo();
		this->m_prevastsSecurityStatusInfo->Used = true;
		this->m_prevastsTradingSessionStatusInfo = this->GetFreeAstsTradingSessionStatusInfo();
		this->m_prevastsTradingSessionStatusInfo->Used = true;
		this->m_prevastsHeartbeatInfo = this->GetFreeAstsHeartbeatInfo();
		this->m_prevastsHeartbeatInfo->Used = true;
		this->m_prevastsIncrementalGenericInfo = this->GetFreeAstsIncrementalGenericInfo();
		this->m_prevastsIncrementalGenericInfo->Used = true;
		this->m_prevastsIncrementalMSRFONDInfo = this->GetFreeAstsIncrementalMSRFONDInfo();
		this->m_prevastsIncrementalMSRFONDInfo->Used = true;
		this->m_prevastsIncrementalMSRCURRInfo = this->GetFreeAstsIncrementalMSRCURRInfo();
		this->m_prevastsIncrementalMSRCURRInfo->Used = true;
		this->m_prevastsIncrementalOLRFONDInfo = this->GetFreeAstsIncrementalOLRFONDInfo();
		this->m_prevastsIncrementalOLRFONDInfo->Used = true;
		this->m_prevastsIncrementalOLRCURRInfo = this->GetFreeAstsIncrementalOLRCURRInfo();
		this->m_prevastsIncrementalOLRCURRInfo->Used = true;
		this->m_prevastsIncrementalTLRFONDInfo = this->GetFreeAstsIncrementalTLRFONDInfo();
		this->m_prevastsIncrementalTLRFONDInfo->Used = true;
		this->m_prevastsIncrementalTLRCURRInfo = this->GetFreeAstsIncrementalTLRCURRInfo();
		this->m_prevastsIncrementalTLRCURRInfo->Used = true;
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
		this->m_prevfortsDefaultSnapshotMessageMDEntriesItemInfo->Used = true;
		this->m_prevfortsDefaultSnapshotMessageInfo = this->GetFreeFortsDefaultSnapshotMessageInfo();
		this->m_prevfortsDefaultSnapshotMessageInfo->Used = true;
		this->m_prevfortsSecurityDefinitionMDFeedTypesItemInfo = this->GetFreeFortsSecurityDefinitionMDFeedTypesItemInfo();
		this->m_prevfortsSecurityDefinitionMDFeedTypesItemInfo->Used = true;
		this->m_prevfortsSecurityDefinitionUnderlyingsItemInfo = this->GetFreeFortsSecurityDefinitionUnderlyingsItemInfo();
		this->m_prevfortsSecurityDefinitionUnderlyingsItemInfo->Used = true;
		this->m_prevfortsSecurityDefinitionInstrumentLegsItemInfo = this->GetFreeFortsSecurityDefinitionInstrumentLegsItemInfo();
		this->m_prevfortsSecurityDefinitionInstrumentLegsItemInfo->Used = true;
		this->m_prevfortsSecurityDefinitionInstrumentAttributesItemInfo = this->GetFreeFortsSecurityDefinitionInstrumentAttributesItemInfo();
		this->m_prevfortsSecurityDefinitionInstrumentAttributesItemInfo->Used = true;
		this->m_prevfortsSecurityDefinitionEvntGrpItemInfo = this->GetFreeFortsSecurityDefinitionEvntGrpItemInfo();
		this->m_prevfortsSecurityDefinitionEvntGrpItemInfo->Used = true;
		this->m_prevfortsSecurityDefinitionInfo = this->GetFreeFortsSecurityDefinitionInfo();
		this->m_prevfortsSecurityDefinitionInfo->Used = true;
		this->m_prevfortsSecurityDefinitionUpdateReportInfo = this->GetFreeFortsSecurityDefinitionUpdateReportInfo();
		this->m_prevfortsSecurityDefinitionUpdateReportInfo->Used = true;
		this->m_prevfortsSecurityStatusInfo = this->GetFreeFortsSecurityStatusInfo();
		this->m_prevfortsSecurityStatusInfo->Used = true;
		this->m_prevfortsHeartbeatInfo = this->GetFreeFortsHeartbeatInfo();
		this->m_prevfortsHeartbeatInfo->Used = true;
		this->m_prevfortsSequenceResetInfo = this->GetFreeFortsSequenceResetInfo();
		this->m_prevfortsSequenceResetInfo->Used = true;
		this->m_prevfortsTradingSessionStatusInfo = this->GetFreeFortsTradingSessionStatusInfo();
		this->m_prevfortsTradingSessionStatusInfo->Used = true;
		this->m_prevfortsNewsNewsTextItemInfo = this->GetFreeFortsNewsNewsTextItemInfo();
		this->m_prevfortsNewsNewsTextItemInfo->Used = true;
		this->m_prevfortsNewsInfo = this->GetFreeFortsNewsInfo();
		this->m_prevfortsNewsInfo->Used = true;
		this->m_prevfortsOrdersLogMDEntriesItemInfo = this->GetFreeFortsOrdersLogMDEntriesItemInfo();
		this->m_prevfortsOrdersLogMDEntriesItemInfo->Used = true;
		this->m_prevfortsOrdersLogInfo = this->GetFreeFortsOrdersLogInfo();
		this->m_prevfortsOrdersLogInfo->Used = true;
		this->m_prevfortsOrdersBookMDEntriesItemInfo = this->GetFreeFortsOrdersBookMDEntriesItemInfo();
		this->m_prevfortsOrdersBookMDEntriesItemInfo->Used = true;
		this->m_prevfortsOrdersBookInfo = this->GetFreeFortsOrdersBookInfo();
		this->m_prevfortsOrdersBookInfo->Used = true;
		this->m_prevfortsLogonInfo = this->GetFreeFortsLogonInfo();
		this->m_prevfortsLogonInfo->Used = true;
		this->m_prevfortsLogoutInfo = this->GetFreeFortsLogoutInfo();
		this->m_prevfortsLogoutInfo->Used = true;
		this->m_prevfortsDefaultIncrementalRefreshMessageInfo = this->GetFreeFortsDefaultIncrementalRefreshMessageInfo();
		this->m_prevfortsDefaultIncrementalRefreshMessageInfo->Used = true;
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
		return this->m_fortsDefaultSnapshotMessageMDEntriesItems->NewItem();
	}

	inline AutoAllocatePointerList<FortsDefaultSnapshotMessageMDEntriesItemInfo>* GetFortsDefaultSnapshotMessageMDEntriesItemInfoPool() {
		return this->m_fortsDefaultSnapshotMessageMDEntriesItems;
	}

	inline FortsDefaultSnapshotMessageInfo* GetFreeFortsDefaultSnapshotMessageInfo() {
		return this->m_fortsDefaultSnapshotMessage->NewItem();
	}

	inline AutoAllocatePointerList<FortsDefaultSnapshotMessageInfo>* GetFortsDefaultSnapshotMessageInfoPool() {
		return this->m_fortsDefaultSnapshotMessage;
	}

	inline FortsSecurityDefinitionMDFeedTypesItemInfo* GetFreeFortsSecurityDefinitionMDFeedTypesItemInfo() {
		return this->m_fortsSecurityDefinitionMDFeedTypesItems->NewItem();
	}

	inline AutoAllocatePointerList<FortsSecurityDefinitionMDFeedTypesItemInfo>* GetFortsSecurityDefinitionMDFeedTypesItemInfoPool() {
		return this->m_fortsSecurityDefinitionMDFeedTypesItems;
	}

	inline FortsSecurityDefinitionUnderlyingsItemInfo* GetFreeFortsSecurityDefinitionUnderlyingsItemInfo() {
		return this->m_fortsSecurityDefinitionUnderlyingsItems->NewItem();
	}

	inline AutoAllocatePointerList<FortsSecurityDefinitionUnderlyingsItemInfo>* GetFortsSecurityDefinitionUnderlyingsItemInfoPool() {
		return this->m_fortsSecurityDefinitionUnderlyingsItems;
	}

	inline FortsSecurityDefinitionInstrumentLegsItemInfo* GetFreeFortsSecurityDefinitionInstrumentLegsItemInfo() {
		return this->m_fortsSecurityDefinitionInstrumentLegsItems->NewItem();
	}

	inline AutoAllocatePointerList<FortsSecurityDefinitionInstrumentLegsItemInfo>* GetFortsSecurityDefinitionInstrumentLegsItemInfoPool() {
		return this->m_fortsSecurityDefinitionInstrumentLegsItems;
	}

	inline FortsSecurityDefinitionInstrumentAttributesItemInfo* GetFreeFortsSecurityDefinitionInstrumentAttributesItemInfo() {
		return this->m_fortsSecurityDefinitionInstrumentAttributesItems->NewItem();
	}

	inline AutoAllocatePointerList<FortsSecurityDefinitionInstrumentAttributesItemInfo>* GetFortsSecurityDefinitionInstrumentAttributesItemInfoPool() {
		return this->m_fortsSecurityDefinitionInstrumentAttributesItems;
	}

	inline FortsSecurityDefinitionEvntGrpItemInfo* GetFreeFortsSecurityDefinitionEvntGrpItemInfo() {
		return this->m_fortsSecurityDefinitionEvntGrpItems->NewItem();
	}

	inline AutoAllocatePointerList<FortsSecurityDefinitionEvntGrpItemInfo>* GetFortsSecurityDefinitionEvntGrpItemInfoPool() {
		return this->m_fortsSecurityDefinitionEvntGrpItems;
	}

	inline FortsSecurityDefinitionInfo* GetFreeFortsSecurityDefinitionInfo() {
		return this->m_fortsSecurityDefinition->NewItem();
	}

	inline AutoAllocatePointerList<FortsSecurityDefinitionInfo>* GetFortsSecurityDefinitionInfoPool() {
		return this->m_fortsSecurityDefinition;
	}

	inline FortsSecurityDefinitionUpdateReportInfo* GetFreeFortsSecurityDefinitionUpdateReportInfo() {
		return this->m_fortsSecurityDefinitionUpdateReport->NewItem();
	}

	inline AutoAllocatePointerList<FortsSecurityDefinitionUpdateReportInfo>* GetFortsSecurityDefinitionUpdateReportInfoPool() {
		return this->m_fortsSecurityDefinitionUpdateReport;
	}

	inline FortsSecurityStatusInfo* GetFreeFortsSecurityStatusInfo() {
		return this->m_fortsSecurityStatus->NewItem();
	}

	inline AutoAllocatePointerList<FortsSecurityStatusInfo>* GetFortsSecurityStatusInfoPool() {
		return this->m_fortsSecurityStatus;
	}

	inline FortsHeartbeatInfo* GetFreeFortsHeartbeatInfo() {
		return this->m_fortsHeartbeat->NewItem();
	}

	inline AutoAllocatePointerList<FortsHeartbeatInfo>* GetFortsHeartbeatInfoPool() {
		return this->m_fortsHeartbeat;
	}

	inline FortsSequenceResetInfo* GetFreeFortsSequenceResetInfo() {
		return this->m_fortsSequenceReset->NewItem();
	}

	inline AutoAllocatePointerList<FortsSequenceResetInfo>* GetFortsSequenceResetInfoPool() {
		return this->m_fortsSequenceReset;
	}

	inline FortsTradingSessionStatusInfo* GetFreeFortsTradingSessionStatusInfo() {
		return this->m_fortsTradingSessionStatus->NewItem();
	}

	inline AutoAllocatePointerList<FortsTradingSessionStatusInfo>* GetFortsTradingSessionStatusInfoPool() {
		return this->m_fortsTradingSessionStatus;
	}

	inline FortsNewsNewsTextItemInfo* GetFreeFortsNewsNewsTextItemInfo() {
		return this->m_fortsNewsNewsTextItems->NewItem();
	}

	inline AutoAllocatePointerList<FortsNewsNewsTextItemInfo>* GetFortsNewsNewsTextItemInfoPool() {
		return this->m_fortsNewsNewsTextItems;
	}

	inline FortsNewsInfo* GetFreeFortsNewsInfo() {
		return this->m_fortsNews->NewItem();
	}

	inline AutoAllocatePointerList<FortsNewsInfo>* GetFortsNewsInfoPool() {
		return this->m_fortsNews;
	}

	inline FortsOrdersLogMDEntriesItemInfo* GetFreeFortsOrdersLogMDEntriesItemInfo() {
		return this->m_fortsOrdersLogMDEntriesItems->NewItem();
	}

	inline AutoAllocatePointerList<FortsOrdersLogMDEntriesItemInfo>* GetFortsOrdersLogMDEntriesItemInfoPool() {
		return this->m_fortsOrdersLogMDEntriesItems;
	}

	inline FortsOrdersLogInfo* GetFreeFortsOrdersLogInfo() {
		return this->m_fortsOrdersLog->NewItem();
	}

	inline AutoAllocatePointerList<FortsOrdersLogInfo>* GetFortsOrdersLogInfoPool() {
		return this->m_fortsOrdersLog;
	}

	inline FortsOrdersBookMDEntriesItemInfo* GetFreeFortsOrdersBookMDEntriesItemInfo() {
		return this->m_fortsOrdersBookMDEntriesItems->NewItem();
	}

	inline AutoAllocatePointerList<FortsOrdersBookMDEntriesItemInfo>* GetFortsOrdersBookMDEntriesItemInfoPool() {
		return this->m_fortsOrdersBookMDEntriesItems;
	}

	inline FortsOrdersBookInfo* GetFreeFortsOrdersBookInfo() {
		return this->m_fortsOrdersBook->NewItem();
	}

	inline AutoAllocatePointerList<FortsOrdersBookInfo>* GetFortsOrdersBookInfoPool() {
		return this->m_fortsOrdersBook;
	}

	inline FortsLogonInfo* GetFreeFortsLogonInfo() {
		return this->m_fortsLogon->NewItem();
	}

	inline AutoAllocatePointerList<FortsLogonInfo>* GetFortsLogonInfoPool() {
		return this->m_fortsLogon;
	}

	inline FortsLogoutInfo* GetFreeFortsLogoutInfo() {
		return this->m_fortsLogout->NewItem();
	}

	inline AutoAllocatePointerList<FortsLogoutInfo>* GetFortsLogoutInfoPool() {
		return this->m_fortsLogout;
	}

	inline FortsDefaultIncrementalRefreshMessageInfo* GetFreeFortsDefaultIncrementalRefreshMessageInfo() {
		return this->m_fortsDefaultIncrementalRefreshMessage->NewItem();
	}

	inline AutoAllocatePointerList<FortsDefaultIncrementalRefreshMessageInfo>* GetFortsDefaultIncrementalRefreshMessageInfoPool() {
		return this->m_fortsDefaultIncrementalRefreshMessage;
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
		return this->m_astsLogon->NewItem();
	}

	inline AutoAllocatePointerList<AstsLogonInfo>* GetAstsLogonInfoPool() {
		return this->m_astsLogon;
	}

	inline AstsLogoutInfo* GetFreeAstsLogoutInfo() {
		return this->m_astsLogout->NewItem();
	}

	inline AutoAllocatePointerList<AstsLogoutInfo>* GetAstsLogoutInfoPool() {
		return this->m_astsLogout;
	}

	inline AstsGenericItemInfo* GetFreeAstsGenericItemInfo() {
		return this->m_astsGenericItems->NewItem();
	}

	inline AutoAllocatePointerList<AstsGenericItemInfo>* GetAstsGenericItemInfoPool() {
		return this->m_astsGenericItems;
	}

	inline AstsGenericInfo* GetFreeAstsGenericInfo() {
		return this->m_astsGeneric->NewItem();
	}

	inline AutoAllocatePointerList<AstsGenericInfo>* GetAstsGenericInfoPool() {
		return this->m_astsGeneric;
	}

	inline AstsOLSFONDItemInfo* GetFreeAstsOLSFONDItemInfo() {
		return this->m_astsOLSFONDItems->NewItem();
	}

	inline AutoAllocatePointerList<AstsOLSFONDItemInfo>* GetAstsOLSFONDItemInfoPool() {
		return this->m_astsOLSFONDItems;
	}

	inline AstsOLSFONDInfo* GetFreeAstsOLSFONDInfo() {
		return this->m_astsOLSFOND->NewItem();
	}

	inline AutoAllocatePointerList<AstsOLSFONDInfo>* GetAstsOLSFONDInfoPool() {
		return this->m_astsOLSFOND;
	}

	inline AstsOLSCURRItemInfo* GetFreeAstsOLSCURRItemInfo() {
		return this->m_astsOLSCURRItems->NewItem();
	}

	inline AutoAllocatePointerList<AstsOLSCURRItemInfo>* GetAstsOLSCURRItemInfoPool() {
		return this->m_astsOLSCURRItems;
	}

	inline AstsOLSCURRInfo* GetFreeAstsOLSCURRInfo() {
		return this->m_astsOLSCURR->NewItem();
	}

	inline AutoAllocatePointerList<AstsOLSCURRInfo>* GetAstsOLSCURRInfoPool() {
		return this->m_astsOLSCURR;
	}

	inline AstsTLSFONDItemInfo* GetFreeAstsTLSFONDItemInfo() {
		return this->m_astsTLSFONDItems->NewItem();
	}

	inline AutoAllocatePointerList<AstsTLSFONDItemInfo>* GetAstsTLSFONDItemInfoPool() {
		return this->m_astsTLSFONDItems;
	}

	inline AstsTLSFONDInfo* GetFreeAstsTLSFONDInfo() {
		return this->m_astsTLSFOND->NewItem();
	}

	inline AutoAllocatePointerList<AstsTLSFONDInfo>* GetAstsTLSFONDInfoPool() {
		return this->m_astsTLSFOND;
	}

	inline AstsTLSCURRItemInfo* GetFreeAstsTLSCURRItemInfo() {
		return this->m_astsTLSCURRItems->NewItem();
	}

	inline AutoAllocatePointerList<AstsTLSCURRItemInfo>* GetAstsTLSCURRItemInfoPool() {
		return this->m_astsTLSCURRItems;
	}

	inline AstsTLSCURRInfo* GetFreeAstsTLSCURRInfo() {
		return this->m_astsTLSCURR->NewItem();
	}

	inline AutoAllocatePointerList<AstsTLSCURRInfo>* GetAstsTLSCURRInfoPool() {
		return this->m_astsTLSCURR;
	}

	inline AstsSecurityDefinitionGroupInstrAttribItemInfo* GetFreeAstsSecurityDefinitionGroupInstrAttribItemInfo() {
		return this->m_astsSecurityDefinitionGroupInstrAttribItems->NewItem();
	}

	inline AutoAllocatePointerList<AstsSecurityDefinitionGroupInstrAttribItemInfo>* GetAstsSecurityDefinitionGroupInstrAttribItemInfoPool() {
		return this->m_astsSecurityDefinitionGroupInstrAttribItems;
	}

	inline AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* GetFreeAstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo() {
		return this->m_astsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems->NewItem();
	}

	inline AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo>* GetAstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfoPool() {
		return this->m_astsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItems;
	}

	inline AstsSecurityDefinitionMarketSegmentGrpItemInfo* GetFreeAstsSecurityDefinitionMarketSegmentGrpItemInfo() {
		return this->m_astsSecurityDefinitionMarketSegmentGrpItems->NewItem();
	}

	inline AutoAllocatePointerList<AstsSecurityDefinitionMarketSegmentGrpItemInfo>* GetAstsSecurityDefinitionMarketSegmentGrpItemInfoPool() {
		return this->m_astsSecurityDefinitionMarketSegmentGrpItems;
	}

	inline AstsSecurityDefinitionInfo* GetFreeAstsSecurityDefinitionInfo() {
		return this->m_astsSecurityDefinition->NewItem();
	}

	inline AutoAllocatePointerList<AstsSecurityDefinitionInfo>* GetAstsSecurityDefinitionInfoPool() {
		return this->m_astsSecurityDefinition;
	}

	inline AstsSecurityStatusInfo* GetFreeAstsSecurityStatusInfo() {
		return this->m_astsSecurityStatus->NewItem();
	}

	inline AutoAllocatePointerList<AstsSecurityStatusInfo>* GetAstsSecurityStatusInfoPool() {
		return this->m_astsSecurityStatus;
	}

	inline AstsTradingSessionStatusInfo* GetFreeAstsTradingSessionStatusInfo() {
		return this->m_astsTradingSessionStatus->NewItem();
	}

	inline AutoAllocatePointerList<AstsTradingSessionStatusInfo>* GetAstsTradingSessionStatusInfoPool() {
		return this->m_astsTradingSessionStatus;
	}

	inline AstsHeartbeatInfo* GetFreeAstsHeartbeatInfo() {
		return this->m_astsHeartbeat->NewItem();
	}

	inline AutoAllocatePointerList<AstsHeartbeatInfo>* GetAstsHeartbeatInfoPool() {
		return this->m_astsHeartbeat;
	}

	inline AstsIncrementalGenericInfo* GetFreeAstsIncrementalGenericInfo() {
		return this->m_astsIncrementalGeneric->NewItem();
	}

	inline AutoAllocatePointerList<AstsIncrementalGenericInfo>* GetAstsIncrementalGenericInfoPool() {
		return this->m_astsIncrementalGeneric;
	}

	inline AstsIncrementalMSRFONDInfo* GetFreeAstsIncrementalMSRFONDInfo() {
		return this->m_astsIncrementalMSRFOND->NewItem();
	}

	inline AutoAllocatePointerList<AstsIncrementalMSRFONDInfo>* GetAstsIncrementalMSRFONDInfoPool() {
		return this->m_astsIncrementalMSRFOND;
	}

	inline AstsIncrementalMSRCURRInfo* GetFreeAstsIncrementalMSRCURRInfo() {
		return this->m_astsIncrementalMSRCURR->NewItem();
	}

	inline AutoAllocatePointerList<AstsIncrementalMSRCURRInfo>* GetAstsIncrementalMSRCURRInfoPool() {
		return this->m_astsIncrementalMSRCURR;
	}

	inline AstsIncrementalOLRFONDInfo* GetFreeAstsIncrementalOLRFONDInfo() {
		return this->m_astsIncrementalOLRFOND->NewItem();
	}

	inline AutoAllocatePointerList<AstsIncrementalOLRFONDInfo>* GetAstsIncrementalOLRFONDInfoPool() {
		return this->m_astsIncrementalOLRFOND;
	}

	inline AstsIncrementalOLRCURRInfo* GetFreeAstsIncrementalOLRCURRInfo() {
		return this->m_astsIncrementalOLRCURR->NewItem();
	}

	inline AutoAllocatePointerList<AstsIncrementalOLRCURRInfo>* GetAstsIncrementalOLRCURRInfoPool() {
		return this->m_astsIncrementalOLRCURR;
	}

	inline AstsIncrementalTLRFONDInfo* GetFreeAstsIncrementalTLRFONDInfo() {
		return this->m_astsIncrementalTLRFOND->NewItem();
	}

	inline AutoAllocatePointerList<AstsIncrementalTLRFONDInfo>* GetAstsIncrementalTLRFONDInfoPool() {
		return this->m_astsIncrementalTLRFOND;
	}

	inline AstsIncrementalTLRCURRInfo* GetFreeAstsIncrementalTLRCURRInfo() {
		return this->m_astsIncrementalTLRCURR->NewItem();
	}

	inline AutoAllocatePointerList<AstsIncrementalTLRCURRInfo>* GetAstsIncrementalTLRCURRInfoPool() {
		return this->m_astsIncrementalTLRCURR;
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
    inline void SetNewBuffer(BYTE *buffer, int length) { 
        this->buffer = buffer;
        this->bufferLength = length;
        this->ResetBuffer();
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

    inline void WriteInt32_Mandatory(INT32 value) { 
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
    inline void WriteInt32_Optional(INT32 value) {
        if (value >= 0)
            value++;
        WriteInt32_Mandatory(value);
    }

    inline void WriteUInt32_Mandatory(UINT32 value) {
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
    inline void WriteUInt32_Optional(UINT32 value) {
        value++;
        WriteUInt32_Mandatory(value);
    }

	inline bool ReadInt32_Optional(INT32 *value) {
		INT32 result;
		UINT64 memory = *((UINT64*)(this->currentPos));
		if((memory & 0xff) == 0x80) {
			this->currentPos++;
			return false;
		}

		if ((memory & 0xff) == 0x00) { // extended positive integer
			memory >>= 8;

			if ((memory & 0x8080) == 0x8000) { // three bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEp_3Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 3;
				*value = result - 1;
				return true;
			}

			if ((memory & 0x80) == 0x80) { // two bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEp_2Byte);
#endif
				this->currentPos += 2;
				result = memory & 0x7f;
				*value = result - 1;
				return true;
			}

			if ((memory & 0x808080) == 0x800000) { // four bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEp_4Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 4;
				*value = result - 1;
				return true;
			}

			if ((memory & 0x80808080) == 0x80000000) { // five bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEp_5Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 5;
				*value = result - 1;
				return true;
			}
			// six bytes
#ifdef COLLECT_STATISTICS_FAST
			ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEp_6Byte);
#endif
			result = memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			this->currentPos += 6;
			*value = result - 1;
			return true;
		}
		else if ((memory & 0xff) == 0x7f) { // extended negative integer
			memory >>= 8;

			result = 0xffffff80;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEn_2Byte);
#endif
				this->currentPos += 2;
				*value = result;
				return true;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEn_3Byte);
#endif
				this->currentPos += 3;
				*value = result;
				return true;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEn_4Byte);
#endif
				this->currentPos += 4;
				*value = result;
				return true;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
#ifdef COLLECT_STATISTICS_FAST
			ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEn_5Byte);
#endif
			this->currentPos += 5;
			*value = result;
			return true;
		}
		else if ((memory & 0x40) != 0) { // simple negative integer
			result = 0xffffff80;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySn_1Byte);
#endif
				this->currentPos++;
				*value = result;
				return true;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySn_2Byte);
#endif
				this->currentPos += 2;
				*value = result;
				return true;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySn_3Byte);
#endif
				this->currentPos += 3;
				*value = result;
				return true;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySn_4Byte);
#endif
				this->currentPos += 4;
				*value = result;
				return true;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
#ifdef COLLECT_STATISTICS_FAST
			ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySn_5Byte);
#endif
			this->currentPos += 5;
			*value = result;
			return true;
		}
		else {  // simple positive integer

			if((memory & 0x808080) == 0x800000) { // three bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySp_3Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 3;
				*value = result - 1;
				return true;
			}

			if(memory & 0x80) { //one byte
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySp_1Byte);
#endif
				this->currentPos++;
				*value = (memory & 0x7f) - 1;
				return true;
			}

			if((memory & 0x8080) == 0x8000) { // two bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySp_2Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 2;
				*value = result - 1;
				return true;
			}
			if((memory & 0x80808080) == 0x80000000) { // four bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySp_4Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 4;
				*value = result - 1;
				return true;
			}
			// five bytes
#ifdef COLLECT_STATISTICS_FAST
			ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySp_5Byte);
#endif
			result = memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			this->currentPos += 5;
			*value = result - 1;
			return true;
		}
	}

	inline INT32 ReadInt32_Optional() {
        INT32 result = ReadInt32_Mandatory();
        if (result > 0)
            return result - 1;
        return result;
    }

	inline bool ReadInt32_Optional_Predict1(INT32 *value) {
		return ReadInt32_Optional(value);
	}

    inline INT32 ReadInt32_Optional_Predict1() {
		INT32 result;
		UINT64 memory = *((UINT64*)(this->currentPos));

		if ((memory & 0xff) == 0x00) { // extended positive integer
			memory >>= 8;

			if ((memory & 0x80) == 0x80) { // two bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEp_2Byte);
#endif
				this->currentPos += 2;
				return (memory & 0x7f) - 1;
			}

			if ((memory & 0x8080) == 0x8000) { // three bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEp_3Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 3;
				return result - 1;
			}

			if ((memory & 0x808080) == 0x800000) { // four bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEp_4Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 4;

				return result - 1;
			}

			if ((memory & 0x80808080) == 0x80000000) { // five bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEp_5Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 5;
				return result - 1;
			}
			// six bytes
#ifdef COLLECT_STATISTICS_FAST
			ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEp_6Byte);
#endif
			result = memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			this->currentPos += 6;
			return result - 1;
		}
		else if ((memory & 0xff) == 0x7f) { // extended negative integer
			memory >>= 8;

			result = 0xffffff80;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEn_2Byte);
#endif
				this->currentPos += 2;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEn_3Byte);
#endif
				this->currentPos += 3;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEn_4Byte);
#endif
				this->currentPos += 4;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
#ifdef COLLECT_STATISTICS_FAST
			ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEn_5Byte);
#endif
			this->currentPos += 5;
			return result;
		}
		else if ((memory & 0x40) != 0) { // simple negative integer
			result = 0xffffff80;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySn_1Byte);
#endif
				this->currentPos++;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySn_2Byte);
#endif
				this->currentPos += 2;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySn_3Byte);
#endif
				this->currentPos += 3;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySn_4Byte);
#endif
				this->currentPos += 4;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
#ifdef COLLECT_STATISTICS_FAST
			ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySn_5Byte);
#endif
			this->currentPos += 5;
			return result;
		}
		else {  // simple positive integer
			if(memory & 0x80) { //one byte
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySp_1Byte);
#endif
				this->currentPos++;
				return (memory & 0x7f) - 1;
			}

			if((memory & 0x808080) == 0x800000) { // three bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySp_3Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 3;
				return result - 1;
			}

			if((memory & 0x8080) == 0x8000) { // two bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySp_2Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 2;
				return result - 1;
			}
			if((memory & 0x80808080) == 0x80000000) { // four bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySp_4Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 4;
				return result - 1;
			}
			// five bytes
#ifdef COLLECT_STATISTICS_FAST
			ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySp_5Byte);
#endif
			result = memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			this->currentPos += 5;
			return result - 1;
		}
    }

    inline INT32 ReadInt32_Mandatory_Predict1() {
		INT32 result;
		UINT64 memory = *((UINT64*)(this->currentPos));

		if ((memory & 0xff) == 0x00) { // extended positive integer
			memory >>= 8;

			if ((memory & 0x80) == 0x80) { // two bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEp_2Byte);
#endif
				this->currentPos += 2;
				return memory & 0x7f;
			}

			if ((memory & 0x8080) == 0x8000) { // three bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEp_3Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 3;
				return result;
			}

			if ((memory & 0x808080) == 0x800000) { // four bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEp_4Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 4;

				return result;
			}

			if ((memory & 0x80808080) == 0x80000000) { // five bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEp_5Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 5;
				return result;
			}
			// six bytes
#ifdef COLLECT_STATISTICS_FAST
			ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEp_6Byte);
#endif
			result = memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			this->currentPos += 6;
			return result;
		}
		else if ((memory & 0xff) == 0x7f) { // extended negative integer
			memory >>= 8;

			result = 0xffffff80;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEn_2Byte);
#endif
				this->currentPos += 2;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEn_3Byte);
#endif
				this->currentPos += 3;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEn_4Byte);
#endif
				this->currentPos += 4;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
#ifdef COLLECT_STATISTICS_FAST
			ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEn_5Byte);
#endif
			this->currentPos += 5;
			return result;
		}
		else if ((memory & 0x40) != 0) { // simple negative integer
			result = 0xffffff80;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySn_1Byte);
#endif
				this->currentPos++;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySn_2Byte);
#endif
				this->currentPos += 2;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySn_3Byte);
#endif
				this->currentPos += 3;
				return result;
			}

			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySn_4Byte);
#endif
				this->currentPos += 4;
				return result;
			}
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
#ifdef COLLECT_STATISTICS_FAST
			ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySn_5Byte);
#endif
			this->currentPos += 5;
			return result;
		}
		else {  // simple positive integer
			if(memory & 0x80) { //one byte
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySp_1Byte);
#endif
				this->currentPos++;
				return memory & 0x7f;
			}

			if((memory & 0x808080) == 0x800000) { // three bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySp_3Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 3;
				return result;
			}

			if((memory & 0x8080) == 0x8000) { // two bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySp_2Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 2;
				return result;
			}
			if((memory & 0x80808080) == 0x80000000) { // four bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySp_4Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 4;
				return result;
			}
			// five bytes
#ifdef COLLECT_STATISTICS_FAST
			ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySp_5Byte);
#endif
			result = memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			this->currentPos += 5;
			return result;
		}
    }

    inline INT32 ReadInt32_Mandatory() {
        INT32 result;
        UINT64 memory = *((UINT64*)(this->currentPos));

        if ((memory & 0xff) == 0x00) { // extended positive integer
			memory >>= 8;

			if ((memory & 0x8080) == 0x8000) { // three bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEp_3Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 3;
				return result;
			}

			if ((memory & 0x80) == 0x80) { // two bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEp_2Byte);
#endif
				this->currentPos += 2;
				return memory & 0x7f;
			}

			if ((memory & 0x808080) == 0x800000) { // four bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEp_4Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 4;

				return result;
			}

			if ((memory & 0x80808080) == 0x80000000) { // five bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEp_5Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 5;
				return result;
			}
			// six bytes
#ifdef COLLECT_STATISTICS_FAST
			ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEp_6Byte);
#endif
			result = memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			this->currentPos += 6;
			return result;
		}
        else if ((memory & 0xff) == 0x7f) { // extended negative integer
            memory >>= 8;

            result = 0xffffff80;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEn_2Byte);
#endif
                this->currentPos += 2;
                return result;
            }

            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEn_3Byte);
#endif
                this->currentPos += 3;
                return result;
            }

            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEn_4Byte);
#endif
                this->currentPos += 4;
                return result;
            }

            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;
#ifdef COLLECT_STATISTICS_FAST
			ProgramStatistics::Total->Inc(Counters::cReadInt32MandatoryEn_5Byte);
#endif
            this->currentPos += 5;
            return result;
        }
        else if ((memory & 0x40) != 0) { // simple negative integer 
            result = 0xffffff80;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySn_1Byte);
#endif
                this->currentPos++;
                return result;
            }

			result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySn_2Byte);
#endif
                this->currentPos += 2;
                return result;
            }

            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySn_3Byte);
#endif
                this->currentPos += 3;
                return result;
            }

            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySn_4Byte);
#endif
                this->currentPos += 4;
                return result;
            }
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
#ifdef COLLECT_STATISTICS_FAST
            ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySn_5Byte);
#endif
            this->currentPos += 5;
            return result;
        }
        else {  // simple positive integer

			if((memory & 0x808080) == 0x800000) { // three bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySp_3Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 3;
				return result;
			}

			if(memory & 0x80) { //one byte
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySp_1Byte);
#endif
				this->currentPos++;
				return memory & 0x7f;
			}

			if((memory & 0x8080) == 0x8000) { // two bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySp_2Byte);
#endif
                    result = memory & 0x7f;
                    result <<= 7;
                    memory >>= 8;
                    result |= memory & 0x7f;
                    this->currentPos += 2;
                    return result;
            }
			if((memory & 0x80808080) == 0x80000000) { // four bytes
#ifdef COLLECT_STATISTICS_FAST
				ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySp_4Byte);
#endif
				result = memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				result <<= 7;
				memory >>= 8;
				result |= memory & 0x7f;
				this->currentPos += 4;
				return result;
			}
			// five bytes
#ifdef COLLECT_STATISTICS_FAST
			ProgramStatistics::Total->Inc(Counters::cReadInt32MandatorySp_5Byte);
#endif
			result = memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			result <<= 7;
			memory >>= 8;
			result |= memory & 0x7f;
			this->currentPos += 5;
			return result;
        }
    }

	inline UINT32 ReadUInt32_Mandatory_Fixed1() {
		UINT32 result = (UINT32)*(this->currentPos) & 0x7f;
		this->currentPos++;
		return result;
	}

    inline UINT32 ReadUInt32_Mandatory_Predict1() {
        UINT32 result = (UINT32)*(this->currentPos);
        if((result & 0x80) == 0x80) {
            this->currentPos++;
            return result & 0x7f;
        }
        return ReadUInt32_Mandatory();
    }

    inline UINT32 ReadUInt32_Mandatory() {
        INT32 result = 0;
        INT32 memory = *((INT32*)(this->currentPos));

        if((memory & 0x8080) != 0) { // first two bytes
            if((memory & 0x80) != 0) {
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadUInt32Mandatory_1Byte);
#endif
                this->currentPos++;
                return memory & 0x7f;
            }
            else {
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadUInt32Mandatory_2Byte);
#endif
                this->currentPos += 2;
                result |= memory & 0x7f;
                memory >>= 8;
                result <<= 7;
                result |= memory & 0x7f;
                return result;
            }
        }
        else { // second two bytes
            if((memory & 0x800000) != 0) {
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadUInt32Mandatory_3Byte);
#endif
                this->currentPos += 3;
                result |= memory & 0x7f;
                memory >>= 8;
                result <<= 7;
                result |= memory & 0x7f;
                memory >>= 8;
                result <<= 7;
                result |= memory & 0x7f;
                return result;
            }
            else {
                this->currentPos += 4;
                result |= memory & 0x7f;
                memory >>= 8;
                result <<= 7;
                result |= memory & 0x7f;
                memory >>= 8;
                result <<= 7;
                result |= memory & 0x7f;
                memory >>= 8;
                result <<= 7;
                result |= memory & 0x7f;

                if((memory & 0x80) == 0) {
                    result <<= 7;
                    memory = *((INT32*)(this->currentPos));
                    result |= memory & 0x7f;
                    this->currentPos++;
#ifdef COLLECT_STATISTICS_FAST
                    ProgramStatistics::Total->Inc(Counters::cReadUInt32Mandatory_5Byte);
#endif
                }
                else {
#ifdef COLLECT_STATISTICS_FAST
                    ProgramStatistics::Total->Inc(Counters::cReadUInt32Mandatory_4Byte);
#endif
                }
                return result;
            }
        }
        return result;
    }

	inline bool ReadUInt32_Optional_Fixed1(UINT32 *result) {
		UINT32 val = (UINT32)*(this->currentPos) & 0x7f;
		this->currentPos++;
		if(val == 0)
			return false;
		(*result) = val - 1;
		return true;
	}

	inline UINT32 ReadUInt32_Optional_Fixed1() {
		return ReadUInt32_Mandatory_Fixed1() - 1;
	}

    inline UINT32 ReadUInt32_Optional_Predict1() {
        return ReadUInt32_Mandatory_Predict1() - 1;
    }

    inline UINT32 ReadUInt32_Optional() {
        UINT32 result;
        UINT64 memory = *((UINT64*)(this->currentPos));

        if((memory & 0x808080) == 0x800000) { // three bytes
#ifdef COLLECT_STATISTICS_FAST
            ProgramStatistics::Total->Inc(Counters::cReadUInt32Mandatory_3Byte);
#endif
            this->currentPos += 3;
            result = memory & 0x7f;
            memory >>= 8;
            result <<= 7;
            result |= memory & 0x7f;
            memory >>= 8;
            result <<= 7;
            result |= memory & 0x7f;
            return result - 1;
        }
        else if((memory & 0x80808080) == 0x80000000) { // four bytes
#ifdef COLLECT_STATISTICS_FAST
            ProgramStatistics::Total->Inc(Counters::cReadUInt32Mandatory_4Byte);
#endif
            this->currentPos += 4;
            result = memory & 0x7f;
            memory >>= 8;
            result <<= 7;
            result |= memory & 0x7f;
            memory >>= 8;
            result <<= 7;
            result |= memory & 0x7f;
            memory >>= 8;
            result <<= 7;
            result |= memory & 0x7f;
            return result - 1;
        }
        else if((memory & 0x8080) == 0x8000) { // two bytes
#ifdef COLLECT_STATISTICS_FAST
            ProgramStatistics::Total->Inc(Counters::cReadUInt32Mandatory_2Byte);
#endif
            this->currentPos += 2;
            result = memory & 0x7f;
            memory >>= 8;
            result <<= 7;
            result |= memory & 0x7f;
            return result - 1;
        }
        else if((memory & 0x80) == 0x80) { // one byte
#ifdef COLLECT_STATISTICS_FAST
            ProgramStatistics::Total->Inc(Counters::cReadUInt32Mandatory_1Byte);
#endif
            this->currentPos++;
            return (memory & 0x7f) - 1;
        }
        //there is no need to check 5 bytes
#ifdef COLLECT_STATISTICS_FAST
        ProgramStatistics::Total->Inc(Counters::cReadUInt32Mandatory_5Byte);
#endif
        this->currentPos += 5;
        result = memory & 0x7f;
        memory >>= 8;
        result <<= 7;
        result |= memory & 0x7f;
        memory >>= 8;
        result <<= 7;
        result |= memory & 0x7f;
        memory >>= 8;
        result <<= 7;
        result |= memory & 0x7f;
        memory >>= 8;
        result <<= 7;
        result |= memory & 0x7f;
        return result - 1;
    }

    inline bool ReadUInt32_Optional(UINT32 *value) {
        INT32 result;
		UINT64 memory = *((UINT64*)(this->currentPos));
        if((memory & 0xff) == 0x80) {
            this->currentPos++;
            return false;
        }

        if((memory & 0x808080) == 0x800000) { // three bytes
#ifdef COLLECT_STATISTICS_FAST
            ProgramStatistics::Total->Inc(Counters::cReadUInt32Mandatory_3Byte);
#endif
            this->currentPos += 3;
            result = memory & 0x7f;
            memory >>= 8;
            result <<= 7;
            result |= memory & 0x7f;
            memory >>= 8;
            result <<= 7;
            result |= memory & 0x7f;
            *value = result - 1;
            return true;
        }
        else if((memory & 0x80808080) == 0x80000000) { // four bytes
#ifdef COLLECT_STATISTICS_FAST
            ProgramStatistics::Total->Inc(Counters::cReadUInt32Mandatory_4Byte);
#endif
            this->currentPos += 4;
            result = memory & 0x7f;
            memory >>= 8;
            result <<= 7;
            result |= memory & 0x7f;
            memory >>= 8;
            result <<= 7;
            result |= memory & 0x7f;
            memory >>= 8;
            result <<= 7;
            result |= memory & 0x7f;
			*value = result - 1;
            return true;
        }
        else if((memory & 0x8080) == 0x8000) { // two bytes
#ifdef COLLECT_STATISTICS_FAST
            ProgramStatistics::Total->Inc(Counters::cReadUInt32Mandatory_2Byte);
#endif
            this->currentPos += 2;
            result = memory & 0x7f;
            memory >>= 8;
            result <<= 7;
            result |= memory & 0x7f;
			*value = result - 1;
            return true;
        }
        else if((memory & 0x80) == 0x80) { // one byte
#ifdef COLLECT_STATISTICS_FAST
            ProgramStatistics::Total->Inc(Counters::cReadUInt32Mandatory_1Byte);
#endif
            this->currentPos++;
            *value = (memory & 0x7f) - 1;
            return true;
        }
        //there is no need to check 5 bytes
#ifdef COLLECT_STATISTICS_FAST
        ProgramStatistics::Total->Inc(Counters::cReadUInt32Mandatory_5Byte);
#endif
        this->currentPos += 5;
        result = memory & 0x7f;
        memory >>= 8;
        result <<= 7;
        result |= memory & 0x7f;
        memory >>= 8;
        result <<= 7;
        result |= memory & 0x7f;
        memory >>= 8;
        result <<= 7;
        result |= memory & 0x7f;
        memory >>= 8;
        result <<= 7;
        result |= memory & 0x7f;
		*value = result - 1;
        return true;
    }

    inline void WriteInt64_Optional(INT64 value) {
        if (value > 0)
            value++;
        WriteInt64_Mandatory(value);
    }
    inline void WriteInt64_Mandatory(INT64 value) { 
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
    inline void WriteUInt64_Optional(UINT64 value) {
        value++;
        WriteUInt64_Mandatory(value);
    }
    inline void WriteUInt64_Mandatory(UINT64 value) {
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

    inline INT64 ReadInt64_Mandatory() {
        INT64 result;
        INT64 memory = *((INT64*)(this->currentPos));

        INT64 valueMasked = memory & 0xff;

        if (valueMasked == 0x00) { // extended positive integer
            result = 0;
            memory >>= 8;

            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 2;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatoryEp_2Byte);
#endif
                return result;
            }
            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 3;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatoryEp_3Byte);
#endif
                return result;
            }
            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 4;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatoryEp_4Byte);
#endif
                return result;
            }
            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 5;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatoryEp_5Byte);
#endif
                return result;
            }
            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 6;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatoryEp_6Byte);
#endif
                return result;
            }
            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 7;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatoryEp_7Byte);
#endif
                return result;
            }
            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 8;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatoryEp_8Byte);
#endif
                return result;
            }
            
            this->currentPos += 8;

            result <<= 7;
            memory = *((INT64*)(this->currentPos));
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos++;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatoryEp_9Byte);
#endif
                return result;
            }

            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 2;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatoryEp_10Byte);
#endif
                return result;
            }

            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;

            this->currentPos += 3;
#ifdef COLLECT_STATISTICS_FAST
            ProgramStatistics::Total->Inc(Counters::cReadInt64MandatoryEp_11Byte);
#endif
            return result;
        }
        else if (valueMasked == 0x7f) { // extended negative integer
            memory >>= 8;

            result = 0xffffffffffffff80;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 2;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatoryEn_2Byte);
#endif
                return result;
            }
            result <<= 7;
            memory >>= 8;

            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 3;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatoryEn_3Byte);
#endif
                return result;
            }

            result <<= 7;
            memory >>= 8;

            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 4;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatoryEn_4Byte);
#endif
                return result;
            }

            result <<= 7;
            memory >>= 8;

            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 5;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatoryEn_5Byte);
#endif
                return result;
            }

            result <<= 7;
            memory >>= 8;

            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 6;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatoryEn_6Byte);
#endif
                return result;
            }

            result <<= 7;
            memory >>= 8;

            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 7;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatoryEn_7Byte);
#endif
                return result;
            }

            result <<= 7;
            memory >>= 8;

            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 8;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatoryEn_8Byte);
#endif
                return result;
            }
            
            this->currentPos += 8;
            result <<= 7;
            memory = *((INT64*)(this->currentPos));
            result |= memory & 0x7f;

            if ((memory & 0x80) != 0) {
                this->currentPos ++;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatoryEn_9Byte);
#endif
                return result;
            }

            result <<= 7;
            memory >>= 8;

            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 2;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatoryEn_10Byte);
#endif
                return result;
            }
            
            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;

            this->currentPos += 3;
#ifdef COLLECT_STATISTICS_FAST
            ProgramStatistics::Total->Inc(Counters::cReadInt64MandatoryEn_11Byte);
#endif
            return result;
        }
        else if ((memory & 0x40) != 0) { // simple negative integer 
            result = 0xffffffffffffff80;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos++;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatorySn_1Byte);
#endif
                return result;
            }
            result <<= 7;
            memory >>= 8;

            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 2;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatorySn_2Byte);
#endif
                return result;
            }

            result <<= 7;
            memory >>= 8;

            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 3;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatorySn_3Byte);
#endif
                return result;
            }

            result <<= 7;
            memory >>= 8;

            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 4;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatorySn_4Byte);
#endif
                return result;
            }

            result <<= 7;
            memory >>= 8;

            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 5;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatorySn_5Byte);
#endif
                return result;
            }

            result <<= 7;
            memory >>= 8;

            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 6;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatorySn_6Byte);
#endif
                return result;
            }

            result <<= 7;
            memory >>= 8;

            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 7;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatorySn_7Byte);
#endif
                return result;
            }

            result <<= 7;
            memory >>= 8;

            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 8;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatorySn_8Byte);
#endif
                return result;
            }

            this->currentPos += 8;
            result <<= 7;
            memory = *((INT64*)(this->currentPos));
            result |= memory & 0x7f;

            if ((memory & 0x80) != 0) {
                this->currentPos ++;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatorySn_9Byte);
#endif
                return result;
            }

            result <<= 7;
            memory >>= 8;

            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 2;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatorySn_10Byte);
#endif
                return result;
            }

            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;

            this->currentPos += 3;
#ifdef COLLECT_STATISTICS_FAST
            ProgramStatistics::Total->Inc(Counters::cReadInt64MandatorySn_11Byte);
#endif
            return result;
        }
        else {  // simple positive integer
            result = 0;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos++;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatorySp_1Byte);
#endif
                return result;
            }
            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 2;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatorySp_2Byte);
#endif
                return result;
            }
            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 3;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatorySp_3Byte);
#endif
                return result;
            }

            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 4;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatorySp_4Byte);
#endif
                return result;
            }

            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 5;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatorySp_5Byte);
#endif
                return result;
            }

            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 6;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatorySp_6Byte);
#endif
                return result;
            }

            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 7;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatorySp_7Byte);
#endif
                return result;
            }

            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 8;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatorySp_8Byte);
#endif
                return result;
            }

            this->currentPos += 8;

            result <<= 7;
            memory = *((INT64*)(this->currentPos));
            result |= memory & 0x7f;

            if ((memory & 0x80) != 0) {
                this->currentPos ++;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatorySp_9Byte);
#endif
                return result;
            }

            result <<= 7;
            memory >>= 8;
            result |= memory & 0x7f;
            if ((memory & 0x80) != 0) {
                this->currentPos += 2;
#ifdef COLLECT_STATISTICS_FAST
                ProgramStatistics::Total->Inc(Counters::cReadInt64MandatorySp_10Byte);
#endif
                return result;
            }

            this->currentPos += 3;
#ifdef COLLECT_STATISTICS_FAST
            ProgramStatistics::Total->Inc(Counters::cReadInt64MandatorySp_11Byte);
#endif
            return result;
        }
    }
    inline INT64 ReadInt64_Optional() {
        INT64 value = ReadInt64_Mandatory();
        if (value > 0)
            return value - 1;
        return value;
    }

	inline UINT64 ReadUInt64_Mandatory_Predict9() {
		UINT64 memory = *(UINT64*)this->currentPos;
		unsigned char val9 = *(this->currentPos + 8);
		if((memory & 0x8080808080808080) == 0 && (val9 & 0x80) == 0x80) {
			UINT64 result = memory & 0x7f;

			memory >>= 8; result <<= 7;
			result |= memory & 0x7f; // 2 byte
			memory >>= 8; result <<= 7;
			result |= memory & 0x7f; // 3 byte
			memory >>= 8; result <<= 7;
			result |= memory & 0x7f; // 4 byte
			memory >>= 8; result <<= 7;
			result |= memory & 0x7f; // 5 byte
			memory >>= 8; result <<= 7;
			result |= memory & 0x7f; // 6 byte
			memory >>= 8; result <<= 7;
			result |= memory & 0x7f; // 7 byte
			memory >>= 8; result <<= 7;
			result |= memory & 0x7f; // 8 byte

			result <<= 7;
			result |= val9 & 0x7f;

			this->currentPos += 9;
			return result;
		}
		return ReadUInt64_Mandatory();
	}

    inline UINT64 ReadUInt64_Mandatory() {
        UINT64 result;
        UINT64 memory = *(UINT64*)this->currentPos;

        result = memory & 0x7f;
        if ((memory & 0x80) != 0) {
            this->currentPos++;
#ifdef COLLECT_STATISTICS_FAST
            ProgramStatistics::Total->Inc(Counters::cReadUInt64Mandatory_1Byte);
#endif
            return result;
        }
        result <<= 7;
        memory >>= 8;
        result |= memory & 0x7f;
        if ((memory & 0x80) != 0) {
            this->currentPos += 2;
#ifdef COLLECT_STATISTICS_FAST
            ProgramStatistics::Total->Inc(Counters::cReadUInt64Mandatory_2Byte);
#endif
            return result;
        }
        result <<= 7;
        memory >>= 8;
        result |= memory & 0x7f;
        if ((memory & 0x80) != 0) {
            this->currentPos += 3;
#ifdef COLLECT_STATISTICS_FAST
            ProgramStatistics::Total->Inc(Counters::cReadUInt64Mandatory_3Byte);
#endif
            return result;
        }

        result <<= 7;
        memory >>= 8;
        result |= memory & 0x7f;
        if ((memory & 0x80) != 0) {
            this->currentPos += 4;
#ifdef COLLECT_STATISTICS_FAST
            ProgramStatistics::Total->Inc(Counters::cReadUInt64Mandatory_4Byte);
#endif
            return result;
        }

        result <<= 7;
        memory >>= 8;
        result |= memory & 0x7f;
        if ((memory & 0x80) != 0) {
            this->currentPos += 5;
#ifdef COLLECT_STATISTICS_FAST
            ProgramStatistics::Total->Inc(Counters::cReadUInt64Mandatory_5Byte);
#endif
            return result;
        }

        result <<= 7;
        memory >>= 8;
        result |= memory & 0x7f;
        if ((memory & 0x80) != 0) {
            this->currentPos += 6;
#ifdef COLLECT_STATISTICS_FAST
            ProgramStatistics::Total->Inc(Counters::cReadUInt64Mandatory_6Byte);
#endif
            return result;
        }

        result <<= 7;
        memory >>= 8;
        result |= memory & 0x7f;
        if ((memory & 0x80) != 0) {
            this->currentPos += 7;
#ifdef COLLECT_STATISTICS_FAST
            ProgramStatistics::Total->Inc(Counters::cReadUInt64Mandatory_7Byte);
#endif
            return result;
        }

        result <<= 7;
        memory >>= 8;
        result |= memory & 0x7f;
        if ((memory & 0x80) != 0) {
            this->currentPos += 8;
#ifdef COLLECT_STATISTICS_FAST
            ProgramStatistics::Total->Inc(Counters::cReadUInt64Mandatory_8Byte);
#endif
            return result;
        }

        this->currentPos += 8;

        result <<= 7;
        memory = *((INT64*)(this->currentPos));
        result |= memory & 0x7f;

        if ((memory & 0x80) != 0) {
            this->currentPos ++;
#ifdef COLLECT_STATISTICS_FAST
            ProgramStatistics::Total->Inc(Counters::cReadUInt64Mandatory_9Byte);
#endif
            return result;
        }

        result <<= 7;
        memory >>= 8;
        result |= memory & 0x7f;

        this->currentPos +=2;
#ifdef COLLECT_STATISTICS_FAST
        ProgramStatistics::Total->Inc(Counters::cReadUInt64Mandatory_10Byte);
#endif
        return result;
    }
    inline UINT64 ReadUInt64_Optional() {
        return ReadUInt64_Mandatory() - 1;
    }

    inline void CopyToBuffer(BYTE *value, int length) { 
        memcpy(this->buffer, value, length);
    }

    // for decima exponent we use predict 1 because power of 10 will fit almost always in one byte
    inline void ReadDecimal_Optional(Decimal *value) {
        value->Exponent = ReadInt32_Optional_Predict1();
        value->Mantissa = ReadInt64_Mandatory();
    }

    inline void ReadDecimal_Mandatory(Decimal *value) {
        value->Exponent = ReadInt32_Mandatory_Predict1();
        value->Mantissa = ReadInt64_Mandatory();
    }

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
        while (true) {
            if ((memory & 0x8080808080808080) != 0) {
                if ((memory & 0x0000000080808080) != 0) {
                    if ((memory & 0x8080) != 0) {
                        if ((memory & 0x80) != 0) {
                            this->currentPos++;
                            break;
                        }
                        else {
                            this->currentPos += 2;
                            break;
                        }
                    }
                    else {
                        if ((memory & 0x800000) != 0) {
                            this->currentPos += 3;
                            break;
                        }
                        else {
                            this->currentPos += 4;
                            break;
                        }
                    }
                }
                else {
                    if ((memory & 0x0000808000000000) != 0) {
                        if ((memory & 0x0000008000000000) != 0) {
                            this->currentPos += 5;
                            break;
                        }
                        else {
                            this->currentPos += 6;
                            break;
                        }
                    }
                    else {
                        if ((memory & 0x0080000000000000) != 0) {
                            this->currentPos += 7;
                            break;
                        }
                        else {
                            this->currentPos += 8;
                            break;
                        }
                    }
                }
            }
            this->currentPos += 8;
            memory = *((UINT64*)this->currentPos);
        }
    }

	inline void ReadString_Optional_Fixed1(char *str, int *lengthAddress) {
		UINT64 memory = *((UINT64*)this->currentPos);
		if((memory & 0x80) != 0) {
			*str = (char)(memory & 0x7f);
			*lengthAddress = 1;
			this->currentPos++;
		}
		else if ((memory & 0xffff) == 0x8000) {
			*lengthAddress = 0;
			this->currentPos += 2;
			return;
		}
	}

	inline void ReadString_Optional_Predict12(char *str, int *lengthAddress) {
		UINT64 memory = *((UINT64*)this->currentPos);

		if((memory & 0x80) != 0) {
			*str = (char)(memory & 0x7f);
			*lengthAddress = 1;
			this->currentPos++;
		}
		else if((memory & 0xffff) == 0x8000) {
			*lengthAddress = 0;
			this->currentPos += 2;
			return;
		}
		else {
			*((unsigned short*)str) = memory & 0x7fff;
			*lengthAddress = 2;
			this->currentPos += 2;
		}
	}

    inline void ReadString_Optional_Predict67Other(char *str, int *lengthAddress) {
        UINT64 memory = *((UINT64*)this->currentPos);
        if ((memory & 0xffff) == 0x8000) {
            *lengthAddress = 0;
            this->currentPos += 2;
            return;
        }
        if((memory & 0x808080808080) == 0x800000000000) { // 6 bytes
            *((unsigned short*)str) = (unsigned short)memory;
            this->currentPos += 2; str += 2; memory >>= 16;
            *((unsigned int*)str) = (unsigned int)(memory & 0x7fffffff);

            *lengthAddress = 6;
            this->currentPos += 4;
            return;
        }
        if((memory & 0x80808080808080) == 0x80000000000000) { // 7 bytes
            *str = (char)memory;
            this->currentPos++; str++; memory >>= 8;

            *((unsigned short*)str) = (unsigned short)memory;
            this->currentPos += 2; str += 2; memory >>= 16;

            *((unsigned int*)str) = (unsigned int)(memory & 0x7fffffff);

            *lengthAddress = 7;
            this->currentPos += 4;
            return;
        }
        ReadString_Optional(str, lengthAddress);
    }

    inline void ReadString_Optional(char *str, int *lengthAddress) {
        UINT64 memory = *((UINT64*)this->currentPos);
        int length = 0;
        if ((memory & 0xffff) == 0x8000) { 
            *lengthAddress = 0;
            this->currentPos += 2;
            return;
        }
        while (true) {
            if ((memory & 0x8080808080808080) != 0) {
                if ((memory & 0x0000000080808080) != 0) {
                    if ((memory & 0x8080) != 0) {
                        if ((memory & 0x80) != 0) {
                            *str = (char)(memory & 0x7f);
                            length++;
                            this->currentPos++;
                            break;
                        }
                        else {
                            *((unsigned short*)str) = (unsigned short)(memory & 0x7fff);
                            length += 2;
                            this->currentPos += 2;
                            break;
                        }
                    }
                    else {
                        if ((memory & 0x800000) != 0) {

                            *str = (char)memory;
                            this->currentPos++; str++; memory >>= 8;
                            *((unsigned short*)str) = (unsigned short)(memory & 0x7fff);

                            length += 3;
                            this->currentPos += 2;
                            break;
                        }
                        else {
                            *((unsigned int*)str) = (unsigned int)(memory & 0x7fffffff);
                            length += 4;
                            this->currentPos += 4;
                            break;
                        }
                    }
                }
                else {
                    if ((memory & 0x0000808000000000) != 0) {
                        if ((memory & 0x0000008000000000) != 0) {

                            *str = (char)memory;
                            this->currentPos++; str++; memory >>= 8;
                            *((unsigned int*)str) = (unsigned int)(memory & 0x7fffffff);

                            length += 5;
                            this->currentPos += 4;
                            break;
                        }
                        else {
                            *((unsigned short*)str) = (unsigned short)memory;
                            this->currentPos += 2; str += 2; memory >>= 16;
                            *((unsigned int*)str) = (unsigned int)(memory & 0x7fffffff);

                            length += 6;
                            this->currentPos += 4;
                            break;
                        }
                    }
                    else {
                        if ((memory & 0x0080000000000000) != 0) {

                            *str = (char)memory;
                            this->currentPos++; str++; memory >>= 8;

                            *((unsigned short*)str) = (unsigned short)memory;
                            this->currentPos += 2; str += 2; memory >>= 16;

                            *((unsigned int*)str) = (unsigned int)(memory & 0x7fffffff);

                            length += 7;
                            this->currentPos += 4;
                            break;
                        }
                        else {
                            *((UINT64*)str) = memory & 0x7fffffffffffffff;

                            length += 8;
                            this->currentPos += 8;
                            break;
                        }
                    }
                }
            }
            *((UINT64*)str) = memory;
            str += 8;

            length += 8;
            this->currentPos += 8;
            memory = *((UINT64*)this->currentPos);
        }
        *lengthAddress = length;
    }

	inline void ReadString_Mandatory_Fixed1(char *str, int *lengthAddress) {
		unsigned char memory = *(this->currentPos);
		if (memory == 0x80) {
			*lengthAddress = 0;
			this->currentPos ++;
			return;
		}
		*str = (char)(memory & 0x7f);
		*lengthAddress = 1;
		this->currentPos++;
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
            if ((memory & 0x8080808080808080) != 0) {
                if ((memory & 0x0000000080808080) != 0) {
                    if ((memory & 0x8080) != 0) {
                        if ((memory & 0x80) != 0) {
                            *str = (char)(memory & 0x7f);
                            length++;
                            this->currentPos++;
                            break;
                        }
                        else {
                            *((unsigned short*)str) = (unsigned short)(memory & 0x7fff);
                            length += 2;
                            this->currentPos += 2;
                            break;
                        }
                    }
                    else {
                        if ((memory & 0x800000) != 0) {

                            *str = (char)memory;
                            this->currentPos++; str++; memory >>= 8;
                            *((unsigned short*)str) = (unsigned short)(memory & 0x7fff);

                            length += 3;
                            this->currentPos += 2;
                            break;
                        }
                        else {
                            *((unsigned int*)str) = (unsigned int)(memory & 0x7fffffff);
                            length += 4;
                            this->currentPos += 4;
                            break;
                        }
                    }
                }
                else {
                    if ((memory & 0x0000808000000000) != 0) {
                        if ((memory & 0x0000008000000000) != 0) {

                            *str = (char)memory;
                            this->currentPos++; str++; memory >>= 8;
                            *((unsigned int*)str) = (unsigned int)(memory & 0x7fffffff);

                            length += 5;
                            this->currentPos += 4;
                            break;
                        }
                        else {
                            *((unsigned short*)str) = (unsigned short)memory;
                            this->currentPos += 2; str += 2; memory >>= 16;
                            *((unsigned int*)str) = (unsigned int)(memory & 0x7fffffff);

                            length += 6;
                            this->currentPos += 4;
                            break;
                        }
                    }
                    else {
                        if ((memory & 0x0080000000000000) != 0) {

                            *str = (char)memory;
                            this->currentPos++; str++; memory >>= 8;

                            *((unsigned short*)str) = (unsigned short)memory;
                            this->currentPos += 2; str += 2; memory >>= 16;

                            *((unsigned int*)str) = (unsigned int)(memory & 0x7fffffff);

                            length += 7;
                            this->currentPos += 4;
                            break;
                        }
                        else {
                            *((UINT64*)str) = memory & 0x7fffffffffffffff;

                            length += 8;
                            this->currentPos += 8;
                            break;
                        }
                    }
                }
            }
            *((UINT64*)str) = memory;
            str += 8;

            length += 8;
            this->currentPos += 8;
            memory = *((UINT64*)this->currentPos);
        }
        *lengthAddress = length;
    }

    inline void ReadByteVector_Optional(BYTE *vecPtrAddress, int *lengthAddress, int maxLength) {
        int length = ReadUInt32_Optional();
        int copyLength = length > maxLength? maxLength: length;
        this->CopyString((char*)vecPtrAddress, (char*)(this->currentPos), copyLength);
        this->currentPos += length;
        *lengthAddress = copyLength;
    }
    inline void ReadByteVector_Mandatory(BYTE *vecPtrAddress, int *lengthAddress, int maxLength) {
        int length = ReadUInt32_Mandatory();
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

		this->ParsePresenceMap(&(this->m_presenceMap));
		this->m_templateId = ReadUInt32_Mandatory();
	}

	int GetAstsTotalNumReports() {
		// ReadMsgNumber and DecodeHeader should be called first
		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		return ReadInt32_Optional();
	}
	inline void* DecodeAstsUnsupportedMessage() { return 0; }
	inline AstsSnapshotInfo* GetAstsSnapshotInfoUnsupported() { return 0; }
	inline AstsLogonInfo* DecodeAstsLogon() {
		AstsLogonInfo* info = GetFreeAstsLogonInfo();
		info->PresenceMap = this->m_presenceMap;

		ReadString_Mandatory(info->TargetCompID, &(info->TargetCompIDLength));
		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		info->HeartBtInt = ReadInt32_Mandatory();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			ReadString_Optional(info->Username, &(info->UsernameLength));
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			ReadString_Optional(info->Password, &(info->PasswordLength));
		ReadString_Mandatory(info->DefaultApplVerID, &(info->DefaultApplVerIDLength));
		this->m_prevastsLogonInfo = info;
		return info;
	}
	inline AstsLogoutInfo* DecodeAstsLogout() {
		AstsLogoutInfo* info = GetFreeAstsLogoutInfo();
		info->PresenceMap = this->m_presenceMap;

		ReadString_Mandatory(info->TargetCompID, &(info->TargetCompIDLength));
		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			ReadString_Optional(info->Text, &(info->TextLength));
		this->m_prevastsLogoutInfo = info;
		return info;
	}
	inline AstsGenericInfo* DecodeAstsGeneric() {
		AstsGenericInfo* info = GetFreeAstsGenericInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		if(!ReadUInt32_Optional(&(info->LastMsgSeqNumProcessed)))
			info->NullMap |= NULL_MAP_INDEX1;
		info->RptSeq = ReadInt32_Mandatory();
		if(!ReadUInt32_Optional(&(info->LastFragment)))
			info->NullMap |= NULL_MAP_INDEX2;
		if(!ReadUInt32_Optional(&(info->RouteFirst)))
			info->NullMap |= NULL_MAP_INDEX3;
		if(!ReadInt32_Optional(&(info->TradSesStatus)))
			info->NullMap |= NULL_MAP_INDEX4;
		if(!ReadInt32_Optional(&(info->MDSecurityTradingStatus)))
			info->NullMap |= NULL_MAP_INDEX5;
		if(!ReadUInt32_Optional(&(info->AuctionIndicator)))
			info->NullMap |= NULL_MAP_INDEX6;
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX7;
		else
			ReadDecimal_Optional(&(info->NetChgPrevDay));

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict1();
		AstsGenericItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsGenericItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				ReadString_Optional_Fixed1(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				ReadString_Optional_Predict67Other(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryDate)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryTime)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			if(!ReadUInt32_Optional(&(gmdeItemInfo->OrigTime)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
			else
				ReadString_Optional(gmdeItemInfo->QuoteCondition, &(gmdeItemInfo->QuoteConditionLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
			else
				ReadString_Optional(gmdeItemInfo->TradeCondition, &(gmdeItemInfo->TradeConditionLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
			else
				ReadString_Optional(gmdeItemInfo->OpenCloseSettlFlag, &(gmdeItemInfo->OpenCloseSettlFlagLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
			else
				ReadString_Optional(gmdeItemInfo->OrdType, &(gmdeItemInfo->OrdTypeLength));
			if(!ReadUInt32_Optional(&(gmdeItemInfo->EffectiveTime)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
			if(!ReadUInt32_Optional(&(gmdeItemInfo->StartTime)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->BidMarketSize));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX17;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->AskMarketSize));
			if(!ReadInt32_Optional(&(gmdeItemInfo->TotalNumOfTrades)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX18;
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX19;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX20;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX21;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
			if(!ReadInt32_Optional(&(gmdeItemInfo->OfferNbOr)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX22;
			if(!ReadInt32_Optional(&(gmdeItemInfo->BidNbOr)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX23;
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX24;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			if(!ReadUInt32_Optional(&(gmdeItemInfo->SettlDate)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX25;
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX26;
			else
				ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength));
			if(!ReadInt32_Optional(&(gmdeItemInfo->SumQtyOfBest)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX27;
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX28;
			else
				ReadString_Optional(gmdeItemInfo->OrderSide, &(gmdeItemInfo->OrderSideLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX29;
			else
				ReadString_Optional_Fixed1(gmdeItemInfo->OrderStatus, &(gmdeItemInfo->OrderStatusLength));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX30;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MinCurrPx));
			if(!ReadUInt32_Optional(&(gmdeItemInfo->MinCurrPxChgTime)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX31;
			if(!ReadUInt32_Optional(&(gmdeItemInfo->VolumeIndicator)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX32;
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX33;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if(!ReadInt32_Optional(&(gmdeItemInfo->PriceType)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX34;
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX35;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->NominalValue));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX36;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX37;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if(!ReadUInt32_Optional(&(gmdeItemInfo->BuyBackDate)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX38;
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX39;
			else
				ReadString_Optional(gmdeItemInfo->CXFlag, &(gmdeItemInfo->CXFlagLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX40;
			else
				ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			this->m_prevastsGenericItemInfo = gmdeItemInfo;
		}

		this->m_prevastsGenericInfo = info;
		return info;
	}
	inline AstsIncrementalGenericInfo* DecodeAstsIncrementalGeneric() {
		AstsIncrementalGenericInfo* info = GetFreeAstsIncrementalGenericInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict1();
		AstsGenericItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsGenericItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
			if(!ReadUInt32_Optional_Fixed1(&(gmdeItemInfo->MDUpdateAction)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				ReadString_Optional_Fixed1(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			else
				ReadString_Optional_Predict67Other(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(!ReadInt32_Optional(&(gmdeItemInfo->RptSeq)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryDate)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			if(!ReadUInt32_Optional(&(gmdeItemInfo->OrigTime)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
			if(!ReadUInt32_Optional(&(gmdeItemInfo->SettlDate)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
			else
				ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength));
			if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryTime)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
			if(!ReadUInt32_Optional(&(gmdeItemInfo->EffectiveTime)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
			if(!ReadUInt32_Optional(&(gmdeItemInfo->StartTime)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
			else
				ReadString_Optional(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;
			else
				ReadString_Optional(gmdeItemInfo->QuoteCondition, &(gmdeItemInfo->QuoteConditionLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;
			else
				ReadString_Optional(gmdeItemInfo->TradeCondition, &(gmdeItemInfo->TradeConditionLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;
			else
				ReadString_Optional(gmdeItemInfo->OpenCloseSettlFlag, &(gmdeItemInfo->OpenCloseSettlFlagLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX17;
			else
				ReadString_Optional(gmdeItemInfo->OrdType, &(gmdeItemInfo->OrdTypeLength));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX18;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->NetChgPrevDay));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX19;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX20;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX21;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX22;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->BidMarketSize));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX23;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->AskMarketSize));
			if(!ReadInt32_Optional(&(gmdeItemInfo->TotalNumOfTrades)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX24;
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX25;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX26;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX27;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
			if(!ReadInt32_Optional(&(gmdeItemInfo->OfferNbOr)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX28;
			if(!ReadInt32_Optional(&(gmdeItemInfo->BidNbOr)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX29;
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX30;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			if(!ReadInt32_Optional(&(gmdeItemInfo->SumQtyOfBest)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX31;
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX32;
			else
				ReadString_Optional(gmdeItemInfo->OrderSide, &(gmdeItemInfo->OrderSideLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX33;
			else
				ReadString_Optional_Fixed1(gmdeItemInfo->OrderStatus, &(gmdeItemInfo->OrderStatusLength));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX34;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MinCurrPx));
			if(!ReadUInt32_Optional(&(gmdeItemInfo->MinCurrPxChgTime)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX35;
			if(!ReadUInt32_Optional(&(gmdeItemInfo->VolumeIndicator)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX36;
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX37;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if(!ReadInt32_Optional(&(gmdeItemInfo->PriceType)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX38;
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX39;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->NominalValue));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX40;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX41;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if(!ReadUInt32_Optional(&(gmdeItemInfo->BuyBackDate)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX42;
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX43;
			else
				ReadString_Optional(gmdeItemInfo->CXFlag, &(gmdeItemInfo->CXFlagLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX44;
			else
				ReadString_Optional(gmdeItemInfo->TradingSessionID, &(gmdeItemInfo->TradingSessionIDLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX45;
			else
				ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			this->m_prevastsGenericItemInfo = gmdeItemInfo;
		}

		this->m_prevastsIncrementalGenericInfo = info;
		return info;
	}
	inline AstsOLSFONDInfo* DecodeAstsOLSFOND() {
		AstsOLSFONDInfo* info = GetFreeAstsOLSFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		if(!ReadUInt32_Optional(&(info->LastMsgSeqNumProcessed)))
			info->NullMap |= NULL_MAP_INDEX0;
		info->RptSeq = ReadInt32_Mandatory();
		if(!ReadUInt32_Optional(&(info->LastFragment)))
			info->NullMap |= NULL_MAP_INDEX1;
		if(!ReadUInt32_Optional(&(info->RouteFirst)))
			info->NullMap |= NULL_MAP_INDEX2;
		if(!ReadInt32_Optional(&(info->TradSesStatus)))
			info->NullMap |= NULL_MAP_INDEX3;
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		if(!ReadInt32_Optional(&(info->MDSecurityTradingStatus)))
			info->NullMap |= NULL_MAP_INDEX5;
		if(!ReadUInt32_Optional(&(info->AuctionIndicator)))
			info->NullMap |= NULL_MAP_INDEX6;

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict1();
		AstsOLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsOLSFONDItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
				else
					ReadString_Optional_Fixed1(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->MDEntryType, m_prevastsOLSFONDItemInfo->MDEntryType, m_prevastsOLSFONDItemInfo->MDEntryTypeLength);
				gmdeItemInfo->MDEntryTypeLength = this->m_prevastsOLSFONDItemInfo->MDEntryTypeLength;
			}
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				ReadString_Optional_Predict67Other(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryDate)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			}
			else {
				gmdeItemInfo->MDEntryDate = this->m_prevastsOLSFONDItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX2)) {
				if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryTime)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevastsOLSFONDItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(!ReadUInt32_Optional(&(gmdeItemInfo->OrigTime)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevastsOLSFONDItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevastsOLSFONDItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevastsOLSFONDItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			}
			else {
				gmdeItemInfo->Yield = this->m_prevastsOLSFONDItemInfo->Yield;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
				else
					ReadString_Optional_Fixed1(gmdeItemInfo->OrderStatus, &(gmdeItemInfo->OrderStatusLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrderStatus, m_prevastsOLSFONDItemInfo->OrderStatus, m_prevastsOLSFONDItemInfo->OrderStatusLength);
				gmdeItemInfo->OrderStatusLength = this->m_prevastsOLSFONDItemInfo->OrderStatusLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX8)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
				else
					ReadString_Optional(gmdeItemInfo->OrdType, &(gmdeItemInfo->OrdTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrdType, m_prevastsOLSFONDItemInfo->OrdType, m_prevastsOLSFONDItemInfo->OrdTypeLength);
				gmdeItemInfo->OrdTypeLength = this->m_prevastsOLSFONDItemInfo->OrdTypeLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX9)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
			}
			else {
				gmdeItemInfo->TotalVolume = this->m_prevastsOLSFONDItemInfo->TotalVolume;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX10)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
				else
					ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionSubID, m_prevastsOLSFONDItemInfo->TradingSessionSubID, m_prevastsOLSFONDItemInfo->TradingSessionSubIDLength);
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevastsOLSFONDItemInfo->TradingSessionSubIDLength;
			}
			this->m_prevastsOLSFONDItemInfo = gmdeItemInfo;
		}

		this->m_prevastsOLSFONDInfo = info;
		return info;
	}
	inline AstsOLSCURRInfo* DecodeAstsOLSCURR() {
		AstsOLSCURRInfo* info = GetFreeAstsOLSCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		if(!ReadUInt32_Optional(&(info->LastMsgSeqNumProcessed)))
			info->NullMap |= NULL_MAP_INDEX0;
		info->RptSeq = ReadInt32_Mandatory();
		if(!ReadUInt32_Optional(&(info->LastFragment)))
			info->NullMap |= NULL_MAP_INDEX1;
		if(!ReadUInt32_Optional(&(info->RouteFirst)))
			info->NullMap |= NULL_MAP_INDEX2;
		if(!ReadInt32_Optional(&(info->TradSesStatus)))
			info->NullMap |= NULL_MAP_INDEX3;
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		if(!ReadInt32_Optional(&(info->MDSecurityTradingStatus)))
			info->NullMap |= NULL_MAP_INDEX5;

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict1();
		AstsOLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsOLSCURRItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
				else
					ReadString_Optional_Fixed1(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->MDEntryType, m_prevastsOLSCURRItemInfo->MDEntryType, m_prevastsOLSCURRItemInfo->MDEntryTypeLength);
				gmdeItemInfo->MDEntryTypeLength = this->m_prevastsOLSCURRItemInfo->MDEntryTypeLength;
			}
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				ReadString_Optional_Predict67Other(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryDate)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			}
			else {
				gmdeItemInfo->MDEntryDate = this->m_prevastsOLSCURRItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX2)) {
				if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryTime)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevastsOLSCURRItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(!ReadUInt32_Optional(&(gmdeItemInfo->OrigTime)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevastsOLSCURRItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevastsOLSCURRItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevastsOLSCURRItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
				else
					ReadString_Optional_Fixed1(gmdeItemInfo->OrderStatus, &(gmdeItemInfo->OrderStatusLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrderStatus, m_prevastsOLSCURRItemInfo->OrderStatus, m_prevastsOLSCURRItemInfo->OrderStatusLength);
				gmdeItemInfo->OrderStatusLength = this->m_prevastsOLSCURRItemInfo->OrderStatusLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
				else
					ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionSubID, m_prevastsOLSCURRItemInfo->TradingSessionSubID, m_prevastsOLSCURRItemInfo->TradingSessionSubIDLength);
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevastsOLSCURRItemInfo->TradingSessionSubIDLength;
			}
			this->m_prevastsOLSCURRItemInfo = gmdeItemInfo;
		}

		this->m_prevastsOLSCURRInfo = info;
		return info;
	}
	inline AstsTLSFONDInfo* DecodeAstsTLSFOND() {
		AstsTLSFONDInfo* info = GetFreeAstsTLSFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		if(!ReadUInt32_Optional(&(info->LastMsgSeqNumProcessed)))
			info->NullMap |= NULL_MAP_INDEX0;
		info->RptSeq = ReadInt32_Mandatory();
		if(!ReadUInt32_Optional(&(info->LastFragment)))
			info->NullMap |= NULL_MAP_INDEX1;
		if(!ReadUInt32_Optional(&(info->RouteFirst)))
			info->NullMap |= NULL_MAP_INDEX2;
		if(!ReadInt32_Optional(&(info->TradSesStatus)))
			info->NullMap |= NULL_MAP_INDEX3;
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		if(!ReadInt32_Optional(&(info->MDSecurityTradingStatus)))
			info->NullMap |= NULL_MAP_INDEX5;
		if(!ReadUInt32_Optional(&(info->AuctionIndicator)))
			info->NullMap |= NULL_MAP_INDEX6;

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict1();
		AstsTLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsTLSFONDItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			ReadString_Mandatory_Fixed1(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				ReadString_Optional_Predict67Other(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryDate)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			}
			else {
				gmdeItemInfo->MDEntryDate = this->m_prevastsTLSFONDItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryTime)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevastsTLSFONDItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX2)) {
				if(!ReadUInt32_Optional(&(gmdeItemInfo->OrigTime)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevastsTLSFONDItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
				else
					ReadString_Optional(gmdeItemInfo->OrderSide, &(gmdeItemInfo->OrderSideLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrderSide, m_prevastsTLSFONDItemInfo->OrderSide, m_prevastsTLSFONDItemInfo->OrderSideLength);
				gmdeItemInfo->OrderSideLength = this->m_prevastsTLSFONDItemInfo->OrderSideLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevastsTLSFONDItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevastsTLSFONDItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			}
			else {
				gmdeItemInfo->AccruedInterestAmt = this->m_prevastsTLSFONDItemInfo->AccruedInterestAmt;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			}
			else {
				gmdeItemInfo->TradeValue = this->m_prevastsTLSFONDItemInfo->TradeValue;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX8)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			}
			else {
				gmdeItemInfo->Yield = this->m_prevastsTLSFONDItemInfo->Yield;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX9)) {
				if(!ReadUInt32_Optional(&(gmdeItemInfo->SettlDate)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
			}
			else {
				gmdeItemInfo->SettlDate = this->m_prevastsTLSFONDItemInfo->SettlDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX10)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
				else
					ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->SettleType, m_prevastsTLSFONDItemInfo->SettleType, m_prevastsTLSFONDItemInfo->SettleTypeLength);
				gmdeItemInfo->SettleTypeLength = this->m_prevastsTLSFONDItemInfo->SettleTypeLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX11)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->Price));
			}
			else {
				gmdeItemInfo->Price = this->m_prevastsTLSFONDItemInfo->Price;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX12)) {
				if(!ReadInt32_Optional(&(gmdeItemInfo->PriceType)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;
			}
			else {
				gmdeItemInfo->PriceType = this->m_prevastsTLSFONDItemInfo->PriceType;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX13)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			}
			else {
				gmdeItemInfo->RepoToPx = this->m_prevastsTLSFONDItemInfo->RepoToPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX14)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			}
			else {
				gmdeItemInfo->BuyBackPx = this->m_prevastsTLSFONDItemInfo->BuyBackPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX15)) {
				if(!ReadUInt32_Optional(&(gmdeItemInfo->BuyBackDate)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;
			}
			else {
				gmdeItemInfo->BuyBackDate = this->m_prevastsTLSFONDItemInfo->BuyBackDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX16)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX17;
				else
					ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionSubID, m_prevastsTLSFONDItemInfo->TradingSessionSubID, m_prevastsTLSFONDItemInfo->TradingSessionSubIDLength);
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevastsTLSFONDItemInfo->TradingSessionSubIDLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX17)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX18;
				else
					ReadString_Optional(gmdeItemInfo->RefOrderID, &(gmdeItemInfo->RefOrderIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->RefOrderID, m_prevastsTLSFONDItemInfo->RefOrderID, m_prevastsTLSFONDItemInfo->RefOrderIDLength);
				gmdeItemInfo->RefOrderIDLength = this->m_prevastsTLSFONDItemInfo->RefOrderIDLength;
			}
			this->m_prevastsTLSFONDItemInfo = gmdeItemInfo;
		}

		this->m_prevastsTLSFONDInfo = info;
		return info;
	}
	inline AstsTLSCURRInfo* DecodeAstsTLSCURR() {
		AstsTLSCURRInfo* info = GetFreeAstsTLSCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		if(!ReadUInt32_Optional(&(info->LastMsgSeqNumProcessed)))
			info->NullMap |= NULL_MAP_INDEX0;
		info->RptSeq = ReadInt32_Mandatory();
		if(!ReadUInt32_Optional(&(info->LastFragment)))
			info->NullMap |= NULL_MAP_INDEX1;
		if(!ReadUInt32_Optional(&(info->RouteFirst)))
			info->NullMap |= NULL_MAP_INDEX2;
		if(!ReadInt32_Optional(&(info->TradSesStatus)))
			info->NullMap |= NULL_MAP_INDEX3;
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		if(!ReadInt32_Optional(&(info->MDSecurityTradingStatus)))
			info->NullMap |= NULL_MAP_INDEX5;

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict1();
		AstsTLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsTLSCURRItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			ReadString_Mandatory_Fixed1(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				ReadString_Optional_Predict67Other(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryDate)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			}
			else {
				gmdeItemInfo->MDEntryDate = this->m_prevastsTLSCURRItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryTime)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevastsTLSCURRItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX2)) {
				if(!ReadUInt32_Optional(&(gmdeItemInfo->OrigTime)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevastsTLSCURRItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
				else
					ReadString_Optional(gmdeItemInfo->OrderSide, &(gmdeItemInfo->OrderSideLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrderSide, m_prevastsTLSCURRItemInfo->OrderSide, m_prevastsTLSCURRItemInfo->OrderSideLength);
				gmdeItemInfo->OrderSideLength = this->m_prevastsTLSCURRItemInfo->OrderSideLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevastsTLSCURRItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevastsTLSCURRItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			}
			else {
				gmdeItemInfo->TradeValue = this->m_prevastsTLSCURRItemInfo->TradeValue;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(!ReadUInt32_Optional(&(gmdeItemInfo->SettlDate)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
			}
			else {
				gmdeItemInfo->SettlDate = this->m_prevastsTLSCURRItemInfo->SettlDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX8)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
				else
					ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->SettleType, m_prevastsTLSCURRItemInfo->SettleType, m_prevastsTLSCURRItemInfo->SettleTypeLength);
				gmdeItemInfo->SettleTypeLength = this->m_prevastsTLSCURRItemInfo->SettleTypeLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX9)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->Price));
			}
			else {
				gmdeItemInfo->Price = this->m_prevastsTLSCURRItemInfo->Price;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX10)) {
				if(!ReadInt32_Optional(&(gmdeItemInfo->PriceType)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
			}
			else {
				gmdeItemInfo->PriceType = this->m_prevastsTLSCURRItemInfo->PriceType;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX11)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			}
			else {
				gmdeItemInfo->RepoToPx = this->m_prevastsTLSCURRItemInfo->RepoToPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX12)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			}
			else {
				gmdeItemInfo->BuyBackPx = this->m_prevastsTLSCURRItemInfo->BuyBackPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX13)) {
				if(!ReadUInt32_Optional(&(gmdeItemInfo->BuyBackDate)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;
			}
			else {
				gmdeItemInfo->BuyBackDate = this->m_prevastsTLSCURRItemInfo->BuyBackDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX14)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;
				else
					ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionSubID, m_prevastsTLSCURRItemInfo->TradingSessionSubID, m_prevastsTLSCURRItemInfo->TradingSessionSubIDLength);
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevastsTLSCURRItemInfo->TradingSessionSubIDLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX15)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;
				else
					ReadString_Optional(gmdeItemInfo->RefOrderID, &(gmdeItemInfo->RefOrderIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->RefOrderID, m_prevastsTLSCURRItemInfo->RefOrderID, m_prevastsTLSCURRItemInfo->RefOrderIDLength);
				gmdeItemInfo->RefOrderIDLength = this->m_prevastsTLSCURRItemInfo->RefOrderIDLength;
			}
			this->m_prevastsTLSCURRItemInfo = gmdeItemInfo;
		}

		this->m_prevastsTLSCURRInfo = info;
		return info;
	}
	inline AstsIncrementalMSRFONDInfo* DecodeAstsIncrementalMSRFOND() {
		AstsIncrementalMSRFONDInfo* info = GetFreeAstsIncrementalMSRFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		if(CheckProcessNullUInt64())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->LastUpdateTime = ReadUInt64_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict1();
		AstsGenericItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsGenericItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
			if(!ReadUInt32_Optional_Fixed1(&(gmdeItemInfo->MDUpdateAction)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				ReadString_Optional_Fixed1(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			else
				ReadString_Optional_Predict67Other(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			else
				ReadString_Optional(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength));
			if(!ReadInt32_Optional(&(gmdeItemInfo->RptSeq)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryDate)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
			if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryTime)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
			if(!ReadUInt32_Optional(&(gmdeItemInfo->StartTime)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
			else
				ReadString_Optional(gmdeItemInfo->QuoteCondition, &(gmdeItemInfo->QuoteConditionLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
			else
				ReadString_Optional(gmdeItemInfo->TradeCondition, &(gmdeItemInfo->TradeConditionLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
			else
				ReadString_Optional(gmdeItemInfo->OpenCloseSettlFlag, &(gmdeItemInfo->OpenCloseSettlFlagLength));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->NetChgPrevDay));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX17;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->BidMarketSize));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX18;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->AskMarketSize));
			if(!ReadInt32_Optional(&(gmdeItemInfo->TotalNumOfTrades)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX19;
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX20;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX21;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(!ReadInt32_Optional(&(gmdeItemInfo->OfferNbOr)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX22;
			if(!ReadInt32_Optional(&(gmdeItemInfo->BidNbOr)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX23;
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX24;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX25;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MinCurrPx));
			if(!ReadUInt32_Optional(&(gmdeItemInfo->MinCurrPxChgTime)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX26;
			if(!ReadUInt32_Optional(&(gmdeItemInfo->VolumeIndicator)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX27;
			if(!ReadUInt32_Optional(&(gmdeItemInfo->SettlDate)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX28;
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX29;
			else
				ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX30;
			else
				ReadString_Optional(gmdeItemInfo->CXFlag, &(gmdeItemInfo->CXFlagLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX31;
			else
				ReadString_Optional(gmdeItemInfo->TradingSessionID, &(gmdeItemInfo->TradingSessionIDLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX32;
			else
				ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			this->m_prevastsGenericItemInfo = gmdeItemInfo;
		}

		this->m_prevastsIncrementalMSRFONDInfo = info;
		return info;
	}
	inline AstsIncrementalMSRCURRInfo* DecodeAstsIncrementalMSRCURR() {
		AstsIncrementalMSRCURRInfo* info = GetFreeAstsIncrementalMSRCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		if(CheckProcessNullUInt64())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->LastUpdateTime = ReadUInt64_Optional();

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict1();
		AstsGenericItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsGenericItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
			if(!ReadUInt32_Optional_Fixed1(&(gmdeItemInfo->MDUpdateAction)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				ReadString_Optional_Fixed1(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			else
				ReadString_Optional_Predict67Other(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			else
				ReadString_Optional(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength));
			if(!ReadInt32_Optional(&(gmdeItemInfo->RptSeq)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryDate)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
			if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryTime)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
			if(!ReadUInt32_Optional(&(gmdeItemInfo->StartTime)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
			else
				ReadString_Optional(gmdeItemInfo->QuoteCondition, &(gmdeItemInfo->QuoteConditionLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
			else
				ReadString_Optional(gmdeItemInfo->TradeCondition, &(gmdeItemInfo->TradeConditionLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
			else
				ReadString_Optional(gmdeItemInfo->OpenCloseSettlFlag, &(gmdeItemInfo->OpenCloseSettlFlagLength));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->NetChgPrevDay));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromWAPrice));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgOpenInterest));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->BidMarketSize));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX17;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->AskMarketSize));
			if(!ReadInt32_Optional(&(gmdeItemInfo->TotalNumOfTrades)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX18;
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX19;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(!ReadInt32_Optional(&(gmdeItemInfo->OfferNbOr)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX20;
			if(!ReadInt32_Optional(&(gmdeItemInfo->BidNbOr)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX21;
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX22;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->ChgFromSettlmnt));
			if(!ReadUInt32_Optional(&(gmdeItemInfo->SettlDate)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX23;
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX24;
			else
				ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX25;
			else
				ReadString_Optional(gmdeItemInfo->CXFlag, &(gmdeItemInfo->CXFlagLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX26;
			else
				ReadString_Optional(gmdeItemInfo->TradingSessionID, &(gmdeItemInfo->TradingSessionIDLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX27;
			else
				ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			this->m_prevastsGenericItemInfo = gmdeItemInfo;
		}

		this->m_prevastsIncrementalMSRCURRInfo = info;
		return info;
	}
	inline AstsIncrementalOLRFONDInfo* DecodeAstsIncrementalOLRFOND() {
		AstsIncrementalOLRFONDInfo* info = GetFreeAstsIncrementalOLRFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict1();
		AstsOLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsOLSFONDItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(!ReadUInt32_Optional_Fixed1(&(gmdeItemInfo->MDUpdateAction)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
				else
					ReadString_Optional_Fixed1(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->MDEntryType, m_prevastsOLSFONDItemInfo->MDEntryType, m_prevastsOLSFONDItemInfo->MDEntryTypeLength);
				gmdeItemInfo->MDEntryTypeLength = this->m_prevastsOLSFONDItemInfo->MDEntryTypeLength;
			}
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			else
				ReadString_Optional_Predict67Other(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
				else
					ReadString_Optional(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength));
			}
			else {
				this->CopyString(gmdeItemInfo->Symbol, m_prevastsOLSFONDItemInfo->Symbol, m_prevastsOLSFONDItemInfo->SymbolLength);
				gmdeItemInfo->SymbolLength = this->m_prevastsOLSFONDItemInfo->SymbolLength;
			}
			if(!ReadInt32_Optional(&(gmdeItemInfo->RptSeq)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX2)) {
				if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryDate)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
			}
			else {
				gmdeItemInfo->MDEntryDate = this->m_prevastsOLSFONDItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryTime)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevastsOLSFONDItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(!ReadUInt32_Optional(&(gmdeItemInfo->OrigTime)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevastsOLSFONDItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevastsOLSFONDItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevastsOLSFONDItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			}
			else {
				gmdeItemInfo->Yield = this->m_prevastsOLSFONDItemInfo->Yield;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX8)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
				else
					ReadString_Optional_Fixed1(gmdeItemInfo->OrderStatus, &(gmdeItemInfo->OrderStatusLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrderStatus, m_prevastsOLSFONDItemInfo->OrderStatus, m_prevastsOLSFONDItemInfo->OrderStatusLength);
				gmdeItemInfo->OrderStatusLength = this->m_prevastsOLSFONDItemInfo->OrderStatusLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX9)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
				else
					ReadString_Optional(gmdeItemInfo->OrdType, &(gmdeItemInfo->OrdTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrdType, m_prevastsOLSFONDItemInfo->OrdType, m_prevastsOLSFONDItemInfo->OrdTypeLength);
				gmdeItemInfo->OrdTypeLength = this->m_prevastsOLSFONDItemInfo->OrdTypeLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX10)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->TotalVolume));
			}
			else {
				gmdeItemInfo->TotalVolume = this->m_prevastsOLSFONDItemInfo->TotalVolume;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX11)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;
				else
					ReadString_Optional(gmdeItemInfo->TradingSessionID, &(gmdeItemInfo->TradingSessionIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionID, m_prevastsOLSFONDItemInfo->TradingSessionID, m_prevastsOLSFONDItemInfo->TradingSessionIDLength);
				gmdeItemInfo->TradingSessionIDLength = this->m_prevastsOLSFONDItemInfo->TradingSessionIDLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX12)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;
				else
					ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionSubID, m_prevastsOLSFONDItemInfo->TradingSessionSubID, m_prevastsOLSFONDItemInfo->TradingSessionSubIDLength);
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevastsOLSFONDItemInfo->TradingSessionSubIDLength;
			}
			this->m_prevastsOLSFONDItemInfo = gmdeItemInfo;
		}

		this->m_prevastsIncrementalOLRFONDInfo = info;
		return info;
	}
	inline AstsIncrementalOLRCURRInfo* DecodeAstsIncrementalOLRCURR() {
		AstsIncrementalOLRCURRInfo* info = GetFreeAstsIncrementalOLRCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict1();
		AstsOLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsOLSCURRItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;

			this->ParsePresenceMap(&(gmdeItemInfo->PresenceMap));

			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX0)) {
				if(!ReadUInt32_Optional_Fixed1(&(gmdeItemInfo->MDUpdateAction)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			}
			else {
				gmdeItemInfo->MDUpdateAction = this->m_prevastsOLSCURRItemInfo->MDUpdateAction;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX1)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
				else
					ReadString_Optional_Fixed1(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			}
			else {
				this->CopyString(gmdeItemInfo->MDEntryType, m_prevastsOLSCURRItemInfo->MDEntryType, m_prevastsOLSCURRItemInfo->MDEntryTypeLength);
				gmdeItemInfo->MDEntryTypeLength = this->m_prevastsOLSCURRItemInfo->MDEntryTypeLength;
			}
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			else
				ReadString_Optional_Predict67Other(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX2)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
				else
					ReadString_Optional(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength));
			}
			else {
				this->CopyString(gmdeItemInfo->Symbol, m_prevastsOLSCURRItemInfo->Symbol, m_prevastsOLSCURRItemInfo->SymbolLength);
				gmdeItemInfo->SymbolLength = this->m_prevastsOLSCURRItemInfo->SymbolLength;
			}
			if(!ReadInt32_Optional(&(gmdeItemInfo->RptSeq)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX3)) {
				if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryDate)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
			}
			else {
				gmdeItemInfo->MDEntryDate = this->m_prevastsOLSCURRItemInfo->MDEntryDate;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX4)) {
				if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryTime)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
			}
			else {
				gmdeItemInfo->MDEntryTime = this->m_prevastsOLSCURRItemInfo->MDEntryTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX5)) {
				if(!ReadUInt32_Optional(&(gmdeItemInfo->OrigTime)))
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
			}
			else {
				gmdeItemInfo->OrigTime = this->m_prevastsOLSCURRItemInfo->OrigTime;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX6)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			}
			else {
				gmdeItemInfo->MDEntryPx = this->m_prevastsOLSCURRItemInfo->MDEntryPx;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX7)) {
				if(CheckProcessNullDecimal())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
				else
					ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			}
			else {
				gmdeItemInfo->MDEntrySize = this->m_prevastsOLSCURRItemInfo->MDEntrySize;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX8)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
				else
					ReadString_Optional_Fixed1(gmdeItemInfo->OrderStatus, &(gmdeItemInfo->OrderStatusLength));
			}
			else {
				this->CopyString(gmdeItemInfo->OrderStatus, m_prevastsOLSCURRItemInfo->OrderStatus, m_prevastsOLSCURRItemInfo->OrderStatusLength);
				gmdeItemInfo->OrderStatusLength = this->m_prevastsOLSCURRItemInfo->OrderStatusLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX9)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
				else
					ReadString_Optional(gmdeItemInfo->TradingSessionID, &(gmdeItemInfo->TradingSessionIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionID, m_prevastsOLSCURRItemInfo->TradingSessionID, m_prevastsOLSCURRItemInfo->TradingSessionIDLength);
				gmdeItemInfo->TradingSessionIDLength = this->m_prevastsOLSCURRItemInfo->TradingSessionIDLength;
			}
			if(CheckOptionalFieldPresence(gmdeItemInfo->PresenceMap, PRESENCE_MAP_INDEX10)) {
				if(CheckProcessNullString())
					gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
				else
					ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			}
			else {
				this->CopyString(gmdeItemInfo->TradingSessionSubID, m_prevastsOLSCURRItemInfo->TradingSessionSubID, m_prevastsOLSCURRItemInfo->TradingSessionSubIDLength);
				gmdeItemInfo->TradingSessionSubIDLength = this->m_prevastsOLSCURRItemInfo->TradingSessionSubIDLength;
			}
			this->m_prevastsOLSCURRItemInfo = gmdeItemInfo;
		}

		this->m_prevastsIncrementalOLRCURRInfo = info;
		return info;
	}
	inline AstsIncrementalTLRFONDInfo* DecodeAstsIncrementalTLRFOND() {
		AstsIncrementalTLRFONDInfo* info = GetFreeAstsIncrementalTLRFONDInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict1();
		AstsTLSFONDItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsTLSFONDItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
			if(!ReadUInt32_Optional_Fixed1(&(gmdeItemInfo->MDUpdateAction)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			ReadString_Mandatory_Fixed1(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				ReadString_Optional_Predict67Other(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			else
				ReadString_Optional(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength));
			if(!ReadInt32_Optional(&(gmdeItemInfo->RptSeq)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryDate)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryTime)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
			if(!ReadUInt32_Optional(&(gmdeItemInfo->OrigTime)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
			else
				ReadString_Optional(gmdeItemInfo->OrderSide, &(gmdeItemInfo->OrderSideLength));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->AccruedInterestAmt));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->Yield));
			if(!ReadUInt32_Optional(&(gmdeItemInfo->SettlDate)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;
			else
				ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if(!ReadInt32_Optional(&(gmdeItemInfo->PriceType)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX17;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX18;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if(!ReadUInt32_Optional(&(gmdeItemInfo->BuyBackDate)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX19;
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX20;
			else
				ReadString_Optional(gmdeItemInfo->TradingSessionID, &(gmdeItemInfo->TradingSessionIDLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX21;
			else
				ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX22;
			else
				ReadString_Optional(gmdeItemInfo->RefOrderID, &(gmdeItemInfo->RefOrderIDLength));
			this->m_prevastsTLSFONDItemInfo = gmdeItemInfo;
		}

		this->m_prevastsIncrementalTLRFONDInfo = info;
		return info;
	}
	inline AstsIncrementalTLRCURRInfo* DecodeAstsIncrementalTLRCURR() {
		AstsIncrementalTLRCURRInfo* info = GetFreeAstsIncrementalTLRCURRInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime

		info->GroupMDEntriesCount = ReadUInt32_Mandatory_Predict1();
		AstsTLSCURRItemInfo* gmdeItemInfo = NULL;

		for(int i = 0; i < info->GroupMDEntriesCount; i++) {
			gmdeItemInfo = GetFreeAstsTLSCURRItemInfo();
			info->GroupMDEntries[i] = gmdeItemInfo;
			if(!ReadUInt32_Optional_Fixed1(&(gmdeItemInfo->MDUpdateAction)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			ReadString_Mandatory_Fixed1(gmdeItemInfo->MDEntryType, &(gmdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				ReadString_Optional_Predict67Other(gmdeItemInfo->MDEntryID, &(gmdeItemInfo->MDEntryIDLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			else
				ReadString_Optional(gmdeItemInfo->Symbol, &(gmdeItemInfo->SymbolLength));
			if(!ReadInt32_Optional(&(gmdeItemInfo->RptSeq)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryDate)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			if(!ReadUInt32_Optional(&(gmdeItemInfo->MDEntryTime)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX5;
			if(!ReadUInt32_Optional(&(gmdeItemInfo->OrigTime)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX6;
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX7;
			else
				ReadString_Optional(gmdeItemInfo->OrderSide, &(gmdeItemInfo->OrderSideLength));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX8;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntryPx));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX9;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->MDEntrySize));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX10;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->TradeValue));
			if(!ReadUInt32_Optional(&(gmdeItemInfo->SettlDate)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX11;
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX12;
			else
				ReadString_Optional(gmdeItemInfo->SettleType, &(gmdeItemInfo->SettleTypeLength));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX13;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->Price));
			if(!ReadInt32_Optional(&(gmdeItemInfo->PriceType)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX14;
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX15;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->RepoToPx));
			if(CheckProcessNullDecimal())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX16;
			else
				ReadDecimal_Optional(&(gmdeItemInfo->BuyBackPx));
			if(!ReadUInt32_Optional(&(gmdeItemInfo->BuyBackDate)))
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX17;
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX18;
			else
				ReadString_Optional(gmdeItemInfo->TradingSessionID, &(gmdeItemInfo->TradingSessionIDLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX19;
			else
				ReadString_Optional_Predict12(gmdeItemInfo->TradingSessionSubID, &(gmdeItemInfo->TradingSessionSubIDLength));
			if(CheckProcessNullString())
				gmdeItemInfo->NullMap |= NULL_MAP_INDEX20;
			else
				ReadString_Optional(gmdeItemInfo->RefOrderID, &(gmdeItemInfo->RefOrderIDLength));
			this->m_prevastsTLSCURRItemInfo = gmdeItemInfo;
		}

		this->m_prevastsIncrementalTLRCURRInfo = info;
		return info;
	}
	inline AstsSecurityDefinitionInfo* DecodeAstsSecurityDefinition() {
		AstsSecurityDefinitionInfo* info = GetFreeAstsSecurityDefinitionInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		if(!ReadInt32_Optional(&(info->TotNumReports)))
			info->NullMap |= NULL_MAP_INDEX0;
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			ReadString_Optional(info->Symbol, &(info->SymbolLength));
		if(CheckProcessNullByteVector())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			ReadByteVector_Optional(info->SecurityID, &(info->SecurityIDLength), 128);
		if(CheckProcessNullByteVector())
			info->NullMap |= NULL_MAP_INDEX3;
		else
			ReadByteVector_Optional(info->SecurityIDSource, &(info->SecurityIDSourceLength), 128);
		if(!ReadInt32_Optional(&(info->Product)))
			info->NullMap |= NULL_MAP_INDEX4;
		if(CheckProcessNullByteVector())
			info->NullMap |= NULL_MAP_INDEX5;
		else
			ReadByteVector_Optional(info->CFICode, &(info->CFICodeLength), 128);
		if(CheckProcessNullByteVector())
			info->NullMap |= NULL_MAP_INDEX6;
		else
			ReadByteVector_Optional(info->SecurityType, &(info->SecurityTypeLength), 128);
		if(!ReadUInt32_Optional(&(info->MaturityDate)))
			info->NullMap |= NULL_MAP_INDEX7;
		if(!ReadUInt32_Optional(&(info->SettlDate)))
			info->NullMap |= NULL_MAP_INDEX8;
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX9;
		else
			ReadString_Optional(info->SettleType, &(info->SettleTypeLength));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX10;
		else
			ReadDecimal_Optional(&(info->OrigIssueAmt));
		if(!ReadUInt32_Optional(&(info->CouponPaymentDate)))
			info->NullMap |= NULL_MAP_INDEX11;
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX12;
		else
			ReadDecimal_Optional(&(info->CouponRate));
		if(!ReadUInt32_Optional(&(info->SettlFixingDate)))
			info->NullMap |= NULL_MAP_INDEX13;
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX14;
		else
			ReadDecimal_Optional(&(info->DividendNetPx));
		if(CheckProcessNullByteVector())
			info->NullMap |= NULL_MAP_INDEX15;
		else
			ReadByteVector_Optional(info->SecurityDesc, &(info->SecurityDescLength), 128);
		if(CheckProcessNullByteVector())
			info->NullMap |= NULL_MAP_INDEX16;
		else
			ReadByteVector_Optional(info->EncodedSecurityDesc, &(info->EncodedSecurityDescLength), 128);
		if(CheckProcessNullByteVector())
			info->NullMap |= NULL_MAP_INDEX17;
		else
			ReadByteVector_Optional(info->QuoteText, &(info->QuoteTextLength), 128);

		if(CheckProcessNullInt32()) {
			info->GroupInstrAttribCount = 0;
			info->NullMap |= NULL_MAP_INDEX18;
		}
		else
			info->GroupInstrAttribCount = ReadUInt32_Optional_Predict1();
		AstsSecurityDefinitionGroupInstrAttribItemInfo* giaItemInfo = NULL;

		for(int i = 0; i < info->GroupInstrAttribCount; i++) {
			giaItemInfo = GetFreeAstsSecurityDefinitionGroupInstrAttribItemInfo();
			info->GroupInstrAttrib[i] = giaItemInfo;
			giaItemInfo->InstrAttribType = ReadInt32_Mandatory();
			if(CheckProcessNullByteVector())
				giaItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				ReadByteVector_Optional(giaItemInfo->InstrAttribValue, &(giaItemInfo->InstrAttribValueLength), 128);
			this->m_prevastsSecurityDefinitionGroupInstrAttribItemInfo = giaItemInfo;
		}

		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX19;
		else
			ReadString_Optional(info->Currency, &(info->CurrencyLength));

		if(CheckProcessNullInt32()) {
			info->MarketSegmentGrpCount = 0;
			info->NullMap |= NULL_MAP_INDEX20;
		}
		else
			info->MarketSegmentGrpCount = ReadUInt32_Optional_Predict1();
		AstsSecurityDefinitionMarketSegmentGrpItemInfo* msgItemInfo = NULL;

		for(int i = 0; i < info->MarketSegmentGrpCount; i++) {
			msgItemInfo = GetFreeAstsSecurityDefinitionMarketSegmentGrpItemInfo();
			info->MarketSegmentGrp[i] = msgItemInfo;
			if(CheckProcessNullDecimal())
				msgItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				ReadDecimal_Optional(&(msgItemInfo->RoundLot));

			if(CheckProcessNullInt32()) {
				msgItemInfo->TradingSessionRulesGrpCount = 0;
				msgItemInfo->NullMap |= NULL_MAP_INDEX1;
			}
			else
				msgItemInfo->TradingSessionRulesGrpCount = ReadUInt32_Optional_Predict1();
			AstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo* tsrgItemInfo = NULL;

			for(int i = 0; i < msgItemInfo->TradingSessionRulesGrpCount; i++) {
				tsrgItemInfo = GetFreeAstsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo();
				msgItemInfo->TradingSessionRulesGrp[i] = tsrgItemInfo;
				ReadString_Mandatory(tsrgItemInfo->TradingSessionID, &(tsrgItemInfo->TradingSessionIDLength));
				if(CheckProcessNullString())
					tsrgItemInfo->NullMap |= NULL_MAP_INDEX0;
				else
					ReadString_Optional_Predict12(tsrgItemInfo->TradingSessionSubID, &(tsrgItemInfo->TradingSessionSubIDLength));
				if(!ReadInt32_Optional(&(tsrgItemInfo->SecurityTradingStatus)))
					tsrgItemInfo->NullMap |= NULL_MAP_INDEX1;
				if(!ReadInt32_Optional(&(tsrgItemInfo->OrderNote)))
					tsrgItemInfo->NullMap |= NULL_MAP_INDEX2;
				this->m_prevastsSecurityDefinitionMarketSegmentGrpTradingSessionRulesGrpItemInfo = tsrgItemInfo;
			}

			this->m_prevastsSecurityDefinitionMarketSegmentGrpItemInfo = msgItemInfo;
		}

		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX21;
		else
			ReadString_Optional(info->SettlCurrency, &(info->SettlCurrencyLength));
		if(!ReadInt32_Optional(&(info->PriceType)))
			info->NullMap |= NULL_MAP_INDEX22;
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX23;
		else
			ReadString_Optional(info->StateSecurityID, &(info->StateSecurityIDLength));
		if(CheckProcessNullByteVector())
			info->NullMap |= NULL_MAP_INDEX24;
		else
			ReadByteVector_Optional(info->EncodedShortSecurityDesc, &(info->EncodedShortSecurityDescLength), 128);
		if(CheckProcessNullByteVector())
			info->NullMap |= NULL_MAP_INDEX25;
		else
			ReadByteVector_Optional(info->MarketCode, &(info->MarketCodeLength), 128);
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX26;
		else
			ReadDecimal_Optional(&(info->MinPriceIncrement));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX27;
		else
			ReadDecimal_Optional(&(info->MktShareLimit));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX28;
		else
			ReadDecimal_Optional(&(info->MktShareThreshold));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX29;
		else
			ReadDecimal_Optional(&(info->MaxOrdersVolume));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX30;
		else
			ReadDecimal_Optional(&(info->PriceMvmLimit));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX31;
		else
			ReadDecimal_Optional(&(info->FaceValue));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX32;
		else
			ReadDecimal_Optional(&(info->BaseSwapPx));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX33;
		else
			ReadDecimal_Optional(&(info->RepoToPx));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX34;
		else
			ReadDecimal_Optional(&(info->BuyBackPx));
		if(!ReadUInt32_Optional(&(info->BuyBackDate)))
			info->NullMap |= NULL_MAP_INDEX35;
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX36;
		else
			ReadDecimal_Optional(&(info->NoSharesIssued));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX37;
		else
			ReadDecimal_Optional(&(info->HighLimit));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX38;
		else
			ReadDecimal_Optional(&(info->LowLimit));
		if(!ReadInt32_Optional(&(info->NumOfDaysToMaturity)))
			info->NullMap |= NULL_MAP_INDEX39;
		this->m_prevastsSecurityDefinitionInfo = info;
		return info;
	}
	inline AstsSecurityStatusInfo* DecodeAstsSecurityStatus() {
		AstsSecurityStatusInfo* info = GetFreeAstsSecurityStatusInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			ReadString_Optional_Predict12(info->TradingSessionSubID, &(info->TradingSessionSubIDLength));
		if(!ReadInt32_Optional(&(info->SecurityTradingStatus)))
			info->NullMap |= NULL_MAP_INDEX2;
		if(!ReadUInt32_Optional(&(info->AuctionIndicator)))
			info->NullMap |= NULL_MAP_INDEX3;
		this->m_prevastsSecurityStatusInfo = info;
		return info;
	}
	inline AstsTradingSessionStatusInfo* DecodeAstsTradingSessionStatus() {
		AstsTradingSessionStatusInfo* info = GetFreeAstsTradingSessionStatusInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		info->TradSesStatus = ReadInt32_Mandatory();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			ReadString_Optional(info->Text, &(info->TextLength));
		ReadString_Mandatory(info->TradingSessionID, &(info->TradingSessionIDLength));
		this->m_prevastsTradingSessionStatusInfo = info;
		return info;
	}
	inline AstsHeartbeatInfo* DecodeAstsHeartbeat() {
		AstsHeartbeatInfo* info = GetFreeAstsHeartbeatInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		this->m_prevastsHeartbeatInfo = info;
		return info;
	}
	inline AstsSnapshotInfo* GetAstsSnapshotInfoGeneric() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		if(!ReadUInt32_Optional(&(info->LastMsgSeqNumProcessed)))
			info->NullMap |= NULL_MAP_INDEX1;
		info->RptSeq = ReadInt32_Mandatory();
		if(!ReadUInt32_Optional(&(info->LastFragment)))
			info->NullMap |= NULL_MAP_INDEX2;
		if(!ReadUInt32_Optional(&(info->RouteFirst)))
			info->NullMap |= NULL_MAP_INDEX3;
		return info;
	}
	inline AstsSnapshotInfo* GetAstsSnapshotInfoOLSFOND() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		if(!ReadUInt32_Optional(&(info->LastMsgSeqNumProcessed)))
			info->NullMap |= NULL_MAP_INDEX0;
		info->RptSeq = ReadInt32_Mandatory();
		if(!ReadUInt32_Optional(&(info->LastFragment)))
			info->NullMap |= NULL_MAP_INDEX1;
		if(!ReadUInt32_Optional(&(info->RouteFirst)))
			info->NullMap |= NULL_MAP_INDEX2;
		SkipToNextField(); // TradSesStatus
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		return info;
	}
	inline AstsSnapshotInfo* GetAstsSnapshotInfoOLSCURR() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		if(!ReadUInt32_Optional(&(info->LastMsgSeqNumProcessed)))
			info->NullMap |= NULL_MAP_INDEX0;
		info->RptSeq = ReadInt32_Mandatory();
		if(!ReadUInt32_Optional(&(info->LastFragment)))
			info->NullMap |= NULL_MAP_INDEX1;
		if(!ReadUInt32_Optional(&(info->RouteFirst)))
			info->NullMap |= NULL_MAP_INDEX2;
		SkipToNextField(); // TradSesStatus
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		return info;
	}
	inline AstsSnapshotInfo* GetAstsSnapshotInfoTLSFOND() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		if(!ReadUInt32_Optional(&(info->LastMsgSeqNumProcessed)))
			info->NullMap |= NULL_MAP_INDEX0;
		info->RptSeq = ReadInt32_Mandatory();
		if(!ReadUInt32_Optional(&(info->LastFragment)))
			info->NullMap |= NULL_MAP_INDEX1;
		if(!ReadUInt32_Optional(&(info->RouteFirst)))
			info->NullMap |= NULL_MAP_INDEX2;
		SkipToNextField(); // TradSesStatus
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		return info;
	}
	inline AstsSnapshotInfo* GetAstsSnapshotInfoTLSCURR() {
		AstsSnapshotInfo *info = GetFreeAstsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		if(!ReadUInt32_Optional(&(info->LastMsgSeqNumProcessed)))
			info->NullMap |= NULL_MAP_INDEX0;
		info->RptSeq = ReadInt32_Mandatory();
		if(!ReadUInt32_Optional(&(info->LastFragment)))
			info->NullMap |= NULL_MAP_INDEX1;
		if(!ReadUInt32_Optional(&(info->RouteFirst)))
			info->NullMap |= NULL_MAP_INDEX2;
		SkipToNextField(); // TradSesStatus
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			ReadString_Optional(info->TradingSessionID, &(info->TradingSessionIDLength));
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
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

		this->ParsePresenceMap(&(this->m_presenceMap));
		this->m_templateId = ReadUInt32_Mandatory();
	}

	int GetFortsTotalNumReports() {
		// ReadMsgNumber and DecodeHeader should be called first
		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		return ReadInt32_Mandatory();
	}
	inline void* DecodeFortsUnsupportedMessage() { return 0; }
	inline FortsSnapshotInfo* GetFortsSnapshotInfoUnsupported() { return 0; }
	inline FortsDefaultIncrementalRefreshMessageInfo* DecodeFortsDefaultIncrementalRefreshMessage() {
		FortsDefaultIncrementalRefreshMessageInfo* info = GetFreeFortsDefaultIncrementalRefreshMessageInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		if(!ReadUInt32_Optional(&(info->LastFragment)))
			info->NullMap |= NULL_MAP_INDEX0;

		info->MDEntriesCount = ReadUInt32_Mandatory_Predict1();
		FortsDefaultSnapshotMessageMDEntriesItemInfo* mdeItemInfo = NULL;

		for(int i = 0; i < info->MDEntriesCount; i++) {
			mdeItemInfo = GetFreeFortsDefaultSnapshotMessageMDEntriesItemInfo();
			info->MDEntries[i] = mdeItemInfo;
			mdeItemInfo->MDUpdateAction = ReadUInt32_Mandatory();
			ReadString_Mandatory(mdeItemInfo->MDEntryType, &(mdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullUInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				mdeItemInfo->SecurityID = ReadUInt64_Optional();
			if(CheckProcessNullString())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				ReadString_Optional(mdeItemInfo->Symbol, &(mdeItemInfo->SymbolLength));
			if(CheckProcessNullString())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			else
				ReadString_Optional(mdeItemInfo->SecurityGroup, &(mdeItemInfo->SecurityGroupLength));
			if(!ReadUInt32_Optional(&(mdeItemInfo->ExchangeTradingSessionID)))
				mdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			mdeItemInfo->RptSeq = ReadUInt32_Mandatory();
			if(!ReadUInt32_Optional(&(mdeItemInfo->MarketDepth)))
				mdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			if(!ReadUInt32_Optional(&(mdeItemInfo->MDPriceLevel)))
				mdeItemInfo->NullMap |= NULL_MAP_INDEX5;
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX6;
			else
				mdeItemInfo->MDEntryID = ReadInt64_Optional();
			if(CheckProcessNullDecimal())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX7;
			else
				ReadDecimal_Optional(&(mdeItemInfo->MDEntryPx));
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX8;
			else
				mdeItemInfo->MDEntrySize = ReadInt64_Optional();
			if(!ReadUInt32_Optional(&(mdeItemInfo->MDEntryDate)))
				mdeItemInfo->NullMap |= NULL_MAP_INDEX9;
			mdeItemInfo->MDEntryTime = ReadUInt64_Mandatory();
			if(!ReadInt32_Optional(&(mdeItemInfo->NumberOfOrders)))
				mdeItemInfo->NullMap |= NULL_MAP_INDEX10;
			if(CheckProcessNullString())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX11;
			else
				ReadString_Optional(mdeItemInfo->MDEntryTradeType, &(mdeItemInfo->MDEntryTradeTypeLength));
			if(!ReadInt32_Optional(&(mdeItemInfo->TrdType)))
				mdeItemInfo->NullMap |= NULL_MAP_INDEX12;
			if(CheckProcessNullDecimal())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX13;
			else
				ReadDecimal_Optional(&(mdeItemInfo->LastPx));
			if(!ReadInt32_Optional(&(mdeItemInfo->MDFlags)))
				mdeItemInfo->NullMap |= NULL_MAP_INDEX14;
			if(CheckProcessNullString())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX15;
			else
				ReadString_Optional(mdeItemInfo->Currency, &(mdeItemInfo->CurrencyLength));
			if(CheckProcessNullUInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX16;
			else
				mdeItemInfo->Revision = ReadUInt64_Optional();
			if(CheckProcessNullString())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX17;
			else
				ReadString_Optional(mdeItemInfo->OrderSide, &(mdeItemInfo->OrderSideLength));
			this->m_prevfortsDefaultSnapshotMessageMDEntriesItemInfo = mdeItemInfo;
		}

		this->m_prevfortsDefaultIncrementalRefreshMessageInfo = info;
		return info;
	}
	inline FortsDefaultSnapshotMessageInfo* DecodeFortsDefaultSnapshotMessage() {
		FortsDefaultSnapshotMessageInfo* info = GetFreeFortsDefaultSnapshotMessageInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		if(!ReadUInt32_Optional(&(info->LastFragment)))
			info->NullMap |= NULL_MAP_INDEX0;
		info->RptSeq = ReadUInt32_Mandatory();
		info->TotNumReports = ReadUInt32_Mandatory();
		info->LastMsgSeqNumProcessed = ReadUInt32_Mandatory();
		if(CheckProcessNullUInt64())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			info->SecurityID = ReadUInt64_Optional();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			ReadString_Optional(info->Symbol, &(info->SymbolLength));
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX3;
		else
			ReadString_Optional(info->SecurityGroup, &(info->SecurityGroupLength));

		info->MDEntriesCount = ReadUInt32_Mandatory_Predict1();
		FortsDefaultSnapshotMessageMDEntriesItemInfo* mdeItemInfo = NULL;

		for(int i = 0; i < info->MDEntriesCount; i++) {
			mdeItemInfo = GetFreeFortsDefaultSnapshotMessageMDEntriesItemInfo();
			info->MDEntries[i] = mdeItemInfo;
			ReadString_Mandatory(mdeItemInfo->MDEntryType, &(mdeItemInfo->MDEntryTypeLength));
			if(!ReadUInt32_Optional(&(mdeItemInfo->ExchangeTradingSessionID)))
				mdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				mdeItemInfo->MDEntryID = ReadInt64_Optional();
			if(!ReadUInt32_Optional(&(mdeItemInfo->MarketDepth)))
				mdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			if(CheckProcessNullDecimal())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			else
				ReadDecimal_Optional(&(mdeItemInfo->MDEntryPx));
			if(!ReadUInt32_Optional(&(mdeItemInfo->MDEntryDate)))
				mdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			mdeItemInfo->MDEntryTime = ReadUInt64_Mandatory();
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX5;
			else
				mdeItemInfo->MDEntrySize = ReadInt64_Optional();
			if(!ReadUInt32_Optional(&(mdeItemInfo->MDPriceLevel)))
				mdeItemInfo->NullMap |= NULL_MAP_INDEX6;
			if(!ReadInt32_Optional(&(mdeItemInfo->NumberOfOrders)))
				mdeItemInfo->NullMap |= NULL_MAP_INDEX7;
			if(CheckProcessNullString())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX8;
			else
				ReadString_Optional(mdeItemInfo->MDEntryTradeType, &(mdeItemInfo->MDEntryTradeTypeLength));
			if(!ReadInt32_Optional(&(mdeItemInfo->TrdType)))
				mdeItemInfo->NullMap |= NULL_MAP_INDEX9;
			if(!ReadInt32_Optional(&(mdeItemInfo->MDFlags)))
				mdeItemInfo->NullMap |= NULL_MAP_INDEX10;
			if(CheckProcessNullString())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX11;
			else
				ReadString_Optional(mdeItemInfo->Currency, &(mdeItemInfo->CurrencyLength));
			if(CheckProcessNullString())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX12;
			else
				ReadString_Optional(mdeItemInfo->OrderSide, &(mdeItemInfo->OrderSideLength));
			this->m_prevfortsDefaultSnapshotMessageMDEntriesItemInfo = mdeItemInfo;
		}

		this->m_prevfortsDefaultSnapshotMessageInfo = info;
		return info;
	}
	inline FortsSecurityDefinitionInfo* DecodeFortsSecurityDefinition() {
		FortsSecurityDefinitionInfo* info = GetFreeFortsSecurityDefinitionInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		info->TotNumReports = ReadUInt32_Mandatory();
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		if(CheckProcessNullByteVector())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			ReadByteVector_Optional(info->SecurityDesc, &(info->SecurityDescLength), 128);
		info->SecurityID = ReadUInt64_Mandatory();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			ReadString_Optional(info->SecurityAltID, &(info->SecurityAltIDLength));
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			ReadString_Optional(info->SecurityAltIDSource, &(info->SecurityAltIDSourceLength));
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX3;
		else
			ReadString_Optional(info->SecurityType, &(info->SecurityTypeLength));
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			ReadString_Optional(info->CFICode, &(info->CFICodeLength));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX5;
		else
			ReadDecimal_Optional(&(info->StrikePrice));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX6;
		else
			ReadDecimal_Optional(&(info->ContractMultiplier));
		if(!ReadUInt32_Optional(&(info->SecurityTradingStatus)))
			info->NullMap |= NULL_MAP_INDEX7;
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX8;
		else
			ReadString_Optional(info->Currency, &(info->CurrencyLength));
		ReadString_Mandatory(info->MarketSegmentID, &(info->MarketSegmentIDLength));
		if(!ReadUInt32_Optional(&(info->TradingSessionID)))
			info->NullMap |= NULL_MAP_INDEX9;
		if(!ReadUInt32_Optional(&(info->ExchangeTradingSessionID)))
			info->NullMap |= NULL_MAP_INDEX10;
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX11;
		else
			ReadDecimal_Optional(&(info->Volatility));

		info->MDFeedTypesCount = ReadUInt32_Mandatory_Predict1();
		FortsSecurityDefinitionMDFeedTypesItemInfo* mdftItemInfo = NULL;

		for(int i = 0; i < info->MDFeedTypesCount; i++) {
			mdftItemInfo = GetFreeFortsSecurityDefinitionMDFeedTypesItemInfo();
			info->MDFeedTypes[i] = mdftItemInfo;
			ReadString_Mandatory(mdftItemInfo->MDFeedType, &(mdftItemInfo->MDFeedTypeLength));
			if(!ReadUInt32_Optional(&(mdftItemInfo->MarketDepth)))
				mdftItemInfo->NullMap |= NULL_MAP_INDEX0;
			if(!ReadUInt32_Optional(&(mdftItemInfo->MDBookType)))
				mdftItemInfo->NullMap |= NULL_MAP_INDEX1;
			this->m_prevfortsSecurityDefinitionMDFeedTypesItemInfo = mdftItemInfo;
		}


		if(CheckProcessNullInt32()) {
			info->UnderlyingsCount = 0;
			info->NullMap |= NULL_MAP_INDEX12;
		}
		else
			info->UnderlyingsCount = ReadUInt32_Optional_Predict1();
		FortsSecurityDefinitionUnderlyingsItemInfo* uItemInfo = NULL;

		for(int i = 0; i < info->UnderlyingsCount; i++) {
			uItemInfo = GetFreeFortsSecurityDefinitionUnderlyingsItemInfo();
			info->Underlyings[i] = uItemInfo;
			ReadString_Mandatory(uItemInfo->UnderlyingSymbol, &(uItemInfo->UnderlyingSymbolLength));
			if(CheckProcessNullUInt64())
				uItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				uItemInfo->UnderlyingSecurityID = ReadUInt64_Optional();
			this->m_prevfortsSecurityDefinitionUnderlyingsItemInfo = uItemInfo;
		}

		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX13;
		else
			ReadDecimal_Optional(&(info->HighLimitPx));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX14;
		else
			ReadDecimal_Optional(&(info->LowLimitPx));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX15;
		else
			ReadDecimal_Optional(&(info->MinPriceIncrement));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX16;
		else
			ReadDecimal_Optional(&(info->MinPriceIncrementAmount));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX17;
		else
			ReadDecimal_Optional(&(info->InitialMarginOnBuy));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX18;
		else
			ReadDecimal_Optional(&(info->InitialMarginOnSell));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX19;
		else
			ReadDecimal_Optional(&(info->InitialMarginSyntetic));
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX20;
		else
			ReadString_Optional(info->QuotationList, &(info->QuotationListLength));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX21;
		else
			ReadDecimal_Optional(&(info->TheorPrice));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX22;
		else
			ReadDecimal_Optional(&(info->TheorPriceLimit));

		if(CheckProcessNullInt32()) {
			info->InstrumentLegsCount = 0;
			info->NullMap |= NULL_MAP_INDEX23;
		}
		else
			info->InstrumentLegsCount = ReadUInt32_Optional_Predict1();
		FortsSecurityDefinitionInstrumentLegsItemInfo* ilItemInfo = NULL;

		for(int i = 0; i < info->InstrumentLegsCount; i++) {
			ilItemInfo = GetFreeFortsSecurityDefinitionInstrumentLegsItemInfo();
			info->InstrumentLegs[i] = ilItemInfo;
			ReadString_Mandatory(ilItemInfo->LegSymbol, &(ilItemInfo->LegSymbolLength));
			ilItemInfo->LegSecurityID = ReadUInt64_Mandatory();
			ReadDecimal_Mandatory(&(ilItemInfo->LegRatioQty));
			this->m_prevfortsSecurityDefinitionInstrumentLegsItemInfo = ilItemInfo;
		}


		if(CheckProcessNullInt32()) {
			info->InstrumentAttributesCount = 0;
			info->NullMap |= NULL_MAP_INDEX24;
		}
		else
			info->InstrumentAttributesCount = ReadUInt32_Optional_Predict1();
		FortsSecurityDefinitionInstrumentAttributesItemInfo* iaItemInfo = NULL;

		for(int i = 0; i < info->InstrumentAttributesCount; i++) {
			iaItemInfo = GetFreeFortsSecurityDefinitionInstrumentAttributesItemInfo();
			info->InstrumentAttributes[i] = iaItemInfo;
			iaItemInfo->InstrAttribType = ReadInt32_Mandatory();
			ReadString_Mandatory(iaItemInfo->InstrAttribValue, &(iaItemInfo->InstrAttribValueLength));
			this->m_prevfortsSecurityDefinitionInstrumentAttributesItemInfo = iaItemInfo;
		}

		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX25;
		else
			ReadDecimal_Optional(&(info->UnderlyingQty));
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX26;
		else
			ReadString_Optional(info->UnderlyingCurrency, &(info->UnderlyingCurrencyLength));

		if(CheckProcessNullInt32()) {
			info->EvntGrpCount = 0;
			info->NullMap |= NULL_MAP_INDEX27;
		}
		else
			info->EvntGrpCount = ReadUInt32_Optional_Predict1();
		FortsSecurityDefinitionEvntGrpItemInfo* egItemInfo = NULL;

		for(int i = 0; i < info->EvntGrpCount; i++) {
			egItemInfo = GetFreeFortsSecurityDefinitionEvntGrpItemInfo();
			info->EvntGrp[i] = egItemInfo;
			egItemInfo->EventType = ReadInt32_Mandatory();
			egItemInfo->EventDate = ReadUInt32_Mandatory();
			egItemInfo->EventTime = ReadUInt64_Mandatory();
			this->m_prevfortsSecurityDefinitionEvntGrpItemInfo = egItemInfo;
		}

		if(!ReadUInt32_Optional(&(info->MaturityDate)))
			info->NullMap |= NULL_MAP_INDEX28;
		if(!ReadUInt32_Optional(&(info->MaturityTime)))
			info->NullMap |= NULL_MAP_INDEX29;
		this->m_prevfortsSecurityDefinitionInfo = info;
		return info;
	}
	inline FortsSecurityDefinitionUpdateReportInfo* DecodeFortsSecurityDefinitionUpdateReport() {
		FortsSecurityDefinitionUpdateReportInfo* info = GetFreeFortsSecurityDefinitionUpdateReportInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		info->SecurityID = ReadUInt64_Mandatory();
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			ReadDecimal_Optional(&(info->Volatility));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			ReadDecimal_Optional(&(info->TheorPrice));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			ReadDecimal_Optional(&(info->TheorPriceLimit));
		this->m_prevfortsSecurityDefinitionUpdateReportInfo = info;
		return info;
	}
	inline FortsSecurityStatusInfo* DecodeFortsSecurityStatus() {
		FortsSecurityStatusInfo* info = GetFreeFortsSecurityStatusInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		info->SecurityID = ReadUInt64_Mandatory();
		ReadString_Mandatory(info->Symbol, &(info->SymbolLength));
		if(!ReadUInt32_Optional(&(info->SecurityTradingStatus)))
			info->NullMap |= NULL_MAP_INDEX0;
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			ReadDecimal_Optional(&(info->HighLimitPx));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			ReadDecimal_Optional(&(info->LowLimitPx));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX3;
		else
			ReadDecimal_Optional(&(info->InitialMarginOnBuy));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX4;
		else
			ReadDecimal_Optional(&(info->InitialMarginOnSell));
		if(CheckProcessNullDecimal())
			info->NullMap |= NULL_MAP_INDEX5;
		else
			ReadDecimal_Optional(&(info->InitialMarginSyntetic));
		this->m_prevfortsSecurityStatusInfo = info;
		return info;
	}
	inline FortsHeartbeatInfo* DecodeFortsHeartbeat() {
		FortsHeartbeatInfo* info = GetFreeFortsHeartbeatInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		this->m_prevfortsHeartbeatInfo = info;
		return info;
	}
	inline FortsSequenceResetInfo* DecodeFortsSequenceReset() {
		FortsSequenceResetInfo* info = GetFreeFortsSequenceResetInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		info->NewSeqNo = ReadUInt32_Mandatory();
		this->m_prevfortsSequenceResetInfo = info;
		return info;
	}
	inline FortsTradingSessionStatusInfo* DecodeFortsTradingSessionStatus() {
		FortsTradingSessionStatusInfo* info = GetFreeFortsTradingSessionStatusInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		info->TradSesOpenTime = ReadUInt64_Mandatory();
		info->TradSesCloseTime = ReadUInt64_Mandatory();
		if(CheckProcessNullUInt64())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			info->TradSesIntermClearingStartTime = ReadUInt64_Optional();
		if(CheckProcessNullUInt64())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			info->TradSesIntermClearingEndTime = ReadUInt64_Optional();
		info->TradingSessionID = ReadUInt32_Mandatory();
		if(!ReadUInt32_Optional(&(info->ExchangeTradingSessionID)))
			info->NullMap |= NULL_MAP_INDEX2;
		info->TradSesStatus = ReadUInt32_Mandatory();
		ReadString_Mandatory(info->MarketSegmentID, &(info->MarketSegmentIDLength));
		if(!ReadInt32_Optional(&(info->TradSesEvent)))
			info->NullMap |= NULL_MAP_INDEX3;
		this->m_prevfortsTradingSessionStatusInfo = info;
		return info;
	}
	inline FortsNewsInfo* DecodeFortsNews() {
		FortsNewsInfo* info = GetFreeFortsNewsInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		if(!ReadUInt32_Optional(&(info->LastFragment)))
			info->NullMap |= NULL_MAP_INDEX0;
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			ReadString_Optional(info->NewsId, &(info->NewsIdLength));
		if(CheckProcessNullUInt64())
			info->NullMap |= NULL_MAP_INDEX2;
		else
			info->OrigTime = ReadUInt64_Optional();
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX3;
		else
			ReadString_Optional(info->LanguageCode, &(info->LanguageCodeLength));
		if(!ReadUInt32_Optional(&(info->Urgency)))
			info->NullMap |= NULL_MAP_INDEX4;
		ReadByteVector_Mandatory(info->Headline, &(info->HeadlineLength), 128);
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX5;
		else
			ReadString_Optional(info->MarketSegmentID, &(info->MarketSegmentIDLength));

		info->NewsTextCount = ReadUInt32_Mandatory_Predict1();
		FortsNewsNewsTextItemInfo* ntItemInfo = NULL;

		for(int i = 0; i < info->NewsTextCount; i++) {
			ntItemInfo = GetFreeFortsNewsNewsTextItemInfo();
			info->NewsText[i] = ntItemInfo;
			ReadByteVector_Mandatory(ntItemInfo->Text, &(ntItemInfo->TextLength), 128);
			this->m_prevfortsNewsNewsTextItemInfo = ntItemInfo;
		}

		this->m_prevfortsNewsInfo = info;
		return info;
	}
	inline FortsOrdersLogInfo* DecodeFortsOrdersLog() {
		FortsOrdersLogInfo* info = GetFreeFortsOrdersLogInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		info->LastFragment = ReadUInt32_Mandatory();

		info->MDEntriesCount = ReadUInt32_Mandatory_Predict1();
		FortsOrdersLogMDEntriesItemInfo* mdeItemInfo = NULL;

		for(int i = 0; i < info->MDEntriesCount; i++) {
			mdeItemInfo = GetFreeFortsOrdersLogMDEntriesItemInfo();
			info->MDEntries[i] = mdeItemInfo;
			mdeItemInfo->MDUpdateAction = ReadUInt32_Mandatory();
			ReadString_Mandatory(mdeItemInfo->MDEntryType, &(mdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				mdeItemInfo->MDEntryID = ReadInt64_Optional();
			if(CheckProcessNullUInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			else
				mdeItemInfo->SecurityID = ReadUInt64_Optional();
			if(!ReadUInt32_Optional(&(mdeItemInfo->RptSeq)))
				mdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			if(!ReadUInt32_Optional(&(mdeItemInfo->MDEntryDate)))
				mdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			mdeItemInfo->MDEntryTime = ReadUInt64_Mandatory();
			if(CheckProcessNullDecimal())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			else
				ReadDecimal_Optional(&(mdeItemInfo->MDEntryPx));
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX5;
			else
				mdeItemInfo->MDEntrySize = ReadInt64_Optional();
			if(CheckProcessNullDecimal())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX6;
			else
				ReadDecimal_Optional(&(mdeItemInfo->LastPx));
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX7;
			else
				mdeItemInfo->LastQty = ReadInt64_Optional();
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX8;
			else
				mdeItemInfo->TradeID = ReadInt64_Optional();
			if(!ReadUInt32_Optional(&(mdeItemInfo->ExchangeTradingSessionID)))
				mdeItemInfo->NullMap |= NULL_MAP_INDEX9;
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX10;
			else
				mdeItemInfo->MDFlags = ReadInt64_Optional();
			if(CheckProcessNullUInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX11;
			else
				mdeItemInfo->Revision = ReadUInt64_Optional();
			this->m_prevfortsOrdersLogMDEntriesItemInfo = mdeItemInfo;
		}

		this->m_prevfortsOrdersLogInfo = info;
		return info;
	}
	inline FortsOrdersBookInfo* DecodeFortsOrdersBook() {
		FortsOrdersBookInfo* info = GetFreeFortsOrdersBookInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		info->LastMsgSeqNumProcessed = ReadUInt32_Mandatory();
		if(!ReadUInt32_Optional(&(info->RptSeq)))
			info->NullMap |= NULL_MAP_INDEX0;
		info->LastFragment = ReadUInt32_Mandatory();
		info->RouteFirst = ReadUInt32_Mandatory();
		info->ExchangeTradingSessionID = ReadUInt32_Mandatory();
		if(CheckProcessNullUInt64())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			info->SecurityID = ReadUInt64_Optional();

		info->MDEntriesCount = ReadUInt32_Mandatory_Predict1();
		FortsOrdersBookMDEntriesItemInfo* mdeItemInfo = NULL;

		for(int i = 0; i < info->MDEntriesCount; i++) {
			mdeItemInfo = GetFreeFortsOrdersBookMDEntriesItemInfo();
			info->MDEntries[i] = mdeItemInfo;
			ReadString_Mandatory(mdeItemInfo->MDEntryType, &(mdeItemInfo->MDEntryTypeLength));
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX0;
			else
				mdeItemInfo->MDEntryID = ReadInt64_Optional();
			if(!ReadUInt32_Optional(&(mdeItemInfo->MDEntryDate)))
				mdeItemInfo->NullMap |= NULL_MAP_INDEX1;
			mdeItemInfo->MDEntryTime = ReadUInt64_Mandatory();
			if(CheckProcessNullDecimal())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX2;
			else
				ReadDecimal_Optional(&(mdeItemInfo->MDEntryPx));
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX3;
			else
				mdeItemInfo->MDEntrySize = ReadInt64_Optional();
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX4;
			else
				mdeItemInfo->TradeID = ReadInt64_Optional();
			if(CheckProcessNullInt64())
				mdeItemInfo->NullMap |= NULL_MAP_INDEX5;
			else
				mdeItemInfo->MDFlags = ReadInt64_Optional();
			this->m_prevfortsOrdersBookMDEntriesItemInfo = mdeItemInfo;
		}

		this->m_prevfortsOrdersBookInfo = info;
		return info;
	}
	inline FortsLogonInfo* DecodeFortsLogon() {
		FortsLogonInfo* info = GetFreeFortsLogonInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		this->m_prevfortsLogonInfo = info;
		return info;
	}
	inline FortsLogoutInfo* DecodeFortsLogout() {
		FortsLogoutInfo* info = GetFreeFortsLogoutInfo();
		info->PresenceMap = this->m_presenceMap;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		if(CheckProcessNullString())
			info->NullMap |= NULL_MAP_INDEX0;
		else
			ReadString_Optional(info->Text, &(info->TextLength));
		this->m_prevfortsLogoutInfo = info;
		return info;
	}
	inline FortsSnapshotInfo* GetFortsSnapshotInfoDefaultSnapshotMessage() {
		FortsSnapshotInfo *info = GetFreeFortsSnapshotInfo();
		info->PresenceMap = this->m_presenceMap;
		info->TemplateId = this->m_templateId;

		SkipToNextField(); // MsgSeqNum
		SkipToNextField(); // SendingTime
		if(!ReadUInt32_Optional(&(info->LastFragment)))
			info->NullMap |= NULL_MAP_INDEX0;
		info->RptSeq = ReadUInt32_Mandatory();
		SkipToNextField(); // TotNumReports
		info->LastMsgSeqNumProcessed = ReadUInt32_Mandatory();
		if(CheckProcessNullUInt64())
			info->NullMap |= NULL_MAP_INDEX1;
		else
			info->SecurityID = ReadUInt64_Optional();
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

