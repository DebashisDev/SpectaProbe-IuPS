/*
 * IUPSGlobal.cpp
 *
 *  Created on: 14-Jul-2016
 *      Author: deb
 */

#include "IUPSGlobal.h"

namespace IUPSFlushRepository {

		std::map<uint32_t, string> iupsFlushMap_sm_0_t_0;
		std::map<uint32_t, string> iupsFlushMap_sm_0_t_1;
		std::map<uint32_t, string> iupsFlushMap_sm_0_t_2;
		std::map<uint32_t, string> iupsFlushMap_sm_0_t_3;
		std::map<uint32_t, string> iupsFlushMap_sm_0_t_4;
		std::map<uint32_t, string> iupsFlushMap_sm_0_t_5;
		std::map<uint32_t, string> iupsFlushMap_sm_0_t_6;
		std::map<uint32_t, string> iupsFlushMap_sm_0_t_7;
		std::map<uint32_t, string> iupsFlushMap_sm_0_t_8;
		std::map<uint32_t, string> iupsFlushMap_sm_0_t_9;

		int iupsFlushMap_sm_0_t_0_cnt = 0;
		int iupsFlushMap_sm_0_t_1_cnt = 0;
		int iupsFlushMap_sm_0_t_2_cnt = 0;
		int iupsFlushMap_sm_0_t_3_cnt = 0;
		int iupsFlushMap_sm_0_t_4_cnt = 0;
		int iupsFlushMap_sm_0_t_5_cnt = 0;
		int iupsFlushMap_sm_0_t_6_cnt = 0;
		int iupsFlushMap_sm_0_t_7_cnt = 0;
		int iupsFlushMap_sm_0_t_8_cnt = 0;
		int iupsFlushMap_sm_0_t_9_cnt = 0;
}

namespace IUPSZmqFlushStore {

	int zmq_flush_t_index = 0;

	std::string zmq_flush_map_iups_t_0[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE];
	std::string zmq_flush_map_iups_t_1[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE];
	std::string zmq_flush_map_iups_t_2[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE];
	std::string zmq_flush_map_iups_t_3[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE];
	std::string zmq_flush_map_iups_t_4[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE];
	std::string zmq_flush_map_iups_t_5[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE];
	std::string zmq_flush_map_iups_t_6[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE];
	std::string zmq_flush_map_iups_t_7[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE];
	std::string zmq_flush_map_iups_t_8[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE];
	std::string zmq_flush_map_iups_t_9[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE];

	int zmq_flush_map_iups_t_0_cnt = 0;
	int zmq_flush_map_iups_t_1_cnt = 0;
	int zmq_flush_map_iups_t_2_cnt = 0;
	int zmq_flush_map_iups_t_3_cnt = 0;
	int zmq_flush_map_iups_t_4_cnt = 0;
	int zmq_flush_map_iups_t_5_cnt = 0;
	int zmq_flush_map_iups_t_6_cnt = 0;
	int zmq_flush_map_iups_t_7_cnt = 0;
	int zmq_flush_map_iups_t_8_cnt = 0;
	int zmq_flush_map_iups_t_9_cnt = 0;
}

namespace IUPSGlobal {

	int pcap_counter = 0;
	std::map<std::string, std::string> TMSI_IMSI_MAP;
	std::map<std::string, std::string> IMSI_TMSI_MAP;

