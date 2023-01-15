/*
 * IUPSGlobal.h
 *
 *  Created on: 14-Jul-2016
 *      Author: deb
 */

#ifndef PLUGINS_IUPS_SRC_IUPSGLOBAL_H_
#define PLUGINS_IUPS_SRC_IUPSGLOBAL_H_

#include <map>
#include "SpectaTypedef.h"
#include "IPGlobal.h"

#define IUPS_POOL_ARRAY_ELEMENTS			100		//Poosible values 10, 100, 1000, 10000, 100000....

#define IUPS_FLUSH_POOL_ARRAY_ELEMENTS	100		//Poosible values 10, 100, 1000, 10000, 100000....
#define IUPS_FLUSH_POOL_ARRAY_SIZE		40000

#define IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE			50000

using namespace std;


typedef struct _iupsSession{

	bool		sccp_cr;
	uint64_t	CRTimeEpochMicroSec;
	bool		sccp_cc;
	uint64_t	CCTimeEpochMicroSec;
	bool		sccp_dt;
	uint64_t	DTTimeEpochMicroSec;
	bool		sccp_rlsd;
	uint64_t	RLSDTimeEpochMicroSec;
	bool		sccp_rlc;
	uint64_t	RLCTimeEpochMicroSec;
	char 		SessionId[SESSION_ID_LEN];
	char		SessionType[DESC_LEN];
	uint64_t 	StartTimeEpochMicroSec;
	uint64_t 	IntmdTimeEpochMicroSec;
	uint64_t 	EndTimeEpochMicroSec;
	uint64_t	LastUpdateTimeEpcohMicroSec;
	char 		SourceMAC[MAC_ADDR_LEN];
	char 		DestinationMAC[MAC_ADDR_LEN];
	uint32_t 	SourceIP;
	uint32_t 	DestinationIP;
	int		TotalBytesUL;
	int		TotalBytesDL;
	int 	VLANId;
	bool 	SessionStartDirUp;
	int 	OPC;
	int 	DPC;
	char	SCCPSessionId[SESSION_ID_LEN];
	char 	Slr[DESC_LEN];
	char 	Dlr[DESC_LEN];
	int		SCCPMsgId;
	char  	SCCPMsgDesc[DESC_LEN];
	int 	RelCause;
	char 	RelDesc[DESC_LEN];
	char 	IMSI[IMSI_LEN];
	char 	IMEI[IMEI_LEN];
	char 	TMSI[IMSI_LEN];
	char 	MSISDN[MSISDN_LEN];
	bool 	RNC_SGSN;
	char 	RNCId[DESC_LEN];
	int  	StartRanapProcedureId;
	char 	StartRanapProcedureDesc[DESC_LEN];
	int  	EndRanapProcedureId;
	char 	EndRanapProcedureDesc[DESC_LEN];
//	int  	LastKnownRanapProcedureId;
//	char 	LastKnownRanapProcedureDesc;
    int  	StartMMSMMessageId;
    char	StartMMSMMessageDesc[DESC_LEN];
    int 	IntmdMMSMMessageId;
    char	IntmdMMSMMessageDesc[DESC_LEN];
    int 	EndMMSMMessageId;
    char	EndMMSMMessageDesc[DESC_LEN];
	int 	SessionBytesUL;
	int 	SessionBytesDL;
    int 	RABCauseId;
	char 	RABCauseDesc[DESC_LEN];
	char 	RABId[DESC_LEN];
	char 	TEId[DESC_LEN];
	int 	RATId;
    int 	RAUpdateId;
    int 	EndCauseId;
	char 	EndCauseDesc[DESC_LEN];
    int 	AttachDetachId;
	char 	AttachDetachDir[DESC_LEN];
	char 	AttachDetachDesc[DESC_LEN];
	int 	PDPStaticAddressRequested;
	char 	PDPAddressRequested[IP_ADDR_LEN];
	char 	PDPAddressAllocated[IP_ADDR_LEN];
	char 	RAIOld[DESC_LEN];
	char 	RAINew[DESC_LEN];
	char 	PLMNFirstId[DESC_LEN];
	char 	PLMNLastId[DESC_LEN];
	char 	SACFirstId[DESC_LEN];
	char 	SACLastId[DESC_LEN];
	char 	LACFirstId[DESC_LEN];
	char 	LACLastId[DESC_LEN];
	char 	RACFirstId[DESC_LEN];
	char 	RACLastId[DESC_LEN];
	char 	APN[APN_LEN];
	int 	ByteSizeUL;
	int 	ByteSizeDL;

	long 	frameByteSizeUL;
	long 	frameByteSizeDL;

    char	Mbrupl[10];
    char	Mbrdnl[10];
    char	ExtendedMbr[10];

	uint16_t	reqPdp_Mbrupl;
	uint16_t	reqPdp_Mbrdnl;
	uint16_t	rspPdp_Mbrupl;
	uint16_t	rspPdp_Mbrdnl;
	uint16_t	rspPdp_ExtMbr;

	_iupsSession()
	{ reset(); }


	void reset()
	{
		sccp_cr = false;
		CRTimeEpochMicroSec = 0;
		sccp_cc = false;
		CCTimeEpochMicroSec = 0;
		sccp_dt = false;
		DTTimeEpochMicroSec = 0;
		sccp_rlsd = false;
		RLSDTimeEpochMicroSec = 0;
		sccp_rlc = false;
		RLCTimeEpochMicroSec = 0;
		SessionId[0] = 0;
		SessionType[0] = 0;
		StartTimeEpochMicroSec = 0;
		IntmdTimeEpochMicroSec = 0;
		EndTimeEpochMicroSec = 0;
		LastUpdateTimeEpcohMicroSec = 0;
		SourceMAC[0] = 0;
		DestinationMAC[0] = 0;
		SourceIP = 0;
		DestinationIP = 0;
		TotalBytesUL = 0;
		TotalBytesDL = 0;
		VLANId = 0;
		SessionStartDirUp = false;
		OPC = 0;
		DPC = 0;
		SCCPSessionId[0] = 0;
		Slr[0] = 0;
		Dlr[0] = 0;
		SCCPMsgId = -1;
		SCCPMsgDesc[0] = 0;
		RelCause = -1;
		RelDesc[0] = 0;
		IMSI[0] = 0;
		IMEI[0] = 0;
		TMSI[0] = 0;
		MSISDN[0] = 0;
		RNC_SGSN = false;
		RNCId[0] = 0;
		StartRanapProcedureId = -1;
		StartRanapProcedureDesc[0] = 0;
		EndRanapProcedureId = -1;
		EndRanapProcedureDesc[0] = 0;
//		LastKnownRanapProcedureId = -1;
//		LastKnownRanapProcedureDesc[0] = 0;
		StartMMSMMessageId = -1;
	    StartMMSMMessageDesc[0] = 0;
		IntmdMMSMMessageId = -1;
	    IntmdMMSMMessageDesc[0] = 0;
		EndMMSMMessageId = -1;
	    EndMMSMMessageDesc[0] = 0;
		SessionBytesUL = 0;
		SessionBytesDL = 0;
		RABCauseId = -1;
		RABCauseDesc[0] = 0;
		RABId[0] = 0;
		TEId[0] = 0;
		RATId = 1;
		RAUpdateId = -1;
		EndCauseId = -1;
		EndCauseDesc[0] = 0;
		AttachDetachId = -1;
		AttachDetachDir[0] = 0;
		AttachDetachDesc[0] = 0;
		PDPStaticAddressRequested = -1;
		PDPAddressRequested[0] = 0;
		PDPAddressAllocated[0] = 0;
		RAIOld[0] = 0;
		RAINew[0] = 0;
		PLMNFirstId[0] = 0;
		PLMNLastId[0] = 0;
		SACFirstId[0] = 0;
		SACLastId[0] = 0;
		LACFirstId[0] = 0;
		LACLastId[0] = 0;
		RACFirstId[0] = 0;
		RACLastId[0] = 0;
		APN[0] = 0;
		ByteSizeUL = 0;
		ByteSizeDL = 0;
		frameByteSizeUL = 0;
		frameByteSizeDL = 0;
	    strcpy(Mbrupl, "0");
	    strcpy(Mbrdnl, "0");
	    strcpy(ExtendedMbr, "0");

	    reqPdp_Mbrupl = 0;
	    reqPdp_Mbrdnl = 0;
	    rspPdp_Mbrupl = 0;
	    rspPdp_Mbrdnl = 0;
	    rspPdp_ExtMbr = 0;

	}

	void set(const _iupsSession *obj)
	{
		this->sccp_cr = obj->sccp_cr;
		this->CRTimeEpochMicroSec = obj->CRTimeEpochMicroSec;
		this->sccp_cc = obj->sccp_cc;
		this->CCTimeEpochMicroSec = obj->CCTimeEpochMicroSec;
		this->sccp_dt = obj->sccp_dt;
		this->DTTimeEpochMicroSec = obj->DTTimeEpochMicroSec;
		this->sccp_rlsd = obj->sccp_rlsd;
		this->RLSDTimeEpochMicroSec = obj->RLSDTimeEpochMicroSec;
		this->sccp_rlc = obj->sccp_rlc;
		this->RLCTimeEpochMicroSec = obj->RLCTimeEpochMicroSec;
		strcpy(this->SessionId, obj->SessionId);
		strcpy(this->SessionType, obj->SessionType);
		this->StartTimeEpochMicroSec = obj->StartTimeEpochMicroSec;
		this->IntmdTimeEpochMicroSec = obj->IntmdTimeEpochMicroSec;
		this->EndTimeEpochMicroSec = obj->EndTimeEpochMicroSec;
		this->LastUpdateTimeEpcohMicroSec = obj->LastUpdateTimeEpcohMicroSec;
		strcpy(this->SourceMAC, obj->SourceMAC);
		strcpy(this->DestinationMAC, obj->DestinationMAC);
		this->SourceIP = obj->SourceIP;
		this->DestinationIP =  obj->DestinationIP;
		this->TotalBytesUL = obj->TotalBytesUL;
		this->TotalBytesDL = obj->TotalBytesDL;
		this->VLANId = obj->VLANId;
		this->SessionStartDirUp = obj->SessionStartDirUp;
		this->OPC = obj->OPC;
		this->DPC = obj->DPC;
		strcpy(this->SCCPSessionId, obj->SCCPSessionId);
		strcpy(this->Slr, obj->Slr);
		strcpy(this->Dlr, obj->Dlr);
		this->SCCPMsgId = obj->SCCPMsgId;
		strcpy(this->SCCPMsgDesc, obj->SCCPMsgDesc);
		this->RelCause = obj->RelCause;
		strcpy(this->RelDesc, obj->RelDesc);
		strcpy(this->IMSI, obj->IMSI);
		strcpy(this->IMEI, obj->IMEI);
		strcpy(this->TMSI, obj->TMSI);
		strcpy(this->MSISDN, obj->MSISDN);
		this->RNC_SGSN = obj->RNC_SGSN;
		strcpy(this->RNCId, obj->RNCId);
		this->StartRanapProcedureId = obj->StartRanapProcedureId;
		strcpy(this->StartRanapProcedureDesc, obj->StartRanapProcedureDesc);
		this->EndRanapProcedureId = obj->EndRanapProcedureId;
		strcpy(this->EndRanapProcedureDesc, obj->EndRanapProcedureDesc);
//		this->LastKnownRanapProcedureId = obj->LastKnownRanapProcedureId;
//		this->LastKnownRanapProcedureDesc, obj->LastKnownRanapProcedureDesc);
		this->StartMMSMMessageId = obj->StartMMSMMessageId;
		strcpy(this->StartMMSMMessageDesc, obj->StartMMSMMessageDesc);
		this->IntmdMMSMMessageId = obj->IntmdMMSMMessageId;
		strcpy(this->IntmdMMSMMessageDesc, obj->IntmdMMSMMessageDesc);
		this->EndMMSMMessageId = obj->EndMMSMMessageId;
		strcpy(this->EndMMSMMessageDesc, obj->EndMMSMMessageDesc);
		this->SessionBytesUL = obj->SessionBytesUL;
		this->SessionBytesDL = obj->SessionBytesDL;
		this->RABCauseId = obj->RABCauseId;
		strcpy(this->RABCauseDesc, obj->RABCauseDesc);
		strcpy(this->RABId, obj->RABId);
		strcpy(this->TEId, obj->TEId);
		this->RATId = obj->RATId;;
		this->RAUpdateId = obj->RAUpdateId;;
		this->EndCauseId = obj->EndCauseId;;
		strcpy(this->EndCauseDesc, obj->EndCauseDesc);
		this->AttachDetachId = obj->AttachDetachId;;
		strcpy(this->AttachDetachDir, obj->AttachDetachDir);
		strcpy(this->AttachDetachDesc, obj->AttachDetachDesc);
		this->PDPStaticAddressRequested = obj->PDPStaticAddressRequested;;
		strcpy(this->PDPAddressRequested, obj->PDPAddressRequested);
		strcpy(this->PDPAddressAllocated, obj->PDPAddressAllocated);
		strcpy(this->RAIOld, obj->RAIOld);
		strcpy(this->RAINew, obj->RAINew);
		strcpy(this->PLMNFirstId, obj->PLMNFirstId);
		strcpy(this->PLMNLastId, obj->PLMNLastId);
		strcpy(this->SACFirstId, obj->SACFirstId);
		strcpy(this->SACLastId, obj->SACLastId);
		strcpy(this->LACFirstId, obj->LACFirstId);
		strcpy(this->LACLastId, obj->LACLastId);
		strcpy(this->RACFirstId, obj->RACFirstId);
		strcpy(this->RACLastId, obj->RACLastId);
		strcpy(this->APN, obj->APN);
		this->ByteSizeUL = obj->ByteSizeUL;
		this->ByteSizeDL = obj->ByteSizeDL;
		this->frameByteSizeUL = obj->frameByteSizeUL;
		this->frameByteSizeDL = obj->frameByteSizeDL;
	    strcpy(this->Mbrupl, obj->Mbrupl);
	    strcpy(this->Mbrdnl, obj->Mbrdnl);
	    strcpy(this->ExtendedMbr, obj->ExtendedMbr);
	    reqPdp_Mbrupl = obj->reqPdp_Mbrupl;
	    reqPdp_Mbrdnl = obj->reqPdp_Mbrdnl;
	    rspPdp_Mbrupl = obj->rspPdp_Mbrupl;
	    rspPdp_Mbrdnl = obj->rspPdp_Mbrdnl;
	    rspPdp_ExtMbr = obj->rspPdp_ExtMbr;
	}

	void copy(const _iupsSession* obj)
	{
		this->sccp_cr = obj->sccp_cr;
		this->CRTimeEpochMicroSec = obj->CRTimeEpochMicroSec;
		this->sccp_cc = obj->sccp_cc;
		this->CCTimeEpochMicroSec = obj->CCTimeEpochMicroSec;
		this->sccp_dt = obj->sccp_dt;
		this->DTTimeEpochMicroSec = obj->DTTimeEpochMicroSec;
		this->sccp_rlsd = obj->sccp_rlsd;
		this->RLSDTimeEpochMicroSec = obj->RLSDTimeEpochMicroSec;
		this->sccp_rlc = obj->sccp_rlc;
		this->RLCTimeEpochMicroSec = obj->RLCTimeEpochMicroSec;
		strcpy(this->SessionId, obj->SessionId);
		strcpy(this->SessionType, obj->SessionType);
		this->StartTimeEpochMicroSec = obj->StartTimeEpochMicroSec;
		this->IntmdTimeEpochMicroSec = obj->IntmdTimeEpochMicroSec;
		this->EndTimeEpochMicroSec = obj->EndTimeEpochMicroSec;
		this->LastUpdateTimeEpcohMicroSec = obj->LastUpdateTimeEpcohMicroSec;
		strcpy(this->SourceMAC, obj->SourceMAC);
		strcpy(this->DestinationMAC, obj->DestinationMAC);
		this->SourceIP = obj->SourceIP;
		this->DestinationIP = obj->DestinationIP;
		this->TotalBytesUL = obj->TotalBytesUL;
		this->TotalBytesDL = obj->TotalBytesDL;
		this->VLANId = obj->VLANId;
		this->SessionStartDirUp = obj->SessionStartDirUp;
		this->OPC = obj->OPC;
		this->DPC = obj->DPC;
		strcpy(this->SCCPSessionId, obj->SCCPSessionId);
		strcpy(this->Slr, obj->Slr);
		strcpy(this->Dlr, obj->Dlr);
		this->SCCPMsgId = obj->SCCPMsgId;
		strcpy(this->SCCPMsgDesc, obj->SCCPMsgDesc);
		this->RelCause = obj->RelCause;
		strcpy(this->RelDesc, obj->RelDesc);
		strcpy(this->IMSI, obj->IMSI);
		strcpy(this->IMEI, obj->IMEI);
		strcpy(this->TMSI, obj->TMSI);
		strcpy(this->MSISDN, obj->MSISDN);
		this->RNC_SGSN = obj->RNC_SGSN;
		strcpy(this->RNCId, obj->RNCId);
		this->StartRanapProcedureId = obj->StartRanapProcedureId;
		strcpy(this->StartRanapProcedureDesc, obj->StartRanapProcedureDesc);
		this->EndRanapProcedureId = obj->EndRanapProcedureId;
		strcpy(this->EndRanapProcedureDesc, obj->EndRanapProcedureDesc);
//		this->LastKnownRanapProcedureId = obj->LastKnownRanapProcedureId;
//		this->LastKnownRanapProcedureDesc, obj->LastKnownRanapProcedureDesc);
		this->StartMMSMMessageId = obj->StartMMSMMessageId;
		strcpy(this->StartMMSMMessageDesc, obj->StartMMSMMessageDesc);
		this->IntmdMMSMMessageId = obj->IntmdMMSMMessageId;
		strcpy(this->IntmdMMSMMessageDesc, obj->IntmdMMSMMessageDesc);
		this->EndMMSMMessageId = obj->EndMMSMMessageId;
		strcpy(this->EndMMSMMessageDesc, obj->EndMMSMMessageDesc);
		this->SessionBytesUL = obj->SessionBytesUL;
		this->SessionBytesDL = obj->SessionBytesDL;
		this->RABCauseId = obj->RABCauseId;;
		strcpy(this->RABCauseDesc, obj->RABCauseDesc);
		strcpy(this->RABId, obj->RABId);
		strcpy(this->TEId, obj->TEId);
		this->RATId = obj->RATId;;
		this->RAUpdateId = obj->RAUpdateId;;
		this->EndCauseId = obj->EndCauseId;;
		strcpy(this->EndCauseDesc, obj->EndCauseDesc);
		this->AttachDetachId = obj->AttachDetachId;;
		strcpy(this->AttachDetachDir, obj->AttachDetachDir);
		strcpy(this->AttachDetachDesc, obj->AttachDetachDesc);
		this->PDPStaticAddressRequested = obj->PDPStaticAddressRequested;;
		strcpy(this->PDPAddressRequested, obj->PDPAddressRequested);
		strcpy(this->PDPAddressAllocated, obj->PDPAddressAllocated);
		strcpy(this->RAIOld, obj->RAIOld);
		strcpy(this->RAINew, obj->RAINew);
		strcpy(this->PLMNFirstId, obj->PLMNFirstId);
		strcpy(this->PLMNLastId, obj->PLMNLastId);
		strcpy(this->SACFirstId, obj->SACFirstId);
		strcpy(this->SACLastId, obj->SACLastId);
		strcpy(this->LACFirstId, obj->LACFirstId);
		strcpy(this->LACLastId, obj->LACLastId);
		strcpy(this->RACFirstId, obj->RACFirstId);
		strcpy(this->RACLastId, obj->RACLastId);
		strcpy(this->APN, obj->APN);
		this->ByteSizeUL = obj->ByteSizeUL;
		this->ByteSizeDL = obj->ByteSizeDL;
		this->frameByteSizeUL = obj->frameByteSizeUL;
		this->frameByteSizeDL = obj->frameByteSizeDL;
	    strcpy(this->Mbrupl, obj->Mbrupl);
	    strcpy(this->Mbrdnl, obj->Mbrdnl);
	    strcpy(this->ExtendedMbr, obj->ExtendedMbr);
	    reqPdp_Mbrupl = obj->reqPdp_Mbrupl;
	    reqPdp_Mbrdnl = obj->reqPdp_Mbrdnl;
	    rspPdp_Mbrupl = obj->rspPdp_Mbrupl;
	    rspPdp_Mbrdnl = obj->rspPdp_Mbrdnl;
	    rspPdp_ExtMbr = obj->rspPdp_ExtMbr;

	}

	void operator=(const _iupsSession& obj)
	{
		this->sccp_cr = obj.sccp_cr;
		this->CRTimeEpochMicroSec = obj.CRTimeEpochMicroSec;
		this->sccp_cc = obj.sccp_cc;
		this->CCTimeEpochMicroSec = obj.CCTimeEpochMicroSec;
		this->sccp_dt = obj.sccp_dt;
		this->DTTimeEpochMicroSec = obj.DTTimeEpochMicroSec;
		this->sccp_rlsd = obj.sccp_rlsd;
		this->RLSDTimeEpochMicroSec = obj.RLSDTimeEpochMicroSec;
		this->sccp_rlc = obj.sccp_rlc;
		this->RLCTimeEpochMicroSec = obj.RLCTimeEpochMicroSec;
		strcpy(this->SessionId, obj.SessionId);
		strcpy(this->SessionType, obj.SessionType);
		this->StartTimeEpochMicroSec = obj.StartTimeEpochMicroSec;
		this->IntmdTimeEpochMicroSec = obj.IntmdTimeEpochMicroSec;
		this->EndTimeEpochMicroSec = obj.EndTimeEpochMicroSec;
		this->LastUpdateTimeEpcohMicroSec = obj.LastUpdateTimeEpcohMicroSec;
		strcpy(this->SourceMAC, obj.SourceMAC);
		strcpy(this->DestinationMAC, obj.DestinationMAC);
		this->SourceIP = obj.SourceIP;
		this->DestinationIP = obj.DestinationIP;
		this->TotalBytesUL = obj.TotalBytesUL;
		this->TotalBytesDL = obj.TotalBytesDL;
		this->VLANId = obj.VLANId;
		this->SessionStartDirUp = obj.SessionStartDirUp;
		this->OPC = obj.OPC;
		this->DPC = obj.DPC;
		strcpy(this->SCCPSessionId, obj.SCCPSessionId);
		strcpy(this->Slr, obj.Slr);
		strcpy(this->Dlr, obj.Dlr);
		this->SCCPMsgId = obj.SCCPMsgId;
		strcpy(this->SCCPMsgDesc, obj.SCCPMsgDesc);
		this->RelCause = obj.RelCause;
		strcpy(this->RelDesc, obj.RelDesc);
		strcpy(this->IMSI, obj.IMSI);
		strcpy(this->IMEI, obj.IMEI);
		strcpy(this->TMSI, obj.TMSI);
		strcpy(this->MSISDN, obj.MSISDN);
		this->RNC_SGSN = obj.RNC_SGSN;
		strcpy(this->RNCId, obj.RNCId);
		this->StartRanapProcedureId = obj.StartRanapProcedureId;
		strcpy(this->StartRanapProcedureDesc, obj.StartRanapProcedureDesc);
		this->EndRanapProcedureId = obj.EndRanapProcedureId;
		strcpy(this->EndRanapProcedureDesc, obj.EndRanapProcedureDesc);
//		this->LastKnownRanapProcedureId = obj.LastKnownRanapProcedureId;
//		this->LastKnownRanapProcedureDesc, obj.LastKnownRanapProcedureDesc);
		this->StartMMSMMessageId = obj.StartMMSMMessageId;
		strcpy(this->StartMMSMMessageDesc, obj.StartMMSMMessageDesc);
		this->IntmdMMSMMessageId = obj.IntmdMMSMMessageId;
		strcpy(this->IntmdMMSMMessageDesc, obj.IntmdMMSMMessageDesc);
		this->EndMMSMMessageId = obj.EndMMSMMessageId;
		strcpy(this->EndMMSMMessageDesc, obj.EndMMSMMessageDesc);
		this->SessionBytesUL = obj.SessionBytesUL;
		this->SessionBytesDL = obj.SessionBytesDL;
		this->RABCauseId = obj.RABCauseId;;
		strcpy(this->RABCauseDesc, obj.RABCauseDesc);
		strcpy(this->RABId, obj.RABId);
		strcpy(this->TEId, obj.TEId);
		this->RATId = obj.RATId;;
		this->RAUpdateId = obj.RAUpdateId;;
		this->EndCauseId = obj.EndCauseId;;
		strcpy(this->EndCauseDesc, obj.EndCauseDesc);
		this->AttachDetachId = obj.AttachDetachId;;
		strcpy(this->AttachDetachDir, obj.AttachDetachDir);
		strcpy(this->AttachDetachDesc, obj.AttachDetachDesc);
		this->PDPStaticAddressRequested = obj.PDPStaticAddressRequested;;
		strcpy(this->PDPAddressRequested, obj.PDPAddressRequested);
		strcpy(this->PDPAddressAllocated, obj.PDPAddressAllocated);
		strcpy(this->RAIOld, obj.RAIOld);
		strcpy(this->RAINew, obj.RAINew);
		strcpy(this->PLMNFirstId, obj.PLMNFirstId);
		strcpy(this->PLMNLastId, obj.PLMNLastId);
		strcpy(this->SACFirstId, obj.SACFirstId);
		strcpy(this->SACLastId, obj.SACLastId);
		strcpy(this->LACFirstId, obj.LACFirstId);
		strcpy(this->LACLastId, obj.LACLastId);
		strcpy(this->RACFirstId, obj.RACFirstId);
		strcpy(this->RACLastId, obj.RACLastId);
		strcpy(this->APN, obj.APN);
		this->ByteSizeUL = obj.ByteSizeUL;
		this->ByteSizeDL = obj.ByteSizeDL;
		this->frameByteSizeUL = obj.frameByteSizeUL;
		this->frameByteSizeDL = obj.frameByteSizeDL;
	    strcpy(this->Mbrupl, obj.Mbrupl);
	    strcpy(this->Mbrdnl, obj.Mbrdnl);
	    strcpy(this->ExtendedMbr, obj.ExtendedMbr);
	    reqPdp_Mbrupl = obj.reqPdp_Mbrupl;
	    reqPdp_Mbrdnl = obj.reqPdp_Mbrdnl;
	    rspPdp_Mbrupl = obj.rspPdp_Mbrupl;
	    rspPdp_Mbrdnl = obj.rspPdp_Mbrdnl;
	    rspPdp_ExtMbr = obj.rspPdp_ExtMbr;
	}
}iupsSession;



