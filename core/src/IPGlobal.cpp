/*
 * TCPGlobal.cpp
 *
 *  Created on: Nov 14, 2015
 *      Author: debashis
 */

#include "IPGlobal.h"

using namespace std;

namespace GContainer
{
	GConfig *config;
}

namespace ipRange{
	int totalIps;
	_ipRange ipRange[100];
}

namespace GTPStats {
	int unique_imsi_cnt = 0;

	uint64_t gtpc_pkt_cnt_i_0_r_0 = 0;
	uint64_t gtpc_pkt_cnt_i_0_r_1 = 0;
	uint64_t gtpc_pkt_cnt_i_0_r_2 = 0;
	uint64_t gtpc_pkt_cnt_i_0_r_3 = 0;

	uint64_t gtpc_pkt_cnt_i_1_r_0 = 0;
	uint64_t gtpc_pkt_cnt_i_1_r_1 = 0;
	uint64_t gtpc_pkt_cnt_i_1_r_2 = 0;
	uint64_t gtpc_pkt_cnt_i_1_r_3 = 0;

	uint64_t gtpc_pkt_cnt_i_2_r_0 = 0;
	uint64_t gtpc_pkt_cnt_i_2_r_1 = 0;
	uint64_t gtpc_pkt_cnt_i_2_r_2 = 0;
	uint64_t gtpc_pkt_cnt_i_2_r_3 = 0;

	uint64_t gtpc_pkt_cnt_i_3_r_0 = 0;
	uint64_t gtpc_pkt_cnt_i_3_r_1 = 0;
	uint64_t gtpc_pkt_cnt_i_3_r_2 = 0;
	uint64_t gtpc_pkt_cnt_i_3_r_3 = 0;

	uint64_t gtpu_pkt_cnt_i_0_r_0 = 0;
	uint64_t gtpu_pkt_cnt_i_0_r_1 = 0;
	uint64_t gtpu_pkt_cnt_i_0_r_2 = 0;
	uint64_t gtpu_pkt_cnt_i_0_r_3 = 0;

	uint64_t gtpu_pkt_cnt_i_1_r_0 = 0;
	uint64_t gtpu_pkt_cnt_i_1_r_1 = 0;
	uint64_t gtpu_pkt_cnt_i_1_r_2 = 0;
	uint64_t gtpu_pkt_cnt_i_1_r_3 = 0;

	uint64_t gtpu_pkt_cnt_i_2_r_0 = 0;
	uint64_t gtpu_pkt_cnt_i_2_r_1 = 0;
	uint64_t gtpu_pkt_cnt_i_2_r_2 = 0;
	uint64_t gtpu_pkt_cnt_i_2_r_3 = 0;

	uint64_t gtpu_pkt_cnt_i_3_r_0 = 0;
	uint64_t gtpu_pkt_cnt_i_3_r_1 = 0;
	uint64_t gtpu_pkt_cnt_i_3_r_2 = 0;
	uint64_t gtpu_pkt_cnt_i_3_r_3 = 0;

	bool gtp_glb_sessions_cnt_process = false;
	uint32_t gtp_glb_lku_up_active_sessions_cnt = 0;
	uint32_t gtp_glb_lku_up_sessions_cnt = 0;
	uint32_t gtp_glb_lku_dn_active_sessions_cnt = 0;
	uint32_t gtp_glb_lku_dn_sessions_cnt = 0;

	uint32_t gtp_glb_inactive_session_cln_cnt = 0;
	uint32_t gtp_glb_lku_up_sessions_cln_cnt = 0;
	uint32_t gtp_glb_lku_dn_sessions_cln_cnt = 0;

	int gtp_glb_sessions_total_cnt = 0;
	int gtp_glb_sessions_utran_cnt = 0;
	int gtp_glb_sessions_geran_cnt = 0;

	int gtp_glb_active_sessions_cnt = 0;

	int gtp_glb_ctl_up_cnt = 0;
	int gtp_glb_data_up_cnt = 0;
	int gtp_glb_ctl_dn_cnt = 0;
	int gtp_glb_data_dn_cnt = 0;

	uint32_t gtp_glb_sessions_op_cr_cnt = 0;
	uint32_t gtp_glb_sessions_op_up_cnt = 0;
	uint32_t gtp_glb_sessions_op_dl_cnt = 0;

	uint32_t gtp_pdp_cr_flush_sm_0 = 0;
	uint32_t gtp_pdp_cr_flush_sm_1 = 0;
	uint32_t gtp_pdp_cr_flush_sm_2 = 0;
	uint32_t gtp_pdp_cr_flush_sm_3 = 0;

	uint32_t gtp_pdp_up_flush_sm_0 = 0;
	uint32_t gtp_pdp_up_flush_sm_1 = 0;
	uint32_t gtp_pdp_up_flush_sm_2 = 0;
	uint32_t gtp_pdp_up_flush_sm_3 = 0;

	uint32_t gtp_pdp_dl_flush_sm_0 = 0;
	uint32_t gtp_pdp_dl_flush_sm_1 = 0;
	uint32_t gtp_pdp_dl_flush_sm_2 = 0;
	uint32_t gtp_pdp_dl_flush_sm_3 = 0;

	uint32_t gtp_pdp_cr_session_sm_0 = 0;
	uint32_t gtp_pdp_cr_session_sm_1 = 0;
	uint32_t gtp_pdp_cr_session_sm_2 = 0;
	uint32_t gtp_pdp_cr_session_sm_3 = 0;

	uint32_t gtp_pdp_up_session_sm_0 = 0;
	uint32_t gtp_pdp_up_session_sm_1 = 0;
	uint32_t gtp_pdp_up_session_sm_2 = 0;
	uint32_t gtp_pdp_up_session_sm_3 = 0;

	uint32_t gtp_pdp_dl_session_sm_0 = 0;
	uint32_t gtp_pdp_dl_session_sm_1 = 0;
	uint32_t gtp_pdp_dl_session_sm_2 = 0;
	uint32_t gtp_pdp_dl_session_sm_3 = 0;

	uint32_t gtpc_pdp_cr_req_sm_0 = 0;
	uint32_t gtpc_pdp_cr_req_sm_1 = 0;
	uint32_t gtpc_pdp_cr_req_sm_2 = 0;
	uint32_t gtpc_pdp_cr_req_sm_3 = 0;
	uint32_t gtpc_pdp_cr_res_sm_0 = 0;
	uint32_t gtpc_pdp_cr_res_sm_1 = 0;
	uint32_t gtpc_pdp_cr_res_sm_2 = 0;
	uint32_t gtpc_pdp_cr_res_sm_3 = 0;

	uint32_t gtpc_pdp_up_req_sm_0 = 0;
	uint32_t gtpc_pdp_up_req_sm_1 = 0;
	uint32_t gtpc_pdp_up_req_sm_2 = 0;
	uint32_t gtpc_pdp_up_req_sm_3 = 0;
	uint32_t gtpc_pdp_up_res_sm_0 = 0;
	uint32_t gtpc_pdp_up_res_sm_1 = 0;
	uint32_t gtpc_pdp_up_res_sm_2 = 0;
	uint32_t gtpc_pdp_up_res_sm_3 = 0;

	uint32_t gtpc_pdp_dl_req_sm_0 = 0;
	uint32_t gtpc_pdp_dl_req_sm_1 = 0;
	uint32_t gtpc_pdp_dl_req_sm_2 = 0;
	uint32_t gtpc_pdp_dl_req_sm_3 = 0;
	uint32_t gtpc_pdp_dl_res_sm_0 = 0;
	uint32_t gtpc_pdp_dl_res_sm_1 = 0;
	uint32_t gtpc_pdp_dl_res_sm_2 = 0;
	uint32_t gtpc_pdp_dl_res_sm_3 = 0;
}

namespace IPStats {

	uint64_t dns_resolved_lookup_size = 0;
	uint64_t dns_lookup_map_size = 0;
	int dns_session_sm_0_cnt = 0;
	int dns_session_sm_1_cnt = 0;
	int dns_session_sm_2_cnt = 0;
	int dns_session_sm_3_cnt = 0;
	int dns_session_sm_4_cnt = 0;

	uint64_t ip_session_fin_only_sm_0_cnt = 0;
	uint64_t ip_session_fin_only_sm_1_cnt = 0;
	uint64_t ip_session_fin_only_sm_2_cnt = 0;
	uint64_t ip_session_fin_only_sm_3_cnt = 0;
	uint64_t ip_session_fin_only_sm_4_cnt = 0;

	int ip_session_total_sm_0_cnt = 0;
	int ip_session_total_sm_1_cnt = 0;
	int ip_session_total_sm_2_cnt = 0;
	int ip_session_total_sm_3_cnt = 0;
	int ip_session_total_sm_4_cnt = 0;

	int ip_session_scanned_sm_0_cnt = 0;
	int ip_session_scanned_sm_1_cnt = 0;
	int ip_session_scanned_sm_2_cnt = 0;
	int ip_session_scanned_sm_3_cnt = 0;
	int ip_session_scanned_sm_4_cnt = 0;

