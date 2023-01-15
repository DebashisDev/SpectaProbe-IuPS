/*
 * PCAP.cpp
 *
 *  Created on: 04-Jul-2016
 *      Author: deb
 */

#include <pcap.h>
#include <unistd.h>

#include "PCAPSource.h"

#include "IPSessionManager.h"
#include "GTPSessionManager.h"
#include "GTPGlobal.h"

double lastTimestamp = 0;

using namespace std::placeholders;

string interfaceFlname;
pcap_t* PCAPSource::pcapHandle = NULL;
int PCAPSource::pkt_counter = 0;

PacketRouter *pcapRouter[8];
GTPSessionManager *pcapGTPSessionManager[10];

int pktcount = 0;
int pcaptargetRouter = 0;

time_t pcapnowglb;
struct tm *pcapnow_tm_glb;
int pcapcurrentSecGlb = 0;

PCAPSource::PCAPSource() {
}

PCAPSource::~PCAPSource() {
}

VOID pcaphexdump(const void* pv, int len)
{
	const unsigned char* p = (const unsigned char*) pv;
	int i;
	for( i = 0; i < len; ++i ) {
		const char* eos;
			switch( i & 15 ) {
				case 0:
					printf("%08x  ", i);
					eos = "";
					break;
				case 1:
					eos = " ";
					break;
				case 15:
					eos = "\n";
					break;
				default:
					eos = (i & 1) ? " " : "";
					break;
			}
			printf("%02x%s", (unsigned) p[i], eos);
	}
	printf(((len & 15) == 0) ? "\n" : "\n\n");

}

void PCAPSource::packetReaderCallback(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
	time_t now;
	struct tm *now_tm;
	pcapnowglb = time(NULL);
	pcapnow_tm_glb = localtime(&pcapnowglb);
	pcapcurrentSecGlb 	= pcapnow_tm_glb->tm_sec;
	struct timespec *ts_out;
	pktcount ++;
	IPGlobal::t_FrameCount++;
//	pcaphexdump(packet, header->len);
//	exit(1);

//	if(pktcount > 1)
//	{
//
//	}
//	else
//	{

//	pcapRouter[pcaptargetRouter]->submit(pcapcurrentSecGlb, (BYTE)packet, header->len, IPGlobal::t_FrameCount, 0);
	pcaptargetRouter++;
	if(pcaptargetRouter >= 4)
		pcaptargetRouter = 0;
//	}

}

void *pcaprouterThread(void* arg)
{
	PacketRouter *ft = (PacketRouter*)arg;
	ft->run();
	return NULL;
}

void *pcapgtpSMThread(void* arg)
{
	GTPSessionManager *ft = (GTPSessionManager*)arg;
	ft->run();
	return NULL;
}


