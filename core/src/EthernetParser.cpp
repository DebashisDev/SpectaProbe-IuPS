/*
 * EthernetProbe.cpp
 *
 *  Created on: 30-Jan-2016
 *      Author: deb
 */

#include <sys/time.h>

#include "EthernetParser.h"

EthernetParser::EthernetParser(int intfid, int rId)
{
	this->_name = "EthernetParser";
	this->setLogLevel(Log::theLog().level());

	this->interfaceId = intfid;
	this->routerId = rId;

	tcp 	= new TCPParser();
	udp 	= new UDPParser();
	gtpc 	= new GTPCParser();
	gtpu 	= new GTPUParser();
	sctp	= new SCTPParser();
	iph = NULL;
	tcpHeader = NULL;
	udpHeader = NULL;


	destMacAddr[0] = sourceMacAddr[0] = '\0';
	ptr_vlan_t = NULL;
	packet_size = user_p = canonical_f = vlan_id = type = vlan_tpid = 0;
	exp = stack = "";
}

EthernetParser::~EthernetParser() {
	delete (tcp);
	delete (udp);
	delete (gtpc);
	delete (gtpu);
	delete (sctp);
}

static void hexDump(const void* pv, int len)
{
  const unsigned char* p = (const unsigned char*) pv;
  int i;
  for( i = 0; i < len; ++i ) {
    const char* eos;
    switch( i & 15 ) {
    case 0:
      printf("%08x  ", i);
      eos = "";
      break;
    case 1:
      eos = " ";
      break;
    case 15:
      eos = "\n";
      break;
    default:
      eos = (i & 1) ? " " : "";
      break;
    }
    printf("%02x%s", (unsigned) p[i], eos);
  }
  printf(((len & 15) == 0) ? "\n" : "\n\n");
}

VOID EthernetParser::parsePacket(const BYTE packet, MPacket *msgObj)
{
    sprintf(msgObj->ethDestMACAddr, "%02x:%02x:%02x:%02x:%02x:%02x", packet[0], packet[1], packet[2], packet[3], packet[4], packet[5]);
    sprintf(msgObj->ethSourceMACAddr, "%02x:%02x:%02x:%02x:%02x:%02x", packet[6], packet[7], packet[8], packet[9], packet[10], packet[11]);

    bool dirFound = false;

    if(GContainer::config->GN_PROBE)
    {
		for(int i=0; i<IPGlobal::SRC_MAC_NOS; i++){
			if(strcmp(msgObj->ethSourceMACAddr, IPGlobal::SGSN_MAC[i]) == 0){
				msgObj->dirUserNetwork = true;
				dirFound = true;
			}else if(strcmp(msgObj->ethDestMACAddr, IPGlobal::SGSN_MAC[i]) == 0){
				msgObj->dirUserNetwork = false;
				dirFound = true;
			}
			if(dirFound) break;
		}
		if(!dirFound){
			for(int i=0; i<IPGlobal::DST_MAC_NOS; i++){
				if(strcmp(msgObj->ethDestMACAddr, IPGlobal::GGSN_MAC[i]) == 0){
					msgObj->dirUserNetwork = true;
					dirFound = true;
				}else if(strcmp(msgObj->ethSourceMACAddr, IPGlobal::GGSN_MAC[i]) == 0){
					msgObj->dirUserNetwork = false;
					dirFound = true;
				}
				if(dirFound) break;
			}
		}
    }
    else if(GContainer::config->IUPS_PROBE)
    {
//    	for(int i=0; i<IPGlobal::SRC_MAC_NOS; i++){
//			if(strcmp(msgObj->ethSourceMACAddr, IPGlobal::RNC_MAC[i]) == 0){
//				msgObj->dirUserNetwork = true;
//				dirFound = true;
//			}else if(strcmp(msgObj->ethDestMACAddr, IPGlobal::RNC_MAC[i]) == 0){
//				msgObj->dirUserNetwork = false;
//				dirFound = true;
//			}
//			if(dirFound) break;
//		}
//		if(!dirFound){
			for(int i=0; i<IPGlobal::DST_MAC_NOS; i++){
				if(strcmp(msgObj->ethDestMACAddr, IPGlobal::SGSN_MAC[i]) == 0){
					msgObj->dirUserNetwork = true;
					dirFound = true;
				}else if(strcmp(msgObj->ethSourceMACAddr, IPGlobal::SGSN_MAC[i]) == 0){
					msgObj->dirUserNetwork = false;
					dirFound = true;
				}
				if(dirFound) break;
			}
//		}
    }


//    if(!dirFound){
//    	printf("**** DIR NOT FOUND FOR MACS [%s] [%s]\n",msgObj->ethSourceMACAddr, msgObj->ethDestMACAddr);
//    	TheLog_nc_v2(Log::Warn, name(),"**** DIR NOT FOUND FOR MACS [%s] [%s]",msgObj->ethSourceMACAddr, msgObj->ethDestMACAddr);
//    }

    uint16_t protocol = packet[12] * 256 + packet[13];		/* Ethernet Containing Protocol */
    uint16_t len = sizeof(struct ether_header);				/* Ethernet Packet Size */

    switch(protocol)
    {
    	case ETH_P_IP:
    		parseIPV4Packet(packet + len, msgObj);
    		break;

    	case ETH_P_8021Q:
    		parse8021QPacket(packet + len, msgObj);
    		break;

    	case ETH_P_MPLS:
    		parseMPLSPacket(packet + len, msgObj);
    		break;

    	default:
    //		TheLog_v1(Log::Error, name(),"!!! UNKNOWN UNKNOWN Protocol ID %d Skipping in Ethernet", protocolId);
//    		printf("UNKNOWN Protocol\n");
    		break;
    }
}