	int ip_session_cleaned_tcp_sm_0_cnt = 0;
	int ip_session_cleaned_tcp_sm_1_cnt = 0;
	int ip_session_cleaned_tcp_sm_2_cnt = 0;
	int ip_session_cleaned_tcp_sm_3_cnt = 0;
	int ip_session_cleaned_tcp_sm_4_cnt = 0;

	int ip_session_cleaned_udp_sm_0_cnt = 0;
	int ip_session_cleaned_udp_sm_1_cnt = 0;
	int ip_session_cleaned_udp_sm_2_cnt = 0;
	int ip_session_cleaned_udp_sm_3_cnt = 0;
	int ip_session_cleaned_udp_sm_4_cnt = 0;
}

namespace IPGlobal{

	BOOL	PROBE_RUNNING_STATUS = true;

	BOOL	PKT_LISTENER_RUNNING_STATUS[4];
	BOOL	PKT_LISTENER_INTF_MON_RUNNING_STATUS[4];
	BOOL	PKT_LISTENER_DAYCHANGE_INDICATION[4];
	BOOL	PKT_ROUTER_RUNNING_STATUS[4][4];

	BOOL	GN_SESSION_MANAGER_RUNNING_STATUS[8];

	BOOL	FLUSHER_RUNNING_STATUS = true;
	BOOL	GN_XDR_RUNNING_STATUS = true;
	BOOL	GN_GTPC_FLUSHER_RUNNING_STATUS = true;
	BOOL	GN_GTPU_FLUSHER_RUNNING_STATUS = true;

	BOOL	GN_FLUSHER_ZMQ_RUNNING_STATUS = true;
	BOOL	PROBE_STATS_RUNNING_STATUS = true;
	int		GN_GTPU_FLUSHER_NO = 0;
	int		GN_GTPU_FLUSHER_CPU_CORE[4] = {0,0,0,0};
	int		GN_GTPC_FLUSHER_CPU_CORE = 0;
	int		GN_ZMQ_FLUSHER_CPU_CORE = 0;
	int		GN_XDR_FLUSHER_CPU_CORE = 0;
	long 	CURRENT_TIME_EPOCH_SEC = 0;
	long 	CURRENT_TIME_EPOCH_MICRO_SEC = 0;

	int	 	CURRENT_TIME_SEC = 0;
	int 	CURRENT_TIME_MIN = 0;
	int 	CURRENT_TIME_HOUR = 0;
	int 	CURRENT_TIME_DAY = 0;
	int 	CURRENT_TIME_MONTH = 0;
	int 	CURRENT_TIME_YEAR = 0;

	int 	PROBE_ID = 1;
	bool 	PRINT_STATS = false;
	int 	PRINT_STATS_FREQ_SEC = 1;

	int 	ACTIVE_INTERFACE;
	string 	PCAP_FILE_NAME;
	int 	PCAP_REPEAT;
	string 	ETHERNET_INTERFACE;
	string 	SOLAR_INTERFACE;

