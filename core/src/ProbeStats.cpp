/*
 * ProbeStats.cpp
 *
 *  Created on: Feb 1, 2017
 *      Author: Deb
 */

#include <ctime>
#include "ProbeStats.h"

ProbeStats::ProbeStats() {
	this->_name = "ProbeStats";
	this->setLogLevel(Log::theLog().level());

}

ProbeStats::~ProbeStats() {
}


void ProbeStats::run()
{
	int printloopCnt = 0;
//	int dnsloopCnt = 0;
	struct tm *now_tm;
	char buffer[80];
	long startTime = 0;
	long runTime = 0;
	int dd = 0, hh = 0, mm = 0, ss = 0;

	gettimeofday(&curTime, NULL);
	startTime = curTime.tv_sec;

	bool isStatsInitialized = false;

	while(IPGlobal::PROBE_STATS_RUNNING_STATUS)
	{
	  sleep(1);
	  printloopCnt++;
//	  dnsloopCnt++;

	  gettimeofday(&curTime, NULL);
	  runTime = curTime.tv_sec - startTime;

//	  if(dnsloopCnt >= 60) {
//		  IPStats::dns_resolved_lookup_size = getDNSResolvedLookupSize();
//		  dnsloopCnt = 0;
//	  }

	  dd = (int)(runTime / 84600);
	  hh = (int)((runTime - (dd * 84600)) / 3600);
	  mm = (int)((runTime - ((dd * 84600) + (hh * 3600))) / 60);
	  ss = (int)(runTime - ((dd * 84600) + (hh * 3600) + (mm * 60)));
	  sprintf(buffer, "%03d:%02d:%02d:%02d",dd,hh,mm,ss);

	  if(printloopCnt >= IPGlobal::PRINT_STATS_FREQ_SEC)
	  {
		  printloopCnt = 0;
		  //printInterfaceStats(runTime);
		  printInterfaceStats(buffer);
		  printf("\n\n");
	  }


	}
	printf("Probe Stats Shutdown Completed\n");
}


//void ProbeStats::printInterfaceStats(long runTime)
void ProbeStats::printInterfaceStats(char *runTime)
{
//	  printf("\n   %07d	         PPS       BW        PKTS               T0       T1       T2       T3       T4       T5       T6       T7       T8       T9\n",runTime);
	  printf("\n   %s	         PPS       BW        PKTS               T0       T1       T2       T3       T4       T5       T6       T7       T8       T9\n",runTime);
	  if(IPGlobal::NO_OF_INTERFACES > 0){
		  printf("         Interface [0]   %08d  %06d    %014llu", IPGlobal::PKT_RATE_INTF_0, IPGlobal::BW_MBPS_INTF_0, IPGlobal::PKTS_TOTAL_INTF_0);
		  printPktStoreStats_i_0();

		  if(GContainer::config->GN_PROBE)
			  printGTPSessionStoreStats_i_0();
		  else if (GContainer::config->IUPS_PROBE)
			  printSccpSessionStoreStats_i_0();
	  }

	  if(IPGlobal::NO_OF_INTERFACES > 1){
		  printf("         Interface [1]   %08d  %06d    %014llu", IPGlobal::PKT_RATE_INTF_1, IPGlobal::BW_MBPS_INTF_1, IPGlobal::PKTS_TOTAL_INTF_1);
		  printPktStoreStats_i_1();
	  }

	  if(GContainer::config->GN_PROBE)
		  printGTPSessionStoreStats_i_1();
	  else if (GContainer::config->IUPS_PROBE && IPGlobal::NO_OF_INTERFACES > 1)
		  printSccpSessionStoreStats_i_1();


	  if(IPGlobal::NO_OF_INTERFACES > 2)
		  printf("         Interface [2]   %08d  %06d    %014llu", IPGlobal::PKT_RATE_INTF_2, IPGlobal::BW_MBPS_INTF_2, IPGlobal::PKTS_TOTAL_INTF_2);
	  if(IPGlobal::NO_OF_INTERFACES > 3)
		  printf("         Interface [3]   %08d  %06d    %014llu", IPGlobal::PKT_RATE_INTF_3, IPGlobal::BW_MBPS_INTF_3, IPGlobal::PKTS_TOTAL_INTF_3);

	  if(GContainer::config->GN_PROBE) {
		  printIPSessionFlushStats();
		  printDNSSessionFlushStats();
		  printGTPcSessionFlushStats();
		  printZmqFlushStats();
	  }
	  else if(GContainer::config->IUPS_PROBE) {
		  printIUPSSessionFlushStats();
		  printIUPSZmqFlushStats();
	  }
}


VOID ProbeStats::printPktStoreStats_i_0()
{
	int i = 0;
	int t_cnt[10];
	for(i=0; i<10; i++)
		t_cnt[i] = 0;

//	t_cnt[0] = t_cnt[0] + PKTStore::pktRepository_i_0_r_0_t_0_cnt + PKTStore::pktRepository_i_0_r_1_t_0_cnt + PKTStore::pktRepository_i_0_r_2_t_1_cnt + PKTStore::pktRepository_i_0_r_3_t_0_cnt;
//	t_cnt[1] = t_cnt[1] + PKTStore::pktRepository_i_0_r_0_t_1_cnt + PKTStore::pktRepository_i_0_r_1_t_1_cnt + PKTStore::pktRepository_i_0_r_2_t_2_cnt + PKTStore::pktRepository_i_0_r_3_t_1_cnt;
//	t_cnt[2] = t_cnt[2] + PKTStore::pktRepository_i_0_r_0_t_2_cnt + PKTStore::pktRepository_i_0_r_1_t_2_cnt + PKTStore::pktRepository_i_0_r_2_t_3_cnt + PKTStore::pktRepository_i_0_r_3_t_2_cnt;
//	t_cnt[3] = t_cnt[3] + PKTStore::pktRepository_i_0_r_0_t_3_cnt + PKTStore::pktRepository_i_0_r_1_t_3_cnt + PKTStore::pktRepository_i_0_r_2_t_4_cnt + PKTStore::pktRepository_i_0_r_3_t_3_cnt;
//	t_cnt[4] = t_cnt[4] + PKTStore::pktRepository_i_0_r_0_t_4_cnt + PKTStore::pktRepository_i_0_r_1_t_4_cnt + PKTStore::pktRepository_i_0_r_2_t_5_cnt + PKTStore::pktRepository_i_0_r_3_t_4_cnt;
//	t_cnt[5] = t_cnt[5] + PKTStore::pktRepository_i_0_r_0_t_5_cnt + PKTStore::pktRepository_i_0_r_1_t_5_cnt + PKTStore::pktRepository_i_0_r_2_t_6_cnt + PKTStore::pktRepository_i_0_r_3_t_5_cnt;
//	t_cnt[6] = t_cnt[6] + PKTStore::pktRepository_i_0_r_0_t_6_cnt + PKTStore::pktRepository_i_0_r_1_t_6_cnt + PKTStore::pktRepository_i_0_r_2_t_7_cnt + PKTStore::pktRepository_i_0_r_3_t_6_cnt;
//	t_cnt[7] = t_cnt[7] + PKTStore::pktRepository_i_0_r_0_t_7_cnt + PKTStore::pktRepository_i_0_r_1_t_7_cnt + PKTStore::pktRepository_i_0_r_2_t_8_cnt + PKTStore::pktRepository_i_0_r_3_t_7_cnt;
//	t_cnt[8] = t_cnt[8] + PKTStore::pktRepository_i_0_r_0_t_8_cnt + PKTStore::pktRepository_i_0_r_1_t_8_cnt + PKTStore::pktRepository_i_0_r_2_t_9_cnt + PKTStore::pktRepository_i_0_r_3_t_8_cnt;
//	t_cnt[9] = t_cnt[9] + PKTStore::pktRepository_i_0_r_0_t_9_cnt + PKTStore::pktRepository_i_0_r_1_t_9_cnt + PKTStore::pktRepository_i_0_r_2_t_9_cnt + PKTStore::pktRepository_i_0_r_3_t_9_cnt;

	t_cnt[0] = t_cnt[0] + PKTStore::pktRepository_i_0_r_0_t_0_cnt;
	t_cnt[1] = t_cnt[1] + PKTStore::pktRepository_i_0_r_0_t_1_cnt;
	t_cnt[2] = t_cnt[2] + PKTStore::pktRepository_i_0_r_0_t_2_cnt;
	t_cnt[3] = t_cnt[3] + PKTStore::pktRepository_i_0_r_0_t_3_cnt;
	t_cnt[4] = t_cnt[4] + PKTStore::pktRepository_i_0_r_0_t_4_cnt;
	t_cnt[5] = t_cnt[5] + PKTStore::pktRepository_i_0_r_0_t_5_cnt;
	t_cnt[6] = t_cnt[6] + PKTStore::pktRepository_i_0_r_0_t_6_cnt;
	t_cnt[7] = t_cnt[7] + PKTStore::pktRepository_i_0_r_0_t_7_cnt;
	t_cnt[8] = t_cnt[8] + PKTStore::pktRepository_i_0_r_0_t_8_cnt;
	t_cnt[9] = t_cnt[9] + PKTStore::pktRepository_i_0_r_0_t_9_cnt;

	printf("   ");
	for(i=0; i<10; i++){
		printf("  %07d", t_cnt[i]);
		t_cnt[i] = 0;
	}
	printf("\n");

	t_cnt[0] = t_cnt[0] + PKTStore::pktRepository_i_0_r_1_t_0_cnt;
	t_cnt[1] = t_cnt[1] + PKTStore::pktRepository_i_0_r_1_t_1_cnt;
	t_cnt[2] = t_cnt[2] + PKTStore::pktRepository_i_0_r_1_t_2_cnt;
	t_cnt[3] = t_cnt[3] + PKTStore::pktRepository_i_0_r_1_t_3_cnt;
	t_cnt[4] = t_cnt[4] + PKTStore::pktRepository_i_0_r_1_t_4_cnt;
	t_cnt[5] = t_cnt[5] + PKTStore::pktRepository_i_0_r_1_t_5_cnt;
	t_cnt[6] = t_cnt[6] + PKTStore::pktRepository_i_0_r_1_t_6_cnt;
	t_cnt[7] = t_cnt[7] + PKTStore::pktRepository_i_0_r_1_t_7_cnt;
	t_cnt[8] = t_cnt[8] + PKTStore::pktRepository_i_0_r_1_t_8_cnt;
	t_cnt[9] = t_cnt[9] + PKTStore::pktRepository_i_0_r_1_t_9_cnt;

	printf("                                                              ");
	for(i=0; i<10; i++){
		printf("  %07d", t_cnt[i]);
		t_cnt[i] = 0;
	}
	printf("\n\n");

}

