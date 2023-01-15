/*
 * GTPMessageV2.cpp
 *
 *  Created on: Jun 9, 2016
 *      Author: soumen
 */
#include <malloc.h>
#include <string.h>
#include <Commondefs.h>
#include <GTPMessageV2.h>
#include <GTPMessagedefV2.h>
#include <SessionMapV2.h>
#include <IpAddress.h>
#include <netinet/in.h>
#include <arpa/inet.h>


intstrmap_V2 GTPMessageV2::gtp_cause_type_V2 = intstrmap_V2();
intstrmap_V2 GTPMessageV2::gtp_rat_type_v2 = intstrmap_V2();
intstrmap_V2 GTPMessageV2::gtp2MsgType = intstrmap_V2();
inf_table_V2 GTPMessageV2::ie_table_V2 = inf_table_V2();

char* GTPMessageV2::get_mnc_mcc_str(uint8_t* m_data, uint32_t offset)
{
	int mcc_mnc;
	uint8_t octet;
	uint16_t mcc, mnc;
	uint8_t mcc1, mcc2, mcc3, mnc1, mnc2, mnc3;
	bool long_mnc;
	/* MCC + MNC */
	memcpy(&mcc_mnc, (m_data + offset), sizeof(uint8_t)*3);
	/* Mobile country code MCC */
	octet = (uint8_t)*(m_data + offset);
	mcc1 = octet & 0x0f;
	mcc2 = octet >> 4;
	offset++;
	octet = (uint8_t)*(m_data + offset);
	mcc3 = octet & 0x0f;
	/* MNC, Mobile network code (octet 3 bits 5 to 8, octet 4) */
	mnc3 = octet >> 4;
	offset++;
	octet = (uint8_t)*(m_data + offset);
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
	char* str = (char*)malloc(48);
	memset(str, 0x0,48);
	sprintf(str, "%u-%u", mnc, mcc);
	return (str);
}

size_t GTPMessageV2::get_cause_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	uint8_t cause_val = *(m_data + offset + 3);
	msgObj->gtpV2Data->cause_val = cause_val;
	return (ie_length);
}

char* GTPMessageV2::bcd_to_str(uint8_t* m_data, uint32_t offset, uint32_t e_usr_addr_ln)
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
	uint32_t t_offset = 0;

	length = e_usr_addr_ln;
	imsi_str = (char *)malloc(((size_t)length)*2+1);
	while (length > t_offset)
	{
		octet = *(m_data + offset);
		offset++;
		imsi_str[iCount] = out[octet & 0x0f];
		iCount++;
	  /*
	   * unpack second value in byte
   	   */
		octet = octet >> 4;
		if (octet == 0x0f)
		{
			break;	/* odd number bytes - hit filler */
		}
		imsi_str[iCount] = out[octet & 0x0f];
		iCount++;
		t_offset++;
	}
	imsi_str[iCount]= '\0';

	return (imsi_str);
}

size_t GTPMessageV2::get_imsi_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	uint16_t imsi_len; // = (uint16_t)*(m_data + offset);
	memcpy(&imsi_len, (m_data + offset), sizeof(uint16_t));
	uint16_t imsi_len_h = ntohs(imsi_len);
	if (imsi_len_h < 1)
		return 3;
	char* imsi = NULL;
	offset = offset + 3;
	imsi = GTPMessageV2::bcd_to_str(m_data, offset, imsi_len_h);
	msgObj->gtpV2Data->imsi_no = std::string(imsi);
	if (imsi != NULL)
		delete[] imsi;
	return (imsi_len_h + 3);
}
uint8_t* GTPMessageV2::decode_apn(uint8_t * m_data, uint16_t length)
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
size_t GTPMessageV2::get_access_pt_name_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t apn_len ; //= (uint16_t)*(m_data + offset);
	memcpy(&apn_len, (m_data + offset), sizeof(uint16_t));
	uint16_t apn_len_h = ntohs(apn_len);
	offset += 3;
	uint8_t* apn = GTPMessageV2::decode_apn((m_data + offset), apn_len_h);
	msgObj->gtpV2Data->apn_info = std::string((char*)apn);

	if (apn != NULL)
	  delete apn;
	ie_length = apn_len_h + 3;
	return (ie_length);
}
size_t GTPMessageV2::get_msisdn_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	uint16_t msisdn_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msisdn_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msisdn_len_h = ntohs(msisdn_len);
	if (msisdn_len_h < 1 || msisdn_len_h > 16)
		return 3;
	char* msisdn = NULL;
	offset = offset + 3;
	msisdn = GTPMessageV2::bcd_to_str(m_data, offset, msisdn_len_h);
	msgObj->gtpV2Data->msisdn = std::string(msisdn);
	if (msisdn != NULL)
		delete[] msisdn;
	return (msisdn_len_h + 3);
}

size_t GTPMessageV2::get_mei_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	uint16_t mei_len; // = (uint16_t)*(m_data + offset);
	memcpy(&mei_len, (m_data + offset), sizeof(uint16_t));
	uint16_t mei_len_h = ntohs(mei_len);
	if (mei_len_h < 1)
		return 3;
	char* mei = NULL;
	
	mei = GTPMessageV2::bcd_to_str(m_data, (offset + 3), mei_len_h);
	msgObj->gtpV2Data->mei_info = std::string(mei);

	if (mei != NULL)
		delete[] mei;
	return (mei_len_h + 3);
}
size_t GTPMessageV2::get_serving_network_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	char* serving_net = NULL;
	uint16_t mei_len; // = (uint16_t)*(m_data + offset);
	memcpy(&mei_len, (m_data + offset), sizeof(uint16_t));
	uint16_t mei_len_h = ntohs(mei_len);
	if (mei_len_h < 1)
		return 3;
	ie_length = mei_len_h + 3;
	serving_net = get_mnc_mcc_str(m_data, offset+3);
	msgObj->gtpV2Data->serving_network = std::string(serving_net);

	if(serving_net != NULL)
	  delete serving_net;
	return (ie_length);
}