	int 	NO_OF_INTERFACES = 1;
	string 	ETHERNET_INTERFACES[MAX_INTERFACE_SUPPORT] 		= {"","","",""};
	string 	SOLAR_INTERFACES[MAX_INTERFACE_SUPPORT] 		= {"","","",""};
	int 	ROUTER_PER_INTERFACE[MAX_INTERFACE_SUPPORT] 	= {0,0,0,0};
	int		PKT_LISTENER_CPU_CORE[MAX_INTERFACE_SUPPORT]	= {0,0,0,0};
	int		PKT_ROUTER_CPU_CORE[MAX_INTERFACE_SUPPORT][MAX_INTERFACE_SUPPORT]	= {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}} ;
	int 	LINE_RATE_PER_INTERFACE[MAX_INTERFACE_SUPPORT] 	= {0,0,0,0};
	int 	PPS_PER_INTERFACE[MAX_INTERFACE_SUPPORT] 		= {100000,100000,100000,100000};
	int		PPS_CAP_PERCENTAGE[MAX_INTERFACE_SUPPORT]		= {50,50,50,50};

	uint32_t PKT_RATE_INTF_0 = 0;
	uint32_t PKT_RATE_INTF_1 = 0;
	uint32_t PKT_RATE_INTF_2 = 0;
	uint32_t PKT_RATE_INTF_3 = 0;

	uint128_t PKTS_TOTAL_INTF_0 = 0;
	uint128_t PKTS_TOTAL_INTF_1 = 0;
	uint128_t PKTS_TOTAL_INTF_2 = 0;
	uint128_t PKTS_TOTAL_INTF_3 = 0;

	uint64_t BW_MBPS_INTF_0 = 0;
	uint64_t BW_MBPS_INTF_1 = 0;
	uint64_t BW_MBPS_INTF_2 = 0;
	uint64_t BW_MBPS_INTF_3 = 0;

	bwData BW_MBPS_i_0_r_0;
	bwData BW_MBPS_i_0_r_1;
	bwData BW_MBPS_i_0_r_2;
	bwData BW_MBPS_i_0_r_3;

	bwData BW_MBPS_i_1_r_0;
	bwData BW_MBPS_i_1_r_1;
	bwData BW_MBPS_i_1_r_2;
	bwData BW_MBPS_i_1_r_3;

	bwData BW_MBPS_i_2_r_0;
	bwData BW_MBPS_i_2_r_1;
	bwData BW_MBPS_i_2_r_2;
	bwData BW_MBPS_i_2_r_3;

	bwData BW_MBPS_i_3_r_0;
	bwData BW_MBPS_i_3_r_1;
	bwData BW_MBPS_i_3_r_2;
	bwData BW_MBPS_i_3_r_3;

	int GN_SESSION_MANAGER_INSTANCES = 0;
	int GN_SESSION_MANAGER_CPU_CORE[8] 	= {0,0,0,0,0,0,0,0};
	int SESSION_MANAGER_TIMEINDEX = 0;
	long SESSION_MANAGER_PER_TIMEINDEX_PKTS = 0;
	int FLUSHER_TIMEINDEX = 0;
	int ZMQ_FLUSHER_TIMEINDEX = 0;
	int SESSION_MANAGER_WRITE_INDEX_ADV = 0;
	int SESSION_MANAGER_READ_INDEX_LAG = 0;

	int IUPS_SESSION_MANAGER_INSTANCES = 0;
	int IUPS_SESSION_MANAGER_CPU_CORE[8] 	= {0,0,0,0,0,0,0,0};
	int	IUPS_ZMQ_FLUSHER_CPU_CORE = 0;
	int IUPS_FLUSHER_CPU_CORE = 0;
	int	IUPS_FLUSHER_NO = 0;

	int  	SRC_MAC_NOS;
	int 	DST_MAC_NOS;
	char 	RNC_MAC[8][18];
	char 	SGSN_MAC[8][18];
	char 	GGSN_MAC[8][18];
	int		SGSN_PC[8];
	int 	TOTAL_SGSN_PC;

	int IPV4_MULTIPLIER_OCTET_1 = 16777216;
	int IPV4_MULTIPLIER_OCTET_2 = 65536;
	int IPV4_MULTIPLIER_OCTET_3 = 256;


	ULONG IPV6_MULTIPLIER_OCTET_1 = 281474976710656;
	ULONG IPV6_MULTIPLIER_OCTET_2 = 1099511627776;
	ULONG IPV6_MULTIPLIER_OCTET_3 = 4294967296;
	ULONG IPV6_MULTIPLIER_OCTET_4 = 16777216;
	ULONG IPV6_MULTIPLIER_OCTET_5 = 65536;
	ULONG IPV6_MULTIPLIER_OCTET_6 = 256;

	bool  queueFlag = false;

	int	IP_SESSION_PKT_LIMIT = 0;
	int IP_SESSION_REPO_MAX_LIMIT = 0;
	int IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE = 0;
	int IP_SESSION_CLEAN_UP_SCAN_FREQ_SEC = 10;
	int IP_SESSION_CLEAN_UP_BATCH_LIMIT = 0;
	int IP_SESSION_DNS_LOOKUP_TIMEOUT_SEC = 60;

	ULONG lastFlusherEpochTimeSec = 0;
	ULONG lastCleanUpEpochTimeSec = 0;
	ULONG sessionSrNo = 1000000;

	uint32_t 	currentDay;

    TCHAR 		tcpConfigFile[50] = "tcp.config";
    TCHAR 		dnsDbDumpFile[50] = "dnsDbFile";
    TCHAR 		TDRFile[100];
    TCHAR		DNSTDRFile[100];
	uint64_t 	processedPacket[2];
    ULONG	 	t_FrameCount = 0;
    fstream 	tcpConfigHandler;
	fstream 	IPXdrHandler;
	fstream 	bwLogHandler;
	fstream 	httpLogHandler;

	fstream 	dnsDumpHandler;
	fstream 	dnsUploadHandler;
	fstream 	dnsDayHandler;

	fstream 	gtpDumpHandler;

	fstream 	IUPSXdrHandler;
	fstream 	IUPSCsvXdrHandler;
	fstream 	GXCsvXdrHandler;
	fstream		RadiusXdrHandler;

	/*
	 * For GN related file stream
	 */
	fstream 	dnsCsvHandler;
	fstream		GTPuCsvHandler;
	fstream		GTPuTdrHandler;
	fstream		GTPcCsvHandler;
	fstream		GTPcTdrHandler;

	uint32_t dummyLoop = 0;
	uint32_t zmqCount = 0;

    int 		sliceValue = 0;

	void 		*tcpZmqContext;
    void 		*tcpZmqRequester;

	void 		*gxZmqContext;
    void 		*gxZmqRequester;

	void 		*radiusZmqContext;
    void 		*radiusZmqRequester;

	void 		*gtpcZmqContext;
    void 		*gtpcZmqRequester;

    void 		*gtpuZmqContext;
    void 		*gtpuZmqRequester;

	void 		*iupsZmqContext;
    void 		*iupsZmqRequester;

    void 		*dnsZmqContext;
    void 		*dnsZmqRequester;

    int		idleSessionExpireTime;
    int 	activeSessionExpireTime;
    int		sessionCleanFreq;

    uint32_t inputType = 0;

    TCHAR	inputSource[200];
    TCHAR	smQueuePath[500];
    TCHAR	ffQueuePath[500];

    int		ffQid = 0;
    int 	xdrFlag = 1;
    int 	flushFlag;
    uint16_t	logLevel;

    std::ifstream ranapxmlfile;
    ULONG	sendQ = 0;
    ULONG	recvQ = 0;
    ULONG	smRcv = 0;

    ULONG	CleanFlush = 0;

    ULONG	PDPCreateReq = 0;
    ULONG	PDPCreateReqNew = 0;
    ULONG	PDPCreateReqExist = 0;

    ULONG	PDPCreateRsp = 0;
    ULONG	PDPCreateClose = 0;
    ULONG	PDPCreateRspNotFound = 0;

    ULONG	PDPUpdateReq = 0;
    ULONG	PDPUpdateReqNew = 0;
    ULONG	PDPUpdateReqExist = 0;

    ULONG	PDPUpdateRsp = 0;
    ULONG	PDPUpdateClose = 0;
    ULONG	PDPUpdateRspNotFound = 0;

    ULONG	PDPDeleteReq = 0;
    ULONG	PDPDeleteReqNew = 0;
    ULONG	PDPDeleteReqExist = 0;

    ULONG	PDPDeleteRsp = 0;
    ULONG	PDPDeleteClose = 0;
    ULONG	PDPDeleteRspNotFound = 0;

    ULONG	globalTableCreate 	= 0;
    ULONG	globalTableDelete 	= 0;
    ULONG	PDPDeleteFlush 	= 0;

    vector<string> TraceSCCPSessionIds;
    vector<string> ipRange;
    uint16_t	gtpVersion = 0;

    std::map<int, int> IPRange;

    std::map<char*, int> macAddress;

    long 	Stats_IPSM_0_cnt = 0;
    long 	Stats_IPSM_1_cnt = 0;
    long 	Stats_IPSM_2_cnt = 0;
    long 	Stats_IPSM_3_cnt = 0;

    uint64_t ip_processed_packets_i_0_r_0;
    uint64_t ip_processed_packets_i_0_r_1;
    uint64_t ip_processed_packets_i_0_r_2;
    uint64_t ip_processed_packets_i_0_r_3;

    uint64_t ip_processed_packets_i_1_r_0;
    uint64_t ip_processed_packets_i_1_r_1;
    uint64_t ip_processed_packets_i_1_r_2;
    uint64_t ip_processed_packets_i_1_r_3;

    uint64_t ip_processed_packets_i_2_r_0;
    uint64_t ip_processed_packets_i_2_r_1;
    uint64_t ip_processed_packets_i_2_r_2;
    uint64_t ip_processed_packets_i_2_r_3;

    uint64_t ip_processed_packets_i_3_r_0;
    uint64_t ip_processed_packets_i_3_r_1;
    uint64_t ip_processed_packets_i_3_r_2;
    uint64_t ip_processed_packets_i_3_r_3;

    uint64_t ip_discarded_packets_i_0_r_0 = 0;
    uint64_t ip_discarded_packets_i_0_r_1 = 0;
    uint64_t ip_discarded_packets_i_0_r_2 = 0;
    uint64_t ip_discarded_packets_i_0_r_3 = 0;

    uint64_t ip_discarded_packets_i_1_r_0 = 0;
    uint64_t ip_discarded_packets_i_1_r_1 = 0;
    uint64_t ip_discarded_packets_i_1_r_2 = 0;
    uint64_t ip_discarded_packets_i_1_r_3 = 0;

    uint64_t ip_discarded_packets_i_2_r_0 = 0;
    uint64_t ip_discarded_packets_i_2_r_1 = 0;
    uint64_t ip_discarded_packets_i_2_r_2 = 0;
    uint64_t ip_discarded_packets_i_2_r_3 = 0;

    uint64_t ip_discarded_packets_i_3_r_0 = 0;
    uint64_t ip_discarded_packets_i_3_r_1 = 0;
    uint64_t ip_discarded_packets_i_3_r_2 = 0;
    uint64_t ip_discarded_packets_i_3_r_3 = 0;

    uint64_t ip_discarded_large_packets_i_0 = 0;
    uint64_t ip_discarded_large_packets_i_1 = 0;
    uint64_t ip_discarded_large_packets_i_2 = 0;
    uint64_t ip_discarded_large_packets_i_3 = 0;

    uint64_t ip_noproto_packets_i_0_r_0 = 0;
    uint64_t ip_noproto_packets_i_0_r_1 = 0;
    uint64_t ip_noproto_packets_i_0_r_2 = 0;
    uint64_t ip_noproto_packets_i_0_r_3 = 0;

    uint64_t ip_noproto_packets_i_1_r_0 = 0;
    uint64_t ip_noproto_packets_i_1_r_1 = 0;
    uint64_t ip_noproto_packets_i_1_r_2 = 0;
    uint64_t ip_noproto_packets_i_1_r_3 = 0;

    uint64_t ip_noproto_packets_i_2_r_0 = 0;
    uint64_t ip_noproto_packets_i_2_r_1 = 0;
    uint64_t ip_noproto_packets_i_2_r_2 = 0;
    uint64_t ip_noproto_packets_i_2_r_3 = 0;

    uint64_t ip_noproto_packets_i_3_r_0 = 0;
    uint64_t ip_noproto_packets_i_3_r_1 = 0;
    uint64_t ip_noproto_packets_i_3_r_2 = 0;
    uint64_t ip_noproto_packets_i_3_r_3 = 0;

}

namespace PCons
{
//	bool ERROR = true;
	bool WARNING = true;
	bool DEBUG = true;
	bool TRACE = true;
	bool LOG = true;


	bool P_MTP3 = false;
	bool P_SCTP = true;
	bool P_SCCP = true;
	bool P_SCCPSM = false;
	bool P_RANAP = true;
	bool P_NAS = true;
	bool P_IUPSSM = false;
	bool P_MME = false;
	bool P_MME_NAS = false;

	long PKT_COUNT = 0;

	long r_pkt_cnt = 0;
	long r_line_cnt = 0;

	long sccp_s_cnt = 0;
	long iups_s_cnt = 0;
	long gmm_s_cnt = 0;
	long r_s_cnt = 0;

	long sccp_flush_cnt = 0;
	long iups_flush_cnt = 0;

	long sccp_flush_init_cnt = 0;
	long iups_flush_init_cnt = 0;

	long iups_gmm_flush_init_cnt = 0;
	long iups_ranap_flush_init_cnt = 0;

}

namespace PKTStore
{

	// Interface_0
	std::map<long, RawPkt*> pktRepository_i_0_r_0_t_0;
	std::map<long, RawPkt*> pktRepository_i_0_r_0_t_1;
	std::map<long, RawPkt*> pktRepository_i_0_r_0_t_2;
	std::map<long, RawPkt*> pktRepository_i_0_r_0_t_3;
	std::map<long, RawPkt*> pktRepository_i_0_r_0_t_4;
	std::map<long, RawPkt*> pktRepository_i_0_r_0_t_5;
	std::map<long, RawPkt*> pktRepository_i_0_r_0_t_6;
	std::map<long, RawPkt*> pktRepository_i_0_r_0_t_7;
	std::map<long, RawPkt*> pktRepository_i_0_r_0_t_8;
	std::map<long, RawPkt*> pktRepository_i_0_r_0_t_9;

	long pktRepository_i_0_r_0_t_0_cnt = 0;
	long pktRepository_i_0_r_0_t_1_cnt = 0;
	long pktRepository_i_0_r_0_t_2_cnt = 0;
	long pktRepository_i_0_r_0_t_3_cnt = 0;
	long pktRepository_i_0_r_0_t_4_cnt = 0;
	long pktRepository_i_0_r_0_t_5_cnt = 0;
	long pktRepository_i_0_r_0_t_6_cnt = 0;
	long pktRepository_i_0_r_0_t_7_cnt = 0;
	long pktRepository_i_0_r_0_t_8_cnt = 0;
	long pktRepository_i_0_r_0_t_9_cnt = 0;

