/*
 * SCCPGlobal.h
 *
 *  Created on: 14-Jul-2016
 *      Author: deb
 */

#ifndef PLUGINS_SCCP_SRC_SCCPCONS_H_
#define PLUGINS_SCCP_SRC_SCCPCONS_H_

#include "IUPSGlobal.h"
#include "IPGlobal.h"

namespace SCCPGlobal{

	extern int SCCPSessionCnt;
	extern int SCCPKeyMap1Cnt;
	extern int SCCPKeyMap2Cnt;
	extern int SCCPImsiTmsiMaoCnt;

	extern int COL_DLR;
	extern int COL_IMSI;
	extern int COL_TMSI;
	extern int COL_IMEI;
	extern int COL_MSISDN;
	extern int COL_RLSD;
	extern const char *SCCP_REL_CAUSE_Val_String[17];
	extern const char *SCCP_TYPE_Val_String[21];


}

typedef struct _sccpSession
{
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
	char		SessionId[40];
	uint64_t 	StartTimeEpochMicroSec;
	uint64_t 	EndTimeEpochMicroSec;
	uint64_t	LastUpdateTimeEpcohMicroSec;
	char		sourceMacAddr[MAC_ADDR_LEN];
	char		destMacAddr[MAC_ADDR_LEN];
	uint32_t 	SourceIP;
	uint32_t 	DestinationIP;
	uint32_t	TotalBytesUL;
	uint32_t	TotalBytesDL;
	uint16_t 	sccp_vlanId;
	bool 		SessionStartDirUp;
	int 		OPC;
	int 		DPC;
	char 		Slr[10];
	char 		Dlr[10];
	int			SCCPMsgId;
	char		SCCPMsgDesc[DESC_LEN];
	int 		RelCause;
	char 		IMSI[IMSI_LEN];
	char 		TMSI[IMSI_LEN];
	char 		IMEI[IMEI_LEN];
	char 		MSISDN[MSISDN_LEN];
	bool 		sccp_imsiAvailable;
	bool		sccp_session_end;
	bool 		trace_dump_active;

	long		frameSizeBytesUp;
	long		frameSizeBytesDn;

	uint16_t			iups_reqPdp_Mbrupl;
	uint16_t			iups_reqPdp_Mbrdnl;
	uint16_t			iups_rspPdp_Mbrupl;
	uint16_t			iups_rspPdp_Mbrdnl;
	uint16_t			iups_Ext_Mbrupl;

	iupsGlobalSession *pIupsGlbSession;

	_sccpSession()
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
		StartTimeEpochMicroSec = 0;
		EndTimeEpochMicroSec = 0;
		LastUpdateTimeEpcohMicroSec = 0;
	    sourceMacAddr[0] = 0;
	    destMacAddr[0] = 0;
		SourceIP = 0;
		DestinationIP = 0;
		TotalBytesUL = 0;
		TotalBytesDL = 0;
		sccp_vlanId = 0;
		SessionStartDirUp = false;
		OPC = 0;
		DPC = 0;
		Slr[0] = 0;
		Dlr[0] = 0;
		SCCPMsgId = -1;
		SCCPMsgDesc[0] = 0;
		RelCause = -1;
		IMSI[0] = 0;
		IMEI[0] = 0;
		TMSI[0] = 0;
		MSISDN[0] = 0;
		sccp_imsiAvailable = false;
		sccp_session_end = false;
		trace_dump_active = false;
		pIupsGlbSession = NULL;
		frameSizeBytesUp = 0;
		frameSizeBytesDn = 0;

		iups_reqPdp_Mbrupl = 0;
		iups_reqPdp_Mbrdnl = 0;
		iups_rspPdp_Mbrupl = 0;
		iups_rspPdp_Mbrdnl = 0;
		iups_Ext_Mbrupl = 0;

	}

	void set(const _sccpSession *obj)
	{
		sccp_cr = obj->sccp_cr;
		CRTimeEpochMicroSec = obj->CRTimeEpochMicroSec;
		sccp_cc = obj->sccp_cc;
		CCTimeEpochMicroSec = obj->CCTimeEpochMicroSec;
		sccp_dt = obj->sccp_dt;
		DTTimeEpochMicroSec = obj->DTTimeEpochMicroSec;
		sccp_rlsd = obj->sccp_rlsd;
		RLSDTimeEpochMicroSec = obj->RLSDTimeEpochMicroSec;
		sccp_rlc = obj->sccp_rlc;
		RLCTimeEpochMicroSec = obj->RLCTimeEpochMicroSec;
		strcpy(this->SessionId, obj->SessionId);
		this->StartTimeEpochMicroSec = obj->StartTimeEpochMicroSec;
		this->EndTimeEpochMicroSec = obj->EndTimeEpochMicroSec;
		this->LastUpdateTimeEpcohMicroSec = obj->LastUpdateTimeEpcohMicroSec;
	    strcpy(this->sourceMacAddr, obj->sourceMacAddr);
	    strcpy(this->destMacAddr, obj->destMacAddr);
		this->SourceIP = obj->SourceIP;
		this->DestinationIP = obj->DestinationIP;
		this->TotalBytesUL = obj->TotalBytesUL;
		this->TotalBytesDL = obj->TotalBytesDL;
		this->sccp_vlanId = obj->sccp_vlanId;
		this->SessionStartDirUp = obj->SessionStartDirUp;
		this->OPC = obj->OPC;
		this->DPC = obj->DPC;
		strcpy(this->Slr, obj->Slr);
		strcpy(this->Dlr, obj->Dlr);
		this->SCCPMsgId = obj->SCCPMsgId;
		strcpy(this->SCCPMsgDesc, obj->SCCPMsgDesc);
		this->RelCause = obj->RelCause;
		strcpy(this->IMSI, obj->IMSI);
		strcpy(this->IMEI, obj->IMEI);
		strcpy(this->TMSI, obj->TMSI);
		strcpy(this->MSISDN, obj->MSISDN);
		this->sccp_imsiAvailable = obj->sccp_imsiAvailable;
		this->sccp_session_end = obj->sccp_session_end;
		this->trace_dump_active = obj->trace_dump_active;
		this->pIupsGlbSession = obj->pIupsGlbSession;
		this->frameSizeBytesUp = obj->frameSizeBytesUp;
		this->frameSizeBytesDn = obj->frameSizeBytesDn;

		this->iups_reqPdp_Mbrupl = obj->iups_reqPdp_Mbrupl;
		this->iups_reqPdp_Mbrdnl = obj->iups_reqPdp_Mbrdnl;
		this->iups_rspPdp_Mbrupl = obj->iups_rspPdp_Mbrupl;
		this->iups_rspPdp_Mbrdnl = obj->iups_rspPdp_Mbrdnl;
		this->iups_Ext_Mbrupl = obj->iups_Ext_Mbrupl;
	}

	_sccpSession(const _sccpSession& obj)
	{
		sccp_cr = obj.sccp_cr;
		CRTimeEpochMicroSec = obj.CRTimeEpochMicroSec;
		sccp_cc = obj.sccp_cc;
		CCTimeEpochMicroSec = obj.CCTimeEpochMicroSec;
		sccp_dt = obj.sccp_dt;
		DTTimeEpochMicroSec = obj.DTTimeEpochMicroSec;
		sccp_rlsd = obj.sccp_rlsd;
		RLSDTimeEpochMicroSec = obj.RLSDTimeEpochMicroSec;
		sccp_rlc = obj.sccp_rlc;
		RLCTimeEpochMicroSec = obj.RLCTimeEpochMicroSec;
		strcpy(SessionId, obj.SessionId);
		StartTimeEpochMicroSec = obj.StartTimeEpochMicroSec;
		EndTimeEpochMicroSec = obj.EndTimeEpochMicroSec;
		LastUpdateTimeEpcohMicroSec = obj.LastUpdateTimeEpcohMicroSec;
		strcpy(sourceMacAddr, obj.sourceMacAddr);
		strcpy(destMacAddr, obj.destMacAddr);
		SourceIP = obj.SourceIP;
		DestinationIP = obj.DestinationIP;
		TotalBytesUL = obj.TotalBytesUL;
		TotalBytesDL = obj.TotalBytesDL;
		sccp_vlanId = obj.sccp_vlanId;
		SessionStartDirUp = false;
		OPC = obj.OPC;
		DPC = obj.DPC;
		strcpy(Slr, obj.Slr);
		strcpy(Dlr, obj.Dlr);
		SCCPMsgId = -1;
		strcpy(SCCPMsgDesc, obj.SCCPMsgDesc);
		RelCause = obj.RelCause;
		strcpy(IMSI, obj.IMSI);
		strcpy(IMEI, obj.IMEI);
		strcpy(TMSI, obj.TMSI);
		strcpy(MSISDN, obj.MSISDN);
		sccp_imsiAvailable = obj.sccp_imsiAvailable;
		sccp_session_end = obj.sccp_session_end;
		trace_dump_active = obj.trace_dump_active;
		pIupsGlbSession = obj.pIupsGlbSession;
		frameSizeBytesUp = obj.frameSizeBytesUp;
		frameSizeBytesDn = obj.frameSizeBytesDn;

		iups_reqPdp_Mbrupl = obj.iups_reqPdp_Mbrupl;
		iups_reqPdp_Mbrdnl = obj.iups_reqPdp_Mbrdnl;
		iups_rspPdp_Mbrupl = obj.iups_rspPdp_Mbrupl;
		iups_rspPdp_Mbrdnl = obj.iups_rspPdp_Mbrdnl;
		iups_Ext_Mbrupl = obj.iups_Ext_Mbrupl;
	}

	void copy(const _sccpSession* obj)
	{
		sccp_cr = obj->sccp_cr;
		CRTimeEpochMicroSec = obj->CRTimeEpochMicroSec;
		sccp_cc = obj->sccp_cc;
		CCTimeEpochMicroSec = obj->CCTimeEpochMicroSec;
		sccp_dt = obj->sccp_dt;
		DTTimeEpochMicroSec = obj->DTTimeEpochMicroSec;
		sccp_rlsd = obj->sccp_rlsd;
		RLSDTimeEpochMicroSec = obj->RLSDTimeEpochMicroSec;
		strcpy(SessionId, obj->SessionId);
		StartTimeEpochMicroSec = obj->StartTimeEpochMicroSec;
		EndTimeEpochMicroSec = obj->EndTimeEpochMicroSec;
		LastUpdateTimeEpcohMicroSec = obj->LastUpdateTimeEpcohMicroSec;
		strcpy(sourceMacAddr, obj->sourceMacAddr);
		strcpy(destMacAddr, obj->destMacAddr);
		SourceIP = obj->SourceIP;
		DestinationIP = obj->DestinationIP;
		TotalBytesUL = obj->TotalBytesUL;
		TotalBytesDL = obj->TotalBytesDL;
		sccp_vlanId = obj->sccp_vlanId;
		SessionStartDirUp = false;
		OPC = obj->OPC;
		DPC = obj->DPC;
		strcpy(Slr, obj->Slr);
		strcpy(Dlr, obj->Dlr);
		SCCPMsgId = -1;
		strcpy(SCCPMsgDesc, obj->SCCPMsgDesc);
		RelCause = obj->RelCause;
		strcpy(IMSI, obj->IMSI);
		strcpy(IMEI, obj->IMEI);
		strcpy(TMSI, obj->TMSI);
		strcpy(MSISDN, obj->MSISDN);
		sccp_imsiAvailable = obj->sccp_imsiAvailable;
		sccp_session_end = obj->sccp_session_end;
		trace_dump_active = obj->trace_dump_active;
		pIupsGlbSession = obj->pIupsGlbSession;
		frameSizeBytesUp = obj->frameSizeBytesUp;
		frameSizeBytesDn = obj->frameSizeBytesDn;
		iups_reqPdp_Mbrupl = obj->iups_reqPdp_Mbrupl;
		iups_reqPdp_Mbrdnl = obj->iups_reqPdp_Mbrdnl;
		iups_rspPdp_Mbrupl = obj->iups_rspPdp_Mbrupl;
		iups_rspPdp_Mbrdnl = obj->iups_rspPdp_Mbrdnl;
		iups_Ext_Mbrupl = obj->iups_Ext_Mbrupl;
	}

	void operator=(const _sccpSession& obj)
	{
		sccp_cr = obj.sccp_cr;
		CRTimeEpochMicroSec = obj.CRTimeEpochMicroSec;
		sccp_cc = obj.sccp_cc;
		CCTimeEpochMicroSec = obj.CCTimeEpochMicroSec;
		sccp_dt = obj.sccp_dt;
		DTTimeEpochMicroSec = obj.DTTimeEpochMicroSec;
		sccp_rlsd = obj.sccp_rlsd;
		RLSDTimeEpochMicroSec = obj.RLSDTimeEpochMicroSec;
		sccp_rlc = obj.sccp_rlc;
		RLCTimeEpochMicroSec = obj.RLCTimeEpochMicroSec;
		strcpy(SessionId, obj.SessionId);
		StartTimeEpochMicroSec = obj.StartTimeEpochMicroSec;
		EndTimeEpochMicroSec = obj.EndTimeEpochMicroSec;
		LastUpdateTimeEpcohMicroSec = obj.LastUpdateTimeEpcohMicroSec;
		strcpy(sourceMacAddr, obj.sourceMacAddr);
		strcpy(destMacAddr, obj.destMacAddr);
		SourceIP = obj.SourceIP;
		DestinationIP = obj.DestinationIP;
		TotalBytesUL = obj.TotalBytesUL;
		TotalBytesDL = obj.TotalBytesDL;
		sccp_vlanId = obj.sccp_vlanId;
		SessionStartDirUp = false;
		OPC = obj.OPC;
		DPC = obj.DPC;
		strcpy(Slr, obj.Slr);
		strcpy(Dlr, obj.Dlr);
		SCCPMsgId = -1;
		strcpy(SCCPMsgDesc, obj.SCCPMsgDesc);
		RelCause = obj.RelCause;
		strcpy(IMSI, obj.IMSI);
		strcpy(IMEI, obj.IMEI);
		strcpy(TMSI, obj.TMSI);
		strcpy(MSISDN, obj.MSISDN);
		sccp_imsiAvailable = obj.sccp_imsiAvailable;
		sccp_session_end = obj.sccp_session_end;
		trace_dump_active = obj.trace_dump_active;
		pIupsGlbSession = obj.pIupsGlbSession;
		frameSizeBytesUp = obj.frameSizeBytesUp;
		frameSizeBytesDn = obj.frameSizeBytesDn;
		iups_reqPdp_Mbrupl = obj.iups_reqPdp_Mbrupl;
		iups_reqPdp_Mbrdnl = obj.iups_reqPdp_Mbrdnl;
		iups_rspPdp_Mbrupl = obj.iups_rspPdp_Mbrupl;
		iups_rspPdp_Mbrdnl = obj.iups_rspPdp_Mbrdnl;
		iups_Ext_Mbrupl = obj.iups_Ext_Mbrupl;
	}
}sccpSession;


