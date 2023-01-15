/*
 * SCCPGlobal.cpp
 *
 *  Created on: 14-Jul-2016
 *      Author: deb
 */

#include "SCCPGlobal.h"

namespace SCCPGlobal{

	int SCCPSessionCnt = 0;
	int SCCPKeyMap1Cnt = 0;
	int SCCPKeyMap2Cnt = 0;
	int SCCPImsiTmsiMaoCnt = 0;

	//int MM_SM_MESSAGE_ID_ARRAY_SIZE = 94;

//	char ProbeId[20] = "IuPS-MP#1";
//	char ProbeDesc[50] = "Pinnacle IuPS Probe v3.0.5";
//	char ProbeIP[30] = "10.202.5.62";
//	char ProbeProtocolDesc[50] = "IuPS [3GPP Rel-12]";
//	char ProbeXDRVer[15] = "IuPS-3.0.5";
//
//	//Only for RANAP XML read
//	std::map<int, std::string> RANAP_XML_FILE;
//
//	bool DEBUG = false;
//	bool TRACE = false;
//	bool LOG  = false;
//	bool WARNING = false;
//	bool ERROR = false;
//	bool DEV = false;
//	bool XDRPRINT = true;
//
//	//bool ONLY_MEMORY_NO_FILE = true;
//	bool WRITE_RELEASE_DR = false;
//	bool WRITE_SESSION_DR = false;
//	bool WRITE_SESSION_SDR = false;
//	bool WRITE_XDR = true;
//	bool PRINT_XDR_ON_SCREEN = false;
//	bool WRITE_CUSTOM_TDR = true;
//	bool WRITE_CUSTOM_TDR_CSV = false;
//	bool WRITE_MARBEN_TRACE_XML = false;
//	bool WRITE_PCAP_TO_XML = false;
//
//	bool SEND_ZMQ = true;
//
	int COL_SLR = 1;
	int COL_DLR = 2;
	int COL_IMSI = 3;
	int COL_TMSI = 4;
	int COL_IMEI = 5;
	int COL_MSISDN = 6;
	int COL_RLSD = 7;
//
//	long process_start_time_sec = 0;
//	unsigned int xdr_custom_counter = 0;
//	unsigned int sccp_packet_counter = 0;
//	unsigned int total_sessions = 0;
//	unsigned int active_sessions = 0;
//	unsigned int max_gmm_session_seen = 0;
//	unsigned int max_ranap_session_seen = 0;
//	unsigned int memory_usage_mb = 0;
//	int avg_mem_per_session_kb = 0;
//	int imsi_map_elements = 0;
//	int imsi_map_size = 0;
//	int sccp_map_elements = 0;
//	int sccp_map_size = 0;
//
//	int IMSI_LENGTH_MIN = 15;
//	int IMEI_LENGTH_MIN = 14;
//
//	char FLOW_DIR_SGSN_RNC[10] = "SGSN->RNC";
//	char FLOW_DIR_RNC_SGSN[10] = "RNC->SGSN";
//
//	int RANAP_SESSION = 1;
//	int GMM_SESSION = 2;
//	const char *SESSION_DESC[4]={
//			"",
//			"RANAP_SESSION",
//			"GMM_SESSION"
//	};
//
//	bool TRACE_ENABLED = false;
//	const char *TRACE_SESSION[] = {};
//	const char *TRACE_IMSI[3] = {"404220003030015","404220563211573", "404220512345678"};
//	std::map<std::string,int> TRACE_IMISLIST_MAP;


	const char *SCCP_TYPE_Val_String[21]={
			"",
			"CR (Connection Request)",
			"CC (Connection Confirm)",
			"CREF (Connection Refused)",
			"RLSD (Released)",
			"RLC (Release Complete)",
			"DT1 (Data Form 1)",
			"DT2 (Data Form 2)",
			"AK (Data Acknowledgment)",
			"UDT (Unitdata)",
			"UDTS (Unitdata Service)",
			"ED (Expedited Data)",
			"EA (Expedited Data Acknowledgment)",
			"RSR (Reset Request)",
			"RSC (Reset Confirm)",
			"ERR (Protocol Data Unit Error)",
			"IT (Inactivity Test)",
			"XUDT (Extended Unitdata)",
			"XUDTS (Extended Unitdata Service)",
			"LUDT (Long Unitdata)",
			"LUDTS (Long Unitdata Service)"
	};

