/*
 * PCAP.h
 *
 *  Created on: 04-Jul-2016
 *      Author: deb
 */

#ifndef PACKETSOURCE_PCAP_SRC_PCAP_H_
#define PACKETSOURCE_PCAP_SRC_PCAP_H_

#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>
#include <pthread.h>

#include "EthernetParser.h"
#include "ProbeUtility.h"

#include "PacketRouter.h"
#include "GTPSessionManager.h"
#include "GTPMessageBroker.h"

using namespace std;

class PCAPSource {
	private:
		void pcapOpenFile();
		static pcap_t *pcapHandle;
		std::string strInputFile;
		char errbuf[PCAP_ERRBUF_SIZE];
		static int pkt_counter;
		VOID printStats();

	public:
		PCAPSource();
		~PCAPSource();
		char  ranapXmlFile[100];

		VOID pcapReader(string fileName);
		void openRanapXMLFile();
		void closeRanapXMLFile();
		static void packetReaderCallback(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);
};

#endif /* PACKETSOURCE_PCAP_SRC_PCAP_H_ */
