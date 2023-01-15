/*
 * GTPSessionManagerV2.cpp
 *
 *  Created on: Oct 30, 2016
 *      Author: Debashis
 */

#include "GTPSessionManagerV2.h"

GTPSessionManagerV2::GTPSessionManagerV2() {
	_thisLogLevel = 0;
	this->_name = "GTPSessionManagerV2";
	this->setLogLevel(Log::theLog().level());
}

GTPSessionManagerV2::~GTPSessionManagerV2() {

}

VOID GTPSessionManagerV2::updateGtpV2Session(TPacket *msgObj, int selfId)
{
	int cSession, dSession, cBearer, uBearer, mBearer = 0;
#if 0
//	SessionStore::getProcedureV2MapSize(&cSession, &dSession, &cBearer, &uBearer, &mBearer, selfId);
//	printf("cSession[%d] dSession[%d] cBearer[%d] uBearer[%d] mBearer[%d]\n", cSession, dSession, cBearer, uBearer, mBearer);

	switch(msgObj->gtpV2Data->msgType)
	{
		case GTPV2_CREATE_SESSION_REQUEST:   // From MME --> SGW
									createSessionReq(msgObj, selfId);
									break;

		case GTPV2_CREATE_SESSION_RESPONSE:  // SGW --> MME
									createSessionRsp(msgObj, selfId);
									break;

		case GTPV2_DELETE_SESSION_REQUEST: // From MME --> SGW
									deleteSessionReq(msgObj, selfId);
									break;

		case GTPV2_DELETE_SESSION_RESPONSE: // SGW --> MME
									deleteSessionRsp(msgObj, selfId);
									break;

		case GTPV2_MODIFY_BEARER_REQUEST:
									modifyBearerReq(msgObj, selfId);
									break;

		case GTPV2_MODIFY_BEARER_RESPONSE:
									modifyBearerRsp(msgObj, selfId);
									break;

		case GTPV2_UPDATE_BEARER_REQUEST:
									updateBearerReq(msgObj, selfId);
									break;

		case GTPV2_UPDATE_BEARER_RESPONSE:
									updateBearerRsp(msgObj, selfId);
									break;
		default:
									break;
	}
#endif
}

/*
 * ---------- CREATE SESSION MESSAGES -----------------
 */

VOID GTPSessionManagerV2::createSessionReq(TPacket *msgObj, int selfId)
{
	ULONG	key = 0;
#if 0
	sh_controlpacketV2 pktstruct = sh_controlpacketV2(new controlpacketV2);
	initializeV2(pktstruct);

	if(msgObj->gtpV2Data->sequence_no != 0)
	{
		key = msgObj->gtpV2Data->sequence_no;
	}
	else
	{
		if(msgObj->gtpV2Data->MME_tunnelId == 0)
					return;
		else
			key = msgObj->gtpV2Data->MME_tunnelId;
	}

	pdp_packetV2_map& create_session = SessionStore::session_create_map[selfId];

	if (create_session.find(key) != create_session.end())
	{
		create_session.erase(create_session.find(key));
		createV2Procedure(pktstruct, msgObj);
		create_session.insert(std::pair<ULONG, sh_controlpacketV2>(key, pktstruct));
	}
	else
	{
		createV2Procedure(pktstruct, msgObj);
		SessionStore::session_create_map[selfId].insert(std::pair<ULONG, sh_controlpacketV2>(key, pktstruct));
	}
#endif
}

VOID GTPSessionManagerV2::createSessionRsp(TPacket *msgObj, int selfId)
{
	ULONG	key = 0;

#if 0
	if(msgObj->gtpV2Data->sequence_no != 0)
	{
		key = msgObj->gtpV2Data->sequence_no;
	}
	else
	{
		if(msgObj->gtpV2Data->pkt_tunnel_id == 0)
					return;
		else
			key = msgObj->gtpV2Data->pkt_tunnel_id;
	}

	pdp_packetV2_map::iterator itr = SessionStore::session_create_map[selfId].find(key);

	if (itr != SessionStore::session_create_map[selfId].end())
	{
		updateV2Procedure(itr->second, msgObj);
//		display(itr->second);

		GTPV2Session *gtpV2Session = new GTPV2Session();
		SessionStore::copyGtpV2Data(itr->second, gtpV2Session);
		SessionStore::updateGTPV2GlobalSession(gtpV2Session);

		/* Update Global Map and Flush Create Session */
		SessionStore::flushGTPV2Session(msgObj->frameData->frameSecond, gtpV2Session, true, selfId);

		SessionStore::session_create_map[selfId].erase(itr);
	}
#endif
}