	int IMSI_TMSI_MAP_SIZE = 0;
	int TMSI_IMSI_MAP_SIZE = 0;

const char *IUPS_MSG_DIR[3]={
		"SGSN->RNC",
		"RNC->SGSN"
};

























const char *ID_Val_String[285]={
		"AreaIdentity",
		"NA",
		"NA",
		"CN-DomainIndicator",
		"Cause",
		"ChosenEncryptionAlgorithm",
		"ChosenIntegrityProtectionAlgorithm",
		"ClassmarkInformation2",
		"ClassmarkInformation3",
		"CriticalityDiagnostics",
		"DL-GTP-PDU-SequenceNumber",
		"EncryptionInformation",
		"IntegrityProtectionInformation",
		"IuTransportAssociation",
		"L3-Information",
		"LAI",
		"NAS-PDU",
		"NonSearchingIndication",
		"NumberOfSteps",
		"OMC-ID",
		"OldBSS-ToNewBSS-Information",
		"PagingAreaID",
		"PagingCause",
		"PermanentNAS-UE-ID",
		"RAB-ContextItem",
		"RAB-ContextList",
		"RAB-DataForwardingItem",
		"RAB-DataForwardingItem-SRNS-CtxReq",
		"RAB-DataForwardingList",
		"RAB-DataForwardingList-SRNS-CtxReq",
		"RAB-DataVolumeReportItem",
		"RAB-DataVolumeReportList",
		"RAB-DataVolumeReportRequestItem",
		"RAB-DataVolumeReportRequestList",
		"RAB-FailedItem",
		"RAB-FailedList",
		"RAB-ID",
		"RAB-QueuedItem",
		"RAB-QueuedList",
		"RAB-ReleaseFailedList",
		"RAB-ReleaseItem",
		"RAB-ReleaseList",
		"RAB-ReleasedItem",
		"RAB-ReleasedList",
		"RAB-ReleasedList-IuRelComp",
		"RAB-RelocationReleaseItem",
		"RAB-RelocationReleaseList",
		"RAB-SetupItem-RelocReq",
		"RAB-SetupItem-RelocReqAck",
		"RAB-SetupList-RelocReq",
		"RAB-SetupList-RelocReqAck",
		"RAB-SetupOrModifiedItem",
		"RAB-SetupOrModifiedList",
		"RAB-SetupOrModifyItem",
		"RAB-SetupOrModifyList",
		"RAC",
		"RelocationType",
		"RequestType",
		"SAI",
		"SAPI",
		"SourceID",
		"Source-ToTarget-TransparentContainer",
		"TargetID",
		"Target-ToSource-TransparentContainer",
		"TemporaryUE-ID",
		"TraceReference",
		"TraceType",
		"TransportLayerAddress",
		"TriggerID",
		"UE-ID",
		"UL-GTP-PDU-SequenceNumber",
		"RAB-FailedtoReportItem",
		"RAB-FailedtoReportList",
		"NA",
		"NA",
		"KeyStatus",
		"DRX-CycleLengthCoefficient",
		"IuSigConIdList",
		"IuSigConIdItem",
		"IuSigConId",
		"DirectTransferInformationItem-RANAP-RelocInf",
		"DirectTransferInformationList-RANAP-RelocInf",
		"RAB-ContextItem-RANAP-RelocInf",
		"RAB-ContextList-RANAP-RelocInf",
		"RAB-ContextFailedtoTransferItem",
		"RAB-ContextFailedtoTransferList",
		"GlobalRNC-ID",
		"RAB-ReleasedItem-IuRelComp",
		"MessageStructure",
		"Alt-RAB-Parameters",
		"Ass-RAB-Parameters",
		"RAB-ModifyList",
		"RAB-ModifyItem",
		"TypeOfError",
		"BroadcastAssistanceDataDecipheringKeys",
		"LocationRelatedDataRequestType",
		"GlobalCN-ID",
		"LastKnownServiceArea",
		"SRB-TrCH-Mapping",
		"InterSystemInformation-TransparentContainer",
		"NewBSS-To-OldBSS-Information",
		""
		""
		"SourceRNC-PDCP-context-info",
		"InformationTransferID",
		"SNA-Access-Information",
		"ProvidedData",
		"GERAN-BSC-Container",
		"GERAN-Classmark",
		"GERAN-Iumode-RAB-Failed-RABAssgntResponse-Item",
		"GERAN-Iumode-RAB-FailedList-RABAssgntResponse",
		"VerticalAccuracyCode",
		"ResponseTime",
		"PositioningPriority",
		"ClientType",
		"LocationRelatedDataRequestTypeSpecificToGERANIuMode",
		"SignallingIndication",
		"hS-DSCH-MAC-d-Flow-ID",
		"UESBI-Iu",
		"PositionData",
		"PositionDataSpecificToGERANIuMode",
		"CellLoadInformationGroup",
		"AccuracyFulfilmentIndicator",
		"InformationTransferType",
		"TraceRecordingSessionInformation",
		"TracePropagationParameters",
		"InterSystemInformationTransferType",
		"SelectedPLMN-ID",
		"RedirectionCompleted",
		"RedirectionIndication",
		"NAS-SequenceNumber",
		"RejectCauseValue",
		"APN",
		"CNMBMSLinkingInformation",
		"DeltaRAListofIdleModeUEs",
		"FrequenceLayerConvergenceFlag",
		"InformationExchangeID",
		"InformationExchangeType",
		"InformationRequested",
		"InformationRequestType",
		"IPMulticastAddress",
		"JoinedMBMSBearerServicesList",
		"LeftMBMSBearerServicesList",
		"MBMSBearerServiceType",
		"MBMSCNDe-Registration",
		"MBMSServiceArea",
		"MBMSSessionDuration",
		"MBMSSessionIdentity",
		"PDP-TypeInformation",
		"RAB-Parameters",
		"RAListofIdleModeUEs",
		"MBMSRegistrationRequestType",
		"SessionUpdateID",
		"TMGI",
		"TransportLayerInformation",
		"UnsuccessfulLinkingList",
		"MBMSLinkingInformation",
		"MBMSSessionRepetitionNumber",
		"AlternativeRABConfiguration",
		"AlternativeRABConfigurationRequest",
		"E-DCH-MAC-d-Flow-ID",
		"SourceBSS-ToTargetBSS-TransparentContainer",
		"TargetBSS-ToSourceBSS-TransparentContainer",
		"TimeToMBMSDataTransfer",
		"IncludeVelocity",
		"VelocityEstimate",
		"RedirectAttemptFlag",
		"RAT-Type",
		"PeriodicLocationInfo",
		"MBMSCountingInformation",
		"170-not-to-be-used-for-IE-ids",
		"ExtendedRNC-ID",
		"Alt-RAB-Parameter-ExtendedGuaranteedBitrateInf",
		"Alt-RAB-Parameter-ExtendedMaxBitrateInf",
		"Ass-RAB-Parameter-ExtendedGuaranteedBitrateList",
		"Ass-RAB-Parameter-ExtendedMaxBitrateList",
		"RAB-Parameter-ExtendedGuaranteedBitrateList",
		"RAB-Parameter-ExtendedMaxBitrateList",
		"Requested-RAB-Parameter-ExtendedMaxBitrateList",
		"Requested-RAB-Parameter-ExtendedGuaranteedBitrateList",
		"LAofIdleModeUEs",
		"newLAListofIdleModeUEs",
		"LAListwithNoIdleModeUEsAnyMore",
		"183-not-to-be-used-for-IE-ids",
		"GANSS-PositioningDataSet",
		"RequestedGANSSAssistanceData",
		"BroadcastGANSSAssistanceDataDecipheringKeys",
		"d-RNTI-for-NoIuCSUP",
		"RAB-SetupList-EnhancedRelocCompleteReq",
		"RAB-SetupItem-EnhancedRelocCompleteReq",
		"RAB-SetupList-EnhancedRelocCompleteRes",
		"RAB-SetupItem-EnhancedRelocCompleteRes",
		"RAB-SetupList-EnhRelocInfoReq",
		"RAB-SetupItem-EnhRelocInfoReq",
		"RAB-SetupList-EnhRelocInfoRes",
		"RAB-SetupItem-EnhRelocInfoRes",
		"OldIuSigConId",
		"RAB-FailedList-EnhRelocInfoRes",
		"RAB-FailedItem-EnhRelocInfoRes",
		"Global-ENB-ID",
		"UE-History-Information",
		"MBMSSynchronisationInformation",
		"SubscriberProfileIDforRFP",
		"CSG-Id",
		"OldIuSigConIdCS",
		"OldIuSigConIdPS",
		"GlobalCN-IDCS",
		"GlobalCN-IDPS",
		"SourceExtendedRNC-ID",
		"RAB-ToBeReleasedItem-EnhancedRelocCompleteRes",
		"RAB-ToBeReleasedList-EnhancedRelocCompleteRes",
		"SourceRNC-ID",
		"Relocation-TargetRNC-ID",
		"Relocation-TargetExtendedRNC-ID",
		"Alt-RAB-Parameter-SupportedGuaranteedBitrateInf",
		"Alt-RAB-Parameter-SupportedMaxBitrateInf",
		"Ass-RAB-Parameter-SupportedGuaranteedBitrateList",
		"Ass-RAB-Parameter-SupportedMaxBitrateList",
		"RAB-Parameter-SupportedGuaranteedBitrateList",
		"RAB-Parameter-SupportedMaxBitrateList",
		"Requested-RAB-Parameter-SupportedMaxBitrateList",
		"Requested-RAB-Parameter-SupportedGuaranteedBitrateList",
		"Relocation-SourceRNC-ID",
		"Relocation-SourceExtendedRNC-ID",
		"EncryptionKey",
		"IntegrityProtectionKey",
		"SRVCC-HO-Indication",
		"SRVCC-Information",
		"SRVCC-Operation-Possible",
		"CSG-Id-List",
		"PSRABtobeReplaced",
		"E-UTRAN-Service-Handover",
		"NA",
		"UE-AggregateMaximumBitRate",
		"CSG-Membership-Status",
		"Cell-Access-Mode",
		"IP-Source-Address",
		"CSFB-Information",
		"PDP-TypeInformation-extension",
		"MSISDN",
		"Offload-RAB-Parameters",
		"LGW-TransportLayerAddress",
		"Correlation-ID",
		"IRAT-Measurement-Configuration",
		"MDT-Configuration",
		"Priority-Class-Indicator",
		"NA",
		"RNSAPRelocationParameters",
		"RABParametersList",
		"Management-Based-MDT-Allowed",
		"HigherBitratesThan16MbpsFlag",
		"Trace-Collection-Entity-IP-Addess",
		"End-Of-CSFB",
		"Time-UE-StayedInCell-EnhancedGranularity",
		"Out-Of-UTRAN",
		"TraceRecordingSessionReference",
		"IMSI",
		"HO-Cause",
		"VoiceSupportMatchIndicator",
		"RSRVCC-HO-Indication",
		"RSRVCC-Information",
		"AnchorPLMN-ID",
		"Tunnel-Information-for-BBF",
		"Management-Based-MDT-PLMN-List",
		"SignallingBasedMDTPLMNList",
		"M4Report",
		"M5Report",
		"M6Report",
		"M7Report",
		"TimingDifferenceULDL",
		"Serving-Cell-Identifier",
		"EARFCN-Extended",
		"RSRVCC-Operation-Possible",
		"SIPTO-LGW-TransportLayerAddress",
		"SIPTO-Correlation-ID",
		"LHN-ID",
		"Session-Re-establishment-Indicator",
		"LastE-UTRANPLMNIdentity",
		"RSRQ-Type",
		"RSRQ-Extension"
	};


















