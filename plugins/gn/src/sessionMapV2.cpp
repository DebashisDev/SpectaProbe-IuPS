/*
 * sessionMap.cpp
 *
 *  Created on: June 18, 2016
 *      Author: soumen
 */
#include <stdio.h>
#include <string.h>
#include <SessionMapV2.h>
#include <mutex>
#include <memory>
//
//extern std::mutex GTPMutex;
//extern std::mutex GTPMQ;
//extern int _debug;

extern SessionV2Q sessionQ_V2;
extern session_V2 sessionMngr_V2;

void session_V2::create_session_update(sh_controlpacket_V2 pktstruct)
{
	// GTPMutex.lock();
	SessionMapV2::iterator itr = sessionTable_V2[INDEX_CU(pktstruct->pkt_tunnel_id)].find(pktstruct->pkt_tunnel_id);
	// GTPMutex.unlock();
	if (itr != sessionTable_V2[INDEX_CU(pktstruct->pkt_tunnel_id)].end())
	{
//		GTPMutex.lock();
//		// @to-do update session data
//		// itr->second->__tv_last = pktstruct->tv;
//
//		GTPMutex.unlock();
	}
}
void session_V2::insert_session(sh_controlpacket_V2 req, sh_controlpacket_V2 res)
{
	sh_controlpacket_V2 thisSession = sh_controlpacket_V2(new controlpacket_V2);

	thisSession->pkt_tunnel_id = res->pkt_tunnel_id;
	thisSession->rec_tunnel_id = req->rec_tunnel_id;
	thisSession->trans_tunnel_id = res->rec_tunnel_id;
	
	thisSession->routing_area_info = req->routing_area_info;
	thisSession->imsi_no = req->imsi_no;
	thisSession->apn_info = req->apn_info;
	thisSession->msisdn = req->msisdn;
	thisSession->mei_info = req->mei_info;
	thisSession->serving_network = req->serving_network;
	thisSession->user_location = req->user_location;

	thisSession->ipv4_add_recv = req->ipv4_add_recv;
	thisSession->ipv4_add_trans = req->ipv4_add_trans;
	thisSession->ipv6_add_recv = req->ipv6_add_recv;
	thisSession->ipv6_add_trans = req->ipv6_add_trans;

	thisSession->STN_SR = req->STN_SR;
	thisSession->end_user_address = req->end_user_address;
	thisSession->gsn = req->gsn;
	thisSession->gsn_ipv6 = res->gsn_ipv6;
	thisSession->gsn_ipv4 = res->gsn_ipv4;
	thisSession->TAD_info = req->TAD_info;
	thisSession->tmsi_info = req->tmsi_info;
	thisSession->global_cnid_str = req->global_cnid_str;
	thisSession->trace_mnc_mcc = req->trace_mnc_mcc;
	thisSession->pdn_type = req->pdn_type;
	thisSession->p_tmsi_sig = req->p_tmsi_sig;
	thisSession->trace_id = req->trace_id;
	thisSession->guti_mnc_mcc = req->guti_mnc_mcc;
	thisSession->plmn_id = req->plmn_id;
	thisSession->rat_type = req->rat_type;
	thisSession->ldn_value = req->ldn_value;
	thisSession->relay_type = req->relay_type;
	thisSession->relay_name = req->relay_name;
	thisSession->twan_ssid = req->twan_ssid;
	thisSession->twan_bssid = req->twan_bssid;
	thisSession->twan_name = req->twan_name;
	thisSession->twan_cai = req->twan_cai;
	
	thisSession->cause_val = res->cause_val;
	thisSession->interface_type = req->interface_type;
	thisSession->counter_val = req->counter_val;
	thisSession->ulink_bit_rate = req->ulink_bit_rate;
	thisSession->dlink_bit_rate = req->dlink_bit_rate;
	thisSession->cn_id = req->cn_id;
	thisSession->charging_id = req->charging_id;
	thisSession->procedure_transt_id = req->procedure_transt_id;
	thisSession->p_tmsi = req->p_tmsi;
	thisSession->day_light_saving_time = req->day_light_saving_time;
	thisSession->time_zone = req->time_zone;
	thisSession->user_grp_id = req->user_grp_id;
	thisSession->mme_code = req->mme_code;
	thisSession->dl_gtpu_seq_no = req->dl_gtpu_seq_no;
	thisSession->ul_gtpu_seq_no = req->ul_gtpu_seq_no;
	thisSession->dl_pdcp_seq_no = req->dl_pdcp_seq_no;
	thisSession->ul_pdcp_seq_no = req->ul_pdcp_seq_no;
	thisSession->nsapi_val = req->nsapi_val;
	thisSession->port_no = req->port_no;
	thisSession->twan_plmni_id = req->twan_plmni_id;
	
	
//	GTPMQ.lock();

	sessionTable_V2[INDEX_CD(thisSession->rec_tunnel_id)].insert
	(std::pair<uint32_t, sh_controlpacket_V2>(thisSession->rec_tunnel_id, thisSession));

	sessionTable_V2[INDEX_CU(thisSession->trans_tunnel_id)].insert
	(std::pair<uint32_t, sh_controlpacket_V2>(thisSession->trans_tunnel_id, thisSession));
	
//	sessionQ_V2.push(thisSession);
//	GTPMQ.unlock();
}


