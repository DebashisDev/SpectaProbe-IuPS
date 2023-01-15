/*
 * GTPMessageBroker.cpp
 *
 *  Created on: Dec 5, 2016
 *      Author: Debashis
 */

#include "GTPMessageBroker.h"
#include <sys/time.h>


GTPMessageBroker::GTPMessageBroker(int intfid, int rId) {

	this->interfaceId = intfid;
	this->routerId = rId;
}

GTPMessageBroker::~GTPMessageBroker() {
}


VOID GTPMessageBroker::assignMessage(MPacket *msgObj)
{

	uint16_t lastDigit = 0;
	int smid = -1;

	switch(msgObj->ipAppProtocol)
	{
			case PACKET_IPPROTO_GTPC:
									smid = 0;
									pushMessageToQueue(smid, msgObj);
									break;

			case PACKET_IPPROTO_GTPU:
									if(msgObj->ipSourceAddr > 0 && msgObj->ipDestAddr > 0)
									{
										if(msgObj->dirUserNetwork)
											lastDigit = msgObj->ipSourceAddr % 100;
										else
											lastDigit = msgObj->ipDestAddr % 100;

										if(lastDigit <= 25) smid = 1;
										else if(lastDigit <= 50) smid = 2;
										else if(lastDigit <= 75) smid = 3;
										else smid = 4;

										pushMessageToQueue(smid, msgObj);
									}
									break;

			default:
									break;
	}
}

//VOID GTPMessageBroker::updateGTPcCounter()
//{
//	switch(interfaceId)
//	{
//		case 0:
//			{
//				switch(routerId)
//				{
//					case 0:
//						GTPStats::gtpc_pkt_cnt_i_0_r_0++;
//						break;
//					case 1:
//						GTPStats::gtpc_pkt_cnt_i_0_r_1++;
//						break;
//					case 2:
//						GTPStats::gtpc_pkt_cnt_i_0_r_2++;
//						break;
//					case 3:
//						GTPStats::gtpc_pkt_cnt_i_0_r_3++;
//						break;
//				}
//			}
//			break;
//
//		case 1:
//			{
//				switch(routerId)
//				{
//					case 0:
//						GTPStats::gtpc_pkt_cnt_i_1_r_0++;
//						break;
//					case 1:
//						GTPStats::gtpc_pkt_cnt_i_1_r_1++;
//						break;
//					case 2:
//						GTPStats::gtpc_pkt_cnt_i_1_r_2++;
//						break;
//					case 3:
//						GTPStats::gtpc_pkt_cnt_i_1_r_3++;
//						break;
//				}
//			}
//			break;
//
//		case 2:
//			{
//				switch(routerId)
//				{
//					case 0:
//						GTPStats::gtpc_pkt_cnt_i_2_r_0++;
//						break;
//					case 1:
//						GTPStats::gtpc_pkt_cnt_i_2_r_1++;
//						break;
//					case 2:
//						GTPStats::gtpc_pkt_cnt_i_2_r_2++;
//						break;
//					case 3:
//						GTPStats::gtpc_pkt_cnt_i_2_r_3++;
//						break;
//				}
//			}
//			break;
//
//		case 3:
//			{
//				switch(routerId)
//				{
//					case 0:
//						GTPStats::gtpc_pkt_cnt_i_3_r_0++;
//						break;
//					case 1:
//						GTPStats::gtpc_pkt_cnt_i_3_r_1++;
//						break;
//					case 2:
//						GTPStats::gtpc_pkt_cnt_i_3_r_2++;
//						break;
//					case 3:
//						GTPStats::gtpc_pkt_cnt_i_3_r_3++;
//						break;
//				}
//			}
//			break;
//	}
//}


//VOID GTPMessageBroker::updateGTPuCounter()
//{
//	switch(interfaceId)
//	{
//		case 0:
//			{
//				switch(routerId)
//				{
//					case 0:
//						GTPStats::gtpu_pkt_cnt_i_0_r_0++;
//						break;
//					case 1:
//						GTPStats::gtpu_pkt_cnt_i_0_r_1++;
//						break;
//					case 2:
//						GTPStats::gtpu_pkt_cnt_i_0_r_2++;
//						break;
//					case 3:
//						GTPStats::gtpu_pkt_cnt_i_0_r_3++;
//						break;
//				}
//			}
//			break;
//
//		case 1:
//			{
//				switch(routerId)
//				{
//					case 0:
//						GTPStats::gtpu_pkt_cnt_i_1_r_0++;
//						break;
//					case 1:
//						GTPStats::gtpu_pkt_cnt_i_1_r_1++;
//						break;
//					case 2:
//						GTPStats::gtpu_pkt_cnt_i_1_r_2++;
//						break;
//					case 3:
//						GTPStats::gtpu_pkt_cnt_i_1_r_3++;
//						break;
//				}
//			}
//			break;
//
//		case 2:
//			{
//				switch(routerId)
//				{
//					case 0:
//						GTPStats::gtpu_pkt_cnt_i_2_r_0++;
//						break;
//					case 1:
//						GTPStats::gtpu_pkt_cnt_i_2_r_1++;
//						break;
//					case 2:
//						GTPStats::gtpu_pkt_cnt_i_2_r_2++;
//						break;
//					case 3:
//						GTPStats::gtpu_pkt_cnt_i_2_r_3++;
//						break;
//				}
//			}
//			break;
//
//		case 3:
//			{
//				switch(routerId)
//				{
//					case 0:
//						GTPStats::gtpu_pkt_cnt_i_3_r_0++;
//						break;
//					case 1:
//						GTPStats::gtpu_pkt_cnt_i_3_r_1++;
//						break;
//					case 2:
//						GTPStats::gtpu_pkt_cnt_i_3_r_2++;
//						break;
//					case 3:
//						GTPStats::gtpu_pkt_cnt_i_3_r_3++;
//						break;
//				}
//			}
//			break;
//	}
//}