namespace SCCPSMStore {

	extern std::map<int, MPacket> sccp_msg_sm_0_i_0_r_0_t_0;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_0_r_0_t_1;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_0_r_0_t_2;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_0_r_0_t_3;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_0_r_0_t_4;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_0_r_0_t_5;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_0_r_0_t_6;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_0_r_0_t_7;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_0_r_0_t_8;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_0_r_0_t_9;
	extern bool sccp_msg_sm_0_i_0_r_0_t_0_busy;
	extern bool sccp_msg_sm_0_i_0_r_0_t_1_busy;
	extern bool sccp_msg_sm_0_i_0_r_0_t_2_busy;
	extern bool sccp_msg_sm_0_i_0_r_0_t_3_busy;
	extern bool sccp_msg_sm_0_i_0_r_0_t_4_busy;
	extern bool sccp_msg_sm_0_i_0_r_0_t_5_busy;
	extern bool sccp_msg_sm_0_i_0_r_0_t_6_busy;
	extern bool sccp_msg_sm_0_i_0_r_0_t_7_busy;
	extern bool sccp_msg_sm_0_i_0_r_0_t_8_busy;
	extern bool sccp_msg_sm_0_i_0_r_0_t_9_busy;
	extern int sccp_msg_sm_0_i_0_r_0_t_0_cnt;
	extern int sccp_msg_sm_0_i_0_r_0_t_1_cnt;
	extern int sccp_msg_sm_0_i_0_r_0_t_2_cnt;
	extern int sccp_msg_sm_0_i_0_r_0_t_3_cnt;
	extern int sccp_msg_sm_0_i_0_r_0_t_4_cnt;
	extern int sccp_msg_sm_0_i_0_r_0_t_5_cnt;
	extern int sccp_msg_sm_0_i_0_r_0_t_6_cnt;
	extern int sccp_msg_sm_0_i_0_r_0_t_7_cnt;
	extern int sccp_msg_sm_0_i_0_r_0_t_8_cnt;
	extern int sccp_msg_sm_0_i_0_r_0_t_9_cnt;