char* GTPMessageV2::decode_uli(uint8_t* m_data, uint32_t offset, uint32_t length, uint8_t flags)
{
	char* uli = NULL;
//@to-do append flag info in uli based on flags
	// CGI
	if (flags & GTPv2_ULI_CGI_MASK)
	{
		uli = get_mnc_mcc_str(m_data, offset);
	}
	// SAI
	if (flags & GTPv2_ULI_SAI_MASK)
	{
		uli = get_mnc_mcc_str(m_data, offset);
	}
	// RAI
	if (flags & GTPv2_ULI_RAI_MASK)
	{
		uli = get_mnc_mcc_str(m_data, offset);
	}
	// TAI
	if (flags & GTPv2_ULI_TAI_MASK)
	{
		uli = get_mnc_mcc_str(m_data, offset);
	}
	// ECGI
	if (flags & GTPv2_ULI_ECGI_MASK)
	{
		uli = get_mnc_mcc_str(m_data, offset);
	}
	// LAI
	if (flags & GTPv2_ULI_LAI_MASK)
	{
		uli = get_mnc_mcc_str(m_data, offset);
	}
	return (uli);
}

size_t GTPMessageV2::get_user_location_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t mei_len; // = (uint16_t)*(m_data + offset);
	memcpy(&mei_len, (m_data + offset), sizeof(uint16_t));
	uint16_t mei_len_h = ntohs(mei_len);
	if (mei_len_h < 1)
		return 3;
	ie_length = mei_len_h + 3;
	uint8_t flags = (*(m_data + offset + 3)) & 0x3f;
	char* uli = decode_uli(m_data, (offset + 4), (uint32_t)mei_len_h, flags);
	msgObj->gtpV2Data->user_location = std::string(uli);

	if(uli != NULL)
	    delete uli;
	return (ie_length);
}

size_t GTPMessageV2::get_f_tied_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	uint8_t flags = *(m_data + offset +3);
	offset = offset + 4;
	uint8_t ipv4, ipv6;
	ipv4 = flags & 0x80;
	ipv6 = flags & 0x40;
	uint32_t tied = 0;
	memcpy(&tied, (m_data + offset), sizeof(uint32_t));
	ULONG pkt_tunnel_id = ntohl(tied);

//	printf("TEID :: %ld\n", pkt_tunnel_id);

	offset = offset + 4;
	if (ipv4 && ipv6)
	{
		uint32_t ipv4addr = 0;
		memcpy(&ipv4addr, (m_data + offset), sizeof(uint32_t));
		IPv4Address ipaddress4 = IPv4Address(ipv4addr);
		msgObj->gtpV2Data->ipv4_address = std::string(ipaddress4.toString());
		offset = offset + 4;
		// ipv6 address
		char* ipv6str	= new char[16];
		for(int i = 0; i < 16; i++)
		  ipv6str[i] = *(m_data + offset + i);
		IPv6Address ip6 = IPv6Address(ipv6str);
//		msgObj->gtpV2Data->ipv6_address = std::string(ipaddress6.toString());
		delete[] ipv6str;
	}
	else if (ipv4)
	{
		uint32_t ipv4addr = 0;
		memcpy(&ipv4addr, (m_data + offset), sizeof(uint32_t));
		IPv4Address ip = IPv4Address(ipv4addr);
		msgObj->gtpV2Data->ipv4_address = std::string(ip.toString());
//		printf("ipv4_address = %s\n", msgObj->gtpV2Data->ipv4_address.c_str());
		offset = offset + 4;
	}
	else if (ipv6)
	{
	    // ipv6 address
	    char* ipv6str	= new char[16];
	    for(int i = 0; i < 16; i++)
	    	ipv6str[i] = *(m_data + offset + i);
	    IPv6Address ip = IPv6Address(ipv6str);
//	    msgObj->gtpV2Data->ipv6_address = std::string(ip.toString());
	    delete[] ipv6str;
	}
	uint8_t interface_type = flags & 0x3f;

	switch(interface_type)
	{
		case 7:		// PGW
				msgObj->gtpV2Data->PGW_interfaceType = interface_type;
				msgObj->gtpV2Data->PGW_tunnelId = pkt_tunnel_id;
				msgObj->gtpV2Data->PGW_ip = msgObj->gtpV2Data->ipv4_address;
				break;

		case 10:	// MME
				msgObj->gtpV2Data->MME_interfaceType = interface_type;
				msgObj->gtpV2Data->MME_tunnelId = pkt_tunnel_id;
				msgObj->gtpV2Data->MME_ip = msgObj->gtpV2Data->ipv4_address;

				break;

		case 11:	// SGW
				msgObj->gtpV2Data->SGW_interfaceType = interface_type;
				msgObj->gtpV2Data->SGW_tunnelId = pkt_tunnel_id;
				msgObj->gtpV2Data->SGW_ip = msgObj->gtpV2Data->ipv4_address;
				break;
	}
//	printf("interface_type = %d| %lu\n", interface_type, msgObj->gtpV2Data->pkt_tunnel_id);
	return (ie_length);
}

size_t GTPMessageV2::get_recovery_restr_counter(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1 )
		return 3;
	ie_length = msg_ie_len_h + 3;
	offset = offset + 3;
	uint32_t counetr_value;
	memcpy(&counetr_value, (m_data + offset), sizeof(uint32_t));
	msgObj->gtpV2Data->counter_val = ntohl(counetr_value);
	return (ie_length);
}

size_t GTPMessageV2::reserved_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}

size_t GTPMessageV2::get_STN_SR_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1 || msg_ie_len_h >16)
		return 3;
	ie_length = msg_ie_len_h + 3;
	char str[msg_ie_len_h];
	for(int i = 0; i < msg_ie_len_h; i++)
	  memcpy(&str[i], (m_data + offset + 3 + i), sizeof(uint8_t));
	msgObj->gtpV2Data->STN_SR = std::string(str);
	return (ie_length);
}