typedef struct _iupsTrxSession{

	bool 		SessionActive;
	bool		IntmdSession;
	bool 		SessionStartDirUp;
	uint64_t	StartTimeEpochMicroSec;
	uint64_t 	IntmdTimeEpochMicroSec;
	uint64_t 	EndTimeEpochMicroSec;
	int  		StartRanapProcedureId;
	char	 	StartRanapProcedureDesc[DESC_LEN];
	int  		EndRanapProcedureId;
	char 		EndRanapProcedureDesc[DESC_LEN];
    int  		StartMMSMMessageId;
    char 		StartMMSMMessageDesc[DESC_LEN];
    int  		IntmdMMSMMessageId;
    char 		IntmdMMSMMessageDesc[DESC_LEN];
    int 		EndMMSMMessageId;
    char		EndMMSMMessageDesc[DESC_LEN];
    int 		RABCauseId;
    char 		RABCauseDesc[DESC_LEN];
    char 		RABId[DESC_LEN];
    char 		TEId[DESC_LEN];
	int 		RATId;
    int 		RAUpdateId;
    int 		EndCauseId;
    char 		EndCauseDesc[DESC_LEN];
    int 		AttachDetachId;
    char 		AttachDetachDir[DESC_LEN];
    char 		AttachDetachDesc[DESC_LEN];
	int 		PDPStaticAddressRequested;
	char 		PDPAddressRequested[DESC_LEN];
	char 		PDPAddressAllocated[DESC_LEN];
	char 		RAIOld[DESC_LEN];
	char 		RAINew[DESC_LEN];
	char 		PLMNFirstId[DESC_LEN];
	char 		PLMNLastId[DESC_LEN];
	char 		SACFirstId[DESC_LEN];
	char 		SACLastId[DESC_LEN];
	char 		LACFirstId[DESC_LEN];
	char 		LACLastId[DESC_LEN];
	char 		RACFirstId[DESC_LEN];
	char 		RACLastId[DESC_LEN];
	char 		APN[APN_LEN];
	int 		ByteSizeUL;
	int 		ByteSizeDL;
    char		Mbrupl[10];
    char		Mbrdnl[10];
    char		ExtendedMbr[10];

	uint16_t	reqPdp_Mbrupl;
	uint16_t	reqPdp_Mbrdnl;
	uint16_t	rspPdp_Mbrupl;
	uint16_t	rspPdp_Mbrdnl;
	uint16_t	rspPdp_ExtMbr;

	_iupsTrxSession()
	{ reset(); }


	void reset()
	{
		SessionActive = false;
		IntmdSession = false;
		SessionStartDirUp = false;
		StartTimeEpochMicroSec = 0;
		IntmdTimeEpochMicroSec = 0;
		EndTimeEpochMicroSec = 0;
		StartRanapProcedureId = -1;
		StartRanapProcedureDesc[0] = 0;
		EndRanapProcedureId = -1;
		EndRanapProcedureDesc[0] = 0;
		StartMMSMMessageId = -1;
	    StartMMSMMessageDesc[0] = 0;
		IntmdMMSMMessageId = -1;
	    IntmdMMSMMessageDesc[0] = 0;
		EndMMSMMessageId = -1;
	    EndMMSMMessageDesc[0] = 0;
//		SessionBytesUL = 0;
//		SessionBytesDL = 0;
		RABCauseId = -1;
		RABCauseDesc[0] = 0;
		RABId[0] = 0;
		TEId[0] = 0;
		RATId = 1;
		RAUpdateId = -1;
		EndCauseId = -1;
		EndCauseDesc[0] = 0;
		AttachDetachId = -1;
		AttachDetachDir[0] = 0;
		AttachDetachDesc[0] = 0;
		PDPStaticAddressRequested = -1;
		PDPAddressRequested[0] = 0;
		PDPAddressAllocated[0] = 0;
		RAIOld[0] = 0;
		RAINew[0] = 0;
		PLMNFirstId[0] = 0;
		PLMNLastId[0] = 0;
		SACFirstId[0] = 0;
		SACLastId[0] = 0;
		LACFirstId[0] = 0;
		LACLastId[0] = 0;
		RACFirstId[0] = 0;
		RACLastId[0] = 0;
		APN[0] = 0;
		ByteSizeUL = 0;
		ByteSizeDL = 0;
	    strcpy(Mbrupl, "0");
	    strcpy(Mbrdnl, "0");
	    strcpy(ExtendedMbr, "0");

		reqPdp_Mbrupl = 0;
		reqPdp_Mbrdnl = 0;
		rspPdp_Mbrupl = 0;
		rspPdp_Mbrdnl = 0;
		rspPdp_ExtMbr = 0;

	}

	void set(const _iupsTrxSession *obj)
	{
		SessionActive = obj->SessionActive;
		IntmdSession = obj->IntmdSession;
		SessionStartDirUp = obj->SessionStartDirUp;
		StartTimeEpochMicroSec = obj->StartTimeEpochMicroSec;
		IntmdTimeEpochMicroSec = obj->IntmdTimeEpochMicroSec;
		EndTimeEpochMicroSec = obj->EndTimeEpochMicroSec;
		StartRanapProcedureId = obj->StartRanapProcedureId;
		strcpy(StartRanapProcedureDesc, obj->StartRanapProcedureDesc);
		EndRanapProcedureId = obj->EndRanapProcedureId;
		strcpy(EndRanapProcedureDesc, obj->EndRanapProcedureDesc);
		StartMMSMMessageId = obj->StartMMSMMessageId;
		strcpy(StartMMSMMessageDesc, obj->StartMMSMMessageDesc);
		IntmdMMSMMessageId = obj->IntmdMMSMMessageId;
		strcpy(IntmdMMSMMessageDesc, obj->IntmdMMSMMessageDesc);
		EndMMSMMessageId = obj->EndMMSMMessageId;
		strcpy(EndMMSMMessageDesc, obj->EndMMSMMessageDesc);
//		SessionBytesUL = obj->;
//		SessionBytesDL = obj->;
		RABCauseId = obj->RABCauseId;
		strcpy(RABCauseDesc, obj->RABCauseDesc);
		strcpy(RABId, obj->RABId);
		strcpy(TEId, obj->TEId);
		RATId = obj->RATId;
		RAUpdateId = obj->RAUpdateId;
		EndCauseId = obj->EndCauseId;
		strcpy(EndCauseDesc, obj->EndCauseDesc);
		AttachDetachId = obj->AttachDetachId;
		strcpy(AttachDetachDir, obj->AttachDetachDir);
		strcpy(AttachDetachDesc, obj->AttachDetachDesc);
		PDPStaticAddressRequested = obj->PDPStaticAddressRequested;
		strcpy(PDPAddressRequested, obj->PDPAddressRequested);
		strcpy(PDPAddressAllocated, obj->PDPAddressAllocated);
		strcpy(RAIOld, obj->RAIOld);
		strcpy(RAINew, obj->RAINew);
		strcpy(PLMNFirstId, obj->PLMNFirstId);
		strcpy(PLMNLastId, obj->PLMNLastId);
		strcpy(SACFirstId, obj->SACFirstId);
		strcpy(SACLastId, obj->SACLastId);
		strcpy(LACFirstId, obj->LACFirstId);
		strcpy(LACLastId, obj->LACLastId);
		strcpy(RACFirstId, obj->RACFirstId);
		strcpy(RACLastId, obj->RACLastId);
		strcpy(APN, obj->APN);
		ByteSizeUL = obj->ByteSizeUL;
		ByteSizeDL = obj->ByteSizeDL;
	    strcpy(Mbrupl, obj->Mbrupl);
	    strcpy(Mbrdnl, obj->Mbrdnl);
	    strcpy(ExtendedMbr, obj->ExtendedMbr);

		reqPdp_Mbrupl = obj->reqPdp_Mbrupl;
		reqPdp_Mbrdnl = obj->reqPdp_Mbrdnl;
		rspPdp_Mbrupl = obj->rspPdp_Mbrupl;
		rspPdp_Mbrdnl = obj->rspPdp_Mbrdnl;
		rspPdp_ExtMbr = obj->rspPdp_ExtMbr;

	}
	void copy(const _iupsTrxSession *obj)
	{
		SessionActive = obj->SessionActive;
		IntmdSession = obj->IntmdSession;
		SessionStartDirUp = obj->SessionStartDirUp;
		StartTimeEpochMicroSec = obj->StartTimeEpochMicroSec;
		IntmdTimeEpochMicroSec = obj->IntmdTimeEpochMicroSec;
		EndTimeEpochMicroSec = obj->EndTimeEpochMicroSec;
		StartRanapProcedureId = obj->StartRanapProcedureId;
		strcpy(StartRanapProcedureDesc, obj->StartRanapProcedureDesc);
		EndRanapProcedureId = obj->EndRanapProcedureId;
		strcpy(EndRanapProcedureDesc, obj->EndRanapProcedureDesc);
		StartMMSMMessageId = obj->StartMMSMMessageId;
		strcpy(StartMMSMMessageDesc, obj->StartMMSMMessageDesc);
		IntmdMMSMMessageId = obj->IntmdMMSMMessageId;
		strcpy(IntmdMMSMMessageDesc, obj->IntmdMMSMMessageDesc);
		EndMMSMMessageId = obj->EndMMSMMessageId;
		strcpy(EndMMSMMessageDesc, obj->EndMMSMMessageDesc);
//		SessionBytesUL = obj->;
//		SessionBytesDL = obj->;
		RABCauseId = obj->RABCauseId;
		strcpy(RABCauseDesc, obj->RABCauseDesc);
		strcpy(RABId, obj->RABId);
		strcpy(TEId, obj->TEId);
		RATId = obj->RATId;
		RAUpdateId = obj->RAUpdateId;
		EndCauseId = obj->EndCauseId;
		strcpy(EndCauseDesc, obj->EndCauseDesc);
		AttachDetachId = obj->AttachDetachId;
		strcpy(AttachDetachDir, obj->AttachDetachDir);
		strcpy(AttachDetachDesc, obj->AttachDetachDesc);
		PDPStaticAddressRequested = obj->PDPStaticAddressRequested;
		strcpy(PDPAddressRequested, obj->PDPAddressRequested);
		strcpy(PDPAddressAllocated, obj->PDPAddressAllocated);
		strcpy(RAIOld, obj->RAIOld);
		strcpy(RAINew, obj->RAINew);
		strcpy(PLMNFirstId, obj->PLMNFirstId);
		strcpy(PLMNLastId, obj->PLMNLastId);
		strcpy(SACFirstId, obj->SACFirstId);
		strcpy(SACLastId, obj->SACLastId);
		strcpy(LACFirstId, obj->LACFirstId);
		strcpy(LACLastId, obj->LACLastId);
		strcpy(RACFirstId, obj->RACFirstId);
		strcpy(RACLastId, obj->RACLastId);
		strcpy(APN, obj->APN);
		ByteSizeUL = obj->ByteSizeUL;
		ByteSizeDL = obj->ByteSizeDL;
	    strcpy(Mbrupl, obj->Mbrupl);
	    strcpy(Mbrdnl, obj->Mbrdnl);
	    strcpy(ExtendedMbr, obj->ExtendedMbr);

		reqPdp_Mbrupl = obj->reqPdp_Mbrupl;
		reqPdp_Mbrdnl = obj->reqPdp_Mbrdnl;
		rspPdp_Mbrupl = obj->rspPdp_Mbrupl;
		rspPdp_Mbrdnl = obj->rspPdp_Mbrdnl;
		rspPdp_ExtMbr = obj->rspPdp_ExtMbr;


	}
	void operator=(const _iupsTrxSession& obj)
	{
		SessionActive = obj.SessionActive;
		IntmdSession = obj.IntmdSession;
		SessionStartDirUp = obj.SessionStartDirUp;
		StartTimeEpochMicroSec = obj.StartTimeEpochMicroSec;
		IntmdTimeEpochMicroSec = obj.IntmdTimeEpochMicroSec;
		EndTimeEpochMicroSec = obj.EndTimeEpochMicroSec;
		StartRanapProcedureId = obj.StartRanapProcedureId;
		strcpy(StartRanapProcedureDesc, obj.StartRanapProcedureDesc);
		EndRanapProcedureId = obj.EndRanapProcedureId;
		strcpy(EndRanapProcedureDesc, obj.EndRanapProcedureDesc);
		StartMMSMMessageId = obj.StartMMSMMessageId;
		strcpy(StartMMSMMessageDesc, obj.StartMMSMMessageDesc);
		IntmdMMSMMessageId = obj.IntmdMMSMMessageId;
		strcpy(IntmdMMSMMessageDesc, obj.IntmdMMSMMessageDesc);
		EndMMSMMessageId = obj.EndMMSMMessageId;
		strcpy(EndMMSMMessageDesc, obj.EndMMSMMessageDesc);
//		SessionBytesUL = obj.;
//		SessionBytesDL = obj.;
		RABCauseId = obj.RABCauseId;
		strcpy(RABCauseDesc, obj.RABCauseDesc);
		strcpy(RABId, obj.RABId);
		strcpy(TEId, obj.TEId);
		RATId = obj.RATId;
		RAUpdateId = obj.RAUpdateId;
		EndCauseId = obj.EndCauseId;
		strcpy(EndCauseDesc, obj.EndCauseDesc);
		AttachDetachId = obj.AttachDetachId;
		strcpy(AttachDetachDir, obj.AttachDetachDir);
		strcpy(AttachDetachDesc, obj.AttachDetachDesc);
		PDPStaticAddressRequested = obj.PDPStaticAddressRequested;
		strcpy(PDPAddressRequested, obj.PDPAddressRequested);
		strcpy(PDPAddressAllocated, obj.PDPAddressAllocated);
		strcpy(RAIOld, obj.RAIOld);
		strcpy(RAINew, obj.RAINew);
		strcpy(PLMNFirstId, obj.PLMNFirstId);
		strcpy(PLMNLastId, obj.PLMNLastId);
		strcpy(SACFirstId, obj.SACFirstId);
		strcpy(SACLastId, obj.SACLastId);
		strcpy(LACFirstId, obj.LACFirstId);
		strcpy(LACLastId, obj.LACLastId);
		strcpy(RACFirstId, obj.RACFirstId);
		strcpy(RACLastId, obj.RACLastId);
		strcpy(APN, obj.APN);
		ByteSizeUL = obj.ByteSizeUL;
		ByteSizeDL = obj.ByteSizeDL;
	    strcpy(Mbrupl, obj.Mbrupl);
	    strcpy(Mbrdnl, obj.Mbrdnl);
	    strcpy(ExtendedMbr, obj.ExtendedMbr);
		reqPdp_Mbrupl = obj.reqPdp_Mbrupl;
		reqPdp_Mbrdnl = obj.reqPdp_Mbrdnl;
		rspPdp_Mbrupl = obj.rspPdp_Mbrupl;
		rspPdp_Mbrdnl = obj.rspPdp_Mbrdnl;
		rspPdp_ExtMbr = obj.rspPdp_ExtMbr;
	}
}iupsTrxSession;


