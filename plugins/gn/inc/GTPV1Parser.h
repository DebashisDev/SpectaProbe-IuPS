/*
 * GTPCParser.h
 *
 *  Created on: 10-Aug-2016
 *      Author: deb
 */

#ifndef PLUGINS_GN_SRC_GTPCV1PARSER_H_
#define PLUGINS_GN_SRC_GTPCV1PARSER_H_

#include "Log.h"
#include "GTPGlobal.h"
#include "ProbeUtility.h"
#include "GTPMessage.h"

#define GTPv1		1
#define GTPv2		2

#pragma pack(push,1)
	struct GTP_V1_hdr {
	#if BYTE_ORDER == LITTLE_ENDIAN
		uint8_t		pdu_no_flag : 1;			/* N-PDU number flag */
		uint8_t		suquence_no_flag  : 1;		/* sequence number flag */
		uint8_t		extended_header_flag  : 1;	/* extension header flag */
		uint8_t     Spare :1;					/* spare bit = 0 */
		uint8_t		protocol_type_flag : 1; 	/* protocol type */
		uint8_t		Version:3;					/* version */
	#endif
	#if BYTE_ORDER == BIG_ENDIAN
		uint8_t		Version:3;					/* version */
		uint8_t		protocol_type_flag : 1; 	/* protocol type */
		uint8_t		Spare :1;					/* spare bit = 0 */
		uint8_t		extended_header_flag  : 1;	/* extension header flag */
		uint8_t		suquence_no_flag  : 1;		/* sequence number flag */
		uint8_t		pdu_no_flag : 1;			/* N-PDU number flag */
	#endif
		uint8_t		MsgType;
		uint16_t	MsgLen;						/* message len,not include header(whole len -8) */
		uint32_t	MsgTeid;					/* teid */
		uint16_t 	Sequence;					/* sequence number */
		uint8_t		N_PDU_Num;					/* N-PDU number */
		uint8_t		ExHeadType;					/* extension header type */
	};
#pragma pack(pop)

class GTPV1Parser : public ProbeUtility
{
	private:
		size_t m_HeaderLen;
		GTP_V1_hdr* hdrv1;
		GTP_V1_hdr* hdr;
		GTPMessage *gtpMessage;

		size_t size_of_hdr;
		size_t header_size;
		int _thisLogLevel;
		string _name;

		inline int thisLogLevel () const {return _thisLogLevel;}
		inline string name() const {return _name;}

		VOID processPacket(const BYTE packet, MPacket *msgObj);
		BOOL isValidInformationElement(const uint8_t first);
		VOID handle_ggsn_sgsn_address(MPacket *msgObj);

	public:
		GTPV1Parser();
		~GTPV1Parser();

		VOID 	setLogLevel (int level) {_thisLogLevel = level;}
		VOID 	parseGtpV1Packet(const BYTE packet, MPacket *msgObj);
		inline GTP_V1_hdr* getGTPHeader(const BYTE packet) { return (GTP_V1_hdr*)packet; };
};

#endif /* PLUGINS_GN_SRC_GTPCV1PARSER_H_ */