VOID ProbeStats::printPktStoreStats_i_1()
{
	int i = 0;
	int t_cnt[10];
	for(i=0; i<10; i++)
		t_cnt[i] = 0;

//	t_cnt[0] = t_cnt[0] + PKTStore::pktRepository_i_1_r_0_t_0_cnt + PKTStore::pktRepository_i_1_r_1_t_0_cnt + PKTStore::pktRepository_i_1_r_2_t_1_cnt + PKTStore::pktRepository_i_1_r_3_t_0_cnt;
//	t_cnt[1] = t_cnt[1] + PKTStore::pktRepository_i_1_r_0_t_1_cnt + PKTStore::pktRepository_i_1_r_1_t_1_cnt + PKTStore::pktRepository_i_1_r_2_t_2_cnt + PKTStore::pktRepository_i_1_r_3_t_1_cnt;
//	t_cnt[2] = t_cnt[2] + PKTStore::pktRepository_i_1_r_0_t_2_cnt + PKTStore::pktRepository_i_1_r_1_t_2_cnt + PKTStore::pktRepository_i_1_r_2_t_3_cnt + PKTStore::pktRepository_i_1_r_3_t_2_cnt;
//	t_cnt[3] = t_cnt[3] + PKTStore::pktRepository_i_1_r_0_t_3_cnt + PKTStore::pktRepository_i_1_r_1_t_3_cnt + PKTStore::pktRepository_i_1_r_2_t_4_cnt + PKTStore::pktRepository_i_1_r_3_t_3_cnt;
//	t_cnt[4] = t_cnt[4] + PKTStore::pktRepository_i_1_r_0_t_4_cnt + PKTStore::pktRepository_i_1_r_1_t_4_cnt + PKTStore::pktRepository_i_1_r_2_t_5_cnt + PKTStore::pktRepository_i_1_r_3_t_4_cnt;
//	t_cnt[5] = t_cnt[5] + PKTStore::pktRepository_i_1_r_0_t_5_cnt + PKTStore::pktRepository_i_1_r_1_t_5_cnt + PKTStore::pktRepository_i_1_r_2_t_6_cnt + PKTStore::pktRepository_i_1_r_3_t_5_cnt;
//	t_cnt[6] = t_cnt[6] + PKTStore::pktRepository_i_1_r_0_t_6_cnt + PKTStore::pktRepository_i_1_r_1_t_6_cnt + PKTStore::pktRepository_i_1_r_2_t_7_cnt + PKTStore::pktRepository_i_1_r_3_t_6_cnt;
//	t_cnt[7] = t_cnt[7] + PKTStore::pktRepository_i_1_r_0_t_7_cnt + PKTStore::pktRepository_i_1_r_1_t_7_cnt + PKTStore::pktRepository_i_1_r_2_t_8_cnt + PKTStore::pktRepository_i_1_r_3_t_7_cnt;
//	t_cnt[8] = t_cnt[8] + PKTStore::pktRepository_i_1_r_0_t_8_cnt + PKTStore::pktRepository_i_1_r_1_t_8_cnt + PKTStore::pktRepository_i_1_r_2_t_9_cnt + PKTStore::pktRepository_i_1_r_3_t_8_cnt;
//	t_cnt[9] = t_cnt[9] + PKTStore::pktRepository_i_1_r_0_t_9_cnt + PKTStore::pktRepository_i_1_r_1_t_9_cnt + PKTStore::pktRepository_i_1_r_2_t_9_cnt + PKTStore::pktRepository_i_1_r_3_t_9_cnt;
//
//	printf("   ");
//	for(i=0; i<10; i++){
//		printf("  %07d", t_cnt[i]);
//		t_cnt[i] = 0;
//	}
//	printf("\n\n");

	t_cnt[0] = t_cnt[0] + PKTStore::pktRepository_i_1_r_0_t_0_cnt;
	t_cnt[1] = t_cnt[1] + PKTStore::pktRepository_i_1_r_0_t_1_cnt;
	t_cnt[2] = t_cnt[2] + PKTStore::pktRepository_i_1_r_0_t_2_cnt;
	t_cnt[3] = t_cnt[3] + PKTStore::pktRepository_i_1_r_0_t_3_cnt;
	t_cnt[4] = t_cnt[4] + PKTStore::pktRepository_i_1_r_0_t_4_cnt;
	t_cnt[5] = t_cnt[5] + PKTStore::pktRepository_i_1_r_0_t_5_cnt;
	t_cnt[6] = t_cnt[6] + PKTStore::pktRepository_i_1_r_0_t_6_cnt;
	t_cnt[7] = t_cnt[7] + PKTStore::pktRepository_i_1_r_0_t_7_cnt;
	t_cnt[8] = t_cnt[8] + PKTStore::pktRepository_i_1_r_0_t_8_cnt;
	t_cnt[9] = t_cnt[9] + PKTStore::pktRepository_i_1_r_0_t_9_cnt;

	printf("   ");
	for(i=0; i<10; i++){
		printf("  %07d", t_cnt[i]);
		t_cnt[i] = 0;
	}
	printf("\n");

	t_cnt[0] = t_cnt[0] + PKTStore::pktRepository_i_1_r_1_t_0_cnt;
	t_cnt[1] = t_cnt[1] + PKTStore::pktRepository_i_1_r_1_t_1_cnt;
	t_cnt[2] = t_cnt[2] + PKTStore::pktRepository_i_1_r_1_t_2_cnt;
	t_cnt[3] = t_cnt[3] + PKTStore::pktRepository_i_1_r_1_t_3_cnt;
	t_cnt[4] = t_cnt[4] + PKTStore::pktRepository_i_1_r_1_t_4_cnt;
	t_cnt[5] = t_cnt[5] + PKTStore::pktRepository_i_1_r_1_t_5_cnt;
	t_cnt[6] = t_cnt[6] + PKTStore::pktRepository_i_1_r_1_t_6_cnt;
	t_cnt[7] = t_cnt[7] + PKTStore::pktRepository_i_1_r_1_t_7_cnt;
	t_cnt[8] = t_cnt[8] + PKTStore::pktRepository_i_1_r_1_t_8_cnt;
	t_cnt[9] = t_cnt[9] + PKTStore::pktRepository_i_1_r_1_t_9_cnt;

	printf("                                                              ");
	for(i=0; i<10; i++){
		printf("  %07d", t_cnt[i]);
		t_cnt[i] = 0;
	}
	printf("\n\n");
}

VOID ProbeStats::printSccpSessionStoreStats_i_0()
{

	if(!GContainer::config->IUPS_PROBE) return;

	int i = 0;
	int t_cnt[10];
	for(i=0; i<10; i++)
		t_cnt[i] = 0;

	t_cnt[0] = 	SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_0_cnt + SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_0_cnt;
	t_cnt[1] = 	SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_1_cnt + SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_1_cnt;
	t_cnt[2] = 	SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_2_cnt + SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_2_cnt;
	t_cnt[3] = 	SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_3_cnt + SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_3_cnt;
	t_cnt[4] = 	SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_4_cnt + SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_4_cnt;
	t_cnt[5] = 	SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_5_cnt + SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_5_cnt;
	t_cnt[6] = 	SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_6_cnt + SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_6_cnt;
	t_cnt[7] = 	SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_7_cnt + SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_7_cnt;
	t_cnt[8] = 	SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_8_cnt + SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_8_cnt;
	t_cnt[9] = 	SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_9_cnt + SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_9_cnt;

	printf("    imsi_map %07d  tmsi_map %07d           sm0 Mpkts -> ",IUPSGlobal::IMSI_TMSI_MAP_SIZE, IUPSGlobal::TMSI_IMSI_MAP_SIZE);

	for(i=0; i<10; i++){
		printf("  %07d",	t_cnt[i]);
		t_cnt[i] = 0;
	}
	printf("\n");
	printf("\n");

}

VOID ProbeStats::printSccpSessionStoreStats_i_1()
{

	if(!GContainer::config->IUPS_PROBE) return;

	int i = 0;
	int t_cnt[10];
	for(i=0; i<10; i++)
		t_cnt[i] = 0;

	t_cnt[0] = 	SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_0_cnt + SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_0_cnt;
	t_cnt[1] = 	SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_1_cnt + SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_1_cnt;
	t_cnt[2] = 	SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_2_cnt + SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_2_cnt;
	t_cnt[3] = 	SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_3_cnt + SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_3_cnt;
	t_cnt[4] = 	SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_4_cnt + SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_4_cnt;
	t_cnt[5] = 	SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_5_cnt + SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_5_cnt;
	t_cnt[6] = 	SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_6_cnt + SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_6_cnt;
	t_cnt[7] = 	SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_7_cnt + SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_7_cnt;
	t_cnt[8] = 	SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_8_cnt + SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_8_cnt;
	t_cnt[9] = 	SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_9_cnt + SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_9_cnt;

	printf("                                                 sm0 Mpkts -> ");

	for(i=0; i<10; i++){
		printf("  %07d",	t_cnt[i]);
		t_cnt[i] = 0;
	}
	printf("\n");
	printf("\n");
	printf("\n");
}

VOID ProbeStats::printGTPSessionStoreStats_i_0()
{
	int i = 0;
	int t_cnt[10];
	for(i=0; i<10; i++)
		t_cnt[i] = 0;

	uint32_t poolSize = IP_SESSION_POOL_ARRAY_SIZE * IP_SESSION_POOL_ARRAY_ELEMENTS;

	t_cnt[0] = 	GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_0_cnt;
	t_cnt[1] = 	GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_1_cnt;
	t_cnt[2] = 	GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_2_cnt;
	t_cnt[3] = 	GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_3_cnt;
	t_cnt[4] = 	GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_4_cnt;
	t_cnt[5] = 	GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_5_cnt;
	t_cnt[6] = 	GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_6_cnt;
	t_cnt[7] = 	GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_7_cnt;
	t_cnt[8] = 	GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_8_cnt;
	t_cnt[9] = 	GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_9_cnt;

	printf("                                                 sm0 Mpkts -> ");
//	printf("   %07d  %016lu    %0.2f    sm0 Mpkts -> ",IPGlobal::FREE_INDEX_CNT_SM_0,IPGlobal::FREE_INDEX_DUR_SM_0, IPGlobal::FREE_INDEX_DUR_SM_0 / IPGlobal::FREE_INDEX_CNT_SM_0);
//	printf("   %09lu    %09u    %011u         sm0 Mpkts -> ",IPStats::ip_session_repo_busy_sm_0_cnt,GTPStats::gtp_glb_sessions_cnt,totPdpCr);
//	printf("   ipS %07lu   scn %07lu  cln (%07lu)      sm0 Mpkts -> ",IPStats::ip_session_repo_busy_sm_0_cnt, IPStats::ip_session_total_sm_0_cnt, IPStats::ip_session_cleaned_tcp_sm_0_cnt + IPStats::ip_session_cleaned_udp_sm_0_cnt);

	 //long ipBusyCount = IPStats::ip_session_repo_busy_sm_0_cnt +
	//					  IPStats::ip_session_repo_busy_sm_1_cnt +
	//					  IPStats::ip_session_repo_busy_sm_2_cnt +
	//					  IPStats::ip_session_repo_busy_sm_3_cnt;

	for(i=0; i<10; i++){
		printf("  %07d",	t_cnt[i]);
		t_cnt[i] = 0;
	}
//	printf("  %07d\n",IPGlobal::FREE_INDEX_CNT_SM_0);
	printf("\n");

	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES > 1){
		t_cnt[0] = GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_0_cnt;
		t_cnt[1] = GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_1_cnt;
		t_cnt[2] = GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_2_cnt;
		t_cnt[3] = GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_3_cnt;
		t_cnt[4] = GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_4_cnt;
		t_cnt[5] = GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_5_cnt;
		t_cnt[6] = GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_6_cnt;
		t_cnt[7] = GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_7_cnt;
		t_cnt[8] = GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_8_cnt;
		t_cnt[9] = GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_9_cnt;

//		printf("                                                 sm1 Mpkts -> ");
//		printf("   %07d  %016lu    %0.2f    sm1 Mpkts -> ",IPGlobal::FREE_INDEX_CNT_SM_1,IPGlobal::FREE_INDEX_DUR_SM_1, IPGlobal::FREE_INDEX_DUR_SM_1 / IPGlobal::FREE_INDEX_CNT_SM_1);
//		printf("   %09lu    %09u                        sm1 Mpkts -> ",IPStats::ip_session_repo_busy_sm_1_cnt,GTPStats::gtp_glb_sessions_op_cr_cnt);
//		printf("   %09lu    %09u    %011u         sm1 Mpkts -> ",IPStats::ip_session_repo_busy_sm_1_cnt,GTPStats::gtp_glb_sessions_op_cr_cnt,totPdpUp);
		printf("   ipS %07d   scn %07d  cln %06d %06d  sm1 Mpkts -> ",IPStats::ip_session_total_sm_1_cnt, IPStats::ip_session_scanned_sm_1_cnt, IPStats::ip_session_cleaned_tcp_sm_1_cnt, IPStats::ip_session_cleaned_udp_sm_1_cnt);

		for(i=0; i<10; i++){
			printf("  %07d",	t_cnt[i]);
			t_cnt[i] = 0;
		}
//		printf("  %07d\n",IPGlobal::FREE_INDEX_CNT_SM_1);
		printf("\n");
	}

	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES > 2){
		t_cnt[0] = GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_0_cnt;
		t_cnt[1] = GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_1_cnt;
		t_cnt[2] = GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_2_cnt;
		t_cnt[3] = GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_3_cnt;
		t_cnt[4] = GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_4_cnt;
		t_cnt[5] = GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_5_cnt;
		t_cnt[6] = GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_6_cnt;
		t_cnt[7] = GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_7_cnt;
		t_cnt[8] = GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_8_cnt;
		t_cnt[9] = GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_9_cnt;

//		printf("                                                 sm2 Mpkts -> ");
//		printf("   %07d  %016lu    %0.2f    sm2 Mpkts -> ",IPGlobal::FREE_INDEX_CNT_SM_2,IPGlobal::FREE_INDEX_DUR_SM_2, IPGlobal::FREE_INDEX_DUR_SM_2 / IPGlobal::FREE_INDEX_CNT_SM_2);
//		printf("   %09lu    %09u                        sm2 Mpkts -> ",IPStats::ip_session_repo_busy_sm_2_cnt,GTPStats::gtp_glb_sessions_op_dl_cnt);
//		printf("   %09lu    %09u    %011u         sm2 Mpkts -> ",IPStats::ip_session_repo_busy_sm_2_cnt,GTPStats::gtp_glb_sessions_op_up_cnt,totPdpDl);
		printf("   ipS %07d   scn %07d  cln %06d %06d  sm2 Mpkts -> ",IPStats::ip_session_total_sm_2_cnt, IPStats::ip_session_scanned_sm_2_cnt, IPStats::ip_session_cleaned_tcp_sm_2_cnt, IPStats::ip_session_cleaned_udp_sm_2_cnt);

		for(i=0; i<10; i++){
			printf("  %07d",	t_cnt[i]);
			t_cnt[i] = 0;
		}
//		printf("  %07d\n",IPGlobal::FREE_INDEX_CNT_SM_2);
		printf("\n");
	}

	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES > 3){
		t_cnt[0] = GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_0_cnt;
		t_cnt[1] = GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_1_cnt;
		t_cnt[2] = GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_2_cnt;
		t_cnt[3] = GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_3_cnt;
		t_cnt[4] = GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_4_cnt;
		t_cnt[5] = GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_5_cnt;
		t_cnt[6] = GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_6_cnt;
		t_cnt[7] = GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_7_cnt;
		t_cnt[8] = GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_8_cnt;
		t_cnt[9] = GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_9_cnt;

//		printf("                                                 sm3 Mpkts -> ");
//		printf("   %07d  %016lu    %0.2f    sm3 Mpkts -> ",IPGlobal::FREE_INDEX_CNT_SM_3,IPGlobal::FREE_INDEX_DUR_SM_3, IPGlobal::FREE_INDEX_DUR_SM_3 / IPGlobal::FREE_INDEX_CNT_SM_3);
//		printf("   %09lu    %09u                        sm3 Mpkts -> ",IPStats::ip_session_repo_busy_sm_3_cnt,GTPStats::gtp_glb_sessions_op_dl_cnt);
		printf("   ipS %07d   scn %07d  cln %06d %06d  sm3 Mpkts -> ",IPStats::ip_session_total_sm_3_cnt, IPStats::ip_session_scanned_sm_3_cnt, IPStats::ip_session_cleaned_tcp_sm_3_cnt, IPStats::ip_session_cleaned_udp_sm_3_cnt);
		for(i=0; i<10; i++){
			printf("  %07d",	t_cnt[i]);
			t_cnt[i] = 0;
		}
//		printf("  %07d\n",IPGlobal::FREE_INDEX_CNT_SM_3);
		printf("\n");
	}

	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES > 4){
		t_cnt[0] = GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_0_cnt;
		t_cnt[1] = GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_1_cnt;
		t_cnt[2] = GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_2_cnt;
		t_cnt[3] = GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_3_cnt;
		t_cnt[4] = GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_4_cnt;
		t_cnt[5] = GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_5_cnt;
		t_cnt[6] = GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_6_cnt;
		t_cnt[7] = GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_7_cnt;
		t_cnt[8] = GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_8_cnt;
		t_cnt[9] = GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_9_cnt;

//		printf("                                                 sm3 Mpkts -> ");
//		printf("   %07d  %016lu    %0.2f    sm3 Mpkts -> ",IPGlobal::FREE_INDEX_CNT_sm_4,IPGlobal::FREE_INDEX_DUR_sm_4, IPGlobal::FREE_INDEX_DUR_sm_4 / IPGlobal::FREE_INDEX_CNT_sm_4);
//		printf("   %09lu    %09u                        sm3 Mpkts -> ",IPStats::ip_session_repo_busy_sm_4_cnt,GTPStats::gtp_glb_sessions_op_dl_cnt);
		printf("   ipS %07d   scn %07d  cln %06d %06d  sm4 Mpkts -> ",IPStats::ip_session_total_sm_4_cnt, IPStats::ip_session_scanned_sm_4_cnt, IPStats::ip_session_cleaned_tcp_sm_4_cnt, IPStats::ip_session_cleaned_udp_sm_4_cnt);
		for(i=0; i<10; i++){
			printf("  %07d",	t_cnt[i]);
			t_cnt[i] = 0;
		}
//		printf("  %07d\n",IPGlobal::FREE_INDEX_CNT_SM_3);
		printf("\n");
	}

	printf("\n");
}

