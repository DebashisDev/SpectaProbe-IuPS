/*
 * PacketRouter.h
 *
 *  Created on: Nov 22, 2016
 *      Author: Debashis
 */

#ifndef CORE_SRC_PACKETROUTER_H_
#define CORE_SRC_PACKETROUTER_H_

#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "SpectaTypedef.h"
#include "BWData.h"
#include "EthernetParser.h"
#include "GTPMessageBroker.h"
#include "SCCPMessageBroker.h"
#include "BaseConfig.h"
#include "Log.h"
#include "IPGlobal.h"

class PacketRouter : public BaseConfig {
	public:

		PacketRouter(int intfid, int rid, int totrouters, int coreid);
		~PacketRouter();

		bool isRepositoryInitialized();

		VOID run();

	private:
		int interfaceId = 0;
		int routerId = 0;
		int routerTotal = 0;
		int coreId = 0;

		bool mem_init = true;

		timeval curTime;
		bool 	dayChanged = false;
		int		curMin = 0;
		int 	prevMin = 0;

		int printCnt = 0;

		BOOL repoInitStatus = false;

		MPacket *msgObj;
		RawPkt *rawPkt;

		BWData 			*bwData;
		EthernetParser *ethParser;
		GTPMessageBroker *gtpMsgBroker;
		SCCPMessageBroker *sccpMsgBroker;

		char * ByteToString(const void* pv, int len);
		int getCurrentSec();

		VOID processQueue(int t_index);

		VOID processQueueDecode(bool &pktRepository_busy, long &pktRepository_cnt, std::map<long, RawPkt*> &pktRepository);

		VOID processQueue_i_0(int t_index);
		VOID processQueue_i_1(int t_index);
		VOID processQueue_i_2(int t_index);
		VOID processQueue_i_3(int t_index);

		VOID processQueue_i_0_r_0(int t_index);
		VOID processQueue_i_0_r_1(int t_index);
//		VOID processQueue_i_0_r_2(int t_index);
//		VOID processQueue_i_0_r_3(int t_index);

		VOID processQueue_i_1_r_0(int t_index);
		VOID processQueue_i_1_r_1(int t_index);
//		VOID processQueue_i_1_r_2(int t_index);
//		VOID processQueue_i_1_r_3(int t_index);

		VOID processQueue_i_2_r_0(int t_index);
		VOID processQueue_i_2_r_1(int t_index);
//		VOID processQueue_i_2_r_2(int t_index);
//		VOID processQueue_i_2_r_3(int t_index);

		VOID processQueue_i_3_r_0(int t_index);
		VOID processQueue_i_3_r_1(int t_index);
//		VOID processQueue_i_3_r_2(int t_index);
//		VOID processQueue_i_3_r_3(int t_index);


		VOID decodePacket();
		VOID countPacket(bool process);
		VOID writeTrace(RawPkt *rawPkt);
		VOID writeTrace_i_0(int index, string hexdump);
		VOID writeTrace_i_1(int index, string hexdump);
		VOID writeTrace_i_2(int index, string hexdump);
		VOID writeTrace_i_3(int index, string hexdump);

};

#endif /* CORE_SRC_PACKETROUTER_H_ */