void PCAPSource::pcapReader(string pcapfile) {
#if 0
	TCHAR errbuf[PCAP_ERRBUF_SIZE];
	int data1, data2, data3, data4;
	GTPGlobal *gGlobal = new GTPGlobal();
	pthread_t threadRouter[IPGlobal::packetRouterInstances];
	pthread_t threadGtpSM[10];

	data1 = data2 = data3 = data4 = 0;
	// Initialize Timer
	timeval start;
	gettimeofday(&start,NULL);

	mapTcpLock::count 	= 1;
	mapUdpLock::count 	= 1;
	mapDnsLock::count 	= 1;
	mapOtrLock::count	= 1;
	mapGtpLock::count	= 1;
	mapGxLock::count	= 1;
	mapRaLock::count	= 1;
	gSessionLock::count = 1;


	// For reading RANAP packets from xml file
	//openRanapXMLFile ();
	int fileId = 12;

	/* Create Threads to receive Packets from VInterface */
	for(int viCounter = 0; viCounter < IPGlobal::packetRouterInstances; viCounter++) {
		pcapRouter[viCounter] = new PacketRouter(0, viCounter);
		pthread_create(&threadRouter[viCounter], NULL, pcaprouterThread, pcapRouter[viCounter]);
		sleep(1);
	}

	/* Create GTPC Session Manager Threads */
	for(int viCounter = 0; viCounter < GContainer::config->MAX_SESSION_MANAGER; viCounter++) {
		pcapGTPSessionManager[viCounter] = new GTPSessionManager(viCounter);
		pthread_create(&threadGtpSM[viCounter], NULL, pcapgtpSMThread, pcapGTPSessionManager[viCounter]);
	}

//	while(true)
//	{
//		if(fileId > 11) fileId = 1;
//		interfaceFlname = pcapfile; //+ std::to_string(fileId);
//
//		printf("Processing PCAP file : %s\n",interfaceFlname.c_str());
//
//		pcapHandle = pcap_open_offline(interfaceFlname.c_str(), errbuf);
//
//		if(pcapHandle == NULL) {
//			cout << "ERROR !!! In reading PCAP File " << interfaceFlname << endl;
//			exit(1);
//		}
//
//		//This loop continues listening the interface
//		pcap_loop(pcapHandle, -1, packetReaderCallback, (u_char *)&pkt_counter);
//		pcap_close(pcapHandle);  //close the PCAP file
//		fileId++;
//	}

	interfaceFlname = pcapfile;
	printf("Processing PCAP file : %s\n",interfaceFlname.c_str());
	pcapHandle = pcap_open_offline(interfaceFlname.c_str(), errbuf);

	if(pcapHandle == NULL) {
		cout << "ERROR !!! In reading PCAP File " << interfaceFlname << endl;
		exit(1);
	}

	//This loop continues listening the interface
	pcap_loop(pcapHandle, -1, packetReaderCallback, (u_char *)&pkt_counter);
	pcap_close(pcapHandle);  //close the PCAP file

#endif

	while(true)
	{
		//printf("\nDecording Completed Packet Processed: %lu Send: %lu| Rcv: %lu| SM Rcv: %lu, Queue Size : %d\n",
		//		IPGlobal::t_FrameCount, IPGlobal::sendQ, IPGlobal::recvQ, IPGlobal::smRcv, IPGlobal::smQid[0].size());
		sleep(1);
		printStats();
	}
}