	bool pktRepository_i_0_r_0_t_0_busy = false;
	bool pktRepository_i_0_r_0_t_1_busy = false;
	bool pktRepository_i_0_r_0_t_2_busy = false;
	bool pktRepository_i_0_r_0_t_3_busy = false;
	bool pktRepository_i_0_r_0_t_4_busy = false;
	bool pktRepository_i_0_r_0_t_5_busy = false;
	bool pktRepository_i_0_r_0_t_6_busy = false;
	bool pktRepository_i_0_r_0_t_7_busy = false;
	bool pktRepository_i_0_r_0_t_8_busy = false;
	bool pktRepository_i_0_r_0_t_9_busy = false;

	std::map<long, RawPkt*> pktRepository_i_0_r_1_t_0;
	std::map<long, RawPkt*> pktRepository_i_0_r_1_t_1;
	std::map<long, RawPkt*> pktRepository_i_0_r_1_t_2;
	std::map<long, RawPkt*> pktRepository_i_0_r_1_t_3;
	std::map<long, RawPkt*> pktRepository_i_0_r_1_t_4;
	std::map<long, RawPkt*> pktRepository_i_0_r_1_t_5;
	std::map<long, RawPkt*> pktRepository_i_0_r_1_t_6;
	std::map<long, RawPkt*> pktRepository_i_0_r_1_t_7;
	std::map<long, RawPkt*> pktRepository_i_0_r_1_t_8;
	std::map<long, RawPkt*> pktRepository_i_0_r_1_t_9;

	long pktRepository_i_0_r_1_t_0_cnt = 0;
	long pktRepository_i_0_r_1_t_1_cnt = 0;
	long pktRepository_i_0_r_1_t_2_cnt = 0;
	long pktRepository_i_0_r_1_t_3_cnt = 0;
	long pktRepository_i_0_r_1_t_4_cnt = 0;
	long pktRepository_i_0_r_1_t_5_cnt = 0;
	long pktRepository_i_0_r_1_t_6_cnt = 0;
	long pktRepository_i_0_r_1_t_7_cnt = 0;
	long pktRepository_i_0_r_1_t_8_cnt = 0;
	long pktRepository_i_0_r_1_t_9_cnt = 0;

	bool pktRepository_i_0_r_1_t_0_busy = false;
	bool pktRepository_i_0_r_1_t_1_busy = false;
	bool pktRepository_i_0_r_1_t_2_busy = false;
	bool pktRepository_i_0_r_1_t_3_busy = false;
	bool pktRepository_i_0_r_1_t_4_busy = false;
	bool pktRepository_i_0_r_1_t_5_busy = false;
	bool pktRepository_i_0_r_1_t_6_busy = false;
	bool pktRepository_i_0_r_1_t_7_busy = false;
	bool pktRepository_i_0_r_1_t_8_busy = false;
	bool pktRepository_i_0_r_1_t_9_busy = false;

//	std::map<long, RawPkt*> pktRepository_i_0_r_2_t_0;
//	std::map<long, RawPkt*> pktRepository_i_0_r_2_t_1;
//	std::map<long, RawPkt*> pktRepository_i_0_r_2_t_2;
//	std::map<long, RawPkt*> pktRepository_i_0_r_2_t_3;
//	std::map<long, RawPkt*> pktRepository_i_0_r_2_t_4;
//	std::map<long, RawPkt*> pktRepository_i_0_r_2_t_5;
//	std::map<long, RawPkt*> pktRepository_i_0_r_2_t_6;
//	std::map<long, RawPkt*> pktRepository_i_0_r_2_t_7;
//	std::map<long, RawPkt*> pktRepository_i_0_r_2_t_8;
//	std::map<long, RawPkt*> pktRepository_i_0_r_2_t_9;
//
//	long pktRepository_i_0_r_2_t_0_cnt = 0;
//	long pktRepository_i_0_r_2_t_1_cnt = 0;
//	long pktRepository_i_0_r_2_t_2_cnt = 0;
//	long pktRepository_i_0_r_2_t_3_cnt = 0;
//	long pktRepository_i_0_r_2_t_4_cnt = 0;
//	long pktRepository_i_0_r_2_t_5_cnt = 0;
//	long pktRepository_i_0_r_2_t_6_cnt = 0;
//	long pktRepository_i_0_r_2_t_7_cnt = 0;
//	long pktRepository_i_0_r_2_t_8_cnt = 0;
//	long pktRepository_i_0_r_2_t_9_cnt = 0;
//
//	std::map<long, RawPkt*> pktRepository_i_0_r_3_t_0;
//	std::map<long, RawPkt*> pktRepository_i_0_r_3_t_1;
//	std::map<long, RawPkt*> pktRepository_i_0_r_3_t_2;
//	std::map<long, RawPkt*> pktRepository_i_0_r_3_t_3;
//	std::map<long, RawPkt*> pktRepository_i_0_r_3_t_4;
//	std::map<long, RawPkt*> pktRepository_i_0_r_3_t_5;
//	std::map<long, RawPkt*> pktRepository_i_0_r_3_t_6;
//	std::map<long, RawPkt*> pktRepository_i_0_r_3_t_7;
//	std::map<long, RawPkt*> pktRepository_i_0_r_3_t_8;
//	std::map<long, RawPkt*> pktRepository_i_0_r_3_t_9;
//
//	long pktRepository_i_0_r_3_t_0_cnt = 0;
//	long pktRepository_i_0_r_3_t_1_cnt = 0;
//	long pktRepository_i_0_r_3_t_2_cnt = 0;
//	long pktRepository_i_0_r_3_t_3_cnt = 0;
//	long pktRepository_i_0_r_3_t_4_cnt = 0;
//	long pktRepository_i_0_r_3_t_5_cnt = 0;
//	long pktRepository_i_0_r_3_t_6_cnt = 0;
//	long pktRepository_i_0_r_3_t_7_cnt = 0;
//	long pktRepository_i_0_r_3_t_8_cnt = 0;
//	long pktRepository_i_0_r_3_t_9_cnt = 0;


	// Interface_1
	std::map<long, RawPkt*> pktRepository_i_1_r_0_t_0;
	std::map<long, RawPkt*> pktRepository_i_1_r_0_t_1;
	std::map<long, RawPkt*> pktRepository_i_1_r_0_t_2;
	std::map<long, RawPkt*> pktRepository_i_1_r_0_t_3;
	std::map<long, RawPkt*> pktRepository_i_1_r_0_t_4;
	std::map<long, RawPkt*> pktRepository_i_1_r_0_t_5;
	std::map<long, RawPkt*> pktRepository_i_1_r_0_t_6;
	std::map<long, RawPkt*> pktRepository_i_1_r_0_t_7;
	std::map<long, RawPkt*> pktRepository_i_1_r_0_t_8;
	std::map<long, RawPkt*> pktRepository_i_1_r_0_t_9;

	long pktRepository_i_1_r_0_t_0_cnt = 0;
	long pktRepository_i_1_r_0_t_1_cnt = 0;
	long pktRepository_i_1_r_0_t_2_cnt = 0;
	long pktRepository_i_1_r_0_t_3_cnt = 0;
	long pktRepository_i_1_r_0_t_4_cnt = 0;
	long pktRepository_i_1_r_0_t_5_cnt = 0;
	long pktRepository_i_1_r_0_t_6_cnt = 0;
	long pktRepository_i_1_r_0_t_7_cnt = 0;
	long pktRepository_i_1_r_0_t_8_cnt = 0;
	long pktRepository_i_1_r_0_t_9_cnt = 0;

	bool pktRepository_i_1_r_0_t_0_busy = false;
	bool pktRepository_i_1_r_0_t_1_busy = false;
	bool pktRepository_i_1_r_0_t_2_busy = false;
	bool pktRepository_i_1_r_0_t_3_busy = false;
	bool pktRepository_i_1_r_0_t_4_busy = false;
	bool pktRepository_i_1_r_0_t_5_busy = false;
	bool pktRepository_i_1_r_0_t_6_busy = false;
	bool pktRepository_i_1_r_0_t_7_busy = false;
	bool pktRepository_i_1_r_0_t_8_busy = false;
	bool pktRepository_i_1_r_0_t_9_busy = false;

	std::map<long, RawPkt*> pktRepository_i_1_r_1_t_0;
	std::map<long, RawPkt*> pktRepository_i_1_r_1_t_1;
	std::map<long, RawPkt*> pktRepository_i_1_r_1_t_2;
	std::map<long, RawPkt*> pktRepository_i_1_r_1_t_3;
	std::map<long, RawPkt*> pktRepository_i_1_r_1_t_4;
	std::map<long, RawPkt*> pktRepository_i_1_r_1_t_5;
	std::map<long, RawPkt*> pktRepository_i_1_r_1_t_6;
	std::map<long, RawPkt*> pktRepository_i_1_r_1_t_7;
	std::map<long, RawPkt*> pktRepository_i_1_r_1_t_8;
	std::map<long, RawPkt*> pktRepository_i_1_r_1_t_9;

