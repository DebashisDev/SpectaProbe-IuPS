/*
 * GTPMessage.cpp
 *
 *  Created on: Jun 9, 2016
 *      Author: soumen
 */
/*
 * GTPMessage.cpp
 *
 *  Created on: Jun 9, 2016
 *      Author: soumen
 */
#include <malloc.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

#include "GTPMessage.h"

#include "GTPMsg.h"
#include "IpAddress.h"
//#include "IPGlobal.h"

using namespace std;

intstrmap gtp_cause_type = intstrmap();
//inf_table ie_table = inf_table();
msgType gtpMsgType = msgType();

size_t GTPMessage::get_routing_area_msg_len(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	int mcc_mnc;
	uint8_t octet;
	uint16_t mcc, mnc;
	uint8_t mcc1, mcc2, mcc3, mnc1, mnc2, mnc3;

	bool long_mnc = false;

	/* MCC + MNC */
	memcpy(&mcc_mnc, (const void *)(packet + offset), sizeof(uint8_t)*3);
	/* Mobile country code MCC */
	octet = (uint8_t)*(packet + offset);
	mcc1 = octet & 0x0f;
	mcc2 = octet >> 4;
	offset++;
	octet = (uint8_t)*(packet + offset);
	mcc3 = octet & 0x0f;
	/* MNC, Mobile network code (octet 3 bits 5 to 8, octet 4) */
	mnc3 = octet >> 4;
	offset++;
	octet = (uint8_t)*(packet + offset);
	mnc1 = octet & 0x0f;
	mnc2 = octet >> 4;

	mcc = 100 * mcc1 + 10 * mcc2 + mcc3;
	mnc = 10 * mnc1 + mnc2;
	if ((mnc3 != 0xf) || (mcc_mnc == 0xffffff))
	{
		long_mnc = true;
#if BYTE_ORDER == LITTLE_ENDIAN
		mnc = 10 * mnc + mnc3;
#endif
#if BYTE_ORDER == BIG_ENDIAN
		mnc = 100 * mnc3 + mnc;
#endif
	}

	if (long_mnc)
	{
		msgObj->gtpcMCC = mcc;
		msgObj->gtpcMNC = mnc;
	}
	else
	{
		msgObj->gtpcMCC = mcc;
		msgObj->gtpcMNC = mnc;
	}

	char lachex[5], rachex[3];

	strcpy(lachex,"");
	strcpy(rachex,"");

	sprintf(lachex,"%02x%02x",packet[offset+1],packet[offset+2]);
	sprintf(rachex,"%02x",packet[offset+3]);

	int lacint = (int)strtol(lachex, NULL, 16);
	int racint = (int)strtol(rachex, NULL, 16);

	msgObj->gtpcLAC = lacint;
	msgObj->gtpcRAC = racint;


//	printf("lac %d| rac %d\n",lacint, racint);
	return (6);
}


size_t GTPMessage::get_recovery_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	// one octet val
	return (1);
}

size_t GTPMessage::get_selection_mode_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	// one octet val
	return (1);
}

size_t GTPMessage::get_cause_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t ie_length = 0;
	uint8_t cause_val = *(packet + offset);
	ie_length++;
	msgObj->gtpcCauseCode = cause_val;
	return (ie_length);
}

char* GTPMessage::bcd_to_str(const BYTE packet, uint32_t offset, uint32_t no_of_octet)
{
	uint32_t length = 0;
	uint8_t octet;
	int iCount = 0;
	char *imsi_str = NULL;
	/*
	 *  0 1 2 3 4 5 6 7 8 9 a b c d e f
	 *  1 2 3 4 5 6 7 8 9 ? ? ? ? ? ? ?
	 * */
	const uint8_t out[16] = {'0','1','2','3','4','5','6','7','8','9','?','?','?','?','?','?'};
	uint32_t t_offset = offset;
//	length = offset + 8;  // imsi is 8 octet
	length = offset + no_of_octet;  // imsi is 8 octet
	imsi_str = (char *)malloc(((size_t)length - offset)*2+1);
	while (t_offset < length)
	{
		octet = *(packet + t_offset);
		imsi_str[iCount] = out[octet & 0x0f];
		iCount++;
	  /*
	   * unpack second value in byte
   	   */
		octet = octet >> 4;
		if (octet == 0x0f) /* odd number bytes - hit filler */
		  break;

		imsi_str[iCount] = out[octet & 0x0f];
		iCount++;
		t_offset++;
	}
	imsi_str[iCount]= '\0';
	return (imsi_str);
}

