/*
 * SCCPMessageBroker.cpp
 *
 *  Created on: Apr 2, 2017
 *      Author: Deb
 */

#include "SCCPMessageBroker.h"

SCCPMessageBroker::SCCPMessageBroker(int intfid, int rId) {
	this->interfaceId = intfid;
	this->routerId = rId;
	this->msgObj = NULL;
}

SCCPMessageBroker::~SCCPMessageBroker() {
}


VOID SCCPMessageBroker::assignMessage(SCTPChunkMap *sctpChnkMap, MPacket *msgPkt)
{
//	this->sctpChunkMap.insert(sctpChnkMap.begin(),sctpChnkMap.end());
	this->sctpChunkMap = sctpChnkMap;
	this->msgObj = msgPkt;
	pushMessageToQueue(0);
}


VOID SCCPMessageBroker::pushMessageToQueue(int smid)
{
	long epochsec = getCurrentEpochSeconds();

	int idx = 0;

//	idx = (((epochsec % 100) /10)  % IPGlobal::SESSION_MANAGER_TIMEINDEX) + 1;
//	if(idx >= IPGlobal::SESSION_MANAGER_TIMEINDEX) idx = idx - IPGlobal::SESSION_MANAGER_TIMEINDEX;

	idx = WRITE_TIME_INDEX(epochsec);

	switch(interfaceId)
	{
		case 0:
			pushMessageToQueue_i_0(smid, idx);
			break;
		case 1:
			pushMessageToQueue_i_1(smid, idx);
			break;
	}
}


VOID SCCPMessageBroker::pushMessageToQueue_i_0(int smid, int idx)
{
	switch(routerId)
	{
		case 0:
			pushToQueue_i_0_r_0(smid, idx);
			break;
		case 1:
			pushToQueue_i_0_r_1(smid, idx);
			break;
			break;
	}
}

VOID SCCPMessageBroker::pushMessageToQueue_i_1(int smid, int idx)
{
	switch(routerId)
	{
		case 0:
			pushToQueue_i_1_r_0(smid, idx);
			break;
		case 1:
			pushToQueue_i_1_r_1(smid, idx);
			break;
	}
}


