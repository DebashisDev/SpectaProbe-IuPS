/*
 * MTP3Parser.h
 *
 *  Created on: 14-Jul-2016
 *      Author: deb
 */

#ifndef PLUGINS_SCTP_SRC_MTP3PARSER_H_
#define PLUGINS_SCTP_SRC_MTP3PARSER_H_

#include <arpa/inet.h>
#include <pcap.h>
#include <stdlib.h>    //malloc
#include <string.h>    //strlen
#include "IPGlobal.h"
#include "SCCPParser.h"

struct ss7hdr {
	unsigned int opc;		// 4 byte
	unsigned int dpc;		// 4 byte
	unsigned char si;		// 1 byte
	unsigned char ni;
	unsigned char mp;
	unsigned char sls;
}__attribute__((packed));

struct m3uahdr {
	unsigned char version;
	unsigned char reserved;
	unsigned char msg_class;
	unsigned char msg_type;
	unsigned int msg_length;	// 4 bytes
}__attribute__((packed));

class MTP3Parser {
	private:
		SCCPParser *sccp;

		public:
		MTP3Parser();
		~MTP3Parser();

		void processPacket(const BYTE packet, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo, int length);

};

#endif /* PLUGINS_SCTP_SRC_MTP3PARSER_H_ */