//void GTPMessage::bcd_to_str(const BYTE packet, uint32_t offset, uint32_t no_of_octet, char *imsi_str)
//{
//	uint32_t length = 0;
//	uint8_t octet;
//	int iCount = 0;
////	char *imsi_str = NULL;
//	/*
//	 *  0 1 2 3 4 5 6 7 8 9 a b c d e f
//	 *  1 2 3 4 5 6 7 8 9 ? ? ? ? ? ? ?
//	 * */
//	const uint8_t out[16] = {'0','1','2','3','4','5','6','7','8','9','?','?','?','?','?','?'};
//	uint32_t t_offset = offset;
////	length = offset + 8;  // imsi is 8 octet
//	length = offset + no_of_octet;  // imsi is 8 octet
////	imsi_str = (char *)malloc(((size_t)length - offset)*2+1);
//	while (t_offset < length)
//	{
//		octet = *(packet + t_offset);
//		imsi_str[iCount] = out[octet & 0x0f];
//		iCount++;
//	  /*
//	   * unpack second value in byte
//   	   */
//		octet = octet >> 4;
//		if (octet == 0x0f) /* odd number bytes - hit filler */
//		  break;
//
//		imsi_str[iCount] = out[octet & 0x0f];
//		iCount++;
//		t_offset++;
//	}
//	imsi_str[iCount]= '\0';
////	return (imsi_str);
//}

size_t GTPMessage::get_imsi_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	char *imsi_str = NULL;
	imsi_str = bcd_to_str(packet, offset, 8);
	strcpy(msgObj->IMSI, imsi_str);
	delete[] imsi_str;
	// imsi is 8 octet size
	return(8);
}

//size_t GTPMessage::get_imsi_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
//{
//	bcd_to_str(packet, offset, 8, msgObj->IMSI);
//	return(8);
//}

size_t GTPMessage::get_nsapi_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t ie_length = 0;
	uint8_t nsapi = *(packet + offset);
	nsapi = nsapi & 0X0F;
	msgObj->gtpcNsapi = (uint32_t)nsapi;
	ie_length++;
	return (ie_length);
}

size_t GTPMessage::get_teardown_indication_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t ie_length = 0;
	uint8_t teardown_ind = *(packet + offset);
	teardown_ind = teardown_ind & 0x01;
	/*
	 * if teardown indication set then all PDP context gets deleted
	 */
//	msgObj->gtpcIsTeardownSet = teardown_ind;
	ie_length++;
	return (ie_length);
}

size_t GTPMessage::get_tied_ctl_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t ie_length = 0;
	uint32_t tnl_id; //
	//= (uint32_t)*(packet + offset);
	memcpy(&tnl_id , (const void *)(packet + offset), sizeof(uint32_t));
	// tied control is 4 octet
	ie_length += 4;
	msgObj->gtpcTunnel_Id_Control = ntohl(tnl_id);

	return (ie_length);
}

size_t GTPMessage::get_reording_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t len = 0;
	uint8_t reorder = *(packet + offset);
	reorder = reorder & 0x01;
//	msgObj->gtpcIsReorder = reorder;
	return (++len);
}

size_t GTPMessage::get_tied_data1_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t ie_length = 0;
	uint32_t tnl_id;
	memcpy(&tnl_id , (const void *)(packet + offset), sizeof(uint32_t));
	// tied data 1 is 4 octet
	ie_length += 4;
	msgObj->gtpcTunnel_Id_Data_1 = ntohl(tnl_id);

	return (ie_length);
}

size_t GTPMessage::get_tied_data2_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t ie_length = 0;
	uint8_t nsapi = *(packet + offset);
	ie_length++;
	offset++;
	nsapi = nsapi & 0X0F;
	msgObj->gtpcNsapi = nsapi;
	uint32_t tnl_id; // = *(packet + offset);
	memcpy(&tnl_id, (const void *)(packet + offset), sizeof(uint32_t));
	// tied data 1 is 4 octet
	ie_length += 4;
	msgObj->gtpcTunnel_Id_Data_2 = ntohl(tnl_id);
	return (ie_length);
}