/*
 * ---------- DELETE SESSION MESSAGES -----------------
 */

VOID GTPSessionManagerV2::deleteSessionReq(TPacket *msgObj, int selfId)
{
	ULONG key = 0;
#if 0
	sh_controlpacketV2 pktstruct = sh_controlpacketV2(new controlpacketV2);
	initializeV2(pktstruct);

	if(msgObj->gtpV2Data->sequence_no != 0)
	{
		key = msgObj->gtpV2Data->sequence_no;
	}
	else
	{
		if(msgObj->gtpV2Data->pkt_tunnel_id == 0)
			return;
	}

	pdp_packetV2_map& delete_session = SessionStore::session_delete_map[selfId];

	if (delete_session.find(key) != delete_session.end())
	{
		delete_session.erase(delete_session.find(key));
		createV2Procedure(pktstruct, msgObj);
		delete_session.insert(std::pair<ULONG, sh_controlpacketV2>(key, pktstruct));
	}
	else
	{
		createV2Procedure(pktstruct, msgObj);
		SessionStore::session_delete_map[selfId].insert(std::pair<ULONG, sh_controlpacketV2>(key, pktstruct));
	}
#endif
}

VOID GTPSessionManagerV2::deleteSessionRsp(TPacket *msgObj, int selfId)
{
	ULONG key = 0;
#if 0
	if(msgObj->gtpV2Data->sequence_no != 0)
	{
		key = msgObj->gtpV2Data->sequence_no;
	}
	else
	{
		if(msgObj->gtpV2Data->pkt_tunnel_id == 0)
			return;
	}

	pdp_packetV2_map::iterator itr = SessionStore::session_delete_map[selfId].find(key);

	if (itr != SessionStore::session_delete_map[selfId].end())
	{
		updateV2Procedure(itr->second, msgObj);

		GTPV2Session *gtpV2Session = new GTPV2Session();
		SessionStore::copyGtpV2Data(itr->second, gtpV2Session);
//		display(itr->second);

		SessionStore::session_delete_map[selfId].erase(itr);

		if(msgObj->gtpV2Data->cause_val == 16) // Request Accepted
			SessionStore::removeGTPV2GlobalSession(msgObj->gtpV2Data->pkt_tunnel_id, CTL_DW);
	}
#endif
}

/*
 * ---------- MODIFY BEARER MESSAGES -----------------
 */
VOID GTPSessionManagerV2::modifyBearerReq(TPacket *msgObj, int selfId)
{
	ULONG key = 0;
#if 0
	sh_controlpacketV2 pktstruct = sh_controlpacketV2(new controlpacketV2);
	initializeV2(pktstruct);

	if(msgObj->gtpV2Data->sequence_no != 0)
	{
		key = msgObj->gtpV2Data->sequence_no;
	}
	else
	{
		if(msgObj->gtpV2Data->pkt_tunnel_id == 0)
			return;
	}

	pdp_packetV2_map& modify_bearer = SessionStore::bearer_modify_map[selfId];

	if (modify_bearer.find(key) != modify_bearer.end())
	{
		modify_bearer.erase(modify_bearer.find(key));
		createV2Procedure(pktstruct, msgObj);
		modify_bearer.insert(std::pair<ULONG, sh_controlpacketV2>(key, pktstruct));
	}
	else
	{
		createV2Procedure(pktstruct, msgObj);
		SessionStore::bearer_modify_map[selfId].insert(std::pair<ULONG, sh_controlpacketV2>(key, pktstruct));
	}
#endif
}