	long pktRepository_i_1_r_1_t_0_cnt = 0;
	long pktRepository_i_1_r_1_t_1_cnt = 0;
	long pktRepository_i_1_r_1_t_2_cnt = 0;
	long pktRepository_i_1_r_1_t_3_cnt = 0;
	long pktRepository_i_1_r_1_t_4_cnt = 0;
	long pktRepository_i_1_r_1_t_5_cnt = 0;
	long pktRepository_i_1_r_1_t_6_cnt = 0;
	long pktRepository_i_1_r_1_t_7_cnt = 0;
	long pktRepository_i_1_r_1_t_8_cnt = 0;
	long pktRepository_i_1_r_1_t_9_cnt = 0;

	bool pktRepository_i_1_r_1_t_0_busy = false;
	bool pktRepository_i_1_r_1_t_1_busy = false;
	bool pktRepository_i_1_r_1_t_2_busy = false;
	bool pktRepository_i_1_r_1_t_3_busy = false;
	bool pktRepository_i_1_r_1_t_4_busy = false;
	bool pktRepository_i_1_r_1_t_5_busy = false;
	bool pktRepository_i_1_r_1_t_6_busy = false;
	bool pktRepository_i_1_r_1_t_7_busy = false;
	bool pktRepository_i_1_r_1_t_8_busy = false;
	bool pktRepository_i_1_r_1_t_9_busy = false;

//	std::map<long, RawPkt*> pktRepository_i_1_r_2_t_0;
//	std::map<long, RawPkt*> pktRepository_i_1_r_2_t_1;
//	std::map<long, RawPkt*> pktRepository_i_1_r_2_t_2;
//	std::map<long, RawPkt*> pktRepository_i_1_r_2_t_3;
//	std::map<long, RawPkt*> pktRepository_i_1_r_2_t_4;
//	std::map<long, RawPkt*> pktRepository_i_1_r_2_t_5;
//	std::map<long, RawPkt*> pktRepository_i_1_r_2_t_6;
//	std::map<long, RawPkt*> pktRepository_i_1_r_2_t_7;
//	std::map<long, RawPkt*> pktRepository_i_1_r_2_t_8;
//	std::map<long, RawPkt*> pktRepository_i_1_r_2_t_9;
//
//	long pktRepository_i_1_r_2_t_0_cnt = 0;
//	long pktRepository_i_1_r_2_t_1_cnt = 0;
//	long pktRepository_i_1_r_2_t_2_cnt = 0;
//	long pktRepository_i_1_r_2_t_3_cnt = 0;
//	long pktRepository_i_1_r_2_t_4_cnt = 0;
//	long pktRepository_i_1_r_2_t_5_cnt = 0;
//	long pktRepository_i_1_r_2_t_6_cnt = 0;
//	long pktRepository_i_1_r_2_t_7_cnt = 0;
//	long pktRepository_i_1_r_2_t_8_cnt = 0;
//	long pktRepository_i_1_r_2_t_9_cnt = 0;
//
//	std::map<long, RawPkt*> pktRepository_i_1_r_3_t_0;
//	std::map<long, RawPkt*> pktRepository_i_1_r_3_t_1;
//	std::map<long, RawPkt*> pktRepository_i_1_r_3_t_2;
//	std::map<long, RawPkt*> pktRepository_i_1_r_3_t_3;
//	std::map<long, RawPkt*> pktRepository_i_1_r_3_t_4;
//	std::map<long, RawPkt*> pktRepository_i_1_r_3_t_5;
//	std::map<long, RawPkt*> pktRepository_i_1_r_3_t_6;
//	std::map<long, RawPkt*> pktRepository_i_1_r_3_t_7;
//	std::map<long, RawPkt*> pktRepository_i_1_r_3_t_8;
//	std::map<long, RawPkt*> pktRepository_i_1_r_3_t_9;
//
//	long pktRepository_i_1_r_3_t_0_cnt = 0;
//	long pktRepository_i_1_r_3_t_1_cnt = 0;
//	long pktRepository_i_1_r_3_t_2_cnt = 0;
//	long pktRepository_i_1_r_3_t_3_cnt = 0;
//	long pktRepository_i_1_r_3_t_4_cnt = 0;
//	long pktRepository_i_1_r_3_t_5_cnt = 0;
//	long pktRepository_i_1_r_3_t_6_cnt = 0;
//	long pktRepository_i_1_r_3_t_7_cnt = 0;
//	long pktRepository_i_1_r_3_t_8_cnt = 0;
//	long pktRepository_i_1_r_3_t_9_cnt = 0;


	// Interface_2
	std::map<long, RawPkt*> pktRepository_i_2_r_0_t_0;
	std::map<long, RawPkt*> pktRepository_i_2_r_0_t_1;
	std::map<long, RawPkt*> pktRepository_i_2_r_0_t_2;
	std::map<long, RawPkt*> pktRepository_i_2_r_0_t_3;
	std::map<long, RawPkt*> pktRepository_i_2_r_0_t_4;
	std::map<long, RawPkt*> pktRepository_i_2_r_0_t_5;
	std::map<long, RawPkt*> pktRepository_i_2_r_0_t_6;
	std::map<long, RawPkt*> pktRepository_i_2_r_0_t_7;
	std::map<long, RawPkt*> pktRepository_i_2_r_0_t_8;
	std::map<long, RawPkt*> pktRepository_i_2_r_0_t_9;

	long pktRepository_i_2_r_0_t_0_cnt = 0;
	long pktRepository_i_2_r_0_t_1_cnt = 0;
	long pktRepository_i_2_r_0_t_2_cnt = 0;
	long pktRepository_i_2_r_0_t_3_cnt = 0;
	long pktRepository_i_2_r_0_t_4_cnt = 0;
	long pktRepository_i_2_r_0_t_5_cnt = 0;
	long pktRepository_i_2_r_0_t_6_cnt = 0;
	long pktRepository_i_2_r_0_t_7_cnt = 0;
	long pktRepository_i_2_r_0_t_8_cnt = 0;
	long pktRepository_i_2_r_0_t_9_cnt = 0;

	bool pktRepository_i_2_r_0_t_0_busy = false;
	bool pktRepository_i_2_r_0_t_1_busy = false;
	bool pktRepository_i_2_r_0_t_2_busy = false;
	bool pktRepository_i_2_r_0_t_3_busy = false;
	bool pktRepository_i_2_r_0_t_4_busy = false;
	bool pktRepository_i_2_r_0_t_5_busy = false;
	bool pktRepository_i_2_r_0_t_6_busy = false;
	bool pktRepository_i_2_r_0_t_7_busy = false;
	bool pktRepository_i_2_r_0_t_8_busy = false;
	bool pktRepository_i_2_r_0_t_9_busy = false;

	std::map<long, RawPkt*> pktRepository_i_2_r_1_t_0;
	std::map<long, RawPkt*> pktRepository_i_2_r_1_t_1;
	std::map<long, RawPkt*> pktRepository_i_2_r_1_t_2;
	std::map<long, RawPkt*> pktRepository_i_2_r_1_t_3;
	std::map<long, RawPkt*> pktRepository_i_2_r_1_t_4;
	std::map<long, RawPkt*> pktRepository_i_2_r_1_t_5;
	std::map<long, RawPkt*> pktRepository_i_2_r_1_t_6;
	std::map<long, RawPkt*> pktRepository_i_2_r_1_t_7;
	std::map<long, RawPkt*> pktRepository_i_2_r_1_t_8;
	std::map<long, RawPkt*> pktRepository_i_2_r_1_t_9;

	long pktRepository_i_2_r_1_t_0_cnt = 0;
	long pktRepository_i_2_r_1_t_1_cnt = 0;
	long pktRepository_i_2_r_1_t_2_cnt = 0;
	long pktRepository_i_2_r_1_t_3_cnt = 0;
	long pktRepository_i_2_r_1_t_4_cnt = 0;
	long pktRepository_i_2_r_1_t_5_cnt = 0;
	long pktRepository_i_2_r_1_t_6_cnt = 0;
	long pktRepository_i_2_r_1_t_7_cnt = 0;
	long pktRepository_i_2_r_1_t_8_cnt = 0;
	long pktRepository_i_2_r_1_t_9_cnt = 0;