size_t GTPMessage::get_end_user_addr_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t ie_length = 0;
	uint16_t e_usr_addr;
	char ipBuffer[40];

	ipBuffer[0] = '\0';

	memcpy(&e_usr_addr, (const void *)(packet + offset), sizeof(uint16_t));
	uint16_t e_usr_addr_ln = ntohs(e_usr_addr);
	ie_length += 2;
	offset += 2;
	//If length is 2, then it is only type, no address
	if (((uint32_t)e_usr_addr_ln) == 2)
	{
		msgObj->gtpUserIpAddressType = packet[offset+1];
		ie_length += 2;
		return ie_length;
	}
	// length will be 6 for IPV4
	else if (((uint32_t)e_usr_addr_ln) == 6)
	{
		// pdp no 0x21
		offset += 2;
		ie_length += 2;

		msgObj->gtpUserIpAddressType = packet[offset-1];
//		msgObj->gtpUserIpAddress = packet[offset]*IPGlobal::IPV4_MULTIPLIER_OCTET_1 + packet[offset+1]*IPGlobal::IPV4_MULTIPLIER_OCTET_3 + packet[offset+2]*IPGlobal::IPV4_MULTIPLIER_OCTET_3 + packet[offset+3];

		sprintf(msgObj->gtpUserIpAddress,"%d.%d.%d.%d",packet[offset],packet[offset+1],packet[offset+2], packet[offset+3]);

//		uint32_t ipv4addr;
//		memcpy(&ipv4addr ,(packet + offset), sizeof(uint32_t));
//
//		sprintf((char *)ipBuffer,"%d.%d.%d.%d",(ipv4addr & 0xFF000000) >> 24,(ipv4addr & 0x00FF0000) >> 16,(ipv4addr & 0x0000FF00) >> 8, ipv4addr & 0x000000FF);
//
//		printf("Address:: %s\n", ipBuffer);
//		exit(1);
//		IPv4Address ipaddr = IPv4Address(ipv4addr);
//		if (ipaddr.isValid())
//			strncpy(msgObj->gtpUserIpAddress, ipaddr.toString().c_str(),
//					(strlen(ipaddr.toString().c_str() + 1))>40?40:(strlen(ipaddr.toString().c_str()) + 1));
//		strcpy(msgObj->gtpUserIpAddress, "ipv4");
		ie_length += 4;
		return ie_length;
	}
	else if (((uint32_t)e_usr_addr_ln) == 18)
	{
		//To be modified as per above logic
	  	offset += 2;
		ie_length += 2;

		msgObj->gtpUserIpAddressType = packet[offset-1];
		sprintf(msgObj->gtpUserIpAddress,"%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x", packet[offset], packet[offset+1], \
				packet[offset+2], packet[offset+3], packet[offset+4], packet[offset+5], packet[offset+6], packet[offset+7], packet[offset+8], packet[offset+9], \
				packet[offset+10], packet[offset+11], packet[offset+12], packet[offset+13], packet[offset+14], packet[offset+15], packet[offset+16]);

//		msgObj->gtpUserIpAddress = packet[offset]  packet[offset+1] *IPGlobal::IPV6_MULTIPLIER_OCTET_1 +
//				packet[offset+1]*IPGlobal::IPV6_MULTIPLIER_OCTET_3 +
//				packet[offset+2]*IPGlobal::IPV6_MULTIPLIER_OCTET_3 +
//				packet[offset+4]*IPGlobal::IPV6_MULTIPLIER_OCTET_4 +
//				packet[offset+5]*IPGlobal::IPV6_MULTIPLIER_OCTET_5 +
//				packet[offset+6];
//
//		// 16 for address, 1 one '/0'
//		char* ipv6 = new char[16];
//		for(int i = 0; i < 16; i++)
//			ipv6[i] = *(packet + offset + i);
//		IPv6Address ipaddr = IPv6Address(ipv6);
//		if (ipaddr.isValid())
//			strncpy(msgObj->gtpUserIpAddress, ipaddr.toString().c_str(),
//			(strlen(ipaddr.toString().c_str() + 1))>40?40:(strlen(ipaddr.toString().c_str()) + 1));
//		strcpy(msgObj->gtpUserIpAddress, "ipv6");
		ie_length += 16;
//		delete[] ipv6;
		return (ie_length);
	}
	else
	{
		// for ppp. PDP no 1
		//strcpy(msgObj->gtpUserIpAddress, "pdp");
		msgObj->gtpUserIpAddressType = packet[offset-1];
		strcpy(msgObj->gtpUserIpAddress, "pdp");
		ie_length += 2;
//		return ie_length;
		return (4);
	}
}
size_t GTPMessage::get_charging_gateway_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t ie_length = 0;
	uint16_t e_usr_addr_ln; // = (uint16_t)*(packet + offset);
	memcpy(&e_usr_addr_ln, (const void *)(packet + offset), sizeof(uint16_t));
	ie_length += 2;
	offset += 2;
	uint16_t pkt_len = ntohs(e_usr_addr_ln);
	// length will be 6 for IPV4

	if (pkt_len == 4)
	{
//		uint32_t ipv4addr = (uint32_t)*(m_data + offset);
		/*
		IPv4Address ipaddr = IPv4Address(ipv4addr);
		if (ipaddr.isValid())
			strncpy(pktstruct->charging_gateway_addr, ipaddr.toString().c_str(),
			(strlen(ipaddr.toString().c_str() + 1))>40?40:(strlen(ipaddr.toString().c_str()) + 1));
			*/
//		ie_length += 4;
//	pktstruct->charging_gateway_addr = ipv4addr;
//		return ie_length;

		sprintf(msgObj->gtpcChargingGWAddr,"%d.%d.%d.%d",packet[offset],packet[offset+1],packet[offset+2], packet[offset+3]);

//		uint32_t ipv4addr; // = (uint32_t)*(packet + offset);
//		memcpy(&ipv4addr ,(packet + offset), sizeof(uint32_t));
//		IPv4Address ipaddr = IPv4Address(ipv4addr);
//		if (ipaddr.isValid())
//			strncpy(msgObj->gtpcChargingGWAddr, ipaddr.toString().c_str(),
//					(strlen(ipaddr.toString().c_str() + 1))>40?40:(strlen(ipaddr.toString().c_str()) + 1));

		ie_length += 4;
//old		msgObj->gtpcData->charging_gateway_addr = ipv4addr;
		return ie_length;
	}
	else if (pkt_len == 16)
	{
		// pdp no 0x57
		// 16 for address, 1 one '/0'

		char* ipv6 = new char[16];
		for(int i = 0; i < 16; i++)
			ipv6[i] = *(packet + offset + i);

		sprintf(msgObj->gtpcChargingGWAddr,"%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x", packet[offset], packet[offset+1], \
				packet[offset+2], packet[offset+3], packet[offset+4], packet[offset+5], packet[offset+6], packet[offset+7], packet[offset+8], packet[offset+9], \
				packet[offset+10], packet[offset+11], packet[offset+12], packet[offset+13], packet[offset+14], packet[offset+15], packet[offset+16]);

		/*
		IPv6Address ipaddr = IPv6Address(ipv6);
		if (ipaddr.isValid())
			strncpy(msgObj->gtpcData->charging_gateway_addr, ipaddr.toString().c_str(),
				(strlen(ipaddr.toString().c_str() + 1))>40?40:(strlen(ipaddr.toString().c_str()) + 1));
				*/
		delete[] ipv6;

		ie_length += 16;
		return (ie_length);
	}
	else
	{
		// for ppp. PDP no 1
		ie_length += 4;
//		return (ie_length);
		return(6);
	}
}

