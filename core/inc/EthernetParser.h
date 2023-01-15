/*
 * EthernetProbe.h
 *
 *  Created on: 30-Jan-2016
 *      Author: deb
 */

#ifndef CORE_SRC_ETHERNETPARSER_H_
#define CORE_SRC_ETHERNETPARSER_H_

#include <string.h>
#include <algorithm>
#include <stdlib.h>    //malloc

#include <netinet/ether.h>
#include <netinet/if_ether.h>
#include <pcap/vlan.h>
#include <netinet/udp.h>
#include <netinet/in.h>

#include "Log.h"
#include "BaseConfig.h"
#include "IPGlobal.h"
#include "IPV4Msg.h"
#include "TCPParser.h"
#include "UDPParser.h"
#include "GTPCParser.h"
#include "GTPUParser.h"
#include "ProbeUtility.h"
#include "GTPGlobal.h"
#include "SCTPParser.h"

#define ETH_P_MPLS 34887
#define MPLS_PACKET_SIZE 4

class EthernetParser : public BaseConfig
{
	private:

		TCPParser		*tcp;
		UDPParser		*udp;
		GTPCParser		*gtpc;
		GTPUParser		*gtpu;

		uint128_t SESSION_KEY_MULTI_1		=		10000000000;
		uint128_t SESSION_KEY_MULTI_2		=		100000;

		struct vlan_tag *ptr_vlan_t;
		uint8_t packet_size;
		uint8_t user_p;
		uint8_t canonical_f;
		uint16_t vlan_id;
		uint16_t type;
		uint16_t vlan_tpid;
		TCHAR destMacAddr[18], sourceMacAddr[18];
		string exp, stack;

		int interfaceId = 0;
		int routerId = 0;

		struct iphdr* 		iph;
		tcphdr 				*tcpHeader;
		struct udphdr 		*udpHeader;

		VOID 	parseNextLayer(const BYTE packet, MPacket *msgObj);
//		u_short getEthData(const BYTE packet, TPacket *msgObj);
		VOID 	parse8021QPacket(const BYTE packet, MPacket *msgObj);
		VOID	parseIPV4Packet(const BYTE packet, MPacket *msgObj);
		VOID 	parseMPLSPacket(const BYTE packet, MPacket *msgObj);

		VOID 	getGTPProtocolType(const BYTE packet, MPacket *msgObj);
		VOID 	getGxProtocolType(const BYTE packet, MPacket *msgObj);
//		VOID 	getDirection(MPacket *msgObj);
		string  getBits(unsigned int x);

	public:
		SCTPParser		*sctp;
		VOID 	parsePacket(const BYTE packet, MPacket *msgObj);
		EthernetParser(int intfid, int rId);
		~EthernetParser();
};

#endif /* CORE_SRC_ETHERNETPARSER_H_ */
