/*
 * GTPcParser.h
 *
 *  Created on: Oct 27, 2016
 *      Author: Debashis
 */

#ifndef PLUGINS_GN_SRC_GTPCPARSER_H_
#define PLUGINS_GN_SRC_GTPCPARSER_H_

#include "Log.h"
#include "GTPGlobal.h"
#include "GTPV1Parser.h"


#pragma pack(push,1)
	struct GTPc_hdr {
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

class GTPCParser : public GTPV1Parser {

	private:
			int _thisLogLevel;
			string _name;
			GTPc_hdr* hdr;
			BYTE packet;
			inline int thisLogLevel () const {return _thisLogLevel;}
			inline string name() const {return _name;}
	public:
			GTPCParser();
			~GTPCParser();

			void parsePacket(BYTE packet, MPacket *msgObj);

			VOID 	setLogLevel (int level) {_thisLogLevel = level;}
			inline GTPc_hdr* getGTPHeader(const BYTE packet) { return (GTPc_hdr*)packet; };
};

#endif /* PLUGINS_GN_SRC_GTPCPARSER_H_ */