	const char *SCCP_REL_CAUSE_Val_String[17]={
			"End user originated",
			"End user congestion",
			"End user failure",
			"SCCP user originated",
			"Remote procedure error",
			"Inconsistent connection data",
			"Access failure",
			"Access congestion",
			"Subsystem failure",
			"Subsystem congestion",
			"MTP failure",
			"Network congestion",
			"Expiration of reset timer",
			"Expiration of receive inactivity timer",
			"Reserved",
			"Unqualified",
			"SCCP failure"
	};

}


namespace SCCPSMStore {

	std::map<int, MPacket> sccp_msg_sm_0_i_0_r_0_t_0;
	std::map<int, MPacket> sccp_msg_sm_0_i_0_r_0_t_1;
	std::map<int, MPacket> sccp_msg_sm_0_i_0_r_0_t_2;
	std::map<int, MPacket> sccp_msg_sm_0_i_0_r_0_t_3;
	std::map<int, MPacket> sccp_msg_sm_0_i_0_r_0_t_4;
	std::map<int, MPacket> sccp_msg_sm_0_i_0_r_0_t_5;
	std::map<int, MPacket> sccp_msg_sm_0_i_0_r_0_t_6;
	std::map<int, MPacket> sccp_msg_sm_0_i_0_r_0_t_7;
	std::map<int, MPacket> sccp_msg_sm_0_i_0_r_0_t_8;
	std::map<int, MPacket> sccp_msg_sm_0_i_0_r_0_t_9;
	bool sccp_msg_sm_0_i_0_r_0_t_0_busy = false;
	bool sccp_msg_sm_0_i_0_r_0_t_1_busy = false;
	bool sccp_msg_sm_0_i_0_r_0_t_2_busy = false;
	bool sccp_msg_sm_0_i_0_r_0_t_3_busy = false;
	bool sccp_msg_sm_0_i_0_r_0_t_4_busy = false;
	bool sccp_msg_sm_0_i_0_r_0_t_5_busy = false;
	bool sccp_msg_sm_0_i_0_r_0_t_6_busy = false;
	bool sccp_msg_sm_0_i_0_r_0_t_7_busy = false;
	bool sccp_msg_sm_0_i_0_r_0_t_8_busy = false;
	bool sccp_msg_sm_0_i_0_r_0_t_9_busy = false;
	int sccp_msg_sm_0_i_0_r_0_t_0_cnt = 0;
	int sccp_msg_sm_0_i_0_r_0_t_1_cnt = 0;
	int sccp_msg_sm_0_i_0_r_0_t_2_cnt = 0;
	int sccp_msg_sm_0_i_0_r_0_t_3_cnt = 0;
	int sccp_msg_sm_0_i_0_r_0_t_4_cnt = 0;
	int sccp_msg_sm_0_i_0_r_0_t_5_cnt = 0;
	int sccp_msg_sm_0_i_0_r_0_t_6_cnt = 0;
	int sccp_msg_sm_0_i_0_r_0_t_7_cnt = 0;
	int sccp_msg_sm_0_i_0_r_0_t_8_cnt = 0;
	int sccp_msg_sm_0_i_0_r_0_t_9_cnt = 0;