	extern std::map<int, MPacket> sccp_msg_sm_0_i_0_r_1_t_0;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_0_r_1_t_1;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_0_r_1_t_2;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_0_r_1_t_3;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_0_r_1_t_4;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_0_r_1_t_5;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_0_r_1_t_6;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_0_r_1_t_7;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_0_r_1_t_8;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_0_r_1_t_9;
	extern bool sccp_msg_sm_0_i_0_r_1_t_0_busy;
	extern bool sccp_msg_sm_0_i_0_r_1_t_1_busy;
	extern bool sccp_msg_sm_0_i_0_r_1_t_2_busy;
	extern bool sccp_msg_sm_0_i_0_r_1_t_3_busy;
	extern bool sccp_msg_sm_0_i_0_r_1_t_4_busy;
	extern bool sccp_msg_sm_0_i_0_r_1_t_5_busy;
	extern bool sccp_msg_sm_0_i_0_r_1_t_6_busy;
	extern bool sccp_msg_sm_0_i_0_r_1_t_7_busy;
	extern bool sccp_msg_sm_0_i_0_r_1_t_8_busy;
	extern bool sccp_msg_sm_0_i_0_r_1_t_9_busy;
	extern int sccp_msg_sm_0_i_0_r_1_t_0_cnt;
	extern int sccp_msg_sm_0_i_0_r_1_t_1_cnt;
	extern int sccp_msg_sm_0_i_0_r_1_t_2_cnt;
	extern int sccp_msg_sm_0_i_0_r_1_t_3_cnt;
	extern int sccp_msg_sm_0_i_0_r_1_t_4_cnt;
	extern int sccp_msg_sm_0_i_0_r_1_t_5_cnt;
	extern int sccp_msg_sm_0_i_0_r_1_t_6_cnt;
	extern int sccp_msg_sm_0_i_0_r_1_t_7_cnt;
	extern int sccp_msg_sm_0_i_0_r_1_t_8_cnt;
	extern int sccp_msg_sm_0_i_0_r_1_t_9_cnt;