size_t GTPMessage::get_gsn_addr_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t ie_length = 0;
	uint16_t gsn_len; // = (uint16_t)*(packet + offset);
	memcpy(&gsn_len, (const void *)(packet + offset), sizeof(uint16_t));
	uint16_t gsnn_len_h = ntohs(gsn_len);
	offset += 2;
	ie_length += 2;

	switch(gsnn_len_h)
	{
		case 4:
		{
//			uint32_t ipv4addr;
//			memcpy(&ipv4addr, (packet + offset), sizeof(uint32_t));
//			IPv4Address ip = IPv4Address(ipv4addr);
//			const char* ipadd = ip.toString().c_str();
//			int iplen = strlen(ipadd);
//			if (ip.isValid())
//				strncpy(msgObj->gtpcGSN, ipadd,
//						(iplen + 1)>40?40:(iplen + 1));

			sprintf(msgObj->gtpcGSN,"%d.%d.%d.%d",packet[offset],packet[offset+1],packet[offset+2], packet[offset+3]);
		}
		break;
		case 5:
		{
//			uint32_t ipv4addr;
//			memcpy(&ipv4addr, (packet + offset + 1), sizeof(uint32_t));
//			IPv4Address ip = IPv4Address(ipv4addr);
//			if (ip.isValid())
//				strncpy(msgObj->gtpcGSN, ip.toString().c_str(),
//				(strlen(ip.toString().c_str()) + 1) > 40?40:(strlen(ip.toString().c_str()) + 1));

			sprintf(msgObj->gtpcGSN,"%d.%d.%d.%d",packet[offset],packet[offset+1],packet[offset+2], packet[offset+3]);

		}
		break;
		case 16:
		{
//			char* ipv6	= new char[16];
//			for(int i = 0; i < 16; i++)
//				ipv6[i] = *(packet + offset + i);
//			IPv6Address ip = IPv6Address(ipv6);
//			if (ip.isValid())
//				strncpy((char *)msgObj->gtpUserIpAddress.c_str(), ip.toString().c_str(),
//				(strlen(ip.toString().c_str() + 1))>40?40:(strlen(ip.toString().c_str()) + 1));
//			delete[] ipv6;

			sprintf(msgObj->gtpcGSN,"%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x", packet[offset], packet[offset+1], \
					packet[offset+2], packet[offset+3], packet[offset+4], packet[offset+5], packet[offset+6], packet[offset+7], packet[offset+8], packet[offset+9], \
					packet[offset+10], packet[offset+11], packet[offset+12], packet[offset+13], packet[offset+14], packet[offset+15], packet[offset+16]);

		}
		break;
		case 17:
		{
//			char* ipv6 = new char[16];
//			for(int i = 0; i < 16; i++)
//				ipv6[i] = *(packet + offset + 1 + i);
//			IPv6Address ip = IPv6Address(ipv6);
//			if (ip.isValid())
//				strncpy((char *)msgObj->gtpUserIpAddress.c_str(), ip.toString().c_str(),
//				(strlen(ip.toString().c_str() + 1))>40?40:(strlen(ip.toString().c_str()) + 1));
//			delete[] ipv6;

			sprintf(msgObj->gtpcGSN,"%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x", packet[offset], packet[offset+1], \
					packet[offset+2], packet[offset+3], packet[offset+4], packet[offset+5], packet[offset+6], packet[offset+7], packet[offset+8], packet[offset+9], \
					packet[offset+10], packet[offset+11], packet[offset+12], packet[offset+13], packet[offset+14], packet[offset+15], packet[offset+16]);
		}
		break;
		default:
		{
			const char* gsn = (char*)(packet + offset);
			strncpy(msgObj->gtpcGSN, gsn, (strlen(gsn) + 1)>40?40:(strlen(gsn) + 1));
		}
	}
	ie_length += gsnn_len_h;
	return (ie_length);
}
size_t GTPMessage::get_tft_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t ie_length = 0;
	uint16_t gsn_len;	// = (uint16_t)*(packet + offset);
	memcpy(&gsn_len, (const void *)(packet + offset), sizeof(uint16_t));
	uint16_t gsnn_len_h = ntohs(gsn_len);
	ie_length = 2 + gsnn_len_h;
	return (ie_length);
}