size_t GTPMessageV2::get_ambr_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	uint32_t ulink_bit_rate, dlink_bit_rate;
	memcpy(&ulink_bit_rate, (m_data + offset + 3), sizeof(uint32_t));
	memcpy(&dlink_bit_rate, (m_data + offset + 3 + 4), sizeof(uint32_t));
	msgObj->gtpV2Data->ulink_bit_rate = ntohl(ulink_bit_rate);
	msgObj->gtpV2Data->dlink_bit_rate = ntohl(dlink_bit_rate);
	return (ie_length);
}

size_t GTPMessageV2::eps_bearer_id(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}

size_t GTPMessageV2::get_ip_address_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	offset = offset + 3;
	if (msg_ie_len_h == 4)
	{
	  // ipv4 address
	  uint32_t ipv4addr;
	  memcpy(&ipv4addr, (m_data + offset), sizeof(uint32_t));
	  IPv4Address ip = IPv4Address(ipv4addr);
	  if (ip.isValid())
	  msgObj->gtpV2Data->gsn = ip.toString();
	  
	}
	else if (msg_ie_len_h == 16)
	{
	    // ipv6 address
	    char* ipv6	= new char[msg_ie_len_h];
	    for(int i = 0; i < msg_ie_len_h; i++)
	    ipv6[i] = *(m_data + offset + i);
	    IPv6Address ip = IPv6Address(ipv6);
	    if (ip.isValid())
		msgObj->gtpV2Data->end_user_address = ip.toString();
	    delete[] ipv6;
	}
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}

size_t GTPMessageV2::get_indication_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}

size_t GTPMessageV2::get_protocol_config_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}

size_t GTPMessageV2::get_pdn_access_aloc_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);

	if (msg_ie_len_h < 1)
		return 3;

	ie_length = msg_ie_len_h + 3;
	uint8_t pdn_type = *(m_data + offset + 3) & 0x7;
	offset = offset + 4;
	if (pdn_type == 1)
	{
		char ipBuffer[20];
		unsigned int address;
		address = (m_data[offset] << 24) | (m_data[offset+1] << 16) | (m_data[offset+2] << 8) | (m_data[offset+3]);
		sprintf((char *)ipBuffer,"%d.%d.%d.%d",(address & 0xFF000000) >> 24,(address & 0x00FF0000) >> 16,(address & 0x0000FF00) >> 8, address & 0x000000FF);
		 msgObj->gtpV2Data->ppa_addr_location = std::string(ipBuffer);
		// ipv4
//	    uint32_t ipv4addr;
//	    memcpy(&ipv4addr, (m_data + offset), sizeof(uint32_t));
//	    IPv4Address ip = IPv4Address(ntohl(ipv4addr));
//	    if (ip.isValid())
//	    msgObj->gtpV2Data->ppa_addr_location = ip.toString();
	}
	if (pdn_type == 2)
	{
	    char* ipv6str	= new char[16];
	    for(int i = 0; i < 16; i++)
	    	ipv6str[i] = *(m_data + offset +1 + i);
	    IPv6Address ip = IPv6Address(ipv6str);
	    msgObj->gtpV2Data->ppa_addr_location = std::string(ip.toString());
	    delete[] ipv6str;
	}
	if (pdn_type == 3)
	{
	    char* ipv6str	= new char[16];
	    for(int i = 0; i < 16; i++)
	    	ipv6str[i] = *(m_data + offset +1 + i);
	    IPv6Address ip6 = IPv6Address(ipv6str);
	    msgObj->gtpV2Data->ppa_addr_location = std::string(ip6.toString());
	    delete[] ipv6str;
	    offset = offset + 16 + 1;
	    
	    uint32_t ipv4addr;
	    memcpy(&ipv4addr, (m_data + offset), sizeof(uint32_t));
	    IPv4Address ip = IPv4Address(ntohl(ipv4addr));
	    if (ip.isValid())
	    msgObj->gtpV2Data->ppa_addr_location = ip.toString();
	}
	
	return (ie_length);
}
size_t GTPMessageV2::get_bearer_qos_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_flow_qos_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_ebs_bearer_TFT_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_TAD_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1 || msg_ie_len_h > 48)
		return 3;
	ie_length = msg_ie_len_h + 3;
	char str[msg_ie_len_h + 1];
	for(int i = 0; i < msg_ie_len_h; i++)
	  memcpy(&str[i], (m_data + offset + 3 + i), sizeof(uint8_t));
	str[msg_ie_len_h + 1] = '\0';
	msgObj->gtpV2Data->TAD_info = std::string(str);
	return (ie_length);
}
size_t GTPMessageV2::get_TMSI_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	char tmsi[msg_ie_len_h + 1];
	for (int i =0; i < msg_ie_len_h; i++)
		memcpy(tmsi, (m_data + offset + 3 + i), sizeof(uint8_t));
	tmsi[msg_ie_len_h + 1] = '\0';
	msgObj->gtpV2Data->tmsi_info = std::string(tmsi);
	return (ie_length);
}
size_t GTPMessageV2::get_global_cn_id(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	char* mnc_mcc = get_mnc_mcc_str(m_data, offset + 3);
	msgObj->gtpV2Data->global_cnid_str = std::string(mnc_mcc);
	if (mnc_mcc != NULL)
	  delete mnc_mcc;
	uint16_t cnid = 0;
	memcpy(&cnid, (m_data + offset + 6), sizeof(uint16_t));
	msgObj->gtpV2Data->cn_id = ntohs(cnid);
	return (ie_length);
}
size_t GTPMessageV2::pdn_data_forwarding_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::S1_udf_data_ford_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_delay_value_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_bearer_context_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1 || ((msg_ie_len_h + offset) > strlen((char*)m_data)))
		return 3;
	ie_length = msg_ie_len_h + 3;

	inf_table_V2 information_table = ie_table_V2;
	int message_length = (int)msg_ie_len_h;
	offset = offset + 3;
	sh_controlpacket_V2 bearer_pkt = sh_controlpacket_V2(new controlpacket_V2);
	bearer_pkt->msgType = msgObj->gtpV2Data->msgType;
	bool flag = 0;
	while(message_length > 0)
	{
		size_t len = 0;
		// this is the information element type
		uint8_t first = *(m_data + offset);
		if (!isvalid(first))
		{
			goto out;
		}
		else
		{
			offset++;
			inf_table_V2::iterator it = information_table.find((int)first);
			if (it != ie_table_V2.end())
			{
				len = it->second(m_data, offset, msgObj, ul);
			}
			else
			{
				len++;
			}
			if (first == GTPV2_IE_F_TEID)
			{
				if (flag == 0)
				{
					bearer_pkt->rec_tunnel_id = msgObj->gtpV2Data->pkt_tunnel_id;
					bearer_pkt->ipv4_add_recv = msgObj->gtpV2Data->ipv4_address;
					bearer_pkt->ipv6_add_recv = msgObj->gtpV2Data->ipv6_address;
					flag = 1;
				}
				else
				{
					bearer_pkt->trans_tunnel_id = msgObj->gtpV2Data->pkt_tunnel_id;
					bearer_pkt->ipv4_add_trans = msgObj->gtpV2Data->ipv4_address;
					bearer_pkt->ipv6_add_trans = msgObj->gtpV2Data->ipv6_address;
					flag = 0;
				}

			}
		}
		offset += len;
		if ((int)len < message_length)
			message_length = message_length - len;
		else
			message_length = 0;
	}