	extern std::map<int, MPacket> sccp_msg_sm_0_i_1_r_0_t_0;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_1_r_0_t_1;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_1_r_0_t_2;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_1_r_0_t_3;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_1_r_0_t_4;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_1_r_0_t_5;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_1_r_0_t_6;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_1_r_0_t_7;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_1_r_0_t_8;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_1_r_0_t_9;
	extern bool sccp_msg_sm_0_i_1_r_0_t_0_busy;
	extern bool sccp_msg_sm_0_i_1_r_0_t_1_busy;
	extern bool sccp_msg_sm_0_i_1_r_0_t_2_busy;
	extern bool sccp_msg_sm_0_i_1_r_0_t_3_busy;
	extern bool sccp_msg_sm_0_i_1_r_0_t_4_busy;
	extern bool sccp_msg_sm_0_i_1_r_0_t_5_busy;
	extern bool sccp_msg_sm_0_i_1_r_0_t_6_busy;
	extern bool sccp_msg_sm_0_i_1_r_0_t_7_busy;
	extern bool sccp_msg_sm_0_i_1_r_0_t_8_busy;
	extern bool sccp_msg_sm_0_i_1_r_0_t_9_busy;
	extern int sccp_msg_sm_0_i_1_r_0_t_0_cnt;
	extern int sccp_msg_sm_0_i_1_r_0_t_1_cnt;
	extern int sccp_msg_sm_0_i_1_r_0_t_2_cnt;
	extern int sccp_msg_sm_0_i_1_r_0_t_3_cnt;
	extern int sccp_msg_sm_0_i_1_r_0_t_4_cnt;
	extern int sccp_msg_sm_0_i_1_r_0_t_5_cnt;
	extern int sccp_msg_sm_0_i_1_r_0_t_6_cnt;
	extern int sccp_msg_sm_0_i_1_r_0_t_7_cnt;
	extern int sccp_msg_sm_0_i_1_r_0_t_8_cnt;
	extern int sccp_msg_sm_0_i_1_r_0_t_9_cnt;