typedef struct _iupsGlobalSession
{
	ULONG	TotalBytesUL;
	ULONG	TotalBytesDL;
	int		LastKnownRanapProcedureId;
	char 	PLMNFirstId[DESC_LEN];
	char 	PLMNLastId[DESC_LEN];
	char 	SACFirstId[DESC_LEN];
	char 	SACLastId[DESC_LEN];
	char 	LACFirstId[DESC_LEN];
	char 	LACLastId[DESC_LEN];
	char 	RACFirstId[DESC_LEN];
	char 	RACLastId[DESC_LEN];
	char 	GlobalRNCId[DESC_LEN];
	//int gmm_session_count;
	std::map<int, iupsTrxSession> SGMmSm;
	//int ranap_session_count;
	std::map<string, iupsTrxSession> SRanap;
	bool imsi_available;
	//Remaining flush happens from this id, and the first id is always 1
	//int last_gmm_session_flush_id;
	//int last_ranap_session_flush_id;
	bool trace_dump_active;


	_iupsGlobalSession()
		{ reset(); }

	_iupsGlobalSession(const _iupsGlobalSession& obj)
	{
		TotalBytesUL = obj.TotalBytesUL;
		TotalBytesDL = obj.TotalBytesDL;
		LastKnownRanapProcedureId = obj.LastKnownRanapProcedureId;
		strcpy(PLMNFirstId, obj.PLMNFirstId);
		strcpy(PLMNLastId, obj.PLMNLastId);
		strcpy(SACFirstId, obj.SACFirstId);
		strcpy(SACLastId, obj.SACLastId);
		strcpy(LACFirstId, obj.LACFirstId);
		strcpy(LACLastId, obj.LACLastId);
		strcpy(RACFirstId, obj.RACFirstId);
		strcpy(RACLastId, obj.RACLastId);
		strcpy(GlobalRNCId, obj.GlobalRNCId);
//		gmm_session_count = 0;
		SGMmSm = obj.SGMmSm;
//		ranap_session_count = 0;
		SRanap = obj.SRanap;
		imsi_available = obj.imsi_available;;
		//Remaining flush happens from this id, and the first id is always 1
//		last_gmm_session_flush_id = 1;
//		last_ranap_session_flush_id = 1;
		trace_dump_active = obj.trace_dump_active;
	}
	void copy(const _iupsGlobalSession* obj)
	{
		TotalBytesUL = obj->TotalBytesUL;
		TotalBytesDL = obj->TotalBytesDL;
		LastKnownRanapProcedureId = obj->LastKnownRanapProcedureId;
		strcpy(PLMNFirstId, obj->PLMNFirstId);
		strcpy(PLMNLastId, obj->PLMNLastId);
		strcpy(SACFirstId, obj->SACFirstId);
		strcpy(SACLastId, obj->SACLastId);
		strcpy(LACFirstId, obj->LACFirstId);
		strcpy(LACLastId, obj->LACLastId);
		strcpy(RACFirstId, obj->RACFirstId);
		strcpy(RACLastId, obj->RACLastId);
		strcpy(GlobalRNCId, obj->GlobalRNCId);
//		gmm_session_count = 0;
		SGMmSm = obj->SGMmSm;
//		ranap_session_count = 0;
		SRanap = obj->SRanap;
		imsi_available = obj->imsi_available;;
		//Remaining flush happens from this id, and the first id is always 1
//		last_gmm_session_flush_id = 1;
//		last_ranap_session_flush_id = 1;
		trace_dump_active = obj->trace_dump_active;
	}
	void operator=(const _iupsGlobalSession& obj)
	{
		TotalBytesUL = obj.TotalBytesUL;
		TotalBytesDL = obj.TotalBytesDL;
		LastKnownRanapProcedureId = obj.LastKnownRanapProcedureId;
		strcpy(PLMNFirstId, obj.PLMNFirstId);
		strcpy(PLMNLastId, obj.PLMNLastId);
		strcpy(SACFirstId, obj.SACFirstId);
		strcpy(SACLastId, obj.SACLastId);
		strcpy(LACFirstId, obj.LACFirstId);
		strcpy(LACLastId, obj.LACLastId);
		strcpy(RACFirstId, obj.RACFirstId);
		strcpy(RACLastId, obj.RACLastId);
		strcpy(GlobalRNCId, obj.GlobalRNCId);
//		gmm_session_count = 0;
		SGMmSm = obj.SGMmSm;
//		ranap_session_count = 0;
		SRanap = obj.SRanap;
		imsi_available = obj.imsi_available;;
		//Remaining flush happens from this id, and the first id is always 1
//		last_gmm_session_flush_id = 1;
//		last_ranap_session_flush_id = 1;
		trace_dump_active = obj.trace_dump_active;
	}

	void reset()
	{
		TotalBytesUL = 0;
		TotalBytesDL = 0;
		LastKnownRanapProcedureId = -1;
		PLMNFirstId[0] = 0;
		PLMNLastId[0] = 0;
		SACFirstId[0] = 0;
		SACLastId[0] = 0;
		LACFirstId[0] = 0;
		LACLastId[0] = 0;
		RACFirstId[0] = 0;
		RACLastId[0] = 0;
		GlobalRNCId[0] = 0;
//		gmm_session_count = 0;
		SGMmSm.clear();
//		ranap_session_count = 0;
		SRanap.clear();
		imsi_available = false;;
		//Remaining flush happens from this id, and the first id is always 1
//		last_gmm_session_flush_id = 1;
//		last_ranap_session_flush_id = 1;
		trace_dump_active = false;
	}

}iupsGlobalSession;