out:
#if 0
	if (msgObj->gtpV2Data->msgType == GTPV2_CREATE_SESSION_REQUEST)
	{
		if (GTPLayerV2::create_bearer_map.find(bearer_pkt->rec_tunnel_id) != GTPLayerV2::create_bearer_map.end())
		{
			// should not happen
			//LOGGER->writeline("PDP create request initiated against already requested tunnel id %u, will close the earlier request\n", msgObj->gtpV2Data->pkt_tunnel_id);
			GTPLayerV2::create_bearer_map.erase(GTPLayerV2::create_bearer_map.find(bearer_pkt->rec_tunnel_id));
			GTPLayerV2::create_bearer_map.insert(std::pair<uint32_t, sh_controlpacket_V2>(bearer_pkt->rec_tunnel_id, bearer_pkt));
	//		DUMP->writeline("Bearer Request packet");
	//		GTPLayerV2::print_this_session(bearer_pkt);
		}
		else
		{
			// no need to lock here, this map gets accessed sequentially
			GTPLayerV2::create_bearer_map.insert(
				std::pair<uint32_t, sh_controlpacket_V2>(bearer_pkt->rec_tunnel_id, bearer_pkt));
	//		DUMP->writeline("Bearer Request packet");
	//		GTPLayerV2::print_this_session(bearer_pkt);
		}
	}
	else if (msgObj->gtpV2Data->msgType == GTPV2_CREATE_SESSION_RESPONSE)
	{
		map_request_ctl_V2::iterator itr = GTPLayerV2::create_bearer_map.find(bearer_pkt->trans_tunnel_id);
		if (itr != GTPLayerV2::create_bearer_map.end())
		{
//			sessionMngr_V2.insert_session(itr->second, bearer_pkt);
			GTPLayerV2::create_bearer_map.erase(itr);
		}
	//	DUMP->writeline("Bearer Response packet");
	//	GTPLayerV2::print_this_session(bearer_pkt);
	}