uint8_t* GTPMessage::decode_apn(uint8_t * m_data, uint16_t length)
{
	 uint8_t* str = new uint8_t[MAX_APN_LENGTH+1];
	 uint32_t curr_len;

	 memset(str, 0, MAX_APN_LENGTH+1);
	 memcpy(str, m_data, length<MAX_APN_LENGTH?length:MAX_APN_LENGTH);
	 curr_len = 0;

	 while ((curr_len < length) && (curr_len < MAX_APN_LENGTH))
	 {
		 uint32_t step = str[curr_len];
		 str[curr_len] = '.';
		 curr_len += step+1;
	 }
	 return str;
}


size_t GTPMessage::get_access_pt_name_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t ie_length = 0;
	uint16_t apn_len ; //= (uint16_t)*(m_data + offset);
	memcpy(&apn_len, (const void *)(packet + offset), sizeof(uint16_t));
	uint16_t apn_len_h = ntohs(apn_len);
	offset += 2;
	ie_length += 2;
	uint8_t* apn = decode_apn((unsigned char *)(packet + offset), apn_len_h);

	if(strlen((const char *)apn) < 50)
		strcpy(msgObj->gtpcAPN, (char*)apn);

	delete apn;
	ie_length += apn_len_h;
	return (ie_length);
}