//namespace IUPSFlushMap {
//extern std::map<ULONG, iupsSession> iupsEndSessionMap_0;
//extern std::map<ULONG, iupsSession> iupsEndSessionMap_1;
//extern std::map<ULONG, iupsSession> iupsEndSessionMap_2;
//extern std::map<ULONG, iupsSession> iupsEndSessionMap_3;
//extern std::map<ULONG, iupsSession> iupsEndSessionMap_4;
//extern std::map<ULONG, iupsSession> iupsEndSessionMap_5;
//extern std::map<ULONG, iupsSession> iupsEndSessionMap_6;
//extern std::map<ULONG, iupsSession> iupsEndSessionMap_7;
//extern std::map<ULONG, iupsSession> iupsEndSessionMap_8;
//extern std::map<ULONG, iupsSession> iupsEndSessionMap_9;
//
//extern ULONG iupsEndSessionMAPCounter_0;
//extern ULONG iupsEndSessionMAPCounter_1;
//extern ULONG iupsEndSessionMAPCounter_2;
//extern ULONG iupsEndSessionMAPCounter_3;
//extern ULONG iupsEndSessionMAPCounter_4;
//extern ULONG iupsEndSessionMAPCounter_5;
//extern ULONG iupsEndSessionMAPCounter_6;
//extern ULONG iupsEndSessionMAPCounter_7;
//extern ULONG iupsEndSessionMAPCounter_8;
//extern ULONG iupsEndSessionMAPCounter_9;
//}

