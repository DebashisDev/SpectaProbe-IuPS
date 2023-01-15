/*
 * GTPMsg.h
 *
 *  Created on: 10-Aug-2016
 *      Author: deb
 */

#ifndef PLUGINS_GN_INC_GTPMSG_H_
#define PLUGINS_GN_INC_GTPMSG_H_

#include <map>
#include <string.h>

//#include "GTPGlobal.h"
//#include "IPGlobal.h"

using namespace std;

#define IMSI_LEN			15
#define MSISDN_LEN			12
#define IMEI_LEN			14
#define APN_LEN		 		50
#define IP_ADDR_LEN 		40

enum GTPMessageType
{
	GTPParser_GTP__UC_ECO_REQ 		= 1,
	GTPParser_GTP_UC_ECO_RES 		= 2,
	GTPParser_GTP_U_Ver_not_found 	= 3,

	GTPV1_CREATE_PDP_REQUEST 		= 16,
	GTPV1_CREATE_PDP_RESPONSE 		= 17,
	GTPV1_UPDATE_PDP_REQUEST 		= 18,
	GTPV1_UPDATE_PDP_RESPONSE 		= 19,
	GTPV1_DELETE_PDP_REQUEST 		= 20,
	GTPV1_DELETE_PDP_RESPONSE 		= 21,

	GTPParser_GTP_U_Error_Ind 		= 26,
	GTPParser_GTP_C_PDU_Notif_REQ 	= 27,
	GTPParser_GTP_C_PDU_Notif_RES 	= 28,

	GTPParser_GTP_C_Identification_REQ = 48,
	GTPParser_GTP_C_Identification_RES = 49,
	GTPParser_GTP_C_SGSN_Context_REQ = 50,
	GTPParser_GTP_C_SGSN_Context_RES = 51,
	GTPParser_GTP_C_SGSN_Context_ACK = 52,
	GTPParser_GTP_GPDU				 = 255
};

typedef struct _gtpV1Data
{
	string			sourceAddr;
	string			destAddr;
	uint32_t		long_sourceAddr;
	uint32_t		long_destAddr;
	uint16_t		s_port;
	uint16_t		d_port;
	string			timeStamp;
	bool			direction;
	uint32_t		sessionId;
//	GTPMessageType 	msg_type;
	uint16_t		msgType;
	string			msg_desc;
	uint16_t 		msgLen;
	uint32_t		gtpcLen;
	uint32_t 		pkt_tunnel_id;
	bool			sequenceFlag;
	uint32_t 		sequenceNo;
	uint16_t 		mcc;
	uint16_t 		mnc;
	uint16_t 		lac;
	string			lachex;
	uint16_t 		rac;
	string			rachex;
	uint16_t 		cellid;
	string			cellidhex;
	string			uli;
	uint16_t 		rat;
	uint32_t 		tunnel_id_control;
	uint32_t 		tunnel_id_data_1;
	uint32_t 		tunnel_id_data_2;
	uint32_t 		nsapi_val;

	uint16_t		mbrupl;
	uint16_t		mbrdnl;

	char 			imsi_no[IMSI_LEN];
	char 			imei[IMEI_LEN];
	char 			end_user_address[IP_ADDR_LEN];
	char 			end_user_protocol[IP_ADDR_LEN];
	char 			apn[APN_LEN];
	char 			addr_data[IP_ADDR_LEN];
	char 			addr_ctl[IP_ADDR_LEN];
	char 			gsn[IP_ADDR_LEN];
	char 			msisdn[MSISDN_LEN];
	char 			charging_gateway_addr[IP_ADDR_LEN];
	uint8_t 		cause_val;
	string			cause_val_desc;
	bool 			is_reorder;
	uint32_t 		charging_Id;
	bool 			is_teardown_set;

	_gtpV1Data()
	{ reset(); }

//	~_gtpV1Data(){}

	void reset()
	{
		sourceAddr = "";
		destAddr = "";
		long_sourceAddr = 0;
		long_destAddr = 0;
		d_port = 0;
		s_port = 0;
		timeStamp = "";
		direction = false;
		tunnel_id_control = 0;
		tunnel_id_data_1 = 0;
		tunnel_id_data_2 = 0;
		pkt_tunnel_id = 0;

		msgType = 0;
		msg_desc = "NA";
		sequenceFlag = false;
		sequenceNo = 0;
		msgLen = 0;
		gtpcLen = 0;
		mcc = 0;
		mnc = 0;
		lac = 0;
		lachex.assign("NA");
		rac = 0;
		rachex.assign("NA");
		cellid = 0;
		cellidhex.assign("NA");

		uli.assign("NA");

		rat = 0;
		nsapi_val = 0;
		mbrupl = 0;
		mbrdnl = 0;

		addr_data[0] = 0;
		addr_ctl[0] = 0;
		strcpy(gsn, "NA");
		is_teardown_set = false;
		is_reorder = false;
		cause_val = 0;
		cause_val_desc = "";
		strcpy(msisdn, "NA");
		strcpy(apn, "NA");
		strcpy(imsi_no, "NA");
		strcpy(imei, "NA");
		strcpy(end_user_protocol, "NA");
		strcpy(end_user_address, "NA");
		strcpy(charging_gateway_addr, "NA");
	}

	void set (const _gtpV1Data *obj)
	{
		this->sourceAddr = obj->sourceAddr;
		this->destAddr = obj->destAddr;
		this->long_sourceAddr = obj->long_sourceAddr;
		this->long_destAddr = obj->long_destAddr;
		this->s_port = obj->s_port;
		this->d_port = obj->d_port;
		this->timeStamp = obj->timeStamp;
		this->direction = obj->direction;
		this->msgType = obj->msgType;
		this->msg_desc = obj->msg_desc;
		this->tunnel_id_control = obj->tunnel_id_control;
		this->tunnel_id_data_1 = obj->tunnel_id_data_1;
		this->tunnel_id_data_2 = obj->tunnel_id_data_2;
		this->pkt_tunnel_id = obj->pkt_tunnel_id;
		this->sequenceFlag = obj->sequenceFlag;
		this->sequenceNo = obj->sequenceNo;
		this->msgLen = obj->msgLen;
		this->gtpcLen = obj->gtpcLen;
		this->mcc = obj->mcc;
		this->mnc = obj->mnc;
		this->lac = obj->lac;
		this->lachex = obj->lachex;
		this->rac = obj->rac;
		this->rachex = obj->rachex;
		this->cellid = obj->cellid;
		this->cellidhex = obj->cellidhex;
		this->uli = obj->uli;
		this->rat = obj->rat;
		this->nsapi_val = obj->nsapi_val;

		this->mbrdnl = obj->mbrdnl;
		this->mbrupl = obj->mbrupl;

		strcpy(this->addr_data, obj->addr_data);
		strcpy(this->addr_ctl, obj->addr_ctl);
		strcpy(this->gsn, obj->gsn);
		this->is_teardown_set = obj->is_teardown_set;
		this->is_reorder = obj->is_reorder;
		this->cause_val = obj->cause_val;
		this->cause_val_desc = obj->cause_val_desc;
		strcpy(this->msisdn, obj->msisdn);
		strcpy(this->apn, obj->apn);
		strcpy(this->imsi_no, obj->imsi_no);
		strcpy(this->imei, obj->imei);
		strcpy(this->end_user_protocol, obj->end_user_protocol);
		strcpy(this->end_user_address, obj->end_user_address);
		strcpy(this->charging_gateway_addr, obj->charging_gateway_addr);
	}
}gtpV1Msg;

#endif /* PLUGINS_GN_INC_GTPMSG_H_ */