VOID ProbeStats::printGTPSessionStoreStats_i_1()
{
	uint64_t totProcessed = 0;
	uint64_t totRej = 0;
	uint64_t largePktsDiscarded = 0;
	uint64_t finOnlySessions = 0;

//	uint64_t totPdpCrReq = GTPStats::gtpc_pdp_cr_req_sm_0 + GTPStats::gtpc_pdp_cr_req_sm_1 + GTPStats::gtpc_pdp_cr_req_sm_2 + GTPStats::gtpc_pdp_cr_req_sm_3;
//	uint64_t totPdpUpReq = GTPStats::gtpc_pdp_up_req_sm_0 + GTPStats::gtpc_pdp_up_req_sm_1 + GTPStats::gtpc_pdp_up_req_sm_2 + GTPStats::gtpc_pdp_up_req_sm_3;
//	uint64_t totPdpDlReq = GTPStats::gtpc_pdp_dl_req_sm_0 + GTPStats::gtpc_pdp_dl_req_sm_1 + GTPStats::gtpc_pdp_dl_req_sm_2 + GTPStats::gtpc_pdp_dl_req_sm_3;

	int i = 0;
	int t_cnt[10];
	for(i=0; i<10; i++)
		t_cnt[i] = 0;

	totProcessed =  IPGlobal::ip_processed_packets_i_0_r_0 + IPGlobal::ip_processed_packets_i_0_r_1 + IPGlobal::ip_processed_packets_i_0_r_2 + IPGlobal::ip_processed_packets_i_0_r_3;
				  + IPGlobal::ip_processed_packets_i_1_r_0 + IPGlobal::ip_processed_packets_i_1_r_1 + IPGlobal::ip_processed_packets_i_1_r_2 + IPGlobal::ip_processed_packets_i_1_r_3;
				  + IPGlobal::ip_processed_packets_i_2_r_0 + IPGlobal::ip_processed_packets_i_2_r_1 + IPGlobal::ip_processed_packets_i_2_r_2 + IPGlobal::ip_processed_packets_i_2_r_3;
				  + IPGlobal::ip_processed_packets_i_3_r_0 + IPGlobal::ip_processed_packets_i_3_r_1 + IPGlobal::ip_processed_packets_i_3_r_2 + IPGlobal::ip_processed_packets_i_3_r_3;

	largePktsDiscarded = IPGlobal::ip_discarded_large_packets_i_0 + IPGlobal::ip_discarded_large_packets_i_1 + IPGlobal::ip_discarded_large_packets_i_2 + IPGlobal::ip_discarded_large_packets_i_3;

	totRej =  IPGlobal::ip_discarded_packets_i_0_r_0 + IPGlobal::ip_discarded_packets_i_0_r_1 + IPGlobal::ip_discarded_packets_i_0_r_2 + IPGlobal::ip_discarded_packets_i_0_r_3;
			+ IPGlobal::ip_discarded_packets_i_1_r_0 + IPGlobal::ip_discarded_packets_i_1_r_1 + IPGlobal::ip_discarded_packets_i_1_r_2 + IPGlobal::ip_discarded_packets_i_1_r_3;
			+ IPGlobal::ip_discarded_packets_i_2_r_0 + IPGlobal::ip_discarded_packets_i_2_r_1 + IPGlobal::ip_discarded_packets_i_2_r_2 + IPGlobal::ip_discarded_packets_i_2_r_3;
			+ IPGlobal::ip_discarded_packets_i_3_r_0 + IPGlobal::ip_discarded_packets_i_3_r_1 + IPGlobal::ip_discarded_packets_i_3_r_2 + IPGlobal::ip_discarded_packets_i_3_r_3;

	finOnlySessions = IPStats::ip_session_fin_only_sm_0_cnt + IPStats::ip_session_fin_only_sm_1_cnt + IPStats::ip_session_fin_only_sm_2_cnt + IPStats::ip_session_fin_only_sm_3_cnt;

	uint32_t poolSize = IP_SESSION_POOL_ARRAY_SIZE * IP_SESSION_POOL_ARRAY_ELEMENTS;

	t_cnt[0] = 	GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_0_cnt;
	t_cnt[1] = 	GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_1_cnt;
	t_cnt[2] = 	GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_2_cnt;
	t_cnt[3] = 	GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_3_cnt;
	t_cnt[4] = 	GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_4_cnt;
	t_cnt[5] = 	GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_5_cnt;
	t_cnt[6] = 	GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_6_cnt;
	t_cnt[7] = 	GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_7_cnt;
	t_cnt[8] = 	GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_8_cnt;
	t_cnt[9] = 	GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_9_cnt;

//	printf("                                                 sm0 Mpkts -> ");
//	printf("   %07d  %016lu    %0.2f    sm0 Mpkts -> ",IPGlobal::FREE_INDEX_CNT_SM_0,IPGlobal::FREE_INDEX_DUR_SM_0, IPGlobal::FREE_INDEX_DUR_SM_0 / IPGlobal::FREE_INDEX_CNT_SM_0);
//	printf("   %'11lu (%011lu)  %011lu        sm0 Mpkts -> ",IPStats::ip_session_repo_busy_sm_0_cnt,IPStats::ip_session_repo_free_sm_0_cnt, totRej);//poolSize);
//	printf("   %011lu (%08lu)  %015lu       sm0 Mpkts -> ",IPStats::ip_session_total_sm_0_cnt, IPStats::ip_session_cleaned_tcp_sm_0_cnt + IPStats::ip_session_cleaned_udp_sm_0_cnt, totProcessed);
//	printf("   glbS %08lu(%08lu)  Pkt %014lu   sm0 Mpkts -> ",GTPStats::gtp_glb_sessions_cnt, GTPStats::gtp_glb_active_sessions_cnt, totProcessed);
	printf("   glbS %08d %07lu    Pkt %014lu   sm0 Mpkts -> ",GTPStats::gtp_glb_active_sessions_cnt, GTPStats::gtp_glb_inactive_session_cln_cnt, totProcessed);
		 //long ipBusyCount = IPStats::ip_session_repo_busy_sm_0_cnt +
	//					  IPStats::ip_session_repo_busy_sm_1_cnt +
	//					  IPStats::ip_session_repo_busy_sm_2_cnt +
	//					  IPStats::ip_session_repo_busy_sm_3_cnt;

	for(i=0; i<10; i++){
		printf("  %07d",	t_cnt[i]);
		t_cnt[i] = 0;
	}
//	printf("  %07d\n",IPGlobal::FREE_INDEX_CNT_SM_0);
	printf("\n");

	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES > 1){
		t_cnt[0] = GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_0_cnt;
		t_cnt[1] = GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_1_cnt;
		t_cnt[2] = GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_2_cnt;
		t_cnt[3] = GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_3_cnt;
		t_cnt[4] = GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_4_cnt;
		t_cnt[5] = GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_5_cnt;
		t_cnt[6] = GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_6_cnt;
		t_cnt[7] = GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_7_cnt;
		t_cnt[8] = GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_8_cnt;
		t_cnt[9] = GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_9_cnt;

//		printf("                                                 sm1 Mpkts -> ");
//		printf("   %07d  %016lu    %0.2f    sm1 Mpkts -> ",IPGlobal::FREE_INDEX_CNT_SM_1,IPGlobal::FREE_INDEX_DUR_SM_1, IPGlobal::FREE_INDEX_DUR_SM_1 / IPGlobal::FREE_INDEX_CNT_SM_1);
//		printf("   %011u (%011u)                     sm1 Mpkts -> ",IPStats::ip_session_total_sm_1_cnt, IPStats::ip_session_cleaned_tcp_sm_1_cnt + IPStats::ip_session_cleaned_udp_sm_1_cnt);
		printf("   glbC %08lu %07d cU ipv6 %010lu      sm1 Mpkts -> ",GTPStats::gtp_glb_sessions_op_cr_cnt, GTPStats::gtp_glb_ctl_up_cnt, totRej);

		for(i=0; i<10; i++){
			printf("  %07d",	t_cnt[i]);
			t_cnt[i] = 0;
		}
//		printf("  %07d\n",IPGlobal::FREE_INDEX_CNT_SM_1);
		printf("\n");
	}

	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES > 2){
		t_cnt[0] = GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_0_cnt;
		t_cnt[1] = GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_1_cnt;
		t_cnt[2] = GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_2_cnt;
		t_cnt[3] = GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_3_cnt;
		t_cnt[4] = GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_4_cnt;
		t_cnt[5] = GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_5_cnt;
		t_cnt[6] = GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_6_cnt;
		t_cnt[7] = GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_7_cnt;
		t_cnt[8] = GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_8_cnt;
		t_cnt[9] = GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_9_cnt;

//		printf("                                                 sm2 Mpkts -> ");
//		printf("   %07d  %016lu    %0.2f    sm2 Mpkts -> ",IPGlobal::FREE_INDEX_CNT_SM_2,IPGlobal::FREE_INDEX_DUR_SM_2, IPGlobal::FREE_INDEX_DUR_SM_2 / IPGlobal::FREE_INDEX_CNT_SM_2);
//		printf("   %011u (%08u)                        sm2 Mpkts -> ",IPStats::ip_session_total_sm_2_cnt, IPStats::ip_session_cleaned_tcp_sm_2_cnt + IPStats::ip_session_cleaned_udp_sm_2_cnt);
		//printf("   %011lu (%08lu)  %015lu       sm2 Mpkts -> ",IPStats::ip_session_total_sm_2_cnt, IPStats::ip_session_cleaned_tcp_sm_2_cnt + IPStats::ip_session_cleaned_udp_sm_2_cnt, finOnlySessions);
		printf("   glbU %08lu %07d dU finP %010lu      sm2 Mpkts -> ",GTPStats::gtp_glb_sessions_op_up_cnt, GTPStats::gtp_glb_data_up_cnt, finOnlySessions);
		for(i=0; i<10; i++){
			printf("  %07d",	t_cnt[i]);
			t_cnt[i] = 0;
		}
//		printf("  %07d\n",IPGlobal::FREE_INDEX_CNT_SM_2);
		printf("\n");
	}

	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES > 3){
		t_cnt[0] = GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_0_cnt;
		t_cnt[1] = GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_1_cnt;
		t_cnt[2] = GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_2_cnt;
		t_cnt[3] = GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_3_cnt;
		t_cnt[4] = GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_4_cnt;
		t_cnt[5] = GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_5_cnt;
		t_cnt[6] = GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_6_cnt;
		t_cnt[7] = GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_7_cnt;
		t_cnt[8] = GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_8_cnt;
		t_cnt[9] = GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_9_cnt;

//		printf("                                                 sm3 Mpkts -> ");
//		printf("   %07d  %016lu    %0.2f    sm3 Mpkts -> ",IPGlobal::FREE_INDEX_CNT_SM_3,IPGlobal::FREE_INDEX_DUR_SM_3, IPGlobal::FREE_INDEX_DUR_SM_3 / IPGlobal::FREE_INDEX_CNT_SM_3);
//		printf("   %011u (%08u)                        sm3 Mpkts -> ",IPStats::ip_session_total_sm_3_cnt, IPStats::ip_session_cleaned_tcp_sm_3_cnt + IPStats::ip_session_cleaned_udp_sm_3_cnt);
		printf("   glbD %08lu %07d cD dnsD %010lu      sm3 Mpkts -> ",GTPStats::gtp_glb_sessions_op_dl_cnt, GTPStats::gtp_glb_ctl_dn_cnt, IPStats::dns_resolved_lookup_size);
		for(i=0; i<10; i++){
			printf("  %07d",	t_cnt[i]);
			t_cnt[i] = 0;
		}
//		printf("  %07d\n",IPGlobal::FREE_INDEX_CNT_SM_3);
		printf("\n");
	}

	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES > 4){
		t_cnt[0] = GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_0_cnt;
		t_cnt[1] = GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_1_cnt;
		t_cnt[2] = GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_2_cnt;
		t_cnt[3] = GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_3_cnt;
		t_cnt[4] = GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_4_cnt;
		t_cnt[5] = GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_5_cnt;
		t_cnt[6] = GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_6_cnt;
		t_cnt[7] = GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_7_cnt;
		t_cnt[8] = GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_8_cnt;
		t_cnt[9] = GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_9_cnt;

//		printf("                                                 sm3 Mpkts -> ");
//		printf("   %07d  %016lu    %0.2f    sm3 Mpkts -> ",IPGlobal::FREE_INDEX_CNT_sm_4,IPGlobal::FREE_INDEX_DUR_sm_4, IPGlobal::FREE_INDEX_DUR_sm_4 / IPGlobal::FREE_INDEX_CNT_sm_4);
//		printf("   %011u (%08u)                        sm3 Mpkts -> ",IPStats::ip_session_total_sm_4_cnt, IPStats::ip_session_cleaned_tcp_sm_4_cnt + IPStats::ip_session_cleaned_udp_sm_4_cnt);
		printf("   glbF %08d %07d dD dnsL %010lu      sm4 Mpkts -> ",GTPStore::freeGlbBitPos, GTPStats::gtp_glb_data_dn_cnt, IPStats::dns_lookup_map_size);//largePktsDiscarded);
		for(i=0; i<10; i++){
			printf("  %07d",	t_cnt[i]);
			t_cnt[i] = 0;
		}
//		printf("  %07d\n",IPGlobal::FREE_INDEX_CNT_sm_4);
		printf("\n");
	}

	printf("\n");
}


