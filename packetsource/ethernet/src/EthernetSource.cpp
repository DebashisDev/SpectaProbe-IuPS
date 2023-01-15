/*
 * Ethernet.cpp
 *
 *  Created on: 04-Jul-2016
 *      Author: debashis
 */

#include "EthernetSource.h"

uint32_t pkt_cnt = 0;

uint64_t  	n_rx_pkts;
uint128_t  	n_rx_bytes;

EthernetSource::EthernetSource(int perListenerRouters, int intfId) {

	//_thisLogLevel = 0;
	this->_name = "EthernetSource";
	this->setLogLevel(Log::theLog().level());

	t_index = 0;
	pcapHandle = NULL;
	InterfaceName = IPGlobal::ETHERNET_INTERFACES[intfId];
	InterfaceId = intfId;
	END_ROUTER_ID = perListenerRouters;
}

EthernetSource::~EthernetSource() {
}

void EthernetSource::packetReaderCallback(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
	//Date change check to reset the counter
	if(IPGlobal::PKT_LISTENER_DAYCHANGE_INDICATION[InterfaceId])
	{
		TheLog_nc_v1(Log::Info, name()," [%d] Day Change Indication received. Pkts read yesterday [%lu]. Reseting counter.", n_rx_pkts);
		n_rx_bytes = 0;
		n_rx_pkts = 0;
		IPGlobal::PKT_LISTENER_DAYCHANGE_INDICATION[InterfaceId] = false;
	}

	n_rx_bytes += header->len;
	n_rx_pkts++;

	if(header->len > 2048){
		countDiscardedPkt();
		return;
	}

    timeval curTime;
    gettimeofday(&curTime, NULL);

	t_index = PKT_WRITE_TIME_INDEX(curTime.tv_sec);

	setPktCounter();

	switch(InterfaceId)
	{
		case 0:
			storepkt_i_0((BYTE)packet, header->len, curTime.tv_sec, curTime.tv_usec*1000);
			break;

		case 1:
			storepkt_i_1((BYTE)packet, header->len, curTime.tv_sec, curTime.tv_usec*1000);
			break;

		case 2:
			storepkt_i_2((BYTE)packet, header->len, curTime.tv_sec, curTime.tv_usec*1000);
			break;

		case 3:
			storepkt_i_3((BYTE)packet, header->len, curTime.tv_sec, curTime.tv_usec*1000);
			break;
	}

	ROUTER_TO_PROCESS++;
	if(ROUTER_TO_PROCESS >= END_ROUTER_ID)
		ROUTER_TO_PROCESS = 0;

}

VOID EthernetSource::countDiscardedPkt(){

	switch(InterfaceId)
	{
		case 0:
			IPGlobal::ip_discarded_large_packets_i_0++;
			break;
		case 1:
			IPGlobal::ip_discarded_large_packets_i_1++;
			break;
		case 2:
			IPGlobal::ip_discarded_large_packets_i_2++;
			break;
		case 3:
			IPGlobal::ip_discarded_large_packets_i_3++;
			break;
	}
}

VOID monitor(int ethInterfaceId);

void* monitor_fn(void* arg)
{
  int id = *(int *)arg;
  monitor(id);
  return NULL;
}

VOID EthernetSource::start()
{
	pthread_t thread_id;

	MAX_PKT_ALLOWED_PER_TIME_INDEX = (int)(((IPGlobal::PPS_PER_INTERFACE[InterfaceId] / IPGlobal::ROUTER_PER_INTERFACE[InterfaceId]) /100 ) * IPGlobal::PPS_CAP_PERCENTAGE[InterfaceId]);

	printf("EthernetSource started with [%d] Routers for Interface [%d]->[%s] with %d% [%d] pps cap\n", END_ROUTER_ID, InterfaceId, InterfaceName.c_str(), IPGlobal::PPS_CAP_PERCENTAGE[InterfaceId], MAX_PKT_ALLOWED_PER_TIME_INDEX);
	TheLog_nc_v5(Log::Info, name(),"  EthernetSource started with [%d] Routers for Interface [%d]->[%s] with %d% [%d] pps cap\n", END_ROUTER_ID, InterfaceId, InterfaceName.c_str(), IPGlobal::PPS_CAP_PERCENTAGE[InterfaceId], MAX_PKT_ALLOWED_PER_TIME_INDEX);

	resetPktCounter();

	pthread_create(&thread_id, NULL, monitor_fn, (void *)&InterfaceId);

	pcapHandle = pcap_open_live(this->InterfaceName.c_str(), BUFSIZ, 1, -1, errbuf);

	if(pcapHandle == NULL)
	{
		cout << "ERROR !!! In reading Ethernet " << this->InterfaceName.c_str() << endl;
		exit(1);
	}

//	if (signal(SIGTERM, eth_sig_handler) == SIG_ERR)
//		printf("SpectaProbe Ethernet Source Can't Received Signal...\n");

	if(pcapHandle != NULL) {
		int ret = this->pcapCaptureLoop();

		if (ret == -2)
			printf("pcap_loop terminated by user...\n");
		else if (ret == 0)
			printf("pcap_loop no more packets to read ...\n");
	}

	if(pcapHandle != NULL)
		pcap_close(pcapHandle);
}

VOID EthernetSource::setPktCounter()
{
	PKT_COUNTER++;

	switch(InterfaceId)
	{
		case 0:
			if(PKT_COUNTER >= 199999999) PKT_COUNTER = 100000001;
			break;
		case 1:
			if(PKT_COUNTER >= 299999999) PKT_COUNTER = 200000001;
			break;
	}
}

VOID EthernetSource::resetPktCounter()
{
	switch(InterfaceId)
	{
		case 0:
			PKT_COUNTER = 100000000;
			break;
		case 1:
			PKT_COUNTER = 200000000;
			break;
	}
}

void EthernetSource::pcapCallBackFunction(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
			EthernetSource *sniffer=reinterpret_cast<EthernetSource *>(args);
			sniffer->packetReaderCallback(args,header,packet);
}

VOID monitor(int ethInterfaceId)
{
	/* Print approx packet rate and bandwidth every second. */
	uint64_t now_bytes, prev_bytes;
	struct timeval start, end;
	struct tm *now_tm;
	int prev_pkts, now_pkts;
	int ms, pkt_rate, mbps;

	prev_pkts = n_rx_pkts;
	prev_bytes = n_rx_bytes;
	gettimeofday(&start, NULL);

	now_tm = localtime(&start.tv_sec);
	int today = 0, lastday = 0;
	today = lastday = now_tm->tm_mday;

	while(IPGlobal::PKT_LISTENER_RUNNING_STATUS[ethInterfaceId])
	{
		sleep(1);
		gettimeofday(&end, NULL);

		now_tm = localtime(&end.tv_sec);
		today = now_tm->tm_mday;


		now_pkts = n_rx_pkts;
		now_bytes = n_rx_bytes;

		if(now_pkts < prev_pkts)
			now_pkts = prev_pkts;
		if(now_bytes < prev_bytes)
			now_bytes = prev_bytes;

		ms = (end.tv_sec - start.tv_sec) * 1000;
		ms += (end.tv_usec - start.tv_usec) / 1000;
		pkt_rate = (int) ((int64_t) (now_pkts - prev_pkts) * 1000 / ms);
		mbps = (int) ((now_bytes - prev_bytes) * 8 / 1000 / ms);

		switch(ethInterfaceId)
		{
			case 0:
				if(lastday != today){
					IPGlobal::PKTS_TOTAL_INTF_0 = 0;
					lastday = today;
				}
				IPGlobal::PKTS_TOTAL_INTF_0 = now_pkts;
				IPGlobal::PKT_RATE_INTF_0 = pkt_rate;
				IPGlobal::BW_MBPS_INTF_0 = mbps;
				break;
			case 1:
				if(lastday != today){
					IPGlobal::PKTS_TOTAL_INTF_1 = 0;
					lastday = today;
				}
				IPGlobal::PKTS_TOTAL_INTF_1 = now_pkts;
				IPGlobal::PKT_RATE_INTF_1 = pkt_rate;
				IPGlobal::BW_MBPS_INTF_1 = mbps;
				break;
			case 2:
				if(lastday != today){
					IPGlobal::PKTS_TOTAL_INTF_2 = 0;
					lastday = today;
				}
				IPGlobal::PKTS_TOTAL_INTF_2 = now_pkts;
				IPGlobal::PKT_RATE_INTF_2 = pkt_rate;
				IPGlobal::BW_MBPS_INTF_2 = mbps;
				break;
			case 3:
				if(lastday != today){
					IPGlobal::PKTS_TOTAL_INTF_3 = 0;
					lastday = today;
				}
				IPGlobal::PKTS_TOTAL_INTF_3 = now_pkts;
				IPGlobal::PKT_RATE_INTF_3 = pkt_rate;
				IPGlobal::BW_MBPS_INTF_3 = mbps;
				break;
		}

		prev_pkts = now_pkts;
		prev_bytes = now_bytes;
		start = end;
	}
}