	std::map<int, MPacket> sccp_msg_sm_0_i_0_r_1_t_0;
	std::map<int, MPacket> sccp_msg_sm_0_i_0_r_1_t_1;
	std::map<int, MPacket> sccp_msg_sm_0_i_0_r_1_t_2;
	std::map<int, MPacket> sccp_msg_sm_0_i_0_r_1_t_3;
	std::map<int, MPacket> sccp_msg_sm_0_i_0_r_1_t_4;
	std::map<int, MPacket> sccp_msg_sm_0_i_0_r_1_t_5;
	std::map<int, MPacket> sccp_msg_sm_0_i_0_r_1_t_6;
	std::map<int, MPacket> sccp_msg_sm_0_i_0_r_1_t_7;
	std::map<int, MPacket> sccp_msg_sm_0_i_0_r_1_t_8;
	std::map<int, MPacket> sccp_msg_sm_0_i_0_r_1_t_9;
	bool sccp_msg_sm_0_i_0_r_1_t_0_busy = false;
	bool sccp_msg_sm_0_i_0_r_1_t_1_busy = false;
	bool sccp_msg_sm_0_i_0_r_1_t_2_busy = false;
	bool sccp_msg_sm_0_i_0_r_1_t_3_busy = false;
	bool sccp_msg_sm_0_i_0_r_1_t_4_busy = false;
	bool sccp_msg_sm_0_i_0_r_1_t_5_busy = false;
	bool sccp_msg_sm_0_i_0_r_1_t_6_busy = false;
	bool sccp_msg_sm_0_i_0_r_1_t_7_busy = false;
	bool sccp_msg_sm_0_i_0_r_1_t_8_busy = false;
	bool sccp_msg_sm_0_i_0_r_1_t_9_busy = false;
	int sccp_msg_sm_0_i_0_r_1_t_0_cnt = 0;
	int sccp_msg_sm_0_i_0_r_1_t_1_cnt = 0;
	int sccp_msg_sm_0_i_0_r_1_t_2_cnt = 0;
	int sccp_msg_sm_0_i_0_r_1_t_3_cnt = 0;
	int sccp_msg_sm_0_i_0_r_1_t_4_cnt = 0;
	int sccp_msg_sm_0_i_0_r_1_t_5_cnt = 0;
	int sccp_msg_sm_0_i_0_r_1_t_6_cnt = 0;
	int sccp_msg_sm_0_i_0_r_1_t_7_cnt = 0;
	int sccp_msg_sm_0_i_0_r_1_t_8_cnt = 0;
	int sccp_msg_sm_0_i_0_r_1_t_9_cnt = 0;


	std::map<int, MPacket> sccp_msg_sm_0_i_1_r_0_t_0;
	std::map<int, MPacket> sccp_msg_sm_0_i_1_r_0_t_1;
	std::map<int, MPacket> sccp_msg_sm_0_i_1_r_0_t_2;
	std::map<int, MPacket> sccp_msg_sm_0_i_1_r_0_t_3;
	std::map<int, MPacket> sccp_msg_sm_0_i_1_r_0_t_4;
	std::map<int, MPacket> sccp_msg_sm_0_i_1_r_0_t_5;
	std::map<int, MPacket> sccp_msg_sm_0_i_1_r_0_t_6;
	std::map<int, MPacket> sccp_msg_sm_0_i_1_r_0_t_7;
	std::map<int, MPacket> sccp_msg_sm_0_i_1_r_0_t_8;
	std::map<int, MPacket> sccp_msg_sm_0_i_1_r_0_t_9;
	bool sccp_msg_sm_0_i_1_r_0_t_0_busy = false;
	bool sccp_msg_sm_0_i_1_r_0_t_1_busy = false;
	bool sccp_msg_sm_0_i_1_r_0_t_2_busy = false;
	bool sccp_msg_sm_0_i_1_r_0_t_3_busy = false;
	bool sccp_msg_sm_0_i_1_r_0_t_4_busy = false;
	bool sccp_msg_sm_0_i_1_r_0_t_5_busy = false;
	bool sccp_msg_sm_0_i_1_r_0_t_6_busy = false;
	bool sccp_msg_sm_0_i_1_r_0_t_7_busy = false;
	bool sccp_msg_sm_0_i_1_r_0_t_8_busy = false;
	bool sccp_msg_sm_0_i_1_r_0_t_9_busy = false;
	int sccp_msg_sm_0_i_1_r_0_t_0_cnt = 0;
	int sccp_msg_sm_0_i_1_r_0_t_1_cnt = 0;
	int sccp_msg_sm_0_i_1_r_0_t_2_cnt = 0;
	int sccp_msg_sm_0_i_1_r_0_t_3_cnt = 0;
	int sccp_msg_sm_0_i_1_r_0_t_4_cnt = 0;
	int sccp_msg_sm_0_i_1_r_0_t_5_cnt = 0;
	int sccp_msg_sm_0_i_1_r_0_t_6_cnt = 0;
	int sccp_msg_sm_0_i_1_r_0_t_7_cnt = 0;
	int sccp_msg_sm_0_i_1_r_0_t_8_cnt = 0;
	int sccp_msg_sm_0_i_1_r_0_t_9_cnt = 0;