#endif

	return (ie_length);
}
size_t GTPMessageV2::get_charging_id_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	uint16_t charging_val;
	memcpy(&charging_val, (m_data + offset + 3), sizeof(uint16_t));
	msgObj->gtpV2Data->charging_id = ntohs(charging_val);
	return (ie_length);
}
size_t GTPMessageV2::get_charging_charac_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_trace_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	char* trace_mcc_mnc = get_mnc_mcc_str(m_data, offset + 3);
	char trace_id[4] = { 0 };
	for(int i = 0; i < 3; i++)
		memcpy(&trace_id[i], (m_data + offset + 6), sizeof(uint8_t));
	msgObj->gtpV2Data->trace_id = std::string(trace_id);
	msgObj->gtpV2Data->trace_mnc_mcc = std::string(trace_mcc_mnc);
	if (trace_mcc_mnc != NULL)
		delete trace_mcc_mnc;
	return (ie_length);
}
size_t GTPMessageV2::get_bearer_flag_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_pdn_type_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	uint8_t flag = *(m_data + offset + 3);
	flag = flag & 0x7;
	std::string pdn_type;
	if (flag == 1)
		pdn_type = std::string("IPV4");
	if (flag == 2)
		pdn_type = std::string("IPV6");
	if (flag == 3)
		pdn_type = std::string("TPV4IPV6");
	msgObj->gtpV2Data->pdn_type = pdn_type;
	return (ie_length);
}
size_t GTPMessageV2::get_procedure_transact_id(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	uint8_t proc_trans_id = *(m_data + offset +3);
	msgObj->gtpV2Data->procedure_transt_id = proc_trans_id;
	return (ie_length);
}
size_t GTPMessageV2::get_mm_context(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_mm_context_utms_cq(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_mm_context_gsm_cq(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_mm_context_utms_q(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_mm_context_eps_qq(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_mm_context_utms_qq(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;

	return (ie_length);
}
size_t GTPMessageV2::get_pdn_connection_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_pdn_no(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_p_tmsi(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	uint32_t p_tmsi = 0;
	memcpy(&p_tmsi, (m_data + offset + 3), sizeof(uint32_t));
	msgObj->gtpV2Data->p_tmsi = ntohl(p_tmsi);
	return (ie_length);
}
size_t GTPMessageV2::get_p_tmsi_sig(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	char p_tmsi_sig[4] = { 0};
	for(int i = 0; i < 3; i++)
		memcpy(&p_tmsi_sig[i], (m_data + offset +3 + i), sizeof(uint8_t));
	p_tmsi_sig[4] = '\0';
	msgObj->gtpV2Data->p_tmsi_sig = std::string(p_tmsi_sig);
	return (ie_length);
}
size_t GTPMessageV2::get_hop_counter(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	uint8_t hop_counter = *(m_data + offset + 3);
	
	return (ie_length);
}
size_t GTPMessageV2::get_ue_time_zone(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	uint8_t time_zone = *(m_data + offset + 3);
	// in hrs +1 hrs if 1 , +2 hrs if 2
	uint8_t day_light_saving_time = *(m_data + offset + 4) & 0x3;
	msgObj->gtpV2Data->time_zone = time_zone;
	msgObj->gtpV2Data->day_light_saving_time = day_light_saving_time;
	return (ie_length);
}
size_t GTPMessageV2::get_trace_ref(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	offset = offset + 3;
	char* trace_mnc_mcc = get_mnc_mcc_str(m_data, offset);
	char traceid[4] = { 0 };
	for(int i = 0; i < 3; i++)
		memcpy(&traceid[i], (m_data + 3 + i), sizeof(uint8_t));
	msgObj->gtpV2Data->trace_mnc_mcc = std::string(trace_mnc_mcc);
	return (ie_length);
}
size_t GTPMessageV2::get_complete_req_msg(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	uint8_t complete_msg_type = *(m_data + offset + 3);
	return (ie_length);
}
size_t GTPMessageV2::get_GUTI_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	char* guti_mnc_mcc = get_mnc_mcc_str(m_data, offset + 3);
	uint16_t user_grp_id = 0;
	memcpy(&user_grp_id, (m_data + offset + 6), sizeof(uint16_t));
	uint8_t mme_code = *(m_data + offset + 8);
	msgObj->gtpV2Data->guti_mnc_mcc = std::string(guti_mnc_mcc);
	if(guti_mnc_mcc != NULL)
	  delete guti_mnc_mcc;
	msgObj->gtpV2Data->user_grp_id = ntohs(user_grp_id);
	msgObj->gtpV2Data->mme_code = mme_code;
	return (ie_length);
}
size_t GTPMessageV2::get_f_container(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_f_cause(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	uint8_t cause_code = *(m_data + offset + 3) & 0xF;
	return (ie_length);
}
size_t GTPMessageV2::get_plmn_id(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	char* plmn_id = get_mnc_mcc_str(m_data, offset + 3);
	msgObj->gtpV2Data->plmn_id = std::string(plmn_id);
	if(plmn_id != NULL)
	  delete plmn_id;
	return (ie_length);
}
size_t GTPMessageV2::get_target_id(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_pkt_flow_id(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_RAB_context(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	uint8_t nsapi = *(m_data + offset + 3) & 0xf;
	offset = offset + 4;
	uint16_t dl_gtpu_seq_no, ul_gtpu_seq_no, dl_pdcp_seq_no, ul_pdcp_seq_no;
	memcpy(&dl_gtpu_seq_no, (m_data + offset), sizeof(uint16_t));
	memcpy(&ul_gtpu_seq_no, (m_data + offset + 2), sizeof(uint16_t));
	memcpy(&dl_pdcp_seq_no, (m_data + offset + 4), sizeof(uint16_t));
	memcpy(&ul_pdcp_seq_no, (m_data + offset + 6), sizeof(uint16_t));
	
	msgObj->gtpV2Data->dl_gtpu_seq_no = ntohs(dl_gtpu_seq_no);
	msgObj->gtpV2Data->ul_gtpu_seq_no = ntohs(ul_gtpu_seq_no);
	msgObj->gtpV2Data->dl_pdcp_seq_no = ntohs(dl_pdcp_seq_no);
	msgObj->gtpV2Data->ul_pdcp_seq_no = ntohs(ul_pdcp_seq_no);
	
	msgObj->gtpV2Data->nsapi_val = nsapi;
	return (ie_length);
}
size_t GTPMessageV2::get_pdcp_ctx_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_udp_src_port(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	uint16_t port_no = 0;
	memcpy(&port_no, (m_data + offset + 3), sizeof(uint16_t));
	msgObj->gtpV2Data->port_no = ntohs(port_no);
	return (ie_length);
}
size_t GTPMessageV2::get_apn_restriction(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	uint8_t apn_rest = *(m_data + offset + 3);
	return (ie_length);
}
size_t GTPMessageV2::get_selection_mode(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	uint8_t sel_mode = *(m_data + offset + 3) & 0x7;

	if (sel_mode == 4)
	{
		msgObj->gtpV2Data->selection_mode.assign("MS or Network provided APN");
	}
	if (sel_mode == 1)
	{
		msgObj->gtpV2Data->selection_mode.assign("MS provided APN");
	}
	if (sel_mode == 2)
	{
		msgObj->gtpV2Data->selection_mode.assign("Network provided APN");
	}

	return (ie_length);
}
size_t GTPMessageV2::get_src_identifc_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_chng_reporting_action(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_fully_qual_csid(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_chnl_needed_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_emlpp_pri(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_node_type(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_fqdn_name(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_transct_identifier(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_mbms_session_duration(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_mbms_service_area(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_mbms_session_id(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_mbms_flow_id(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_mbms_ip_multicast(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_mbms_distribution_ack(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_rsfp_index(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_UCI_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_csg_info_action(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_csg_id(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_csg_cmi(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_service_indicator(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_detatch_type(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_ldn_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1 || msg_ie_len_h > 400)
		return 3;
	ie_length = msg_ie_len_h + 3;
	char ldn[msg_ie_len_h +1];
	for(int i = 0; i < msg_ie_len_h; i++)
	  memcpy(&ldn, (m_data + offset + 3 + i), sizeof(uint8_t));
	ldn[msg_ie_len_h +1] = '\0';
	msgObj->gtpV2Data->ldn_value = std::string(ldn);
	return (ie_length);
}
size_t GTPMessageV2::get_node_feature(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_mbms_time_to_data_transfer(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_throttling_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_arp_polocy(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_epc_timer(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_sig_priority_indc(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_tmgi_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_additional_mm_ctx_srvcc(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_additional_flags_for_srvcc(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_mmbr(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_mdt_config(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_apco_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_mbms_data_tf_time(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_henb_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_ipv4_profile(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_change_in_report(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_action_indication(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_twan_identifier(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	ie_length = msg_ie_len_h + 3;
	offset = offset + 3;
	uint8_t flags = *(m_data + offset);
	// incr for flag
	offset++;
	uint8_t ssid_length = *(m_data + offset);
	// incr for ssid_length
	offset++;

	char str[(int)ssid_length + 1];
	for(int i =0; i < ssid_length; i++)
	  memcpy(&str, (m_data + offset + i), sizeof(uint8_t));
	str[(int)ssid_length + 1] = '\0';
	offset = offset + ssid_length;
	msgObj->gtpV2Data->twan_ssid = std::string(str);
	
	uint8_t bssid_f, civai_f, plmni_f, opnai_f,laii_f;
	bssid_f = flags & 0x1;
	if (bssid_f)
	{
	  char bssid[7] = { 0 };
	  for(int i =0; i < 6; i++)
	    memcpy(&bssid, (m_data + offset + i), sizeof(uint8_t));
	  offset = offset + 6;
	  msgObj->gtpV2Data->twan_bssid = std::string(bssid);
	}
	civai_f = flags & 0x2;
	if (civai_f)
	{
	    uint8_t civil_aaddr_l = *(m_data + offset);
	    offset++;
	    char cal[(int)civil_aaddr_l + 1];
	    for(int i =0; i < civil_aaddr_l; i++)
	      memcpy(&cal, (m_data + offset + i), sizeof(uint8_t));
	    cal[(int)civil_aaddr_l + 1] = '\0';
	    offset = offset + civil_aaddr_l;
	    msgObj->gtpV2Data->twan_cai = std::string(cal);
	}
	plmni_f = flags & 0x4;
	if (plmni_f)
	{
	    uint32_t twan_plmni_id = 0;
	    memcpy(&twan_plmni_id, (m_data + offset), sizeof(uint32_t));
	    // pktstruct twan_plmni_id
	    offset = offset + 4;
	    msgObj->gtpV2Data->twan_plmni_id = ntohl(twan_plmni_id);
	}
	opnai_f = flags & 0x8;
	if (opnai_f)
	{
 	    uint8_t twan_plmni_ln = *(m_data + offset);
	    offset++;
	    char twan_name[(int)twan_plmni_ln + 1];
	    for(int i =0; i < twan_plmni_ln; i++)
	      memcpy(&twan_name, (m_data + offset + i), sizeof(uint8_t));
	    twan_name[(int)twan_plmni_ln + 1] = '\0';
	    offset = offset + twan_plmni_ln;
	    msgObj->gtpV2Data->twan_name = std::string(twan_name);
	}
	laii_f = flags & 0x10;
	if (laii_f)
	{
	  uint8_t relay_id_type = *(m_data + offset);
	  offset++;
	  std::string relay_type;
	  if(relay_id_type == 0)
	    relay_type = std::string("ipv4 or ipv6");
	  else
	    relay_type = std::string("FQDN");
	  uint8_t relay_len = *(m_data + offset);
	  offset++;
	  char relay_name[(int)relay_len + 1];
	  for(int i =0; i < relay_len; i++)
	      memcpy(&relay_name, (m_data + offset + i), sizeof(uint8_t));
	  relay_name[(int)relay_len + 1] = '\0';
	  offset = offset + relay_len;
	  msgObj->gtpV2Data->relay_type = relay_type;
	  msgObj->gtpV2Data->relay_name = std::string(relay_name);
	}
	return (ie_length);
}
size_t GTPMessageV2::get_uli_timestamp(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_mbms_flag(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_run_nas_cause(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	
	return (ie_length);
}
size_t GTPMessageV2::get_cn_operation_sell_entity(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	
	return (ie_length);
}
size_t GTPMessageV2::wlan_mode_ind(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	
	return (ie_length);
}
size_t GTPMessageV2::get_node_no(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	
	return (ie_length);
}
size_t GTPMessageV2::get_presence_report_act(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	
	return (ie_length);
}
size_t GTPMessageV2::get_presence_report_inf(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_TWAN_id_ts(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_overload_ctl_inf(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_control_inf(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_metric(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_sequence_no(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_apn_rel_cap(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}
size_t GTPMessageV2::get_private_data_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t msg_ie_len; // = (uint16_t)*(m_data + offset);
	memcpy(&msg_ie_len, (m_data + offset), sizeof(uint16_t));
	uint16_t msg_ie_len_h = ntohs(msg_ie_len);
	if (msg_ie_len_h < 1)
		return 3;
	else
		ie_length = msg_ie_len_h + 3;
	// to do break CGI,SAI,RAI,TAI,ECGI,LAI
	return (ie_length);
}


size_t GTPMessageV2::get_rat_info(uint8_t* m_data, uint32_t offset, TPacket *msgObj, bool ul)
{
	size_t ie_length = 0;
	uint16_t mei_len; // = (uint16_t)*(m_data + offset);
	memcpy(&mei_len, (m_data + offset), sizeof(uint16_t));
	uint16_t mei_len_h = ntohs(mei_len);
	if (mei_len_h < 1)
	  return 3;
	ie_length = mei_len_h + 3;
	uint8_t ie_type = *(m_data + offset + 3);
	if ((uint32_t)ie_type > 8)
	  return (ie_length);
//	init_rat_type();
//	intstrmap_V2::iterator it = gtp_rat_type_v2.find((int)ie_type);
//	if (it != gtp_rat_type_v2.end())
//	{
//	  std::string rat_type = std::string(it->second);
//	  msgObj->gtpV2Data->rat_type = rat_type;
//	}
	
	msgObj->gtpV2Data->ratId = ie_type;
	return (ie_length);
	
}

void GTPMessageV2::init_msg_type()
{
	gtp2MsgType.insert(std::pair<int, std::string>(32,  "CREATE SESSION REQUEST"));
	gtp2MsgType.insert(std::pair<int, std::string>(33,  "CREATE SESSION RESPONSE"));
	gtp2MsgType.insert(std::pair<int, std::string>(34,  "MODIFY BEARER REQUEST"));
	gtp2MsgType.insert(std::pair<int, std::string>(35,  "MODIFY BEARER RESPONSE"));
	gtp2MsgType.insert(std::pair<int, std::string>(36,  "DELETE SESSION REQUEST"));
	gtp2MsgType.insert(std::pair<int, std::string>(37,  "DELETE SESSION RESPONSE"));
	gtp2MsgType.insert(std::pair<int, std::string>(95,  "CREATE BEARER REQUEST"));
	gtp2MsgType.insert(std::pair<int, std::string>(96,  "CREATE BEARER RESPONSE"));
	gtp2MsgType.insert(std::pair<int, std::string>(97,  "UPDATE BEARER REQUEST"));
	gtp2MsgType.insert(std::pair<int, std::string>(98,  "UPDATE BEARER RESPONSE"));
	gtp2MsgType.insert(std::pair<int, std::string>(99,  "DELETE BEARER REQUEST"));
	gtp2MsgType.insert(std::pair<int, std::string>(100, "DELETE BEARER RESPONSE"));
}

void GTPMessageV2::init_rat_type()
{
	gtp_rat_type_v2.insert(std::pair<int, std::string>(0, "Reserved"));
	gtp_rat_type_v2.insert(std::pair<int, std::string>(1, "UTRAN"));
	gtp_rat_type_v2.insert(std::pair<int, std::string>(2, "GERAN"));
	gtp_rat_type_v2.insert(std::pair<int, std::string>(3, "WLAN"));
	gtp_rat_type_v2.insert(std::pair<int, std::string>(4, "GAN"));
	gtp_rat_type_v2.insert(std::pair<int, std::string>(5, "HSPA Evolution"));
	gtp_rat_type_v2.insert(std::pair<int, std::string>(6, "EUTRAN"));
	gtp_rat_type_v2.insert(std::pair<int, std::string>(7, "VIRTUAL"));
//	gtp_rat_type_v2.insert(std::pair<int, std::string>(7, "SPARE"));
}

void GTPMessageV2::init_cause_type()
{
	gtp_cause_type_V2.insert(std::pair<int, std::string>(0, std::string(MSG_V2_RSV)));
	gtp_cause_type_V2.insert(std::pair<int, std::string>(1, std::string(MSG_V2_RSV)));
	gtp_cause_type_V2.insert(std::pair<int, std::string>(2, std::string(MSG_LOCAL_DETACH)));
	gtp_cause_type_V2.insert(std::pair<int, std::string>(3, std::string(MSG_COMP_DETACH)));
	gtp_cause_type_V2.insert(std::pair<int, std::string>(4, std::string(MSG_RAT_CHANGE)));
	gtp_cause_type_V2.insert(std::pair<int, std::string>(5, std::string(MSG_ISR_DEACT)));
	gtp_cause_type_V2.insert(std::pair<int, std::string>(6, std::string(MSG_ERR_RNC)));
	gtp_cause_type_V2.insert(std::pair<int, std::string>(7, std::string(MSG_IMSI_DETACH)));
	gtp_cause_type_V2.insert(std::pair<int, std::string>(8, std::string(MSG_REACT_REQ)));
	gtp_cause_type_V2.insert(std::pair<int, std::string>(9, std::string(MSG_PDN_APN_DISALL)));
	gtp_cause_type_V2.insert(std::pair<int, std::string>(10, std::string(MSG_ACCESS_CHANGED)));
	gtp_cause_type_V2.insert(std::pair<int, std::string>(16, std::string(MSG_SUCCESS)));
	gtp_cause_type_V2.insert(std::pair<int, std::string>(100, std::string(MSG_REMOTE_PEER)));
	gtp_cause_type_V2.insert(std::pair<int, std::string>(177, std::string(MSG_PDN_INACTIVITY)));
	gtp_cause_type_V2.insert(std::pair<int, std::string>(192, std::string(MSG_PGW_NOT_RES)));
	gtp_cause_type_V2.insert(std::pair<int, std::string>(193, std::string(MSG_NET_FAIL)));
	gtp_cause_type_V2.insert(std::pair<int, std::string>(194, std::string(MSG_QOS_PAR)));
	gtp_cause_type_V2.insert(std::pair<int, std::string>(210, std::string(MSG_REQ_ACCEPTED)));
	gtp_cause_type_V2.insert(std::pair<int, std::string>(220, std::string(MSG_REQ_ACCP_PART)));
	gtp_cause_type_V2.insert(std::pair<int, std::string>(221, std::string(MSG_NEW_PDN)));
	gtp_cause_type_V2.insert(std::pair<int, std::string>(253, std::string(MSG_NEW_PDN_SIN_ADD))); /* charging */
	gtp_cause_type_V2.insert(std::pair<int, std::string>(255, std::string(MSG_CONTX_NOT_FOUND)));
}

void GTPMessageV2::init_ie_table()
{
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_CAUSE, &get_cause_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_IMSI, &get_imsi_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_REC_REST_CNT, &get_recovery_restr_counter));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_STN_SR, &get_STN_SR_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_SRC_TGT_TRANS_CON, &reserved_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_TGT_SRC_TRANS_CON, &reserved_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_MM_CON_EUTRAN_SRVCC, &reserved_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_MM_CON_UTRAN_SRVCC, &reserved_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_SRVCC_CAUSE, &reserved_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_TGT_RNC_ID, &reserved_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_TGT_GLOGAL_CELL_ID, &get_msisdn_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_TEID_C, &reserved_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_SV_FLAGS, &reserved_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_SAI, &get_private_data_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_MM_CTX_FOR_CS_TO_PS_SRVCC, &reserved_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_APN, &get_access_pt_name_info));

	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_AMBR, &get_ambr_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_EBI, &eps_bearer_id));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IP_ADDRESS, &get_ip_address_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_MEI, &get_mei_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_MSISDN, &get_msisdn_info));
	// length calculation same as tft
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_INDICATION, &get_indication_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_PCO, &get_protocol_config_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_PAA, &get_pdn_access_aloc_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_BEARER_QOS, &get_bearer_qos_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_FLOW_QOS, &get_flow_qos_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_RAT_TYPE, &get_rat_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_SERV_NET, &get_serving_network_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_BEARER_TFT, &get_ebs_bearer_TFT_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_TAD, &get_TAD_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_ULI, &get_user_location_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_F_TEID, &get_f_tied_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_TMSI, &get_TMSI_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_GLOBAL_CNID, &get_global_cn_id));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_S103PDF, &pdn_data_forwarding_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_S1UDF, &S1_udf_data_ford_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_DEL_VAL, &get_delay_value_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_BEARER_CTX, &get_bearer_context_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_CHAR_ID, &get_charging_id_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_CHAR_CHAR, &get_charging_charac_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_TRA_INFO, &get_trace_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_BEARER_FLAG, &get_bearer_flag_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_PDN_TYPE, &get_pdn_type_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_PTI, &get_procedure_transact_id));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_DRX_PARAM, &reserved_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_UE_NET_CAPABILITY, &reserved_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_MM_CONTEXT_GSM_T, &get_mm_context));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_MM_CONTEXT_UTMS_CQ, &get_mm_context_utms_cq));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_MM_CONTEXT_GSM_CQ, &get_mm_context_gsm_cq));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_MM_CONTEXT_UTMS_Q, &get_mm_context_utms_q));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_MM_CONTEXT_EPS_QQ, &get_mm_context_eps_qq));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_MM_CONTEXT_UTMS_QQ, &get_mm_context_utms_qq));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_PDN_CONNECTION, &get_pdn_connection_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_PDN_NUMBERS, &get_pdn_no));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_P_TMSI, &get_p_tmsi));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_P_TMSI_SIG, &get_p_tmsi_sig));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_HOP_COUNTER, &get_hop_counter));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_UE_TIME_ZONE, &get_ue_time_zone));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_TRACE_REFERENCE, &get_trace_ref));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_COMPLETE_REQUEST_MSG, &get_complete_req_msg));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_GUTI, &get_GUTI_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_F_CONTAINER, &get_f_container));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_F_CAUSE, &get_f_cause));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_SEL_PLMN_ID, &get_plmn_id));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_TARGET_ID, &get_target_id));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_PKT_FLOW_ID, &get_pkt_flow_id));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_RAB_CONTEXT, &get_RAB_context));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_S_RNC_PDCP_CTX_INFO, &get_pdcp_ctx_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_UDP_S_PORT_NR, &get_udp_src_port));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_APN_RESTRICTION, &get_apn_restriction));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_SEL_MODE, &get_selection_mode));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_SOURCE_IDENT, &get_src_identifc_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_BEARER_CONTROL_MODE, &reserved_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_CNG_REP_ACT, &get_chng_reporting_action));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_FQ_CSID, &get_fully_qual_csid));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_CHANNEL_NEEDED, &get_chnl_needed_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_EMLPP_PRI, &get_emlpp_pri));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_NODE_TYPE, &get_node_type));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_FQDN, &get_fqdn_name));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_TI, &get_transct_identifier));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_MBMS_SESSION_DURATION, &get_mbms_session_duration));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_MBMS_SERVICE_AREA, &get_mbms_service_area));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_MBMS_SESSION_ID, &get_mbms_session_id));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_MBMS_FLOW_ID, &get_mbms_flow_id));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_MBMS_IP_MC_DIST, &get_mbms_ip_multicast));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_MBMS_DIST_ACK, &get_mbms_distribution_ack));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_RFSP_INDEX, &get_rsfp_index));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_UCI, &get_UCI_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_CSG_INFO_REP_ACTION, &get_csg_info_action));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_CSG_ID, &get_csg_id));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_CMI, &get_csg_cmi));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_SERVICE_INDICATOR, &get_service_indicator));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_DETACH_TYPE, &get_detatch_type));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_LDN, &get_ldn_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_NODE_FEATURES, &get_node_feature));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_MBMS_TIME_TO_DATA_XFER, &get_mbms_time_to_data_transfer));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_THROTTLING, &get_throttling_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_ARP, &get_arp_polocy));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_EPC_TIMER, &get_epc_timer));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_SIG_PRIO_IND, &get_sig_priority_indc));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_TMGI, &get_tmgi_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_ADD_MM_CONT_FOR_SRVCC, &get_additional_mm_ctx_srvcc));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_ADD_FLAGS_FOR_SRVCC, &get_additional_flags_for_srvcc));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_MMBR, &get_mmbr));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_MDT_CONFIG, &get_mdt_config));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_APCO, &get_apco_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_ABS_MBMS_DATA_TF_TIME, &get_mbms_data_tf_time));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_HENB_INFO_REPORT, &get_henb_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_IP4CP, &get_ipv4_profile));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_CHANGE_TO_REPORT_FLAGS, &get_change_in_report));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_ACTION_INDICATION, &get_action_indication));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_TWAN_IDENTIFIER, &get_twan_identifier));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_ULI_TIMESTAMP, &get_uli_timestamp));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_MBMS_FLAGS, &get_mbms_flag));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_RAN_NAS_CAUSE, &get_run_nas_cause));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_CN_OP_SEL_ENT, &get_cn_operation_sell_entity));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_TRUST_WLAN_MODE_IND, &wlan_mode_ind));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_NODE_NUMBER, &get_node_no));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_NODE_IDENTIFIER, &get_node_no));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_PRES_REP_AREA_ACT, &get_presence_report_act));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_PRES_REP_AREA_INF, &get_presence_report_inf));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_TWAN_ID_TS, &get_TWAN_id_ts));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_OVERLOAD_CONTROL_INF, &get_overload_ctl_inf));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_LOAD_CONTROL_INF, &get_control_inf));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_METRIC, &get_metric));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_SEQ_NO, &get_sequence_no));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_APN_AND_REL_CAP, &get_apn_rel_cap));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_PRIVATE_EXT, &get_private_data_info));
	ie_table_V2.insert(std::pair<int, pfn_V2>(GTPV2_IE_PAGING_CAUSE, &reserved_info));
}
