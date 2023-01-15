/*
 * ICMP.h
 *
 *  Created on: Apr 26, 2016
 *      Author: root
 */

#ifndef SRC_ICMP_H_
#define SRC_ICMP_H_

#include <netinet/icmp6.h>
#include <netinet/ip_icmp.h>

#include "BaseConfig.h"
#include "IPGlobal.h"

#define	 MAX_ICMP_TYPE 260
#define  ICMP_V4		4
#define  ICMP_V6		6
#define randomQueue	rand() % 2 + 0

class ICMP {
public:
	ICMP();
	~ICMP();

	void parsePacket(const BYTE packet, TPacket *msgObj, uint16_t ver);

	char *icmp6Type[300] = {
					"Reserved",						//0
					"Destination Unreachable",		//1
					"Packet Too Big",				//2
					"Time Exceeded",				//3
					"Parameter Problem",			//4
					"Unassigned",					//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//10
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//20
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//30
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//40
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//50
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//60
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//70
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//80
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//90
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Private experimentation",		//100
					"Private experimentation",		//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//110
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//120
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Expansion of ICMPv6 error messages",						//7
					"Echo Request",						//8
					"Echo Reply",						//9
					"Multicast Listener Query",			//130
					"Multicast Listener Report",		//1
					"Multicast Listener Done",			//2
					"Router Solicitation (NDP)",		//3
					"Router Advertisement (NDP)",		//4
					"Neighbor Solicitation (NDP)",		//5
					"Neighbor Advertisement (NDP)",		//6
					"Redirect Message (NDP)",			//7
					"Router Renumbering",				//8
					"ICMP Node Information Query",		//9
					"ICMP Node Information Response",	//140
					"Inverse Neighbor Discovery Solicitation Message",	//1
					"Inverse Neighbor Discovery Advertisement Message",	//2
					"Multicast Listener Discovery",						//3
					"Home Agent Address Discovery Request Message",		//4
					"Home Agent Address Discovery Reply Message",		//5
					"Mobile Prefix Solicitation",						//6
					"Mobile Prefix Advertisement",						//7
					"Certification Path Solicitation (SEND)",			//8
					"Certification Path Advertisement (SEND)",			//9
					"ICMP messages utilized by experimental mobility protocols",	//150
					"Multicast Router Advertisement (MRD)",				//1
					"Multicast Router Solicitation (MRD)",				//2
					"Multicast Router Termination (MRD)",				//3
					"FMIPv6 Messages",						//4
					"RPL Control Message",						//5
					"ILNPv6 Locator Update Message",						//6
					"Duplicate Address Request",						//7
					"Duplicate Address Confirmation",						//8
					"MPL Control Message",						//9
					"Unassigned",						//160
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//170
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//180
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//190
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Private experimentation",						//200
					"Private experimentation",						//1
					"Unknown",						//2
					"Unknown",						//3
					"Unknown",						//4
					"Unknown",						//5
					"Unknown",						//6
					"Unknown",						//7
					"Unknown",						//8
					"Unknown",						//9
					"Unknown",						//210
					"Unknown",						//1
					"Unknown",						//2
					"Unknown",						//3
					"Unknown",						//4
					"Unknown",						//5
					"Unknown",						//6
					"Unknown",						//7
					"Unknown",						//8
					"Unknown",						//9
					"Unknown",						//220
					"Unknown",						//1
					"Unknown",						//2
					"Unknown",						//3
					"Unknown",						//4
					"Unknown",						//5
					"Unknown",						//6
					"Unknown",						//7
					"Unknown",						//8
					"Unknown",						//9
					"Unknown",						//230
					"Unknown",						//1
					"Unknown",						//2
					"Unknown",						//3
					"Unknown",						//4
					"Unknown",						//5
					"Unknown",						//6
					"Unknown",						//7
					"Unknown",						//8
					"Unknown",						//9
					"Unknown",						//240
					"Unknown",						//1
					"Unknown",						//2
					"Unknown",						//3
					"Unknown",						//4
					"Unknown",						//5
					"Unknown",						//6
					"Unknown",						//7
					"Unknown",						//8
					"Unknown",						//9
					"Unknown",						//250
					"Unknown",						//1
					"Unknown",						//2
					"Unknown",						//3
					"Unknown",						//4
					"Reserved for expansion of ICMPv6 informational messages",						//5
					"Unknown",						//6
					"Unknown",						//7
					"Unknown",						//8
					"Unknown",						//9
					"Unknown"						//260
	};

	char *icmp4Type[300] = {
					"Echo Reply",								//0
					"Unassigned",								//1
					"Unassigned",								//2
					"Destination Unreachable",					//3
					"Source Quench (Deprecated)",				//4
					"Redirect",									//5
					"Alternate Host Address (Deprecated)",		//6
					"Unassigned",								//7
					"Echo",										//8
					"Router Advertisement",						//9
					"Router Solicitation",						//10
					"Time Exceeded",							//1
					"Parameter Problem",						//2
					"Timestamp",								//3
					"Timestamp Reply",							//4
					"Information Request (Deprecated)",			//5
					"Information Reply (Deprecated)",			//6
					"Address Mask Request (Deprecated)",		//7
					"Address Mask Reply (Deprecated)",			//8
					"Reserved (for Security)",					//9
					"Reserved",						//20
					"Reserved",						//1
					"Reserved",						//2
					"Reserved",						//3
					"Reserved",						//4
					"Reserved",						//5
					"Reserved",						//6
					"Reserved",						//7
					"Reserved",						//8
					"Reserved",						//9
					"Traceroute",								//30
					"Datagram Conversion Error",				//1
					"Mobile Host Redirect (Deprecated)",		//2
					"IPv6 Where-Are-You (Deprecated)",			//3
					"IPv6 I-Am-Here (Deprecated)",				//4
					"Mobile Registration Request (Deprecated)",	//5
					"Mobile Registration Reply (Deprecated)",	//6
					"Domain Name Request (Deprecated)",			//7
					"Domain Name Reply (Deprecated)",			//8
					"SKIP (Deprecated)",						//9
					"Photuris",									//40
					"ICMP messages utilized by experimental mobility protocols", //1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//50
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//60
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//70
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//80
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//90
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//100
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//110
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//120
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//130
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//140
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//150
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//160
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//170
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//180
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//190
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//200
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//210
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//220
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//230
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//240
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Unassigned",						//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned",						//250
					"Unassigned",						//1
					"Unassigned",						//2
					"Unassigned",						//3
					"Unassigned",						//4
					"Reserved",							//5
					"Unassigned",						//6
					"Unassigned",						//7
					"Unassigned",						//8
					"Unassigned",						//9
					"Unassigned"						//260
	};
};

#endif /* SRC_ICMP_H_ */
