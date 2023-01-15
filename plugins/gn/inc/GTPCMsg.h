/*
 * GTPCMsg.h
 *
 *  Created on: 10-Aug-2016
 *      Author: deb
 */

#ifndef PLUGINS_GN_INC_GTPCMSG_H_
#define PLUGINS_GN_INC_GTPCMSG_H_

#include <map>
#include <string.h>
#include "IPGlobal.h"

using namespace std;

//#define MAX_ADDR_STRING_LEN 40
//#define MAX_APN_LENGTH 		100
//#define MAX_IMSI_LEN		17

enum GTPMessageType
{
	// echo request GTPC and GTPU
	GTPParser_GTP__UC_ECO_REQ = 1,
	// echo response, GTPC and GTPU
	GTPParser_GTP_UC_ECO_RES = 2,
	// version not found, GTPC
	GTPParser_GTP_U_Ver_not_found = 3,
	// GTPC: create pdp request
	GTPParser_GTP_C_Create_PDP_REQ = 16,
	GTPParser_GTP_C_Create_PDP_RES = 17,
	GTPParser_GTP_C_Update_PDP_REQ = 18,
	GTPParser_GTP_C_Update_PDP_RES = 19,
	GTPParser_GTP_C_Delete_PDP_REQ = 20,
	GTPParser_GTP_C_Delete_PDP_RES = 21,

	GTPParser_GTP_U_Error_Ind = 26,
	GTPParser_GTP_C_PDU_Notif_REQ = 27,
	GTPParser_GTP_C_PDU_Notif_RES = 28,

	GTPParser_GTP_C_Identification_REQ = 48,
	GTPParser_GTP_C_Identification_RES = 49,
	GTPParser_GTP_C_SGSN_Context_REQ = 50,
	GTPParser_GTP_C_SGSN_Context_RES = 51,
	GTPParser_GTP_C_SGSN_Context_ACK = 52,
	GTPParser_GTP_GPDU	= 255
};

typedef struct _gtpcData
{
//	string		sIP;
//	string		dIP;
	uint32_t	sIP;
	uint32_t	dIP;
	uint16_t 	sp;
	uint16_t 	dp;
	bool		direction;
	uint16_t	udpLen;
	/*
	 * NSAPI and Tunnel ID together can I dentify the PDP context
	 */
	uint32_t tunnel_id_control;
	uint32_t tunnel_id_data_1;
	uint32_t tunnel_id_data_2;
	uint32_t pkt_tunnel_id;
	uint32_t sequence_no;
	uint16_t msgLen;
	uint32_t packetLen;

	uint16_t mcc;
	uint16_t mnc;

	GTPMessageType msg_type;
	uint32_t session_no;
	uint32_t n_pdu_no;
	uint32_t nsapi_val;

	char gsn_addr_data[IP_ADDR_LEN];
	char gsn_addr_ctl[IP_ADDR_LEN];
	char gsn[IP_ADDR_LEN];

	string action;

	// if tear down indication is set,all pdp context identified by NSAPI
	// shall be deleted
	bool is_teardown_set;
	bool is_reorder;
	uint8_t cause_val;
	char msisdn[MSISDN_LEN];
	char apn[APN_LEN];
	char imsi_no[IMSI_LEN];
	char end_user_protocol[5];
	char end_user_address[IP_ADDR_LEN];
	uint32_t src_ip_address; //[MAX_ADDR_STRING_LEN];
	uint32_t dest_ip_address; //[MAX_ADDR_STRING_LEN];
//	uint32_t charging_gateway_addr; //[MAX_ADDR_STRING_LEN];
	char charging_gateway_addr[IP_ADDR_LEN];
	timeval tv;

	_gtpcData()
	{
		reset();
	}

	void reset()
	{
//		sIP.clear();
//		dIP.clear();
		sIP = 0;
		dIP = 0;
		sp = 0;
		dp = 0;
		direction = false;
		udpLen = 0;
		tunnel_id_control = 0;
		tunnel_id_data_1 = 0;
		tunnel_id_data_2 = 0;
		pkt_tunnel_id = 0;
		sequence_no = 0;
		msgLen = 0;
		packetLen = 0;
		mcc = 0;
		mnc = 0;
		session_no = 0;
		n_pdu_no = 0;
		nsapi_val = 0;
		gsn_addr_data[0] = 0;
		gsn_addr_ctl[0] = 0;
		gsn[0] = 0;
		action.clear();
		is_teardown_set = false;
		is_reorder = false;
		cause_val = 0;
		msisdn[0] = 0;
		apn[0] = 0;
		imsi_no[0] = 0;
		end_user_protocol[0] = 0;
		end_user_address[0] = 0;
		src_ip_address = 0;
		dest_ip_address = 0;
		charging_gateway_addr[0] = 0;
	}

	void set (const _gtpcData *obj)
	{
		this->sIP = obj->sIP;
		this->dIP = obj->dIP;
		this->sp = obj->sp;
		this->dp = obj->dp;

		this->direction = obj->direction;

		this->udpLen = obj->udpLen;
		this->tunnel_id_control = obj->tunnel_id_control;
		this->tunnel_id_data_1 = obj->tunnel_id_data_1;
		this->tunnel_id_data_2 = obj->tunnel_id_data_2;
		this->pkt_tunnel_id = obj->pkt_tunnel_id;
		this->sequence_no = obj->sequence_no;
		this->msgLen = obj->msgLen;
		this->packetLen = obj->packetLen;
		this->mcc = obj->mcc;
		this->mnc = obj->mnc;
		this->session_no = obj->session_no;
		this->n_pdu_no = obj->n_pdu_no;
		this->nsapi_val = obj->nsapi_val;
		strcpy(this->gsn_addr_data, obj->gsn_addr_data);
		strcpy(this->gsn_addr_ctl, obj->gsn_addr_ctl);
		strcpy(this->gsn, obj->gsn);
		this->action = obj->action;
		this->is_teardown_set = obj->is_teardown_set;
		this->is_reorder = obj->is_reorder;
		this->cause_val = obj->cause_val;
		strcpy(this->msisdn, obj->msisdn);
		strcpy(this->apn, obj->apn);
		strcpy(this->imsi_no, obj->imsi_no);
		strcpy(this->end_user_protocol, obj->end_user_protocol);
		strcpy(this->end_user_address, obj->end_user_address);
		this->src_ip_address = obj->src_ip_address;
		this->dest_ip_address = obj->dest_ip_address;
		strcpy(this->charging_gateway_addr, obj->charging_gateway_addr);
	}
}gtpcMsg;

#endif /* PLUGINS_GN_INC_GTPCMSG_H_ */