VOID ProbeStats::printGTPSessionStoreStats()
{
	int i = 0;

//	int totalCount[10];
	int t_cnt[10];
	for(i=0; i<10; i++)
	{
//		totalCount[i] = 0;
		t_cnt[i] = 0;
	}

	if(IPGlobal::NO_OF_INTERFACES > 0){
		t_cnt[0] = 	GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_0_cnt;
		t_cnt[1] = 	GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_1_cnt;
		t_cnt[2] = 	GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_2_cnt;
		t_cnt[3] = 	GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_3_cnt;
		t_cnt[4] = 	GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_4_cnt;
		t_cnt[5] = 	GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_5_cnt;
		t_cnt[6] = 	GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_6_cnt;
		t_cnt[7] = 	GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_7_cnt;
		t_cnt[8] = 	GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_8_cnt;
		t_cnt[9] = 	GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_9_cnt;
	}
	if(IPGlobal::NO_OF_INTERFACES > 1){
		t_cnt[0] += GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_0_cnt;
		t_cnt[1] += GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_1_cnt;
		t_cnt[2] += GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_2_cnt;
		t_cnt[3] += GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_3_cnt;
		t_cnt[4] += GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_4_cnt;
		t_cnt[5] += GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_5_cnt;
		t_cnt[6] += GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_6_cnt;
		t_cnt[7] += GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_7_cnt;
		t_cnt[8] += GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_8_cnt;
		t_cnt[9] += GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_9_cnt;
	}
	if(IPGlobal::NO_OF_INTERFACES > 2){
		t_cnt[0] += GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_0_cnt;
		t_cnt[1] += GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_1_cnt;
		t_cnt[2] += GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_2_cnt;
		t_cnt[3] += GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_3_cnt;
		t_cnt[4] += GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_4_cnt;
		t_cnt[5] += GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_5_cnt;
		t_cnt[6] += GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_6_cnt;
		t_cnt[7] += GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_7_cnt;
		t_cnt[8] += GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_8_cnt;
		t_cnt[9] += GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_9_cnt;
	}
	if(IPGlobal::NO_OF_INTERFACES > 3){
		t_cnt[0] += GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_0_cnt;
		t_cnt[1] += GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_1_cnt;
		t_cnt[2] += GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_2_cnt;
		t_cnt[3] += GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_3_cnt;
		t_cnt[4] += GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_4_cnt;
		t_cnt[5] += GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_5_cnt;
		t_cnt[6] += GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_6_cnt;
		t_cnt[7] += GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_7_cnt;
		t_cnt[8] += GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_8_cnt;
		t_cnt[9] += GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_9_cnt;
	}

	printf("                               sm0 Mpkts -> ");
	for(i=0; i<10; i++){
		printf("  %07d",	t_cnt[i]);
//		totalCount[i] += t_cnt[i];
		t_cnt[i] = 0;
	}
	printf("\n");

	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES > 1){
		if(IPGlobal::NO_OF_INTERFACES > 0){
			t_cnt[0] = GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_0_cnt;
			t_cnt[1] = GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_1_cnt;
			t_cnt[2] = GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_2_cnt;
			t_cnt[3] = GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_3_cnt;
			t_cnt[4] = GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_4_cnt;
			t_cnt[5] = GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_5_cnt;
			t_cnt[6] = GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_6_cnt;
			t_cnt[7] = GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_7_cnt;
			t_cnt[8] = GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_8_cnt;
			t_cnt[9] = GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_9_cnt;
		}
		if(IPGlobal::NO_OF_INTERFACES > 1){
			t_cnt[0] += GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_0_cnt;
			t_cnt[1] += GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_1_cnt;
			t_cnt[2] += GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_2_cnt;
			t_cnt[3] += GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_3_cnt;
			t_cnt[4] += GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_4_cnt;
			t_cnt[5] += GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_5_cnt;
			t_cnt[6] += GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_6_cnt;
			t_cnt[7] += GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_7_cnt;
			t_cnt[8] += GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_8_cnt;
			t_cnt[9] += GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_9_cnt;
		}
		if(IPGlobal::NO_OF_INTERFACES > 2){
			t_cnt[0] += GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_0_cnt;
			t_cnt[1] += GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_1_cnt;
			t_cnt[2] += GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_2_cnt;
			t_cnt[3] += GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_3_cnt;
			t_cnt[4] += GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_4_cnt;
			t_cnt[5] += GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_5_cnt;
			t_cnt[6] += GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_6_cnt;
			t_cnt[7] += GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_7_cnt;
			t_cnt[8] += GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_8_cnt;
			t_cnt[9] += GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_9_cnt;
		}
		if(IPGlobal::NO_OF_INTERFACES > 3){
			t_cnt[0] += GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_0_cnt;
			t_cnt[1] += GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_1_cnt;
			t_cnt[2] += GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_2_cnt;
			t_cnt[3] += GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_3_cnt;
			t_cnt[4] += GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_4_cnt;
			t_cnt[5] += GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_5_cnt;
			t_cnt[6] += GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_6_cnt;
			t_cnt[7] += GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_7_cnt;
			t_cnt[8] += GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_8_cnt;
			t_cnt[9] += GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_9_cnt;
		}

		printf("                               sm1 Mpkts -> ");
		for(i=0; i<10; i++){
			printf("  %07d",	t_cnt[i]);
//			totalCount[i] += t_cnt[i];
			t_cnt[i] = 0;
		}
		printf("\n");
	}

	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES > 2){
		if(IPGlobal::NO_OF_INTERFACES > 0){
			t_cnt[0] = GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_0_cnt;
			t_cnt[1] = GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_1_cnt;
			t_cnt[2] = GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_2_cnt;
			t_cnt[3] = GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_3_cnt;
			t_cnt[4] = GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_4_cnt;
			t_cnt[5] = GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_5_cnt;
			t_cnt[6] = GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_6_cnt;
			t_cnt[7] = GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_7_cnt;
			t_cnt[8] = GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_8_cnt;
			t_cnt[9] = GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_9_cnt;
		}
		if(IPGlobal::NO_OF_INTERFACES > 1){
			t_cnt[0] += GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_0_cnt;
			t_cnt[1] += GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_1_cnt;
			t_cnt[2] += GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_2_cnt;
			t_cnt[3] += GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_3_cnt;
			t_cnt[4] += GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_4_cnt;
			t_cnt[5] += GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_5_cnt;
			t_cnt[6] += GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_6_cnt;
			t_cnt[7] += GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_7_cnt;
			t_cnt[8] += GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_8_cnt;
			t_cnt[9] += GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_9_cnt;
		}
		if(IPGlobal::NO_OF_INTERFACES > 2){
			t_cnt[0] += GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_0_cnt;
			t_cnt[1] += GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_1_cnt;
			t_cnt[2] += GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_2_cnt;
			t_cnt[3] += GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_3_cnt;
			t_cnt[4] += GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_4_cnt;
			t_cnt[5] += GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_5_cnt;
			t_cnt[6] += GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_6_cnt;
			t_cnt[7] += GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_7_cnt;
			t_cnt[8] += GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_8_cnt;
			t_cnt[9] += GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_9_cnt;
		}
		if(IPGlobal::NO_OF_INTERFACES > 3){
			t_cnt[0] += GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_0_cnt;
			t_cnt[1] += GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_1_cnt;
			t_cnt[2] += GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_2_cnt;
			t_cnt[3] += GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_3_cnt;
			t_cnt[4] += GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_4_cnt;
			t_cnt[5] += GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_5_cnt;
			t_cnt[6] += GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_6_cnt;
			t_cnt[7] += GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_7_cnt;
			t_cnt[8] += GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_8_cnt;
			t_cnt[9] += GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_9_cnt;
		}

		printf("                               sm2 Mpkts -> ");
		for(i=0; i<10; i++){
			printf("  %07d",	t_cnt[i]);
//			totalCount[i] += t_cnt[i];
			t_cnt[i] = 0;
		}
		printf("\n");
	}

	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES > 3){
		if(IPGlobal::NO_OF_INTERFACES > 0){
			t_cnt[0] = GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_0_cnt;
			t_cnt[1] = GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_1_cnt;
			t_cnt[2] = GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_2_cnt;
			t_cnt[3] = GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_3_cnt;
			t_cnt[4] = GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_4_cnt;
			t_cnt[5] = GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_5_cnt;
			t_cnt[6] = GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_6_cnt;
			t_cnt[7] = GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_7_cnt;
			t_cnt[8] = GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_8_cnt;
			t_cnt[9] = GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_9_cnt;
		}
		if(IPGlobal::NO_OF_INTERFACES > 1){
			t_cnt[0] += GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_0_cnt;
			t_cnt[1] += GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_1_cnt;
			t_cnt[2] += GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_2_cnt;
			t_cnt[3] += GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_3_cnt;
			t_cnt[4] += GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_4_cnt;
			t_cnt[5] += GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_5_cnt;
			t_cnt[6] += GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_6_cnt;
			t_cnt[7] += GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_7_cnt;
			t_cnt[8] += GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_8_cnt;
			t_cnt[9] += GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_9_cnt;
		}
		if(IPGlobal::NO_OF_INTERFACES > 2){
			t_cnt[0] += GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_0_cnt;
			t_cnt[1] += GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_1_cnt;
			t_cnt[2] += GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_2_cnt;
			t_cnt[3] += GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_3_cnt;
			t_cnt[4] += GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_4_cnt;
			t_cnt[5] += GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_5_cnt;
			t_cnt[6] += GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_6_cnt;
			t_cnt[7] += GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_7_cnt;
			t_cnt[8] += GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_8_cnt;
			t_cnt[9] += GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_9_cnt;
		}
		if(IPGlobal::NO_OF_INTERFACES > 3){
			t_cnt[0] += GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_0_cnt;
			t_cnt[1] += GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_1_cnt;
			t_cnt[2] += GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_2_cnt;
			t_cnt[3] += GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_3_cnt;
			t_cnt[4] += GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_4_cnt;
			t_cnt[5] += GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_5_cnt;
			t_cnt[6] += GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_6_cnt;
			t_cnt[7] += GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_7_cnt;
			t_cnt[8] += GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_8_cnt;
			t_cnt[9] += GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_9_cnt;
		}

		printf("                               sm3 Mpkts -> ");
		for(i=0; i<10; i++){
			printf("  %07d",	t_cnt[i]);
//			totalCount[i] += t_cnt[i];
			t_cnt[i] = 0;
		}
		printf("\n");
	}


	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES > 4){
		if(IPGlobal::NO_OF_INTERFACES > 0){
			t_cnt[0] = GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_0_cnt;
			t_cnt[1] = GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_1_cnt;
			t_cnt[2] = GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_2_cnt;
			t_cnt[3] = GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_3_cnt;
			t_cnt[4] = GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_4_cnt;
			t_cnt[5] = GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_5_cnt;
			t_cnt[6] = GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_6_cnt;
			t_cnt[7] = GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_7_cnt;
			t_cnt[8] = GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_8_cnt;
			t_cnt[9] = GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_9_cnt;
		}
		if(IPGlobal::NO_OF_INTERFACES > 1){
			t_cnt[0] += GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_0_cnt;
			t_cnt[1] += GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_1_cnt;
			t_cnt[2] += GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_2_cnt;
			t_cnt[3] += GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_3_cnt;
			t_cnt[4] += GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_4_cnt;
			t_cnt[5] += GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_5_cnt;
			t_cnt[6] += GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_6_cnt;
			t_cnt[7] += GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_7_cnt;
			t_cnt[8] += GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_8_cnt;
			t_cnt[9] += GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_9_cnt;
		}
		if(IPGlobal::NO_OF_INTERFACES > 2){
			t_cnt[0] += GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_0_cnt;
			t_cnt[1] += GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_1_cnt;
			t_cnt[2] += GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_2_cnt;
			t_cnt[3] += GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_3_cnt;
			t_cnt[4] += GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_4_cnt;
			t_cnt[5] += GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_5_cnt;
			t_cnt[6] += GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_6_cnt;
			t_cnt[7] += GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_7_cnt;
			t_cnt[8] += GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_8_cnt;
			t_cnt[9] += GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_9_cnt;
		}
		if(IPGlobal::NO_OF_INTERFACES > 3){
			t_cnt[0] += GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_0_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_0_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_0_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_0_cnt;
			t_cnt[1] += GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_1_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_1_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_1_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_1_cnt;
			t_cnt[2] += GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_2_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_2_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_2_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_2_cnt;
			t_cnt[3] += GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_3_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_3_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_3_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_3_cnt;
			t_cnt[4] += GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_4_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_4_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_4_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_4_cnt;
			t_cnt[5] += GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_5_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_5_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_5_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_5_cnt;
			t_cnt[6] += GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_6_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_6_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_6_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_6_cnt;
			t_cnt[7] += GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_7_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_7_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_7_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_7_cnt;
			t_cnt[8] += GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_8_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_8_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_8_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_8_cnt;
			t_cnt[9] += GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_9_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_9_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_9_cnt + GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_9_cnt;
		}

		printf("                               sm3 Mpkts -> ");
		for(i=0; i<10; i++){
			printf("  %07d",	t_cnt[i]);
//			totalCount[i] += t_cnt[i];
			t_cnt[i] = 0;
		}
		printf("\n");
	}