//uint8_t* GTPMessage::decode_apn(uint8_t * m_data, uint16_t length)
//{
////	 uint8_t* str = new uint8_t[MAX_APN_LENGTH+1];
////	 uint32_t curr_len;
////
////	 memset(str, 0, MAX_APN_LENGTH+1);
////	 memcpy(str, m_data, length<MAX_APN_LENGTH?length:MAX_APN_LENGTH);
//
//	uint8_t str[MAX_APN_LENGTH+1];
//	str[0] = 0;
//	uint32_t curr_len = 0;
//	memcpy(str, m_data, length<MAX_APN_LENGTH?length:MAX_APN_LENGTH);
//
//	 while ((curr_len < length) && (curr_len < MAX_APN_LENGTH))
//	 {
//		 uint32_t step = str[curr_len];
//		 str[curr_len] = '.';
//		 curr_len += step+1;
//	 }
//	 str[curr_len] = '\0';
//	 return str;
//}
//
//
//size_t GTPMessage::get_access_pt_name_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
//{
//	size_t ie_length = 0;
//	uint16_t apn_len ; //= (uint16_t)*(m_data + offset);
//	memcpy(&apn_len, (const void *)(packet + offset), sizeof(uint16_t));
//	uint16_t apn_len_h = ntohs(apn_len);
//	offset += 2;
//	ie_length += 2;
//	uint8_t* apn = decode_apn((unsigned char *)(packet + offset), apn_len_h);
//
//	if(strlen((const char *)apn) < 50)
//		strcpy(msgObj->APN, (char*)apn);
//
////	delete apn;
//
//	ie_length += apn_len_h;
//	return (ie_length);
//}


size_t GTPMessage::get_rab_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t ie_length = 0;
	uint16_t qos_len;// = (uint16_t)*(packet + offset);
	memcpy(&qos_len, (const void *)(packet + offset), sizeof(uint16_t));
	uint16_t qos_len_h = ntohs(qos_len);
	// one more octet for retention
	ie_length += 7;
	ie_length += qos_len_h;
	return (ie_length);
}
size_t GTPMessage::get_qos_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t ie_length = 0;
	uint16_t qos_len;// = (uint16_t)*(packet + offset);
	memcpy(&qos_len, (const void *)(packet + offset), sizeof(uint16_t));
	uint16_t qos_len_h = ntohs(qos_len);
	// one more octet for retention

	uint16_t mbrupl = *(packet + offset + 8); // Maximum bit rate for uplink
	uint16_t mbrdnl = *(packet + offset + 9); // Maximum bit rate for dnlink

	if(qos_len_h > 8) {

		if(mbrupl >= 1 && mbrupl <= 63 )
		{
			// giving a range of values from 1 kbps to 63 kbps in 1 kbps increments.
			msgObj->gtpcMbrupl = mbrupl;
		}
		else if(mbrupl >= 64 && mbrupl <= 127)
		{
			// giving a range of values from 64 kbps to 568 kbps in 8 kbps increments.
			msgObj->gtpcMbrupl = 64 + (mbrupl - 64) * 8;
		}
		else if(mbrupl >= 128 && mbrupl <= 254)
		{
			// giving a range of values from 576 kbps to 8640 kbps in 64 kbps increments.
			msgObj->gtpcMbrupl = 576 + (mbrupl - 128) * 64;
		}
		else
		{
			// 0 kbps
			msgObj->gtpcMbrupl = 0;
		}

		if(mbrdnl >= 1 && mbrdnl <= 63 )
			msgObj->gtpcMbrdnl = mbrdnl;
		else if(mbrdnl >= 64 && mbrdnl <= 127)
			msgObj->gtpcMbrdnl = 64 + (mbrdnl - 64) * 8;
		else if(mbrdnl >= 128 && mbrdnl <= 254)
			msgObj->gtpcMbrdnl = 576 + (mbrdnl - 128) * 64;
		else
			msgObj->gtpcMbrdnl = 0;
	}

	if(qos_len_h >= 15) {
		uint16_t max_dl_ext = 	*(packet + offset + 15); // Ext Maximum bit rate for down link

        /* Octet 15 */
        if ((max_dl_ext > 0) && (max_dl_ext <= 74))
        	msgObj->gtpcExtMbrdnl = 8600 + max_dl_ext * 100;
        else if ((max_dl_ext > 74) && (max_dl_ext <= 186))
        	msgObj->gtpcExtMbrdnl = 16000 + (max_dl_ext - 74) * 1000;
        else if ((max_dl_ext > 186) && (max_dl_ext <= 250))
        	msgObj->gtpcExtMbrdnl = 128000 + (max_dl_ext - 186) * 2000;
	}

//	printf("Packet# %lu| Uplink = %d kbps| Dnlink = %d kbps\n",
//			IPGlobal::t_FrameCount, msgObj->gtpData->mbrupl, msgObj->gtpData->mbrdnl);

	ie_length += 2; // earlier it was 3
	ie_length += qos_len_h;

	return (ie_length);
}