	const char *Procedure_Val_String[48]={
		"RAB-Assignment",
		"Iu-Release",
		"RelocationPreparation",
		"RelocationResourceAllocation",
		"RelocationCancel",
		"SRNS-ContextTransfer",
		"SecurityModeControl",
		"DataVolumeReport",
		"NA",
		"Reset",
		"RAB-ReleaseRequest",
		"Iu-ReleaseRequest",
		"RelocationDetect",
		"RelocationComplete",
		"Paging",
		"CommonID",
		"CN-InvokeTrace",
		"LocationReportingControl",
		"LocationReport",
		"InitialUE-Message",
		"DirectTransfer",
		"OverloadControl",
		"ErrorIndication",
		"SRNS-DataForward",
		"ForwardSRNS-Context",
		"privateMessage",
		"CN-DeactivateTrace",
		"ResetResource",
		"RANAP-Relocation",
		"RAB-ModifyRequest",
		"LocationRelatedData",
		"InformationTransfer",
		"UESpecificInformation",
		"UplinkInformationExchange",
		"DirectInformationTransfer",
		"MBMSSessionStart",
		"MBMSSessionUpdate",
		"MBMSSessionStop",
		"MBMSUELinking",
		"MBMSRegistration",
		"MBMSCNDe-Registration-Procedure",
		"MBMSRABEstablishmentIndication",
		"MBMSRABRelease",
		"enhancedRelocationComplete",
		"enhancedRelocationCompleteConfirm",
		"RANAPenhancedRelocation",
		"SRVCCPreparation",
		"UeRadioCapabilityMatch"
	};


















