	bool pktRepository_i_2_r_1_t_0_busy = false;
	bool pktRepository_i_2_r_1_t_1_busy = false;
	bool pktRepository_i_2_r_1_t_2_busy = false;
	bool pktRepository_i_2_r_1_t_3_busy = false;
	bool pktRepository_i_2_r_1_t_4_busy = false;
	bool pktRepository_i_2_r_1_t_5_busy = false;
	bool pktRepository_i_2_r_1_t_6_busy = false;
	bool pktRepository_i_2_r_1_t_7_busy = false;
	bool pktRepository_i_2_r_1_t_8_busy = false;
	bool pktRepository_i_2_r_1_t_9_busy = false;

//	std::map<long, RawPkt*> pktRepository_i_2_r_2_t_0;
//	std::map<long, RawPkt*> pktRepository_i_2_r_2_t_1;
//	std::map<long, RawPkt*> pktRepository_i_2_r_2_t_2;
//	std::map<long, RawPkt*> pktRepository_i_2_r_2_t_3;
//	std::map<long, RawPkt*> pktRepository_i_2_r_2_t_4;
//	std::map<long, RawPkt*> pktRepository_i_2_r_2_t_5;
//	std::map<long, RawPkt*> pktRepository_i_2_r_2_t_6;
//	std::map<long, RawPkt*> pktRepository_i_2_r_2_t_7;
//	std::map<long, RawPkt*> pktRepository_i_2_r_2_t_8;
//	std::map<long, RawPkt*> pktRepository_i_2_r_2_t_9;
//
//	long pktRepository_i_2_r_2_t_0_cnt = 0;
//	long pktRepository_i_2_r_2_t_1_cnt = 0;
//	long pktRepository_i_2_r_2_t_2_cnt = 0;
//	long pktRepository_i_2_r_2_t_3_cnt = 0;
//	long pktRepository_i_2_r_2_t_4_cnt = 0;
//	long pktRepository_i_2_r_2_t_5_cnt = 0;
//	long pktRepository_i_2_r_2_t_6_cnt = 0;
//	long pktRepository_i_2_r_2_t_7_cnt = 0;
//	long pktRepository_i_2_r_2_t_8_cnt = 0;
//	long pktRepository_i_2_r_2_t_9_cnt = 0;
//
//	std::map<long, RawPkt*> pktRepository_i_2_r_3_t_0;
//	std::map<long, RawPkt*> pktRepository_i_2_r_3_t_1;
//	std::map<long, RawPkt*> pktRepository_i_2_r_3_t_2;
//	std::map<long, RawPkt*> pktRepository_i_2_r_3_t_3;
//	std::map<long, RawPkt*> pktRepository_i_2_r_3_t_4;
//	std::map<long, RawPkt*> pktRepository_i_2_r_3_t_5;
//	std::map<long, RawPkt*> pktRepository_i_2_r_3_t_6;
//	std::map<long, RawPkt*> pktRepository_i_2_r_3_t_7;
//	std::map<long, RawPkt*> pktRepository_i_2_r_3_t_8;
//	std::map<long, RawPkt*> pktRepository_i_2_r_3_t_9;
//
//	long pktRepository_i_2_r_3_t_0_cnt = 0;
//	long pktRepository_i_2_r_3_t_1_cnt = 0;
//	long pktRepository_i_2_r_3_t_2_cnt = 0;
//	long pktRepository_i_2_r_3_t_3_cnt = 0;
//	long pktRepository_i_2_r_3_t_4_cnt = 0;
//	long pktRepository_i_2_r_3_t_5_cnt = 0;
//	long pktRepository_i_2_r_3_t_6_cnt = 0;
//	long pktRepository_i_2_r_3_t_7_cnt = 0;
//	long pktRepository_i_2_r_3_t_8_cnt = 0;
//	long pktRepository_i_2_r_3_t_9_cnt = 0;


	// Interface_3
	std::map<long, RawPkt*> pktRepository_i_3_r_0_t_0;
	std::map<long, RawPkt*> pktRepository_i_3_r_0_t_1;
	std::map<long, RawPkt*> pktRepository_i_3_r_0_t_2;
	std::map<long, RawPkt*> pktRepository_i_3_r_0_t_3;
	std::map<long, RawPkt*> pktRepository_i_3_r_0_t_4;
	std::map<long, RawPkt*> pktRepository_i_3_r_0_t_5;
	std::map<long, RawPkt*> pktRepository_i_3_r_0_t_6;
	std::map<long, RawPkt*> pktRepository_i_3_r_0_t_7;
	std::map<long, RawPkt*> pktRepository_i_3_r_0_t_8;
	std::map<long, RawPkt*> pktRepository_i_3_r_0_t_9;

	long pktRepository_i_3_r_0_t_0_cnt = 0;
	long pktRepository_i_3_r_0_t_1_cnt = 0;
	long pktRepository_i_3_r_0_t_2_cnt = 0;
	long pktRepository_i_3_r_0_t_3_cnt = 0;
	long pktRepository_i_3_r_0_t_4_cnt = 0;
	long pktRepository_i_3_r_0_t_5_cnt = 0;
	long pktRepository_i_3_r_0_t_6_cnt = 0;
	long pktRepository_i_3_r_0_t_7_cnt = 0;
	long pktRepository_i_3_r_0_t_8_cnt = 0;
	long pktRepository_i_3_r_0_t_9_cnt = 0;

	bool pktRepository_i_3_r_0_t_0_busy = false;
	bool pktRepository_i_3_r_0_t_1_busy = false;
	bool pktRepository_i_3_r_0_t_2_busy = false;
	bool pktRepository_i_3_r_0_t_3_busy = false;
	bool pktRepository_i_3_r_0_t_4_busy = false;
	bool pktRepository_i_3_r_0_t_5_busy = false;
	bool pktRepository_i_3_r_0_t_6_busy = false;
	bool pktRepository_i_3_r_0_t_7_busy = false;
	bool pktRepository_i_3_r_0_t_8_busy = false;
	bool pktRepository_i_3_r_0_t_9_busy = false;

	std::map<long, RawPkt*> pktRepository_i_3_r_1_t_0;
	std::map<long, RawPkt*> pktRepository_i_3_r_1_t_1;
	std::map<long, RawPkt*> pktRepository_i_3_r_1_t_2;
	std::map<long, RawPkt*> pktRepository_i_3_r_1_t_3;
	std::map<long, RawPkt*> pktRepository_i_3_r_1_t_4;
	std::map<long, RawPkt*> pktRepository_i_3_r_1_t_5;
	std::map<long, RawPkt*> pktRepository_i_3_r_1_t_6;
	std::map<long, RawPkt*> pktRepository_i_3_r_1_t_7;
	std::map<long, RawPkt*> pktRepository_i_3_r_1_t_8;
	std::map<long, RawPkt*> pktRepository_i_3_r_1_t_9;

	long pktRepository_i_3_r_1_t_0_cnt = 0;
	long pktRepository_i_3_r_1_t_1_cnt = 0;
	long pktRepository_i_3_r_1_t_2_cnt = 0;
	long pktRepository_i_3_r_1_t_3_cnt = 0;
	long pktRepository_i_3_r_1_t_4_cnt = 0;
	long pktRepository_i_3_r_1_t_5_cnt = 0;
	long pktRepository_i_3_r_1_t_6_cnt = 0;
	long pktRepository_i_3_r_1_t_7_cnt = 0;
	long pktRepository_i_3_r_1_t_8_cnt = 0;
	long pktRepository_i_3_r_1_t_9_cnt = 0;

	bool pktRepository_i_3_r_1_t_0_busy = false;
	bool pktRepository_i_3_r_1_t_1_busy = false;
	bool pktRepository_i_3_r_1_t_2_busy = false;
	bool pktRepository_i_3_r_1_t_3_busy = false;
	bool pktRepository_i_3_r_1_t_4_busy = false;
	bool pktRepository_i_3_r_1_t_5_busy = false;
	bool pktRepository_i_3_r_1_t_6_busy = false;
	bool pktRepository_i_3_r_1_t_7_busy = false;
	bool pktRepository_i_3_r_1_t_8_busy = false;
	bool pktRepository_i_3_r_1_t_9_busy = false;


//	std::map<long, RawPkt*> pktRepository_i_3_r_2_t_0;
//	std::map<long, RawPkt*> pktRepository_i_3_r_2_t_1;
//	std::map<long, RawPkt*> pktRepository_i_3_r_2_t_2;
//	std::map<long, RawPkt*> pktRepository_i_3_r_2_t_3;
//	std::map<long, RawPkt*> pktRepository_i_3_r_2_t_4;
//	std::map<long, RawPkt*> pktRepository_i_3_r_2_t_5;
//	std::map<long, RawPkt*> pktRepository_i_3_r_2_t_6;
//	std::map<long, RawPkt*> pktRepository_i_3_r_2_t_7;
//	std::map<long, RawPkt*> pktRepository_i_3_r_2_t_8;
//	std::map<long, RawPkt*> pktRepository_i_3_r_2_t_9;
//
//	long pktRepository_i_3_r_2_t_0_cnt = 0;
//	long pktRepository_i_3_r_2_t_1_cnt = 0;
//	long pktRepository_i_3_r_2_t_2_cnt = 0;
//	long pktRepository_i_3_r_2_t_3_cnt = 0;
//	long pktRepository_i_3_r_2_t_4_cnt = 0;
//	long pktRepository_i_3_r_2_t_5_cnt = 0;
//	long pktRepository_i_3_r_2_t_6_cnt = 0;
//	long pktRepository_i_3_r_2_t_7_cnt = 0;
//	long pktRepository_i_3_r_2_t_8_cnt = 0;
//	long pktRepository_i_3_r_2_t_9_cnt = 0;
//
//	std::map<long, RawPkt*> pktRepository_i_3_r_3_t_0;
//	std::map<long, RawPkt*> pktRepository_i_3_r_3_t_1;
//	std::map<long, RawPkt*> pktRepository_i_3_r_3_t_2;
//	std::map<long, RawPkt*> pktRepository_i_3_r_3_t_3;
//	std::map<long, RawPkt*> pktRepository_i_3_r_3_t_4;
//	std::map<long, RawPkt*> pktRepository_i_3_r_3_t_5;
//	std::map<long, RawPkt*> pktRepository_i_3_r_3_t_6;
//	std::map<long, RawPkt*> pktRepository_i_3_r_3_t_7;
//	std::map<long, RawPkt*> pktRepository_i_3_r_3_t_8;
//	std::map<long, RawPkt*> pktRepository_i_3_r_3_t_9;
//
//	long pktRepository_i_3_r_3_t_0_cnt = 0;
//	long pktRepository_i_3_r_3_t_1_cnt = 0;
//	long pktRepository_i_3_r_3_t_2_cnt = 0;
//	long pktRepository_i_3_r_3_t_3_cnt = 0;
//	long pktRepository_i_3_r_3_t_4_cnt = 0;
//	long pktRepository_i_3_r_3_t_5_cnt = 0;
//	long pktRepository_i_3_r_3_t_6_cnt = 0;
//	long pktRepository_i_3_r_3_t_7_cnt = 0;
//	long pktRepository_i_3_r_3_t_8_cnt = 0;
//	long pktRepository_i_3_r_3_t_9_cnt = 0;

}

