/*
 * Ethernet.h
 *
 *  Created on: 04-Jul-2016
 *      Author: debashis
 */

#ifndef PACKETSOURCE_ETH_SRC_ETH_H_
#define PACKETSOURCE_ETH_SRC_ETH_H_

#include <pcap.h>
#include <unistd.h>
#include <signal.h>

#include "BaseConfig.h"
#include "Log.h"
#include "SpectaTypedef.h"
#include "GTPGlobal.h"
#include "TCPUDPGlobal.h"

using namespace std;


class EthernetSource : BaseConfig{

	public:
		EthernetSource(int perListenerRouters, int intfId);
		~EthernetSource();
		void packetReaderCallback(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);
		VOID start();
		static void pcapCallBackFunction(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);

		int pcapCaptureLoop(int pkt_count=-1) {
		    return pcap_loop(pcapHandle, pkt_count, pcapCallBackFunction, reinterpret_cast<u_char *>(this));
		}

	private:
		int InterfaceId;
		string InterfaceName;
		pcap_t *pcapHandle;
		//int pkt_counter;
		int MAX_PKT_ALLOWED_PER_TIME_INDEX = 0;
		uint64_t PKT_COUNTER = 0;

		char errbuf[PCAP_ERRBUF_SIZE];
		VOID countDiscardedPkt();
		int t_index;
		void eth_sig_handler(int signo);

		int ROUTER_TO_PROCESS = 0;
		int END_ROUTER_ID = 0;

		VOID setPktCounter();
		VOID resetPktCounter();

		VOID storepkt_i_0(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
		VOID storepkt_i_1(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
		VOID storepkt_i_2(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
		VOID storepkt_i_3(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);

		VOID storepkt_i_0_r_0(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
		VOID storepkt_i_0_r_1(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
//		VOID storepkt_i_0_r_2(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
//		VOID storepkt_i_0_r_3(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);

		VOID storepkt_i_1_r_0(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
		VOID storepkt_i_1_r_1(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
//		VOID storepkt_i_1_r_2(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
//		VOID storepkt_i_1_r_3(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);

		VOID storepkt_i_2_r_0(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
		VOID storepkt_i_2_r_1(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
//		VOID storepkt_i_2_r_2(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
//		VOID storepkt_i_2_r_3(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);

		VOID storepkt_i_3_r_0(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
		VOID storepkt_i_3_r_1(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
//		VOID storepkt_i_3_r_2(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);
//		VOID storepkt_i_3_r_3(BYTE pkt, uint16_t len, long tv_sec, uint32_t tv_nsec);



};

#endif /* PACKETSOURCE_ETH_SRC_ETH_H_ */
