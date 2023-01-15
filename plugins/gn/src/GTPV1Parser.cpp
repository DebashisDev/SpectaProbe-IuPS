/*
 * GTPCParser.cpp
 *
 *  Created on: 10-Aug-2016
 *      Author: deb
 */

#include <unistd.h>

#include "GTPV1Parser.h"
#include "GTPMessage.h"
#include "GTPSessionManager.h"

GTPV1Parser::GTPV1Parser() {
	hdrv1 = 0;
	hdr = 0;
	header_size = 0;
	this->_name = "GTP";
	setLogLevel(Log::theLog().level());
	gtpMessage = new GTPMessage();
	size_of_hdr = sizeof(GTP_V1_hdr);
}

GTPV1Parser::~GTPV1Parser() {
	delete(gtpMessage);
}

VOID GTPV1Parser::parseGtpV1Packet(const BYTE packet, MPacket *msgObj)
{
	hdrv1 = getGTPHeader(packet);

	if ((hdrv1->Version != 1) && (hdrv1->protocol_type_flag != 1))
	{
//		printf("Received GTP-2 or GTP-0 or GTP-charging packet, discarding");
		msgObj->ipAppProtocol = 0;
		return;
	}

	msgObj->gtpcMsgLen 			= ntohs(hdrv1->MsgLen);
	msgObj->gtpcPktTunnelId 	= ntohl(hdrv1->MsgTeid);

	msgObj->gtpcMsgType 		= hdrv1->MsgType;

	msgObj->gtpcIsSquenceFlag 	= false; //hdrv1->suquence_no_flag;

	msgObj->gtpcSequenceNo 		= hdrv1->Sequence;

	switch(msgObj->gtpcMsgType)
	{
		case GTPV1_CREATE_PDP_REQUEST:	// 16
				processPacket(packet, msgObj);
				IPGlobal::dnsDayHandler << msgObj->IMSI << " " << msgObj->gtpcCellId << endl;
//				msgObj->isUpDir = true;
				break;

		case GTPV1_CREATE_PDP_RESPONSE: // 17
				processPacket(packet, msgObj);

//				printf("CTRL [%u] DATA [%u] IP[%s] Code[%d]\n",
//						msgObj->gtpcTunnel_Id_Control, msgObj->gtpcTunnel_Id_Data_1,  msgObj->gtpUserIpAddress, msgObj->gtpcCauseCode);
//				msgObj->isUpDir = false;
				break;

		case GTPV1_UPDATE_PDP_REQUEST:  // 18
				processPacket(packet, msgObj);
//				msgObj->isUpDir = true;
				break;

		case GTPV1_UPDATE_PDP_RESPONSE: // 19
				processPacket(packet, msgObj);
//				msgObj->isUpDir = false;
				break;

		case GTPV1_DELETE_PDP_REQUEST: 	// 20
				processPacket(packet, msgObj);
//				msgObj->isUpDir = true;
				break;
		case GTPV1_DELETE_PDP_RESPONSE:	// 21
				processPacket(packet, msgObj);
//				msgObj->isUpDir = false;
				break;

		default:
				msgObj->ipAppProtocol = 0;
				break;
	}
}

bool GTPV1Parser::isValidInformationElement(const uint8_t first)
{
	bool bRet = true;
	for (int ic = 0; ic < 11; ic++)
	{
		if (first == unknown_ie[ic])
		{
			bRet = false;
			return (bRet);
		}
	}
	if ((first >= 30) && (first <= 126))
	{
		bRet = false;
		return (bRet);
	}
	// Added by Debashis
	if((first >= 148) && (first <= 154))
	{ return (bRet); }

	if ((first >= 144) && (first <=250))
	{
		bRet = false;
		return (bRet);
	}
	return (bRet);
}