VOID EthernetSource::storepkt_i_0(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec)
{
	switch(ROUTER_TO_PROCESS)
	{
		case 0:
			storepkt_i_0_r_0(pkt, len, tv_sec, tv_nsec);
			break;

		case 1:
			storepkt_i_0_r_1(pkt, len, tv_sec, tv_nsec);
			break;

//		case 2:
//			storepkt_i_0_r_2(pktno, pkt, len, tv_sec, tv_nsec);
//			break;
//
//		case 3:
//			storepkt_i_0_r_3(pktno, pkt, len, tv_sec, tv_nsec);
//			break;
	}
}

VOID EthernetSource::storepkt_i_1(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec)
{
	switch(ROUTER_TO_PROCESS)
	{
		case 0:
			storepkt_i_1_r_0(pkt, len, tv_sec, tv_nsec);
			break;

		case 1:
			storepkt_i_1_r_1(pkt, len, tv_sec, tv_nsec);
			break;

//		case 2:
//			storepkt_i_1_r_2(pktno, pkt, len, tv_sec, tv_nsec);
//			break;
//
//		case 3:
//			storepkt_i_1_r_3(pktno, pkt, len, tv_sec, tv_nsec);
//			break;
	}
}

VOID EthernetSource::storepkt_i_2(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec)
{
	switch(ROUTER_TO_PROCESS)
	{
		case 0:
			storepkt_i_2_r_0(pkt, len, tv_sec, tv_nsec);
			break;

		case 1:
			storepkt_i_2_r_1(pkt, len, tv_sec, tv_nsec);
			break;

//		case 2:
//			storepkt_i_2_r_2(pktno, pkt, len, tv_sec, tv_nsec);
//			break;
//
//		case 3:
//			storepkt_i_2_r_3(pktno, pkt, len, tv_sec, tv_nsec);
//			break;
	}
}

VOID EthernetSource::storepkt_i_3(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec)
{
	switch(ROUTER_TO_PROCESS)
	{
		case 0:
			storepkt_i_3_r_0(pkt, len, tv_sec, tv_nsec);
			break;

		case 1:
			storepkt_i_3_r_1(pkt, len, tv_sec, tv_nsec);
			break;

//		case 2:
//			storepkt_i_3_r_2(pkt, len, tv_sec, tv_nsec);
//			break;
//
//		case 3:
//			storepkt_i_3_r_3(pkt, len, tv_sec, tv_nsec);
//			break;
	}
}