/*
 	MultiProtocol Label Switching Header, Label: 221658, Exp: 0, S: 1, TTL: 255
    0011 0110 0001 1101 1010 .... .... .... = MPLS Label: 221658
    .... .... .... .... .... 000. .... .... = MPLS Experimental Bits: 0
    .... .... .... .... .... ...1 .... .... = MPLS Bottom Of Label Stack: 1
    .... .... .... .... .... .... 1111 1111 = MPLS TTL: 255
*/

VOID EthernetParser::parseMPLSPacket(const BYTE packet, MPacket *msgObj) {

//	uint16_t offset = 0;
//	msgObj->mplsLevel = VAL_USHORT(packet + offset); // 0011 0110 0001 1101 (2 Bytes)
//	offset += 2;
//	int level = VAL_BYTE(packet + offset);			 // 1010 0001 (1 byte)
//	offset += 1;
//
//	msgObj->mplsLevel = (msgObj->mplsLevel<<4) + (level>>4);
//	int level2 = level&0x0f;
//
//	string ret = getBits(level2);
//	for(int length = 1; length < ret.length(); length++)
//	{
//		if(length <= 3) exp += ret[length];
//		else
//			stack = ret[length];
//	}
//	msgObj->mplsBits = atoi(exp.c_str());
//	msgObj->mplsStack = atoi(stack.c_str());
//	msgObj->mplsTtl = VAL_BYTE(packet + offset);

//	printf(" Experimental::%s| Stack::%s| TTL::%d\n",exp.c_str(), stack.c_str(), TTL);
	parseIPV4Packet(packet + MPLS_PACKET_SIZE, msgObj);
}

VOID EthernetParser::parse8021QPacket(const BYTE packet, MPacket *msgObj)
{
	ptr_vlan_t = (struct vlan_tag*)packet;
	packet_size = sizeof(struct vlan_tag);
	vlan_tpid = ntohs((unsigned short int)ptr_vlan_t->vlan_tpid);
	vlan_id = (uint16_t)(vlan_tpid & 0x0FFF);
	type = ntohs((unsigned short int)ptr_vlan_t->vlan_tci);

	msgObj->ethVLanId = vlan_id;

	if(type == ETH_P_IP)
		parseIPV4Packet(packet + packet_size, msgObj);
}