//	printf("                                           ------------------------------------------------------------------------------------------\n                                         ");
//	for( i = 0; i < 10; i++ ) {
//		printf("  %07d", totalCount[i]);
//		totalCount[i] = 0;
//	}
//	printf("\n\n");
}

VOID ProbeStats::printGTPcSessionFlushStats()
{
	int i = 0;

	//	int totalCount[10];
	int t_cnt[10];
	for(i=0; i<10; i++)
	{
	//		totalCount[i] = 0;
		t_cnt[i] = 0;
	}

	t_cnt[0] = GTPFlushRepository::gtpcV1FlushMap_sm_0_t_0_cnt;
	t_cnt[1] = GTPFlushRepository::gtpcV1FlushMap_sm_0_t_1_cnt;
	t_cnt[2] = GTPFlushRepository::gtpcV1FlushMap_sm_0_t_2_cnt;
	t_cnt[3] = GTPFlushRepository::gtpcV1FlushMap_sm_0_t_3_cnt;
	t_cnt[4] = GTPFlushRepository::gtpcV1FlushMap_sm_0_t_4_cnt;
	t_cnt[5] = GTPFlushRepository::gtpcV1FlushMap_sm_0_t_5_cnt;
	t_cnt[6] = GTPFlushRepository::gtpcV1FlushMap_sm_0_t_6_cnt;
	t_cnt[7] = GTPFlushRepository::gtpcV1FlushMap_sm_0_t_7_cnt;
	t_cnt[8] = GTPFlushRepository::gtpcV1FlushMap_sm_0_t_8_cnt;
	t_cnt[9] = GTPFlushRepository::gtpcV1FlushMap_sm_0_t_9_cnt;
//	printf("                                               Fl_gtpc_sm0 -> ");
//	printf("   imsiU %07d  Lku %011lu(%011lu) Fl_gtpc_sm0 -> ",GTPStats::unique_imsi_cnt, GTPStats::gtp_get_imsi_suc_cnt, GTPStats::gtp_get_imsi_req_cnt);
	printf("   imsiU %07d                               Fl_gtpc_sm0 -> ",GTPStats::unique_imsi_cnt);
	for(i=0; i<10; i++){
		printf("  %07d",	t_cnt[i]);
//		totalCount[i] += t_cnt[i];
		t_cnt[i] = 0;
	}
	printf("\n");

//	if(IPGlobal::SESSION_MANAGER_INSTANCES > 1){
//		t_cnt[0] = GTPFlushRepository::gtpcV1FlushMap_sm_1_t_0_cnt;
//		t_cnt[1] = GTPFlushRepository::gtpcV1FlushMap_sm_1_t_1_cnt;
//		t_cnt[2] = GTPFlushRepository::gtpcV1FlushMap_sm_1_t_2_cnt;
//		t_cnt[3] = GTPFlushRepository::gtpcV1FlushMap_sm_1_t_3_cnt;
//		t_cnt[4] = GTPFlushRepository::gtpcV1FlushMap_sm_1_t_4_cnt;
//		t_cnt[5] = GTPFlushRepository::gtpcV1FlushMap_sm_1_t_5_cnt;
//		t_cnt[6] = GTPFlushRepository::gtpcV1FlushMap_sm_1_t_6_cnt;
//		t_cnt[7] = GTPFlushRepository::gtpcV1FlushMap_sm_1_t_7_cnt;
//		t_cnt[8] = GTPFlushRepository::gtpcV1FlushMap_sm_1_t_8_cnt;
//		t_cnt[9] = GTPFlushRepository::gtpcV1FlushMap_sm_1_t_9_cnt;
//		printf("                                               Fl_gtpc_sm1 -> ");
//		for(i=0; i<10; i++){
//			printf("  %07d",	t_cnt[i]);
////			totalCount[i] += t_cnt[i];
//			t_cnt[i] = 0;
//		}
//		printf("\n");
//	}
//	if(IPGlobal::SESSION_MANAGER_INSTANCES > 2){
//		t_cnt[0] = GTPFlushRepository::gtpcV1FlushMap_sm_2_t_0_cnt;
//		t_cnt[1] = GTPFlushRepository::gtpcV1FlushMap_sm_2_t_1_cnt;
//		t_cnt[2] = GTPFlushRepository::gtpcV1FlushMap_sm_2_t_2_cnt;
//		t_cnt[3] = GTPFlushRepository::gtpcV1FlushMap_sm_2_t_3_cnt;
//		t_cnt[4] = GTPFlushRepository::gtpcV1FlushMap_sm_2_t_4_cnt;
//		t_cnt[5] = GTPFlushRepository::gtpcV1FlushMap_sm_2_t_5_cnt;
//		t_cnt[6] = GTPFlushRepository::gtpcV1FlushMap_sm_2_t_6_cnt;
//		t_cnt[7] = GTPFlushRepository::gtpcV1FlushMap_sm_2_t_7_cnt;
//		t_cnt[8] = GTPFlushRepository::gtpcV1FlushMap_sm_2_t_8_cnt;
//		t_cnt[9] = GTPFlushRepository::gtpcV1FlushMap_sm_2_t_9_cnt;
//		printf("                                               Fl_gtpc_sm2 -> ");
//		for(i=0; i<10; i++){
//			printf("  %07d",	t_cnt[i]);
////			totalCount[i] += t_cnt[i];
//			t_cnt[i] = 0;
//		}
//		printf("\n");
//	}
//	if(IPGlobal::SESSION_MANAGER_INSTANCES > 3){
//		t_cnt[0] = GTPFlushRepository::gtpcV1FlushMap_sm_3_t_0_cnt;
//		t_cnt[1] = GTPFlushRepository::gtpcV1FlushMap_sm_3_t_1_cnt;
//		t_cnt[2] = GTPFlushRepository::gtpcV1FlushMap_sm_3_t_2_cnt;
//		t_cnt[3] = GTPFlushRepository::gtpcV1FlushMap_sm_3_t_3_cnt;
//		t_cnt[4] = GTPFlushRepository::gtpcV1FlushMap_sm_3_t_4_cnt;
//		t_cnt[5] = GTPFlushRepository::gtpcV1FlushMap_sm_3_t_5_cnt;
//		t_cnt[6] = GTPFlushRepository::gtpcV1FlushMap_sm_3_t_6_cnt;
//		t_cnt[7] = GTPFlushRepository::gtpcV1FlushMap_sm_3_t_7_cnt;
//		t_cnt[8] = GTPFlushRepository::gtpcV1FlushMap_sm_3_t_8_cnt;
//		t_cnt[9] = GTPFlushRepository::gtpcV1FlushMap_sm_3_t_9_cnt;
//		printf("                                               Fl_gtpc_sm3 -> ");
//		for(i=0; i<10; i++){
//			printf("  %07d",	t_cnt[i]);
////			totalCount[i] += t_cnt[i];
//			t_cnt[i] = 0;
//		}
//		printf("\n");
//	}

//	printf("                                           ------------------------------------------------------------------------------------------\n                                         ");
//	for( i = 0; i < 10; i++ ) {
//		printf("  %07d", totalCount[i]);
//		totalCount[i] = 0;
//	}
//	printf("\n");
}

