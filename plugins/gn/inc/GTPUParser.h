/*
 * GTPUParser.h
 *
 *  Created on: 02-Aug-2016
 *      Author: deb
 */

#ifndef PLUGINS_GN_SRC_GTPUPARSER_H_
#define PLUGINS_GN_SRC_GTPUPARSER_H_

#include <netinet/ip.h>
//#include <arpa/inet.h>
//#include <netinet/udp.h>
//#include <netinet/in.h>

//#include "IPv4Layer.h"
#include "Log.h"
#include "BaseConfig.h"
#include "TCPParser.h"
#include "UDPParser.h"
#include "ProbeUtility.h"
#include "OtherIPV4Parser.h"
#include "DnsData.h"

#define UDP_HDR_LEN		8


#pragma pack(push,1)
	struct GTP_hdr {
	#if BYTE_ORDER == LITTLE_ENDIAN
		/* basic 8 bytes */
		uint8_t		pdu_no_flag : 1;	/* N-PDU number flag */
		uint8_t		suquence_no_flag  : 1;	/* sequence number flag */
		uint8_t		extended_header_flag  : 1;	/* extension header flag */
		uint8_t     Spare :1;	/* spare bit = 0 */
		uint8_t		protocol_type_flag : 1; 	/* protocol type */
		uint8_t		Version:3;	/* version */
		#endif
	#if BYTE_ORDER == BIG_ENDIAN
		uint8_t		Version:3;	/* version */
		uint8_t		protocol_type_flag : 1; 	/* protocol type */
		uint8_t		Spare :1;	/* spare bit = 0 */
		uint8_t		extended_header_flag  : 1;	/* extension header flag */
		uint8_t		suquence_no_flag  : 1;	/* sequence number flag */
		uint8_t		pdu_no_flag : 1;	/* N-PDU number flag */
	#endif
		uint8_t		MsgType;
		uint16_t	MsgLen;		/* message len,not include header(whole len -8) */
		uint32_t	MsgTeid;	/* teid */
	/* look as payload */
		// only be considered if E_f, S_f, PN_f
		uint16_t 	Sequence;	/* sequence number */
		uint8_t		N_PDU_Num;	/* N-PDU number */
		uint8_t		ExHeadType;	/* extension header type */
	};
#pragma pack(pop)
typedef enum
{
	GTP_P_TCP = 0,
	GTP_P_UDP,
	GTP_P_OTR,
}GTPParserId;

class GTPUParser : public BaseConfig, public ProbeUtility {

private:
	TCPParser *tcpParser;
	UDPParser *udpParser;
	OtherIPV4Parser *otrParser;
	DnsData *dnsData;

	GTP_hdr* hdr;
	struct iphdr* iph;

	BYTE packet;

public:
	GTPUParser();
	~GTPUParser();

	VOID 	parsePacket(const BYTE packet, MPacket *tPacket);
	VOID 	parseGTPuIP(const BYTE packet, MPacket *msgObj);

	VOID	parseNextLayer(const BYTE packet, MPacket *msgObj);
	VOID	getIPDirection(MPacket *msgObj);

	inline GTP_hdr* getGTPHeader() { return (GTP_hdr*)packet; };
};

#endif /* PLUGINS_GN_SRC_GTPUPARSER_H_ */