// - IPv4 Parsing

void EthernetParser::parseIPV4Packet(const BYTE packet, MPacket *msgObj)
{
		uint16_t offset = 12;
		iph = (struct iphdr *)(packet);
		char	SouceIP[5];
		int i = 0;

		msgObj->ipTLen 		= ntohs((uint16_t)iph->tot_len);
		msgObj->ipHLen 		= ((unsigned int)iph->ihl)*4;

		msgObj->ipVer 			= iph->version;
		msgObj->ipProtocol 		= iph->protocol; // TCP or UDP
		msgObj->ipAppProtocol 	= iph->protocol; // TCP or UDP

		msgObj->ipTtl 		= iph->ttl;

//		msgObj->ipSourceAddr = VAL_ULONG(packet + offset);

		msgObj->ipSourceAddr=(msgObj->ipSourceAddr << 8) + (0xff & packet[offset]);
		msgObj->ipSourceAddr=(msgObj->ipSourceAddr << 8) + (0xff & packet[offset + 1]);
		msgObj->ipSourceAddr=(msgObj->ipSourceAddr << 8) + (0xff & packet[offset + 2]);
		msgObj->ipSourceAddr=(msgObj->ipSourceAddr << 8) + (0xff & packet[offset + 3]);

		offset += 4;
//		msgObj->ipDestAddr 	 = VAL_ULONG(packet + offset);

		msgObj->ipDestAddr=(msgObj->ipDestAddr << 8) + (0xff & packet[offset]);
		msgObj->ipDestAddr=(msgObj->ipDestAddr << 8) + (0xff & packet[offset + 1]);
		msgObj->ipDestAddr=(msgObj->ipDestAddr << 8) + (0xff & packet[offset + 2]);
		msgObj->ipDestAddr=(msgObj->ipDestAddr << 8) + (0xff & packet[offset + 3]);


		if(GContainer::config->GN_PROBE)
		{
			if(msgObj->ipAppProtocol == PACKET_IPPROTO_UDP) {
				getGTPProtocolType(packet, msgObj);
				switch(msgObj->ipAppProtocol)
				{
					case PACKET_IPPROTO_GTPC:
					case PACKET_IPPROTO_GTPU:
							parseNextLayer(packet + msgObj->ipHLen, msgObj);
							break;

					default:
							break;
				}
			}
		}
		else if(GContainer::config->IUPS_PROBE)
		{
			if(msgObj->ipAppProtocol == PACKET_IPPROTO_SCTP)
				parseNextLayer(packet + msgObj->ipHLen, msgObj);
		}

//		msgObj->ipSessionKeySrc = ((SESSION_KEY_MULTI_1 + msgObj->ipSourceAddr) * SESSION_KEY_MULTI_2) + msgObj->protoSourcePort;
//		msgObj->ipSessionKeyDest = ((SESSION_KEY_MULTI_1 + msgObj->ipDestAddr) * SESSION_KEY_MULTI_2) + msgObj->protoDestPort;

//		else if(GContainer::config->GX_PROBE && msgObj->ipAppProtocol == PACKET_IPPROTO_TCP)
//		{
//			getGxProtocolType(packet, msgObj);
//			getDirection(msgObj);
//		}

}

//VOID EthernetParser::getGxProtocolType(const BYTE packet, MPacket *msgObj)
//{
//	tcpHeader = (struct tcphdr *)(packet + msgObj->ipHLen);
//	msgObj->protoHLen = ((tcpHeader->doff) << 2);
//	msgObj->protoSourcePort = ntohs((unsigned short int)tcpHeader->source);
//	msgObj->protoDestPort = ntohs((unsigned short int)tcpHeader->dest);
//
	if((msgObj->protoSourcePort == GX_PORT) || (msgObj->protoDestPort == GX_PORT))
//	{
//		msgObj->ipProtocol = PACKET_IPPROTO_GX;
//	}
//	else
//	{
//		msgObj->ipProtocol = 0;
//	}
//}