VOID ProbeStats::printIPSessionFlushStats()
{
	int i = 0;

	uint64_t totPdpCrReq = GTPStats::gtpc_pdp_cr_req_sm_0 + GTPStats::gtpc_pdp_cr_req_sm_1 + GTPStats::gtpc_pdp_cr_req_sm_2 + GTPStats::gtpc_pdp_cr_req_sm_3;
	uint64_t totPdpUpReq = GTPStats::gtpc_pdp_up_req_sm_0 + GTPStats::gtpc_pdp_up_req_sm_1 + GTPStats::gtpc_pdp_up_req_sm_2 + GTPStats::gtpc_pdp_up_req_sm_3;
	uint64_t totPdpDlReq = GTPStats::gtpc_pdp_dl_req_sm_0 + GTPStats::gtpc_pdp_dl_req_sm_1 + GTPStats::gtpc_pdp_dl_req_sm_2 + GTPStats::gtpc_pdp_dl_req_sm_3;

	uint64_t totPdpCrRes = GTPStats::gtpc_pdp_cr_res_sm_0 + GTPStats::gtpc_pdp_cr_res_sm_1 + GTPStats::gtpc_pdp_cr_res_sm_2 + GTPStats::gtpc_pdp_cr_res_sm_3;
	uint64_t totPdpUpRes = GTPStats::gtpc_pdp_up_res_sm_0 + GTPStats::gtpc_pdp_up_res_sm_1 + GTPStats::gtpc_pdp_up_res_sm_2 + GTPStats::gtpc_pdp_up_res_sm_3;
	uint64_t totPdpDlRes = GTPStats::gtpc_pdp_dl_res_sm_0 + GTPStats::gtpc_pdp_dl_res_sm_1 + GTPStats::gtpc_pdp_dl_res_sm_2 + GTPStats::gtpc_pdp_dl_res_sm_3;

	uint64_t totPdpCrMapSize = GTPStats::gtp_pdp_cr_session_sm_0 + GTPStats::gtp_pdp_cr_session_sm_1 + GTPStats::gtp_pdp_cr_session_sm_2 + GTPStats::gtp_pdp_cr_session_sm_3;
	uint64_t totPdpUpMapSize = GTPStats::gtp_pdp_up_session_sm_0 + GTPStats::gtp_pdp_up_session_sm_1 + GTPStats::gtp_pdp_up_session_sm_2 + GTPStats::gtp_pdp_up_session_sm_3;
	uint64_t totPdpDlMapSize = GTPStats::gtp_pdp_dl_session_sm_0 + GTPStats::gtp_pdp_dl_session_sm_1 + GTPStats::gtp_pdp_dl_session_sm_2 + GTPStats::gtp_pdp_dl_session_sm_3;

//	uint64_t totPdpCrFlushSize = GTPStats::gtp_pdp_cr_flush_sm_0 + GTPStats::gtp_pdp_cr_flush_sm_1 + GTPStats::gtp_pdp_cr_flush_sm_2 + GTPStats::gtp_pdp_cr_flush_sm_3;
//	uint64_t totPdpUpFlushSize = GTPStats::gtp_pdp_up_flush_sm_0 + GTPStats::gtp_pdp_up_flush_sm_1 + GTPStats::gtp_pdp_up_flush_sm_2 + GTPStats::gtp_pdp_up_flush_sm_3;
//	uint64_t totPdpDlFlushSize = GTPStats::gtp_pdp_dl_flush_sm_0 + GTPStats::gtp_pdp_dl_flush_sm_1 + GTPStats::gtp_pdp_dl_flush_sm_2 + GTPStats::gtp_pdp_dl_flush_sm_3;

	uint64_t totGTPcPkts =
			GTPStats::gtpc_pkt_cnt_i_0_r_0 + GTPStats::gtpc_pkt_cnt_i_1_r_0 + GTPStats::gtpc_pkt_cnt_i_2_r_0 + GTPStats::gtpc_pkt_cnt_i_3_r_0 +
			GTPStats::gtpc_pkt_cnt_i_0_r_1 + GTPStats::gtpc_pkt_cnt_i_1_r_1 + GTPStats::gtpc_pkt_cnt_i_2_r_1 + GTPStats::gtpc_pkt_cnt_i_3_r_1 +
			GTPStats::gtpc_pkt_cnt_i_0_r_2 + GTPStats::gtpc_pkt_cnt_i_1_r_2 + GTPStats::gtpc_pkt_cnt_i_2_r_2 + GTPStats::gtpc_pkt_cnt_i_3_r_2 +
			GTPStats::gtpc_pkt_cnt_i_0_r_3 + GTPStats::gtpc_pkt_cnt_i_1_r_3 + GTPStats::gtpc_pkt_cnt_i_2_r_3 + GTPStats::gtpc_pkt_cnt_i_3_r_3;

	uint64_t totGTPuPkts =
			GTPStats::gtpu_pkt_cnt_i_0_r_0 + GTPStats::gtpu_pkt_cnt_i_1_r_0 + GTPStats::gtpu_pkt_cnt_i_2_r_0 + GTPStats::gtpu_pkt_cnt_i_3_r_0 +
			GTPStats::gtpu_pkt_cnt_i_0_r_1 + GTPStats::gtpu_pkt_cnt_i_1_r_1 + GTPStats::gtpu_pkt_cnt_i_2_r_1 + GTPStats::gtpu_pkt_cnt_i_3_r_1 +
			GTPStats::gtpu_pkt_cnt_i_0_r_2 + GTPStats::gtpu_pkt_cnt_i_1_r_2 + GTPStats::gtpu_pkt_cnt_i_2_r_2 + GTPStats::gtpu_pkt_cnt_i_3_r_2 +
			GTPStats::gtpu_pkt_cnt_i_0_r_3 + GTPStats::gtpu_pkt_cnt_i_1_r_3 + GTPStats::gtpu_pkt_cnt_i_2_r_3 + GTPStats::gtpu_pkt_cnt_i_3_r_3;


	int t_cnt[10];

	for(i=0; i<10; i++)
	{
		t_cnt[i] = 0;
	}
//	t_cnt[0] = IPFlushRepository::ipFlushMap_sm_0_t_0_cnt;
//	t_cnt[1] = IPFlushRepository::ipFlushMap_sm_0_t_1_cnt;
//	t_cnt[2] = IPFlushRepository::ipFlushMap_sm_0_t_2_cnt;
//	t_cnt[3] = IPFlushRepository::ipFlushMap_sm_0_t_3_cnt;
//	t_cnt[4] = IPFlushRepository::ipFlushMap_sm_0_t_4_cnt;
//	t_cnt[5] = IPFlushRepository::ipFlushMap_sm_0_t_5_cnt;
//	t_cnt[6] = IPFlushRepository::ipFlushMap_sm_0_t_6_cnt;
//	t_cnt[7] = IPFlushRepository::ipFlushMap_sm_0_t_7_cnt;
//	t_cnt[8] = IPFlushRepository::ipFlushMap_sm_0_t_8_cnt;
//	t_cnt[9] = IPFlushRepository::ipFlushMap_sm_0_t_9_cnt;
//	printf("   pCRRq %09lu  Res %09lu  Ac %07lu    Fl_ip_sm0 -> ",totPdpCrReq, totPdpCrRes,totPdpCrMapSize);
//
//	for(i=0; i<10; i++){
//		printf("  %07d",	t_cnt[i]);
////		totalCount[i] += t_cnt[i];
//		t_cnt[i] = 0;
//	}
//	printf("\n");

	/* Combined Print */
	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES > 1){
		t_cnt[0] = IPFlushRepository::ipFlushMap_f_0_sm_1_t_0_cnt + IPFlushRepository::ipFlushMap_f_1_sm_1_t_0_cnt + IPFlushRepository::ipFlushMap_f_2_sm_1_t_0_cnt + IPFlushRepository::ipFlushMap_f_3_sm_1_t_0_cnt;
		t_cnt[1] = IPFlushRepository::ipFlushMap_f_0_sm_1_t_1_cnt + IPFlushRepository::ipFlushMap_f_1_sm_1_t_1_cnt + IPFlushRepository::ipFlushMap_f_2_sm_1_t_1_cnt + IPFlushRepository::ipFlushMap_f_3_sm_1_t_1_cnt;
		t_cnt[2] = IPFlushRepository::ipFlushMap_f_0_sm_1_t_2_cnt + IPFlushRepository::ipFlushMap_f_1_sm_1_t_2_cnt + IPFlushRepository::ipFlushMap_f_2_sm_1_t_2_cnt + IPFlushRepository::ipFlushMap_f_3_sm_1_t_2_cnt;
		t_cnt[3] = IPFlushRepository::ipFlushMap_f_0_sm_1_t_3_cnt + IPFlushRepository::ipFlushMap_f_1_sm_1_t_3_cnt + IPFlushRepository::ipFlushMap_f_2_sm_1_t_3_cnt + IPFlushRepository::ipFlushMap_f_3_sm_1_t_3_cnt;
		t_cnt[4] = IPFlushRepository::ipFlushMap_f_0_sm_1_t_4_cnt + IPFlushRepository::ipFlushMap_f_1_sm_1_t_4_cnt + IPFlushRepository::ipFlushMap_f_2_sm_1_t_4_cnt + IPFlushRepository::ipFlushMap_f_3_sm_1_t_4_cnt;
		t_cnt[5] = IPFlushRepository::ipFlushMap_f_0_sm_1_t_5_cnt + IPFlushRepository::ipFlushMap_f_1_sm_1_t_5_cnt + IPFlushRepository::ipFlushMap_f_2_sm_1_t_5_cnt + IPFlushRepository::ipFlushMap_f_3_sm_1_t_5_cnt;
		t_cnt[6] = IPFlushRepository::ipFlushMap_f_0_sm_1_t_6_cnt + IPFlushRepository::ipFlushMap_f_1_sm_1_t_6_cnt + IPFlushRepository::ipFlushMap_f_2_sm_1_t_6_cnt + IPFlushRepository::ipFlushMap_f_3_sm_1_t_6_cnt;
		t_cnt[7] = IPFlushRepository::ipFlushMap_f_0_sm_1_t_7_cnt + IPFlushRepository::ipFlushMap_f_1_sm_1_t_7_cnt + IPFlushRepository::ipFlushMap_f_2_sm_1_t_7_cnt + IPFlushRepository::ipFlushMap_f_3_sm_1_t_7_cnt;
		t_cnt[8] = IPFlushRepository::ipFlushMap_f_0_sm_1_t_8_cnt + IPFlushRepository::ipFlushMap_f_1_sm_1_t_8_cnt + IPFlushRepository::ipFlushMap_f_2_sm_1_t_8_cnt + IPFlushRepository::ipFlushMap_f_3_sm_1_t_8_cnt;
		t_cnt[9] = IPFlushRepository::ipFlushMap_f_0_sm_1_t_9_cnt + IPFlushRepository::ipFlushMap_f_1_sm_1_t_9_cnt + IPFlushRepository::ipFlushMap_f_2_sm_1_t_9_cnt + IPFlushRepository::ipFlushMap_f_3_sm_1_t_9_cnt;

		printf("   pCRRq %09lu  Res %09lu  Ac %07lu    Fl_ip_sm1 -> ",totPdpCrReq, totPdpCrRes,totPdpCrMapSize);
		for(i=0; i<10; i++){
			printf("  %07d",	t_cnt[i]);
//			totalCount[i] += t_cnt[i];
			t_cnt[i] = 0;
		}
		printf("\n");
	}
	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES > 2){
		t_cnt[0] = IPFlushRepository::ipFlushMap_f_0_sm_2_t_0_cnt + IPFlushRepository::ipFlushMap_f_1_sm_2_t_0_cnt + IPFlushRepository::ipFlushMap_f_2_sm_2_t_0_cnt + IPFlushRepository::ipFlushMap_f_3_sm_2_t_0_cnt;
		t_cnt[1] = IPFlushRepository::ipFlushMap_f_0_sm_2_t_1_cnt + IPFlushRepository::ipFlushMap_f_1_sm_2_t_1_cnt + IPFlushRepository::ipFlushMap_f_2_sm_2_t_1_cnt + IPFlushRepository::ipFlushMap_f_3_sm_2_t_1_cnt;
		t_cnt[2] = IPFlushRepository::ipFlushMap_f_0_sm_2_t_2_cnt + IPFlushRepository::ipFlushMap_f_1_sm_2_t_2_cnt + IPFlushRepository::ipFlushMap_f_2_sm_2_t_2_cnt + IPFlushRepository::ipFlushMap_f_3_sm_2_t_2_cnt;
		t_cnt[3] = IPFlushRepository::ipFlushMap_f_0_sm_2_t_3_cnt + IPFlushRepository::ipFlushMap_f_1_sm_2_t_3_cnt + IPFlushRepository::ipFlushMap_f_2_sm_2_t_3_cnt + IPFlushRepository::ipFlushMap_f_3_sm_2_t_3_cnt;
		t_cnt[4] = IPFlushRepository::ipFlushMap_f_0_sm_2_t_4_cnt + IPFlushRepository::ipFlushMap_f_1_sm_2_t_4_cnt + IPFlushRepository::ipFlushMap_f_2_sm_2_t_4_cnt + IPFlushRepository::ipFlushMap_f_3_sm_2_t_4_cnt;
		t_cnt[5] = IPFlushRepository::ipFlushMap_f_0_sm_2_t_5_cnt + IPFlushRepository::ipFlushMap_f_1_sm_2_t_5_cnt + IPFlushRepository::ipFlushMap_f_2_sm_2_t_5_cnt + IPFlushRepository::ipFlushMap_f_3_sm_2_t_5_cnt;
		t_cnt[6] = IPFlushRepository::ipFlushMap_f_0_sm_2_t_6_cnt + IPFlushRepository::ipFlushMap_f_1_sm_2_t_6_cnt + IPFlushRepository::ipFlushMap_f_2_sm_2_t_6_cnt + IPFlushRepository::ipFlushMap_f_3_sm_2_t_6_cnt;
		t_cnt[7] = IPFlushRepository::ipFlushMap_f_0_sm_2_t_7_cnt + IPFlushRepository::ipFlushMap_f_1_sm_2_t_7_cnt + IPFlushRepository::ipFlushMap_f_2_sm_2_t_7_cnt + IPFlushRepository::ipFlushMap_f_3_sm_2_t_7_cnt;
		t_cnt[8] = IPFlushRepository::ipFlushMap_f_0_sm_2_t_8_cnt + IPFlushRepository::ipFlushMap_f_1_sm_2_t_8_cnt + IPFlushRepository::ipFlushMap_f_2_sm_2_t_8_cnt + IPFlushRepository::ipFlushMap_f_3_sm_2_t_8_cnt;
		t_cnt[9] = IPFlushRepository::ipFlushMap_f_0_sm_2_t_9_cnt + IPFlushRepository::ipFlushMap_f_1_sm_2_t_9_cnt + IPFlushRepository::ipFlushMap_f_2_sm_2_t_9_cnt + IPFlushRepository::ipFlushMap_f_3_sm_2_t_9_cnt;

		printf("   pUPRq %09lu  Res %09lu  Ac %07lu    Fl_ip_sm2 -> ",totPdpUpReq, totPdpUpRes,totPdpUpMapSize);
		for(i=0; i<10; i++){
			printf("  %07d",	t_cnt[i]);
//			totalCount[i] += t_cnt[i];
			t_cnt[i] = 0;
		}
		printf("\n");
	}
	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES > 3){
		t_cnt[0] = IPFlushRepository::ipFlushMap_f_0_sm_3_t_0_cnt + IPFlushRepository::ipFlushMap_f_1_sm_3_t_0_cnt + IPFlushRepository::ipFlushMap_f_2_sm_3_t_0_cnt + IPFlushRepository::ipFlushMap_f_3_sm_3_t_0_cnt;
		t_cnt[1] = IPFlushRepository::ipFlushMap_f_0_sm_3_t_1_cnt + IPFlushRepository::ipFlushMap_f_1_sm_3_t_1_cnt + IPFlushRepository::ipFlushMap_f_2_sm_3_t_1_cnt + IPFlushRepository::ipFlushMap_f_3_sm_3_t_1_cnt;
		t_cnt[2] = IPFlushRepository::ipFlushMap_f_0_sm_3_t_2_cnt + IPFlushRepository::ipFlushMap_f_1_sm_3_t_2_cnt + IPFlushRepository::ipFlushMap_f_2_sm_3_t_2_cnt + IPFlushRepository::ipFlushMap_f_3_sm_3_t_2_cnt;
		t_cnt[3] = IPFlushRepository::ipFlushMap_f_0_sm_3_t_3_cnt + IPFlushRepository::ipFlushMap_f_1_sm_3_t_3_cnt + IPFlushRepository::ipFlushMap_f_2_sm_3_t_3_cnt + IPFlushRepository::ipFlushMap_f_3_sm_3_t_3_cnt;
		t_cnt[4] = IPFlushRepository::ipFlushMap_f_0_sm_3_t_4_cnt + IPFlushRepository::ipFlushMap_f_1_sm_3_t_4_cnt + IPFlushRepository::ipFlushMap_f_2_sm_3_t_4_cnt + IPFlushRepository::ipFlushMap_f_3_sm_3_t_4_cnt;
		t_cnt[5] = IPFlushRepository::ipFlushMap_f_0_sm_3_t_5_cnt + IPFlushRepository::ipFlushMap_f_1_sm_3_t_5_cnt + IPFlushRepository::ipFlushMap_f_2_sm_3_t_5_cnt + IPFlushRepository::ipFlushMap_f_3_sm_3_t_5_cnt;
		t_cnt[6] = IPFlushRepository::ipFlushMap_f_0_sm_3_t_6_cnt + IPFlushRepository::ipFlushMap_f_1_sm_3_t_6_cnt + IPFlushRepository::ipFlushMap_f_2_sm_3_t_6_cnt + IPFlushRepository::ipFlushMap_f_3_sm_3_t_6_cnt;
		t_cnt[7] = IPFlushRepository::ipFlushMap_f_0_sm_3_t_7_cnt + IPFlushRepository::ipFlushMap_f_1_sm_3_t_7_cnt + IPFlushRepository::ipFlushMap_f_2_sm_3_t_7_cnt + IPFlushRepository::ipFlushMap_f_3_sm_3_t_7_cnt;
		t_cnt[8] = IPFlushRepository::ipFlushMap_f_0_sm_3_t_8_cnt + IPFlushRepository::ipFlushMap_f_1_sm_3_t_8_cnt + IPFlushRepository::ipFlushMap_f_2_sm_3_t_8_cnt + IPFlushRepository::ipFlushMap_f_3_sm_3_t_8_cnt;
		t_cnt[9] = IPFlushRepository::ipFlushMap_f_0_sm_3_t_9_cnt + IPFlushRepository::ipFlushMap_f_1_sm_3_t_9_cnt + IPFlushRepository::ipFlushMap_f_2_sm_3_t_9_cnt + IPFlushRepository::ipFlushMap_f_3_sm_3_t_9_cnt;

		printf("   pDLRq %09lu  Res %09lu  Ac %07lu    Fl_ip_sm3 -> ",totPdpDlReq, totPdpDlRes,totPdpDlMapSize);
		for(i=0; i<10; i++){
			printf("  %07d",	t_cnt[i]);
//			totalCount[i] += t_cnt[i];
			t_cnt[i] = 0;
		}
		printf("\n");
	}
	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES > 4){
		t_cnt[0] = IPFlushRepository::ipFlushMap_f_0_sm_4_t_0_cnt + IPFlushRepository::ipFlushMap_f_1_sm_4_t_0_cnt + IPFlushRepository::ipFlushMap_f_2_sm_4_t_0_cnt + IPFlushRepository::ipFlushMap_f_3_sm_4_t_0_cnt;
		t_cnt[1] = IPFlushRepository::ipFlushMap_f_0_sm_4_t_1_cnt + IPFlushRepository::ipFlushMap_f_1_sm_4_t_1_cnt + IPFlushRepository::ipFlushMap_f_2_sm_4_t_1_cnt + IPFlushRepository::ipFlushMap_f_3_sm_4_t_1_cnt;
		t_cnt[2] = IPFlushRepository::ipFlushMap_f_0_sm_4_t_2_cnt + IPFlushRepository::ipFlushMap_f_1_sm_4_t_2_cnt + IPFlushRepository::ipFlushMap_f_2_sm_4_t_2_cnt + IPFlushRepository::ipFlushMap_f_3_sm_4_t_2_cnt;
		t_cnt[3] = IPFlushRepository::ipFlushMap_f_0_sm_4_t_3_cnt + IPFlushRepository::ipFlushMap_f_1_sm_4_t_3_cnt + IPFlushRepository::ipFlushMap_f_2_sm_4_t_3_cnt + IPFlushRepository::ipFlushMap_f_3_sm_4_t_3_cnt;
		t_cnt[4] = IPFlushRepository::ipFlushMap_f_0_sm_4_t_4_cnt + IPFlushRepository::ipFlushMap_f_1_sm_4_t_4_cnt + IPFlushRepository::ipFlushMap_f_2_sm_4_t_4_cnt + IPFlushRepository::ipFlushMap_f_3_sm_4_t_4_cnt;
		t_cnt[5] = IPFlushRepository::ipFlushMap_f_0_sm_4_t_5_cnt + IPFlushRepository::ipFlushMap_f_1_sm_4_t_5_cnt + IPFlushRepository::ipFlushMap_f_2_sm_4_t_5_cnt + IPFlushRepository::ipFlushMap_f_3_sm_4_t_5_cnt;
		t_cnt[6] = IPFlushRepository::ipFlushMap_f_0_sm_4_t_6_cnt + IPFlushRepository::ipFlushMap_f_1_sm_4_t_6_cnt + IPFlushRepository::ipFlushMap_f_2_sm_4_t_6_cnt + IPFlushRepository::ipFlushMap_f_3_sm_4_t_6_cnt;
		t_cnt[7] = IPFlushRepository::ipFlushMap_f_0_sm_4_t_7_cnt + IPFlushRepository::ipFlushMap_f_1_sm_4_t_7_cnt + IPFlushRepository::ipFlushMap_f_2_sm_4_t_7_cnt + IPFlushRepository::ipFlushMap_f_3_sm_4_t_7_cnt;
		t_cnt[8] = IPFlushRepository::ipFlushMap_f_0_sm_4_t_8_cnt + IPFlushRepository::ipFlushMap_f_1_sm_4_t_8_cnt + IPFlushRepository::ipFlushMap_f_2_sm_4_t_8_cnt + IPFlushRepository::ipFlushMap_f_3_sm_4_t_8_cnt;
		t_cnt[9] = IPFlushRepository::ipFlushMap_f_0_sm_4_t_9_cnt + IPFlushRepository::ipFlushMap_f_1_sm_4_t_9_cnt + IPFlushRepository::ipFlushMap_f_2_sm_4_t_9_cnt + IPFlushRepository::ipFlushMap_f_3_sm_4_t_9_cnt;

		printf("   pkGTc %09lu  GTu %015lu          Fl_ip_sm4 -> ",totGTPcPkts, totGTPuPkts);
		for(i=0; i<10; i++){
			printf("  %07d",	t_cnt[i]);
//			totalCount[i] += t_cnt[i];
			t_cnt[i] = 0;
		}
		printf("\n");
	}

	printf("\n");
}