	const char *Ranap_ID_Val_String[280]={
		"AreaIdentity",
		"NA",
		"NA",
		"CN-DomainIndicator",
		"Cause",
		"ChosenEncryptionAlgorithm",
		"ChosenIntegrityProtectionAlgorithm",
		"ClassmarkInformation2",
		"ClassmarkInformation3",
		"CriticalityDiagnostics",
		"DL-GTP-PDU-SequenceNumber",
		"EncryptionInformation",
		"IntegrityProtectionInformation",
		"IuTransportAssociation",
		"L3-Information",
		"LAI",
		"NAS-PDU",
		"NonSearchingIndication",
		"NumberOfSteps",
		"OMC-ID",
		"OldBSS-ToNewBSS-Information",
		"PagingAreaID",
		"PagingCause",
		"PermanentNAS-UE-ID",
		"RAB-ContextItem",
		"RAB-ContextList",
		"RAB-DataForwardingItem",
		"RAB-DataForwardingItem-SRNS-CtxReq",
		"RAB-DataForwardingList",
		"RAB-DataForwardingList-SRNS-CtxReq",
		"RAB-DataVolumeReportItem",
		"RAB-DataVolumeReportList",
		"RAB-DataVolumeReportRequestItem",
		"RAB-DataVolumeReportRequestList",
		"RAB-FailedItem",
		"RAB-FailedList",
		"RAB-ID",
		"RAB-QueuedItem",
		"RAB-QueuedList",
		"RAB-ReleaseFailedList",
		"RAB-ReleaseItem",
		"RAB-ReleaseList",
		"RAB-ReleasedItem",
		"RAB-ReleasedList",
		"RAB-ReleasedList-IuRelComp",
		"RAB-RelocationReleaseItem",
		"RAB-RelocationReleaseList",
		"RAB-SetupItem-RelocReq",
		"RAB-SetupItem-RelocReqAck",
		"RAB-SetupList-RelocReq",
		"RAB-SetupList-RelocReqAck",
		"RAB-SetupOrModifiedItem",
		"RAB-SetupOrModifiedList",
		"RAB-SetupOrModifyItem",
		"RAB-SetupOrModifyList",
		"RAC",
		"RelocationType",
		"RequestType",
		"SAI",
		"SAPI",
		"SourceID",
		"Source-ToTarget-TransparentContainer",
		"TargetID",
		"Target-ToSource-TransparentContainer",
		"TemporaryUE-ID",
		"TraceReference",
		"TraceType",
		"TransportLayerAddress",
		"TriggerID",
		"UE-ID",
		"UL-GTP-PDU-SequenceNumber",
		"RAB-FailedtoReportItem",
		"RAB-FailedtoReportList",
		"NA",
		"NA",
		"KeyStatus",
		"DRX-CycleLengthCoefficient",
		"IuSigConIdList",
		"IuSigConIdItem",
		"IuSigConId",
		"DirectTransferInformationItem-RANAP-RelocInf",
		"DirectTransferInformationList-RANAP-RelocInf",
		"RAB-ContextItem-RANAP-RelocInf",
		"RAB-ContextList-RANAP-RelocInf",
		"RAB-ContextFailedtoTransferItem",
		"RAB-ContextFailedtoTransferList",
		"GlobalRNC-ID",
		"RAB-ReleasedItem-IuRelComp",
		"MessageStructure",
		"Alt-RAB-Parameters",
		"Ass-RAB-Parameters",
		"RAB-ModifyList",
		"RAB-ModifyItem",
		"TypeOfError",
		"BroadcastAssistanceDataDecipheringKeys",
		"LocationRelatedDataRequestType",
		"GlobalCN-ID",
		"LastKnownServiceArea",
		"SRB-TrCH-Mapping",
		"InterSystemInformation-TransparentContainer",
		"NewBSS-To-OldBSS-Information",
		""
		""
		"SourceRNC-PDCP-context-info",
		"InformationTransferID",
		"SNA-Access-Information",
		"ProvidedData",
		"GERAN-BSC-Container",
		"GERAN-Classmark",
		"GERAN-Iumode-RAB-Failed-RABAssgntResponse-Item",
		"GERAN-Iumode-RAB-FailedList-RABAssgntResponse",
		"VerticalAccuracyCode",
		"ResponseTime",
		"PositioningPriority",
		"ClientType",
		"LocationRelatedDataRequestTypeSpecificToGERANIuMode",
		"SignallingIndication",
		"hS-DSCH-MAC-d-Flow-ID",
		"UESBI-Iu",
		"PositionData",
		"PositionDataSpecificToGERANIuMode",
		"CellLoadInformationGroup",
		"AccuracyFulfilmentIndicator",
		"InformationTransferType",
		"TraceRecordingSessionInformation",
		"TracePropagationParameters",
		"InterSystemInformationTransferType",
		"SelectedPLMN-ID",
		"RedirectionCompleted",
		"RedirectionIndication",
		"NAS-SequenceNumber",
		"RejectCauseValue",
		"APN",
		"CNMBMSLinkingInformation",
		"DeltaRAListofIdleModeUEs",
		"FrequenceLayerConvergenceFlag",
		"InformationExchangeID",
		"InformationExchangeType",
		"InformationRequested",
		"InformationRequestType",
		"IPMulticastAddress",
		"JoinedMBMSBearerServicesList",
		"LeftMBMSBearerServicesList",
		"MBMSBearerServiceType",
		"MBMSCNDe-Registration",
		"MBMSServiceArea",
		"MBMSSessionDuration",
		"MBMSSessionIdentity",
		"PDP-TypeInformation",
		"RAB-Parameters",
		"RAListofIdleModeUEs",
		"MBMSRegistrationRequestType",
		"SessionUpdateID",
		"TMGI",
		"TransportLayerInformation",
		"UnsuccessfulLinkingList",
		"MBMSLinkingInformation",
		"MBMSSessionRepetitionNumber",
		"AlternativeRABConfiguration",
		"AlternativeRABConfigurationRequest",
		"E-DCH-MAC-d-Flow-ID",
		"SourceBSS-ToTargetBSS-TransparentContainer",
		"TargetBSS-ToSourceBSS-TransparentContainer",
		"TimeToMBMSDataTransfer",
		"IncludeVelocity",
		"VelocityEstimate",
		"RedirectAttemptFlag",
		"RAT-Type",
		"PeriodicLocationInfo",
		"MBMSCountingInformation",
		"170-not-to-be-used-for-IE-ids",
		"ExtendedRNC-ID",
		"Alt-RAB-Parameter-ExtendedGuaranteedBitrateInf",
		"Alt-RAB-Parameter-ExtendedMaxBitrateInf",
		"Ass-RAB-Parameter-ExtendedGuaranteedBitrateList",
		"Ass-RAB-Parameter-ExtendedMaxBitrateList",
		"RAB-Parameter-ExtendedGuaranteedBitrateList",
		"RAB-Parameter-ExtendedMaxBitrateList",
		"Requested-RAB-Parameter-ExtendedMaxBitrateList",
		"Requested-RAB-Parameter-ExtendedGuaranteedBitrateList",
		"LAofIdleModeUEs",
		"newLAListofIdleModeUEs",
		"LAListwithNoIdleModeUEsAnyMore",
		"183-not-to-be-used-for-IE-ids",
		"GANSS-PositioningDataSet",
		"RequestedGANSSAssistanceData",
		"BroadcastGANSSAssistanceDataDecipheringKeys",
		"d-RNTI-for-NoIuCSUP",
		"RAB-SetupList-EnhancedRelocCompleteReq",
		"RAB-SetupItem-EnhancedRelocCompleteReq",
		"RAB-SetupList-EnhancedRelocCompleteRes",
		"RAB-SetupItem-EnhancedRelocCompleteRes",
		"RAB-SetupList-EnhRelocInfoReq",
		"RAB-SetupItem-EnhRelocInfoReq",
		"RAB-SetupList-EnhRelocInfoRes",
		"RAB-SetupItem-EnhRelocInfoRes",
		"OldIuSigConId",
		"RAB-FailedList-EnhRelocInfoRes",
		"RAB-FailedItem-EnhRelocInfoRes",
		"Global-ENB-ID",
		"UE-History-Information",
		"MBMSSynchronisationInformation",
		"SubscriberProfileIDforRFP",
		"CSG-Id",
		"OldIuSigConIdCS",
		"OldIuSigConIdPS",
		"GlobalCN-IDCS",
		"GlobalCN-IDPS",
		"SourceExtendedRNC-ID",
		"RAB-ToBeReleasedItem-EnhancedRelocCompleteRes",
		"RAB-ToBeReleasedList-EnhancedRelocCompleteRes",
		"SourceRNC-ID",
		"Relocation-TargetRNC-ID",
		"Relocation-TargetExtendedRNC-ID",
		"Alt-RAB-Parameter-SupportedGuaranteedBitrateInf",
		"Alt-RAB-Parameter-SupportedMaxBitrateInf",
		"Ass-RAB-Parameter-SupportedGuaranteedBitrateList",
		"Ass-RAB-Parameter-SupportedMaxBitrateList",
		"RAB-Parameter-SupportedGuaranteedBitrateList",
		"RAB-Parameter-SupportedMaxBitrateList",
		"Requested-RAB-Parameter-SupportedMaxBitrateList",
		"Requested-RAB-Parameter-SupportedGuaranteedBitrateList",
		"Relocation-SourceRNC-ID",
		"Relocation-SourceExtendedRNC-ID",
		"EncryptionKey",
		"IntegrityProtectionKey",
		"SRVCC-HO-Indication",
		"SRVCC-Information",
		"SRVCC-Operation-Possible",
		"CSG-Id-List",
		"PSRABtobeReplaced",
		"E-UTRAN-Service-Handover",
		"NA",
		"UE-AggregateMaximumBitRate",
		"CSG-Membership-Status",
		"Cell-Access-Mode",
		"IP-Source-Address",
		"CSFB-Information",
		"PDP-TypeInformation-extension",
		"MSISDN",
		"Offload-RAB-Parameters",
		"LGW-TransportLayerAddress",
		"Correlation-ID",
		"IRAT-Measurement-Configuration",
		"MDT-Configuration",
		"Priority-Class-Indicator",
		"NA",
		"RNSAPRelocationParameters",
		"RABParametersList",
		"Management-Based-MDT-Allowed",
		"HigherBitratesThan16MbpsFlag",
		"Trace-Collection-Entity-IP-Addess",
		"End-Of-CSFB",
		"Time-UE-StayedInCell-EnhancedGranularity",
		"Out-Of-UTRAN",
		"TraceRecordingSessionReference",
		"IMSI",
		"HO-Cause",
		"VoiceSupportMatchIndicator",
		"RSRVCC-HO-Indication",
		"RSRVCC-Information",
		"AnchorPLMN-ID",
		"Tunnel-Information-for-BBF",
		"Management-Based-MDT-PLMN-List",
		"SignallingBasedMDTPLMNList",
		"M4Report",
		"M5Report",
		"M6Report",
		"M7Report",
		"TimingDifferenceULDL",
		"Serving-Cell-Identifier",
		"EARFCN-Extended",
		"RSRVCC-Operation-Possible",
		"SIPTO-LGW-TransportLayerAddress",
		"SIPTO-Correlation-ID",
		"LHN-ID",
		"Session-Re-establishment-Indicator",
		"LastE-UTRANPLMNIdentity",
		"RSRQ-Type",
		"RSRQ-Extension"
	};