VOID EthernetParser::getGTPProtocolType(const BYTE packet, MPacket *msgObj)
{
	uint16_t	s_port, d_port;
	s_port = d_port = 0;

	struct udphdr *udpHeader = (struct udphdr *)(packet + msgObj->ipHLen);

	s_port = ntohs((unsigned short int)udpHeader->source);
	d_port = ntohs((unsigned short int)udpHeader->dest);

	msgObj->gtpcMsgLen = ntohs((unsigned short int)udpHeader->len);

	if((s_port == GTPC_PORT) || (s_port == GTPC_PORT1))
	{
		msgObj->gtpSGSNAddr = msgObj->ipDestAddr;
		msgObj->gtpGGSNAddr = msgObj->ipSourceAddr;
		msgObj->gtpSGSNPort = d_port;
		msgObj->gtpGGSNPort = s_port;
		msgObj->ipAppProtocol = PACKET_IPPROTO_GTPC;
//		msgObj->isUpDir = true;
	}
	else if((d_port == GTPC_PORT) || (d_port == GTPC_PORT1))
	{
		msgObj->gtpGGSNAddr = msgObj->ipDestAddr;
		msgObj->gtpSGSNAddr = msgObj->ipSourceAddr;
		msgObj->gtpGGSNPort = d_port;
		msgObj->gtpSGSNPort = s_port;
		msgObj->ipAppProtocol = PACKET_IPPROTO_GTPC;
//		msgObj->isUpDir = false;
	}
	else if(s_port == GTPU_PORT)
	{
		msgObj->gtpSGSNAddr = msgObj->ipSourceAddr;
		msgObj->gtpGGSNAddr = msgObj->ipDestAddr;
		msgObj->gtpSGSNPort = s_port;
		msgObj->gtpGGSNPort = d_port;
		msgObj->ipAppProtocol = PACKET_IPPROTO_GTPU;
//		msgObj->isUpDir = true;
	}
	else if(d_port == GTPU_PORT)
	{
		msgObj->gtpGGSNAddr = msgObj->ipSourceAddr;
		msgObj->gtpSGSNAddr = msgObj->ipDestAddr;
		msgObj->gtpGGSNPort = s_port;
		msgObj->gtpSGSNPort = d_port;
		msgObj->ipAppProtocol = PACKET_IPPROTO_GTPU;
//		msgObj->isUpDir = false;
	}
	if((s_port == RADIUS_AUTH) || (s_port == RADIUS_ACCO) || (s_port == RADIUS_AUTH1) || (s_port == RADIUS_ACCO1)) {
//		msgObj->radiusData->s_port = s_port;
//		msgObj->radiusData->d_port = d_port;
//		msgObj->radiusData->sourceAddr = msgObj->ipData->s_addr_long;
//		msgObj->radiusData->destAddr = msgObj->ipData->d_addr_long;
//
//		msgObj->ipData->protocol = PACKET_IPPROTO_RADIUS;
//		msgObj->radiusData->direction = DOWN_WARDS;
	}
	else if((d_port == RADIUS_AUTH) || (d_port == RADIUS_ACCO) || (d_port == RADIUS_AUTH1) || (d_port == RADIUS_ACCO1)) {
//		msgObj->radiusData->s_port = s_port;
//		msgObj->radiusData->d_port = d_port;
//		msgObj->radiusData->sourceAddr = msgObj->ipData->s_addr_long;
//		msgObj->radiusData->destAddr = msgObj->ipData->d_addr_long;
//		msgObj->ipData->protocol = PACKET_IPPROTO_RADIUS;
//		msgObj->radiusData->direction = UP_WARDS;
	}

}