VOID ProbeStats::printDNSSessionFlushStats()
{
	int i = 0;

	//	int totalCount[10];
	int t_cnt[10];
	for(i=0; i<10; i++)
	{
	//		totalCount[i] = 0;
		t_cnt[i] = 0;
	}


//	t_cnt[0] = IPFlushRepository::dnsFlushMap_sm_0_t_0_cnt;
//	t_cnt[1] = IPFlushRepository::dnsFlushMap_sm_0_t_1_cnt;
//	t_cnt[2] = IPFlushRepository::dnsFlushMap_sm_0_t_2_cnt;
//	t_cnt[3] = IPFlushRepository::dnsFlushMap_sm_0_t_3_cnt;
//	t_cnt[4] = IPFlushRepository::dnsFlushMap_sm_0_t_4_cnt;
//	t_cnt[5] = IPFlushRepository::dnsFlushMap_sm_0_t_5_cnt;
//	t_cnt[6] = IPFlushRepository::dnsFlushMap_sm_0_t_6_cnt;
//	t_cnt[7] = IPFlushRepository::dnsFlushMap_sm_0_t_7_cnt;
//	t_cnt[8] = IPFlushRepository::dnsFlushMap_sm_0_t_8_cnt;
//	t_cnt[9] = IPFlushRepository::dnsFlushMap_sm_0_t_9_cnt;
//	printf("                                                Fl_dns_sm0 -> ");
//	for(i=0; i<10; i++){
//		printf("  %07d",	t_cnt[i]);
////		totalCount[i] += t_cnt[i];
//		t_cnt[i] = 0;
//	}
//	printf("\n");

	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES > 1){
		t_cnt[0] = IPFlushRepository::dnsFlushMap_f_0_sm_1_t_0_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_1_t_0_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_1_t_0_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_1_t_0_cnt;
		t_cnt[1] = IPFlushRepository::dnsFlushMap_f_0_sm_1_t_1_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_1_t_1_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_1_t_1_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_1_t_1_cnt;
		t_cnt[2] = IPFlushRepository::dnsFlushMap_f_0_sm_1_t_2_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_1_t_2_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_1_t_2_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_1_t_2_cnt;
		t_cnt[3] = IPFlushRepository::dnsFlushMap_f_0_sm_1_t_3_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_1_t_3_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_1_t_3_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_1_t_3_cnt;
		t_cnt[4] = IPFlushRepository::dnsFlushMap_f_0_sm_1_t_4_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_1_t_4_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_1_t_4_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_1_t_4_cnt;
		t_cnt[5] = IPFlushRepository::dnsFlushMap_f_0_sm_1_t_5_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_1_t_5_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_1_t_5_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_1_t_5_cnt;
		t_cnt[6] = IPFlushRepository::dnsFlushMap_f_0_sm_1_t_6_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_1_t_6_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_1_t_6_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_1_t_6_cnt;
		t_cnt[7] = IPFlushRepository::dnsFlushMap_f_0_sm_1_t_7_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_1_t_7_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_1_t_7_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_1_t_7_cnt;
		t_cnt[8] = IPFlushRepository::dnsFlushMap_f_0_sm_1_t_8_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_1_t_8_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_1_t_8_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_1_t_8_cnt;
		t_cnt[9] = IPFlushRepository::dnsFlushMap_f_0_sm_1_t_9_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_1_t_9_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_1_t_9_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_1_t_9_cnt;

		printf("   Dns %06d                                   Fl_dns_sm1 -> ",IPStats::dns_session_sm_1_cnt);
		for(i=0; i<10; i++){
			printf("  %07d",	t_cnt[i]);
//			totalCount[i] += t_cnt[i];
			t_cnt[i] = 0;
		}
		printf("\n");
	}
	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES > 2){
		t_cnt[0] = IPFlushRepository::dnsFlushMap_f_0_sm_2_t_0_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_2_t_0_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_2_t_0_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_2_t_0_cnt;
		t_cnt[1] = IPFlushRepository::dnsFlushMap_f_0_sm_2_t_1_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_2_t_1_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_2_t_1_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_2_t_1_cnt;
		t_cnt[2] = IPFlushRepository::dnsFlushMap_f_0_sm_2_t_2_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_2_t_2_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_2_t_2_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_2_t_2_cnt;
		t_cnt[3] = IPFlushRepository::dnsFlushMap_f_0_sm_2_t_3_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_2_t_3_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_2_t_3_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_2_t_3_cnt;
		t_cnt[4] = IPFlushRepository::dnsFlushMap_f_0_sm_2_t_4_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_2_t_4_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_2_t_4_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_2_t_4_cnt;
		t_cnt[5] = IPFlushRepository::dnsFlushMap_f_0_sm_2_t_5_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_2_t_5_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_2_t_5_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_2_t_5_cnt;
		t_cnt[6] = IPFlushRepository::dnsFlushMap_f_0_sm_2_t_6_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_2_t_6_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_2_t_6_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_2_t_6_cnt;
		t_cnt[7] = IPFlushRepository::dnsFlushMap_f_0_sm_2_t_7_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_2_t_7_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_2_t_7_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_2_t_7_cnt;
		t_cnt[8] = IPFlushRepository::dnsFlushMap_f_0_sm_2_t_8_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_2_t_8_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_2_t_8_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_2_t_8_cnt;
		t_cnt[9] = IPFlushRepository::dnsFlushMap_f_0_sm_2_t_9_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_2_t_9_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_2_t_9_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_2_t_9_cnt;

		printf("   Dns %06d                                   Fl_dns_sm2 -> ",IPStats::dns_session_sm_2_cnt);
		for(i=0; i<10; i++){
			printf("  %07d",	t_cnt[i]);
//			totalCount[i] += t_cnt[i];
			t_cnt[i] = 0;
		}
		printf("\n");
	}
	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES > 3){
		t_cnt[0] = IPFlushRepository::dnsFlushMap_f_0_sm_3_t_0_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_3_t_0_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_3_t_0_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_3_t_0_cnt;
		t_cnt[1] = IPFlushRepository::dnsFlushMap_f_0_sm_3_t_1_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_3_t_1_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_3_t_1_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_3_t_1_cnt;
		t_cnt[2] = IPFlushRepository::dnsFlushMap_f_0_sm_3_t_2_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_3_t_2_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_3_t_2_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_3_t_2_cnt;
		t_cnt[3] = IPFlushRepository::dnsFlushMap_f_0_sm_3_t_3_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_3_t_3_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_3_t_3_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_3_t_3_cnt;
		t_cnt[4] = IPFlushRepository::dnsFlushMap_f_0_sm_3_t_4_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_3_t_4_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_3_t_4_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_3_t_4_cnt;
		t_cnt[5] = IPFlushRepository::dnsFlushMap_f_0_sm_3_t_5_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_3_t_5_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_3_t_5_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_3_t_5_cnt;
		t_cnt[6] = IPFlushRepository::dnsFlushMap_f_0_sm_3_t_6_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_3_t_6_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_3_t_6_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_3_t_6_cnt;
		t_cnt[7] = IPFlushRepository::dnsFlushMap_f_0_sm_3_t_7_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_3_t_7_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_3_t_7_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_3_t_7_cnt;
		t_cnt[8] = IPFlushRepository::dnsFlushMap_f_0_sm_3_t_8_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_3_t_8_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_3_t_8_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_3_t_8_cnt;
		t_cnt[9] = IPFlushRepository::dnsFlushMap_f_0_sm_3_t_9_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_3_t_9_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_3_t_9_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_3_t_9_cnt;

		printf("   Dns %06d                                   Fl_dns_sm3 -> ",IPStats::dns_session_sm_3_cnt);
		for(i=0; i<10; i++){
			printf("  %07d",	t_cnt[i]);
//			totalCount[i] += t_cnt[i];
			t_cnt[i] = 0;
		}
		printf("\n");
	}

	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES > 4){
		t_cnt[0] = IPFlushRepository::dnsFlushMap_f_0_sm_4_t_0_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_4_t_0_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_4_t_0_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_4_t_0_cnt;
		t_cnt[1] = IPFlushRepository::dnsFlushMap_f_0_sm_4_t_1_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_4_t_1_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_4_t_1_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_4_t_1_cnt;
		t_cnt[2] = IPFlushRepository::dnsFlushMap_f_0_sm_4_t_2_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_4_t_2_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_4_t_2_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_4_t_2_cnt;
		t_cnt[3] = IPFlushRepository::dnsFlushMap_f_0_sm_4_t_3_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_4_t_3_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_4_t_3_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_4_t_3_cnt;
		t_cnt[4] = IPFlushRepository::dnsFlushMap_f_0_sm_4_t_4_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_4_t_4_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_4_t_4_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_4_t_4_cnt;
		t_cnt[5] = IPFlushRepository::dnsFlushMap_f_0_sm_4_t_5_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_4_t_5_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_4_t_5_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_4_t_5_cnt;
		t_cnt[6] = IPFlushRepository::dnsFlushMap_f_0_sm_4_t_6_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_4_t_6_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_4_t_6_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_4_t_6_cnt;
		t_cnt[7] = IPFlushRepository::dnsFlushMap_f_0_sm_4_t_7_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_4_t_7_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_4_t_7_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_4_t_7_cnt;
		t_cnt[8] = IPFlushRepository::dnsFlushMap_f_0_sm_4_t_8_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_4_t_8_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_4_t_8_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_4_t_8_cnt;
		t_cnt[9] = IPFlushRepository::dnsFlushMap_f_0_sm_4_t_9_cnt + IPFlushRepository::dnsFlushMap_f_1_sm_4_t_9_cnt + IPFlushRepository::dnsFlushMap_f_2_sm_4_t_9_cnt + IPFlushRepository::dnsFlushMap_f_3_sm_4_t_9_cnt;

		printf("   Dns %06d                                   Fl_dns_sm4 -> ",IPStats::dns_session_sm_4_cnt);
		for(i=0; i<10; i++){
			printf("  %07d",	t_cnt[i]);
//			totalCount[i] += t_cnt[i];
			t_cnt[i] = 0;
		}
		printf("\n");
	}