namespace TraceStore
{
	std::string tr_msg_i_0_r_0_t_0[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_0_t_1[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_0_t_2[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_0_t_3[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_0_t_4[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_0_t_5[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_0_t_6[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_0_t_7[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_0_t_8[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_0_t_9[TRACE_QUEUE_LIMIT];
	int tr_msg_i_0_r_0_t_0_cnt = 0;
	int tr_msg_i_0_r_0_t_1_cnt = 0;
	int tr_msg_i_0_r_0_t_2_cnt = 0;
	int tr_msg_i_0_r_0_t_3_cnt = 0;
	int tr_msg_i_0_r_0_t_4_cnt = 0;
	int tr_msg_i_0_r_0_t_5_cnt = 0;
	int tr_msg_i_0_r_0_t_6_cnt = 0;
	int tr_msg_i_0_r_0_t_7_cnt = 0;
	int tr_msg_i_0_r_0_t_8_cnt = 0;
	int tr_msg_i_0_r_0_t_9_cnt = 0;

	std::string tr_msg_i_0_r_1_t_0[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_1_t_1[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_1_t_2[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_1_t_3[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_1_t_4[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_1_t_5[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_1_t_6[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_1_t_7[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_1_t_8[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_1_t_9[TRACE_QUEUE_LIMIT];
	int tr_msg_i_0_r_1_t_0_cnt = 0;
	int tr_msg_i_0_r_1_t_1_cnt = 0;
	int tr_msg_i_0_r_1_t_2_cnt = 0;
	int tr_msg_i_0_r_1_t_3_cnt = 0;
	int tr_msg_i_0_r_1_t_4_cnt = 0;
	int tr_msg_i_0_r_1_t_5_cnt = 0;
	int tr_msg_i_0_r_1_t_6_cnt = 0;
	int tr_msg_i_0_r_1_t_7_cnt = 0;
	int tr_msg_i_0_r_1_t_8_cnt = 0;
	int tr_msg_i_0_r_1_t_9_cnt = 0;

	std::string tr_msg_i_0_r_2_t_0[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_2_t_1[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_2_t_2[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_2_t_3[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_2_t_4[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_2_t_5[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_2_t_6[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_2_t_7[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_2_t_8[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_2_t_9[TRACE_QUEUE_LIMIT];
	int tr_msg_i_0_r_2_t_0_cnt = 0;
	int tr_msg_i_0_r_2_t_1_cnt = 0;
	int tr_msg_i_0_r_2_t_2_cnt = 0;
	int tr_msg_i_0_r_2_t_3_cnt = 0;
	int tr_msg_i_0_r_2_t_4_cnt = 0;
	int tr_msg_i_0_r_2_t_5_cnt = 0;
	int tr_msg_i_0_r_2_t_6_cnt = 0;
	int tr_msg_i_0_r_2_t_7_cnt = 0;
	int tr_msg_i_0_r_2_t_8_cnt = 0;
	int tr_msg_i_0_r_2_t_9_cnt = 0;

	std::string tr_msg_i_0_r_3_t_0[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_3_t_1[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_3_t_2[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_3_t_3[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_3_t_4[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_3_t_5[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_3_t_6[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_3_t_7[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_3_t_8[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_0_r_3_t_9[TRACE_QUEUE_LIMIT];
	int tr_msg_i_0_r_3_t_0_cnt = 0;
	int tr_msg_i_0_r_3_t_1_cnt = 0;
	int tr_msg_i_0_r_3_t_2_cnt = 0;
	int tr_msg_i_0_r_3_t_3_cnt = 0;
	int tr_msg_i_0_r_3_t_4_cnt = 0;
	int tr_msg_i_0_r_3_t_5_cnt = 0;
	int tr_msg_i_0_r_3_t_6_cnt = 0;
	int tr_msg_i_0_r_3_t_7_cnt = 0;
	int tr_msg_i_0_r_3_t_8_cnt = 0;
	int tr_msg_i_0_r_3_t_9_cnt = 0;



	std::string tr_msg_i_1_r_0_t_0[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_0_t_1[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_0_t_2[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_0_t_3[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_0_t_4[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_0_t_5[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_0_t_6[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_0_t_7[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_0_t_8[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_0_t_9[TRACE_QUEUE_LIMIT];
	int tr_msg_i_1_r_0_t_0_cnt = 0;
	int tr_msg_i_1_r_0_t_1_cnt = 0;
	int tr_msg_i_1_r_0_t_2_cnt = 0;
	int tr_msg_i_1_r_0_t_3_cnt = 0;
	int tr_msg_i_1_r_0_t_4_cnt = 0;
	int tr_msg_i_1_r_0_t_5_cnt = 0;
	int tr_msg_i_1_r_0_t_6_cnt = 0;
	int tr_msg_i_1_r_0_t_7_cnt = 0;
	int tr_msg_i_1_r_0_t_8_cnt = 0;
	int tr_msg_i_1_r_0_t_9_cnt = 0;

	std::string tr_msg_i_1_r_1_t_0[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_1_t_1[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_1_t_2[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_1_t_3[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_1_t_4[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_1_t_5[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_1_t_6[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_1_t_7[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_1_t_8[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_1_t_9[TRACE_QUEUE_LIMIT];
	int tr_msg_i_1_r_1_t_0_cnt = 0;
	int tr_msg_i_1_r_1_t_1_cnt = 0;
	int tr_msg_i_1_r_1_t_2_cnt = 0;
	int tr_msg_i_1_r_1_t_3_cnt = 0;
	int tr_msg_i_1_r_1_t_4_cnt = 0;
	int tr_msg_i_1_r_1_t_5_cnt = 0;
	int tr_msg_i_1_r_1_t_6_cnt = 0;
	int tr_msg_i_1_r_1_t_7_cnt = 0;
	int tr_msg_i_1_r_1_t_8_cnt = 0;
	int tr_msg_i_1_r_1_t_9_cnt = 0;

	std::string tr_msg_i_1_r_2_t_0[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_2_t_1[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_2_t_2[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_2_t_3[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_2_t_4[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_2_t_5[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_2_t_6[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_2_t_7[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_2_t_8[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_2_t_9[TRACE_QUEUE_LIMIT];
	int tr_msg_i_1_r_2_t_0_cnt = 0;
	int tr_msg_i_1_r_2_t_1_cnt = 0;
	int tr_msg_i_1_r_2_t_2_cnt = 0;
	int tr_msg_i_1_r_2_t_3_cnt = 0;
	int tr_msg_i_1_r_2_t_4_cnt = 0;
	int tr_msg_i_1_r_2_t_5_cnt = 0;
	int tr_msg_i_1_r_2_t_6_cnt = 0;
	int tr_msg_i_1_r_2_t_7_cnt = 0;
	int tr_msg_i_1_r_2_t_8_cnt = 0;
	int tr_msg_i_1_r_2_t_9_cnt = 0;

	std::string tr_msg_i_1_r_3_t_0[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_3_t_1[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_3_t_2[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_3_t_3[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_3_t_4[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_3_t_5[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_3_t_6[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_3_t_7[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_3_t_8[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_1_r_3_t_9[TRACE_QUEUE_LIMIT];
	int tr_msg_i_1_r_3_t_0_cnt = 0;
	int tr_msg_i_1_r_3_t_1_cnt = 0;
	int tr_msg_i_1_r_3_t_2_cnt = 0;
	int tr_msg_i_1_r_3_t_3_cnt = 0;
	int tr_msg_i_1_r_3_t_4_cnt = 0;
	int tr_msg_i_1_r_3_t_5_cnt = 0;
	int tr_msg_i_1_r_3_t_6_cnt = 0;
	int tr_msg_i_1_r_3_t_7_cnt = 0;
	int tr_msg_i_1_r_3_t_8_cnt = 0;
	int tr_msg_i_1_r_3_t_9_cnt = 0;


	std::string tr_msg_i_2_r_0_t_0[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_0_t_1[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_0_t_2[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_0_t_3[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_0_t_4[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_0_t_5[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_0_t_6[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_0_t_7[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_0_t_8[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_0_t_9[TRACE_QUEUE_LIMIT];
	int tr_msg_i_2_r_0_t_0_cnt = 0;
	int tr_msg_i_2_r_0_t_1_cnt = 0;
	int tr_msg_i_2_r_0_t_2_cnt = 0;
	int tr_msg_i_2_r_0_t_3_cnt = 0;
	int tr_msg_i_2_r_0_t_4_cnt = 0;
	int tr_msg_i_2_r_0_t_5_cnt = 0;
	int tr_msg_i_2_r_0_t_6_cnt = 0;
	int tr_msg_i_2_r_0_t_7_cnt = 0;
	int tr_msg_i_2_r_0_t_8_cnt = 0;
	int tr_msg_i_2_r_0_t_9_cnt = 0;

	std::string tr_msg_i_2_r_1_t_0[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_1_t_1[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_1_t_2[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_1_t_3[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_1_t_4[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_1_t_5[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_1_t_6[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_1_t_7[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_1_t_8[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_1_t_9[TRACE_QUEUE_LIMIT];
	int tr_msg_i_2_r_1_t_0_cnt = 0;
	int tr_msg_i_2_r_1_t_1_cnt = 0;
	int tr_msg_i_2_r_1_t_2_cnt = 0;
	int tr_msg_i_2_r_1_t_3_cnt = 0;
	int tr_msg_i_2_r_1_t_4_cnt = 0;
	int tr_msg_i_2_r_1_t_5_cnt = 0;
	int tr_msg_i_2_r_1_t_6_cnt = 0;
	int tr_msg_i_2_r_1_t_7_cnt = 0;
	int tr_msg_i_2_r_1_t_8_cnt = 0;
	int tr_msg_i_2_r_1_t_9_cnt = 0;

	std::string tr_msg_i_2_r_2_t_0[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_2_t_1[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_2_t_2[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_2_t_3[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_2_t_4[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_2_t_5[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_2_t_6[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_2_t_7[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_2_t_8[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_2_t_9[TRACE_QUEUE_LIMIT];
	int tr_msg_i_2_r_2_t_0_cnt = 0;
	int tr_msg_i_2_r_2_t_1_cnt = 0;
	int tr_msg_i_2_r_2_t_2_cnt = 0;
	int tr_msg_i_2_r_2_t_3_cnt = 0;
	int tr_msg_i_2_r_2_t_4_cnt = 0;
	int tr_msg_i_2_r_2_t_5_cnt = 0;
	int tr_msg_i_2_r_2_t_6_cnt = 0;
	int tr_msg_i_2_r_2_t_7_cnt = 0;
	int tr_msg_i_2_r_2_t_8_cnt = 0;
	int tr_msg_i_2_r_2_t_9_cnt = 0;

	std::string tr_msg_i_2_r_3_t_0[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_3_t_1[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_3_t_2[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_3_t_3[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_3_t_4[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_3_t_5[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_3_t_6[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_3_t_7[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_3_t_8[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_2_r_3_t_9[TRACE_QUEUE_LIMIT];
	int tr_msg_i_2_r_3_t_0_cnt = 0;
	int tr_msg_i_2_r_3_t_1_cnt = 0;
	int tr_msg_i_2_r_3_t_2_cnt = 0;
	int tr_msg_i_2_r_3_t_3_cnt = 0;
	int tr_msg_i_2_r_3_t_4_cnt = 0;
	int tr_msg_i_2_r_3_t_5_cnt = 0;
	int tr_msg_i_2_r_3_t_6_cnt = 0;
	int tr_msg_i_2_r_3_t_7_cnt = 0;
	int tr_msg_i_2_r_3_t_8_cnt = 0;
	int tr_msg_i_2_r_3_t_9_cnt = 0;


	std::string tr_msg_i_3_r_0_t_0[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_0_t_1[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_0_t_2[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_0_t_3[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_0_t_4[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_0_t_5[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_0_t_6[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_0_t_7[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_0_t_8[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_0_t_9[TRACE_QUEUE_LIMIT];
	int tr_msg_i_3_r_0_t_0_cnt = 0;
	int tr_msg_i_3_r_0_t_1_cnt = 0;
	int tr_msg_i_3_r_0_t_2_cnt = 0;
	int tr_msg_i_3_r_0_t_3_cnt = 0;
	int tr_msg_i_3_r_0_t_4_cnt = 0;
	int tr_msg_i_3_r_0_t_5_cnt = 0;
	int tr_msg_i_3_r_0_t_6_cnt = 0;
	int tr_msg_i_3_r_0_t_7_cnt = 0;
	int tr_msg_i_3_r_0_t_8_cnt = 0;
	int tr_msg_i_3_r_0_t_9_cnt = 0;

	std::string tr_msg_i_3_r_1_t_0[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_1_t_1[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_1_t_2[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_1_t_3[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_1_t_4[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_1_t_5[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_1_t_6[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_1_t_7[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_1_t_8[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_1_t_9[TRACE_QUEUE_LIMIT];
	int tr_msg_i_3_r_1_t_0_cnt = 0;
	int tr_msg_i_3_r_1_t_1_cnt = 0;
	int tr_msg_i_3_r_1_t_2_cnt = 0;
	int tr_msg_i_3_r_1_t_3_cnt = 0;
	int tr_msg_i_3_r_1_t_4_cnt = 0;
	int tr_msg_i_3_r_1_t_5_cnt = 0;
	int tr_msg_i_3_r_1_t_6_cnt = 0;
	int tr_msg_i_3_r_1_t_7_cnt = 0;
	int tr_msg_i_3_r_1_t_8_cnt = 0;
	int tr_msg_i_3_r_1_t_9_cnt = 0;

	std::string tr_msg_i_3_r_2_t_0[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_2_t_1[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_2_t_2[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_2_t_3[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_2_t_4[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_2_t_5[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_2_t_6[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_2_t_7[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_2_t_8[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_2_t_9[TRACE_QUEUE_LIMIT];
	int tr_msg_i_3_r_2_t_0_cnt = 0;
	int tr_msg_i_3_r_2_t_1_cnt = 0;
	int tr_msg_i_3_r_2_t_2_cnt = 0;
	int tr_msg_i_3_r_2_t_3_cnt = 0;
	int tr_msg_i_3_r_2_t_4_cnt = 0;
	int tr_msg_i_3_r_2_t_5_cnt = 0;
	int tr_msg_i_3_r_2_t_6_cnt = 0;
	int tr_msg_i_3_r_2_t_7_cnt = 0;
	int tr_msg_i_3_r_2_t_8_cnt = 0;
	int tr_msg_i_3_r_2_t_9_cnt = 0;

	std::string tr_msg_i_3_r_3_t_0[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_3_t_1[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_3_t_2[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_3_t_3[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_3_t_4[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_3_t_5[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_3_t_6[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_3_t_7[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_3_t_8[TRACE_QUEUE_LIMIT];
	std::string tr_msg_i_3_r_3_t_9[TRACE_QUEUE_LIMIT];
	int tr_msg_i_3_r_3_t_0_cnt = 0;
	int tr_msg_i_3_r_3_t_1_cnt = 0;
	int tr_msg_i_3_r_3_t_2_cnt = 0;
	int tr_msg_i_3_r_3_t_3_cnt = 0;
	int tr_msg_i_3_r_3_t_4_cnt = 0;
	int tr_msg_i_3_r_3_t_5_cnt = 0;
	int tr_msg_i_3_r_3_t_6_cnt = 0;
	int tr_msg_i_3_r_3_t_7_cnt = 0;
	int tr_msg_i_3_r_3_t_8_cnt = 0;
	int tr_msg_i_3_r_3_t_9_cnt = 0;

}

namespace mapGtpLock {
	pthread_mutex_t lockCount = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t nonzero = PTHREAD_COND_INITIALIZER;
	unsigned count;
}

namespace mapTcpLock {
	pthread_mutex_t lockCount = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t nonzero = PTHREAD_COND_INITIALIZER;
	unsigned count;
}

namespace mapUdpLock {
	pthread_mutex_t lockCount = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t nonzero = PTHREAD_COND_INITIALIZER;
	unsigned count;
}

namespace mapDnsLock {
	pthread_mutex_t lockCount = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t nonzero = PTHREAD_COND_INITIALIZER;
	unsigned count;
}

namespace mapOtrLock {
	pthread_mutex_t lockCount = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t nonzero = PTHREAD_COND_INITIALIZER;
	unsigned count;
}

namespace mapGxLock {
	pthread_mutex_t lockCount = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t nonzero = PTHREAD_COND_INITIALIZER;
	unsigned count;
}

namespace mapRaLock {
	pthread_mutex_t lockCount = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t nonzero = PTHREAD_COND_INITIALIZER;
	unsigned count;
}

namespace vInterfaceLock {
	pthread_mutex_t readyMutex 	= PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t  readyCond  	= PTHREAD_COND_INITIALIZER;
	int             readyCount;
}

namespace gSessionLock {
	pthread_mutex_t lockCount 	= PTHREAD_MUTEX_INITIALIZER;;
	pthread_cond_t nonzero  	= PTHREAD_COND_INITIALIZER;
	unsigned count;
}