VOID GTPSessionManagerV2::modifyBearerRsp(TPacket *msgObj, int selfId)
{
	ULONG key = 0;
#if 0
	if(msgObj->gtpV2Data->sequence_no != 0)
	{
		key = msgObj->gtpV2Data->sequence_no;
	}
	else
	{
		if(msgObj->gtpV2Data->pkt_tunnel_id == 0)
			return;
	}

	pdp_packetV2_map::iterator itr = SessionStore::bearer_modify_map[selfId].find(key);

	if (itr != SessionStore::bearer_modify_map[selfId].end())
	{
		updateV2Procedure(itr->second, msgObj);

		GTPV2Session *gtpV2Session = new GTPV2Session();
		SessionStore::copyGtpV2Data(itr->second, gtpV2Session);
//		display(itr->second);

		/* Loopup Session Data and Copy */
		GTPV2Session *sessionData = lookupGTPV2GlobalSession(gtpV2Session->pkt_tunnel_id, CTL_DW);

		if(sessionData != NULL)
		{ sessionDataCopy(gtpV2Session, sessionData); }

		SessionStore::bearer_modify_map[selfId].erase(itr);

		/* Update Global Map and Flush Create Session */
		SessionStore::flushGTPV2Session(msgObj->frameData->frameMinute, gtpV2Session, true, selfId);

	}
#endif
}

/*
 * ---------- UPDATE BEARER MESSAGES -----------------
 */
VOID GTPSessionManagerV2::updateBearerReq(TPacket *msgObj, int selfId)
{
	ULONG key = 0;
#if 0
	sh_controlpacketV2 pktstruct = sh_controlpacketV2(new controlpacketV2);
	initializeV2(pktstruct);

	if(msgObj->gtpV2Data->sequence_no != 0)
	{
		key = msgObj->gtpV2Data->sequence_no;
	}
	else
	{
		if(msgObj->gtpV2Data->pkt_tunnel_id == 0)
			return;
	}

	pdp_packetV2_map& update_bearer = SessionStore::bearer_update_map[selfId];

	if (update_bearer.find(key) != update_bearer.end())
	{
		update_bearer.erase(update_bearer.find(key));
		createV2Procedure(pktstruct, msgObj);
		update_bearer.insert(std::pair<ULONG, sh_controlpacketV2>(key, pktstruct));
	}
	else
	{
		createV2Procedure(pktstruct, msgObj);
		SessionStore::bearer_update_map[selfId].insert(std::pair<ULONG, sh_controlpacketV2>(key, pktstruct));
	}
#endif
}

VOID GTPSessionManagerV2::updateBearerRsp(TPacket *msgObj, int selfId)
{
	ULONG key = 0;
#if 0
	if(msgObj->gtpV2Data->sequence_no != 0)
	{
		key = msgObj->gtpV2Data->sequence_no;
	}
	else
	{
		if(msgObj->gtpV2Data->pkt_tunnel_id == 0)
			return;
	}

	pdp_packetV2_map::iterator itr = SessionStore::bearer_update_map[selfId].find(key);

	if (itr != SessionStore::bearer_update_map[selfId].end())
	{
		updateV2Procedure(itr->second, msgObj);

		GTPV2Session *gtpV2Session = new GTPV2Session();
		SessionStore::copyGtpV2Data(itr->second, gtpV2Session);
//		display(itr->second);

		/* Loopup Session Data and Copy */
		GTPV2Session *sessionData = lookupGTPV2GlobalSession(gtpV2Session->pkt_tunnel_id, CTL_DW);

		if(sessionData != NULL)
		{ sessionDataCopy(gtpV2Session, sessionData); }

		SessionStore::bearer_update_map[selfId].erase(itr);

		/* Update Global Map and Flush Create Session */
		SessionStore::flushGTPV2Session(msgObj->frameData->frameSecond, gtpV2Session, true, selfId);
	}
#endif
}

VOID GTPSessionManagerV2::sessionDataCopy(GTPV2Session *gtpV2Session, GTPV2Session *sessionData)
{
	gtpV2Session->msisdn			= sessionData->msisdn;
	gtpV2Session->imsi 				= sessionData->imsi;
	gtpV2Session->imei 				= sessionData->imei;
	gtpV2Session->rat_type 			= sessionData->rat_type;
	gtpV2Session->apn_info 			= sessionData->apn_info;
	gtpV2Session->rat_type 			= sessionData->rat_type;
	gtpV2Session->ppa_addr_location = sessionData->ppa_addr_location;
	gtpV2Session->selection_mode 	= sessionData->selection_mode;
	gtpV2Session->serving_network 	= sessionData->serving_network;
	gtpV2Session->user_location 	= sessionData->user_location;
}