VOID EthernetParser::parseNextLayer(const BYTE packet, MPacket *msgObj)
{
	switch(msgObj->ipAppProtocol)
	{
		case PACKET_IPPROTO_TCP:
//					tcp->parsePacket(packet, msgObj);
					break;

		case PACKET_IPPROTO_UDP:
//					udp->parsePacket(packet, msgObj);
					break;

		case PACKET_IPPROTO_GTPC:
					gtpc->parsePacket(packet, msgObj);
					break;

		case PACKET_IPPROTO_GTPU:
					gtpu->parsePacket(packet, msgObj);
					break;

//		case PACKET_IPPROTO_GX:
//					gx->parsePacket(packet, msgObj);
//					break;

		case PACKET_IPPROTO_RADIUS:
//					radius->parsePacket(packet, msgObj);
					break;

		case PACKET_IPPROTO_ICMP: 		// Internet Control Message Protocol.
		case PACKET_IPPROTO_IGMP: 		// Internet Group management Protocol.
		case PACLET_IPPROTO_EGP: 		// Exterior Gateway Protocol.
		case PACKET_IPPROTO_PUP: 		// PUP Protocol.
		case PACKET_IPPROTO_IDP: 		// XNS IDP protocol.
		case PACKET_IPPROTO_TP: 		// SO Transport Protocol Class 4.
		case PACKET_IPPROTO_IPV6: 		//IPv6 header.
		case PACKET_IPPROTO_ROUTING: 	//IPv6 Routing header.
		case PACKET_IPPROTO_FRAGMENT: 	//IPv6 fragmentation header.
		case PACKET_IPPROTO_RSVP: 		//Reservation Protocol.
		case PACKET_IPPROTO_GRE: 		//General Routing Encapsulation.
		case PACKET_IPPROTO_ESP: 		//encapsulating security payload.
		case PACKET_IPPROTO_AH: 		//Authentication header.
		case PACKET_IPPROTO_ICMPV6: 	//ICMPV6.
		case PACKET_IPPROTO_NONE: 		//IPv6 no next header.
		case PACKET_IPPROTO_DSTOPTS: 	//IPv6 destination options.
		case PACKET_IPPROTO_MTP: 		//Multicast Transport Protocol.
		case PACKET_IPPROTO_ENCAP:	 	//Encapsulation Header.
		case PACKET_IPPROTO_PIM: 		//Protocol Independent Multicast.
		case PACKET_IPPROTO_COMP: 		//Compression Header Protocol.
		case PACKET_IPPROTO_UDPLITE: 	//UDP-Lite protocol.
		case PACKET_IPPROTO_RAW: 		//Raw IP Packets.
//					otr->parsePacket(packet, msgObj);
					break;

        case PACKET_IPPROTO_SCTP:
        			if(GContainer::config->IUPS_PROBE)
        				sctp->parsePacket(packet, msgObj);
        			break;

		default:
					break;
	}
}

string EthernetParser::getBits(unsigned int x)
{
  string ret;
  for (unsigned int mask=0x10; mask; mask>>=1) {
    ret += (x & mask) ? "1" : "0";
  }
  return ret;
}


//VOID EthernetParser::getDirection(MPacket *msgObj)
//{
//	int rangeLen = 0;
//	std::string ipInList;
//	bool dirSet = false;
//
////    for (unsigned counter = 0; counter < IPGlobal::ipRange.size(); ++counter)
////    {
////    	ipInList = IPGlobal::ipRange.at(counter);
////    	rangeLen = ipInList.length();
////    	if(msgObj->ipData->sourceAddr.compare(0, rangeLen, ipInList) == 0)
////    	{
////    		msgObj->ipData->direction = UP_WARDS;
////    		printf("Source IP:: %s - UP\n", msgObj->ipData->sourceAddr.c_str());
////    		dirSet = true;
////    		break;
////
////    	}else if(msgObj->ipData->destAddr.compare(0, rangeLen, ipInList) == 0)
////    	{
////    		msgObj->ipData->direction = DOWN_WARDS;
////    		printf("Destination IP:: %s - DOWN\n", msgObj->ipData->destAddr.c_str());
////    		dirSet = true;
////    		break;
////    	}
////    }
//
//    if(!dirSet)
//    {
//    	msgObj->DirSgsnGgsn = false;
//    }
//}


