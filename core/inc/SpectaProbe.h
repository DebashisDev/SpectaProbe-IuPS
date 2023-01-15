/*
 * SpectaProbe.h
 *
 *  Created on: 29-Jan-2016
 *      Author: deb
 */

#ifndef SRC_SPECTAPROBE_H_
#define SRC_SPECTAPROBE_H_

#include <signal.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "GTPXdrFlusher.h"
#include "Log.h"
#include "PacketListener.h"
#include "EthernetSource.h"
#include "PCAPSource.h"
#include "SpectaTypedef.h"
#include "EthernetParser.h"
#include "BaseConfig.h"
//#include "PacketParser.h"
#include "GConstant.h"
#include "GTPFlusherZmq.h"
#include "TraceListener.h"
#include "GTPXdrWriter.h"
#include "ProbeStats.h"
#include "GTPXdrFlusher.h"

#include "GTPConfig.h"
#include "GTPuFlusher.h"
#include "GTPcFlusher.h"

#include "IUPSFlusher.h"
#include "IUPSFlusherZmq.h"

typedef enum
{
	PCAP = 0,
	ETH,
	SF
}interfaceType;

//class SpectaProbe : public BaseConfig, public PacketParser, public IPCTransport {
class SpectaProbe : public BaseConfig {

	private:

		//void sig_handler(int signo);
		timeval curTime;
		struct tm *now_tm;

		void pinThread(pthread_t th,int i);

		VOID startInterface();
		VOID readIPRange();
		VOID openZmq();

		VOID initialize_pkt_repo();

		VOID initialize_pkt_repo_i_0();
		VOID initialize_pkt_repo_i_1();
		VOID initialize_pkt_repo_i_2();
		VOID initialize_pkt_repo_i_3();

		VOID process();
		VOID initializeLog();
		VOID initializeConfig();
		VOID readConfiguration();
		bool isRepositoryInitialized();

		VOID dumpStats();
		VOID loadStats();

	public:
		SpectaProbe(char *fileName);
		~SpectaProbe();
		VOID start();
};

#endif /* SRC_SPECTAPROBE_H_ */