VOID GTPSessionManagerV2::updateV2Procedure(sh_controlpacketV2 pktstruct, TPacket *msgObj)
{
//	pktstruct->GTPRspMsgId		 = msgObj->gtpV2Data->msgType;
//	pktstruct->GTPRspMsgDesc	 = msgObj->gtpV2Data->msg_desc;
//	pktstruct->rspPacketNo 		 = msgObj->frameData->frameCount;
//	pktstruct->pkt_tunnel_id 	 = msgObj->gtpV2Data->pkt_tunnel_id;
//	pktstruct->cause_val 		 = msgObj->gtpV2Data->cause_val;
//	pktstruct->cause_desc 		 = msgObj->gtpV2Data->cause_desc;
//	pktstruct->PGW_interfaceType = msgObj->gtpV2Data->PGW_interfaceType;
//	pktstruct->PGW_tunnelId 	 = msgObj->gtpV2Data->PGW_tunnelId;
//	pktstruct->PGW_ip 			 = msgObj->gtpV2Data->PGW_ip;
//
//	pktstruct->SGW_interfaceType = msgObj->gtpV2Data->SGW_interfaceType;
//	pktstruct->SGW_tunnelId 	 = msgObj->gtpV2Data->SGW_tunnelId;
//	pktstruct->SGW_ip			 = msgObj->gtpV2Data->SGW_ip;
//
//	pktstruct->EndTime 			 = msgObj->gtpV2Data->timeStamp;
//	pktstruct->EndTimeEpochMicroSec = msgObj->frameData->epochTimeMicroSec;
//
//	pktstruct->ByteSizeDL = msgObj->gtpV2Data->ByteSizeDL;
}

VOID GTPSessionManagerV2::createV2Procedure(sh_controlpacketV2 pktstruct, TPacket *msgObj)
{
//	pktstruct->SessionId = generateKey(msgObj);
//	pktstruct->direction = msgObj->gtpV2Data->direction;
//	pktstruct->sequence_no = msgObj->gtpV2Data->sequence_no;
//	pktstruct->GTPReqMsgId	= msgObj->gtpV2Data->msgType;
//	pktstruct->GTPReqMsgDesc	= msgObj->gtpV2Data->msg_desc;
//	pktstruct->interfaceName = msgObj->frameData->interfaceName;
//	pktstruct->sourceAddr = msgObj->ipData->sourceAddr;
//	pktstruct->s_port = msgObj->gtpV1Data->s_port;
//	pktstruct->destAddr =msgObj->ipData->destAddr;
//	pktstruct->d_port = msgObj->gtpV1Data->d_port;
//	pktstruct->s_addr_mac = msgObj->ethernetData->sourceMacAddr;
//	pktstruct->d_addr_mac = msgObj->ethernetData->destMacAddr;
//	pktstruct->StartTime = msgObj->gtpV2Data->timeStamp;
//	pktstruct->StartTimeEpochMicroSec = msgObj->frameData->epochTimeMicroSec;
//
//	pktstruct->reqPacketNo = msgObj->frameData->frameCount;
//	pktstruct->msisdn = msgObj->gtpV2Data->msisdn;
//	pktstruct->imsi = msgObj->gtpV2Data->imsi_no;
//	pktstruct->imei = msgObj->gtpV2Data->mei_info;
//	pktstruct->apn_info = msgObj->gtpV2Data->apn_info.erase(0,1);
//	pktstruct->user_location = msgObj->gtpV2Data->user_location;
//	pktstruct->rat_type = msgObj->gtpV2Data->rat_type;
//	pktstruct->serving_network = msgObj->gtpV2Data->serving_network;
//	pktstruct->ppa_addr_location = msgObj->gtpV2Data->ppa_addr_location;
//	pktstruct->selection_mode = msgObj->gtpV2Data->selection_mode;
//	pktstruct->MME_interfaceType = msgObj->gtpV2Data->MME_interfaceType;
//	pktstruct->MME_tunnelId = msgObj->gtpV2Data->MME_tunnelId;
//	pktstruct->MME_ip = msgObj->gtpV2Data->MME_ip;
//
//	pktstruct->PGW_interfaceType = msgObj->gtpV2Data->PGW_interfaceType;
//	pktstruct->PGW_tunnelId = msgObj->gtpV2Data->PGW_tunnelId;
//	pktstruct->PGW_ip = msgObj->gtpV2Data->PGW_ip;
//
//	pktstruct->SGW_interfaceType = msgObj->gtpV2Data->SGW_interfaceType;
//	pktstruct->SGW_tunnelId = msgObj->gtpV2Data->SGW_tunnelId;
//	pktstruct->SGW_ip = msgObj->gtpV2Data->SGW_ip;
//
//	pktstruct->ByteSizeUL = msgObj->gtpV2Data->ByteSizeUL;

}