	extern std::map<int, MPacket> sccp_msg_sm_0_i_1_r_1_t_0;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_1_r_1_t_1;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_1_r_1_t_2;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_1_r_1_t_3;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_1_r_1_t_4;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_1_r_1_t_5;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_1_r_1_t_6;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_1_r_1_t_7;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_1_r_1_t_8;
	extern std::map<int, MPacket> sccp_msg_sm_0_i_1_r_1_t_9;
	extern bool sccp_msg_sm_0_i_1_r_1_t_0_busy;
	extern bool sccp_msg_sm_0_i_1_r_1_t_1_busy;
	extern bool sccp_msg_sm_0_i_1_r_1_t_2_busy;
	extern bool sccp_msg_sm_0_i_1_r_1_t_3_busy;
	extern bool sccp_msg_sm_0_i_1_r_1_t_4_busy;
	extern bool sccp_msg_sm_0_i_1_r_1_t_5_busy;
	extern bool sccp_msg_sm_0_i_1_r_1_t_6_busy;
	extern bool sccp_msg_sm_0_i_1_r_1_t_7_busy;
	extern bool sccp_msg_sm_0_i_1_r_1_t_8_busy;
	extern bool sccp_msg_sm_0_i_1_r_1_t_9_busy;
	extern int sccp_msg_sm_0_i_1_r_1_t_0_cnt;
	extern int sccp_msg_sm_0_i_1_r_1_t_1_cnt;
	extern int sccp_msg_sm_0_i_1_r_1_t_2_cnt;
	extern int sccp_msg_sm_0_i_1_r_1_t_3_cnt;
	extern int sccp_msg_sm_0_i_1_r_1_t_4_cnt;
	extern int sccp_msg_sm_0_i_1_r_1_t_5_cnt;
	extern int sccp_msg_sm_0_i_1_r_1_t_6_cnt;
	extern int sccp_msg_sm_0_i_1_r_1_t_7_cnt;
	extern int sccp_msg_sm_0_i_1_r_1_t_8_cnt;
	extern int sccp_msg_sm_0_i_1_r_1_t_9_cnt;

	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_0_t_0;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_0_t_1;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_0_t_2;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_0_t_3;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_0_t_4;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_0_t_5;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_0_t_6;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_0_t_7;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_0_t_8;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_0_t_9;

	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_1_t_0;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_1_t_1;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_1_t_2;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_1_t_3;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_1_t_4;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_1_t_5;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_1_t_6;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_1_t_7;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_1_t_8;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_1_t_9;

	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_0_t_0;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_0_t_1;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_0_t_2;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_0_t_3;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_0_t_4;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_0_t_5;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_0_t_6;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_0_t_7;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_0_t_8;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_0_t_9;

	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_1_t_0;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_1_t_1;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_1_t_2;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_1_t_3;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_1_t_4;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_1_t_5;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_1_t_6;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_1_t_7;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_1_t_8;
	extern std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_1_t_9;

}

#endif /* PLUGINS_SCCP_SRC_SCCPCONS_H_ */
