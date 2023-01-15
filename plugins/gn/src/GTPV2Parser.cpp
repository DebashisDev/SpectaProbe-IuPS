/*
 * GTPV2Parser.cpp
 *
 *  Created on: Oct 26, 2016
 *      Author: Debashis
 */

#include "GTPV2Parser.h"
#include "GTPMessage.h"

GTPV2Parser::GTPV2Parser() {
	uplink = false;
	packet = NULL;
	hdr = new GTP_V2_hdr();

	GTPMessageV2::init_cause_type();
	GTPMessageV2::init_ie_table();
	GTPMessageV2::init_msg_type();
	GTPMessageV2::init_rat_type();
}

GTPV2Parser::~GTPV2Parser() {
	delete(hdr);
}

VOID GTPV2Parser::parseGtpV2Packet(const BYTE packet, MPacket *msgObj)
{
#if 0
//	GTPMessageV2::init_cause_type();
//	GTPMessageV2::init_ie_table();
//	GTPMessageV2::init_msg_type();
//	GTPMessageV2::init_rat_type();

	msgType msgDesc = GTPMessageV2::get_msg_type_map();
	msgType ratDesc = GTPMessageV2::get_rat_type_map();
	msgType causeDesc = GTPMessageV2::get_cause_type_map();

	this->packet = packet;

	TCHAR lchar[10];
	lchar[0] = 0;
	size_t offset = 0;

	hdr->flags = VAL_BYTE(this->packet);
	hdr->p_flag = (hdr->flags & 0x10) >> 4;
	hdr->t_flag = (hdr->flags & 0x08) >> 3;

	offset += 1; 	// Flag

	hdr->MsgType = VAL_BYTE(this->packet + offset);
	offset += 1; 	// Message Type

	hdr->MsgLen 		= VAL_USHORT(this->packet + offset);
	offset += 2;	// Message Length

	if (hdr->t_flag) {
		hdr->MsgTeid = VAL_ULONG(this->packet + offset);
		offset += 4;
	}

	sprintf(lchar, "%02x%02x%02x", this->packet[offset], this->packet[offset+1], this->packet[offset+2]);
	hdr->sequenceNo = ProbeUtility::HextoDigits(lchar);
	offset += 4; // SequenceNo (3 Bytes) + Spare (1 Byte)



//	printf("\n# %ld Msg Type:: %d TEID:: %ld\n", IPGlobal::t_FrameCount, hdr->MsgType, hdr->MsgTeid);
//	return;

	msgObj->gtpV2Data->msgType 			= hdr->MsgType;
	msgObj->gtpV2Data->msg_desc 		= msgDesc[msgObj->gtpV2Data->msgType];
	msgObj->gtpV2Data->sequence_no 		= hdr->sequenceNo;
	msgObj->gtpV2Data->pkt_tunnel_id 	= hdr->MsgTeid;

	switch(hdr->MsgType)
	{
		case GTPV2_CREATE_SESSION_REQUEST: 		// MME --> SGW
							msgObj->gtpV2Data->ByteSizeUL = msgObj->frameData->frameSize;
							msgObj->gtpV2Data->timeStamp = msgObj->frameData->frameTimeStamp;
							msgObj->gtpV2Data->direction = false;
							processPacket(this->packet, msgObj, offset);

							if(msgObj->gtpV2Data->ratId >= 0 && msgObj->gtpV2Data->ratId <= 7)
								msgObj->gtpV2Data->rat_type	= ratDesc[msgObj->gtpV2Data->ratId];

							break;

		case GTPV2_CREATE_SESSION_RESPONSE: 	// MME <-- SGW
							msgObj->gtpV2Data->ByteSizeDL = msgObj->frameData->frameSize;
							msgObj->gtpV2Data->timeStamp = msgObj->frameData->frameTimeStamp;
							processPacket(this->packet, msgObj, offset);

							if(msgObj->gtpV2Data->cause_val > 0)
								msgObj->gtpV2Data->cause_desc = causeDesc[msgObj->gtpV2Data->cause_val];

							break;

		case GTPV2_DELETE_SESSION_REQUEST: 		// MME --> SGW
							msgObj->gtpV2Data->ByteSizeUL = msgObj->frameData->frameSize;
							msgObj->gtpV2Data->timeStamp = msgObj->frameData->frameTimeStamp;
							msgObj->gtpV2Data->direction = false;
							processPacket(this->packet, msgObj, offset);

							if(msgObj->gtpV2Data->ratId >= 0 && msgObj->gtpV2Data->ratId <= 7)
								msgObj->gtpV2Data->rat_type	= ratDesc[msgObj->gtpV2Data->ratId];

							break;

		case GTPV2_DELETE_SESSION_RESPONSE:		// MME <-- SGW
							msgObj->gtpV2Data->ByteSizeDL = msgObj->frameData->frameSize;
							msgObj->gtpV2Data->timeStamp = msgObj->frameData->frameTimeStamp;
							processPacket(this->packet, msgObj, offset);

							if(msgObj->gtpV2Data->cause_val > 0)
								msgObj->gtpV2Data->cause_desc = causeDesc[msgObj->gtpV2Data->cause_val];

							break;

		case GTPV2_CREATE_BEARER_REQUEST:		// MME <-- SGW
							msgObj->gtpV2Data->ByteSizeDL = msgObj->frameData->frameSize;
							msgObj->gtpV2Data->timeStamp = msgObj->frameData->frameTimeStamp;
							msgObj->gtpV2Data->direction = true;
							processPacket(this->packet, msgObj, offset);

							break;

		case GTPV2_CREATE_BEARER_RESPONSE:		// MME --> SGW
							msgObj->gtpV2Data->ByteSizeUL = msgObj->frameData->frameSize;
							msgObj->gtpV2Data->timeStamp = msgObj->frameData->frameTimeStamp;
							processPacket(this->packet, msgObj, offset);

							break;

		case GTPV2_MODIFY_BEARER_REQUEST:		// MME --> SGW
							msgObj->gtpV2Data->ByteSizeUL = msgObj->frameData->frameSize;
							msgObj->gtpV2Data->timeStamp = msgObj->frameData->frameTimeStamp;
							msgObj->gtpV2Data->direction = false;
							processPacket(this->packet, msgObj, offset);

							if(msgObj->gtpV2Data->ratId >= 0 && msgObj->gtpV2Data->ratId <= 7)
								msgObj->gtpV2Data->rat_type	= ratDesc[msgObj->gtpV2Data->ratId];

							break;

		case GTPV2_MODIFY_BEARER_RESPONSE:		// MME <-- SGW
							msgObj->gtpV2Data->ByteSizeDL = msgObj->frameData->frameSize;
							msgObj->gtpV2Data->timeStamp = msgObj->frameData->frameTimeStamp;
							processPacket(this->packet, msgObj, offset);

							if(msgObj->gtpV2Data->cause_val > 0)
								msgObj->gtpV2Data->cause_desc = causeDesc[msgObj->gtpV2Data->cause_val];
							break;

		case GTPV2_UPDATE_BEARER_REQUEST:		// MME <-- SGW
							msgObj->gtpV2Data->ByteSizeDL = msgObj->frameData->frameSize;
							msgObj->gtpV2Data->timeStamp = msgObj->frameData->frameTimeStamp;
							msgObj->gtpV2Data->direction = true;
							processPacket(this->packet, msgObj, offset);

							if(msgObj->gtpV2Data->ratId >= 0 && msgObj->gtpV2Data->ratId <= 7)
								msgObj->gtpV2Data->rat_type	= ratDesc[msgObj->gtpV2Data->ratId];

							break;

		case GTPV2_UPDATE_BEARER_RESPONSE:	// MME --> SGW
//							printf("\n# %ld Msg Type:: %d TEID:: %ld\n", IPGlobal::t_FrameCount, hdr->MsgType, hdr->MsgTeid);
							msgObj->gtpV2Data->ByteSizeUL = msgObj->frameData->frameSize;
							msgObj->gtpV2Data->timeStamp = msgObj->frameData->frameTimeStamp;
							processPacket(this->packet, msgObj, offset);

							if(msgObj->gtpV2Data->cause_val > 0)
								msgObj->gtpV2Data->cause_desc = causeDesc[msgObj->gtpV2Data->cause_val];

							break;

		case GTPV2_DELETE_BEARER_REQUEST:	// MME <-- SGW
							msgObj->gtpV2Data->ByteSizeDL = msgObj->frameData->frameSize;
							msgObj->gtpV2Data->timeStamp = msgObj->frameData->frameTimeStamp;
							msgObj->gtpV2Data->direction = true;
							processPacket(this->packet, msgObj, offset);

							if(msgObj->gtpV2Data->ratId >= 0 && msgObj->gtpV2Data->ratId <= 7)
								msgObj->gtpV2Data->rat_type	= ratDesc[msgObj->gtpV2Data->ratId];

							break;

		case GTPV2_DELETE_BEARER_RESPONSE:	// MME --> SGW
//							printf("\n# %ld Msg Type:: %d TEID:: %ld\n", IPGlobal::t_FrameCount, hdr->MsgType, hdr->MsgTeid);
							msgObj->gtpV2Data->ByteSizeUL = msgObj->frameData->frameSize;
							msgObj->gtpV2Data->timeStamp = msgObj->frameData->frameTimeStamp;
							processPacket(this->packet, msgObj, offset);

							if(msgObj->gtpV2Data->cause_val > 0)
								msgObj->gtpV2Data->cause_desc = causeDesc[msgObj->gtpV2Data->cause_val];

							break;

		default:
							break;
	}
#endif
}