VOID GTPSessionManagerV2::display(sh_controlpacketV2 pktstruct)
{
			printf("\n");
//			printf("Request Packet      : %ld\n", pktstruct->reqPacketNo);
//			printf("Response Packet     : %ld\n", pktstruct->rspPacketNo);
//			printf("Packet Hdr          : %ld\n", pktstruct->pkt_tunnel_id);
//			printf("MSISDN              : %s\n",  pktstruct->msisdn.c_str());
//			printf("IMSI                : %s\n",  pktstruct->imsi.c_str());
//			printf("IMEI                : %s\n",  pktstruct->imei.c_str());
//			printf("APN                 : %s\n",  pktstruct->apn_info.c_str());
//			printf("USER LOCATON        : %s\n",  pktstruct->user_location.c_str());
//			printf("RAT                 : %s\n",  pktstruct->rat_type.c_str());
//			printf("SERVING NETWORK     : %s\n",  pktstruct->serving_network.c_str());
//			printf("Cause Code          : %d\n",  pktstruct->cause_val);
//
//			printf("MME_interfaceType   : %d\n",  pktstruct->MME_interfaceType);
//			printf("MME_tunnelId        : %lu\n", pktstruct->MME_tunnelId);
//			printf("MME_ip              : %s\n",  pktstruct->MME_ip.c_str());
//
//			printf("PGW_interfaceType   : %d\n",  pktstruct->PGW_interfaceType);
//			printf("PGW_tunnelId        : %lu\n", pktstruct->PGW_tunnelId);
//			printf("PGW_ip              : %s\n",  pktstruct->PGW_ip.c_str());
//
//			printf("SGW_interfaceType   : %d\n",  pktstruct->SGW_interfaceType);
//			printf("SGW_tunnelId        : %lu\n", pktstruct->SGW_tunnelId);
//			printf("SGW_ip              : %s\n",  pktstruct->SGW_ip.c_str());
}