size_t GTPMessage::get_protocol_config_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	uint16_t length;
	memcpy(&length, (const void *)(packet + offset), sizeof(uint16_t));
	uint16_t len = ntohs(length);

	return (2+len);
}

char* GTPMessage::decode_msisdn(uint8_t *packet)
 {
  char *digit_str = NULL;
  int offset = 0;
  offset += 1;
  digit_str = bcd_to_str(packet, offset, 6);
  return (digit_str);
 }

size_t GTPMessage::get_msisdn_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t ie_length = 0;
	uint16_t msisdn_len; // = (uint16_t)*(packet + offset);
	memcpy(&msisdn_len, (const void *)(packet + offset), sizeof(uint16_t));
	uint16_t msisdn_len_h = ntohs(msisdn_len);
	offset += 2;
	ie_length += 2;
	if (msisdn_len_h < 1)
		return ie_length;
	char* msisdn = NULL;
	msisdn = decode_msisdn((uint8_t*)(packet + offset));
	strcpy(msgObj->MSISDN, msisdn);
	if (msisdn != NULL)
		delete[] msisdn;
	ie_length += msisdn_len_h;
	return (ie_length);
}

//void GTPMessage::decode_msisdn(uint8_t *packet, char *msisdn)
// {
//  char *digit_str = NULL;
//  int offset = 0;
//  offset += 1;
//  bcd_to_str(packet, offset, 6, msisdn);
////  return (digit_str);
// }
//
//size_t GTPMessage::get_msisdn_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
//{
//	size_t ie_length = 0;
//	uint16_t msisdn_len; // = (uint16_t)*(packet + offset);
//	memcpy(&msisdn_len, (const void *)(packet + offset), sizeof(uint16_t));
//	uint16_t msisdn_len_h = ntohs(msisdn_len);
//	offset += 2;
//	ie_length += 2;
//	if (msisdn_len_h < 1)
//		return ie_length;
////	char* msisdn = NULL;
//	decode_msisdn((uint8_t*)(packet + offset), msgObj->MSISDN);
////	strcpy(msgObj->MSISDN, msisdn);
////	if (msisdn != NULL)
////		delete[] msisdn;
//	ie_length += msisdn_len_h;
//	return (ie_length);
//}

size_t GTPMessage::get_private_data_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t ie_length = 0;
	uint16_t e_usr_addr;
	memcpy(&e_usr_addr, (const void *)(packet + offset), sizeof(uint16_t));
	uint16_t e_usr_addr_ln = ntohs(e_usr_addr);
	ie_length += 2;
	offset += 2;
	ie_length += e_usr_addr_ln;
	return ie_length;
}
size_t GTPMessage::get_ssgn_no_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t ie_length = 0;
	uint16_t qos_len;// = (uint16_t)*(packet + offset);
	memcpy(&qos_len, (const void *)(packet + offset), sizeof(uint16_t));
	uint16_t qos_len_h = ntohs(qos_len);
	// one more octet for retention
	ie_length += 2;
	ie_length += qos_len_h;
	return (ie_length);
}

size_t GTPMessage::get_RAT_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t ie_length = 0;
	uint16_t ratLen;
	memcpy(&ratLen, (const void *)(packet + offset), sizeof(uint16_t));
	uint16_t len = ntohs(ratLen);

	offset += 2;

	msgObj->gtpcRAT = *(packet + offset);
	if(msgObj->gtpcRAT > 2)
		msgObj->gtpcRAT = 0;

	ie_length += 2;
	ie_length += len;

	return(ie_length);
}

size_t GTPMessage::get_ULI_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t ie_length = 0;
	uint16_t uliLen, uliType;
	memcpy(&uliLen, (const void *)(packet + offset), sizeof(uint16_t));
	offset+= 2;	//Length
	uint16_t len = ntohs(uliLen);
	ie_length = len + 2;

	uliType= *(packet + offset); //Geographic Location Type
	offset++;

