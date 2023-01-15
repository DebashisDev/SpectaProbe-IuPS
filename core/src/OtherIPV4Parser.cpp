/*
 * OtherIPV4Parser.cpp
 *
 *  Created on: 18-Jul-2016
 *      Author: deb
 */

#include "OtherIPV4Parser.h"


OtherIPV4Parser::OtherIPV4Parser() {

}

OtherIPV4Parser::~OtherIPV4Parser() {
}

VOID
OtherIPV4Parser::parsePacket(const BYTE packet, MPacket *msgObj)
{
	switch(msgObj->ipProtocol)
	{
		case IPPROTO_ICMP: // Internet Control Message Protocol.
				msgObj->ipAppProtocol = IPPROTO_ICMP;
				break;

		case IPPROTO_IGMP: // Internet Group management Protocol.
				msgObj->ipAppProtocol = IPPROTO_IGMP;
				break;

		case IPPROTO_EGP: // Exterior Gateway Protocol.
				msgObj->ipAppProtocol = IPPROTO_EGP;
				break;

		case IPPROTO_PUP: // PUP Protocol.
				msgObj->ipAppProtocol = IPPROTO_PUP;
				break;

		case IPPROTO_IDP: // XNS IDP protocol.
				msgObj->ipAppProtocol = IPPROTO_IDP;
				break;

		case IPPROTO_TP: // SO Transport Protocol Class 4.
				msgObj->ipAppProtocol = IPPROTO_TP;
				break;

		case IPPROTO_IPV6: //IPv6 header.
				msgObj->ipAppProtocol = IPPROTO_IPV6;
				break;

		case IPPROTO_ROUTING: //IPv6 Routing header.
				msgObj->ipAppProtocol = IPPROTO_ROUTING;
				break;

		case IPPROTO_FRAGMENT: //IPv6 fragmentation header.
				msgObj->ipAppProtocol = IPPROTO_FRAGMENT;
				break;

		case IPPROTO_RSVP: //Reservation Protocol.
				msgObj->ipAppProtocol = IPPROTO_RSVP;
				break;

		case IPPROTO_GRE: //General Routing Encapsulation.
				msgObj->ipAppProtocol = IPPROTO_GRE;
				break;

		case IPPROTO_ESP: //encapsulating security payload.
				msgObj->ipAppProtocol = IPPROTO_ESP;
				break;

		case IPPROTO_AH: //Authentication header.
				msgObj->ipAppProtocol = IPPROTO_AH;
				break;

		case IPPROTO_ICMPV6: //ICMPV6.
				msgObj->ipAppProtocol = IPPROTO_ICMPV6;
				break;

		case IPPROTO_NONE: //IPv6 no next header.
				msgObj->ipAppProtocol = IPPROTO_NONE;
				break;

		case IPPROTO_DSTOPTS: //IPv6 destination options.
				msgObj->ipAppProtocol = IPPROTO_DSTOPTS;
				break;

		case IPPROTO_MTP: //Multicast Transport Protocol.
				msgObj->ipAppProtocol = IPPROTO_MTP;
				break;

		case IPPROTO_ENCAP: //Encapsulation Header.
				msgObj->ipAppProtocol = IPPROTO_ENCAP;
				break;

		case IPPROTO_PIM: //Protocol Independent Multicast.
				msgObj->ipAppProtocol = IPPROTO_PIM;
				break;

		case IPPROTO_COMP: //Compression Header Protocol.
				msgObj->ipAppProtocol = IPPROTO_COMP;
				break;

//		case IPPROTO_SCTP: //Stream Control Transmission Protocol.
//				msgObj->ipAppProtocol = IPPROTO_SCTP;
//				break;

		case IPPROTO_UDPLITE: //UDP-Lite protocol.
				msgObj->ipAppProtocol = IPPROTO_UDPLITE;
				break;

		case IPPROTO_RAW: //Raw IP Packets.
				msgObj->ipAppProtocol = IPPROTO_RAW;
				break;

		case IPPROTO_HOPOPTS:
				msgObj->ipAppProtocol = IPPROTO_HOPOPTS;
				break;

	}
}