VOID GTPSessionManagerV2::initializeV2(sh_controlpacketV2 pktstruct)
{
//	pktstruct->StartTimeEpochMicroSec = 0;
//	pktstruct->EndTimeEpochMicroSec = 0;
//	pktstruct->VLANId = 0;
//	pktstruct->s_port = 0;
//	pktstruct->d_port = 0;
//	pktstruct->GTPReqMsgId = 0;
//	pktstruct->GTPRspMsgId = 0;
//	pktstruct->GTPReqMsgDesc.assign("NA");
//	pktstruct->GTPRspMsgDesc.assign("NA");
//	pktstruct->EndCauseId = 0;
//	pktstruct->ByteSizeUL = 0;
//	pktstruct->ByteSizeDL = 0;
//
//	pktstruct->reqPacketNo = 0;
//	pktstruct->rspPacketNo = 0;
//
//	pktstruct->interfaceName.assign("NA");
//	pktstruct->SessionId.assign("NA");
//	pktstruct->StartTime.assign("NA");
//	pktstruct->EndTime.assign("NA");
//	pktstruct->s_addr_mac.assign("NA");
//	pktstruct->d_addr_mac.assign("NA");
//	pktstruct->sourceAddr.assign("NA");
//	pktstruct->destAddr.assign("NA");
//
//	pktstruct->msgType = 0;
//	pktstruct->m_flags = 0;
//	pktstruct->sequence_no = 0;
//	pktstruct->pkt_tunnel_id = 0;
//
//	pktstruct->rec_tunnel_id = 0;
//	pktstruct->trans_tunnel_id = 0;
//	pktstruct->bearer_recv_t_id = 0;
//	pktstruct->bearer_trans_t_id = 0;
//
//	pktstruct->routing_area_info.assign("NA");
//	pktstruct->imsi.assign("NA");
//	pktstruct->apn_info.assign("NA");
//	pktstruct->msisdn.assign("NA");
//	pktstruct->imei.assign("NA");
//	pktstruct->serving_network.assign("NA");
//	pktstruct->user_location.assign("NA");
//	pktstruct->ppa_addr_location.assign("NA");
//	pktstruct->ipv4_address.assign("NA");
//	pktstruct->ipv6_address.assign("NA");
//
//	pktstruct->ipv4_add_recv.assign("NA");
//	pktstruct->ipv4_add_trans.assign("NA");
//	pktstruct->ipv6_add_recv.assign("NA");
//	pktstruct->ipv6_add_trans.assign("NA");
//
//	pktstruct->STN_SR.assign("NA");
//	pktstruct->end_user_address.assign("NA");
//	pktstruct->gsn.assign("NA");
////	pktstruct->gsn_ipv6.assign("NA");
//	pktstruct->selection_mode.assign("NA");
//	pktstruct->ppa_addr_location.assign("NA");
//	pktstruct->TAD_info.assign("NA");
//	pktstruct->tmsi_info.assign("NA");
//	pktstruct->global_cnid_str.assign("NA");
//	pktstruct->trace_mnc_mcc.assign("NA");
//	pktstruct->pdn_type.assign("NA");
//	pktstruct->p_tmsi_sig.assign("NA");
//	pktstruct->trace_id.assign("NA");
//	pktstruct->guti_mnc_mcc.assign("NA");
//	pktstruct->plmn_id.assign("NA");
//	pktstruct->rat_type.assign("NA");
//	pktstruct->ldn_value.assign("NA");
//	pktstruct->relay_type.assign("NA");
//	pktstruct->relay_name.assign("NA");
//	pktstruct->twan_ssid.assign("NA");
//	pktstruct->twan_bssid.assign("NA");
//	pktstruct->twan_name.assign("NA");
//	pktstruct->twan_cai.assign("NA");
//
//	pktstruct->cause_val = 0;
//	pktstruct->cause_desc.assign("NA");
//	pktstruct->MME_interfaceType = 0;
//	pktstruct->MME_tunnelId = 0;
//	pktstruct->MME_ip.assign("NA");
//
//	pktstruct->PGW_interfaceType = 0;
//	pktstruct->PGW_tunnelId = 0;
//	pktstruct->PGW_ip.assign("NA");
//
//	pktstruct->SGW_interfaceType = 0;
//	pktstruct->SGW_tunnelId = 0;
//	pktstruct->SGW_ip.assign("NA");
//
//	pktstruct->counter_val = 0;
//	pktstruct->ulink_bit_rate = 0;
//	pktstruct->dlink_bit_rate = 0;
//	pktstruct->cn_id = 0;
//	pktstruct->charging_id = 0;
//	pktstruct->procedure_transt_id = 0;
//	pktstruct->p_tmsi = 0;
//	pktstruct->day_light_saving_time = 0;
//	pktstruct->time_zone = 0;
//	pktstruct->user_grp_id = 0;
//	pktstruct->mme_code = 0;
//	pktstruct->dl_gtpu_seq_no = 0;
//	pktstruct->ul_gtpu_seq_no = 0;
//	pktstruct->dl_pdcp_seq_no = 0;
//	pktstruct->ul_pdcp_seq_no = 0;
//	pktstruct->nsapi_val = 0;
//	pktstruct->port_no = 0;
//	pktstruct->twan_plmni_id = 0;
//
//	pktstruct->bearer_recv = false;
//	pktstruct->bearer_trans = false;
}

string GTPSessionManagerV2::generateKey(TPacket *msgObj)
{
	string key;

	if(msgObj->gtpV2Data->sequence_no != 0)
	{
		key.assign(std::to_string(msgObj->gtpV2Data->sequence_no))
		   .append("-")
		   .append(std::to_string(msgObj->gtpV2Data->msgType));
	}
	else
	{
		key.assign(std::to_string(msgObj->gtpV2Data->MME_tunnelId))
		   .append("-")
		   .append(std::to_string(msgObj->gtpV1Data->msgType));
	}

	return key;
}