namespace IUPSGlobal {

	extern int pcap_counter;
	extern std::map<std::string, std::string> TMSI_IMSI_MAP;
	extern std::map<std::string, std::string> IMSI_TMSI_MAP;

	extern int IMSI_TMSI_MAP_SIZE;
	extern int TMSI_IMSI_MAP_SIZE;

	extern const char *ID_Val_String[285];
	extern const char *Procedure_Val_String[48];
	extern const char *Ranap_ID_Val_String[280];
	extern const char *Attach_Type_Val_String[6];
	extern const char *Attach_Result_Val_String[5];
	extern const char *Detach_Type_MS_NW_Val_String[5];
	extern const char *Detach_Type_NW_MS_Val_String[5];
	extern const char *Detach_Power_Off_Type_MS_NW_Val_String[5];
	extern const char *RA_Update_Type_Val_String[5];
	extern const char *Mobile_Id_Type_Val_String[7];
	extern const char *IMEISV_Type_Val_String[3];
	extern const char *PD_Val_String[15];
	extern const char *MM_SM_Message_Id_Val_String[];
	extern const char *MM_Cause_Codes_Val_String[];
	extern const char *SM_Cause_Codes_Val_String[];
	extern const char *IUPS_MSG_DIR[];
}


namespace IUPSFlushRepository {
		extern std::map<uint32_t, string> iupsFlushMap_sm_0_t_0;
		extern std::map<uint32_t, string> iupsFlushMap_sm_0_t_1;
		extern std::map<uint32_t, string> iupsFlushMap_sm_0_t_2;
		extern std::map<uint32_t, string> iupsFlushMap_sm_0_t_3;
		extern std::map<uint32_t, string> iupsFlushMap_sm_0_t_4;
		extern std::map<uint32_t, string> iupsFlushMap_sm_0_t_5;
		extern std::map<uint32_t, string> iupsFlushMap_sm_0_t_6;
		extern std::map<uint32_t, string> iupsFlushMap_sm_0_t_7;
		extern std::map<uint32_t, string> iupsFlushMap_sm_0_t_8;
		extern std::map<uint32_t, string> iupsFlushMap_sm_0_t_9;

