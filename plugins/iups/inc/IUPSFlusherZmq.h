/*
 * IUPSFlusherZmq.h
 *
 *  Created on: 13-Feb-2017
 *      Author: Deb
 */

#ifndef PLUGINS_IUPS_SRC_IUPSFLUSHERZMQ_H_
#define PLUGINS_IUPS_SRC_IUPSFLUSHERZMQ_H_

#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

#include "Log.h"
#include "IPGlobal.h"
#include "IUPSGlobal.h"
#include "BaseConfig.h"

#define FLASH_TYPE_IUPS	4

class IUPSFlusherZmq : BaseConfig{

	public:
		IUPSFlusherZmq();
		~IUPSFlusherZmq();

		VOID run();

	private:

		timeval curTime;
		int		TPS_PER_100MS = 1000;
		VOID 	process(int index);
		VOID 	sendIupsZmqData(std::string (&zmq_flush_map)[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE], int &zmq_flush_map_cnt);
		VOID 	openZmq();
};
#endif /* PLUGINS_IUPS_SRC_IUPSFLUSHERZMQ_H_ */
