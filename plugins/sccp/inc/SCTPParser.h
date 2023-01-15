/*
 * PSCTP.h
 *
 *  Created on: 14-Jul-2016
 *      Author: deb
 */

#ifndef PLUGINS_SCTP_SRC_PSCTP_H_
#define PLUGINS_SCTP_SRC_PSCTP_H_

#include "BaseConfig.h"
#include "SpectaTypedef.h"
#include "IPGlobal.h"
#include "MTP3Parser.h"
//#include "MMEParser.h"
#include "TCPParser.h"
#include "Log.h"

#define SCTP_DATA 0
#define SCTP_INIT 1
#define SCTP_INIT_ACK 2
#define SCTP_SACK 3
#define SCTP_HEARTBEAT 4
#define SCTP_HEARTBEAT_ACK 5
#define SCTP_ABORT 6
#define SCTP_SHUTDOWN 7
#define SCTP_SHUTDOWN_ACK 8
#define SCTP_ERROR 9
#define SCTP_COOKIE_ECHO 10
#define SCTP_COOKIE_ACK 11
#define SCTP_ECNE 12
#define SCTP_CWR 13
#define SCTP_SHUTDOWN_COMPLETE 14

//const char *SCTP_TYPE_Val_String[15]={
//	"SCTP_DATA",
//	"SCTP_INIT",
//	"SCTP_INIT_ACK",
//	"SCTP_SACK",
//	"SCTP_HEARTBEAT",
//	"SCTP_HEARTBEAT_ACK",
//	"SCTP_ABORT",
//	"SCTP_SHUTDOWN",
//	"SCTP_SHUTDOWN_ACK",
//	"SCTP_ERROR",
//	"SCTP_COOKIE_ECHO",
//	"SCTP_COOKIE_ACK",
//	"SCTP_ECNE",
//	"SCTP_CWR",
//	"SCTP_SHUTDOWN_COMPLETE"
//};

//defines for the packet type code in an ETHERNET header
#define IPPROTO_M3UA (0x0003)
#define IPPROTO_S1AP (0x0012)

struct sctphdr {
	unsigned short source_port;	// 2 bytes
	unsigned short dest_port;
	unsigned int verification_tag;
	unsigned int checksum;
	/* chunks follow */
}__attribute__((packed));

/*
** SCTP chunk params
*/
struct sctp_chunkhdr {
	unsigned char chunk_type;
	unsigned char chunk_flags;
	unsigned short chunk_length;
	/* optional params */
}__attribute__((packed));


/*
** SCTP chunk
*/
struct sctp_chunk {
	unsigned int tsn_ack;
	unsigned int arwc;
	unsigned short ngab;
	unsigned short nd_tsn;
	/* optional params */
}__attribute__((packed));

/*
** sctp chunk data type zero
*/
struct sctp_datahdr {
	unsigned int tsn;
	unsigned short stream_id;
	unsigned short sequence_no;
	unsigned int protocol_identifier;
	//unsigned char payload[0];
}__attribute__((packed));

/*
** SCTOP chunk optional/varibale length paramaters definiton
*/
struct sctp_paramhdr {
	unsigned short param_type;
	unsigned short param_length;
}__attribute__((packed));


class SCTPParser : public BaseConfig
{
	private:
		int decode_sctp_chunk_data(const BYTE packet, int offset, int data_length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		MTP3Parser *mtp3;
		SCTP *sctpMsgObj;

	public:
		SCTPParser();
		~SCTPParser();

		std::map<uint64_t, SCTPChunkMap > sctpMap;

		void parsePacket(const BYTE packet, MPacket *msgObj);
};

#endif /* PLUGINS_SCTP_SRC_PSCTP_H_ */