#if 0
void GTPV2Parser::processPacket(const BYTE packet, TPacket *msgObj, size_t offset)
{ parse_packet(packet, msgObj, offset); }

void GTPV2Parser::parse_packet(const BYTE packet, TPacket *msgObj, size_t offset)
{
	size_t initialOffset = offset;

	if (!hdr->p_flag)
	{
		get_IE_Info(msgObj, offset, packet, hdr->MsgLen + 4);
	}
	else
	{
		GTP_V2_hdr* hrd2 = (GTP_V2_hdr*)(packet + ( hdr->MsgLen + 4 + initialOffset));
		parse_packet(packet, msgObj, (hdr->MsgLen + 4 + initialOffset));
	}
}

void GTPV2Parser::get_IE_Info(TPacket *msgObj, size_t offset, const BYTE packet, size_t msgLen)
{
	uint8_t first = 0;
	bool flag = 0;

	try
	{
		inf_table_V2 information_table = GTPMessageV2::get_information_decoder_table();
		int message_length = (int)msgLen - offset;
		while(message_length > 0)
		{
			size_t len = 0;
			// this is the information element type
			first = *(packet + offset);

			if (!GTPMessageV2::isvalid(first))
			{ return; }
			else
			{
				offset++;				// Debashis:: Increment IE Type (1 Byte)
				message_length -= 1;	// Debashis:: Decrement message length by 1 Byte (IE Type)
				inf_table_V2::iterator it = information_table.find((int)first);

				if (it != information_table.end())
				{ len = it->second(packet, offset, msgObj, uplink); }
				else
				{ len++; }

				if (first == GTPV2_IE_F_TEID)
				{
					if (flag == 0) {
						msgObj->gtpV2Data->rec_tunnel_id = msgObj->gtpV2Data->pkt_tunnel_id;
						flag = 1;
					}
					else {
						msgObj->gtpV2Data->trans_tunnel_id = msgObj->gtpV2Data->pkt_tunnel_id;
						flag = 0;
					}
				}
			}
			offset += len;
			if (len < message_length)
				message_length = message_length - len;
			else
				message_length = 0;

		}
	}
	catch (...)
	{
		printf("error in loop %d", (int)first);
	}
}
#endif
