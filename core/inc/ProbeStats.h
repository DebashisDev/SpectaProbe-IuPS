/*
 * ProbeStats.h
 *
 *  Created on: Feb 1, 2017
 *      Author: Deb
 */

#ifndef CORE_SRC_PROBESTATS_H_
#define CORE_SRC_PROBESTATS_H_

#include <unistd.h>
#include "SpectaTypedef.h"
#include "Log.h"
#include "IPGlobal.h"
#include <locale.h>
#include <time.h>
#include <sys/time.h>

#include "GTPGlobal.h"
#include "SCCPGlobal.h"
#include "TCPUDPGlobal.h"
#include "DnsData.h"

class ProbeStats : public DnsData {
	public:
		ProbeStats();
		~ProbeStats();

		VOID run();

	private:
		timeval curTime;

//		void printInterfaceStats(long runTime);
		void printInterfaceStats(char *runTime);
		VOID printPktStoreStats_i_0();
		VOID printPktStoreStats_i_1();
		VOID printSccpSessionStoreStats_i_0();
		VOID printSccpSessionStoreStats_i_1();
		VOID printGTPSessionStoreStats_i_0();
		VOID printGTPSessionStoreStats_i_1();
		VOID printGTPSessionStoreStats();
		VOID printGTPcSessionFlushStats();
		VOID printIPSessionFlushStats();
		VOID printDNSSessionFlushStats();
		VOID printIUPSSessionFlushStats();
		VOID printZmqFlushStats();
		VOID printIUPSZmqFlushStats();

};

#endif /* CORE_SRC_PROBESTATS_H_ */