VOID GTPMessageBroker::pushMessageToQueue(int smid, MPacket *msgObj)
{
	long epochsec = getCurrentEpochSeconds();

	int idx = 0;

	if(smid == 0)
	{
//		idx = WRITE_TIME_INDEX(epochsec);
//		idx = epochsec % 10;

		//idx = (((epochsec % 100) /10)  % IPGlobal::SESSION_MANAGER_TIMEINDEX) + 1;
		//if(idx >= IPGlobal::SESSION_MANAGER_TIMEINDEX) idx = idx - IPGlobal::SESSION_MANAGER_TIMEINDEX;

//		idx = ((epochsec % 50) / 5) + 1;
//		if(idx >= 10) idx = idx - 10;
		idx = WRITE_TIME_INDEX(epochsec);
	}
	else{
//		idx = (epochsec % 10) + 3;		//+3 sec
//		if(idx > 9) idx = idx - 10;

//		idx = ((epochsec % 100) /10) + 1;		//+30 sec
//		if(idx > 9) idx = idx - 10;

		//idx = (((epochsec % 100) /10)  % IPGlobal::SESSION_MANAGER_TIMEINDEX) + IPGlobal::SESSION_MANAGER_WRITE_INDEX_ADV;
		//if(idx >= IPGlobal::SESSION_MANAGER_TIMEINDEX) idx = idx - IPGlobal::SESSION_MANAGER_TIMEINDEX;

		idx = ((epochsec % 50) / 5) + IPGlobal::SESSION_MANAGER_WRITE_INDEX_ADV;
		if(idx >= 10) idx = idx - 10;
	}

	switch(interfaceId)
	{
		case 0:
			pushMessageToQueue_i_0(smid, idx, msgObj);
			break;
		case 1:
			pushMessageToQueue_i_1(smid, idx, msgObj);
			break;
		case 2:
			pushMessageToQueue_i_2(smid, idx, msgObj);
			break;
		case 3:
			pushMessageToQueue_i_3(smid, idx, msgObj);
			break;
	}
}


VOID GTPMessageBroker::pushMessageToQueue_i_0(int smid, int idx, MPacket *msgObj)
{

	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES == 3){
		if(smid == 2) smid = 1;
		else if(smid == 3) smid = 2;
		else if(smid == 4) smid = 2;
	}


	switch(routerId)
	{
		case 0:
			pushToQueue_i_0_r_0(smid, idx, msgObj);
			break;
		case 1:
			pushToQueue_i_0_r_1(smid, idx, msgObj);
			break;
		case 2:
			pushToQueue_i_0_r_2(smid, idx, msgObj);
			break;
		case 3:
			pushToQueue_i_0_r_3(smid, idx, msgObj);
			break;
	}
}

VOID GTPMessageBroker::pushMessageToQueue_i_1(int smid, int idx, MPacket *msgObj)
{

	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES == 3){
		if(smid == 2) smid = 1;
		else if(smid == 3) smid = 2;
		else if(smid == 4) smid = 2;
	}

	switch(routerId)
	{
		case 0:
			pushToQueue_i_1_r_0(smid, idx, msgObj);
			break;
		case 1:
			pushToQueue_i_1_r_1(smid, idx, msgObj);
			break;
		case 2:
			pushToQueue_i_1_r_2(smid, idx, msgObj);
			break;
		case 3:
			pushToQueue_i_1_r_3(smid, idx, msgObj);
			break;
	}
}

VOID GTPMessageBroker::pushMessageToQueue_i_2(int smid, int idx, MPacket *msgObj)
{

	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES == 3){
		if(smid == 2) smid = 1;
		else if(smid == 3) smid = 2;
		else if(smid == 4) smid = 2;
	}


	switch(routerId)
	{
		case 0:
			pushToQueue_i_2_r_0(smid, idx, msgObj);
			break;
		case 1:
			pushToQueue_i_2_r_1(smid, idx, msgObj);
			break;
		case 2:
			pushToQueue_i_2_r_2(smid, idx, msgObj);
			break;
		case 3:
			pushToQueue_i_2_r_3(smid, idx, msgObj);
			break;
	}
}

VOID GTPMessageBroker::pushMessageToQueue_i_3(int smid, int idx, MPacket *msgObj)
{

	if(IPGlobal::GN_SESSION_MANAGER_INSTANCES == 3){
		if(smid == 2) smid = 1;
		else if(smid == 3) smid = 2;
		else if(smid == 4) smid = 2;
	}


	switch(routerId)
	{
		case 0:
			pushToQueue_i_3_r_0(smid, idx, msgObj);
			break;
		case 1:
			pushToQueue_i_3_r_1(smid, idx, msgObj);
			break;
		case 2:
			pushToQueue_i_3_r_2(smid, idx, msgObj);
			break;
		case 3:
			pushToQueue_i_3_r_3(smid, idx, msgObj);
			break;
	}
}


