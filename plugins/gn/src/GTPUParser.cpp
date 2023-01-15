/*
 * GTPUParser.cpp
 *
 *  Created on: 02-Aug-2016
 *      Author: deb
 */

#include "GTPUParser.h"
#include <string>
#include "GTPGlobal.h"

using namespace std;

GTPUParser::GTPUParser() {
	tcpParser = new TCPParser();
	udpParser = new UDPParser();
	otrParser = new OtherIPV4Parser();
	dnsData = new DnsData();
	iph = NULL;
	hdr = 0;
	packet = NULL;
	this->_name = "GTPUParser";
	setLogLevel(Log::theLog().level());
}

GTPUParser::~GTPUParser() {
	delete (otrParser);
	delete (tcpParser);
	delete (udpParser);
	delete (dnsData);
}

static void hexDumpGTPu(const void* pv, int len)
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

VOID GTPUParser::parsePacket(const BYTE pkt, MPacket *msgObj)
{
	uint16_t   gtpHeaderByte = 0;

	packet = pkt + 8;

	if ((VAL_BYTE(packet) & 0xF8) != 0x30 ) {
//		TheLog_v1(Log::Info,name()," Packet No.#%d **** Invalid Flag", IPGlobal::t_FrameCount);
//		printf(" **** GTPU Invalid Flag\n");
		msgObj->ipAppProtocol = 0;
		return;
	}

	hdr = getGTPHeader();

	// Process only MsgType = 255 (T-PDUs)
	// 1 & 2 - "Echo" messages
	// 26    - "Error Indication" message.
	// 31    - "Supported Extension Headers Notification" message.

	if(hdr->MsgType != GTPParser_GTP_GPDU) {
		msgObj->ipAppProtocol = 0;
		return;
	}

	/* Check Sequence No Present or not */
	if (VAL_BYTE(packet) == 0x32) 	// Present (To retrive VAL_USHORT(this->packet + 8))
		gtpHeaderByte = 12;
	else									// Not Present
		gtpHeaderByte = 8;

	switch(hdr->Version)
	{
			case GTPv1:
//					msgObj->gtpcPktTunnelId = ntohl(hdr->MsgTeid);		//Header Tunnel Id
					msgObj->gtpcPktTunnelId = VAL_ULONG(packet + 4);
					parseGTPuIP(packet + gtpHeaderByte, msgObj);
					break;

			default:
					msgObj->ipAppProtocol = 0;
					break;
	}
}

VOID GTPUParser::parseGTPuIP(const BYTE pkt, MPacket *msgObj)
{
	struct iphdr* iph = (struct iphdr *)(pkt);

	//45
	//00
	//00 60 - len
	//1c 2b - identification
	//00 - flag
	//00 - offset
	//7e - ttl
	//11 - protocol
	//c5 cb - checksum
	//da f8 52 7e - source ip
	//da f8 52 27 - dest ip
	//08 68 08 68 ---

	msgObj->ipVer 			= iph->version;

	if(msgObj->ipVer != 4)
		return;

	msgObj->ipTLen 		= ntohs((uint16_t)iph->tot_len);
	msgObj->ipHLen 		= ((unsigned int)iph->ihl)*4;
	msgObj->ipProtocol 	= iph->protocol; // TCP or UDP
	msgObj->ipTtl 		= iph->ttl;

    int offset = 12;

//    printf("1 %s ",B2H[pkt[offset+3] >> 4]);
//    printf("2 %s\n",B2H[pkt[offset+3] & 0x0f]);
//
//    sprintf(msgObj->sourceAddr, "%02x%02x%02x%02x", pkt[offset+3], pkt[offset + 2], pkt[offset + 1], pkt[offset]);
//	offset += 4;
//	sprintf(msgObj->destAddr, "%02x%02x%02x%02x", pkt[offset+3], pkt[offset + 2], pkt[offset + 1], pkt[offset]);
//
//	printf("IP %s\n",msgObj->sourceAddr);
//	exit(0);

	msgObj->ipSourceAddr=(msgObj->ipSourceAddr << 8) + (0xff & pkt[offset]);
	msgObj->ipSourceAddr=(msgObj->ipSourceAddr << 8) + (0xff & pkt[offset + 1]);
	msgObj->ipSourceAddr=(msgObj->ipSourceAddr << 8) + (0xff & pkt[offset + 2]);
	msgObj->ipSourceAddr=(msgObj->ipSourceAddr << 8) + (0xff & pkt[offset + 3]);

	offset += 4;
	msgObj->ipDestAddr=(msgObj->ipDestAddr << 8) + (0xff & pkt[offset]);
	msgObj->ipDestAddr=(msgObj->ipDestAddr << 8) + (0xff & pkt[offset + 1]);
	msgObj->ipDestAddr=(msgObj->ipDestAddr << 8) + (0xff & pkt[offset + 2]);
	msgObj->ipDestAddr=(msgObj->ipDestAddr << 8) + (0xff & pkt[offset + 3]);

//	msgObj->ipSourceAddr = VAL_ULONG(pkt+12);
//	msgObj->ipDestAddr 	 = VAL_ULONG(pkt+16);


    parseNextLayer(pkt + msgObj->ipHLen, msgObj);

    iph = NULL;
}

VOID GTPUParser::parseNextLayer(const BYTE packet, MPacket *msgObj)
{
	switch(msgObj->ipProtocol)
	{
		case IPPROTO_TCP:		//  Transmission Control Protocol
					tcpParser->parsePacket(packet, msgObj);
					break;


		case IPPROTO_UDP:		//User Datagram Protocol
					udpParser->parsePacket(packet, msgObj);
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
//					otrParser->parsePacket(packet, msgObj);
					break;
		default:
					return;
	}
}

VOID GTPUParser::getIPDirection(MPacket *msgObj)
{
//    int rangeLen = 0;
//    std::string ipInList;
 //   ULONG address;
//
//	for(auto elem : IPGlobal::IPRange)
//	{
//		if(msgObj->ipSourceAddr >= elem.first && msgObj->ipSourceAddr <= elem.second) {
//			msgObj->isUpDir = true;
//			break;
//		}
//		else if(msgObj->ipDestAddr >= elem.first && msgObj->ipDestAddr <= elem.second) {
//			msgObj->isUpDir = false;
//			break;
//		}
//	}
}