	const char *Attach_Type_Val_String[6]={
		"NA",
		"GPRS attach",
		"Not used (earlier versions of the protocol",
		"Combined GPRS/IMSI attach",
		"Emergency attach"
	};

	const char *Attach_Result_Val_String[5]={
		"NA",
		"GPRS only attached",
		"Not used (earlier versions of the protocol",
		"Combined GPRS/IMSI attached"
	};

	const char *Detach_Type_MS_NW_Val_String[5]={
		"NA",
		"GPRS Detach",
		"IMSI Detach",
		"Combined GPRS/IMSI detach"
	};

	const char *Detach_Type_NW_MS_Val_String[5]={
		"NA",
		"Re-attach required",
		"Re-attach not required",
		"IMSI detach (after VLR failure)"
	};

	const char *Detach_Power_Off_Type_MS_NW_Val_String[5]={
		"Normal detach",
		"Power switched off"
	};

	const char *RA_Update_Type_Val_String[5]={
		"RA updating",
		"Combined RA/LA updating",
		"Combined RA/LA updating with IMSI attach",
		"Periodic updating"
	};

	const char *Mobile_Id_Type_Val_String[7]={
		"NA",
		"IMSI",
		"IMEI",
		"IMEISV",
		"TMSI/P-TMSI/M-TMSI",
		"TMGI and optional MBMS Session Identity",
		"No Identity"
	};

