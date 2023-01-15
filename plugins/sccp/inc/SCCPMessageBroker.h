/*
 * SCCPMessageBroker.h
 *
 *  Created on: Apr 2, 2017
 *      Author: Deb
 */

#ifndef PLUGINS_SCCP_SRC_SCCPMESSAGEBROKER_H_
#define PLUGINS_SCCP_SRC_SCCPMESSAGEBROKER_H_

#include "BaseConfig.h"
#include "SCCPGlobal.h"
#include "IPGlobal.h"

class SCCPMessageBroker : BaseConfig {

	public:
		SCCPMessageBroker(int intfid, int rId);
		virtual ~SCCPMessageBroker();

		VOID assignMessage(SCTPChunkMap *sctpChunkMap, MPacket *msgObj);

	private:
		int interfaceId = 0;
		int routerId = 0;
		SCTPChunkMap *sctpChunkMap;
		MPacket *msgObj;

		VOID pushMessageToQueue(int smid);

		VOID pushMessageToQueue_i_0(int smid, int idx);
		VOID pushMessageToQueue_i_1(int smid, int idx);

		VOID pushToQueue_i_0_r_0(int smid, int idx);
		VOID pushToQueue_i_0_r_1(int smid, int idx);

		VOID pushToQueue_i_1_r_0(int smid, int idx);
		VOID pushToQueue_i_1_r_1(int smid, int idx);
};

#endif /* PLUGINS_SCCP_SRC_SCCPMESSAGEBROKER_H_ */