//	if(uliType > 3)
//		printf("ULI Len::%d Type::%d %lu\n", len, uliType, IPGlobal::t_FrameCount);

	int mcc_mnc;
	uint8_t octet;
	uint16_t mcc, mnc;
	uint8_t mcc1, mcc2, mcc3, mnc1, mnc2, mnc3;

	bool long_mnc = false;

	/* MCC + MNC */
	memcpy(&mcc_mnc, (const void *)(packet + offset), sizeof(uint8_t)*3);
	/* Mobile country code MCC */
	octet = (uint8_t)*(packet + offset);
	mcc1 = octet & 0x0f;
	mcc2 = octet >> 4;
	offset++;
	octet = (uint8_t)*(packet + offset);
	mcc3 = octet & 0x0f;
	/* MNC, Mobile network code (octet 3 bits 5 to 8, octet 4) */
	mnc3 = octet >> 4;
	offset++;
	octet = (uint8_t)*(packet + offset);
	mnc1 = octet & 0x0f;
	mnc2 = octet >> 4;

	mcc = 100 * mcc1 + 10 * mcc2 + mcc3;
	mnc = 10 * mnc1 + mnc2;
	if ((mnc3 != 0xf) || (mcc_mnc == 0xffffff))
	{
		long_mnc = true;
#if BYTE_ORDER == LITTLE_ENDIAN
		mnc = 10 * mnc + mnc3;
#endif
#if BYTE_ORDER == BIG_ENDIAN
		mnc = 100 * mnc3 + mnc;
#endif
	}

	char lachex[5];
	lachex[0] = '\0';
	sprintf(lachex,"%02x%02x",packet[offset+1],packet[offset+2]);
//	printf("lachex %s\n",lachex);
//	offset++;
//	offset++;

	char cellhex[5];
	cellhex[0] = '\0';

	sprintf(cellhex,"%02x%02x",packet[offset+3],packet[offset+4]);
//	printf("cellhex %s\n",cellhex);
	offset++;
	offset++;

	int lacint = (int)strtol(lachex, NULL, 16);
	int cellint = (int)strtol(cellhex, NULL, 16);

	msgObj->gtpcLAC = lacint;
	msgObj->gtpcCellId = cellint;
//	msgObj->gtpcCellIdHex.assign(cellhex);
//
//	msgObj->gtpcULI.assign(std::to_string(mcc))
//						.append("-")
//						.append(std::to_string(mnc))
//						.append("-")
//						.append(std::to_string(lacint))
//						.append("-")
//						.append(std::to_string(cellint));


//	printf("msgObj->gtpData->uli :: %s\n",msgObj->gtpData->uli.c_str());
	return (ie_length);
}

size_t GTPMessage::get_timezone_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t ie_length = 0;
	uint16_t timezoneLen;
	memcpy(&timezoneLen, (const void *)(packet + offset), sizeof(uint16_t));
	uint16_t len = ntohs(timezoneLen);

	ie_length = len + 2;
	offset += 2;
	return(ie_length);
}

char* GTPMessage::decode_imei(uint8_t *packet)
 {
  char *digit_str = NULL;
  int offset = 0;
  digit_str = bcd_to_str(packet, offset, 8);
  return (digit_str);
 }

size_t GTPMessage::get_IMEI_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t ie_length = 0;
	uint16_t imeiLen;
	memcpy(&imeiLen, (const void *)(packet + offset), sizeof(uint16_t));
	uint16_t len = ntohs(imeiLen);

	char *imei = NULL;
	offset += 2;
	imei = decode_imei((uint8_t*)(packet + offset));
	strcpy(msgObj->IMEI, imei);

	delete[] imei;

	ie_length = len + 2;
	return(ie_length);
}

//void GTPMessage::decode_imei(uint8_t *packet, char *imei)
// {
//  char *digit_str = NULL;
//  int offset = 0;
//  bcd_to_str(packet, offset, 8, imei);
// }
//
//size_t GTPMessage::get_IMEI_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
//{
//	size_t ie_length = 0;
//	uint16_t imeiLen;
//	memcpy(&imeiLen, (const void *)(packet + offset), sizeof(uint16_t));
//	uint16_t len = ntohs(imeiLen);
//
//	offset += 2;
//	decode_imei((uint8_t*)(packet + offset), msgObj->IMEI);
//
//	ie_length = len + 2;
//	return(ie_length);
//}

size_t GTPMessage::get_common_flag(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t ie_length = 0;
	uint16_t commonlen;
	memcpy(&commonlen, (const void *)(packet + offset), sizeof(uint16_t));
	uint16_t len = ntohs(commonlen);

	offset += 2;
	ie_length = len + 2;
	return(ie_length);
}

size_t GTPMessage::get_apn_restriction(const BYTE packet, uint32_t offset, MPacket *msgObj)
{
	size_t ie_length = 0;
	uint16_t apnlen;
	memcpy(&apnlen, (const void *)(packet + offset), sizeof(uint16_t));
	uint16_t len = ntohs(apnlen);
	//printf("******* APN Restriction Len : %d\n", len);
	offset += 2;
	ie_length = len + 2;
	return(ie_length);
}

