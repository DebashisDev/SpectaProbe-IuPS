/*
 * GTPMessageBroker.h
 *
 *  Created on: Dec 5, 2016
 *      Author: Debashis
 */

#ifndef PLUGINS_GN_SRC_GTPMESSAGEBROKER_H_
#define PLUGINS_GN_SRC_GTPMESSAGEBROKER_H_

#include <unistd.h>
#include "IPGlobal.h"
#include "BaseConfig.h"
#include "GTPGlobal.h"

class GTPMessageBroker : BaseConfig {
	public:
		GTPMessageBroker(int intfid, int rId);
		virtual ~GTPMessageBroker();

		VOID assignMessage(MPacket *msgObj);

	private:
		int interfaceId = 0;
		int routerId = 0;

		VOID updateGTPcCounter();
		VOID updateGTPuCounter();

		VOID pushMessageToQueue(int smid, MPacket *msgObj);

		VOID pushMessageToQueue_i_0(int smid, int idx, MPacket *msgObj);
		VOID pushMessageToQueue_i_1(int smid, int idx, MPacket *msgObj);
		VOID pushMessageToQueue_i_2(int smid, int idx, MPacket *msgObj);
		VOID pushMessageToQueue_i_3(int smid, int idx, MPacket *msgObj);

		VOID pushGTPCMessageToSmgr(MPacket *msgObj);
		VOID pushGTPUMessageToSmgr(MPacket *msgObj);

		VOID pushToQueue_i_0_r_0(int smid, int idx, MPacket *msgObj);
		VOID pushToQueue_i_0_r_1(int smid, int idx, MPacket *msgObj);
		VOID pushToQueue_i_0_r_2(int smid, int idx, MPacket *msgObj);
		VOID pushToQueue_i_0_r_3(int smid, int idx, MPacket *msgObj);

		VOID pushToQueue_i_1_r_0(int smid, int idx, MPacket *msgObj);
		VOID pushToQueue_i_1_r_1(int smid, int idx, MPacket *msgObj);
		VOID pushToQueue_i_1_r_2(int smid, int idx, MPacket *msgObj);
		VOID pushToQueue_i_1_r_3(int smid, int idx, MPacket *msgObj);

		VOID pushToQueue_i_2_r_0(int smid, int idx, MPacket *msgObj);
		VOID pushToQueue_i_2_r_1(int smid, int idx, MPacket *msgObj);
		VOID pushToQueue_i_2_r_2(int smid, int idx, MPacket *msgObj);
		VOID pushToQueue_i_2_r_3(int smid, int idx, MPacket *msgObj);

		VOID pushToQueue_i_3_r_0(int smid, int idx, MPacket *msgObj);
		VOID pushToQueue_i_3_r_1(int smid, int idx, MPacket *msgObj);
		VOID pushToQueue_i_3_r_2(int smid, int idx, MPacket *msgObj);
		VOID pushToQueue_i_3_r_3(int smid, int idx, MPacket *msgObj);

};

#endif /* PLUGINS_GN_SRC_GTPMESSAGEBROKER_H_ */