VOID EthernetSource::storepkt_i_0_r_0(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec)
{
	switch(t_index)
	{
		case 0:
			{
				if(PKTStore::pktRepository_i_0_r_0_t_0_busy || PKTStore::pktRepository_i_0_r_0_t_0_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_0_r_0_t_0[PKTStore::pktRepository_i_0_r_0_t_0_cnt]->len = len;
				PKTStore::pktRepository_i_0_r_0_t_0[PKTStore::pktRepository_i_0_r_0_t_0_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_0_r_0_t_0[PKTStore::pktRepository_i_0_r_0_t_0_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_0_r_0_t_0[PKTStore::pktRepository_i_0_r_0_t_0_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_0_r_0_t_0[PKTStore::pktRepository_i_0_r_0_t_0_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_0_r_0_t_0_cnt++;
			}
			break;
		case 1:
			{
				if(PKTStore::pktRepository_i_0_r_0_t_1_busy || PKTStore::pktRepository_i_0_r_0_t_1_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_0_r_0_t_1[PKTStore::pktRepository_i_0_r_0_t_1_cnt]->len = len;
				PKTStore::pktRepository_i_0_r_0_t_1[PKTStore::pktRepository_i_0_r_0_t_1_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_0_r_0_t_1[PKTStore::pktRepository_i_0_r_0_t_1_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_0_r_0_t_1[PKTStore::pktRepository_i_0_r_0_t_1_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_0_r_0_t_1[PKTStore::pktRepository_i_0_r_0_t_1_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_0_r_0_t_1_cnt++;
			}
			break;
		case 2:
			{
				if(PKTStore::pktRepository_i_0_r_0_t_2_busy || PKTStore::pktRepository_i_0_r_0_t_2_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_0_r_0_t_2[PKTStore::pktRepository_i_0_r_0_t_2_cnt]->len = len;
				PKTStore::pktRepository_i_0_r_0_t_2[PKTStore::pktRepository_i_0_r_0_t_2_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_0_r_0_t_2[PKTStore::pktRepository_i_0_r_0_t_2_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_0_r_0_t_2[PKTStore::pktRepository_i_0_r_0_t_2_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_0_r_0_t_2[PKTStore::pktRepository_i_0_r_0_t_2_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_0_r_0_t_2_cnt++;
			}
			break;
		case 3:
			{
				if(PKTStore::pktRepository_i_0_r_0_t_3_busy || PKTStore::pktRepository_i_0_r_0_t_3_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_0_r_0_t_3[PKTStore::pktRepository_i_0_r_0_t_3_cnt]->len = len;
				PKTStore::pktRepository_i_0_r_0_t_3[PKTStore::pktRepository_i_0_r_0_t_3_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_0_r_0_t_3[PKTStore::pktRepository_i_0_r_0_t_3_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_0_r_0_t_3[PKTStore::pktRepository_i_0_r_0_t_3_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_0_r_0_t_3[PKTStore::pktRepository_i_0_r_0_t_3_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_0_r_0_t_3_cnt++;
			}
			break;
		case 4:
			{
				if(PKTStore::pktRepository_i_0_r_0_t_4_busy || PKTStore::pktRepository_i_0_r_0_t_4_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_0_r_0_t_4[PKTStore::pktRepository_i_0_r_0_t_4_cnt]->len = len;
				PKTStore::pktRepository_i_0_r_0_t_4[PKTStore::pktRepository_i_0_r_0_t_4_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_0_r_0_t_4[PKTStore::pktRepository_i_0_r_0_t_4_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_0_r_0_t_4[PKTStore::pktRepository_i_0_r_0_t_4_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_0_r_0_t_4[PKTStore::pktRepository_i_0_r_0_t_4_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_0_r_0_t_4_cnt++;
			}
			break;
		case 5:
			{
				if(PKTStore::pktRepository_i_0_r_0_t_5_busy || PKTStore::pktRepository_i_0_r_0_t_5_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_0_r_0_t_5[PKTStore::pktRepository_i_0_r_0_t_5_cnt]->len = len;
				PKTStore::pktRepository_i_0_r_0_t_5[PKTStore::pktRepository_i_0_r_0_t_5_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_0_r_0_t_5[PKTStore::pktRepository_i_0_r_0_t_5_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_0_r_0_t_5[PKTStore::pktRepository_i_0_r_0_t_5_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_0_r_0_t_5[PKTStore::pktRepository_i_0_r_0_t_5_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_0_r_0_t_5_cnt++;
			}
			break;
		case 6:
			{
				if(PKTStore::pktRepository_i_0_r_0_t_6_busy || PKTStore::pktRepository_i_0_r_0_t_6_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_0_r_0_t_6[PKTStore::pktRepository_i_0_r_0_t_6_cnt]->len = len;
				PKTStore::pktRepository_i_0_r_0_t_6[PKTStore::pktRepository_i_0_r_0_t_6_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_0_r_0_t_6[PKTStore::pktRepository_i_0_r_0_t_6_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_0_r_0_t_6[PKTStore::pktRepository_i_0_r_0_t_6_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_0_r_0_t_6[PKTStore::pktRepository_i_0_r_0_t_6_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_0_r_0_t_6_cnt++;
			}
			break;
		case 7:
			{
				if(PKTStore::pktRepository_i_0_r_0_t_7_busy || PKTStore::pktRepository_i_0_r_0_t_7_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_0_r_0_t_7[PKTStore::pktRepository_i_0_r_0_t_7_cnt]->len = len;
				PKTStore::pktRepository_i_0_r_0_t_7[PKTStore::pktRepository_i_0_r_0_t_7_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_0_r_0_t_7[PKTStore::pktRepository_i_0_r_0_t_7_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_0_r_0_t_7[PKTStore::pktRepository_i_0_r_0_t_7_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_0_r_0_t_7[PKTStore::pktRepository_i_0_r_0_t_7_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_0_r_0_t_7_cnt++;
			}
			break;
		case 8:
			{
				if(PKTStore::pktRepository_i_0_r_0_t_8_busy || PKTStore::pktRepository_i_0_r_0_t_8_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_0_r_0_t_8[PKTStore::pktRepository_i_0_r_0_t_8_cnt]->len = len;
				PKTStore::pktRepository_i_0_r_0_t_8[PKTStore::pktRepository_i_0_r_0_t_8_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_0_r_0_t_8[PKTStore::pktRepository_i_0_r_0_t_8_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_0_r_0_t_8[PKTStore::pktRepository_i_0_r_0_t_8_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_0_r_0_t_8[PKTStore::pktRepository_i_0_r_0_t_8_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_0_r_0_t_8_cnt++;
			}
			break;
		case 9:
			{
				if(PKTStore::pktRepository_i_0_r_0_t_9_busy || PKTStore::pktRepository_i_0_r_0_t_9_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_0_r_0_t_9[PKTStore::pktRepository_i_0_r_0_t_9_cnt]->len = len;
				PKTStore::pktRepository_i_0_r_0_t_9[PKTStore::pktRepository_i_0_r_0_t_9_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_0_r_0_t_9[PKTStore::pktRepository_i_0_r_0_t_9_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_0_r_0_t_9[PKTStore::pktRepository_i_0_r_0_t_9_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_0_r_0_t_9[PKTStore::pktRepository_i_0_r_0_t_9_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_0_r_0_t_9_cnt++;
			}
			break;
	}
}

VOID EthernetSource::storepkt_i_0_r_1(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec)
{
	switch(t_index)
	{
		case 0:
			{
				if(PKTStore::pktRepository_i_0_r_1_t_0_busy || PKTStore::pktRepository_i_0_r_1_t_0_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_0_r_1_t_0[PKTStore::pktRepository_i_0_r_1_t_0_cnt]->len = len;
				PKTStore::pktRepository_i_0_r_1_t_0[PKTStore::pktRepository_i_0_r_1_t_0_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_0_r_1_t_0[PKTStore::pktRepository_i_0_r_1_t_0_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_0_r_1_t_0[PKTStore::pktRepository_i_0_r_1_t_0_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_0_r_1_t_0[PKTStore::pktRepository_i_0_r_1_t_0_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_0_r_1_t_0_cnt++;
			}
			break;
		case 1:
			{
				if(PKTStore::pktRepository_i_0_r_1_t_1_busy || PKTStore::pktRepository_i_0_r_1_t_1_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_0_r_1_t_1[PKTStore::pktRepository_i_0_r_1_t_1_cnt]->len = len;
				PKTStore::pktRepository_i_0_r_1_t_1[PKTStore::pktRepository_i_0_r_1_t_1_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_0_r_1_t_1[PKTStore::pktRepository_i_0_r_1_t_1_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_0_r_1_t_1[PKTStore::pktRepository_i_0_r_1_t_1_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_0_r_1_t_1[PKTStore::pktRepository_i_0_r_1_t_1_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_0_r_1_t_1_cnt++;
			}
			break;
		case 2:
			{
				if(PKTStore::pktRepository_i_0_r_1_t_2_busy || PKTStore::pktRepository_i_0_r_1_t_2_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_0_r_1_t_2[PKTStore::pktRepository_i_0_r_1_t_2_cnt]->len = len;
				PKTStore::pktRepository_i_0_r_1_t_2[PKTStore::pktRepository_i_0_r_1_t_2_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_0_r_1_t_2[PKTStore::pktRepository_i_0_r_1_t_2_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_0_r_1_t_2[PKTStore::pktRepository_i_0_r_1_t_2_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_0_r_1_t_2[PKTStore::pktRepository_i_0_r_1_t_2_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_0_r_1_t_2_cnt++;
			}
			break;
		case 3:
			{
				if(PKTStore::pktRepository_i_0_r_1_t_3_busy || PKTStore::pktRepository_i_0_r_1_t_3_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_0_r_1_t_3[PKTStore::pktRepository_i_0_r_1_t_3_cnt]->len = len;
				PKTStore::pktRepository_i_0_r_1_t_3[PKTStore::pktRepository_i_0_r_1_t_3_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_0_r_1_t_3[PKTStore::pktRepository_i_0_r_1_t_3_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_0_r_1_t_3[PKTStore::pktRepository_i_0_r_1_t_3_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_0_r_1_t_3[PKTStore::pktRepository_i_0_r_1_t_3_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_0_r_1_t_3_cnt++;
			}
			break;
		case 4:
			{
				if(PKTStore::pktRepository_i_0_r_1_t_4_busy || PKTStore::pktRepository_i_0_r_1_t_4_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_0_r_1_t_4[PKTStore::pktRepository_i_0_r_1_t_4_cnt]->len = len;
				PKTStore::pktRepository_i_0_r_1_t_4[PKTStore::pktRepository_i_0_r_1_t_4_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_0_r_1_t_4[PKTStore::pktRepository_i_0_r_1_t_4_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_0_r_1_t_4[PKTStore::pktRepository_i_0_r_1_t_4_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_0_r_1_t_4[PKTStore::pktRepository_i_0_r_1_t_4_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_0_r_1_t_4_cnt++;
			}
			break;
		case 5:
			{
				if(PKTStore::pktRepository_i_0_r_1_t_5_busy || PKTStore::pktRepository_i_0_r_1_t_5_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_0_r_1_t_5[PKTStore::pktRepository_i_0_r_1_t_5_cnt]->len = len;
				PKTStore::pktRepository_i_0_r_1_t_5[PKTStore::pktRepository_i_0_r_1_t_5_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_0_r_1_t_5[PKTStore::pktRepository_i_0_r_1_t_5_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_0_r_1_t_5[PKTStore::pktRepository_i_0_r_1_t_5_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_0_r_1_t_5[PKTStore::pktRepository_i_0_r_1_t_5_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_0_r_1_t_5_cnt++;
			}
			break;
		case 6:
			{
				if(PKTStore::pktRepository_i_0_r_1_t_6_busy || PKTStore::pktRepository_i_0_r_1_t_6_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_0_r_1_t_6[PKTStore::pktRepository_i_0_r_1_t_6_cnt]->len = len;
				PKTStore::pktRepository_i_0_r_1_t_6[PKTStore::pktRepository_i_0_r_1_t_6_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_0_r_1_t_6[PKTStore::pktRepository_i_0_r_1_t_6_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_0_r_1_t_6[PKTStore::pktRepository_i_0_r_1_t_6_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_0_r_1_t_6[PKTStore::pktRepository_i_0_r_1_t_6_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_0_r_1_t_6_cnt++;
			}
			break;
		case 7:
			{
				if(PKTStore::pktRepository_i_0_r_1_t_7_busy || PKTStore::pktRepository_i_0_r_1_t_7_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_0_r_1_t_7[PKTStore::pktRepository_i_0_r_1_t_7_cnt]->len = len;
				PKTStore::pktRepository_i_0_r_1_t_7[PKTStore::pktRepository_i_0_r_1_t_7_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_0_r_1_t_7[PKTStore::pktRepository_i_0_r_1_t_7_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_0_r_1_t_7[PKTStore::pktRepository_i_0_r_1_t_7_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_0_r_1_t_7[PKTStore::pktRepository_i_0_r_1_t_7_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_0_r_1_t_7_cnt++;
			}
			break;
		case 8:
			{
				if(PKTStore::pktRepository_i_0_r_1_t_8_busy || PKTStore::pktRepository_i_0_r_1_t_8_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_0_r_1_t_8[PKTStore::pktRepository_i_0_r_1_t_8_cnt]->len = len;
				PKTStore::pktRepository_i_0_r_1_t_8[PKTStore::pktRepository_i_0_r_1_t_8_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_0_r_1_t_8[PKTStore::pktRepository_i_0_r_1_t_8_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_0_r_1_t_8[PKTStore::pktRepository_i_0_r_1_t_8_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_0_r_1_t_8[PKTStore::pktRepository_i_0_r_1_t_8_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_0_r_1_t_8_cnt++;
			}
			break;
		case 9:
			{
				if(PKTStore::pktRepository_i_0_r_1_t_9_busy || PKTStore::pktRepository_i_0_r_1_t_9_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_0_r_1_t_9[PKTStore::pktRepository_i_0_r_1_t_9_cnt]->len = len;
				PKTStore::pktRepository_i_0_r_1_t_9[PKTStore::pktRepository_i_0_r_1_t_9_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_0_r_1_t_9[PKTStore::pktRepository_i_0_r_1_t_9_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_0_r_1_t_9[PKTStore::pktRepository_i_0_r_1_t_9_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_0_r_1_t_9[PKTStore::pktRepository_i_0_r_1_t_9_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_0_r_1_t_9_cnt++;
			}
			break;
	}
}


VOID EthernetSource::storepkt_i_1_r_0(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec)
{
	switch(t_index)
	{
		case 0:
			{
				if(PKTStore::pktRepository_i_1_r_0_t_0_busy || PKTStore::pktRepository_i_1_r_0_t_0_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_1_r_0_t_0[PKTStore::pktRepository_i_1_r_0_t_0_cnt]->len = len;
				PKTStore::pktRepository_i_1_r_0_t_0[PKTStore::pktRepository_i_1_r_0_t_0_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_1_r_0_t_0[PKTStore::pktRepository_i_1_r_0_t_0_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_1_r_0_t_0[PKTStore::pktRepository_i_1_r_0_t_0_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_1_r_0_t_0[PKTStore::pktRepository_i_1_r_0_t_0_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_1_r_0_t_0_cnt++;
			}
			break;
		case 1:
			{
				if(PKTStore::pktRepository_i_1_r_0_t_1_busy || PKTStore::pktRepository_i_1_r_0_t_1_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_1_r_0_t_1[PKTStore::pktRepository_i_1_r_0_t_1_cnt]->len = len;
				PKTStore::pktRepository_i_1_r_0_t_1[PKTStore::pktRepository_i_1_r_0_t_1_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_1_r_0_t_1[PKTStore::pktRepository_i_1_r_0_t_1_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_1_r_0_t_1[PKTStore::pktRepository_i_1_r_0_t_1_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_1_r_0_t_1[PKTStore::pktRepository_i_1_r_0_t_1_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_1_r_0_t_1_cnt++;
			}
			break;
		case 2:
			{
				if(PKTStore::pktRepository_i_1_r_0_t_2_busy || PKTStore::pktRepository_i_1_r_0_t_2_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_1_r_0_t_2[PKTStore::pktRepository_i_1_r_0_t_2_cnt]->len = len;
				PKTStore::pktRepository_i_1_r_0_t_2[PKTStore::pktRepository_i_1_r_0_t_2_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_1_r_0_t_2[PKTStore::pktRepository_i_1_r_0_t_2_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_1_r_0_t_2[PKTStore::pktRepository_i_1_r_0_t_2_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_1_r_0_t_2[PKTStore::pktRepository_i_1_r_0_t_2_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_1_r_0_t_2_cnt++;
			}
			break;
		case 3:
			{
				if(PKTStore::pktRepository_i_1_r_0_t_3_busy || PKTStore::pktRepository_i_1_r_0_t_3_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_1_r_0_t_3[PKTStore::pktRepository_i_1_r_0_t_3_cnt]->len = len;
				PKTStore::pktRepository_i_1_r_0_t_3[PKTStore::pktRepository_i_1_r_0_t_3_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_1_r_0_t_3[PKTStore::pktRepository_i_1_r_0_t_3_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_1_r_0_t_3[PKTStore::pktRepository_i_1_r_0_t_3_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_1_r_0_t_3[PKTStore::pktRepository_i_1_r_0_t_3_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_1_r_0_t_3_cnt++;
			}
			break;
		case 4:
			{
				if(PKTStore::pktRepository_i_1_r_0_t_4_busy || PKTStore::pktRepository_i_1_r_0_t_4_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_1_r_0_t_4[PKTStore::pktRepository_i_1_r_0_t_4_cnt]->len = len;
				PKTStore::pktRepository_i_1_r_0_t_4[PKTStore::pktRepository_i_1_r_0_t_4_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_1_r_0_t_4[PKTStore::pktRepository_i_1_r_0_t_4_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_1_r_0_t_4[PKTStore::pktRepository_i_1_r_0_t_4_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_1_r_0_t_4[PKTStore::pktRepository_i_1_r_0_t_4_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_1_r_0_t_4_cnt++;
			}
			break;
		case 5:
			{
				if(PKTStore::pktRepository_i_1_r_0_t_5_busy || PKTStore::pktRepository_i_1_r_0_t_5_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_1_r_0_t_5[PKTStore::pktRepository_i_1_r_0_t_5_cnt]->len = len;
				PKTStore::pktRepository_i_1_r_0_t_5[PKTStore::pktRepository_i_1_r_0_t_5_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_1_r_0_t_5[PKTStore::pktRepository_i_1_r_0_t_5_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_1_r_0_t_5[PKTStore::pktRepository_i_1_r_0_t_5_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_1_r_0_t_5[PKTStore::pktRepository_i_1_r_0_t_5_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_1_r_0_t_5_cnt++;
			}
			break;
		case 6:
			{
				if(PKTStore::pktRepository_i_1_r_0_t_6_busy || PKTStore::pktRepository_i_1_r_0_t_6_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_1_r_0_t_6[PKTStore::pktRepository_i_1_r_0_t_6_cnt]->len = len;
				PKTStore::pktRepository_i_1_r_0_t_6[PKTStore::pktRepository_i_1_r_0_t_6_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_1_r_0_t_6[PKTStore::pktRepository_i_1_r_0_t_6_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_1_r_0_t_6[PKTStore::pktRepository_i_1_r_0_t_6_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_1_r_0_t_6[PKTStore::pktRepository_i_1_r_0_t_6_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_1_r_0_t_6_cnt++;
			}
			break;
		case 7:
			{
				if(PKTStore::pktRepository_i_1_r_0_t_7_busy || PKTStore::pktRepository_i_1_r_0_t_7_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_1_r_0_t_7[PKTStore::pktRepository_i_1_r_0_t_7_cnt]->len = len;
				PKTStore::pktRepository_i_1_r_0_t_7[PKTStore::pktRepository_i_1_r_0_t_7_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_1_r_0_t_7[PKTStore::pktRepository_i_1_r_0_t_7_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_1_r_0_t_7[PKTStore::pktRepository_i_1_r_0_t_7_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_1_r_0_t_7[PKTStore::pktRepository_i_1_r_0_t_7_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_1_r_0_t_7_cnt++;
			}
			break;
		case 8:
			{
				if(PKTStore::pktRepository_i_1_r_0_t_8_busy || PKTStore::pktRepository_i_1_r_0_t_8_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_1_r_0_t_8[PKTStore::pktRepository_i_1_r_0_t_8_cnt]->len = len;
				PKTStore::pktRepository_i_1_r_0_t_8[PKTStore::pktRepository_i_1_r_0_t_8_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_1_r_0_t_8[PKTStore::pktRepository_i_1_r_0_t_8_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_1_r_0_t_8[PKTStore::pktRepository_i_1_r_0_t_8_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_1_r_0_t_8[PKTStore::pktRepository_i_1_r_0_t_8_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_1_r_0_t_8_cnt++;
			}
			break;
		case 9:
			{
				if(PKTStore::pktRepository_i_1_r_0_t_9_busy || PKTStore::pktRepository_i_1_r_0_t_9_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_1_r_0_t_9[PKTStore::pktRepository_i_1_r_0_t_9_cnt]->len = len;
				PKTStore::pktRepository_i_1_r_0_t_9[PKTStore::pktRepository_i_1_r_0_t_9_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_1_r_0_t_9[PKTStore::pktRepository_i_1_r_0_t_9_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_1_r_0_t_9[PKTStore::pktRepository_i_1_r_0_t_9_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_1_r_0_t_9[PKTStore::pktRepository_i_1_r_0_t_9_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_1_r_0_t_9_cnt++;
			}
			break;
	}
}

VOID EthernetSource::storepkt_i_1_r_1(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec)
{
	switch(t_index)
	{
		case 0:
			{
				if(PKTStore::pktRepository_i_1_r_1_t_0_busy || PKTStore::pktRepository_i_1_r_1_t_0_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_1_r_1_t_0[PKTStore::pktRepository_i_1_r_1_t_0_cnt]->len = len;
				PKTStore::pktRepository_i_1_r_1_t_0[PKTStore::pktRepository_i_1_r_1_t_0_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_1_r_1_t_0[PKTStore::pktRepository_i_1_r_1_t_0_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_1_r_1_t_0[PKTStore::pktRepository_i_1_r_1_t_0_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_1_r_1_t_0[PKTStore::pktRepository_i_1_r_1_t_0_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_1_r_1_t_0_cnt++;
			}
			break;
		case 1:
			{
				if(PKTStore::pktRepository_i_1_r_1_t_1_busy || PKTStore::pktRepository_i_1_r_1_t_1_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_1_r_1_t_1[PKTStore::pktRepository_i_1_r_1_t_1_cnt]->len = len;
				PKTStore::pktRepository_i_1_r_1_t_1[PKTStore::pktRepository_i_1_r_1_t_1_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_1_r_1_t_1[PKTStore::pktRepository_i_1_r_1_t_1_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_1_r_1_t_1[PKTStore::pktRepository_i_1_r_1_t_1_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_1_r_1_t_1[PKTStore::pktRepository_i_1_r_1_t_1_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_1_r_1_t_1_cnt++;
			}
			break;
		case 2:
			{
				if(PKTStore::pktRepository_i_1_r_1_t_2_busy || PKTStore::pktRepository_i_1_r_1_t_2_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_1_r_1_t_2[PKTStore::pktRepository_i_1_r_1_t_2_cnt]->len = len;
				PKTStore::pktRepository_i_1_r_1_t_2[PKTStore::pktRepository_i_1_r_1_t_2_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_1_r_1_t_2[PKTStore::pktRepository_i_1_r_1_t_2_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_1_r_1_t_2[PKTStore::pktRepository_i_1_r_1_t_2_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_1_r_1_t_2[PKTStore::pktRepository_i_1_r_1_t_2_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_1_r_1_t_2_cnt++;
			}
			break;
		case 3:
			{
				if(PKTStore::pktRepository_i_1_r_1_t_3_busy || PKTStore::pktRepository_i_1_r_1_t_3_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_1_r_1_t_3[PKTStore::pktRepository_i_1_r_1_t_3_cnt]->len = len;
				PKTStore::pktRepository_i_1_r_1_t_3[PKTStore::pktRepository_i_1_r_1_t_3_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_1_r_1_t_3[PKTStore::pktRepository_i_1_r_1_t_3_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_1_r_1_t_3[PKTStore::pktRepository_i_1_r_1_t_3_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_1_r_1_t_3[PKTStore::pktRepository_i_1_r_1_t_3_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_1_r_1_t_3_cnt++;
			}
			break;
		case 4:
			{
				if(PKTStore::pktRepository_i_1_r_1_t_4_busy || PKTStore::pktRepository_i_1_r_1_t_4_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_1_r_1_t_4[PKTStore::pktRepository_i_1_r_1_t_4_cnt]->len = len;
				PKTStore::pktRepository_i_1_r_1_t_4[PKTStore::pktRepository_i_1_r_1_t_4_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_1_r_1_t_4[PKTStore::pktRepository_i_1_r_1_t_4_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_1_r_1_t_4[PKTStore::pktRepository_i_1_r_1_t_4_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_1_r_1_t_4[PKTStore::pktRepository_i_1_r_1_t_4_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_1_r_1_t_4_cnt++;
			}
			break;
		case 5:
			{
				if(PKTStore::pktRepository_i_1_r_1_t_5_busy || PKTStore::pktRepository_i_1_r_1_t_5_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_1_r_1_t_5[PKTStore::pktRepository_i_1_r_1_t_5_cnt]->len = len;
				PKTStore::pktRepository_i_1_r_1_t_5[PKTStore::pktRepository_i_1_r_1_t_5_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_1_r_1_t_5[PKTStore::pktRepository_i_1_r_1_t_5_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_1_r_1_t_5[PKTStore::pktRepository_i_1_r_1_t_5_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_1_r_1_t_5[PKTStore::pktRepository_i_1_r_1_t_5_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_1_r_1_t_5_cnt++;
			}
			break;
		case 6:
			{
				if(PKTStore::pktRepository_i_1_r_1_t_6_busy || PKTStore::pktRepository_i_1_r_1_t_6_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_1_r_1_t_6[PKTStore::pktRepository_i_1_r_1_t_6_cnt]->len = len;
				PKTStore::pktRepository_i_1_r_1_t_6[PKTStore::pktRepository_i_1_r_1_t_6_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_1_r_1_t_6[PKTStore::pktRepository_i_1_r_1_t_6_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_1_r_1_t_6[PKTStore::pktRepository_i_1_r_1_t_6_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_1_r_1_t_6[PKTStore::pktRepository_i_1_r_1_t_6_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_1_r_1_t_6_cnt++;
			}
			break;
		case 7:
			{
				if(PKTStore::pktRepository_i_1_r_1_t_7_busy || PKTStore::pktRepository_i_1_r_1_t_7_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_1_r_1_t_7[PKTStore::pktRepository_i_1_r_1_t_7_cnt]->len = len;
				PKTStore::pktRepository_i_1_r_1_t_7[PKTStore::pktRepository_i_1_r_1_t_7_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_1_r_1_t_7[PKTStore::pktRepository_i_1_r_1_t_7_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_1_r_1_t_7[PKTStore::pktRepository_i_1_r_1_t_7_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_1_r_1_t_7[PKTStore::pktRepository_i_1_r_1_t_7_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_1_r_1_t_7_cnt++;
			}
			break;
		case 8:
			{
				if(PKTStore::pktRepository_i_1_r_1_t_8_busy || PKTStore::pktRepository_i_1_r_1_t_8_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_1_r_1_t_8[PKTStore::pktRepository_i_1_r_1_t_8_cnt]->len = len;
				PKTStore::pktRepository_i_1_r_1_t_8[PKTStore::pktRepository_i_1_r_1_t_8_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_1_r_1_t_8[PKTStore::pktRepository_i_1_r_1_t_8_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_1_r_1_t_8[PKTStore::pktRepository_i_1_r_1_t_8_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_1_r_1_t_8[PKTStore::pktRepository_i_1_r_1_t_8_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_1_r_1_t_8_cnt++;
			}
			break;
		case 9:
			{
				if(PKTStore::pktRepository_i_1_r_1_t_9_busy || PKTStore::pktRepository_i_1_r_1_t_9_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_1_r_1_t_9[PKTStore::pktRepository_i_1_r_1_t_9_cnt]->len = len;
				PKTStore::pktRepository_i_1_r_1_t_9[PKTStore::pktRepository_i_1_r_1_t_9_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_1_r_1_t_9[PKTStore::pktRepository_i_1_r_1_t_9_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_1_r_1_t_9[PKTStore::pktRepository_i_1_r_1_t_9_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_1_r_1_t_9[PKTStore::pktRepository_i_1_r_1_t_9_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_1_r_1_t_9_cnt++;
			}
			break;
	}
}


VOID EthernetSource::storepkt_i_2_r_0(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec)
{
	switch(t_index)
	{
		case 0:
			{
				if(PKTStore::pktRepository_i_2_r_0_t_0_busy || PKTStore::pktRepository_i_2_r_0_t_0_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_2_r_0_t_0[PKTStore::pktRepository_i_2_r_0_t_0_cnt]->len = len;
				PKTStore::pktRepository_i_2_r_0_t_0[PKTStore::pktRepository_i_2_r_0_t_0_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_2_r_0_t_0[PKTStore::pktRepository_i_2_r_0_t_0_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_2_r_0_t_0[PKTStore::pktRepository_i_2_r_0_t_0_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_2_r_0_t_0[PKTStore::pktRepository_i_2_r_0_t_0_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_2_r_0_t_0_cnt++;
			}
			break;
		case 1:
			{
				if(PKTStore::pktRepository_i_2_r_0_t_1_busy || PKTStore::pktRepository_i_2_r_0_t_1_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_2_r_0_t_1[PKTStore::pktRepository_i_2_r_0_t_1_cnt]->len = len;
				PKTStore::pktRepository_i_2_r_0_t_1[PKTStore::pktRepository_i_2_r_0_t_1_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_2_r_0_t_1[PKTStore::pktRepository_i_2_r_0_t_1_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_2_r_0_t_1[PKTStore::pktRepository_i_2_r_0_t_1_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_2_r_0_t_1[PKTStore::pktRepository_i_2_r_0_t_1_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_2_r_0_t_1_cnt++;
			}
			break;
		case 2:
			{
				if(PKTStore::pktRepository_i_2_r_0_t_2_busy || PKTStore::pktRepository_i_2_r_0_t_2_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_2_r_0_t_2[PKTStore::pktRepository_i_2_r_0_t_2_cnt]->len = len;
				PKTStore::pktRepository_i_2_r_0_t_2[PKTStore::pktRepository_i_2_r_0_t_2_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_2_r_0_t_2[PKTStore::pktRepository_i_2_r_0_t_2_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_2_r_0_t_2[PKTStore::pktRepository_i_2_r_0_t_2_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_2_r_0_t_2[PKTStore::pktRepository_i_2_r_0_t_2_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_2_r_0_t_2_cnt++;
			}
			break;
		case 3:
			{
				if(PKTStore::pktRepository_i_2_r_0_t_3_busy || PKTStore::pktRepository_i_2_r_0_t_3_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_2_r_0_t_3[PKTStore::pktRepository_i_2_r_0_t_3_cnt]->len = len;
				PKTStore::pktRepository_i_2_r_0_t_3[PKTStore::pktRepository_i_2_r_0_t_3_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_2_r_0_t_3[PKTStore::pktRepository_i_2_r_0_t_3_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_2_r_0_t_3[PKTStore::pktRepository_i_2_r_0_t_3_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_2_r_0_t_3[PKTStore::pktRepository_i_2_r_0_t_3_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_2_r_0_t_3_cnt++;
			}
			break;
		case 4:
			{
				if(PKTStore::pktRepository_i_2_r_0_t_4_busy || PKTStore::pktRepository_i_2_r_0_t_4_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_2_r_0_t_4[PKTStore::pktRepository_i_2_r_0_t_4_cnt]->len = len;
				PKTStore::pktRepository_i_2_r_0_t_4[PKTStore::pktRepository_i_2_r_0_t_4_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_2_r_0_t_4[PKTStore::pktRepository_i_2_r_0_t_4_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_2_r_0_t_4[PKTStore::pktRepository_i_2_r_0_t_4_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_2_r_0_t_4[PKTStore::pktRepository_i_2_r_0_t_4_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_2_r_0_t_4_cnt++;
			}
			break;
		case 5:
			{
				if(PKTStore::pktRepository_i_2_r_0_t_5_busy || PKTStore::pktRepository_i_2_r_0_t_5_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_2_r_0_t_5[PKTStore::pktRepository_i_2_r_0_t_5_cnt]->len = len;
				PKTStore::pktRepository_i_2_r_0_t_5[PKTStore::pktRepository_i_2_r_0_t_5_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_2_r_0_t_5[PKTStore::pktRepository_i_2_r_0_t_5_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_2_r_0_t_5[PKTStore::pktRepository_i_2_r_0_t_5_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_2_r_0_t_5[PKTStore::pktRepository_i_2_r_0_t_5_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_2_r_0_t_5_cnt++;
			}
			break;
		case 6:
			{
				if(PKTStore::pktRepository_i_2_r_0_t_6_busy || PKTStore::pktRepository_i_2_r_0_t_6_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_2_r_0_t_6[PKTStore::pktRepository_i_2_r_0_t_6_cnt]->len = len;
				PKTStore::pktRepository_i_2_r_0_t_6[PKTStore::pktRepository_i_2_r_0_t_6_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_2_r_0_t_6[PKTStore::pktRepository_i_2_r_0_t_6_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_2_r_0_t_6[PKTStore::pktRepository_i_2_r_0_t_6_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_2_r_0_t_6[PKTStore::pktRepository_i_2_r_0_t_6_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_2_r_0_t_6_cnt++;
			}
			break;
		case 7:
			{
				if(PKTStore::pktRepository_i_2_r_0_t_7_busy || PKTStore::pktRepository_i_2_r_0_t_7_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_2_r_0_t_7[PKTStore::pktRepository_i_2_r_0_t_7_cnt]->len = len;
				PKTStore::pktRepository_i_2_r_0_t_7[PKTStore::pktRepository_i_2_r_0_t_7_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_2_r_0_t_7[PKTStore::pktRepository_i_2_r_0_t_7_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_2_r_0_t_7[PKTStore::pktRepository_i_2_r_0_t_7_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_2_r_0_t_7[PKTStore::pktRepository_i_2_r_0_t_7_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_2_r_0_t_7_cnt++;
			}
			break;
		case 8:
			{
				if(PKTStore::pktRepository_i_2_r_0_t_8_busy || PKTStore::pktRepository_i_2_r_0_t_8_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_2_r_0_t_8[PKTStore::pktRepository_i_2_r_0_t_8_cnt]->len = len;
				PKTStore::pktRepository_i_2_r_0_t_8[PKTStore::pktRepository_i_2_r_0_t_8_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_2_r_0_t_8[PKTStore::pktRepository_i_2_r_0_t_8_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_2_r_0_t_8[PKTStore::pktRepository_i_2_r_0_t_8_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_2_r_0_t_8[PKTStore::pktRepository_i_2_r_0_t_8_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_2_r_0_t_8_cnt++;
			}
			break;
		case 9:
			{
				if(PKTStore::pktRepository_i_2_r_0_t_9_busy || PKTStore::pktRepository_i_2_r_0_t_9_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_2_r_0_t_9[PKTStore::pktRepository_i_2_r_0_t_9_cnt]->len = len;
				PKTStore::pktRepository_i_2_r_0_t_9[PKTStore::pktRepository_i_2_r_0_t_9_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_2_r_0_t_9[PKTStore::pktRepository_i_2_r_0_t_9_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_2_r_0_t_9[PKTStore::pktRepository_i_2_r_0_t_9_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_2_r_0_t_9[PKTStore::pktRepository_i_2_r_0_t_9_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_2_r_0_t_9_cnt++;
			}
			break;
	}
}

VOID EthernetSource::storepkt_i_2_r_1(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec)
{
	switch(t_index)
	{
		case 0:
			{
				if(PKTStore::pktRepository_i_2_r_1_t_0_busy || PKTStore::pktRepository_i_2_r_1_t_0_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_2_r_1_t_0[PKTStore::pktRepository_i_2_r_1_t_0_cnt]->len = len;
				PKTStore::pktRepository_i_2_r_1_t_0[PKTStore::pktRepository_i_2_r_1_t_0_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_2_r_1_t_0[PKTStore::pktRepository_i_2_r_1_t_0_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_2_r_1_t_0[PKTStore::pktRepository_i_2_r_1_t_0_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_2_r_1_t_0[PKTStore::pktRepository_i_2_r_1_t_0_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_2_r_1_t_0_cnt++;
			}
			break;
		case 1:
			{
				if(PKTStore::pktRepository_i_2_r_1_t_1_busy || PKTStore::pktRepository_i_2_r_1_t_1_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_2_r_1_t_1[PKTStore::pktRepository_i_2_r_1_t_1_cnt]->len = len;
				PKTStore::pktRepository_i_2_r_1_t_1[PKTStore::pktRepository_i_2_r_1_t_1_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_2_r_1_t_1[PKTStore::pktRepository_i_2_r_1_t_1_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_2_r_1_t_1[PKTStore::pktRepository_i_2_r_1_t_1_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_2_r_1_t_1[PKTStore::pktRepository_i_2_r_1_t_1_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_2_r_1_t_1_cnt++;
			}
			break;
		case 2:
			{
				if(PKTStore::pktRepository_i_2_r_1_t_2_busy || PKTStore::pktRepository_i_2_r_1_t_2_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_2_r_1_t_2[PKTStore::pktRepository_i_2_r_1_t_2_cnt]->len = len;
				PKTStore::pktRepository_i_2_r_1_t_2[PKTStore::pktRepository_i_2_r_1_t_2_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_2_r_1_t_2[PKTStore::pktRepository_i_2_r_1_t_2_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_2_r_1_t_2[PKTStore::pktRepository_i_2_r_1_t_2_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_2_r_1_t_2[PKTStore::pktRepository_i_2_r_1_t_2_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_2_r_1_t_2_cnt++;
			}
			break;
		case 3:
			{
				if(PKTStore::pktRepository_i_2_r_1_t_3_busy || PKTStore::pktRepository_i_2_r_1_t_3_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_2_r_1_t_3[PKTStore::pktRepository_i_2_r_1_t_3_cnt]->len = len;
				PKTStore::pktRepository_i_2_r_1_t_3[PKTStore::pktRepository_i_2_r_1_t_3_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_2_r_1_t_3[PKTStore::pktRepository_i_2_r_1_t_3_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_2_r_1_t_3[PKTStore::pktRepository_i_2_r_1_t_3_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_2_r_1_t_3[PKTStore::pktRepository_i_2_r_1_t_3_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_2_r_1_t_3_cnt++;
			}
			break;
		case 4:
			{
				if(PKTStore::pktRepository_i_2_r_1_t_4_busy || PKTStore::pktRepository_i_2_r_1_t_4_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_2_r_1_t_4[PKTStore::pktRepository_i_2_r_1_t_4_cnt]->len = len;
				PKTStore::pktRepository_i_2_r_1_t_4[PKTStore::pktRepository_i_2_r_1_t_4_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_2_r_1_t_4[PKTStore::pktRepository_i_2_r_1_t_4_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_2_r_1_t_4[PKTStore::pktRepository_i_2_r_1_t_4_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_2_r_1_t_4[PKTStore::pktRepository_i_2_r_1_t_4_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_2_r_1_t_4_cnt++;
			}
			break;
		case 5:
			{
				if(PKTStore::pktRepository_i_2_r_1_t_5_busy || PKTStore::pktRepository_i_2_r_1_t_5_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_2_r_1_t_5[PKTStore::pktRepository_i_2_r_1_t_5_cnt]->len = len;
				PKTStore::pktRepository_i_2_r_1_t_5[PKTStore::pktRepository_i_2_r_1_t_5_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_2_r_1_t_5[PKTStore::pktRepository_i_2_r_1_t_5_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_2_r_1_t_5[PKTStore::pktRepository_i_2_r_1_t_5_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_2_r_1_t_5[PKTStore::pktRepository_i_2_r_1_t_5_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_2_r_1_t_5_cnt++;
			}
			break;
		case 6:
			{
				if(PKTStore::pktRepository_i_2_r_1_t_6_busy || PKTStore::pktRepository_i_2_r_1_t_6_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_2_r_1_t_6[PKTStore::pktRepository_i_2_r_1_t_6_cnt]->len = len;
				PKTStore::pktRepository_i_2_r_1_t_6[PKTStore::pktRepository_i_2_r_1_t_6_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_2_r_1_t_6[PKTStore::pktRepository_i_2_r_1_t_6_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_2_r_1_t_6[PKTStore::pktRepository_i_2_r_1_t_6_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_2_r_1_t_6[PKTStore::pktRepository_i_2_r_1_t_6_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_2_r_1_t_6_cnt++;
			}
			break;
		case 7:
			{
				if(PKTStore::pktRepository_i_2_r_1_t_7_busy || PKTStore::pktRepository_i_2_r_1_t_7_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_2_r_1_t_7[PKTStore::pktRepository_i_2_r_1_t_7_cnt]->len = len;
				PKTStore::pktRepository_i_2_r_1_t_7[PKTStore::pktRepository_i_2_r_1_t_7_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_2_r_1_t_7[PKTStore::pktRepository_i_2_r_1_t_7_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_2_r_1_t_7[PKTStore::pktRepository_i_2_r_1_t_7_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_2_r_1_t_7[PKTStore::pktRepository_i_2_r_1_t_7_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_2_r_1_t_7_cnt++;
			}
			break;
		case 8:
			{
				if(PKTStore::pktRepository_i_2_r_1_t_8_busy || PKTStore::pktRepository_i_2_r_1_t_8_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_2_r_1_t_8[PKTStore::pktRepository_i_2_r_1_t_8_cnt]->len = len;
				PKTStore::pktRepository_i_2_r_1_t_8[PKTStore::pktRepository_i_2_r_1_t_8_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_2_r_1_t_8[PKTStore::pktRepository_i_2_r_1_t_8_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_2_r_1_t_8[PKTStore::pktRepository_i_2_r_1_t_8_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_2_r_1_t_8[PKTStore::pktRepository_i_2_r_1_t_8_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_2_r_1_t_8_cnt++;
			}
			break;
		case 9:
			{
				if(PKTStore::pktRepository_i_2_r_1_t_9_busy || PKTStore::pktRepository_i_2_r_1_t_9_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_2_r_1_t_9[PKTStore::pktRepository_i_2_r_1_t_9_cnt]->len = len;
				PKTStore::pktRepository_i_2_r_1_t_9[PKTStore::pktRepository_i_2_r_1_t_9_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_2_r_1_t_9[PKTStore::pktRepository_i_2_r_1_t_9_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_2_r_1_t_9[PKTStore::pktRepository_i_2_r_1_t_9_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_2_r_1_t_9[PKTStore::pktRepository_i_2_r_1_t_9_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_2_r_1_t_9_cnt++;
			}
			break;
	}
}


VOID EthernetSource::storepkt_i_3_r_0(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec)
{
	switch(t_index)
	{
		case 0:
			{
				if(PKTStore::pktRepository_i_3_r_0_t_0_busy || PKTStore::pktRepository_i_3_r_0_t_0_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_3_r_0_t_0[PKTStore::pktRepository_i_3_r_0_t_0_cnt]->len = len;
				PKTStore::pktRepository_i_3_r_0_t_0[PKTStore::pktRepository_i_3_r_0_t_0_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_3_r_0_t_0[PKTStore::pktRepository_i_3_r_0_t_0_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_3_r_0_t_0[PKTStore::pktRepository_i_3_r_0_t_0_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_3_r_0_t_0[PKTStore::pktRepository_i_3_r_0_t_0_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_3_r_0_t_0_cnt++;
			}
			break;
		case 1:
			{
				if(PKTStore::pktRepository_i_3_r_0_t_1_busy || PKTStore::pktRepository_i_3_r_0_t_1_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_3_r_0_t_1[PKTStore::pktRepository_i_3_r_0_t_1_cnt]->len = len;
				PKTStore::pktRepository_i_3_r_0_t_1[PKTStore::pktRepository_i_3_r_0_t_1_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_3_r_0_t_1[PKTStore::pktRepository_i_3_r_0_t_1_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_3_r_0_t_1[PKTStore::pktRepository_i_3_r_0_t_1_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_3_r_0_t_1[PKTStore::pktRepository_i_3_r_0_t_1_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_3_r_0_t_1_cnt++;
			}
			break;
		case 2:
			{
				if(PKTStore::pktRepository_i_3_r_0_t_2_busy || PKTStore::pktRepository_i_3_r_0_t_2_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_3_r_0_t_2[PKTStore::pktRepository_i_3_r_0_t_2_cnt]->len = len;
				PKTStore::pktRepository_i_3_r_0_t_2[PKTStore::pktRepository_i_3_r_0_t_2_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_3_r_0_t_2[PKTStore::pktRepository_i_3_r_0_t_2_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_3_r_0_t_2[PKTStore::pktRepository_i_3_r_0_t_2_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_3_r_0_t_2[PKTStore::pktRepository_i_3_r_0_t_2_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_3_r_0_t_2_cnt++;
			}
			break;
		case 3:
			{
				if(PKTStore::pktRepository_i_3_r_0_t_3_busy || PKTStore::pktRepository_i_3_r_0_t_3_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_3_r_0_t_3[PKTStore::pktRepository_i_3_r_0_t_3_cnt]->len = len;
				PKTStore::pktRepository_i_3_r_0_t_3[PKTStore::pktRepository_i_3_r_0_t_3_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_3_r_0_t_3[PKTStore::pktRepository_i_3_r_0_t_3_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_3_r_0_t_3[PKTStore::pktRepository_i_3_r_0_t_3_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_3_r_0_t_3[PKTStore::pktRepository_i_3_r_0_t_3_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_3_r_0_t_3_cnt++;
			}
			break;
		case 4:
			{
				if(PKTStore::pktRepository_i_3_r_0_t_4_busy || PKTStore::pktRepository_i_3_r_0_t_4_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_3_r_0_t_4[PKTStore::pktRepository_i_3_r_0_t_4_cnt]->len = len;
				PKTStore::pktRepository_i_3_r_0_t_4[PKTStore::pktRepository_i_3_r_0_t_4_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_3_r_0_t_4[PKTStore::pktRepository_i_3_r_0_t_4_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_3_r_0_t_4[PKTStore::pktRepository_i_3_r_0_t_4_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_3_r_0_t_4[PKTStore::pktRepository_i_3_r_0_t_4_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_3_r_0_t_4_cnt++;
			}
			break;
		case 5:
			{
				if(PKTStore::pktRepository_i_3_r_0_t_5_busy || PKTStore::pktRepository_i_3_r_0_t_5_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_3_r_0_t_5[PKTStore::pktRepository_i_3_r_0_t_5_cnt]->len = len;
				PKTStore::pktRepository_i_3_r_0_t_5[PKTStore::pktRepository_i_3_r_0_t_5_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_3_r_0_t_5[PKTStore::pktRepository_i_3_r_0_t_5_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_3_r_0_t_5[PKTStore::pktRepository_i_3_r_0_t_5_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_3_r_0_t_5[PKTStore::pktRepository_i_3_r_0_t_5_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_3_r_0_t_5_cnt++;
			}
			break;
		case 6:
			{
				if(PKTStore::pktRepository_i_3_r_0_t_6_busy || PKTStore::pktRepository_i_3_r_0_t_6_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_3_r_0_t_6[PKTStore::pktRepository_i_3_r_0_t_6_cnt]->len = len;
				PKTStore::pktRepository_i_3_r_0_t_6[PKTStore::pktRepository_i_3_r_0_t_6_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_3_r_0_t_6[PKTStore::pktRepository_i_3_r_0_t_6_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_3_r_0_t_6[PKTStore::pktRepository_i_3_r_0_t_6_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_3_r_0_t_6[PKTStore::pktRepository_i_3_r_0_t_6_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_3_r_0_t_6_cnt++;
			}
			break;
		case 7:
			{
				if(PKTStore::pktRepository_i_3_r_0_t_7_busy || PKTStore::pktRepository_i_3_r_0_t_7_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_3_r_0_t_7[PKTStore::pktRepository_i_3_r_0_t_7_cnt]->len = len;
				PKTStore::pktRepository_i_3_r_0_t_7[PKTStore::pktRepository_i_3_r_0_t_7_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_3_r_0_t_7[PKTStore::pktRepository_i_3_r_0_t_7_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_3_r_0_t_7[PKTStore::pktRepository_i_3_r_0_t_7_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_3_r_0_t_7[PKTStore::pktRepository_i_3_r_0_t_7_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_3_r_0_t_7_cnt++;
			}
			break;
		case 8:
			{
				if(PKTStore::pktRepository_i_3_r_0_t_8_busy || PKTStore::pktRepository_i_3_r_0_t_8_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_3_r_0_t_8[PKTStore::pktRepository_i_3_r_0_t_8_cnt]->len = len;
				PKTStore::pktRepository_i_3_r_0_t_8[PKTStore::pktRepository_i_3_r_0_t_8_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_3_r_0_t_8[PKTStore::pktRepository_i_3_r_0_t_8_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_3_r_0_t_8[PKTStore::pktRepository_i_3_r_0_t_8_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_3_r_0_t_8[PKTStore::pktRepository_i_3_r_0_t_8_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_3_r_0_t_8_cnt++;
			}
			break;
		case 9:
			{
				if(PKTStore::pktRepository_i_3_r_0_t_9_busy || PKTStore::pktRepository_i_3_r_0_t_9_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_3_r_0_t_9[PKTStore::pktRepository_i_3_r_0_t_9_cnt]->len = len;
				PKTStore::pktRepository_i_3_r_0_t_9[PKTStore::pktRepository_i_3_r_0_t_9_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_3_r_0_t_9[PKTStore::pktRepository_i_3_r_0_t_9_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_3_r_0_t_9[PKTStore::pktRepository_i_3_r_0_t_9_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_3_r_0_t_9[PKTStore::pktRepository_i_3_r_0_t_9_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_3_r_0_t_9_cnt++;
			}
			break;
	}
}

VOID EthernetSource::storepkt_i_3_r_1(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec)
{
	switch(t_index)
	{
		case 0:
			{
				if(PKTStore::pktRepository_i_3_r_1_t_0_busy || PKTStore::pktRepository_i_3_r_1_t_0_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_3_r_1_t_0[PKTStore::pktRepository_i_3_r_1_t_0_cnt]->len = len;
				PKTStore::pktRepository_i_3_r_1_t_0[PKTStore::pktRepository_i_3_r_1_t_0_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_3_r_1_t_0[PKTStore::pktRepository_i_3_r_1_t_0_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_3_r_1_t_0[PKTStore::pktRepository_i_3_r_1_t_0_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_3_r_1_t_0[PKTStore::pktRepository_i_3_r_1_t_0_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_3_r_1_t_0_cnt++;
			}
			break;
		case 1:
			{
				if(PKTStore::pktRepository_i_3_r_1_t_1_busy || PKTStore::pktRepository_i_3_r_1_t_1_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_3_r_1_t_1[PKTStore::pktRepository_i_3_r_1_t_1_cnt]->len = len;
				PKTStore::pktRepository_i_3_r_1_t_1[PKTStore::pktRepository_i_3_r_1_t_1_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_3_r_1_t_1[PKTStore::pktRepository_i_3_r_1_t_1_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_3_r_1_t_1[PKTStore::pktRepository_i_3_r_1_t_1_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_3_r_1_t_1[PKTStore::pktRepository_i_3_r_1_t_1_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_3_r_1_t_1_cnt++;
			}
			break;
		case 2:
			{
				if(PKTStore::pktRepository_i_3_r_1_t_2_busy || PKTStore::pktRepository_i_3_r_1_t_2_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_3_r_1_t_2[PKTStore::pktRepository_i_3_r_1_t_2_cnt]->len = len;
				PKTStore::pktRepository_i_3_r_1_t_2[PKTStore::pktRepository_i_3_r_1_t_2_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_3_r_1_t_2[PKTStore::pktRepository_i_3_r_1_t_2_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_3_r_1_t_2[PKTStore::pktRepository_i_3_r_1_t_2_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_3_r_1_t_2[PKTStore::pktRepository_i_3_r_1_t_2_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_3_r_1_t_2_cnt++;
			}
			break;
		case 3:
			{
				if(PKTStore::pktRepository_i_3_r_1_t_3_busy || PKTStore::pktRepository_i_3_r_1_t_3_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_3_r_1_t_3[PKTStore::pktRepository_i_3_r_1_t_3_cnt]->len = len;
				PKTStore::pktRepository_i_3_r_1_t_3[PKTStore::pktRepository_i_3_r_1_t_3_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_3_r_1_t_3[PKTStore::pktRepository_i_3_r_1_t_3_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_3_r_1_t_3[PKTStore::pktRepository_i_3_r_1_t_3_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_3_r_1_t_3[PKTStore::pktRepository_i_3_r_1_t_3_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_3_r_1_t_3_cnt++;
			}
			break;
		case 4:
			{
				if(PKTStore::pktRepository_i_3_r_1_t_4_busy || PKTStore::pktRepository_i_3_r_1_t_4_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_3_r_1_t_4[PKTStore::pktRepository_i_3_r_1_t_4_cnt]->len = len;
				PKTStore::pktRepository_i_3_r_1_t_4[PKTStore::pktRepository_i_3_r_1_t_4_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_3_r_1_t_4[PKTStore::pktRepository_i_3_r_1_t_4_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_3_r_1_t_4[PKTStore::pktRepository_i_3_r_1_t_4_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_3_r_1_t_4[PKTStore::pktRepository_i_3_r_1_t_4_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_3_r_1_t_4_cnt++;
			}
			break;
		case 5:
			{
				if(PKTStore::pktRepository_i_3_r_1_t_5_busy || PKTStore::pktRepository_i_3_r_1_t_5_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_3_r_1_t_5[PKTStore::pktRepository_i_3_r_1_t_5_cnt]->len = len;
				PKTStore::pktRepository_i_3_r_1_t_5[PKTStore::pktRepository_i_3_r_1_t_5_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_3_r_1_t_5[PKTStore::pktRepository_i_3_r_1_t_5_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_3_r_1_t_5[PKTStore::pktRepository_i_3_r_1_t_5_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_3_r_1_t_5[PKTStore::pktRepository_i_3_r_1_t_5_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_3_r_1_t_5_cnt++;
			}
			break;
		case 6:
			{
				if(PKTStore::pktRepository_i_3_r_1_t_6_busy || PKTStore::pktRepository_i_3_r_1_t_6_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_3_r_1_t_6[PKTStore::pktRepository_i_3_r_1_t_6_cnt]->len = len;
				PKTStore::pktRepository_i_3_r_1_t_6[PKTStore::pktRepository_i_3_r_1_t_6_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_3_r_1_t_6[PKTStore::pktRepository_i_3_r_1_t_6_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_3_r_1_t_6[PKTStore::pktRepository_i_3_r_1_t_6_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_3_r_1_t_6[PKTStore::pktRepository_i_3_r_1_t_6_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_3_r_1_t_6_cnt++;
			}
			break;
		case 7:
			{
				if(PKTStore::pktRepository_i_3_r_1_t_7_busy || PKTStore::pktRepository_i_3_r_1_t_7_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_3_r_1_t_7[PKTStore::pktRepository_i_3_r_1_t_7_cnt]->len = len;
				PKTStore::pktRepository_i_3_r_1_t_7[PKTStore::pktRepository_i_3_r_1_t_7_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_3_r_1_t_7[PKTStore::pktRepository_i_3_r_1_t_7_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_3_r_1_t_7[PKTStore::pktRepository_i_3_r_1_t_7_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_3_r_1_t_7[PKTStore::pktRepository_i_3_r_1_t_7_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_3_r_1_t_7_cnt++;
			}
			break;
		case 8:
			{
				if(PKTStore::pktRepository_i_3_r_1_t_8_busy || PKTStore::pktRepository_i_3_r_1_t_8_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_3_r_1_t_8[PKTStore::pktRepository_i_3_r_1_t_8_cnt]->len = len;
				PKTStore::pktRepository_i_3_r_1_t_8[PKTStore::pktRepository_i_3_r_1_t_8_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_3_r_1_t_8[PKTStore::pktRepository_i_3_r_1_t_8_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_3_r_1_t_8[PKTStore::pktRepository_i_3_r_1_t_8_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_3_r_1_t_8[PKTStore::pktRepository_i_3_r_1_t_8_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_3_r_1_t_8_cnt++;
			}
			break;
		case 9:
			{
				if(PKTStore::pktRepository_i_3_r_1_t_9_busy || PKTStore::pktRepository_i_3_r_1_t_9_cnt >= MAX_PKT_ALLOWED_PER_TIME_INDEX) return;
				PKTStore::pktRepository_i_3_r_1_t_9[PKTStore::pktRepository_i_3_r_1_t_9_cnt]->len = len;
				PKTStore::pktRepository_i_3_r_1_t_9[PKTStore::pktRepository_i_3_r_1_t_9_cnt]->tv_sec = tv_sec;
				PKTStore::pktRepository_i_3_r_1_t_9[PKTStore::pktRepository_i_3_r_1_t_9_cnt]->tv_nsec = tv_nsec;
				PKTStore::pktRepository_i_3_r_1_t_9[PKTStore::pktRepository_i_3_r_1_t_9_cnt]->pkt_no = PKT_COUNTER;
				memcpy(PKTStore::pktRepository_i_3_r_1_t_9[PKTStore::pktRepository_i_3_r_1_t_9_cnt]->pkt, pkt, len);
				PKTStore::pktRepository_i_3_r_1_t_9_cnt++;
			}
			break;
	}
}

