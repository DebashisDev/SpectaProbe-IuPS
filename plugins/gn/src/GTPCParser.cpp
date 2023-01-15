/*
 * GTPcParser.cpp
 *
 *  Created on: Oct 27, 2016
 *      Author: Debashis
 */

#include "GTPCParser.h"

GTPCParser::GTPCParser() {
	this->_name = "GTPc";
	setLogLevel(Log::theLog().level());

	packet = NULL;
	hdr = 0;
}

GTPCParser::~GTPCParser() {

}

void hexdump1(const void* pv, int len)
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

void GTPCParser::parsePacket(const BYTE pkt, MPacket *msgObj)
{
	packet = pkt + 8; // 8 bytes -- UDP Header Size

	// GTP 1st byte
	if ((VAL_BYTE(packet) & 0xF8) != 0x30) {
		if ((VAL_BYTE(packet) & 0xF8) != 0x48) {
//				TheLog_v1(Log::Info,name()," Packet No.#%d **** Invalid Flag", IPGlobal::t_FrameCount);
//				printf(" Packet No.#%d **** GTP Invalid Flag\n", IPGlobal::t_FrameCount);
				msgObj->ipAppProtocol = 0;
				return;
		}
	}

	hdr = getGTPHeader(packet);

	switch(hdr->Version)
	{
			case GTPv1:
					msgObj->gtpcVersion = GTPv1;
					parseGtpV1Packet(packet, msgObj);
					IPGlobal::gtpVersion = GTPv1;
					break;

//			case GTPv2:
//					msgObj->gtpcVersion = GTPv2;
//					parseGtpV2Packet(packet, msgObj);
//					IPGlobal::gtpVersion = GTPv2;
//
//					break;

			default:
					msgObj->ipAppProtocol = 0;
					break;
	}
}