void GTPV1Parser::processPacket(const BYTE packet, MPacket *msgObj)
{
	size_t offset = 0;

	header_size = 0;
	hdr = (GTP_V1_hdr*)packet;

	if (hdr->pdu_no_flag | hdr->extended_header_flag | hdr->suquence_no_flag)
		header_size = size_of_hdr;
	else
		header_size = size_of_hdr - 4;

	size_t m_DataLen = msgObj->gtpcMsgLen + 12;
	int offset_length = msgObj->gtpcMsgLen;

	while(offset_length > 4) // Last 4 Bytes are VLAN Trailer
	{
		size_t len = 0;
		uint8_t first = *(packet + header_size + offset);		// this is the information element type
		offset++;

		if (!isValidInformationElement(first))
		{ break; }

		switch(first)
		{
			case GTP_EXT_CAUSE:
					len = gtpMessage->get_cause_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_IMSI:
					len = gtpMessage->get_imsi_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_RAI:
					len = gtpMessage->get_routing_area_msg_len(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_SELECT:
					len = gtpMessage->get_selection_mode_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_TEARD_IND:
					len = gtpMessage->get_teardown_indication_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_USER_ADDR:
					len = gtpMessage->get_end_user_addr_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_NSAPI:
					len = gtpMessage->get_nsapi_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_TEID_II:
					len = gtpMessage->get_tied_data2_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_TEID:
					len = gtpMessage->get_tied_data1_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_MSISDN:
					len = gtpMessage->get_msisdn_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_GSN_ADDR:
					len = gtpMessage->get_gsn_addr_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_TEID_CP:
					len = gtpMessage->get_tied_ctl_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_PRIV_EXT:
					len = gtpMessage->get_private_data_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_CHARGING:
					len = gtpMessage->get_charging_gateway_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_CHARG_ID:
					len = gtpMessage->get_charging_ID_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_TRACE_REF:
			case GTP_EXT_PTMSI:
			case GTP_EXT_PKT_F:
					len = gtpMessage->get_trace_ref_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_TRACE_TYPE:
					len = gtpMessage->get_trace_type_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_APN:
					len = gtpMessage->get_access_pt_name_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_TFT:
			case GTP_EXT_TRIG_ID:
			case GTP_EXT_OMC:
			case GTP_EXT_UTRN:
					len = gtpMessage->get_tft_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_CHARG_CHRC:
					len = gtpMessage->get_charg_charc_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_PROTO_CONF:
					len = gtpMessage->get_protocol_config_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_REORDER:
					len = gtpMessage->get_reording_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_SSGN_NO:
					len = gtpMessage->get_ssgn_no_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_RECOV:
			case GTP_EXT_TLLI:
			case GTP_EXT_TMSI:
			case GTP_EXT_MAP:
			case GTP_EXT_MS_V:
			case GTP_EXT_RAD_SMS:
			case GTP_EXT_MS_NOT_RECH:
			case GTP_EXT_RP:
					len = gtpMessage->get_recovery_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_HEADER_T_L:
			case GTP_EXT_QOS:
					len = gtpMessage->get_qos_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_RAB:
					len = gtpMessage->get_rab_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_AUTH_T:
					len = gtpMessage->get_auth_tip_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_RABCONT:
					len = gtpMessage->get_rab_context_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_RANAP:
					len = gtpMessage->get_RANAP_cause_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_COMMON_FLAG:
					len = gtpMessage->get_common_flag(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_APN_RES:
					len = gtpMessage->get_apn_restriction(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_RAT:
					len = gtpMessage->get_RAT_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_ULI:
					len = gtpMessage->get_ULI_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_TZ:
					len = gtpMessage->get_timezone_info(packet, header_size + offset, msgObj);
					break;

			case GTP_EXT_IMEI:
					len = gtpMessage->get_IMEI_info(packet, header_size + offset, msgObj);
					break;

			default:
					len++;
					break;
		}

		// only for ssgn and ggsn adressing
		if (first == 133)
			handle_ggsn_sgsn_address(msgObj);

		offset += len;
		offset_length = (int)(m_DataLen - (header_size + offset));
	}
}

void GTPV1Parser::handle_ggsn_sgsn_address(MPacket *msgObj)
{
	static int count = 0;

	if(strlen(msgObj->gtpcGSN) > 20)
	{ return; }

	if (count == 0)
	{
		strcpy(msgObj->gtpcSgsnAddrCtl, msgObj->gtpcGSN);
		count++;
	}
	else if (count == 1)
	{
		strcpy(msgObj->gtpcSgsnAddrData, msgObj->gtpcGSN);
		count = 0;
	}
}
