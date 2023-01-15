/*
 * PacketParser.h
 *
 *  Created on: 04-Jul-2016
 *      Author: deb
 */

#ifndef CORE_SRC_PACKETPARSER_H_
#define CORE_SRC_PACKETPARSER_H_

#include "SpectaTypedef.h"
#include "IPGlobal.h"

class PacketParser {

	public:
		PacketParser();
		virtual ~PacketParser();
		virtual VOID parsePacket(const BYTE packet, TPacket *msgObj) = 0;
		virtual PacketParser* getNextParser(uint16_t protocol) = 0;
		virtual TPacket* getMsgObj() = 0;
};

#endif /* CORE_SRC_PACKETPARSER_H_ */