//	printf("                                           ------------------------------------------------------------------------------------------\n                                         ");
//	for( i = 0; i < 10; i++ ) {
//		printf("  %07d", totalCount[i]);
//		totalCount[i] = 0;
//	}
	printf("\n");
}

VOID ProbeStats::printZmqFlushStats()
{

//	printf("\n                                                  Zmq_GTPc -> ");
	printf("\n   glbLkuUP %08lu (%08lu)   cln %08lu    Zmq_GTPc -> ",GTPStats::gtp_glb_lku_up_active_sessions_cnt, GTPStats::gtp_glb_lku_up_sessions_cnt, GTPStats::gtp_glb_lku_up_sessions_cln_cnt);

	printf("  %07d  %07d  %07d  %07d  %07d  %07d  %07d  %07d  %07d  %07d",
								GTPZmqFlushStore::zmq_flush_map_gtpc_t_0_cnt,
								GTPZmqFlushStore::zmq_flush_map_gtpc_t_1_cnt,
								GTPZmqFlushStore::zmq_flush_map_gtpc_t_2_cnt,
								GTPZmqFlushStore::zmq_flush_map_gtpc_t_3_cnt,
								GTPZmqFlushStore::zmq_flush_map_gtpc_t_4_cnt,
								GTPZmqFlushStore::zmq_flush_map_gtpc_t_5_cnt,
								GTPZmqFlushStore::zmq_flush_map_gtpc_t_6_cnt,
								GTPZmqFlushStore::zmq_flush_map_gtpc_t_7_cnt,
								GTPZmqFlushStore::zmq_flush_map_gtpc_t_8_cnt,
								GTPZmqFlushStore::zmq_flush_map_gtpc_t_9_cnt);

//	printf("\n                                                  Zmq_GTPu -> ");
	printf("\n   glbLkuDN %08lu (%08lu)   cln %08lu    Zmq_GTPu -> ",GTPStats::gtp_glb_lku_dn_active_sessions_cnt, GTPStats::gtp_glb_lku_dn_sessions_cnt, GTPStats::gtp_glb_lku_dn_sessions_cln_cnt);
	printf("  %07d  %07d  %07d  %07d  %07d  %07d  %07d  %07d  %07d  %07d",
								IPFlushRepository::ip_zmq_flush_f_0_t_0_cnt + IPFlushRepository::ip_zmq_flush_f_1_t_0_cnt,
								IPFlushRepository::ip_zmq_flush_f_0_t_1_cnt + IPFlushRepository::ip_zmq_flush_f_1_t_1_cnt,
								IPFlushRepository::ip_zmq_flush_f_0_t_2_cnt + IPFlushRepository::ip_zmq_flush_f_1_t_2_cnt,
								IPFlushRepository::ip_zmq_flush_f_0_t_3_cnt + IPFlushRepository::ip_zmq_flush_f_1_t_3_cnt,
								IPFlushRepository::ip_zmq_flush_f_0_t_4_cnt + IPFlushRepository::ip_zmq_flush_f_1_t_4_cnt,
								IPFlushRepository::ip_zmq_flush_f_0_t_5_cnt + IPFlushRepository::ip_zmq_flush_f_1_t_5_cnt,
								IPFlushRepository::ip_zmq_flush_f_0_t_6_cnt + IPFlushRepository::ip_zmq_flush_f_1_t_6_cnt,
								IPFlushRepository::ip_zmq_flush_f_0_t_7_cnt + IPFlushRepository::ip_zmq_flush_f_1_t_7_cnt,
								IPFlushRepository::ip_zmq_flush_f_0_t_8_cnt + IPFlushRepository::ip_zmq_flush_f_1_t_8_cnt,
								IPFlushRepository::ip_zmq_flush_f_0_t_9_cnt + IPFlushRepository::ip_zmq_flush_f_1_t_9_cnt);
	printf("\n   glbSessN %08d  U %07d   G %07d        Zmq_DNS -> ",GTPStats::gtp_glb_sessions_total_cnt,GTPStats::gtp_glb_sessions_utran_cnt,GTPStats::gtp_glb_sessions_geran_cnt);
	printf("  %07d  %07d  %07d  %07d  %07d  %07d  %07d  %07d  %07d  %07d",
								IPFlushRepository::dns_zmq_flush_f_0_t_0_cnt + IPFlushRepository::dns_zmq_flush_f_1_t_0_cnt,
								IPFlushRepository::dns_zmq_flush_f_0_t_1_cnt + IPFlushRepository::dns_zmq_flush_f_1_t_1_cnt,
								IPFlushRepository::dns_zmq_flush_f_0_t_2_cnt + IPFlushRepository::dns_zmq_flush_f_1_t_2_cnt,
								IPFlushRepository::dns_zmq_flush_f_0_t_3_cnt + IPFlushRepository::dns_zmq_flush_f_1_t_3_cnt,
								IPFlushRepository::dns_zmq_flush_f_0_t_4_cnt + IPFlushRepository::dns_zmq_flush_f_1_t_4_cnt,
								IPFlushRepository::dns_zmq_flush_f_0_t_5_cnt + IPFlushRepository::dns_zmq_flush_f_1_t_5_cnt,
								IPFlushRepository::dns_zmq_flush_f_0_t_6_cnt + IPFlushRepository::dns_zmq_flush_f_1_t_6_cnt,
								IPFlushRepository::dns_zmq_flush_f_0_t_7_cnt + IPFlushRepository::dns_zmq_flush_f_1_t_7_cnt,
								IPFlushRepository::dns_zmq_flush_f_0_t_8_cnt + IPFlushRepository::dns_zmq_flush_f_1_t_8_cnt,
								IPFlushRepository::dns_zmq_flush_f_0_t_9_cnt + IPFlushRepository::dns_zmq_flush_f_1_t_9_cnt);
	printf("\n");

}

VOID ProbeStats::printIUPSSessionFlushStats()
{
        int i = 0;

        int t_cnt[10];
        for(i=0; i<10; i++)
                t_cnt[i] = 0;

        t_cnt[0] = IUPSFlushRepository::iupsFlushMap_sm_0_t_0_cnt;
        t_cnt[1] = IUPSFlushRepository::iupsFlushMap_sm_0_t_1_cnt;
        t_cnt[2] = IUPSFlushRepository::iupsFlushMap_sm_0_t_2_cnt;
        t_cnt[3] = IUPSFlushRepository::iupsFlushMap_sm_0_t_3_cnt;
        t_cnt[4] = IUPSFlushRepository::iupsFlushMap_sm_0_t_4_cnt;
        t_cnt[5] = IUPSFlushRepository::iupsFlushMap_sm_0_t_5_cnt;
        t_cnt[6] = IUPSFlushRepository::iupsFlushMap_sm_0_t_6_cnt;
        t_cnt[7] = IUPSFlushRepository::iupsFlushMap_sm_0_t_7_cnt;
        t_cnt[8] = IUPSFlushRepository::iupsFlushMap_sm_0_t_8_cnt;
        t_cnt[9] = IUPSFlushRepository::iupsFlushMap_sm_0_t_9_cnt;
        printf("    S %06d K1 %06d K2 %06d Im %05d      Fl_Iups_sm0 -> ", SCCPGlobal::SCCPSessionCnt, SCCPGlobal::SCCPKeyMap1Cnt, SCCPGlobal::SCCPKeyMap2Cnt, SCCPGlobal::SCCPImsiTmsiMaoCnt);
        for(i=0; i<10; i++){
                printf("  %07d",        t_cnt[i]);
                t_cnt[i] = 0;
        }
        printf("\n");
        printf("\n");

}

VOID ProbeStats::printIUPSZmqFlushStats()
{
	printf("\n                                                  Zmq_Iups -> ");
	printf("  %07d  %07d  %07d  %07d  %07d  %07d  %07d  %07d  %07d  %07d",
								IUPSZmqFlushStore::zmq_flush_map_iups_t_0_cnt,
								IUPSZmqFlushStore::zmq_flush_map_iups_t_1_cnt,
								IUPSZmqFlushStore::zmq_flush_map_iups_t_2_cnt,
								IUPSZmqFlushStore::zmq_flush_map_iups_t_3_cnt,
								IUPSZmqFlushStore::zmq_flush_map_iups_t_4_cnt,
								IUPSZmqFlushStore::zmq_flush_map_iups_t_5_cnt,
								IUPSZmqFlushStore::zmq_flush_map_iups_t_6_cnt,
								IUPSZmqFlushStore::zmq_flush_map_iups_t_7_cnt,
								IUPSZmqFlushStore::zmq_flush_map_iups_t_8_cnt,
								IUPSZmqFlushStore::zmq_flush_map_iups_t_9_cnt);

	printf("\n");
}