	const char *IMEISV_Type_Val_String[3]={
		"IMEISV not requested",
		"IMEISV requested"
	};

	const char *PD_Val_String[15]={
		"PD_Group_call_control",
		"PD_Broadcast_call_control",
		"PD_EPS_session_management_messages",
		"PD_Call_control_Call_related_SS_messages",
		"PD_GPRS_Transparent_Transport_Protocol_GTTP",
		"PD_Mobility_management_messages",
		"PD_Radio_resources_management_messages",
		"PD_EPS_mobility_management_messages",
		"PD_GPRS_mobility_management_messages",
		"PD_SMS_messages",
		"PD_GPRS_session_management_messages",
		"PD_Non_call_related_SS_messages",
		"PD_Location_services",
		"PD_Reserved_for_extension_of_the_PD_to_one_octet_length",
		"PD_Used_by_tests_procedures"
	};

	const char *MM_SM_Message_Id_Val_String[] = {
		"NA",																	//0x00 00
		"MM_Attach_request",												//0x01 01
		"MM_Attach_accept",													//0x02 02
		"MM_Attach_complete",												//0x03 03
		"MM_Attach_reject",													//0x04 04
		"MM_Detach_request",												//0x05 05
		"MM_Detach_accept",													//0x06 06
		"NA",																	//     07  Not defined in specs
		"MM_Routing_area_update_request",									//0x08 08
		"MM_Routing_area_update_accept",									//0x09 09
		"MM_Routing_area_update_complete",									//0x0a 10
		"MM_Routing_area_update_reject",									//0x0b 11
		"MM_Service_Request",												//0x0c 12
		"MM_Service_Accept",												//0x0d 13
		"MM_Service_Reject",												//0x0e 14
		"NA",																	//     15, not define in specs
		"MM_P_TMSI_reallocation_command",									//0x10 16
		"MM_P_TMSI_reallocation_complete",									//0x11 17
		"MM_Authentication_and_ciphering_req",								//0x12 18
		"MM_Authentication_and_ciphering_resp",								//0x13 19
		"MM_Authentication_and_ciphering_rej",								//0x14 20
		"MM_Identity_request",												//0x15 21, moved up in sequence
		"MM_Identity_response",												//0x16 22, moved up in sequence
		"NA",																	//0x17 23, not defined in specs
		"NA",																	//0x18 24, not defined in specs
		"NA",																	//0x19 25, not defined in specs
		"NA",																	//0x1a 26, not defined in specs
		"MM_Authentication_and_ciphering_failure",							//0x1b 27
		"NA",																	//0x1c 28, not defined in specs
		"NA",																	//0x1d 29, not defined in specs
		"NA",																	//0x1e 30, not defined in specs
		"NA",																	//0x1f 31, not defined in specs
		"MM_GMM_status",													//0x20 32
		"MM_GMM_information",												//0x21 33
		"NA",																	//     34
		"NA",																	//     35
		"NA",																	//     36
		"NA",																	//     37
		"NA",																	//     38
		"NA",																	//     39
		"NA",																	//     40
		"NA",																	//     41
		"NA",																	//     42
		"NA",																	//     43
		"NA",																	//     44
		"NA",																	//     45
		"NA",																	//     46
		"NA",																	//     47
		"NA",																	//     48
		"NA",																	//     49
		"NA",																	//     50
		"NA",																	//     51
		"NA",																	//     52
		"NA",																	//     53
		"NA",																	//     54
		"NA",																	//     55
		"NA",																	//     56
		"NA",																	//     57
		"NA",																	//     58
		"NA",																	//     59
		"NA",																	//     60
		"NA",																	//     61
		"NA",																	//     62
		"NA",																	//     63
		"NA",																	//     64
		"SM_Activate_PDP_context_request",									//0x41 65
		"SM_Activate_PDP_context_accept",									//0x42 66
		"SM_Activate_PDP_context_reject",									//0x43 67
		"SM_Request_PDP_context_activation",								//0x44 68
		"SM_Request_PDP_context_activation_rej",							//0x45 69
		"SM_Deactivate_PDP_context_request",								//0x46 70
		"SM_Deactivate_PDP_context_accept",									//0x47 71
		"SM_Modify_PDP_context_request_Network_to_MS_direction",			//0x48 72
		"SM_Modify_PDP_context_accept_MS_to_network_direction",				//0x49 73
		"SM_Modify_PDP_context_request_MS_to_network_direction",			//0x4a 74
		"SM_Modify_PDP_context_accept_Network_to_MS_direction",				//0x4b 75
		"SM_Modify_PDP_context_reject",										//0x4c 76
		"SM_Activate_secondary_PDP_context_request",						//0x4d 77
		"SM_Activate_secondary_PDP_context_accept",							//0x4e 78
		"SM_Activate_secondary_PDP_context_reject",							//0x4f 79
		"SM_Reserved_was_allocated_in_earlier_phases_of_the_protocol",		//0x50 80
		"SM_Reserved_was_allocated_in_earlier_phases_of_the_protocol",		//0x51 81
		"SM_Reserved_was_allocated_in_earlier_phases_of_the_protocol",		//0x52 82
		"SM_Reserved_was_allocated_in_earlier_phases_of_the_protocol",		//0x53 83
		"SM_Reserved_was_allocated_in_earlier_phases_of_the_protocol",		//0x54 84
		"SM_SM_Status",														//0x55 85
		"SM_Activate_MBMS_Context_Request",									//0x56 86
		"SM_Activate_MBMS_Context_Accept",									//0x57 87
		"SM_Activate_MBMS_Context_Reject",									//0x58 88
		"SM_Request_MBMS_Context_Activation",								//0x59 89
		"SM_Request_MBMS_Context_Activation_Reject",						//0x5a 90
		"SM_Request_Secondary_PDP_Context_Activation",						//0x5b 91
		"SM_Request_Secondary_PDP_Context_Activation_Reject",				//0x5c 92
		"SM_Notification"													//0x5d 93
	};