	std::map<int, MPacket> sccp_msg_sm_0_i_1_r_1_t_0;
	std::map<int, MPacket> sccp_msg_sm_0_i_1_r_1_t_1;
	std::map<int, MPacket> sccp_msg_sm_0_i_1_r_1_t_2;
	std::map<int, MPacket> sccp_msg_sm_0_i_1_r_1_t_3;
	std::map<int, MPacket> sccp_msg_sm_0_i_1_r_1_t_4;
	std::map<int, MPacket> sccp_msg_sm_0_i_1_r_1_t_5;
	std::map<int, MPacket> sccp_msg_sm_0_i_1_r_1_t_6;
	std::map<int, MPacket> sccp_msg_sm_0_i_1_r_1_t_7;
	std::map<int, MPacket> sccp_msg_sm_0_i_1_r_1_t_8;
	std::map<int, MPacket> sccp_msg_sm_0_i_1_r_1_t_9;
	bool sccp_msg_sm_0_i_1_r_1_t_0_busy = false;
	bool sccp_msg_sm_0_i_1_r_1_t_1_busy = false;
	bool sccp_msg_sm_0_i_1_r_1_t_2_busy = false;
	bool sccp_msg_sm_0_i_1_r_1_t_3_busy = false;
	bool sccp_msg_sm_0_i_1_r_1_t_4_busy = false;
	bool sccp_msg_sm_0_i_1_r_1_t_5_busy = false;
	bool sccp_msg_sm_0_i_1_r_1_t_6_busy = false;
	bool sccp_msg_sm_0_i_1_r_1_t_7_busy = false;
	bool sccp_msg_sm_0_i_1_r_1_t_8_busy = false;
	bool sccp_msg_sm_0_i_1_r_1_t_9_busy = false;
	int sccp_msg_sm_0_i_1_r_1_t_0_cnt = 0;
	int sccp_msg_sm_0_i_1_r_1_t_1_cnt = 0;
	int sccp_msg_sm_0_i_1_r_1_t_2_cnt = 0;
	int sccp_msg_sm_0_i_1_r_1_t_3_cnt = 0;
	int sccp_msg_sm_0_i_1_r_1_t_4_cnt = 0;
	int sccp_msg_sm_0_i_1_r_1_t_5_cnt = 0;
	int sccp_msg_sm_0_i_1_r_1_t_6_cnt = 0;
	int sccp_msg_sm_0_i_1_r_1_t_7_cnt = 0;
	int sccp_msg_sm_0_i_1_r_1_t_8_cnt = 0;
	int sccp_msg_sm_0_i_1_r_1_t_9_cnt = 0;

	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_0_t_0;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_0_t_1;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_0_t_2;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_0_t_3;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_0_t_4;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_0_t_5;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_0_t_6;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_0_t_7;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_0_t_8;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_0_t_9;

	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_1_t_0;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_1_t_1;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_1_t_2;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_1_t_3;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_1_t_4;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_1_t_5;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_1_t_6;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_1_t_7;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_1_t_8;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_0_r_1_t_9;

	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_0_t_0;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_0_t_1;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_0_t_2;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_0_t_3;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_0_t_4;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_0_t_5;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_0_t_6;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_0_t_7;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_0_t_8;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_0_t_9;

	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_1_t_0;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_1_t_1;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_1_t_2;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_1_t_3;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_1_t_4;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_1_t_5;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_1_t_6;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_1_t_7;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_1_t_8;
	std::map<uint64_t, SCTPChunkMap> sctpChunkMap_sm_0_i_1_r_1_t_9;


}

