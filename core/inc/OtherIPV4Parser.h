/*
 * OtherIPV4Parser.h
 *
 *  Created on: 18-Jul-2016
 *      Author: deb
 */

#ifndef CORE_SRC_OTHERIPV4PARSER_H_
#define CORE_SRC_OTHERIPV4PARSER_H_

#include <netinet/ip.h>
#include <arpa/inet.h>

#include "SpectaTypedef.h"
#include "BaseConfig.h"
//#include "PacketParser.h"
#include "IPV4Msg.h"
#include "IPGlobal.h"

class OtherIPV4Parser : public BaseConfig
{
	public:
		OtherIPV4Parser();
		~OtherIPV4Parser();

		VOID parsePacket(const BYTE packet, MPacket *msgObj);
//		virtual PacketParser* getNextParser(uint16_t protocolid);
//		virtual TPacket* getMsgObj();
};

#endif /* CORE_SRC_OTHERIPV4PARSER_H_ */