VOID GTPSessionManagerV2::buildCSVData(GTPV2Session *pGtpSession, string& csvBuffer)
{
	csvBuffer.clear();

	if(pGtpSession->SessionId.length() == 0) {
		csvBuffer.assign("NULL");
		return;
	}

//	csvBuffer.assign(to_string(IPGlobal::probeId))
//			 .append(",")
//			 .append("2123,")				// GTP ID
//			 .append("GTPc-v2,")			// Protocol Description
//			 .append(pGtpSession->interfaceName)
//			 .append(",")
//			 .append(pGtpSession->SessionId)
//			 .append(",")
//			 .append("GTPC,")
//			 .append(pGtpSession->StartTime)
//			 .append(",")
//			 .append(to_string(pGtpSession->StartTimeEpochMicroSec))
//			 .append(",")
//			 .append(pGtpSession->EndTime)
//			 .append(",")
//			 .append(to_string(pGtpSession->EndTimeEpochMicroSec))
//			 .append(",")
//			 .append(MSG_DIRECTION_V2[pGtpSession->direction].c_str())
//			 .append(",")
//			 .append(pGtpSession->s_addr_mac)
//			 .append(",")
//			 .append(pGtpSession->d_addr_mac)
//			 .append(",")
//			 .append(pGtpSession->sourceAddr)
//			 .append(",")
//			 .append(pGtpSession->destAddr)
//			 .append(",")
//			 .append(std::to_string(pGtpSession->s_port))
//			 .append(",")
//			 .append(std::to_string(pGtpSession->d_port))
//			 .append(",")
//			 .append(pGtpSession->imsi)
//			 .append(",")
//			 .append(pGtpSession->imei)
//			 .append(",")
//			 .append(pGtpSession->msisdn)
//			 .append(",")
//			 .append(std::to_string(pGtpSession->GTPReqMsgId))
//			 .append(",")
//			 .append(pGtpSession->GTPReqMsgDesc)
//			 .append(",")
//			 .append(pGtpSession->rat_type)
//			 .append(",")
//			 .append(pGtpSession->user_location)
//			 .append(",")
//			 .append(pGtpSession->apn_info)
//			 .append(",")
//			 .append(std::to_string(pGtpSession->GTPRspMsgId))
//			 .append(",")
//			 .append(pGtpSession->GTPRspMsgDesc)
//			 .append(",")
//			 .append(std::to_string(pGtpSession->cause_val))
//			 .append(",")
//			 .append(pGtpSession->cause_desc)
//			 .append(",")
//			 .append(std::to_string(pGtpSession->ByteSizeUL))
//			 .append(",")
//			 .append(std::to_string(pGtpSession->ByteSizeDL));
}