VOID SCCPMessageBroker::pushToQueue_i_0_r_0(int smid, int idx){

	int chunks = sctpChunkMap->size();

	switch(smid)
	{
		case 0:
			{


				switch(idx)
				{
					case 0:
						if(SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_0_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_0_r_0_t_0[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_0[SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_0_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_0_cnt++;
						break;
					case 1:
						if(SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_1_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_0_r_0_t_1[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_1[SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_1_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_1_cnt++;
						break;
					case 2:
						if(SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_2_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_0_r_0_t_2[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_2[SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_2_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_2_cnt++;
						break;
					case 3:
						if(SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_3_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_0_r_0_t_3[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_3[SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_3_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_3_cnt++;
						break;
					case 4:
						if(SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_4_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_0_r_0_t_4[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_4[SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_4_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_4_cnt++;
						break;
					case 5:
						if(SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_5_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_0_r_0_t_5[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_5[SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_5_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_5_cnt++;
						break;
					case 6:
						if(SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_6_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_0_r_0_t_6[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_6[SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_6_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_6_cnt++;
						break;
					case 7:
						if(SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_7_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_0_r_0_t_7[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_7[SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_7_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_7_cnt++;
						break;
					case 8:
						if(SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_8_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_0_r_0_t_8[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_8[SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_8_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_8_cnt++;
						break;
					case 9:
						if(SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_9_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_0_r_0_t_9[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_9[SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_9_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_0_r_0_t_9_cnt++;
						break;
				}
			}
			break;
	}
}

VOID SCCPMessageBroker::pushToQueue_i_0_r_1(int smid, int idx){

	int chunks = sctpChunkMap->size();

	switch(smid)
	{
		case 0:
			{


				switch(idx)
				{
					case 0:
						if(SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_0_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_0_r_1_t_0[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_0[SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_0_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_0_cnt++;
						break;
					case 1:
						if(SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_1_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_0_r_1_t_1[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_1[SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_1_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_1_cnt++;
						break;
					case 2:
						if(SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_2_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_0_r_1_t_2[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_2[SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_2_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_2_cnt++;
						break;
					case 3:
						if(SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_3_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_0_r_1_t_3[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_3[SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_3_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_3_cnt++;
						break;
					case 4:
						if(SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_4_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_0_r_1_t_4[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_4[SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_4_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_4_cnt++;
						break;
					case 5:
						if(SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_5_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_0_r_1_t_5[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_5[SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_5_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_5_cnt++;
						break;
					case 6:
						if(SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_6_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_0_r_1_t_6[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_6[SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_6_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_6_cnt++;
						break;
					case 7:
						if(SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_7_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_0_r_1_t_7[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_7[SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_7_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_7_cnt++;
						break;
					case 8:
						if(SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_8_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_0_r_1_t_8[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_8[SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_8_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_8_cnt++;
						break;
					case 9:
						if(SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_9_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_0_r_1_t_9[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_9[SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_9_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_0_r_1_t_9_cnt++;
						break;
				}
			}
			break;
	}
}


VOID SCCPMessageBroker::pushToQueue_i_1_r_0(int smid, int idx){

	int chunks = sctpChunkMap->size();

	switch(smid)
	{
		case 0:
			{


				switch(idx)
				{
					case 0:
						if(SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_0_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_1_r_0_t_0[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_0[SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_0_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_0_cnt++;
						break;
					case 1:
						if(SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_1_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_1_r_0_t_1[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_1[SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_1_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_1_cnt++;
						break;
					case 2:
						if(SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_2_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_1_r_0_t_2[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_2[SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_2_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_2_cnt++;
						break;
					case 3:
						if(SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_3_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_1_r_0_t_3[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_3[SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_3_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_3_cnt++;
						break;
					case 4:
						if(SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_4_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_1_r_0_t_4[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_4[SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_4_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_4_cnt++;
						break;
					case 5:
						if(SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_5_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_1_r_0_t_5[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_5[SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_5_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_5_cnt++;
						break;
					case 6:
						if(SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_6_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_1_r_0_t_6[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_6[SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_6_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_6_cnt++;
						break;
					case 7:
						if(SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_7_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_1_r_0_t_7[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_7[SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_7_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_7_cnt++;
						break;
					case 8:
						if(SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_8_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_1_r_0_t_8[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_8[SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_8_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_8_cnt++;
						break;
					case 9:
						if(SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_9_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_1_r_0_t_9[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_9[SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_9_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_1_r_0_t_9_cnt++;
						break;
				}
			}
			break;
	}
}


VOID SCCPMessageBroker::pushToQueue_i_1_r_1(int smid, int idx){

	int chunks = sctpChunkMap->size();

	switch(smid)
	{
		case 0:
			{


				switch(idx)
				{
					case 0:
						if(SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_0_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_1_r_1_t_0[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_0[SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_0_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_0_cnt++;
						break;
					case 1:
						if(SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_1_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_1_r_1_t_1[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_1[SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_1_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_1_cnt++;
						break;
					case 2:
						if(SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_2_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_1_r_1_t_2[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_2[SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_2_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_2_cnt++;
						break;
					case 3:
						if(SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_3_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_1_r_1_t_3[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_3[SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_3_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_3_cnt++;
						break;
					case 4:
						if(SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_4_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_1_r_1_t_4[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_4[SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_4_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_4_cnt++;
						break;
					case 5:
						if(SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_5_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_1_r_1_t_5[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_5[SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_5_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_5_cnt++;
						break;
					case 6:
						if(SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_6_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_1_r_1_t_6[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_6[SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_6_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_6_cnt++;
						break;
					case 7:
						if(SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_7_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_1_r_1_t_7[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_7[SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_7_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_7_cnt++;
						break;
					case 8:
						if(SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_8_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_1_r_1_t_8[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_8[SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_8_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_8_cnt++;
						break;
					case 9:
						if(SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_9_busy) break;
						for(int i=0; i<chunks; i++){
							SCCPSMStore::sctpChunkMap_sm_0_i_1_r_1_t_9[msgObj->packetNo][i].copy(&(*sctpChunkMap)[i]);
						}
						SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_9[SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_9_cnt].copy(msgObj);
						SCCPSMStore::sccp_msg_sm_0_i_1_r_1_t_9_cnt++;
						break;
				}
			}
			break;
	}
}