	const char *MM_Cause_Codes_Val_String[] = {
			"0x00",
			"0x01",
			"IMSI unknown in HLR [0x02]",
			"Illegal MS [0x03]",
			"0x04",
			"IMEI not accepted [0x05]",
			"Illegal ME [0x06]",
			"GPRS services not allowed [0x07]",
			"GPRS services and non-GPRS services not allowed [0x08]",
			"MS identity cannot be derived by the network [0x09]",
			"Implicitly detached [0x0a]",
			"PLMN not allowed [0x0b]",
			"Location Area not allowed [0x0c]",
			"Roaming not allowed in this location area [0x0d]",
			"GPRS services not allowed in this PLMN [0x0e]",
			"No Suitable Cells In Location Area [0x0f]",
			"MSC temporarily not reachable [0x10]",
			"Network failure [0x11]",
			"0x12",
			"0x13",
			"MAC failure [0x14]",
			"Synch failure [0x15]",
			"Congestion [0x16]",
			"GSM authentication unacceptable [0x17]",
			"0x18",
			"Not authorized for this CSG [0x19]",
			"0x1a",
			"0x1b",
			"SMS provided via GPRS in this routing area [0x1c]",
			"0x1d",
			"0x1e",
			"0x1f",
			"0x20",
			"0x21",
			"0x22",
			"0x23",
			"0x24",
			"0x25",
			"0x26",
			"0x27",
			"No PDP context activated [0x28]",
			"0x29",
			"0x2a",
			"0x2b",
			"0x2c",
			"0x2d",
			"0x2e",
			"0x2f",
			"Retry upon entry into a new cell 0x30 [0x30]",
			"Retry upon entry into a new cell 0x31 [0x31]",
			"Retry upon entry into a new cell 0x32 [0x32]",
			"Retry upon entry into a new cell 0x33 [0x33]",
			"Retry upon entry into a new cell 0x34 [0x34]",
			"Retry upon entry into a new cell 0x35 [0x35]",
			"Retry upon entry into a new cell 0x36 [0x36]",
			"Retry upon entry into a new cell 0x37 [0x37]",
			"Retry upon entry into a new cell 0x38 [0x38]",
			"Retry upon entry into a new cell 0x39 [0x39]",
			"Retry upon entry into a new cell 0x3a [0x3a]",
			"Retry upon entry into a new cell 0x3b [0x3b]",
			"Retry upon entry into a new cell 0x3c [0x3c]",
			"Retry upon entry into a new cell 0x3d [0x3d]",
			"Retry upon entry into a new cell 0x3e [0x3e]",
			"Retry upon entry into a new cell 0x3f [0x3f]",
			"0x40",
			"0x41",
			"0x42",
			"0x43",
			"0x44",
			"0x45",
			"0x46",
			"0x47",
			"0x48",
			"0x49",
			"0x4a",
			"0x4b",
			"0x4c",
			"0x4d",
			"0x4e",
			"0x4f",
			"0x50",
			"0x51",
			"0x52",
			"0x53",
			"0x54",
			"0x55",
			"0x56",
			"0x57",
			"0x58",
			"0x59",
			"0x5a",
			"0x5b",
			"0x5c",
			"0x5d",
			"0x5e",
			"Semantically incorrect message [0x5f]",
			"Invalid mandatory information [0x60]",
			"Message type non-existent or not implemented [0x61]",
			"Message type not compatible with the protocol state [0x62]",
			"Information element non-existent or not implemented [0x63]",
			"Conditional IE error [0x64]",
			"Message not compatible with the protocol state [0x65]",
			"0x66",
			"0x67",
			"0x68",
			"0x69",
			"0x6a",
			"0x6b",
			"0x6c",
			"0x6d",
			"0x6e",
			"Protocol error-unspecified [0x6f]"
	};

