/*
 * GTPFlusherZmq.h
 *
 *  Created on: 13-Feb-2017
 *      Author: Deb
 */

#ifndef PLUGINS_GN_SRC_GTPFLUSHERZMQ_H_
#define PLUGINS_GN_SRC_GTPFLUSHERZMQ_H_

#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

#include "Log.h"
#include "IPGlobal.h"
#include "GTPGlobal.h"
#include "BaseConfig.h"
#include "TCPUDPGlobal.h"

#define FLASH_TYPE_GTPU	1
#define FLASH_TYPE_GTPC	2
#define FLASH_TYPE_GTPU_DNS	3

class GTPFlusherZmq : BaseConfig{

	public:

		GTPFlusherZmq();
		~GTPFlusherZmq();

		VOID run();

	private:

		timeval curTime;
		int		TPS_PER_100MS = 1000;
		VOID 	process(int index);
		VOID 	sendGTPcZmqData(std::vector<xdrStore> &zmq_flush_map, int &zmq_flush_map_cnt);
//		VOID 	sendGTPuZmqData(std::vector<xdrStore> &zmq_flush_map, int &zmq_flush_map_cnt);
		VOID 	sendGTPuZmqData(std::map<int, xdrStore> &zmq_flush_map, int &zmq_flush_map_cnt);
//		VOID 	sendGTPuDnsZmqData(std::vector<xdrStore> &zmq_flush_map, int &zmq_flush_map_cnt);
		VOID 	sendGTPuDnsZmqData(std::map<int, xdrStore> &zmq_flush_map, int &zmq_flush_map_cnt);
		VOID 	openZmq();
};
#endif /* PLUGINS_GN_SRC_GTPFLUSHERZMQ_H_ */