VOID GTPSessionManagerV2::buildTDRData(GTPV2Session *pGtpSession, string& tdrdata)
{
	char *buffer;
	buffer = (char *)malloc(300);

	buffer[0] = 0;
	tdrdata.clear();

//	char prefix[4] = "_p_";
//	sprintf(buffer, "-- GTPv2 TDR -------------------------------------\n");
//	tdrdata.assign(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sProbe_Id			: %d\n", prefix, IPGlobal::probeId);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sProtocol_Id			: 2123\n", prefix);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sProtocol_Desc		: GTPc\n", prefix);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sInterface			: %s\n", prefix, pGtpSession->interfaceName.c_str());
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sSession_Id			: %s\n", prefix, pGtpSession->SessionId.c_str());
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sStart_Time			: %s\n", prefix, pGtpSession->StartTime.c_str());
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sStart_Time_MS		: %lu\n", prefix, pGtpSession->StartTimeEpochMicroSec);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sEnd_Time			: %s\n", prefix, pGtpSession->EndTime.c_str());
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sEnd_Time_MS	 		: %lu\n", prefix,  pGtpSession->EndTimeEpochMicroSec);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	%sInitiation_Dir		: %s\n", prefix,  MSG_DIRECTION_V2[pGtpSession->direction].c_str());
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sSource_Mac_Addr		: %s\n", prefix, pGtpSession->s_addr_mac.c_str());
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sDestination_Mac_Addr		: %s\n", prefix, pGtpSession->d_addr_mac.c_str());
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sSource_IP_Addr		: %s\n", prefix, pGtpSession->sourceAddr.c_str());
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sDestination_IP_Addr		: %s\n", prefix, pGtpSession->destAddr.c_str());
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sOPC				: %d\n", prefix, pGtpSession->s_port);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sDPC				: %d\n", prefix, pGtpSession->d_port);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//
//	if(pGtpSession->msisdn.empty() || pGtpSession->msisdn.length() < MSISDN_LENGTH_MIN){
//		sprintf(buffer, "	%sMSISDN			: NA\n", prefix);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}
//	else{
//		sprintf(buffer, "	%sMSISDN			: %s\n", prefix, pGtpSession->msisdn.c_str());
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}
//
//	if(pGtpSession->imsi.empty() || pGtpSession->imsi.length() < IMSI_LENGTH_MIN){
//		sprintf(buffer, "	%sIMSI				: NA\n", prefix);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}
//	else{
//		sprintf(buffer, "	%sIMSI				: %s\n", prefix, pGtpSession->imsi.c_str());
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}
//
//	if(pGtpSession->imei.empty() || pGtpSession->imei.length() < IMEI_LENGTH_MIN){
//		sprintf(buffer, "	%sIMEI				: NA\n", prefix);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}
//	else{
//		sprintf(buffer, "	%sIMEI				: %s\n", prefix, pGtpSession->imei.c_str());
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}
//
//	sprintf(buffer, "	%sPacket #			: %lu\n", prefix, pGtpSession->reqPacketNo);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//
//	if(pGtpSession->GTPReqMsgId == -1){
//		sprintf(buffer, "	%sGTPc_Procedure_Id		:\n", prefix);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//		sprintf(buffer, "	%sGTPc_Procedure_Desc		:\n", prefix);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}
//	else{
//		sprintf(buffer, "	%sGTPc_Procedure_Id		: %d\n", prefix, pGtpSession->GTPReqMsgId);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//		sprintf(buffer, "	%sGTPc_Procedure_Desc		: %s\n", prefix, pGtpSession->GTPReqMsgDesc.c_str());
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}
//
//	sprintf(buffer, "	%sRAT  			: %s\n", prefix, pGtpSession->rat_type.c_str());
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	%sAPN  			: %s\n", prefix, pGtpSession->apn_info.c_str());
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	%sPPA  			: %s\n", prefix, pGtpSession->ppa_addr_location.c_str());
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	%sSelection Mode		: %s\n", prefix, pGtpSession->selection_mode.c_str());
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	%sPDP_Addr_Allocated		: %s\n", prefix, pGtpSession->user_location.c_str());
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	%sServing Network		: %s\n", prefix, pGtpSession->serving_network.c_str());
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	%sPacket #			: %lu\n", prefix, pGtpSession->rspPacketNo);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//
//	if(pGtpSession->GTPRspMsgId == -1){
//		sprintf(buffer, "	%sGTPC_End_Procedure_Id	:\n", prefix);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//		sprintf(buffer, "	%sGTPC_End_Procedure_Desc	:\n", prefix);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}else{
//		sprintf(buffer, "	%sGTPC_End_Procedure_Id	: %d\n", prefix, pGtpSession->GTPRspMsgId);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//		sprintf(buffer, "	%sGTPC_End_Procedure_Desc	: %s\n", prefix, pGtpSession->GTPRspMsgDesc.c_str());
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}
//
//
//	if(pGtpSession->cause_val == -1){
//		sprintf(buffer, "	%sEnd_Cause			:\n", prefix);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}
//	else{
//		sprintf(buffer, "	%sEnd_Cause			: %d\n", prefix, pGtpSession->cause_val);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//
//		sprintf(buffer, "	%sEnd_Cause_Desc		: %s\n", prefix, pGtpSession->cause_desc.c_str());
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}
//
//	sprintf(buffer, "	%sBytes_Transfer_ul		: %d\n", prefix, pGtpSession->ByteSizeUL);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sBytes_Transfer_dl		: %d\n", prefix, pGtpSession->ByteSizeDL);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';


	sprintf(buffer, "-------------------------------------------------\n");
	tdrdata.append(buffer);

//	buffer[0] = '\0';
	delete[] buffer;
//	return tdrdata;
}