VOID PCAPSource::printStats(){
	int i = 0;

	long totalCount[6];

//			totalCount[0] = 0;
//			totalCount[1] = 0;
//			totalCount[2] = 0;
//			totalCount[3] = 0;
//			totalCount[4] = 0;
//			totalCount[5] = 0;

//			for( i = 0; i < IPGlobal::packetRouterInstances; i++ ) {
//				printf("                    %08ld %08ld %08ld %08ld %08ld %08ld\n",
//						pcapRouter[i]->pktRepository_0_cnt,
//						pcapRouter[i]->pktRepository_1_cnt,
//						pcapRouter[i]->pktRepository_2_cnt,
//						pcapRouter[i]->pktRepository_3_cnt,
//						pcapRouter[i]->pktRepository_4_cnt,
//						pcapRouter[i]->pktRepository_5_cnt);
//
//				totalCount[0] = totalCount[0] + pcapRouter[i]->pktRepository_0_cnt;
//				totalCount[1] = totalCount[1] + pcapRouter[i]->pktRepository_1_cnt;
//				totalCount[2] = totalCount[2] + pcapRouter[i]->pktRepository_2_cnt;
//				totalCount[3] = totalCount[3] + pcapRouter[i]->pktRepository_3_cnt;
//				totalCount[4] = totalCount[4] + pcapRouter[i]->pktRepository_4_cnt;
//				totalCount[5] = totalCount[5] + pcapRouter[i]->pktRepository_5_cnt;
//			}
//			printf("                    ------------------------------------------------------\n");
//			printf("                    ");
//			for( i = 0; i < 6; i++ ) {
//				printf("%08ld ", totalCount[i]);
//			}
//			printf("\n\n");
//
//			totalCount[0] = 0;
//			totalCount[1] = 0;
//			totalCount[2] = 0;
//			totalCount[3] = 0;
//			totalCount[4] = 0;
//			totalCount[5] = 0;
//
//			long t_0_cnt = 0;
//			long t_1_cnt = 0;
//			long t_2_cnt = 0;
//			long t_3_cnt = 0;
//			long t_4_cnt = 0;
//			long t_5_cnt = 0;
//
//			if(4 > 0){
//
//				t_0_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_0_t_0.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_0_t_0.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_0_t_0.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_0_t_0.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_0_t_0.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_0_t_0.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_0_t_0.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_0_t_0.size();
//
//				t_1_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_0_t_1.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_0_t_1.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_0_t_1.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_0_t_1.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_0_t_1.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_0_t_1.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_0_t_1.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_0_t_1.size();
//
//				t_2_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_0_t_2.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_0_t_2.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_0_t_2.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_0_t_2.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_0_t_2.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_0_t_2.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_0_t_2.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_0_t_2.size();
//
//				t_3_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_0_t_3.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_0_t_3.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_0_t_3.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_0_t_3.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_0_t_3.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_0_t_3.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_0_t_3.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_0_t_3.size();
//
//				t_4_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_0_t_4.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_0_t_4.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_0_t_4.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_0_t_4.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_0_t_4.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_0_t_4.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_0_t_4.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_0_t_4.size();
//
//				t_5_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_0_t_5.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_0_t_5.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_0_t_5.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_0_t_5.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_0_t_5.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_0_t_5.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_0_t_5.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_0_t_4.size();
//
//				printf("                    %08ld %08ld %08ld %08ld %08ld %08ld\n",
//					t_0_cnt,t_1_cnt,t_2_cnt,t_3_cnt,t_4_cnt,t_5_cnt);
//
//				totalCount[0] = totalCount[0] + t_0_cnt;
//				totalCount[1] = totalCount[1] + t_1_cnt;
//				totalCount[2] = totalCount[2] + t_2_cnt;
//				totalCount[3] = totalCount[3] + t_3_cnt;
//				totalCount[4] = totalCount[4] + t_4_cnt;
//				totalCount[5] = totalCount[5] + t_5_cnt;
//			}
//
//			if(4 > 1){
//				t_0_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_1_t_0.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_1_t_0.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_1_t_0.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_1_t_0.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_1_t_0.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_1_t_0.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_1_t_0.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_1_t_0.size();
//
//				t_1_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_1_t_1.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_1_t_1.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_1_t_1.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_1_t_1.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_1_t_1.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_1_t_1.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_1_t_1.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_1_t_1.size();
//
//				t_2_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_1_t_2.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_1_t_2.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_1_t_2.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_1_t_2.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_1_t_2.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_1_t_2.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_1_t_2.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_1_t_2.size();
//
//				t_3_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_1_t_3.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_1_t_3.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_1_t_3.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_1_t_3.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_1_t_3.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_1_t_3.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_1_t_3.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_1_t_3.size();
//
//				t_4_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_1_t_4.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_1_t_4.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_1_t_4.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_1_t_4.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_1_t_4.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_1_t_4.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_1_t_4.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_1_t_4.size();
//
//				t_5_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_1_t_5.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_1_t_5.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_1_t_5.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_1_t_5.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_1_t_5.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_1_t_5.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_1_t_5.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_1_t_4.size();
//
//				printf("                    %08ld %08ld %08ld %08ld %08ld %08ld\n",
//					t_0_cnt,t_1_cnt,t_2_cnt,t_3_cnt,t_4_cnt,t_5_cnt);
//
//				totalCount[0] = totalCount[0] + t_0_cnt;
//				totalCount[1] = totalCount[1] + t_1_cnt;
//				totalCount[2] = totalCount[2] + t_2_cnt;
//				totalCount[3] = totalCount[3] + t_3_cnt;
//				totalCount[4] = totalCount[4] + t_4_cnt;
//				totalCount[5] = totalCount[5] + t_5_cnt;
//			}
//
//			if(4 > 2){
//				t_0_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_2_t_0.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_2_t_0.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_2_t_0.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_2_t_0.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_2_t_0.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_2_t_0.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_2_t_0.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_2_t_0.size();
//
//				t_1_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_2_t_1.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_2_t_1.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_2_t_1.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_2_t_1.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_2_t_1.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_2_t_1.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_2_t_1.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_2_t_1.size();
//
//				t_2_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_2_t_2.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_2_t_2.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_2_t_2.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_2_t_2.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_2_t_2.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_2_t_2.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_2_t_2.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_2_t_2.size();
//
//				t_3_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_2_t_3.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_2_t_3.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_2_t_3.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_2_t_3.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_2_t_3.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_2_t_3.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_2_t_3.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_2_t_3.size();
//
//				t_4_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_2_t_4.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_2_t_4.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_2_t_4.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_2_t_4.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_2_t_4.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_2_t_4.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_2_t_4.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_2_t_4.size();
//
//				t_5_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_2_t_5.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_2_t_5.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_2_t_5.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_2_t_5.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_2_t_5.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_2_t_5.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_2_t_5.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_2_t_4.size();
//
//				printf("                    %08ld %08ld %08ld %08ld %08ld %08ld\n",
//					t_0_cnt,t_1_cnt,t_2_cnt,t_3_cnt,t_4_cnt,t_5_cnt);
//
//				totalCount[0] = totalCount[0] + t_0_cnt;
//				totalCount[1] = totalCount[1] + t_1_cnt;
//				totalCount[2] = totalCount[2] + t_2_cnt;
//				totalCount[3] = totalCount[3] + t_3_cnt;
//				totalCount[4] = totalCount[4] + t_4_cnt;
//				totalCount[5] = totalCount[5] + t_5_cnt;
//			}
//			if(4 > 3){
//				t_0_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_3_t_0.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_3_t_0.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_3_t_0.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_3_t_0.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_3_t_0.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_3_t_0.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_3_t_0.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_3_t_0.size();
//
//				t_1_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_3_t_1.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_3_t_1.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_3_t_1.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_3_t_1.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_3_t_1.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_3_t_1.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_3_t_1.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_3_t_1.size();
//
//				t_2_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_3_t_2.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_3_t_2.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_3_t_2.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_3_t_2.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_3_t_2.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_3_t_2.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_3_t_2.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_3_t_2.size();
//
//				t_3_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_3_t_3.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_3_t_3.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_3_t_3.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_3_t_3.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_3_t_3.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_3_t_3.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_3_t_3.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_3_t_3.size();
//
//				t_4_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_3_t_4.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_3_t_4.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_3_t_4.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_3_t_4.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_3_t_4.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_3_t_4.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_3_t_4.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_3_t_4.size();
//
//				t_5_cnt = 	MSGStoreGTPC::gtpc_msg_i_0_r_0_sm_3_t_5.size() + MSGStoreGTPC::gtpc_msg_i_0_r_1_sm_3_t_5.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_2_sm_3_t_5.size() + MSGStoreGTPC::gtpc_msg_i_0_r_3_sm_3_t_5.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_4_sm_3_t_5.size() + MSGStoreGTPC::gtpc_msg_i_0_r_5_sm_3_t_5.size() +
//							MSGStoreGTPC::gtpc_msg_i_0_r_6_sm_3_t_5.size() + MSGStoreGTPC::gtpc_msg_i_0_r_7_sm_3_t_4.size();
//
//				printf("                    %08ld %08ld %08ld %08ld %08ld %08ld\n",
//					t_0_cnt,t_1_cnt,t_2_cnt,t_3_cnt,t_4_cnt,t_5_cnt);
//
//				totalCount[0] = totalCount[0] + t_0_cnt;
//				totalCount[1] = totalCount[1] + t_1_cnt;
//				totalCount[2] = totalCount[2] + t_2_cnt;
//				totalCount[3] = totalCount[3] + t_3_cnt;
//				totalCount[4] = totalCount[4] + t_4_cnt;
//				totalCount[5] = totalCount[5] + t_5_cnt;
//			}
//			printf("                    ------------------------------------------------------\n");
//			printf("                    ");
//			for( i = 0; i < 6; i++ ) {
//				printf("%08ld ", totalCount[i]);
//			}
//			printf("\n\n");

#if 0
			totalCount[0] = 0;
			totalCount[1] = 0;
			totalCount[2] = 0;
			totalCount[3] = 0;
			totalCount[4] = 0;
			totalCount[5] = 0;

			if(4 > 0){
				printf("                    %08ld %08ld %08ld %08ld %08ld %08ld\n",
						GTPFlushRepository::gtpcFlushMap_sm_0_t_0.size(),
						GTPFlushRepository::gtpcFlushMap_sm_0_t_1.size(),
						GTPFlushRepository::gtpcFlushMap_sm_0_t_2.size(),
						GTPFlushRepository::gtpcFlushMap_sm_0_t_3.size(),
						GTPFlushRepository::gtpcFlushMap_sm_0_t_4.size(),
						GTPFlushRepository::gtpcFlushMap_sm_0_t_5.size());

				totalCount[0] = totalCount[0] + GTPFlushRepository::gtpcFlushMap_sm_0_t_0.size();
				totalCount[1] = totalCount[1] + GTPFlushRepository::gtpcFlushMap_sm_0_t_1.size();
				totalCount[2] = totalCount[2] + GTPFlushRepository::gtpcFlushMap_sm_0_t_2.size();
				totalCount[3] = totalCount[3] + GTPFlushRepository::gtpcFlushMap_sm_0_t_3.size();
				totalCount[4] = totalCount[4] + GTPFlushRepository::gtpcFlushMap_sm_0_t_4.size();
				totalCount[5] = totalCount[5] + GTPFlushRepository::gtpcFlushMap_sm_0_t_5.size();
			}

			if(4 > 1){
				printf("                    %08ld %08ld %08ld %08ld %08ld %08ld\n",
										GTPFlushRepository::gtpcFlushMap_sm_1_t_0.size(),
										GTPFlushRepository::gtpcFlushMap_sm_1_t_1.size(),
										GTPFlushRepository::gtpcFlushMap_sm_1_t_2.size(),
										GTPFlushRepository::gtpcFlushMap_sm_1_t_3.size(),
										GTPFlushRepository::gtpcFlushMap_sm_1_t_4.size(),
										GTPFlushRepository::gtpcFlushMap_sm_1_t_5.size());

								totalCount[0] = totalCount[0] + GTPFlushRepository::gtpcFlushMap_sm_1_t_0.size();
								totalCount[1] = totalCount[1] + GTPFlushRepository::gtpcFlushMap_sm_1_t_1.size();
								totalCount[2] = totalCount[2] + GTPFlushRepository::gtpcFlushMap_sm_1_t_2.size();
								totalCount[3] = totalCount[3] + GTPFlushRepository::gtpcFlushMap_sm_1_t_3.size();
								totalCount[4] = totalCount[4] + GTPFlushRepository::gtpcFlushMap_sm_1_t_4.size();
								totalCount[5] = totalCount[5] + GTPFlushRepository::gtpcFlushMap_sm_1_t_5.size();
			}

			if(4 > 2){
				printf("                    %08ld %08ld %08ld %08ld %08ld %08ld\n",
										GTPFlushRepository::gtpcFlushMap_sm_2_t_0.size(),
										GTPFlushRepository::gtpcFlushMap_sm_2_t_1.size(),
										GTPFlushRepository::gtpcFlushMap_sm_2_t_2.size(),
										GTPFlushRepository::gtpcFlushMap_sm_2_t_3.size(),
										GTPFlushRepository::gtpcFlushMap_sm_2_t_4.size(),
										GTPFlushRepository::gtpcFlushMap_sm_2_t_5.size());

								totalCount[0] = totalCount[0] + GTPFlushRepository::gtpcFlushMap_sm_2_t_0.size();
								totalCount[1] = totalCount[1] + GTPFlushRepository::gtpcFlushMap_sm_2_t_1.size();
								totalCount[2] = totalCount[2] + GTPFlushRepository::gtpcFlushMap_sm_2_t_2.size();
								totalCount[3] = totalCount[3] + GTPFlushRepository::gtpcFlushMap_sm_2_t_3.size();
								totalCount[4] = totalCount[4] + GTPFlushRepository::gtpcFlushMap_sm_2_t_4.size();
								totalCount[5] = totalCount[5] + GTPFlushRepository::gtpcFlushMap_sm_2_t_5.size();
			}
			if(4 > 3){
				printf("                    %08ld %08ld %08ld %08ld %08ld %08ld\n",
										GTPFlushRepository::gtpcFlushMap_sm_3_t_0.size(),
										GTPFlushRepository::gtpcFlushMap_sm_3_t_1.size(),
										GTPFlushRepository::gtpcFlushMap_sm_3_t_2.size(),
										GTPFlushRepository::gtpcFlushMap_sm_3_t_3.size(),
										GTPFlushRepository::gtpcFlushMap_sm_3_t_4.size(),
										GTPFlushRepository::gtpcFlushMap_sm_3_t_5.size());

								totalCount[0] = totalCount[0] + GTPFlushRepository::gtpcFlushMap_sm_3_t_0.size();
								totalCount[1] = totalCount[1] + GTPFlushRepository::gtpcFlushMap_sm_3_t_1.size();
								totalCount[2] = totalCount[2] + GTPFlushRepository::gtpcFlushMap_sm_3_t_2.size();
								totalCount[3] = totalCount[3] + GTPFlushRepository::gtpcFlushMap_sm_3_t_3.size();
								totalCount[4] = totalCount[4] + GTPFlushRepository::gtpcFlushMap_sm_3_t_4.size();
								totalCount[5] = totalCount[5] + GTPFlushRepository::gtpcFlushMap_sm_3_t_5.size();
			}
			printf("                    ------------------------------------------------------\n");
			printf("                    ");
			for( i = 0; i < 6; i++ ) {
				printf("%08ld ", totalCount[i]);
			}
			printf("\n\n");
#endif
}