		extern int iupsFlushMap_sm_0_t_0_cnt;
		extern int iupsFlushMap_sm_0_t_1_cnt;
		extern int iupsFlushMap_sm_0_t_2_cnt;
		extern int iupsFlushMap_sm_0_t_3_cnt;
		extern int iupsFlushMap_sm_0_t_4_cnt;
		extern int iupsFlushMap_sm_0_t_5_cnt;
		extern int iupsFlushMap_sm_0_t_6_cnt;
		extern int iupsFlushMap_sm_0_t_7_cnt;
		extern int iupsFlushMap_sm_0_t_8_cnt;
		extern int iupsFlushMap_sm_0_t_9_cnt;
}

namespace IUPSZmqFlushStore {
	extern int zmq_flush_t_index;
	extern std::string zmq_flush_map_iups_t_0[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE];
	extern std::string zmq_flush_map_iups_t_1[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE];
	extern std::string zmq_flush_map_iups_t_2[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE];
	extern std::string zmq_flush_map_iups_t_3[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE];
	extern std::string zmq_flush_map_iups_t_4[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE];
	extern std::string zmq_flush_map_iups_t_5[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE];
	extern std::string zmq_flush_map_iups_t_6[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE];
	extern std::string zmq_flush_map_iups_t_7[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE];
	extern std::string zmq_flush_map_iups_t_8[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE];
	extern std::string zmq_flush_map_iups_t_9[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE];

	extern int zmq_flush_map_iups_t_0_cnt;
	extern int zmq_flush_map_iups_t_1_cnt;
	extern int zmq_flush_map_iups_t_2_cnt;
	extern int zmq_flush_map_iups_t_3_cnt;
	extern int zmq_flush_map_iups_t_4_cnt;
	extern int zmq_flush_map_iups_t_5_cnt;
	extern int zmq_flush_map_iups_t_6_cnt;
	extern int zmq_flush_map_iups_t_7_cnt;
	extern int zmq_flush_map_iups_t_8_cnt;
	extern int zmq_flush_map_iups_t_9_cnt;
}
#endif /* PLUGINS_IUPS_SRC_IUPSGLOBAL_H_ */