VOID GTPMessageBroker::pushToQueue_i_0_r_0(int smid, int idx, MPacket *msgObj){

	switch(smid)
	{
		case 0:
			{
				switch(idx)
				{
					case 0:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_0_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_0[GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_0_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_0_cnt++;
						break;
					case 1:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_1_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_1[GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_1_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_1_cnt++;
						break;
					case 2:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_2_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_2[GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_2_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_2_cnt++;
						break;
					case 3:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_3_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_3[GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_3_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_3_cnt++;
						break;
					case 4:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_4_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_4[GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_4_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_4_cnt++;
						break;
					case 5:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_5_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_5[GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_5_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_5_cnt++;
						break;
					case 6:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_6_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_6[GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_6_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_6_cnt++;
						break;
					case 7:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_7_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_7[GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_7_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_7_cnt++;
						break;
					case 8:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_8_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_8[GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_8_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_8_cnt++;
						break;
					case 9:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_9_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_9[GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_9_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_0_t_9_cnt++;
						break;
				}
			}
			break;

		case 1:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_0[GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_1[GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_2[GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_3[GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_4[GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_5[GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_6[GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_7[GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_8[GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_9[GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_0_t_9_cnt++;
					break;
				}
			}
			break;

		case 2:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_0[GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_1[GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_2[GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_3[GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_4[GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_5[GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_6[GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_7[GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_8[GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_9[GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_0_t_9_cnt++;
					break;
				}
			}
			break;

		case 3:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_0[GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_1[GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_2[GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_3[GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_4[GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_5[GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_6[GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_7[GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_8[GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_9[GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_0_t_9_cnt++;
					break;
				}
			}
			break;

		case 4:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_0[GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_1[GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_2[GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_3[GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_4[GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_5[GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_6[GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_7[GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_8[GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_9[GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_0_t_9_cnt++;
					break;
				}
			}
			break;
	}

}

VOID GTPMessageBroker::pushToQueue_i_0_r_1(int smid, int idx, MPacket *msgObj){

	switch(smid)
	{
		case 0:
			{
				switch(idx)
				{
					case 0:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_0_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_0[GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_0_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_0_cnt++;
						break;
					case 1:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_1_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_1[GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_1_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_1_cnt++;
						break;
					case 2:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_2_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_2[GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_2_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_2_cnt++;
						break;
					case 3:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_3_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_3[GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_3_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_3_cnt++;
						break;
					case 4:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_4_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_4[GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_4_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_4_cnt++;
						break;
					case 5:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_5_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_5[GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_5_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_5_cnt++;
						break;
					case 6:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_6_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_6[GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_6_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_6_cnt++;
						break;
					case 7:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_7_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_7[GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_7_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_7_cnt++;
						break;
					case 8:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_8_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_8[GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_8_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_8_cnt++;
						break;
					case 9:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_9_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_9[GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_9_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_1_t_9_cnt++;
						break;
				}
			}
			break;

		case 1:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_0[GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_1[GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_2[GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_3[GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_4[GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_5[GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_6[GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_7[GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_8[GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_9[GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_1_t_9_cnt++;
					break;
				}
			}
			break;

		case 2:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_0[GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_1[GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_2[GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_3[GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_4[GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_5[GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_6[GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_7[GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_8[GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_9[GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_1_t_9_cnt++;
					break;
				}
			}
			break;

		case 3:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_0[GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_1[GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_2[GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_3[GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_4[GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_5[GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_6[GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_7[GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_8[GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_9[GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_1_t_9_cnt++;
					break;
				}
			}
			break;

		case 4:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_0[GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_1[GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_2[GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_3[GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_4[GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_5[GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_6[GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_7[GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_8[GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_9[GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_1_t_9_cnt++;
					break;
				}
			}
			break;
	}

}

VOID GTPMessageBroker::pushToQueue_i_0_r_2(int smid, int idx, MPacket *msgObj){

	switch(smid)
	{
		case 0:
			{
				switch(idx)
				{
					case 0:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_0_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_0[GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_0_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_0_cnt++;
						break;
					case 1:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_1_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_1[GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_1_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_1_cnt++;
						break;
					case 2:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_2_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_2[GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_2_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_2_cnt++;
						break;
					case 3:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_3_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_3[GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_3_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_3_cnt++;
						break;
					case 4:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_4_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_4[GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_4_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_4_cnt++;
						break;
					case 5:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_5_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_5[GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_5_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_5_cnt++;
						break;
					case 6:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_6_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_6[GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_6_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_6_cnt++;
						break;
					case 7:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_7_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_7[GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_7_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_7_cnt++;
						break;
					case 8:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_8_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_8[GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_8_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_8_cnt++;
						break;
					case 9:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_9_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_9[GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_9_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_2_t_9_cnt++;
						break;
				}
			}
			break;

		case 1:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_0[GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_1[GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_2[GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_3[GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_4[GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_5[GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_6[GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_7[GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_8[GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_9[GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_2_t_9_cnt++;
					break;
				}
			}
			break;

		case 2:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_0[GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_1[GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_2[GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_3[GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_4[GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_5[GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_6[GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_7[GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_8[GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_9[GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_2_t_9_cnt++;
					break;
				}
			}
			break;

		case 3:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_0[GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_1[GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_2[GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_3[GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_4[GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_5[GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_6[GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_7[GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_8[GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_9[GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_2_t_9_cnt++;
					break;
				}
			}
			break;

		case 4:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_0[GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_1[GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_2[GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_3[GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_4[GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_5[GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_6[GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_7[GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_8[GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_9[GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_2_t_9_cnt++;
					break;
				}
			}
			break;
	}

}

VOID GTPMessageBroker::pushToQueue_i_0_r_3(int smid, int idx, MPacket *msgObj){

	switch(smid)
	{
		case 0:
			{
				switch(idx)
				{
					case 0:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_0_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_0[GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_0_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_0_cnt++;
						break;
					case 1:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_1_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_1[GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_1_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_1_cnt++;
						break;
					case 2:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_2_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_2[GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_2_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_2_cnt++;
						break;
					case 3:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_3_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_3[GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_3_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_3_cnt++;
						break;
					case 4:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_4_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_4[GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_4_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_4_cnt++;
						break;
					case 5:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_5_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_5[GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_5_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_5_cnt++;
						break;
					case 6:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_6_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_6[GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_6_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_6_cnt++;
						break;
					case 7:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_7_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_7[GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_7_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_7_cnt++;
						break;
					case 8:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_8_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_8[GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_8_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_8_cnt++;
						break;
					case 9:
						if(GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_9_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_9[GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_9_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_0_r_3_t_9_cnt++;
						break;
				}
			}
			break;

		case 1:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_0[GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_1[GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_2[GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_3[GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_4[GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_5[GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_6[GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_7[GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_8[GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_9[GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_0_r_3_t_9_cnt++;
					break;
				}
			}
			break;

		case 2:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_0[GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_1[GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_2[GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_3[GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_4[GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_5[GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_6[GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_7[GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_8[GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_9[GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_0_r_3_t_9_cnt++;
					break;
				}
			}
			break;

		case 3:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_0[GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_1[GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_2[GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_3[GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_4[GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_5[GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_6[GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_7[GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_8[GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_9[GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_0_r_3_t_9_cnt++;
					break;
				}
			}
			break;

		case 4:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_0[GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_1[GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_2[GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_3[GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_4[GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_5[GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_6[GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_7[GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_8[GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_9[GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_0_r_3_t_9_cnt++;
					break;
				}
			}
			break;
	}

}

VOID GTPMessageBroker::pushToQueue_i_1_r_0(int smid, int idx, MPacket *msgObj){

	switch(smid)
	{
		case 0:
			{
				switch(idx)
				{
					case 0:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_0_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_0[GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_0_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_0_cnt++;
						break;
					case 1:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_1_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_1[GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_1_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_1_cnt++;
						break;
					case 2:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_2_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_2[GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_2_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_2_cnt++;
						break;
					case 3:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_3_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_3[GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_3_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_3_cnt++;
						break;
					case 4:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_4_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_4[GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_4_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_4_cnt++;
						break;
					case 5:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_5_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_5[GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_5_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_5_cnt++;
						break;
					case 6:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_6_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_6[GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_6_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_6_cnt++;
						break;
					case 7:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_7_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_7[GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_7_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_7_cnt++;
						break;
					case 8:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_8_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_8[GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_8_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_8_cnt++;
						break;
					case 9:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_9_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_9[GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_9_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_0_t_9_cnt++;
						break;
				}
			}
			break;

		case 1:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_0[GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_1[GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_2[GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_3[GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_4[GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_5[GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_6[GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_7[GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_8[GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_9[GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_0_t_9_cnt++;
					break;
				}
			}
			break;

		case 2:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_0[GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_1[GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_2[GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_3[GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_4[GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_5[GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_6[GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_7[GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_8[GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_9[GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_0_t_9_cnt++;
					break;
				}
			}
			break;

		case 3:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_0[GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_1[GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_2[GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_3[GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_4[GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_5[GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_6[GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_7[GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_8[GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_9[GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_0_t_9_cnt++;
					break;
				}
			}
			break;

		case 4:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_0[GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_1[GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_2[GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_3[GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_4[GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_5[GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_6[GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_7[GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_8[GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_9[GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_0_t_9_cnt++;
					break;
				}
			}
			break;
	}

}

VOID GTPMessageBroker::pushToQueue_i_1_r_1(int smid, int idx, MPacket *msgObj){

	switch(smid)
	{
		case 0:
			{
				switch(idx)
				{
					case 0:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_0_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_0[GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_0_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_0_cnt++;
						break;
					case 1:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_1_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_1[GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_1_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_1_cnt++;
						break;
					case 2:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_2_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_2[GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_2_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_2_cnt++;
						break;
					case 3:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_3_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_3[GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_3_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_3_cnt++;
						break;
					case 4:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_4_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_4[GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_4_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_4_cnt++;
						break;
					case 5:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_5_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_5[GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_5_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_5_cnt++;
						break;
					case 6:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_6_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_6[GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_6_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_6_cnt++;
						break;
					case 7:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_7_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_7[GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_7_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_7_cnt++;
						break;
					case 8:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_8_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_8[GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_8_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_8_cnt++;
						break;
					case 9:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_9_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_9[GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_9_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_1_t_9_cnt++;
						break;
				}
			}
			break;

		case 1:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_0[GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_1[GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_2[GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_3[GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_4[GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_5[GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_6[GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_7[GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_8[GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_9[GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_1_t_9_cnt++;
					break;
				}
			}
			break;

		case 2:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_0[GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_1[GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_2[GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_3[GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_4[GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_5[GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_6[GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_7[GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_8[GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_9[GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_1_t_9_cnt++;
					break;
				}
			}
			break;

		case 3:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_0[GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_1[GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_2[GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_3[GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_4[GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_5[GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_6[GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_7[GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_8[GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_9[GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_1_t_9_cnt++;
					break;
				}
			}
			break;

		case 4:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_0[GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_1[GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_2[GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_3[GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_4[GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_5[GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_6[GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_7[GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_8[GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_9[GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_1_t_9_cnt++;
					break;
				}
			}
			break;
	}

}

VOID GTPMessageBroker::pushToQueue_i_1_r_2(int smid, int idx, MPacket *msgObj){

	switch(smid)
	{
		case 0:
			{
				switch(idx)
				{
					case 0:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_0_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_0[GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_0_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_0_cnt++;
						break;
					case 1:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_1_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_1[GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_1_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_1_cnt++;
						break;
					case 2:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_2_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_2[GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_2_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_2_cnt++;
						break;
					case 3:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_3_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_3[GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_3_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_3_cnt++;
						break;
					case 4:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_4_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_4[GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_4_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_4_cnt++;
						break;
					case 5:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_5_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_5[GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_5_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_5_cnt++;
						break;
					case 6:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_6_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_6[GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_6_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_6_cnt++;
						break;
					case 7:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_7_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_7[GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_7_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_7_cnt++;
						break;
					case 8:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_8_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_8[GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_8_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_8_cnt++;
						break;
					case 9:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_9_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_9[GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_9_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_2_t_9_cnt++;
						break;
				}
			}
			break;

		case 1:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_0[GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_1[GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_2[GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_3[GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_4[GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_5[GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_6[GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_7[GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_8[GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_9[GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_2_t_9_cnt++;
					break;
				}
			}
			break;

		case 2:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_0[GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_1[GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_2[GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_3[GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_4[GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_5[GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_6[GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_7[GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_8[GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_9[GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_2_t_9_cnt++;
					break;
				}
			}
			break;

		case 3:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_0[GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_1[GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_2[GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_3[GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_4[GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_5[GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_6[GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_7[GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_8[GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_9[GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_2_t_9_cnt++;
					break;
				}
			}
			break;

		case 4:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_0[GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_1[GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_2[GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_3[GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_4[GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_5[GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_6[GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_7[GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_8[GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_9[GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_2_t_9_cnt++;
					break;
				}
			}
			break;
	}

}

VOID GTPMessageBroker::pushToQueue_i_1_r_3(int smid, int idx, MPacket *msgObj){

	switch(smid)
	{
		case 0:
			{
				switch(idx)
				{
					case 0:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_0_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_0[GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_0_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_0_cnt++;
						break;
					case 1:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_1_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_1[GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_1_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_1_cnt++;
						break;
					case 2:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_2_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_2[GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_2_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_2_cnt++;
						break;
					case 3:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_3_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_3[GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_3_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_3_cnt++;
						break;
					case 4:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_4_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_4[GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_4_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_4_cnt++;
						break;
					case 5:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_5_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_5[GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_5_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_5_cnt++;
						break;
					case 6:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_6_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_6[GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_6_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_6_cnt++;
						break;
					case 7:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_7_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_7[GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_7_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_7_cnt++;
						break;
					case 8:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_8_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_8[GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_8_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_8_cnt++;
						break;
					case 9:
						if(GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_9_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_9[GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_9_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_1_r_3_t_9_cnt++;
						break;
				}
			}
			break;

		case 1:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_0[GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_1[GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_2[GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_3[GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_4[GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_5[GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_6[GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_7[GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_8[GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_9[GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_1_r_3_t_9_cnt++;
					break;
				}
			}
			break;

		case 2:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_0[GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_1[GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_2[GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_3[GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_4[GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_5[GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_6[GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_7[GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_8[GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_9[GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_1_r_3_t_9_cnt++;
					break;
				}
			}
			break;

		case 3:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_0[GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_1[GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_2[GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_3[GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_4[GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_5[GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_6[GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_7[GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_8[GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_9[GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_1_r_3_t_9_cnt++;
					break;
				}
			}
			break;

		case 4:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_0[GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_1[GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_2[GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_3[GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_4[GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_5[GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_6[GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_7[GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_8[GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_9[GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_1_r_3_t_9_cnt++;
					break;
				}
			}
			break;
	}

}

VOID GTPMessageBroker::pushToQueue_i_2_r_0(int smid, int idx, MPacket *msgObj){

	switch(smid)
	{
		case 0:
			{
				switch(idx)
				{
					case 0:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_0_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_0[GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_0_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_0_cnt++;
						break;
					case 1:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_1_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_1[GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_1_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_1_cnt++;
						break;
					case 2:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_2_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_2[GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_2_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_2_cnt++;
						break;
					case 3:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_3_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_3[GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_3_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_3_cnt++;
						break;
					case 4:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_4_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_4[GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_4_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_4_cnt++;
						break;
					case 5:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_5_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_5[GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_5_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_5_cnt++;
						break;
					case 6:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_6_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_6[GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_6_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_6_cnt++;
						break;
					case 7:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_7_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_7[GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_7_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_7_cnt++;
						break;
					case 8:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_8_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_8[GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_8_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_8_cnt++;
						break;
					case 9:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_9_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_9[GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_9_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_0_t_9_cnt++;
						break;
				}
			}
			break;

		case 1:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_0[GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_1[GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_2[GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_3[GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_4[GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_5[GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_6[GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_7[GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_8[GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_9[GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_0_t_9_cnt++;
					break;
				}
			}
			break;

		case 2:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_0[GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_1[GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_2[GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_3[GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_4[GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_5[GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_6[GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_7[GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_8[GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_9[GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_0_t_9_cnt++;
					break;
				}
			}
			break;

		case 3:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_0[GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_1[GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_2[GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_3[GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_4[GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_5[GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_6[GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_7[GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_8[GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_9[GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_0_t_9_cnt++;
					break;
				}
			}
			break;

		case 4:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_0[GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_1[GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_2[GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_3[GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_4[GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_5[GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_6[GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_7[GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_8[GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_9[GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_0_t_9_cnt++;
					break;
				}
			}
			break;
	}

}

VOID GTPMessageBroker::pushToQueue_i_2_r_1(int smid, int idx, MPacket *msgObj){

	switch(smid)
	{
		case 0:
			{
				switch(idx)
				{
					case 0:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_0_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_0[GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_0_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_0_cnt++;
						break;
					case 1:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_1_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_1[GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_1_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_1_cnt++;
						break;
					case 2:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_2_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_2[GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_2_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_2_cnt++;
						break;
					case 3:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_3_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_3[GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_3_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_3_cnt++;
						break;
					case 4:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_4_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_4[GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_4_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_4_cnt++;
						break;
					case 5:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_5_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_5[GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_5_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_5_cnt++;
						break;
					case 6:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_6_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_6[GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_6_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_6_cnt++;
						break;
					case 7:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_7_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_7[GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_7_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_7_cnt++;
						break;
					case 8:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_8_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_8[GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_8_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_8_cnt++;
						break;
					case 9:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_9_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_9[GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_9_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_1_t_9_cnt++;
						break;
				}
			}
			break;

		case 1:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_0[GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_1[GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_2[GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_3[GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_4[GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_5[GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_6[GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_7[GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_8[GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_9[GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_1_t_9_cnt++;
					break;
				}
			}
			break;

		case 2:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_0[GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_1[GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_2[GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_3[GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_4[GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_5[GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_6[GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_7[GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_8[GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_9[GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_1_t_9_cnt++;
					break;
				}
			}
			break;

		case 3:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_0[GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_1[GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_2[GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_3[GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_4[GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_5[GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_6[GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_7[GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_8[GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_9[GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_1_t_9_cnt++;
					break;
				}
			}
			break;

		case 4:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_0[GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_1[GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_2[GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_3[GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_4[GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_5[GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_6[GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_7[GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_8[GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_9[GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_1_t_9_cnt++;
					break;
				}
			}
			break;
	}

}

VOID GTPMessageBroker::pushToQueue_i_2_r_2(int smid, int idx, MPacket *msgObj){

	switch(smid)
	{
		case 0:
			{
				switch(idx)
				{
					case 0:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_0_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_0[GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_0_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_0_cnt++;
						break;
					case 1:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_1_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_1[GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_1_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_1_cnt++;
						break;
					case 2:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_2_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_2[GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_2_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_2_cnt++;
						break;
					case 3:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_3_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_3[GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_3_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_3_cnt++;
						break;
					case 4:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_4_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_4[GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_4_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_4_cnt++;
						break;
					case 5:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_5_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_5[GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_5_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_5_cnt++;
						break;
					case 6:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_6_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_6[GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_6_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_6_cnt++;
						break;
					case 7:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_7_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_7[GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_7_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_7_cnt++;
						break;
					case 8:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_8_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_8[GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_8_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_8_cnt++;
						break;
					case 9:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_9_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_9[GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_9_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_2_t_9_cnt++;
						break;
				}
			}
			break;

		case 1:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_0[GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_1[GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_2[GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_3[GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_4[GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_5[GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_6[GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_7[GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_8[GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_9[GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_2_t_9_cnt++;
					break;
				}
			}
			break;

		case 2:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_0[GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_1[GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_2[GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_3[GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_4[GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_5[GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_6[GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_7[GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_8[GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_9[GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_2_t_9_cnt++;
					break;
				}
			}
			break;

		case 3:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_0[GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_1[GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_2[GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_3[GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_4[GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_5[GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_6[GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_7[GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_8[GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_9[GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_2_t_9_cnt++;
					break;
				}
			}
			break;

		case 4:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_0[GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_1[GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_2[GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_3[GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_4[GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_5[GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_6[GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_7[GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_8[GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_9[GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_2_t_9_cnt++;
					break;
				}
			}
			break;
	}

}

VOID GTPMessageBroker::pushToQueue_i_2_r_3(int smid, int idx, MPacket *msgObj){

	switch(smid)
	{
		case 0:
			{
				switch(idx)
				{
					case 0:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_0_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_0[GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_0_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_0_cnt++;
						break;
					case 1:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_1_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_1[GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_1_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_1_cnt++;
						break;
					case 2:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_2_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_2[GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_2_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_2_cnt++;
						break;
					case 3:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_3_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_3[GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_3_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_3_cnt++;
						break;
					case 4:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_4_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_4[GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_4_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_4_cnt++;
						break;
					case 5:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_5_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_5[GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_5_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_5_cnt++;
						break;
					case 6:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_6_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_6[GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_6_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_6_cnt++;
						break;
					case 7:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_7_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_7[GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_7_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_7_cnt++;
						break;
					case 8:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_8_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_8[GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_8_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_8_cnt++;
						break;
					case 9:
						if(GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_9_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_9[GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_9_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_2_r_3_t_9_cnt++;
						break;
				}
			}
			break;

		case 1:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_0[GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_1[GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_2[GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_3[GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_4[GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_5[GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_6[GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_7[GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_8[GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_9[GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_2_r_3_t_9_cnt++;
					break;
				}
			}
			break;

		case 2:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_0[GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_1[GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_2[GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_3[GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_4[GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_5[GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_6[GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_7[GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_8[GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_9[GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_2_r_3_t_9_cnt++;
					break;
				}
			}
			break;

		case 3:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_0[GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_1[GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_2[GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_3[GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_4[GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_5[GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_6[GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_7[GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_8[GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_9[GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_2_r_3_t_9_cnt++;
					break;
				}
			}
			break;

		case 4:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_0[GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_1[GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_2[GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_3[GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_4[GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_5[GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_6[GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_7[GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_8[GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_9[GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_2_r_3_t_9_cnt++;
					break;
				}
			}
			break;
	}

}

VOID GTPMessageBroker::pushToQueue_i_3_r_0(int smid, int idx, MPacket *msgObj){

	switch(smid)
	{
		case 0:
			{
				switch(idx)
				{
					case 0:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_0_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_0[GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_0_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_0_cnt++;
						break;
					case 1:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_1_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_1[GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_1_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_1_cnt++;
						break;
					case 2:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_2_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_2[GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_2_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_2_cnt++;
						break;
					case 3:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_3_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_3[GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_3_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_3_cnt++;
						break;
					case 4:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_4_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_4[GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_4_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_4_cnt++;
						break;
					case 5:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_5_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_5[GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_5_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_5_cnt++;
						break;
					case 6:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_6_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_6[GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_6_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_6_cnt++;
						break;
					case 7:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_7_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_7[GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_7_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_7_cnt++;
						break;
					case 8:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_8_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_8[GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_8_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_8_cnt++;
						break;
					case 9:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_9_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_9[GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_9_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_0_t_9_cnt++;
						break;
				}
			}
			break;

		case 1:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_0[GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_1[GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_2[GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_3[GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_4[GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_5[GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_6[GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_7[GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_8[GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_9[GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_0_t_9_cnt++;
					break;
				}
			}
			break;

		case 2:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_0[GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_1[GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_2[GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_3[GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_4[GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_5[GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_6[GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_7[GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_8[GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_9[GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_0_t_9_cnt++;
					break;
				}
			}
			break;

		case 3:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_0[GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_1[GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_2[GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_3[GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_4[GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_5[GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_6[GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_7[GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_8[GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_9[GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_0_t_9_cnt++;
					break;
				}
			}
			break;

		case 4:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_0[GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_1[GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_2[GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_3[GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_4[GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_5[GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_6[GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_7[GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_8[GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_9[GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_0_t_9_cnt++;
					break;
				}
			}
			break;
	}

}

VOID GTPMessageBroker::pushToQueue_i_3_r_1(int smid, int idx, MPacket *msgObj){

	switch(smid)
	{
		case 0:
			{
				switch(idx)
				{
					case 0:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_0_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_0[GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_0_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_0_cnt++;
						break;
					case 1:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_1_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_1[GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_1_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_1_cnt++;
						break;
					case 2:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_2_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_2[GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_2_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_2_cnt++;
						break;
					case 3:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_3_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_3[GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_3_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_3_cnt++;
						break;
					case 4:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_4_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_4[GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_4_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_4_cnt++;
						break;
					case 5:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_5_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_5[GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_5_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_5_cnt++;
						break;
					case 6:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_6_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_6[GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_6_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_6_cnt++;
						break;
					case 7:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_7_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_7[GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_7_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_7_cnt++;
						break;
					case 8:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_8_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_8[GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_8_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_8_cnt++;
						break;
					case 9:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_9_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_9[GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_9_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_1_t_9_cnt++;
						break;
				}
			}
			break;

		case 1:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_0[GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_1[GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_2[GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_3[GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_4[GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_5[GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_6[GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_7[GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_8[GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_9[GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_1_t_9_cnt++;
					break;
				}
			}
			break;

		case 2:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_0[GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_1[GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_2[GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_3[GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_4[GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_5[GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_6[GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_7[GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_8[GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_9[GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_1_t_9_cnt++;
					break;
				}
			}
			break;

		case 3:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_0[GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_1[GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_2[GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_3[GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_4[GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_5[GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_6[GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_7[GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_8[GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_9[GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_1_t_9_cnt++;
					break;
				}
			}
			break;

		case 4:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_0[GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_1[GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_2[GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_3[GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_4[GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_5[GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_6[GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_7[GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_8[GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_9[GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_1_t_9_cnt++;
					break;
				}
			}
			break;
	}

}

VOID GTPMessageBroker::pushToQueue_i_3_r_2(int smid, int idx, MPacket *msgObj){

	switch(smid)
	{
		case 0:
			{
				switch(idx)
				{
					case 0:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_0_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_0[GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_0_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_0_cnt++;
						break;
					case 1:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_1_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_1[GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_1_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_1_cnt++;
						break;
					case 2:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_2_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_2[GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_2_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_2_cnt++;
						break;
					case 3:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_3_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_3[GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_3_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_3_cnt++;
						break;
					case 4:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_4_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_4[GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_4_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_4_cnt++;
						break;
					case 5:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_5_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_5[GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_5_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_5_cnt++;
						break;
					case 6:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_6_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_6[GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_6_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_6_cnt++;
						break;
					case 7:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_7_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_7[GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_7_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_7_cnt++;
						break;
					case 8:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_8_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_8[GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_8_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_8_cnt++;
						break;
					case 9:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_9_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_9[GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_9_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_2_t_9_cnt++;
						break;
				}
			}
			break;

		case 1:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_0[GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_1[GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_2[GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_3[GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_4[GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_5[GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_6[GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_7[GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_8[GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_9[GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_2_t_9_cnt++;
					break;
				}
			}
			break;

		case 2:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_0[GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_1[GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_2[GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_3[GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_4[GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_5[GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_6[GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_7[GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_8[GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_9[GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_2_t_9_cnt++;
					break;
				}
			}
			break;

		case 3:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_0[GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_1[GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_2[GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_3[GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_4[GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_5[GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_6[GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_7[GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_8[GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_9[GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_2_t_9_cnt++;
					break;
				}
			}
			break;

		case 4:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_0[GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_1[GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_2[GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_3[GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_4[GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_5[GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_6[GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_7[GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_8[GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_9[GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_2_t_9_cnt++;
					break;
				}
			}
			break;
	}

}

VOID GTPMessageBroker::pushToQueue_i_3_r_3(int smid, int idx, MPacket *msgObj){

	switch(smid)
	{
		case 0:
			{
				switch(idx)
				{
					case 0:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_0_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_0[GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_0_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_0_cnt++;
						break;
					case 1:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_1_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_1[GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_1_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_1_cnt++;
						break;
					case 2:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_2_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_2[GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_2_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_2_cnt++;
						break;
					case 3:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_3_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_3[GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_3_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_3_cnt++;
						break;
					case 4:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_4_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_4[GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_4_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_4_cnt++;
						break;
					case 5:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_5_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_5[GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_5_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_5_cnt++;
						break;
					case 6:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_6_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_6[GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_6_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_6_cnt++;
						break;
					case 7:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_7_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_7[GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_7_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_7_cnt++;
						break;
					case 8:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_8_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_8[GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_8_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_8_cnt++;
						break;
					case 9:
						if(GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_9_busy) break;
						GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_9[GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_9_cnt].copy(msgObj);
						GTPSMStore::gtp_msg_sm_0_i_3_r_3_t_9_cnt++;
						break;
				}
			}
			break;

		case 1:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_0[GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_1[GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_2[GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_3[GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_4[GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_5[GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_6[GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_7[GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_8[GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_9[GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_1_i_3_r_3_t_9_cnt++;
					break;
				}
			}
			break;

		case 2:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_0[GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_1[GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_2[GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_3[GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_4[GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_5[GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_6[GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_7[GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_8[GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_9[GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_2_i_3_r_3_t_9_cnt++;
					break;
				}
			}
			break;

		case 3:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_0[GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_1[GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_2[GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_3[GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_4[GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_5[GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_6[GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_7[GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_8[GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_9[GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_3_i_3_r_3_t_9_cnt++;
					break;
				}
			}
			break;

		case 4:
			{
				switch(idx)
				{
				case 0:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_0_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_0[GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_0_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_0_cnt++;
					break;
				case 1:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_1_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_1[GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_1_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_1_cnt++;
					break;
				case 2:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_2_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_2[GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_2_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_2_cnt++;
					break;
				case 3:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_3_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_3[GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_3_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_3_cnt++;
					break;
				case 4:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_4_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_4[GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_4_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_4_cnt++;
					break;
				case 5:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_5_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_5[GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_5_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_5_cnt++;
					break;
				case 6:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_6_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_6[GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_6_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_6_cnt++;
					break;
				case 7:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_7_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_7[GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_7_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_7_cnt++;
					break;
				case 8:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_8_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_8[GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_8_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_8_cnt++;
					break;
				case 9:
					if(GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_9_busy) break;
					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_9[GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_9_cnt].copy(msgObj);
					GTPSMStore::gtp_msg_sm_4_i_3_r_3_t_9_cnt++;
					break;
				}
			}
			break;
	}

}


