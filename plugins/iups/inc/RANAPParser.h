/*
 * RANAPParser.h
 *
 *  Created on: 16-Jul-2016
 *      Author: Deb
 */

#ifndef PLUGINS_IUPS_SRC_RANAPPARSER_H_
#define PLUGINS_IUPS_SRC_RANAPPARSER_H_

#include <string.h>
#include <algorithm>
#include "SpectaTypedef.h"
#include "BaseConfig.h"
#include "IPGlobal.h"
#include "ProbeUtility.h"
//#include "RANAPConstants.h"
#include "NASParser.h"
#include "SCCPSessionManager.h"
#include "SCCPGlobal.h"
#include "ranap.h"
#include "ProbeUtility.h"

#define PDU_TYPEDEF			RANAP_PDU		/* representation class */
#define PDU_CONTAINER		RANAP_PDU_PDU	/* coding class */
#define UNIV_CONTAINER		ranap_PDU			/* universal coding container */
#define CTLTBL				ranap_Control   	/* control class */

#define ENCODING_RULES		OSS_PER_ALIGNED 	/* encoding rules */
#define XML_ENCODING_RULES	OSS_XER 			/* encoding rules */

class RANAPParser : public BaseConfig, public ProbeUtility
{
	private:

		NASParser *nasParser;
//		MPacket *msgObj;
//		SCCPSessionManager *sm;

		CTLTBL ctl;								/* ASN.1/C++ control object */


//		OssGlobal	w, *world = &w;						/* structure ossGlobal */
//		rnpRANAP_PDU *DecodedDataPtr;

		std::map<std::string,int> MAP_RANAP_ID;

		VOID parseRanapProcedures(int proc_id, std::string xmlin, int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		VOID parsePacketToXml(const BYTE packet, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		string decode_ranap_packet(const BYTE packet, int length);
		BYTE packStringToByteArray(string input);
		std::string get_value(std::string inxml, std::string cmptag);
		std::string get_value(int startPos, std::string inxml, std::string cmptag);
		std::string processIMSI(std::string imsi);
		VOID PLMNHexDec();
		VOID makeNewRAI();
		VOID setRABCauseId(MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
//		VOID traceSessionXml(string xml);
		VOID printPacketBytes(const BYTE packet, int size);

	public:
		RANAPParser();
		~RANAPParser();
		VOID initialize();
		VOID parsePacket(const BYTE packet, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
//		virtual PacketParser* getNextParser(uint16_t protocolid);
//		virtual MPacket* getMsgObj();

		std::string getRanapXML();

};


#endif /* PLUGINS_IUPS_SRC_RANAPPARSER_H_ */