	const char *SM_Cause_Codes_Val_String[] = {
			"0x00",
			"0x01",
			"0x02",
			"0x03",
			"0x04",
			"0x05",
			"0x06",
			"0x07",
			"Operator Determined Barring [0x08]",
			"0x09",
			"0x0a",
			"0x0b",
			"0x0c",
			"0x0d",
			"0x0e",
			"0x0f",
			"0x10",
			"0x11",
			"0x12",
			"0x13",
			"0x14",
			"0x15",
			"0x16",
			"0x17",
			"MBMS bearer capabilities insufficient for the service [0x18]",
			"LLC or SNDCP failure(A/Gb mode only) [0x19]",
			"Insufficient resources [0x1a]",
			"Missing or unknown APN [0x1b]",
			"Unknown PDP address or PDP type [0x1c]",
			"User authentication failed [0x1d]",
			"Activation rejected by GGSN Serving GW or PDN GW [0x1e]",
			"Activation rejected unspecified [0x1f]",
			"Service option not supported [0x20]",
			"Requested service option not subscribed [0x21]",
			"Service option temporarily out of order [0x22]",
			"NSAPI already used (not sent) [0x23]",
			"Regular deactivation [0x24]",
			"QoS not accepted [0x25]",
			"Network failure [0x26]",
			"Reactivation requested [0x27]",
			"Feature not supported [0x28]",
			"Semantic error in the TFT operation [0x29]",
			"Syntactical error in the TFT operation [0x2a]",
			"Unknown PDP context [0x2b]",
			"Semantic errors in packet filter(s) [0x2c]",
			"Syntactical errors in packet filter(s) [0x2d]",
			"PDP context without TFT already activated  [0x2e]",
			"Multicast group membership time-out  [0x2f]",
			"Request rejected BCM violation [0x30]",
			"0x31",
			"PDP type IPv4 only allowed [0x32]",
			"PDP type IPv6 only allowed [0x33]",
			"Single address bearers only allowed [0x34]",
			"0x35",
			"0x36",
			"0x37",
			"Collision with network initiated request [0x38]",
			"0x39",
			"0x3a",
			"0x3b",
			"Bearer handling not supported [0x3C]",
			"0x3d",
			"0x3e",
			"0x3f",
			"0x40",
			"Maximum number of PDP contexts reached [0x41]",
			"Requested APN not supported in current RAT and PLMN combination [0x42]",
			"0x43",
			"0x44",
			"0x45",
			"0x46",
			"0x47",
			"0x48",
			"0x49",
			"0x4a",
			"0x4b",
			"0x4c",
			"0x4d",
			"0x4e",
			"0x4f",
			"0x50",
			"Invalid transaction identifier value [0x51]",
			"0x52",
			"0x53",
			"0x54",
			"0x55",
			"0x56",
			"0x57",
			"0x58",
			"0x59",
			"0x5a",
			"0x5b",
			"0x5c",
			"0x5d",
			"0x5e",
			"Semantically incorrect message [0x5f]",
			"Invalid mandatory information [0x60]",
			"Message type non-existent or not implemented [0x61]",
			"Message type not compatible with the protocol state [0x62]",
			"Information element non-existent or not implemented [0x63]",
			"Conditional IE error [0x64]",
			"Message not compatible with the protocol state [0x65]",
			"0x66",
			"0x67",
			"0x68",
			"0x69",
			"0x6a",
			"0x6b",
			"0x6c",
			"0x6d",
			"0x6e",
			"Protocol error-unspecified [0x6f]",
			"APN restriction value incompatible with active PDP context [0x70]"
	};
}