void session_V2::update_session(sh_controlpacket_V2 req, sh_controlpacket_V2 res)
{
// 	GTPMutex.lock();
 	sh_controlpacket_V2 thisSession = lookup(req->pkt_tunnel_id, CTL_UP);
 	if (thisSession == NULL)
 	{
 		thisSession = lookup(req->pkt_tunnel_id, CTL_DW);
 	}

	// remove the session's maps
	sessionTable_V2[INDEX_CD(thisSession->rec_tunnel_id)].erase(thisSession->rec_tunnel_id);
	sessionTable_V2[INDEX_CU(thisSession->trans_tunnel_id)].erase(thisSession->trans_tunnel_id);

//	GTPMutex.unlock();

	thisSession->__procedure_type = UPDATE1;
//	GTPMutex.lock();
	sessionTable_V2[INDEX_CU(thisSession->trans_tunnel_id)].insert
	(std::pair<uint32_t, sh_controlpacket_V2>(thisSession->trans_tunnel_id, thisSession));
	sessionTable_V2[INDEX_CD(thisSession->rec_tunnel_id)].insert
	(std::pair<uint32_t, sh_controlpacket_V2>(thisSession->rec_tunnel_id, thisSession));

//	GTPMutex.unlock();
//
//	GTPMQ.lock();
//	sessionQ_V2.push(thisSession);
//	GTPMQ.unlock();
}

void session_V2::erase_session(const uint32_t tied)
{
//	GTPMutex.lock();
	SessionMapV2::iterator itr = sessionTable_V2[INDEX_CD(tied)].find(tied);
//	GTPMutex.unlock();

	if (itr != sessionTable_V2[INDEX_CD(tied)].end())
	{
//		GTPMQ.lock();
		itr->second->__procedure_type = DELETE1;
//		sessionQ_V2.push(itr->second);
//		GTPMQ.unlock();

//		GTPMutex.lock();
		sessionTable_V2[INDEX_CD(itr->second->rec_tunnel_id)].erase(itr->second->rec_tunnel_id);
		sessionTable_V2[INDEX_CU(itr->second->trans_tunnel_id)].erase(itr->second->trans_tunnel_id);

//		GTPMutex.unlock();
	}
	else
	{
//		GTPMutex.lock();
		itr = sessionTable_V2[INDEX_CU(tied)].find(tied);
//		GTPMutex.unlock();
		if (itr != sessionTable_V2[INDEX_CU(tied)].end())
		{
//			GTPMQ.lock();
			//itr->second->__procedure_type = DELETE;
//			sessionQ_V2.push(itr->second);
//			GTPMQ.unlock();

//			GTPMutex.lock();
			sessionTable_V2[INDEX_CD(itr->second->rec_tunnel_id)].erase(itr->second->rec_tunnel_id);
			sessionTable_V2[INDEX_CU(itr->second->trans_tunnel_id)].erase(itr->second->trans_tunnel_id);
//			GTPMutex.unlock();
		}
	}
}


sh_controlpacket_V2 session_V2::lookup(const uint32_t pkt_tunnel_id, TIED_TYPE type)
{

	SessionMapV2::iterator itr;
//	sh_controlpacket_V2 ss = sh_controlpacket_V2(new sessionstruct);

	switch(type)
	{
	case CTL_UP:
		// GTPMutex.lock();
		// sgsn intiated, target tunnel id is ggsn tied, stored as INDEX_CU
		itr = sessionTable_V2[INDEX_CU(pkt_tunnel_id)].find(pkt_tunnel_id);
		// GTPMutex.unlock();
		// did we get one?
		if (itr != sessionTable_V2[INDEX_CU(pkt_tunnel_id)].end())
		{
			return (itr->second);
		}
	break;
	case CTL_DW:
		// GTPMutex.lock();
		// sgsn intiated, target tunnel id is ggsn tied, stored as INDEX_CU
		itr = sessionTable_V2[INDEX_DU(pkt_tunnel_id)].find(pkt_tunnel_id);
		// GTPMutex.unlock();
		// did we get one?
		if (itr != sessionTable_V2[INDEX_DU(pkt_tunnel_id)].end())
		{
			return (itr->second);
		}
		break;
	default:
		break;
	}
	return (NULL);
}


